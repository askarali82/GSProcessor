//---------------------------------------------------------------------------
#include <System.hpp>
#pragma hdrstop

#include "BatchProcessingThreadU.h"
#include "Spectrum.hpp"
#include "Common.h"
#include "BatchProcessingResultsFormU.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TBatchProcessingThread::TBatchProcessingThread(
    const TData &BData, const String &DirName, TStrings *Files, HWND WndToNotify):
    TThread(false),
    BaseData(BData),
    DirectoryName(DirName),
    LangID(::LangID),
    FileNames(new TStringList()),
    WindowToNotify(WndToNotify),
    Be7IsCalculated(false)
{
    try
    {
        if (!DirectoryName.IsEmpty())
        {
            GetFilesList();
        }
        else
        {
            FileNames->Assign(Files);
            FileNames->Sort();
        }
    }
    catch (const Exception &E)
    {
        Terminate();
        String Msg = L"Quyidagi xatolik yuz berdi:\r\n" + E.Message;
        String Title = L"Xato";
        if (LangID == 1)
        {
            Msg = L"The following error occurred:\r\n" + E.Message;
            Title = L"Error";
        }
        Application->MessageBox(Msg.c_str(), Title.c_str(), MB_OK | MB_ICONERROR);
    }
}
//---------------------------------------------------------------------------
void TBatchProcessingThread::GetFilesList()
{
    try
    {
        FileNames->Clear();
        const String &Path = DirectoryName + L"\\";
        TSearchRec SR;
        if (FindFirst(Path + "*.asw", faAnyFile, SR) != 0)
        {
            return;
        }
        try
        {
            do
            {
                if ((SR.Attr & faDirectory) == 0)
                {
                    FileNames->Add(Path + SR.Name);
                }
            } while (FindNext(SR) == 0);
        }
        __finally
        {
            FindClose(SR);
        }
    }
    catch (const Exception &)
    {
    }
}
//---------------------------------------------------------------------------
void __fastcall TBatchProcessingThread::Execute()
{
    try
    {
        Be7IsCalculated =
            BaseData.BeEn1 > 0 && BaseData.BeEn2 > 0 &&
            BaseData.BeEn2 > BaseData.BeEn1 &&
            BaseData.BePhotopeakEff1 > 0 && BaseData.BePhotopeakEff2 > 0 && BaseData.BePhotopeakEff3 > 0;

        for (int i = 0; !Terminated && i < FileNames->Count; i++)
        {
            const String &FileName = FileNames->Strings[i];
            TResultItem *ResultItem = new TResultItem();
            ResultItem->FileName = FileName;
            try
            {
                LOG("Working with '" + FileName + "' ...");
                TSpectrum WorkSpc;
                if (!WorkSpc.LoadFromFile(FileName, false))
                {
                    String Msg = L"Spektrni o'qishni imkoni bo'lmadi: ";
                    if (LangID == 1)
                    {
                        Msg = L"Couldn't read spectrum: ";
                    }
                    throw Exception(Msg + WorkSpc.ErrorMessage);
                }
                else if (!Utils::IsEqual(WorkSpc.Volume, BaseData.Ths[1].Volume))
                {
                    String Msg = L"Spektrda namuna hajmi noto'g'ri.";
                    if (LangID == 1)
                    {
                        Msg = L"Sample volume is not valid.";
                    }
                    throw Exception(Msg);
                }
                if (!CreateVirtualSpectra(WorkSpc))
                {
                    continue;
                }
                CalculateActivities(
                    WorkSpc,
                    ResultItem->ThActivity,
                    ResultItem->ThC,
                    ResultItem->RaActivity,
                    ResultItem->RaC,
                    ResultItem->KActivity,
                    ResultItem->KC,
                    ResultItem->CsActivity,
                    ResultItem->CsC,
                    ResultItem->BeActivity);
            }
            catch (const Exception &E)
            {
                LOGEXCEPTION(E);
                ResultItem->OK = false;
                ResultItem->Comment = E.Message;
            }
            PostMessage(WindowToNotify, WM_POSTRESULT, (WPARAM)ResultItem, 0);
        }
    }
    catch (const Exception &E)
    {
        LOGEXCEPTION(E);
    }
}
//---------------------------------------------------------------------------
bool TBatchProcessingThread::CreateVirtualSpectra(const TSpectrum &Spectrum)
{
    const double DensityInGramPerLitre = Spectrum.DensityInGramPerLitre;

    if (BaseData.ValidSpectra(0) && BaseData.ValidSpectra(1) && BaseData.ValidSpectra(2))
    {
        String ErrorMsg;

        // Th-232
        bool DensityOK =
            BaseData.Ths[1].DensityInGramPerLitre > BaseData.Ths[0].DensityInGramPerLitre &&
            BaseData.Ths[1].DensityInGramPerLitre < BaseData.Ths[2].DensityInGramPerLitre;
        if (!DensityOK)
        {
            ErrorMsg = L"Th-232 etalon namunalari zichliklarida xatolik bor.";
            if (LangID == 1)
            {
                ErrorMsg = L"Error in densities of Th-232 standard samples.";
            }
            throw Exception(ErrorMsg);
        }
        Utils::NormalizeStandardSources(BaseData.Ths[1], const_cast<TSpectrum &>(BaseData.Ths[0]), BaseData.ThEn1, BaseData.ThEn2);
        Utils::NormalizeStandardSources(BaseData.Ths[1], const_cast<TSpectrum &>(BaseData.Ths[2]), BaseData.ThEn1, BaseData.ThEn2);
        if (DensityInGramPerLitre <= BaseData.Ths[1].DensityInGramPerLitre)
        {
            const double K1 = (1 - ((BaseData.Ths[1].DensityInGramPerLitre - DensityInGramPerLitre) /
                (BaseData.Ths[1].DensityInGramPerLitre - BaseData.Ths[0].DensityInGramPerLitre)));
            const double K2 = ((BaseData.Ths[1].DensityInGramPerLitre - DensityInGramPerLitre) /
                (BaseData.Ths[1].DensityInGramPerLitre - BaseData.Ths[0].DensityInGramPerLitre));

            ThSpc = BaseData.Ths[1].Multiply(K1);
            TSpectrum Sum;
            TSpectrum::CheckError(ThSpc.Add(BaseData.Ths[0].Multiply(K2), Sum), ThSpc.ErrorMessage);
            ThSpc = Sum;
        }
        else
        {
            const double K1 = (1 - ((BaseData.Ths[2].DensityInGramPerLitre - DensityInGramPerLitre) /
                    (BaseData.Ths[2].DensityInGramPerLitre - BaseData.Ths[1].DensityInGramPerLitre)));
            const double K2 = ((BaseData.Ths[2].DensityInGramPerLitre - DensityInGramPerLitre) /
                    (BaseData.Ths[2].DensityInGramPerLitre - BaseData.Ths[1].DensityInGramPerLitre));

            ThSpc = BaseData.Ths[2].Multiply(K1);
            TSpectrum Sum;
            TSpectrum::CheckError(ThSpc.Add(BaseData.Ths[1].Multiply(K2), Sum), ThSpc.ErrorMessage);
            ThSpc = Sum;
        }

        // Ra-226
        DensityOK =
            BaseData.Ras[1].DensityInGramPerLitre > BaseData.Ras[0].DensityInGramPerLitre &&
            BaseData.Ras[1].DensityInGramPerLitre < BaseData.Ras[2].DensityInGramPerLitre;
        if (!DensityOK)
        {
            ErrorMsg = L"Ra-226 etalon namunalari zichliklarida xatolik bor.";
            if (LangID == 1)
            {
                ErrorMsg = L"Error in densities of Ra-226 standard samples.";
            }
            throw Exception(ErrorMsg);
        }
        Utils::NormalizeStandardSources(BaseData.Ras[1], const_cast<TSpectrum &>(BaseData.Ras[0]), BaseData.RaEn1, BaseData.RaEn2);
        Utils::NormalizeStandardSources(BaseData.Ras[1], const_cast<TSpectrum &>(BaseData.Ras[2]), BaseData.RaEn1, BaseData.RaEn2);
        if (DensityInGramPerLitre <= BaseData.Ras[1].DensityInGramPerLitre)
        {
            const double K1 = (1 - ((BaseData.Ras[1].DensityInGramPerLitre - DensityInGramPerLitre) /
                    (BaseData.Ras[1].DensityInGramPerLitre - BaseData.Ras[0].DensityInGramPerLitre)));
            const double K2 = ((BaseData.Ras[1].DensityInGramPerLitre - DensityInGramPerLitre) /
                    (BaseData.Ras[1].DensityInGramPerLitre - BaseData.Ras[0].DensityInGramPerLitre));

            RaSpc = BaseData.Ras[1].Multiply(K1);
            TSpectrum Sum;
            TSpectrum::CheckError(RaSpc.Add(BaseData.Ras[0].Multiply(K2), Sum), RaSpc.ErrorMessage);
            RaSpc = Sum;
        }
        else
        {
            const double K1 = (1 - ((BaseData.Ras[2].DensityInGramPerLitre - DensityInGramPerLitre) /
                    (BaseData.Ras[2].DensityInGramPerLitre - BaseData.Ras[1].DensityInGramPerLitre)));
            const double K2 = ((BaseData.Ras[2].DensityInGramPerLitre - DensityInGramPerLitre) /
                    (BaseData.Ras[2].DensityInGramPerLitre - BaseData.Ras[1].DensityInGramPerLitre));

            RaSpc = BaseData.Ras[2].Multiply(K1);
            TSpectrum Sum;
            TSpectrum::CheckError(RaSpc.Add(BaseData.Ras[1].Multiply(K2), Sum), RaSpc.ErrorMessage);
            RaSpc = Sum;
        }

        // K-40
        DensityOK =
            BaseData.Ks[1].DensityInGramPerLitre > BaseData.Ks[0].DensityInGramPerLitre &&
            BaseData.Ks[1].DensityInGramPerLitre < BaseData.Ks[2].DensityInGramPerLitre;
        if (!DensityOK)
        {
            ErrorMsg = L"K-40 etalon namunalari zichliklarida xatolik bor.";
            if (LangID == 1)
            {
                ErrorMsg = L"Error in densities of K-40 standard samples.";
            }
            throw Exception(ErrorMsg);
        }
        Utils::NormalizeStandardSources(BaseData.Ks[1], const_cast<TSpectrum &>(BaseData.Ks[0]), BaseData.KEn1, BaseData.KEn2);
        Utils::NormalizeStandardSources(BaseData.Ks[1], const_cast<TSpectrum &>(BaseData.Ks[2]), BaseData.KEn1, BaseData.KEn2);
        if (DensityInGramPerLitre <= BaseData.Ks[1].DensityInGramPerLitre)
        {
            const double K1 = (1 - ((BaseData.Ks[1].DensityInGramPerLitre - DensityInGramPerLitre) /
                    (BaseData.Ks[1].DensityInGramPerLitre - BaseData.Ks[0].DensityInGramPerLitre)));
            const double K2 = ((BaseData.Ks[1].DensityInGramPerLitre - DensityInGramPerLitre) /
                    (BaseData.Ks[1].DensityInGramPerLitre - BaseData.Ks[0].DensityInGramPerLitre));

            KSpc = BaseData.Ks[1].Multiply(K1);
            TSpectrum Sum;
            TSpectrum::CheckError(KSpc.Add(BaseData.Ks[0].Multiply(K2), Sum), KSpc.ErrorMessage);
            KSpc = Sum;
        }
        else
        {
            const double K1 = (1 - ((BaseData.Ks[2].DensityInGramPerLitre - DensityInGramPerLitre) /
                    (BaseData.Ks[2].DensityInGramPerLitre - BaseData.Ks[1].DensityInGramPerLitre)));
            const double K2 = ((BaseData.Ks[2].DensityInGramPerLitre - DensityInGramPerLitre) /
                    (BaseData.Ks[2].DensityInGramPerLitre - BaseData.Ks[1].DensityInGramPerLitre));

            KSpc = BaseData.Ks[2].Multiply(K1);
            TSpectrum Sum;
            TSpectrum::CheckError(KSpc.Add(BaseData.Ks[1].Multiply(K2), Sum), KSpc.ErrorMessage);
            KSpc = Sum;
        }

        // Cs-137
        DensityOK =
            BaseData.Css[1].DensityInGramPerLitre > BaseData.Css[0].DensityInGramPerLitre &&
            BaseData.Css[1].DensityInGramPerLitre < BaseData.Css[2].DensityInGramPerLitre;
        if (!DensityOK)
        {
            ErrorMsg = L"Cs-137 etalon namunalari zichliklarida xatolik bor.";
            if (LangID == 1)
            {
                ErrorMsg = L"Error in densities of Cs-137 standard samples.";
            }
            throw Exception(ErrorMsg);
        }
        Utils::NormalizeStandardSources(BaseData.Css[1], const_cast<TSpectrum &>(BaseData.Css[0]), BaseData.CsEn1, BaseData.CsEn2);
        Utils::NormalizeStandardSources(BaseData.Css[1], const_cast<TSpectrum &>(BaseData.Css[2]), BaseData.CsEn1, BaseData.CsEn2);
        if (DensityInGramPerLitre <= BaseData.Css[1].DensityInGramPerLitre)
        {
            const double K1 = (1 - ((BaseData.Css[1].DensityInGramPerLitre - DensityInGramPerLitre) /
                    (BaseData.Css[1].DensityInGramPerLitre - BaseData.Css[0].DensityInGramPerLitre)));
            const double K2 = ((BaseData.Css[1].DensityInGramPerLitre - DensityInGramPerLitre) /
                    (BaseData.Css[1].DensityInGramPerLitre - BaseData.Css[0].DensityInGramPerLitre));

            CsSpc = BaseData.Css[1].Multiply(K1);
            TSpectrum Sum;
            TSpectrum::CheckError(CsSpc.Add(BaseData.Css[0].Multiply(K2), Sum), CsSpc.ErrorMessage);
            CsSpc = Sum;
        }
        else
        {
            const double K1 = (1 - ((BaseData.Css[2].DensityInGramPerLitre - DensityInGramPerLitre) /
                    (BaseData.Css[2].DensityInGramPerLitre - BaseData.Css[1].DensityInGramPerLitre)));
            const double K2 = ((BaseData.Css[2].DensityInGramPerLitre - DensityInGramPerLitre) /
                    (BaseData.Css[2].DensityInGramPerLitre - BaseData.Css[1].DensityInGramPerLitre));

            CsSpc = BaseData.Css[2].Multiply(K1);
            TSpectrum Sum;
            TSpectrum::CheckError(CsSpc.Add(BaseData.Css[1].Multiply(K2), Sum), CsSpc.ErrorMessage);
            CsSpc = Sum;
        }

        // Fon
        DensityOK =
            BaseData.Bkgs[1].DensityInGramPerLitre > BaseData.Bkgs[0].DensityInGramPerLitre &&
            BaseData.Bkgs[1].DensityInGramPerLitre < BaseData.Bkgs[2].DensityInGramPerLitre;
        if (!DensityOK)
        {
            ErrorMsg = L"Tabiiy fon namunalari zichliklarida xatolik bor.";
            if (LangID == 1)
            {
                ErrorMsg = L"Error in densities of background samples.";
            }
            throw Exception(ErrorMsg);
        }
        if (DensityInGramPerLitre <= BaseData.Bkgs[1].DensityInGramPerLitre)
        {
            const double K1 = (1 - ((BaseData.Bkgs[1].DensityInGramPerLitre - DensityInGramPerLitre) /
                    BaseData.Bkgs[1].DensityInGramPerLitre));
            const double K2 = ((BaseData.Bkgs[1].DensityInGramPerLitre - DensityInGramPerLitre) /
                    BaseData.Bkgs[1].DensityInGramPerLitre);

            BkgSpc = BaseData.Bkgs[1].Multiply(K1);
            TSpectrum Sum;
            TSpectrum::CheckError(BkgSpc.Add(BaseData.Bkgs[0].Multiply(K2), Sum), BkgSpc.ErrorMessage);
            BkgSpc = Sum;
        }
        else
        {
            const double K1 = (1 - ((BaseData.Bkgs[2].DensityInGramPerLitre - DensityInGramPerLitre) /
                    (BaseData.Bkgs[2].DensityInGramPerLitre - BaseData.Bkgs[1].DensityInGramPerLitre)));
            const double K2 = ((BaseData.Bkgs[2].DensityInGramPerLitre - DensityInGramPerLitre) /
                    (BaseData.Bkgs[2].DensityInGramPerLitre - BaseData.Bkgs[1].DensityInGramPerLitre));

            BkgSpc = BaseData.Bkgs[2].Multiply(K1);
            TSpectrum Sum;
            TSpectrum::CheckError(BkgSpc.Add(BaseData.Bkgs[1].Multiply(K2), Sum), BkgSpc.ErrorMessage);
            BkgSpc = Sum;
        }
        return true;
    }
    else
    {
        LOG(L"One or more reference and/or background samples spectra not found.");
        return false;
    }
}
//---------------------------------------------------------------------------
void TBatchProcessingThread::CalculateCountsAndActivitiesInStdSamples()
{
    ThCount = ThSpc.CalculateCountByEnergyRange(BaseData.ThEn1, BaseData.ThEn2);
    ThActivity =
        StrToFloat(ThSpc.ExtraStringData) *
        System::Exp(-(System::Ln(2) / 1.405E10) * ThSpc.ExtraFloatData);
    auto N_sa = 1.0 / (ThSpc.Duration * ThActivity);
    RaThCount_sa =
        ThSpc.CalculateCountByEnergyRange(BaseData.RaEn1, BaseData.RaEn2) * N_sa;
    KThCount_sa =
        ThSpc.CalculateCountByEnergyRange(BaseData.KEn1, BaseData.KEn2) * N_sa;
    CsThCount_sa =
        ThSpc.CalculateCountByEnergyRange(BaseData.CsEn1, BaseData.CsEn2) * N_sa;
    BeThCount_sa = Be7IsCalculated ?
        ThSpc.CalculateCountByEnergyRange(BaseData.BeEn1, BaseData.BeEn2) * N_sa : 0;


    RaCount = RaSpc.CalculateCountByEnergyRange(BaseData.RaEn1, BaseData.RaEn2);
    RaActivity =
        StrToFloat(RaSpc.ExtraStringData) *
        System::Exp(-(System::Ln(2) / 1602) * RaSpc.ExtraFloatData);
    N_sa = 1.0 / (RaSpc.Duration * RaActivity);
    KRaCount_sa =
        RaSpc.CalculateCountByEnergyRange(BaseData.KEn1, BaseData.KEn2) * N_sa;
    CsRaCount_sa =
        RaSpc.CalculateCountByEnergyRange(BaseData.CsEn1, BaseData.CsEn2) * N_sa;
    BeRaCount_sa = Be7IsCalculated ?
        RaSpc.CalculateCountByEnergyRange(BaseData.BeEn1, BaseData.BeEn2) * N_sa : 0;


    KCount = KSpc.CalculateCountByEnergyRange(BaseData.KEn1, BaseData.KEn2);
    KActivity =
        StrToFloat(KSpc.ExtraStringData) *
        System::Exp(-(System::Ln(2) / 1.251E9) * KSpc.ExtraFloatData);
    N_sa = 1.0 / (KSpc.Duration * KActivity);
    CsKCount_sa =
        KSpc.CalculateCountByEnergyRange(BaseData.CsEn1, BaseData.CsEn2) * N_sa;
    BeKCount_sa = Be7IsCalculated ?
        KSpc.CalculateCountByEnergyRange(BaseData.BeEn1, BaseData.BeEn2) * N_sa : 0;


    CsCount = CsSpc.CalculateCountByEnergyRange(BaseData.CsEn1, BaseData.CsEn2);
    CsActivity =
        StrToFloat(CsSpc.ExtraStringData) *
        System::Exp(-(System::Ln(2) / 30) * CsSpc.ExtraFloatData);
    N_sa = 1.0 / (CsSpc.Duration * CsActivity);
    BeCsCount_sa = Be7IsCalculated ?
        CsSpc.CalculateCountByEnergyRange(BaseData.BeEn1, BaseData.BeEn2) * N_sa : 0;
}
//---------------------------------------------------------------------------
void TBatchProcessingThread::CalculateActivities(
    const TSpectrum &Spectrum, String &ThStr,
    String &ThCstr, String &RaStr, String &RaCstr,
    String &KStr, String &KCstr, String &CsStr,
    String &CsCstr, String &BeStr)
{
    String Msg = L"Spektrlarni ayirishda xatolik yuz berdi.";
    if (LangID == 1)
    {
        Msg = L"An error occurred upon subtracting spectra.";
    }

    CalculateCountsAndActivitiesInStdSamples();

    const double Weight =
        SameText(Spectrum.WeightUnit, L"kg") ? Spectrum.Weight : Spectrum.Weight / 1000;

    const auto InSmpDuration = Spectrum.Duration / BkgSpc.Duration;
    const auto BkgThCount =
        BkgSpc.CalculateCountByEnergyRange(BaseData.ThEn1, BaseData.ThEn2) * InSmpDuration;
    const auto BkgRaCount =
        BkgSpc.CalculateCountByEnergyRange(BaseData.RaEn1, BaseData.RaEn2) * InSmpDuration;
    const auto BkgKCount =
        BkgSpc.CalculateCountByEnergyRange(BaseData.KEn1, BaseData.KEn2) * InSmpDuration;
    const auto BkgCsCount =
        BkgSpc.CalculateCountByEnergyRange(BaseData.CsEn1, BaseData.CsEn2) * InSmpDuration;
    const auto BkgBeCount = Be7IsCalculated ?
        BkgSpc.CalculateCountByEnergyRange(BaseData.BeEn1, BaseData.BeEn2) * InSmpDuration : 0;



    const double MDATh =
        3 * System::Sqrt(BkgThCount) * (ThActivity / (ThCount * (Spectrum.Duration / ThSpc.Duration) * Weight));
    const double MDARa =
        3 * System::Sqrt(BkgRaCount) * (RaActivity / (RaCount * (Spectrum.Duration / RaSpc.Duration) * Weight));
    const double MDAK =
        3 * System::Sqrt(BkgKCount) * (KActivity / (KCount * (Spectrum.Duration / KSpc.Duration) * Weight));
    const double MDACs =
        3 * System::Sqrt(BkgCsCount) * (CsActivity / (CsCount * (Spectrum.Duration / CsSpc.Duration) * Weight));
    const double BePhotopeakEff = Be7IsCalculated ?
        Utils::CalcBe7Effectivity(BaseData.BePhotopeakEff1, BaseData.BePhotopeakEff2, BaseData.BePhotopeakEff3, Spectrum.DensityInGramPerLitre) :
        0;
    const double BeCoeff = Be7IsCalculated ? (0.104 * BePhotopeakEff * Spectrum.Duration) : 0;
    const double MDABe = Be7IsCalculated ? (3 * System::Sqrt(BkgBeCount)) / (BeCoeff * Weight) : 0;

    LOG(L"BePhotopeakEff = " + String(BePhotopeakEff) + L" for density " + String(Spectrum.DensityInGramPerLitre));


    const double dN1 = std::abs(Spectrum.DensityInGramPerLitre - BaseData.Ths[0].DensityInGramPerLitre);
    const double dN2 = std::abs(Spectrum.DensityInGramPerLitre - BaseData.Ths[1].DensityInGramPerLitre);
    const double dN3 = std::abs(Spectrum.DensityInGramPerLitre - BaseData.Ths[2].DensityInGramPerLitre);
    int Idx = 0;
    double MindN = dN1;
    if (dN2 <= MindN)
    {
        MindN = dN2;
        Idx = 1;
    }
    if (dN3 <= MindN)
    {
        Idx = 2;
    }
    const double ThActivityError = BaseData.ThActivityErrors[Idx];
    const double RaActivityError = BaseData.RaActivityErrors[Idx];
    const double KActivityError = BaseData.KActivityErrors[Idx];
    const double CsActivityError = BaseData.CsActivityErrors[Idx];

    TSpectrum SubtractedSpc;
    TSpectrum TMPSpc;
    bool OK = Spectrum.Subtract(BkgSpc.Multiply(InSmpDuration), TMPSpc, true);
    TSpectrum::CheckError(OK, Msg + L"\r\n\r\n" + Spectrum.ErrorMessage);
    SubtractedSpc = TMPSpc;
    const double SmpThCount = SubtractedSpc.CalculateCountByEnergyRange(BaseData.ThEn1, BaseData.ThEn2);
    auto ThC = SmpThCount / ThCount;
    ThC = ThC < 0 ? 0 : ThC;
    ThCstr = Utils::RoundFloatValue(ThC);
    const auto SmpThActivity = (ThSpc.Duration * ThActivity * ThC) / Spectrum.Duration;
    const auto SmpRaThCount = SmpThActivity * Spectrum.Duration * RaThCount_sa;
    const auto SmpKThCount = SmpThActivity * Spectrum.Duration * KThCount_sa;
    const auto SmpCsThCount = SmpThActivity * Spectrum.Duration * CsThCount_sa;
    const auto SmpBeThCount = Be7IsCalculated ? SmpThActivity * BeThCount_sa * Spectrum.Duration: 0;
    const double ThError1 =
        SmpThCount > 0 ? (System::Sqrt(SmpThCount + BkgThCount) / SmpThCount) : 0;
    const double ThError = System::Sqrt(Utils::Sqr(ThError1) + Utils::Sqr(ThActivityError));



    TMPSpc = TSpectrum();
    OK = SubtractedSpc.Subtract(ThSpc.Multiply(ThC), TMPSpc, true);
    TSpectrum::CheckError(OK, Msg + L"\r\n\r\n" + SubtractedSpc.ErrorMessage);
    SubtractedSpc = TMPSpc;
    const double SmpRaCount = SubtractedSpc.CalculateCountByEnergyRange(BaseData.RaEn1, BaseData.RaEn2);
    auto RaC = SmpRaCount / RaCount;
    RaC = RaC < 0 ? 0 : RaC;
    RaCstr = Utils::RoundFloatValue(RaC);
    const auto SmpRaActivity = (RaSpc.Duration * RaActivity * RaC) / Spectrum.Duration;
    const auto SmpKRaCount = SmpRaActivity * Spectrum.Duration * KRaCount_sa;
    const auto SmpCsRaCount = SmpRaActivity * Spectrum.Duration * CsRaCount_sa;
    const auto SmpBeRaCount = Be7IsCalculated ? SmpRaActivity * Spectrum.Duration * BeRaCount_sa : 0;
    const double RaError1 =
        SmpRaCount > 0 ? (System::Sqrt(SmpRaCount + (BkgRaCount + SmpRaThCount)) / SmpRaCount) : 0;
    const double RaError = System::Sqrt(Utils::Sqr(RaError1) + Utils::Sqr(RaActivityError));



    TMPSpc = TSpectrum();
    OK = SubtractedSpc.Subtract(RaSpc.Multiply(RaC), TMPSpc, true);
    TSpectrum::CheckError(OK, Msg + L"\r\n\r\n" + SubtractedSpc.ErrorMessage);
    SubtractedSpc = TMPSpc;
    const double SmpKCount = SubtractedSpc.CalculateCountByEnergyRange(BaseData.KEn1, BaseData.KEn2);
    auto KC = SmpKCount / KCount;
    KC = KC < 0 ? 0 : KC;
    KCstr = Utils::RoundFloatValue(KC);
    const auto SmpKActivity = (KSpc.Duration * KActivity * KC) / Spectrum.Duration;
    const auto SmpCsKCount = SmpKActivity * Spectrum.Duration * CsKCount_sa;
    const auto SmpBeKCount = Be7IsCalculated ? SmpKActivity * Spectrum.Duration * BeKCount_sa : 0;
    const double KError1 =
        SmpKCount > 0 ? (System::Sqrt(SmpKCount + (BkgKCount + SmpKThCount + SmpKRaCount)) / SmpKCount) : 0;
    const double KError  = System::Sqrt(Utils::Sqr(KError1) + Utils::Sqr(KActivityError));



    TMPSpc = TSpectrum();
    OK = SubtractedSpc.Subtract(KSpc.Multiply(KC), TMPSpc, true);
    TSpectrum::CheckError(OK, Msg + L"\r\n\r\n" + SubtractedSpc.ErrorMessage);
    SubtractedSpc = TMPSpc;
    const double SmpCsCount = SubtractedSpc.CalculateCountByEnergyRange(BaseData.CsEn1, BaseData.CsEn2);
    auto CsC = SmpCsCount / CsCount;
    CsC = CsC < 0 ? 0 : CsC;
    CsCstr = Utils::RoundFloatValue(CsC);
    const auto SmpCsActivity = (CsSpc.Duration * CsActivity * CsC) / Spectrum.Duration;
    const auto SmpBeCsCount = Be7IsCalculated ? SmpCsActivity * Spectrum.Duration * BeCsCount_sa : 0;
    const double CsError1 =
        SmpCsCount > 0 ? (System::Sqrt(SmpCsCount + (BkgCsCount + SmpCsThCount + SmpCsRaCount + SmpCsKCount)) / SmpCsCount) : 0;
    const double CsError = System::Sqrt(Utils::Sqr(CsError1) + Utils::Sqr(CsActivityError));



    TMPSpc = TSpectrum();
    OK = SubtractedSpc.Subtract(CsSpc.Multiply(CsC), TMPSpc, true);
    TSpectrum::CheckError(OK, Msg + L"\r\n\r\n" + SubtractedSpc.ErrorMessage);
    SubtractedSpc = TMPSpc;

    const double SmpBeCount =
        Be7IsCalculated ? SubtractedSpc.CalculateCountByEnergyRange(BaseData.BeEn1, BaseData.BeEn2) : 0;

    const auto SmpBeActivity =
        Be7IsCalculated ? SmpBeCount / BeCoeff : 0;

    const double BeError1 =
        Be7IsCalculated ? (System::Sqrt(SmpBeCount + (BkgBeCount + SmpBeThCount + SmpBeRaCount + SmpBeKCount + SmpBeCsCount)) / SmpBeCount) : 0;

    const double BeError =
        Be7IsCalculated ? System::Sqrt(Utils::Sqr(BeError1) + Utils::Sqr(0.1)) : 0;



    const double SmpThActivityPerKg = SmpThActivity / Weight;
    const double SmpRaActivityPerKg = SmpRaActivity / Weight;
    const double SmpKActivityPerKg  = SmpKActivity  / Weight;
    const double SmpCsActivityPerKg = SmpCsActivity / Weight;
    const double SmpBeActivityPerKg = Be7IsCalculated ? SmpBeActivity / Weight : 0;


    static const String PM = L" " + String(Char(0x00B1)) + L" ";

    ThStr =
        SmpThActivityPerKg < MDATh || ThError >= 1 ?
        L"< " + Utils::RoundFloatValue(MDATh, 2, false) :
        Utils::RoundFloatValue(SmpThActivityPerKg, 2, false) + PM +
        Utils::RoundFloatValue(SmpThActivityPerKg * ThError, 2, false);
    RaStr =
        SmpRaActivityPerKg < MDARa || RaError >= 1 ?
        L"< " + Utils::RoundFloatValue(MDARa, 2, false) :
        Utils::RoundFloatValue(SmpRaActivityPerKg, 2, false) + PM +
        Utils::RoundFloatValue(SmpRaActivityPerKg * RaError, 2, false);
    KStr =
        SmpKActivityPerKg < MDAK || KError >= 1 ?
        L"< " + Utils::RoundFloatValue(MDAK, 2, false) :
        Utils::RoundFloatValue(SmpKActivityPerKg, 2, false) + PM +
        Utils::RoundFloatValue(SmpKActivityPerKg * KError, 2, false);
    CsStr =
        SmpCsActivityPerKg < MDACs || CsError >= 1 ?
        L"< " + Utils::RoundFloatValue(MDACs, 2, false) :
        Utils::RoundFloatValue(SmpCsActivityPerKg, 2, false) + PM +
        Utils::RoundFloatValue(SmpCsActivityPerKg * CsError, 2, false);
    if (Be7IsCalculated)
    {
        BeStr =
            SmpBeActivityPerKg < MDABe || BeError >= 1 ?
            L"< " + Utils::RoundFloatValue(MDABe, 2, false) :
            Utils::RoundFloatValue(SmpBeActivityPerKg, 2, false) + PM +
            Utils::RoundFloatValue(SmpBeActivityPerKg * BeError, 2, false);
    }
    else
    {
        BeStr = L"---";
    }
}
