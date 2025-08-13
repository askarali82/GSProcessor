//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "MainFormU.h"
#include "SettingsFormU.h"
#include <memory>
#include <System.StrUtils.hpp>
#include <System.hpp>
#include <System.Math.hpp>
#include <DateUtils.hpp>
#include "shellapi.h"
#include "ShiftingFormU.h"
#include "Common.h"
#include "BatchProcessingResultsFormU.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner):
    TForm(Owner), AppName(L"GSProcessor")
{
    Application->Title = AppName;
    Application->ModalPopupMode = pmAuto;
    Application->OnException = OnAppException;
    Application->HintHidePause = 8000;
    Application->HintPause = 300;
    Caption = AppName;
    FormatSettings.DateSeparator = L'.';
    FormatSettings.DecimalSeparator = L'.';
    FormatSettings.ShortDateFormat = L"dd.mm.yyyy";
    SmpDValEdit1->Text = 0.01;
    SmpDValEdit2->Text = 0.01;
    BkgDValEdit1->Text = 0.01;
    BkgDValEdit2->Text = 0.01;
    ThDValEdit1->Text = 0.01;
    ThDValEdit2->Text = 0.01;
    RaDValEdit1->Text = 0.01;
    RaDValEdit2->Text = 0.01;
    KDValEdit1->Text = 0.01;
    KDValEdit2->Text = 0.01;
    CsDValEdit1->Text = 0.01;
    CsDValEdit2->Text = 0.01;

    std::unique_ptr<TIniFile> SettingsFile(new TIniFile(L".\\Settings.ini"));
    LanguageAction->Tag = SettingsFile->ReadString(L"UILanguage", L"LangID", L"0").ToIntDef(0);
    LangID = LanguageAction->Tag;
    ChangeUILanguage();
    TSpectrum::SetLanguage();

    HRESULT HResult;
    if ((HResult = CoInitializeEx(0, COINIT_APARTMENTTHREADED)) == S_OK || HResult == S_FALSE)
    {
        DispName[0] = 0;
        BrowseInfo.hwndOwner = Handle;
        BrowseInfo.pidlRoot = 0;
        BrowseInfo.pszDisplayName = DispName;
        BrowseInfo.lpszTitle = DirSelectionString.c_str();
        BrowseInfo.ulFlags = BIF_NEWDIALOGSTYLE | BIF_RETURNONLYFSDIRS;
        BrowseInfo.lpfn = 0;
        BrowseInfo.lParam = 0;
        BrowseInfo.iImage = 0;
    }
    else
    {
        const String Msg(
            String(L"Couldn't initialize COM library. Error code: ") + IntToStr((int)HResult) + L". "
            L"Folder browsing dialog box will not work.");
        MessageBox(Handle, Msg.c_str(), 0, MB_ICONERROR | MB_OK);
    }

    FormResize(nullptr);

    ThUpButton->Tag = reinterpret_cast<NativeInt>(ThSnSe2);
    ThDownButton->Tag = reinterpret_cast<NativeInt>(ThSnSe2);

    RaUpButton->Tag = reinterpret_cast<NativeInt>(RaSnSe2);
    RaDownButton->Tag = reinterpret_cast<NativeInt>(RaSnSe2);

    KUpButton->Tag = reinterpret_cast<NativeInt>(KSnSe2);
    KDownButton->Tag = reinterpret_cast<NativeInt>(KSnSe2);

    CsUpButton->Tag = reinterpret_cast<NativeInt>(CsSnSe2);
    CsDownButton->Tag = reinterpret_cast<NativeInt>(CsSnSe2);

    SpectraLoadTimer->Enabled = true;
}
//---------------------------------------------------------------------------
__fastcall TMainForm::~TMainForm()
{
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::OnAppException(TObject* Sender, Exception* E)
{
    const String &Time = Now().FormatString("dd.mm.yyyy - hh:nn:ss");
    const String SenderClassName = Sender->ClassName();
    TControl *C = dynamic_cast<TControl *>(Sender);
    const String SenderName = C == 0 ? String("N/A") : C->Name;
    String SenderParentClassName("N/A");
    String SenderParentName("N/A");
    if (C != 0 && C->Parent != 0)
    {
        SenderParentClassName = C->Parent->ClassName();
        SenderParentName = C->Parent->Name;
    }
    const String ExceptionClassName = E->ClassName();
    LOG("\r\n\r\n"
         "Time: " + Time + L"\r\n"
         "Sender class: " + SenderClassName + L"\r\n"
         "Sender name: " + SenderName + L"\r\n"
         "Sender parent class: " + SenderParentClassName + L"\r\n"
         "Sender parent name: " + SenderParentName + L"\r\n"
         "Exception class: " + ExceptionClassName + L"\r\n"
         "Exception message: " + E->Message + L"\r\n");
    String ErrorMsg =
        L"Quyidagi xatolik yuz berdi. Iltimos, dasturchiga xabar bering:\r\n\r\n" + E->Message;
    if (LangID == 1)
    {
        ErrorMsg = L"The following error occurred. Please inform the developer:\r\n\r\n" + E->Message;
    }
    Application->MessageBox(ErrorMsg.c_str(), ErrorTitle.c_str(), MB_OK | MB_ICONERROR);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormResize(TObject *Sender)
{
    const int CH = ClientHeight - ToolBarPanel->Height - StatusBar->Height - 6;
    const int H = CH / 6;
    const double IW = double(ClientWidth) * 0.6;
    const double SW = ClientWidth - IW - 4;
    const double DIW = IW / 5.0;

    ThInfoPanel->Left = 0;
    ThInfoPanel->Width = DIW - 4;

    RaInfoPanel->Left = ThInfoPanel->Left + ThInfoPanel->Width + 4;
    RaInfoPanel->Width = DIW - 4;

    KInfoPanel->Left = RaInfoPanel->Left + RaInfoPanel->Width + 4;
    KInfoPanel->Width = DIW - 4;
    Application->ProcessMessages();

    CsInfoPanel->Left = KInfoPanel->Left + KInfoPanel->Width + 4;
    CsInfoPanel->Width = DIW - 4;

    SampleInfoPanel->Left = CsInfoPanel->Left + CsInfoPanel->Width + 4;
    SampleInfoPanel->Width = DIW - 4;

    FinalSpcChart->Left = 0;
    FinalSpcChart->Top = SampleInfoPanel->Top + SampleInfoPanel->Height + 2;
    FinalSpcChart->Width = SampleInfoPanel->Left + SampleInfoPanel->Width;
    FinalSpcChart->Height = StatusBar->Top - FinalSpcChart->Top - 2;//FinalSpcChart->Width / 2;
    /*if ((FinalSpcChart->Top + FinalSpcChart->Height) > StatusBar->Top)
    {
        FinalSpcChart->Height = StatusBar->Top - FinalSpcChart->Top - 1;
    }*/
    Application->ProcessMessages();

    SamplePanel->Height = H;
    SamplePanel->Width = SW;
    SamplePanel->Top = ToolBarPanel->Height + 2;
    SamplePanel->Left = ClientWidth - SamplePanel->Width;

    BkgPanel->Height = H;
    BkgPanel->Width = SW;
    BkgPanel->Top = SamplePanel->Top + SamplePanel->Height + 1;
    BkgPanel->Left = ClientWidth - BkgPanel->Width;
    Application->ProcessMessages();

    ThPanel->Height = H;
    ThPanel->Width = SW;
    ThPanel->Top = BkgPanel->Top + BkgPanel->Height + 1;
    ThPanel->Left = ClientWidth - ThPanel->Width;

    RaPanel->Height = H;
    RaPanel->Width = SW;
    RaPanel->Top = ThPanel->Top + ThPanel->Height + 1;
    RaPanel->Left = ClientWidth - RaPanel->Width;
    Application->ProcessMessages();

    KPanel->Height = H;
    KPanel->Width = SW;
    KPanel->Top = RaPanel->Top + RaPanel->Height + 1;
    KPanel->Left = ClientWidth - KPanel->Width;

    CsPanel->Height = H;
    CsPanel->Width = SW;
    CsPanel->Top = KPanel->Top + KPanel->Height + 1;
    CsPanel->Left = ClientWidth - CsPanel->Width;
    Application->ProcessMessages();
}
//---------------------------------------------------------------------------
void TMainForm::DrawSpectrum(const TSpectrum &Spc, TLineSeries *LineSeries)
{
    LineSeries->Clear();
    for (size_t i = 0; i < Spc.Counts.size(); i++)
    {
        LineSeries->AddXY(Spc.Energies[i], Spc.Counts[i]);
    }
}
//---------------------------------------------------------------------------
TData TMainForm::GetData() const
{
    if (!ValidSpectra(0) && !ValidSpectra(1) && !ValidSpectra(2))
    {
        String StdSamplesSpectraError = L"Etalon namunalar spektrlarida xatolik bor.";
        if (LangID == 1)
        {
            StdSamplesSpectraError = L"There are errors in reference samples spectra.";
        }
        throw Exception(StdSamplesSpectraError);
    }
    const TData Result
    {
        {Bkgs[0], Bkgs[1], Bkgs[2]},
        {Ths[0],  Ths[1],  Ths[2]},
        {Ras[0],  Ras[1],  Ras[2]},
        {Ks[0],   Ks[1],   Ks[2]},
        {Css[0],  Css[1],  Css[2]},

        ThEn1,
        ThEn2,
        RaEn1,
        RaEn2,
        KEn1,
        KEn2,
        CsEn1,
        CsEn2,
        BeEn1,
        BeEn2,

        BePhotopeakEff1,
        BePhotopeakEff2,
        BePhotopeakEff3,

        BeSysError,

        MinPeakWidth,
        MaxEnergyError,

        {ThActivityErrors[0], ThActivityErrors[1], ThActivityErrors[2]},
        {RaActivityErrors[0], RaActivityErrors[1], RaActivityErrors[2]},
        {KActivityErrors[0],  KActivityErrors[1],  KActivityErrors[2]},
        {CsActivityErrors[0], CsActivityErrors[1], CsActivityErrors[2]}
    };
    return Result;
}
//---------------------------------------------------------------------------
void TMainForm::InitStdSamples(TSettingsForm *Form)
{
    static const double DAYS_IN_YEAR = 365.25;

    if (Form->Density_1_SamplesValid())
    {
        Bkgs[0].LoadFromFile(Form->Bkg1FileName->Text);
        Ths[0].LoadFromFile(Form->Th1FileName->Text);
        Ths[0].ExtraStringData = Form->Th1ActivityEdit->Text;
        Ths[0].ExtraFloatData =
            Dateutils::DaysBetween(Form->Th1MesDate->Date, Form->Th1Date->Date) / DAYS_IN_YEAR;
        ThActivityErrors[0] = Sysutils::StrToFloatDef(Form->Th1ErrorEdit->Text, 0) / 100.0;

        Ras[0].LoadFromFile(Form->Ra1FileName->Text);
        Ras[0].ExtraStringData = Form->Ra1ActivityEdit->Text;
        Ras[0].ExtraFloatData =
            Dateutils::DaysBetween(Form->Ra1MesDate->Date, Form->Ra1Date->Date) / DAYS_IN_YEAR;
        RaActivityErrors[0] = Sysutils::StrToFloatDef(Form->Ra1ErrorEdit->Text, 0) / 100.0;

        Ks[0].LoadFromFile(Form->K1FileName->Text);
        Ks[0].ExtraStringData = Form->K1ActivityEdit->Text;
        Ks[0].ExtraFloatData =
            Dateutils::DaysBetween(Form->K1MesDate->Date, Form->K1Date->Date) / DAYS_IN_YEAR;
        KActivityErrors[0] = Sysutils::StrToFloatDef(Form->K1ErrorEdit->Text, 0) / 100.0;

        Css[0].LoadFromFile(Form->Cs1FileName->Text);
        Css[0].ExtraStringData = Form->Cs1ActivityEdit->Text;
        Css[0].ExtraFloatData =
            Dateutils::DaysBetween(Form->Cs1MesDate->Date, Form->Cs1Date->Date) / DAYS_IN_YEAR;
        CsActivityErrors[0] = Sysutils::StrToFloatDef(Form->Cs1ErrorEdit->Text, 0) / 100.0;

        SubtractBkgFromStandardSources(0);
    }
    if (Form->Density_2_SamplesValid())
    {
        Bkgs[1].LoadFromFile(Form->Bkg2FileName->Text);
        Ths[1].LoadFromFile(Form->Th2FileName->Text);
        Ths[1].ExtraStringData = Form->Th2ActivityEdit->Text;
        Ths[1].ExtraFloatData =
            Dateutils::DaysBetween(Form->Th2MesDate->Date, Form->Th2Date->Date) / DAYS_IN_YEAR;
        ThActivityErrors[1] = Sysutils::StrToFloatDef(Form->Th2ErrorEdit->Text, 0) / 100.0;

        Ras[1].LoadFromFile(Form->Ra2FileName->Text);
        Ras[1].ExtraStringData = Form->Ra2ActivityEdit->Text;
        Ras[1].ExtraFloatData =
            Dateutils::DaysBetween(Form->Ra2MesDate->Date, Form->Ra2Date->Date) / DAYS_IN_YEAR;
        RaActivityErrors[1] = Sysutils::StrToFloatDef(Form->Ra2ErrorEdit->Text, 0) / 100.0;

        Ks[1].LoadFromFile(Form->K2FileName->Text);
        Ks[1].ExtraStringData = Form->K2ActivityEdit->Text;
        Ks[1].ExtraFloatData =
            Dateutils::DaysBetween(Form->K2MesDate->Date, Form->K2Date->Date) / DAYS_IN_YEAR;
        KActivityErrors[1] = Sysutils::StrToFloatDef(Form->K2ErrorEdit->Text, 0) / 100.0;

        Css[1].LoadFromFile(Form->Cs2FileName->Text);
        Css[1].ExtraStringData = Form->Cs2ActivityEdit->Text;
        Css[1].ExtraFloatData =
            Dateutils::DaysBetween(Form->Cs2MesDate->Date, Form->Cs2Date->Date) / DAYS_IN_YEAR;
        CsActivityErrors[1] = Sysutils::StrToFloatDef(Form->Cs2ErrorEdit->Text, 0) / 100.0;

        SubtractBkgFromStandardSources(1);
    }
    if (Form->Density_3_SamplesValid())
    {
        Bkgs[2].LoadFromFile(Form->Bkg3FileName->Text);
        Ths[2].LoadFromFile(Form->Th3FileName->Text);
        Ths[2].ExtraStringData = Form->Th3ActivityEdit->Text;
        Ths[2].ExtraFloatData =
            Dateutils::DaysBetween(Form->Th3MesDate->Date, Form->Th3Date->Date) / DAYS_IN_YEAR;
        ThActivityErrors[2] = Sysutils::StrToFloatDef(Form->Th3ErrorEdit->Text, 0) / 100.0;

        Ras[2].LoadFromFile(Form->Ra3FileName->Text);
        Ras[2].ExtraStringData = Form->Ra3ActivityEdit->Text;
        Ras[2].ExtraFloatData =
            Dateutils::DaysBetween(Form->Ra3MesDate->Date, Form->Ra3Date->Date) / DAYS_IN_YEAR;
        RaActivityErrors[2] = Sysutils::StrToFloatDef(Form->Ra3ErrorEdit->Text, 0) / 100.0;

        Ks[2].LoadFromFile(Form->K3FileName->Text);
        Ks[2].ExtraStringData = Form->K3ActivityEdit->Text;
        Ks[2].ExtraFloatData =
            Dateutils::DaysBetween(Form->K3MesDate->Date, Form->K3Date->Date) / DAYS_IN_YEAR;
        KActivityErrors[2] = Sysutils::StrToFloatDef(Form->K3ErrorEdit->Text, 0) / 100.0;

        Css[2].LoadFromFile(Form->Cs3FileName->Text);
        Css[2].ExtraStringData = Form->Cs3ActivityEdit->Text;
        Css[2].ExtraFloatData =
            Dateutils::DaysBetween(Form->Cs3MesDate->Date, Form->Cs3Date->Date) / DAYS_IN_YEAR;
        CsActivityErrors[2] = Sysutils::StrToFloatDef(Form->Cs3ErrorEdit->Text, 0) / 100.0;

        SubtractBkgFromStandardSources(2);
    }
    SetEnergyRanges(Form);
    if (ValidSpectra(0) && ValidSpectra(1) && ValidSpectra(2))
    {
        VI = 1;
        Utils::NormalizeStandardSources(Ths[1], Ths[0], ThEn1, ThEn2);
        Utils::NormalizeStandardSources(Ths[1], Ths[2], ThEn1, ThEn2);
        Utils::NormalizeStandardSources(Ras[1], Ras[0], RaEn1, RaEn2);
        Utils::NormalizeStandardSources(Ras[1], Ras[2], RaEn1, RaEn2);
        Utils::NormalizeStandardSources(Ks[1], Ks[0], KEn1, KEn2);
        Utils::NormalizeStandardSources(Ks[1], Ks[2], KEn1, KEn2);
        Utils::NormalizeStandardSources(Css[1], Css[0], CsEn1, CsEn2);
        Utils::NormalizeStandardSources(Css[1], Css[2], CsEn1, CsEn2);
    }
    else if (ValidSpectra(0) && ValidSpectra(1))
    {
        VI = 1;
        Utils::NormalizeStandardSources(Ths[1], Ths[0], ThEn1, ThEn2);
        Utils::NormalizeStandardSources(Ras[1], Ras[0], RaEn1, RaEn2);
        Utils::NormalizeStandardSources(Ks[1], Ks[0], KEn1, KEn2);
        Utils::NormalizeStandardSources(Css[1], Css[0], CsEn1, CsEn2);
    }
    else if (ValidSpectra(0) && ValidSpectra(2))
    {
        VI = 2;
        Utils::NormalizeStandardSources(Ths[2], Ths[0], ThEn1, ThEn2);
        Utils::NormalizeStandardSources(Ras[2], Ras[0], RaEn1, RaEn2);
        Utils::NormalizeStandardSources(Ks[2], Ks[0], KEn1, KEn2);
        Utils::NormalizeStandardSources(Css[2], Css[0], CsEn1, CsEn2);
    }
    else if (ValidSpectra(1) && ValidSpectra(2))
    {
        VI = 1;
        Utils::NormalizeStandardSources(Ths[1], Ths[2], ThEn1, ThEn2);
        Utils::NormalizeStandardSources(Ras[1], Ras[2], RaEn1, RaEn2);
        Utils::NormalizeStandardSources(Ks[1], Ks[2], KEn1, KEn2);
        Utils::NormalizeStandardSources(Css[1], Css[2], CsEn1, CsEn2);
    }
    else if (ValidSpectra(0))
    {
        VI = 0;
    }
    else if (ValidSpectra(1))
    {
        VI = 1;
    }
    else if (ValidSpectra(2))
    {
        VI = 2;
    }
    Energy1Edit->Text = Ths[VI].Energy1;
    Energy2Edit->Text = Ths[VI].Energy2;
    CreateVirtualSpectra();
    CalculateCountsInStdSamples();
    PopulateStandardSourcesInfo(Form);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::StandardSamplesButtonClick(TObject *Sender)
{
    std::unique_ptr<TSettingsForm> Form(new TSettingsForm(Application));
    if (Form->ShowModal() != mrOk)
    {
        return;
    }
    Bkgs[0] = Bkgs[1] = Bkgs[2] = TSpectrum();
    Ths[0] = Ths[1] = Ths[2] = TSpectrum();
    Ras[0] = Ras[1] = Ras[2] = TSpectrum();
    Ks[0] = Ks[1] = Ks[2] = TSpectrum();
    Css[0] = Css[1] = Css[2] = TSpectrum();
    InitStdSamples(Form.get());
}
//---------------------------------------------------------------------------
void TMainForm::SubtractBkgFromStandardSources(const int Idx)
{
    TSpectrum Spc;
    TSpectrum::CheckError(Ths[Idx].Subtract(Bkgs[Idx], Spc, false, true), Ths[Idx].ErrorMessage);
    Ths[Idx] = Spc;
    Spc = TSpectrum();

    TSpectrum::CheckError(Ras[Idx].Subtract(Bkgs[Idx], Spc, false, true), Ras[Idx].ErrorMessage);
    Ras[Idx] = Spc;
    Spc = TSpectrum();

    TSpectrum::CheckError(Ks[Idx].Subtract(Bkgs[Idx], Spc, false, true), Ks[Idx].ErrorMessage);
    Ks[Idx] = Spc;
    Spc = TSpectrum();

    TSpectrum::CheckError(Css[Idx].Subtract(Bkgs[Idx], Spc, false, true), Css[Idx].ErrorMessage);
    Css[Idx] = Spc;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::OnSpectraLoadTimer(TObject *Sender)
{
    SpectraLoadTimer->Enabled = false;
    std::unique_ptr<TSettingsForm> Form(new TSettingsForm(Application));
    String ErrorMessage;
    if ((!Form->Density_1_SamplesValid() && !Form->Density_2_SamplesValid() && !Form->Density_3_SamplesValid()) ||
        !Form->VolumesAreValid(ErrorMessage))
    {
        if (!ErrorMessage.IsEmpty())
        {
            Application->MessageBox(ErrorMessage.c_str(), ErrorTitle.c_str(), MB_OK | MB_ICONERROR);
        }
        if (Form->ShowModal() != mrOk)
        {
            return;
        }
    }
    ShiftingForm->ChangeUILanguage();
    if (BatchProcessingResultsForm != nullptr)
    {
        BatchProcessingResultsForm->ChangeUILanguage();
    }
    InitStdSamples(Form.get());
    ChangeUILanguage();
}
//---------------------------------------------------------------------------
void TMainForm::SetEnergyRanges(TSettingsForm *Settings)
{
    ThEn1 = Sysutils::StrToFloatDef(Settings->ThEnergy1Edit->Text, 0);
    ThEn2 = Sysutils::StrToFloatDef(Settings->ThEnergy2Edit->Text, 0);
    RaEn1 = Sysutils::StrToFloatDef(Settings->RaEnergy1Edit->Text, 0);
    RaEn2 = Sysutils::StrToFloatDef(Settings->RaEnergy2Edit->Text, 0);
    KEn1 = Sysutils::StrToFloatDef(Settings->KEnergy1Edit->Text, 0);
    KEn2 = Sysutils::StrToFloatDef(Settings->KEnergy2Edit->Text, 0);
    CsEn1 = Sysutils::StrToFloatDef(Settings->CsEnergy1Edit->Text, 0);
    CsEn2 = Sysutils::StrToFloatDef(Settings->CsEnergy2Edit->Text, 0);
    BeEn1 = Sysutils::StrToFloatDef(Settings->BeEnergy1Edit->Text, 0);
    BeEn2 = Sysutils::StrToFloatDef(Settings->BeEnergy2Edit->Text, 0);

    const auto &Strs = Utils::CreateStringVectorFromDelimitedStr(Settings->Be7PhotopeakEffEdit->Text, L';', false);
    BePhotopeakEff1 = Strs.size() > 0 ? (Sysutils::StrToFloatDef(Strs[0].Trim(), 0) / 100.0) : 0;
    BePhotopeakEff2 = Strs.size() > 1 ? (Sysutils::StrToFloatDef(Strs[1].Trim(), 0) / 100.0) : 0;
    BePhotopeakEff3 = Strs.size() > 2 ? (Sysutils::StrToFloatDef(Strs[2].Trim(), 0) / 100.0) : 0;

    BeSysError = Sysutils::StrToFloatDef(Settings->Be7SystematicErrorEdit->Text.Trim(), 0) / 100.0;

    MinPeakWidth = Sysutils::StrToFloatDef(Settings->GetSetting(L"PeakSearch", L"MinPeakWidth"), 0);
    MaxEnergyError = Sysutils::StrToFloatDef(Settings->GetSetting(L"PeakSearch", L"MaxEnergyError"), 0);
}
//---------------------------------------------------------------------------
bool TMainForm::ValidSpectra(const int Idx) const
{
    return
        Idx >= 0 && Idx <= 2 &&
        Bkgs[Idx].IsValid() &&
        Ths[Idx].IsValid() &&
        Ras[Idx].IsValid() &&
        Ks[Idx].IsValid() &&
        Css[Idx].IsValid();
}
//---------------------------------------------------------------------------
void TMainForm::CreateVirtualSpectraFrom3Set(const int __LangID, const double DensityInGramPerLitre)
{
    // Th-232
    LOG(L"Creating Th...");
    bool DensityOK =
        Ths[1].DensityInGramPerLitre > Ths[0].DensityInGramPerLitre &&
        Ths[1].DensityInGramPerLitre < Ths[2].DensityInGramPerLitre;
    if (!DensityOK)
    {
        String ErrorMsg = L"Th-232 etalon namunalari zichliklarida xatolik bor.";
        if (__LangID == 1)
        {
            ErrorMsg = L"Error in densities of Th-232 standard samples.";
        }
        throw Exception(ErrorMsg);
    }

    if (DensityInGramPerLitre <= Ths[1].DensityInGramPerLitre)
    {
        TSpectrum &Result = OrigThSpc;
        const double X = ((Ths[1].DensityInGramPerLitre - DensityInGramPerLitre) /
            (Ths[1].DensityInGramPerLitre - Ths[0].DensityInGramPerLitre));

        Result = Ths[1].Multiply(1 - X);
        TSpectrum Sum;
        TSpectrum::CheckError(Result.Add(Ths[0].Multiply(X), Sum), Result.ErrorMessage);
        Result = Sum;
    }
    else
    {
        TSpectrum &Result = OrigThSpc;
        const double X = ((Ths[2].DensityInGramPerLitre - DensityInGramPerLitre) /
                (Ths[2].DensityInGramPerLitre - Ths[1].DensityInGramPerLitre));

        Result = Ths[2].Multiply(1 - X);
        TSpectrum Sum;
        TSpectrum::CheckError(Result.Add(Ths[1].Multiply(X), Sum), Result.ErrorMessage);
        Result = Sum;
    }
    LOG(L"Shifting Th...");
    ShiftTh();

    // Ra-226
    LOG(L"Creating Ra...");
    DensityOK =
        Ras[1].DensityInGramPerLitre > Ras[0].DensityInGramPerLitre &&
        Ras[1].DensityInGramPerLitre < Ras[2].DensityInGramPerLitre;
    if (!DensityOK)
    {
        String ErrorMsg = L"Ra-226 etalon namunalari zichliklarida xatolik bor.";
        if (__LangID == 1)
        {
            ErrorMsg = L"Error in densities of Ra-226 standard samples.";
        }
        throw Exception(ErrorMsg);
    }

    if (DensityInGramPerLitre <= Ras[1].DensityInGramPerLitre)
    {
        TSpectrum &Result = OrigRaSpc;
        const double X = ((Ras[1].DensityInGramPerLitre - DensityInGramPerLitre) /
                (Ras[1].DensityInGramPerLitre - Ras[0].DensityInGramPerLitre));

        Result = Ras[1].Multiply(1 - X);
        TSpectrum Sum;
        TSpectrum::CheckError(Result.Add(Ras[0].Multiply(X), Sum), Result.ErrorMessage);
        Result = Sum;
    }
    else
    {
        TSpectrum &Result = OrigRaSpc;
        const double X = ((Ras[2].DensityInGramPerLitre - DensityInGramPerLitre) /
                (Ras[2].DensityInGramPerLitre - Ras[1].DensityInGramPerLitre));

        Result = Ras[2].Multiply(1 - X);
        TSpectrum Sum;
        TSpectrum::CheckError(Result.Add(Ras[1].Multiply(X), Sum), Result.ErrorMessage);
        Result = Sum;
    }
    LOG(L"Shifting Ra...");
    ShiftRa();

    // K-40
    LOG(L"Creating K...");
    DensityOK =
        Ks[1].DensityInGramPerLitre > Ks[0].DensityInGramPerLitre &&
        Ks[1].DensityInGramPerLitre < Ks[2].DensityInGramPerLitre;
    if (!DensityOK)
    {
        String ErrorMsg = L"K-40 etalon namunalari zichliklarida xatolik bor.";
        if (__LangID == 1)
        {
            ErrorMsg = L"Error in densities of K-40 standard samples.";
        }
        throw Exception(ErrorMsg);
    }

    if (DensityInGramPerLitre <= Ks[1].DensityInGramPerLitre)
    {
        TSpectrum &Result = OrigKSpc;
        const double X = ((Ks[1].DensityInGramPerLitre - DensityInGramPerLitre) /
                (Ks[1].DensityInGramPerLitre - Ks[0].DensityInGramPerLitre));

        Result = Ks[1].Multiply(1 - X);
        TSpectrum Sum;
        TSpectrum::CheckError(Result.Add(Ks[0].Multiply(X), Sum), Result.ErrorMessage);
        Result = Sum;
    }
    else
    {
        TSpectrum &Result = OrigKSpc;
        const double X = ((Ks[2].DensityInGramPerLitre - DensityInGramPerLitre) /
                (Ks[2].DensityInGramPerLitre - Ks[1].DensityInGramPerLitre));

        Result = Ks[2].Multiply(1 - X);
        TSpectrum Sum;
        TSpectrum::CheckError(Result.Add(Ks[1].Multiply(X), Sum), Result.ErrorMessage);
        Result = Sum;
    }
    LOG(L"Shifting K...");
    ShiftK();

    // Cs-137
    LOG(L"Creating Cs...");
    DensityOK =
        Css[1].DensityInGramPerLitre > Css[0].DensityInGramPerLitre &&
        Css[1].DensityInGramPerLitre < Css[2].DensityInGramPerLitre;
    if (!DensityOK)
    {
        String ErrorMsg = L"Cs-137 etalon namunalari zichliklarida xatolik bor.";
        if (__LangID == 1)
        {
            ErrorMsg = L"Error in densities of Cs-137 standard samples.";
        }
        throw Exception(ErrorMsg);
    }

    if (DensityInGramPerLitre <= Css[1].DensityInGramPerLitre)
    {
        TSpectrum &Result = OrigCsSpc;
        const double X = ((Css[1].DensityInGramPerLitre - DensityInGramPerLitre) /
                (Css[1].DensityInGramPerLitre - Css[0].DensityInGramPerLitre));

        Result = Css[1].Multiply(1 - X);
        TSpectrum Sum;
        TSpectrum::CheckError(Result.Add(Css[0].Multiply(X), Sum), Result.ErrorMessage);
        Result = Sum;
    }
    else
    {
        TSpectrum &Result = OrigCsSpc;
        const double X = ((Css[2].DensityInGramPerLitre - DensityInGramPerLitre) /
                (Css[2].DensityInGramPerLitre - Css[1].DensityInGramPerLitre));

        Result = Css[2].Multiply(1 - X);
        TSpectrum Sum;
        TSpectrum::CheckError(Result.Add(Css[1].Multiply(X), Sum), Result.ErrorMessage);
        Result = Sum;
    }
    LOG(L"Shifting Cs...");
    ShiftCs();

    // Fon
    LOG(L"Creating Bkg...");
    DensityOK =
        Bkgs[1].DensityInGramPerLitre > Bkgs[0].DensityInGramPerLitre &&
        Bkgs[1].DensityInGramPerLitre < Bkgs[2].DensityInGramPerLitre;
    if (!DensityOK)
    {
        String ErrorMsg = L"Tabiiy fon namunalari zichliklarida xatolik bor.";
        if (__LangID == 1)
        {
            ErrorMsg = L"Error in densities of background samples.";
        }
        throw Exception(ErrorMsg);
    }

    if (DensityInGramPerLitre <= Bkgs[1].DensityInGramPerLitre)
    {
        TSpectrum &Result = OrigBkgSpc;
        const double X = ((Bkgs[1].DensityInGramPerLitre - DensityInGramPerLitre) /
                Bkgs[1].DensityInGramPerLitre);

        Result = Bkgs[1].Multiply(1 - X);
        TSpectrum Sum;
        TSpectrum::CheckError(Result.Add(Bkgs[0].Multiply(X), Sum), Result.ErrorMessage);
        Result = Sum;
    }
    else
    {
        TSpectrum &Result = OrigBkgSpc;
        const double X = ((Bkgs[2].DensityInGramPerLitre - DensityInGramPerLitre) /
                (Bkgs[2].DensityInGramPerLitre - Bkgs[1].DensityInGramPerLitre));

        Result = Bkgs[2].Multiply(1 - X);
        TSpectrum Sum;
        TSpectrum::CheckError(Result.Add(Bkgs[1].Multiply(X), Sum), Result.ErrorMessage);
        Result = Sum;
    }
    LOG(L"Shifting Bkg...");
    ShiftBkg();
    LOG(L"Virtual spectra created from 3 set.");
}
//---------------------------------------------------------------------------
void TMainForm::CreateVirtualSpectraFrom2Set(
    const int __LangID, const double DensityInGramPerLitre, const int I1, const int I2)
{
    // Th-232
    LOG(L"Creating Th...");
    bool DensityOK = Ths[I1].DensityInGramPerLitre < Ths[I2].DensityInGramPerLitre;
    if (!DensityOK)
    {
        String ErrorMsg = L"Th-232 etalon namunalari zichliklarida xatolik bor.";
        if (__LangID == 1)
        {
            ErrorMsg = L"Error in densities of Th-232 standard samples.";
        }
        throw Exception(ErrorMsg);
    }

    TSpectrum &ResultTh = OrigThSpc;
    double X = ((Ths[I2].DensityInGramPerLitre - DensityInGramPerLitre) /
            (Ths[I2].DensityInGramPerLitre - Ths[I1].DensityInGramPerLitre));

    ResultTh = Ths[I2].Multiply(1 - X);
    TSpectrum Sum;
    TSpectrum::CheckError(ResultTh.Add(Ths[I1].Multiply(X), Sum), ResultTh.ErrorMessage);
    ResultTh = Sum;
    LOG(L"Shifting Th...");
    ShiftTh();

    // Ra-226
    LOG(L"Creating Ra...");
    DensityOK = Ras[I1].DensityInGramPerLitre < Ras[I2].DensityInGramPerLitre;
    if (!DensityOK)
    {
        String ErrorMsg = L"Ra-226 etalon namunalari zichliklarida xatolik bor.";
        if (__LangID == 1)
        {
            ErrorMsg = L"Error in densities of Ra-226 standard samples.";
        }
        throw Exception(ErrorMsg);
    }

    TSpectrum &ResultRa = OrigRaSpc;
    X = ((Ras[I2].DensityInGramPerLitre - DensityInGramPerLitre) /
            (Ras[I2].DensityInGramPerLitre - Ras[I1].DensityInGramPerLitre));

    ResultRa = Ras[I2].Multiply(1 - X);
    Sum = TSpectrum();
    TSpectrum::CheckError(ResultRa.Add(Ras[I1].Multiply(X), Sum), ResultRa.ErrorMessage);
    ResultRa = Sum;
    LOG(L"Shifting Ra...");
    ShiftRa();

    // K-40
    LOG(L"Creating K...");
    DensityOK = Ks[I1].DensityInGramPerLitre < Ks[I2].DensityInGramPerLitre;
    if (!DensityOK)
    {
        String ErrorMsg = L"K-40 etalon namunalari zichliklarida xatolik bor.";
        if (__LangID == 1)
        {
            ErrorMsg = L"Error in densities of K-40 standard samples.";
        }
        throw Exception(ErrorMsg);
    }

    TSpectrum &ResultK = OrigKSpc;
    X = ((Ks[I2].DensityInGramPerLitre - DensityInGramPerLitre) /
            (Ks[I2].DensityInGramPerLitre - Ks[I1].DensityInGramPerLitre));

    ResultK = Ks[I2].Multiply(1 - X);
    Sum = TSpectrum();
    TSpectrum::CheckError(ResultK.Add(Ks[I1].Multiply(X), Sum), ResultK.ErrorMessage);
    ResultK = Sum;
    LOG(L"Shifting K...");
    ShiftK();

    // Cs-137
    LOG(L"Creating Cs...");
    DensityOK = Css[I1].DensityInGramPerLitre < Css[I2].DensityInGramPerLitre;
    if (!DensityOK)
    {
        String ErrorMsg = L"Cs-137 etalon namunalari zichliklarida xatolik bor.";
        if (__LangID == 1)
        {
            ErrorMsg = L"Error in densities of Cs-137 standard samples.";
        }
        throw Exception(ErrorMsg);
    }

    TSpectrum &ResultCs = OrigCsSpc;
    X = ((Css[I2].DensityInGramPerLitre - DensityInGramPerLitre) /
            (Css[I2].DensityInGramPerLitre - Css[I1].DensityInGramPerLitre));

    ResultCs = Css[I2].Multiply(1 - X);
    Sum = TSpectrum();
    TSpectrum::CheckError(ResultCs.Add(Css[I1].Multiply(X), Sum), ResultCs.ErrorMessage);
    ResultCs = Sum;
    LOG(L"Shifting Cs...");
    ShiftCs();

    // Fon
    LOG(L"Creating Bkg...");
    DensityOK = Bkgs[I1].DensityInGramPerLitre < Bkgs[I2].DensityInGramPerLitre;
    if (!DensityOK)
    {
        String ErrorMsg = L"Tabiiy fon namunalari zichliklarida xatolik bor.";
        if (__LangID == 1)
        {
            ErrorMsg = L"Error in densities of background samples.";
        }
        throw Exception(ErrorMsg);
    }

    TSpectrum &ResultBkg = OrigBkgSpc;
    X = ((Bkgs[I2].DensityInGramPerLitre - DensityInGramPerLitre) /
            (Bkgs[I2].DensityInGramPerLitre - Bkgs[I1].DensityInGramPerLitre));

    ResultBkg = Bkgs[I2].Multiply(1 - X);
    Sum = TSpectrum();
    TSpectrum::CheckError(ResultBkg.Add(Bkgs[I1].Multiply(X), Sum), ResultBkg.ErrorMessage);
    ResultBkg = Sum;
    LOG(L"Shifting Bkg...");
    ShiftBkg();
    LOG(L"Virtual spectra created from 2 set.");
}
//---------------------------------------------------------------------------
void TMainForm::CreateVirtualSpectra()
{
    const int __LangID = LangID;
    const double DensityInGramPerLitre = Sysutils::StrToFloatDef(SampleDensity->Text, 0);
    LOG("DensityInGramPerLitre = " + Sysutils::FloatToStrF(DensityInGramPerLitre, ffFixed, 15, 2));

    if (ValidSpectra(0) && ValidSpectra(1) && ValidSpectra(2))
    {
        CreateVirtualSpectraFrom3Set(__LangID, DensityInGramPerLitre);
    }
    else if (ValidSpectra(0) && ValidSpectra(1))
    {
        CreateVirtualSpectraFrom2Set(__LangID, DensityInGramPerLitre, 0, 1);
    }
    else if (ValidSpectra(0) && ValidSpectra(2))
    {
        CreateVirtualSpectraFrom2Set(__LangID, DensityInGramPerLitre, 0, 2);
    }
    else if (ValidSpectra(1) && ValidSpectra(2))
    {
        CreateVirtualSpectraFrom2Set(__LangID, DensityInGramPerLitre, 1, 2);
    }
    else if (ValidSpectra(0) || ValidSpectra(1) || ValidSpectra(2))
    {
        OrigThSpc = Ths[VI];
        ShiftTh();
        OrigRaSpc = Ras[VI];
        ShiftRa();
        OrigKSpc = Ks[VI];
        ShiftK();
        OrigCsSpc = Css[VI];
        ShiftCs();
        OrigBkgSpc = Bkgs[VI];
        ShiftBkg();
    }
    else
    {
        String ErrorMsg = L"Bir yoki undan ortiq etalon va/yoki fon namunalari spektrlari topilmadi.";
        if (__LangID == 1)
        {
            ErrorMsg = L"One or more reference and/or background samples spectra not found.";
        }
        Application->MessageBox(ErrorMsg.c_str(), ErrorTitle.c_str(), MB_OK | MB_ICONERROR);
    }
}
//---------------------------------------------------------------------------
void TMainForm::CalculateCountsInStdSamples()
{
    ThCount = ThSpc.CalculateCountByEnergyRange(ThEn1, ThEn2);
    ThSum->Text = Utils::RoundFloatValue(ThCount);

    RaCount = RaSpc.CalculateCountByEnergyRange(RaEn1, RaEn2);
    RaSum->Text = Utils::RoundFloatValue(RaCount);

    KCount = KSpc.CalculateCountByEnergyRange(KEn1, KEn2);
    KSum->Text = Utils::RoundFloatValue(KCount);

    CsCount = CsSpc.CalculateCountByEnergyRange(CsEn1, CsEn2);
    CsSum->Text = Utils::RoundFloatValue(CsCount);
}
//---------------------------------------------------------------------------
void TMainForm::CalculateMDAs(
    const TSpectrum &Bkg, double &MDATh, double &MDARa, double &MDAK, double &MDACs, double &MDABe) const
{
    const double CountThBkg = Bkg.CalculateCountByEnergyRange(ThEn1, ThEn2);
    const double CountRaBkg = Bkg.CalculateCountByEnergyRange(RaEn1, RaEn2);
    const double CountKBkg = Bkg.CalculateCountByEnergyRange(KEn1, KEn2);
    const double CountCsBkg = Bkg.CalculateCountByEnergyRange(CsEn1, CsEn2);
    const double CountBeBkg =
        (BeEn1 > 0 && BeEn2 > 0 && BeEn2 > BeEn1) ? Bkg.CalculateCountByEnergyRange(BeEn1, BeEn2) : 0;
    const double MassCoeff = StrToFloat(SampleMass->Text) / 1000;

    MDATh =
        3 * System::Sqrt(CountThBkg) * (StrToFloat(ThActivity->Text) / (ThCount * (SampleSpc.Duration / ThSpc.Duration) * MassCoeff));
    MDARa =
        3 * System::Sqrt(CountRaBkg) * (StrToFloat(RaActivity->Text) / (RaCount * (SampleSpc.Duration / RaSpc.Duration) * MassCoeff));
    MDAK =
        3 * System::Sqrt(CountKBkg) * (StrToFloat(KActivity->Text) / (KCount * (SampleSpc.Duration / KSpc.Duration) * MassCoeff));
    MDACs =
        3 * System::Sqrt(CountCsBkg) * (StrToFloat(CsActivity->Text) / (CsCount * (SampleSpc.Duration / CsSpc.Duration) * MassCoeff));

    const double DensityInGramPerLitre = Sysutils::StrToFloatDef(SampleDensity->Text, 0);
    const double BePhotopeakEff =
        Utils::CalcBe7Effectivity(BePhotopeakEff1, BePhotopeakEff2, BePhotopeakEff3, DensityInGramPerLitre);
    LOG(L"BePhotopeakEff = " + String(BePhotopeakEff) + L" for density " + SampleDensity->Text);
    MDABe =
        (CountBeBkg > 0 && BePhotopeakEff > 0) ?
        ((3 * System::Sqrt(CountBeBkg)) / (0.104 * SampleSpc.Duration * BePhotopeakEff * MassCoeff)) : 0;
}
//---------------------------------------------------------------------------
void TMainForm::DecomposeSampleSpectrum()
{
    try
    {
        String Msg = L"Spektrlarni ayirishda xatolik yuz berdi.";
        String BelowMDA = L"<AMA";
        if (LangID == 1)
        {
            Msg = L"There is an error on subtracting the spectra.";
            BelowMDA = L"<MDA";
        }

        const auto OrigCount = OrigSampleSpc.CalculateTotalCount();
        const auto LastCount = SampleSpc.CalculateTotalCount();
        const auto CountError = std::abs(LastCount - OrigCount) / OrigCount;
        const double ThActivityError =
            System::Sqrt(Utils::Sqr(ThActivityErrors[0]) + Utils::Sqr(ThActivityErrors[1]) + Utils::Sqr(ThActivityErrors[2]));
        const double RaActivityError =
            System::Sqrt(Utils::Sqr(RaActivityErrors[0]) + Utils::Sqr(RaActivityErrors[1]) + Utils::Sqr(RaActivityErrors[2]));
        const double KActivityError =
            System::Sqrt(Utils::Sqr(KActivityErrors[0]) + Utils::Sqr(KActivityErrors[1]) + Utils::Sqr(KActivityErrors[2]));
        const double CsActivityError =
            System::Sqrt(Utils::Sqr(CsActivityErrors[0]) + Utils::Sqr(CsActivityErrors[1]) + Utils::Sqr(CsActivityErrors[2]));

        DrawSpectrum(SampleSpc, SampleSpectrum);
        CalculateCountsInStdSamples();
        TSpectrum TMPSpc = BkgSpc.Multiply(int(SubtractBkgAction->Checked) * SampleSpc.Duration / BkgSpc.Duration);
        BkgSpcWithCoeff = TMPSpc;
        DrawSpectrum(TMPSpc, BkgSpectrum);
        bool OK = SampleSpc.Subtract(TMPSpc, Sample_M_Bkg);
        TSpectrum::CheckError(OK, Msg + L"\r\n\r\n" + SampleSpc.ErrorMessage);

        double MDATh;
        double MDARa;
        double MDAK;
        double MDACs;
        double MDABe;
        CalculateMDAs(TMPSpc, MDATh, MDARa, MDAK, MDACs, MDABe);
        ThMDA->Text = Utils::RoundFloatValue(MDATh, 2, false);
        RaMDA->Text = Utils::RoundFloatValue(MDARa, 2, false);
        KMDA->Text = Utils::RoundFloatValue(MDAK, 2, false);
        CsMDA->Text = Utils::RoundFloatValue(MDACs, 2, false);
        BeMDA->Text = MDABe > 0 ? Utils::RoundFloatValue(MDABe, 2, false) : String();

        const double BkgTh = TMPSpc.CalculateCountByEnergyRange(ThEn1, ThEn2);
        const double BkgRa = TMPSpc.CalculateCountByEnergyRange(RaEn1, RaEn2);
        const double BkgK = TMPSpc.CalculateCountByEnergyRange(KEn1, KEn2);
        const double BkgCs = TMPSpc.CalculateCountByEnergyRange(CsEn1, CsEn2);
        const double BkgBe = MDABe > 0 ? TMPSpc.CalculateCountByEnergyRange(BeEn1, BeEn2) : 0;

        double Count = Sample_M_Bkg.CalculateCountByEnergyRange(ThEn1, ThEn2);
        double Coeff = Count / ThCount;
        Coeff = Coeff < 0 ? 0 : Coeff;
        SampleThSum->Text = Utils::RoundFloatValue(Count);
        ThSnSe1->Text = Utils::RoundFloatValue(Coeff, 5);
        ThC = Sysutils::StrToFloatDef(ThSnSe2->Text, 0);
        double Activity =
            ((ThSpc.Duration * Sysutils::StrToFloatDef(ThActivity->Text, 0) * ThC) /
            (SampleSpc.Duration * Sysutils::StrToFloatDef(SampleMass->Text, 0))) * 1000;
        SampleThActivity->Text = Activity >= MDATh ? Utils::RoundFloatValue(Activity, 2, false) : BelowMDA;
        TMPSpc = ThSpc.Multiply(ThC);
        ThSpcWithCoeff = TMPSpc;
        DrawSpectrum(TMPSpc, ThSpectrum);
        OK = Sample_M_Bkg.Subtract(TMPSpc, Sample_M_Th);
        TSpectrum::CheckError(OK, Msg + L"\r\n\r\n" + Sample_M_Bkg.ErrorMessage);

        const double ThError1 = Count > 0 ? (System::Sqrt(Count + BkgTh) / Count) : 0;
        const double ThTh = TMPSpc.CalculateCountByEnergyRange(ThEn1, ThEn2);
        const double ThRa = TMPSpc.CalculateCountByEnergyRange(RaEn1, RaEn2);
        const double ThK = TMPSpc.CalculateCountByEnergyRange(KEn1, KEn2);
        const double ThCs = TMPSpc.CalculateCountByEnergyRange(CsEn1, CsEn2);
        const double ThBe = MDABe > 0 ? TMPSpc.CalculateCountByEnergyRange(BeEn1, BeEn2) : 0;
        const double ThError =
            System::Sqrt(Utils::Sqr(ThError1) + Utils::Sqr(CountError) + Utils::Sqr(ThActivityError));
        SampleThError->Text = Activity >= MDATh ? Utils::RoundFloatValue(Activity * ThError, 2, false) : String();

        Count = Sample_M_Th.CalculateCountByEnergyRange(RaEn1, RaEn2);
        Coeff = Count / RaCount;
        Coeff = Coeff < 0 ? 0 : Coeff;
        SampleRaSum->Text = Utils::RoundFloatValue(Count);
        RaSnSe1->Text = Utils::RoundFloatValue(Coeff, 5);
        RaC = Sysutils::StrToFloatDef(RaSnSe2->Text, 0);
        Activity =
            ((RaSpc.Duration * Sysutils::StrToFloatDef(RaActivity->Text, 0) * RaC) /
            (SampleSpc.Duration * Sysutils::StrToFloatDef(SampleMass->Text, 0))) * 1000;
        SampleRaActivity->Text = Activity >= MDARa ? Utils::RoundFloatValue(Activity, 2, false) : BelowMDA;
        TMPSpc = RaSpc.Multiply(RaC);
        RaSpcWithCoeff = TMPSpc;
        DrawSpectrum(TMPSpc, RaSpectrum);
        OK = Sample_M_Th.Subtract(TMPSpc, Sample_M_Ra);
        TSpectrum::CheckError(OK, Msg + L"\r\n\r\n" + Sample_M_Th.ErrorMessage);

        const double RaError1 = Count > 0 ? (System::Sqrt(Count + (BkgRa + ThRa)) / Count) : 0;
        const double RaRa = TMPSpc.CalculateCountByEnergyRange(RaEn1, RaEn2);
        const double RaK = TMPSpc.CalculateCountByEnergyRange(KEn1, KEn2);
        const double RaCs = TMPSpc.CalculateCountByEnergyRange(CsEn1, CsEn2);
        const double RaBe = MDABe > 0 ? TMPSpc.CalculateCountByEnergyRange(BeEn1, BeEn2) : 0;
        const double RaError =
            System::Sqrt(Utils::Sqr(RaError1) + Utils::Sqr(CountError) + Utils::Sqr(RaActivityError));
        SampleRaError->Text = Activity >= MDARa ? Utils::RoundFloatValue(Activity * RaError, 2, false) : String();

        Count = Sample_M_Ra.CalculateCountByEnergyRange(KEn1, KEn2);
        Coeff = Count / KCount;
        Coeff = Coeff < 0 ? 0 : Coeff;
        SampleKSum->Text = Utils::RoundFloatValue(Count);
        KSnSe1->Text = Utils::RoundFloatValue(Coeff, 5);
        KC = Sysutils::StrToFloatDef(KSnSe2->Text, 0);
        Activity =
            ((KSpc.Duration * Sysutils::StrToFloatDef(KActivity->Text, 0) * KC) /
            (SampleSpc.Duration * Sysutils::StrToFloatDef(SampleMass->Text, 0))) * 1000;
        SampleKActivity->Text = Activity >= MDAK ? Utils::RoundFloatValue(Activity, 2, false) : BelowMDA;
        TMPSpc = KSpc.Multiply(KC);
        KSpcWithCoeff = TMPSpc;
        DrawSpectrum(TMPSpc, KSpectrum);
        OK = Sample_M_Ra.Subtract(TMPSpc, Sample_M_K);
        TSpectrum::CheckError(OK, Msg + L"\r\n\r\n" + Sample_M_Ra.ErrorMessage);

        const double KError1 = Count > 0 ? (System::Sqrt(Count + (BkgK + ThK + RaK)) / Count) : 0;
        const double KK = TMPSpc.CalculateCountByEnergyRange(KEn1, KEn2);
        const double KCs = TMPSpc.CalculateCountByEnergyRange(CsEn1, CsEn2);
        const double KBe = MDABe > 0 ? TMPSpc.CalculateCountByEnergyRange(BeEn1, BeEn2) : 0;
        const double KError  =
            System::Sqrt(Utils::Sqr(KError1) + Utils::Sqr(CountError) + Utils::Sqr(KActivityError));
        SampleKError->Text = Activity >= MDAK ? Utils::RoundFloatValue(Activity * KError, 2, false) : String();

        Count = Sample_M_K.CalculateCountByEnergyRange(CsEn1, CsEn2);
        Coeff = Count / CsCount;
        Coeff = Coeff < 0 ? 0 : Coeff;
        SampleCsSum->Text = Utils::RoundFloatValue(Count);
        CsSnSe1->Text = Utils::RoundFloatValue(Coeff, 5);
        CsC = Sysutils::StrToFloatDef(CsSnSe2->Text, 0);
        Activity =
            ((CsSpc.Duration * Sysutils::StrToFloatDef(CsActivity->Text, 0) * CsC) /
            (SampleSpc.Duration * Sysutils::StrToFloatDef(SampleMass->Text, 0))) * 1000;
        SampleCsActivity->Text = Activity >= MDACs ? Utils::RoundFloatValue(Activity, 2, false) : BelowMDA;
        TMPSpc = CsSpc.Multiply(CsC);
        CsSpcWithCoeff = TMPSpc;
        DrawSpectrum(TMPSpc, CsSpectrum);
        OK = Sample_M_K.Subtract(TMPSpc, Sample_M_Cs);
        TSpectrum::CheckError(OK, Msg + L"\r\n\r\n" + Sample_M_K.ErrorMessage);

        const double CsError1 = Count > 0 ? (System::Sqrt(Count + (BkgCs + ThCs + RaCs + KCs)) / Count) : 0;
        const double CsCs = TMPSpc.CalculateCountByEnergyRange(CsEn1, CsEn2);
        const double CsBe = MDABe > 0 ? TMPSpc.CalculateCountByEnergyRange(BeEn1, BeEn2) : 0;
        const double CsError =
            System::Sqrt(Utils::Sqr(CsError1) + Utils::Sqr(CountError) + Utils::Sqr(CsActivityError));
        SampleCsError->Text = Activity >= MDACs ? Utils::RoundFloatValue(Activity * CsError, 2, false) : String();

        Count = Sample_M_Cs.CalculateCountByEnergyRange(BeEn1, BeEn2);
        if (SmoothFInalSpectrumAction->Checked)
        {
            Sample_M_Cs = Sample_M_Cs.SavitzkyGolaySmooth();
        }
        DrawSpectrum(Sample_M_Cs, FinalSpectrum);
        BeSum->Text = Utils::RoundFloatValue(Count);
        if (MDABe > 0)
        {
            const double DensityInGramPerLitre = Sysutils::StrToFloatDef(SampleDensity->Text, 0);
            const double BePhotopeakEff =
                Utils::CalcBe7Effectivity(BePhotopeakEff1, BePhotopeakEff2, BePhotopeakEff3, DensityInGramPerLitre);
            LOG(L"BePhotopeakEff = " + String(BePhotopeakEff) + L" for density " + SampleDensity->Text);
            const double Weight = SameText(SampleSpc.WeightUnit, L"kg") ? (SampleSpc.Weight * 1000) : SampleSpc.Weight;
            Activity = Count / (0.104 * SampleSpc.Duration * BePhotopeakEff * (Weight / 1000));
            BeActivityPerKilogram = Activity >= MDABe ? Utils::RoundFloatValue(Activity, 2, false) : BelowMDA;
            const double TotalMass = Sysutils::StrToFloatDef(SampleOrigMass->Text, 0) * 0.001;
            const double Square = Sysutils::StrToFloatDef(SampleSquare->Text, 0) * 0.0001;
            const double BeError1 =
                Count > 0 ? (System::Sqrt(Count + (BkgBe + ThBe + RaBe + KBe + CsBe)) / Count) : 0;
            const double BeError = System::Sqrt(Utils::Sqr(BeError1) + Utils::Sqr(CountError) + Utils::Sqr(BeSysError));
            BeErrorPerKilogram = Activity >= MDABe ? Utils::RoundFloatValue(Activity * BeError, 2, false) : String();

            if (TotalMass > 0 && Square > 0 && Activity >= MDABe)
            {
                Activity *= (TotalMass / Square);
                BeActivityPerSquare = Utils::RoundFloatValue(Activity, 2, false);
                BeErrorPerSquare = Utils::RoundFloatValue(Activity * BeError, 2, false);
            }
            else
            {
                BeActivityPerSquare = L"";
                BeErrorPerSquare = L"";
            }

            BeActivityPerKgOrSq->Text = BeActivityPerKgOrSq->Tag ? BeActivityPerKilogram : BeActivityPerSquare;
            SampleBeError->Text = BeActivityPerKgOrSq->Tag ? BeErrorPerKilogram : BeErrorPerSquare;
        }
        else
        {
            BeActivityPerKgOrSq->Text = L"";
            SampleBeError->Text = L"";
            BeActivityPerKilogram = L"";
            BeErrorPerKilogram = L"";
            BeActivityPerSquare = L"";
            BeErrorPerSquare = L"";
        }
    }
    catch (const Exception &E)
    {
        Application->MessageBox(E.Message.c_str(), ErrorTitle.c_str(), MB_OK | MB_ICONERROR);
    }
}
//---------------------------------------------------------------------------
void TMainForm::PopulateStandardSourcesInfo(TSettingsForm *Settings)
{
    ThTime->Text = Utils::RoundFloatValue(ThSpc.Duration);
    ThSum->Text = Utils::RoundFloatValue(ThCount);
    double Act =
        StrToFloatDef(ThSpc.ExtraStringData, 0) *
        System::Exp(-(System::Ln(2) / 1.405E10) * ThSpc.ExtraFloatData);
    ThActivity->Text = Utils::RoundFloatValue(Act, 2, false);

    RaTime->Text = Utils::RoundFloatValue(RaSpc.Duration);
    RaSum->Text = Utils::RoundFloatValue(RaCount);
    Act =
        StrToFloatDef(RaSpc.ExtraStringData, 0) *
        System::Exp(-(System::Ln(2) / 1602) * RaSpc.ExtraFloatData);
    RaActivity->Text = Utils::RoundFloatValue(Act, 2, false);

    KTime->Text = Utils::RoundFloatValue(KSpc.Duration);
    KSum->Text = Utils::RoundFloatValue(KCount);
    Act =
        StrToFloatDef(KSpc.ExtraStringData, 0) *
        System::Exp(-(System::Ln(2) / 1.251E9) * KSpc.ExtraFloatData);
    KActivity->Text = Utils::RoundFloatValue(Act, 2, false);

    CsTime->Text = Utils::RoundFloatValue(CsSpc.Duration);
    CsSum->Text = Utils::RoundFloatValue(CsCount);
    Act =
        StrToFloatDef(CsSpc.ExtraStringData, 0) *
        System::Exp(-(System::Ln(2) / 30) * CsSpc.ExtraFloatData);
    CsActivity->Text = Utils::RoundFloatValue(Act, 2, false);

    const double Energy1 = Ths[VI].Energy1;
    const double Energy2 = Ths[VI].Energy2;
    BkgChan1Edit->Text = CalcCenterOfPeak(BkgSpc, Energy1);
    BkgChan2Edit->Text = CalcCenterOfPeak(BkgSpc, Energy2);

    ThChan1Edit->Text = CalcCenterOfPeak(ThSpc, Energy1);
    ThChan2Edit->Text = CalcCenterOfPeak(ThSpc, Energy2);

    RaChan1Edit->Text = CalcCenterOfPeak(RaSpc, Energy1);
    RaChan2Edit->Text = CalcCenterOfPeak(RaSpc, Energy2);

    KChan1Edit->Text = CalcCenterOfPeak(KSpc, Energy1);
    KChan2Edit->Text = CalcCenterOfPeak(KSpc, Energy2);

    CsChan1Edit->Text = CalcCenterOfPeak(CsSpc, Energy1);
    CsChan2Edit->Text = CalcCenterOfPeak(CsSpc, Energy2);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::OnParamChange(TObject *Sender)
{
    TEdit *Edit = dynamic_cast<TEdit *>(Sender);
    if (!Edit->Focused() ||
        (!Edit->Text.IsEmpty() && Sysutils::StrToFloatDef(Edit->Text, -1) < 0))
    {
        return;
    }
    if (Sender == SampleDensity)
    {
        CreateVirtualSpectra();
    }
    if (SampleSpc.IsValid() && BkgSpc.IsValid() && ThSpc.IsValid() &&
        RaSpc.IsValid() && KSpc.IsValid() && CsSpc.IsValid())
    {
        DecomposeSampleSpectrum();
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FinalSpcChartMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
    if (Button == mbLeft)
    {
        Selecting = true;
        SelectStartX = X;
        SelectEndX = X;
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FinalSpcChartMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
    if (Selecting && Button == mbLeft)
    {
        Selecting = false;
        SelectEndX = X;
        if (SelectStartX == SelectEndX)
        {
            return;
        }
        FinalSpcChart->Repaint();

        double StartVal = FinalSpectrum->XScreenToValue(SelectStartX);
        double EndVal   = FinalSpectrum->XScreenToValue(SelectEndX);
        if (StartVal > EndVal)
        {
            std::swap(StartVal, EndVal);
        }

        const int StartCh = FindChannelByEnergy(StartVal, FinalSpectrum);
        const int EndCh = FindChannelByEnergy(EndVal, FinalSpectrum);

        if (StartCh >= 0 && EndCh > StartCh)
        {
            const int ChannelCount = EndCh - StartCh;
            const double TotalCounts = Sample_M_Cs.CalculateCountByChannelRange(StartCh, EndCh);
            const double NetCounts = Sample_M_Cs.CalculateNetCountByChannelRange(StartCh, EndCh);
            const auto Centroid = Sample_M_Cs.CalculateCentroidByChannelRange(StartCh, EndCh);;

            String StatInfo;
            if (LangID == 0)
            {
                StatInfo.sprintf(L"Tanlangan soha: %d - %d / %.2f keV - %.2f keV (%d kanallar / %.2f keV)\n"
                                 L"Markaz: %.2f / %.2f keV\n"
                                 L"Jami hisob: %.0f\n"
                                 L"Fotocho'qqi yuzasi: %.0f",
                                 StartCh, EndCh, StartVal, EndVal, ChannelCount,
                                 EndVal - StartVal, Centroid.first, Centroid.second, TotalCounts, NetCounts);
            }
            else
            {
                StatInfo.sprintf(L"Selected area: %d - %d / %.2f keV - %.2f keV (%d channels / %.2f keV)\n"
                                 L"Center: %.2f / %.2f keV\n"
                                 L"Total counts: %.0f\n"
                                 L"Photopeak area: %.0f",
                                 StartCh, EndCh, StartVal, EndVal, ChannelCount,
                                 EndVal - StartVal, Centroid.first, Centroid.second, TotalCounts, NetCounts);
            }
            Application->MessageBox(StatInfo.c_str(), L"Information", MB_OK | MB_ICONINFORMATION);
        }

        SelectStartX = 0;
        SelectEndX = 0;
        FinalSpcChart->Repaint();
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::OnChartMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y)
{
    TChart *Chart = dynamic_cast<TChart *>(Sender);
    TLineSeries *Series = dynamic_cast<TLineSeries *>(Chart->SeriesList->Items[0]);
    if (Series->Count() <= 0 || X < Chart->ChartRect.Left || X > Chart->ChartRect.Right ||
        Y < Chart->ChartRect.Top  || Y > Chart->ChartRect.Bottom)
    {
        return;
    }

    StatusBar->Panels->Items[0]->Text = Chart->Title->Text->Strings[0];

    String EnergyStr = L"Energiya: ";
    String ChannelStr = L"Kanal: ";
    String CountStr = L"Impuls: ";
    if (LangID == 1)
    {
        EnergyStr = L"Energy: ";
        ChannelStr = L"Channel: ";
        CountStr = L"Count: ";
    }

    const double En = Series->XScreenToValue(X);
    const int Ch = FindChannelByEnergy(En, Series);
    StatusBar->Panels->Items[2]->Text = EnergyStr + Utils::RoundFloatValue(En);
    if (Ch >= 0 && Ch < Series->Count())
    {
        const double N = Series->YValues->Value[Ch];
        StatusBar->Panels->Items[1]->Text = ChannelStr + IntToStr(Ch);
        StatusBar->Panels->Items[3]->Text = CountStr + Utils::RoundFloatValue(N);
    }

    Chart->Tag = X;

    if (Chart == FinalSpcChart && Selecting)
    {
        SelectEndX = X;
        Chart->Repaint();
    }
    else
    {
        Chart->Repaint();
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::OnChartAfterDraw(TObject *Sender)
{
    TChart *Chart = dynamic_cast<TChart *>(Sender);
    TLineSeries *Series = dynamic_cast<TLineSeries *>(Chart->SeriesList->Items[0]);
    if (Series->Count() <= 0)
    {
        return;
    }
    if (Chart->Tag >= Chart->ChartRect.Left && Chart->Tag <= Chart->ChartRect.Right)
    {
        auto Canvas = Chart->Canvas;
        Canvas->Pen->Color = clBlack;
        Canvas->Pen->Width = 1;

        Canvas->MoveTo(Chart->Tag, Chart->ChartRect.Top);
        Canvas->LineTo(Chart->Tag, Chart->ChartRect.Bottom);
    }

    if (Chart != FinalSpcChart || SelectStartX == SelectEndX)
    {
        return;
    }

    int X1 = SelectStartX;
    int X2 = SelectEndX;
    if (X1 > X2)
    {
        std::swap(X1, X2);
    }

    auto C = FinalSpcChart->Canvas;
    C->Brush->Style = bsSolid;
    C->Brush->Color = clDkGray;
    C->Pen->Style = psClear;

    const TRect &PlotRect = FinalSpcChart->ChartRect;
    C->FillRect(Rect(X1, PlotRect.Top, X2, PlotRect.Bottom));

    const double StartVal = FinalSpectrum->XScreenToValue(X1);
    const double EndVal   = FinalSpectrum->XScreenToValue(X2);

    C->Pen->Color = clRed;
    C->Pen->Style = psSolid;

    bool FirstPoint = true;
    for (int i = 0; i < FinalSpectrum->Count(); i++)
    {
        const double xv = FinalSpectrum->XValue[i];
        if (xv >= StartVal && xv <= EndVal)
        {
            const int px = FinalSpectrum->CalcXPos(i);
            const int py = FinalSpectrum->CalcYPos(i);
            if (FirstPoint)
            {
                C->MoveTo(px, py);
                FirstPoint = false;
            }
            else
            {
                C->LineTo(px, py);
            }
        }
    }
}
//---------------------------------------------------------------------------
int TMainForm::FindChannelByEnergy(const double En, TLineSeries *Spc) const
{
    int Nearest = -1;
    double MinDiff = 1e99;

    for (int i = 0; i < Spc->Count(); i++)
    {
        const double Diff = fabs(Spc->XValue[i] - En);
        if (Diff < MinDiff)
        {
            MinDiff = Diff;
            Nearest = i;
        }
    }
    return Nearest;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ParamEditClick(TObject *Sender)
{
    TEdit *ParamEdit = dynamic_cast<TEdit *>(Sender);
    ParamEdit->SelectAll();
}
//---------------------------------------------------------------------------
String TMainForm::GetVersionString(const String &DefaultVal) const
{
    try
    {
        const String &FileName = Sysutils::GetModuleName(unsigned(HInstance));
        DWORD Hnd, Size = GetFileVersionInfoSizeW(FileName.c_str(), &Hnd);
        if (Size > 0)
        {
            unsigned char *Buffer = new unsigned char[Size];
            try
            {
                void *Data = nullptr;
                UINT Len = 0;
                if (GetFileVersionInfoW(FileName.c_str(), Hnd, Size, Buffer) != 0 &&
                    VerQueryValueW(Buffer, L"\\", &Data, &Len) != 0)
                {
                    VS_FIXEDFILEINFO FI;
                    CopyMemory(&FI, Data, sizeof(VS_FIXEDFILEINFO));
                    const String s1((int)HIWORD(FI.dwProductVersionMS));
                    const String s2((int)LOWORD(FI.dwProductVersionMS));
                    const String s3((int)HIWORD(FI.dwProductVersionLS));
                    return s1 + "." + s2 + "." + s3;
                }
            }
            __finally
            {
                delete [] Buffer;
            }
        }
    }
    catch (Exception &)
    {
    }
    return DefaultVal;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::HelpButtonClick(TObject *Sender)
{
    String Icons = L"Piktogrammalar: https://icons8.com";
    String AboutStr = L"Dastur haqida";
    String Copyright = L"Samarqand Davlat Universiteti";
    String Developer = L"Dasturchi: Asqarali Azimov";
    if (LangID == 1)
    {
        Icons = L"Icons: https://icons8.com";
        AboutStr = L"About";
        Copyright = L"Samarkand State University";
        Developer = L"Developer: Askarali Azimov";
    }

    String Version = GetVersionString();
    if (!Version.IsEmpty())
    {
        Version = L" v" + Version + L".";
    }
    const String &Message =
        String(AppName + Version + L"\r\n") +
        Char(169) + L" " + Copyright + L", 2021 - 2025.\r\n\r\n" +
        Developer + L"\r\n" +
        Icons;
    Application->MessageBox(Message.c_str(), AboutStr.c_str(), MB_OK | MB_ICONINFORMATION);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ShiftingButtonClick(TObject *Sender)
{
    if (ShiftingForm->SaveSpectrum2->OnClick != 0)
    {
        ShiftingForm->Reset();
    }
    ShiftingForm->SaveSpectrum2->OnClick = 0;
    ShiftingForm->SaveSpectrum2->DropdownMenu = ShiftingForm->SaveButtonPopupMenu;
    ShiftingForm->Show();
}
//---------------------------------------------------------------------------
bool TMainForm::ShiftSrc()
{
    bool Result = false;
    const double En1 = Sysutils::StrToFloatDef(Energy1Edit->Text, 0);
    const double En2 = Sysutils::StrToFloatDef(Energy2Edit->Text, 0);
    const double SrcCh1 = Ths[VI].Channel1;
    const double SrcCh2 = Ths[VI].Channel2;
    const double SmpCh1 = Sysutils::StrToFloatDef(SmpChan1Edit->Text, 0);
    const double SmpCh2 = Sysutils::StrToFloatDef(SmpChan2Edit->Text, 0);
    if (En1    > 0 && En2    > En1    &&
        SrcCh1 > 0 && SrcCh2 > SrcCh1 &&
        SmpCh1 > 0 && SmpCh2 > SmpCh1 &&
        OrigSampleSpc.IsValid())
    {
        TSpectrum ShiftedSample;
        if (OrigSampleSpc.Shift(SrcCh1, SrcCh2, SmpCh1, SmpCh2, En1, En2, ShiftedSample))
        {
            SampleSpc = ShiftedSample;
            Result = true;
        }
    }
    if (!Result)
    {
        SampleSpc = OrigSampleSpc;
    }
    return Result;
}
//---------------------------------------------------------------------------
bool TMainForm::ShiftBkg()
{
    bool Result = false;
    const double En1 = Sysutils::StrToFloatDef(Energy1Edit->Text, 0);
    const double En2 = Sysutils::StrToFloatDef(Energy2Edit->Text, 0);
    const double SrcCh1 = Ths[VI].Channel1;
    const double SrcCh2 = Ths[VI].Channel2;
    const double BkgCh1 = Sysutils::StrToFloatDef(BkgChan1Edit->Text, 0);
    const double BkgCh2 = Sysutils::StrToFloatDef(BkgChan2Edit->Text, 0);
    if (En1    > 0 && En2    > En1 &&
        SrcCh1 > 0 && SrcCh2 > SrcCh1 &&
        BkgCh1 > 0 && BkgCh2 > BkgCh1 &&
        OrigBkgSpc.IsValid())
    {
        TSpectrum ShiftedSample;
        if (OrigBkgSpc.Shift(SrcCh1, SrcCh2, BkgCh1, BkgCh2, En1, En2, ShiftedSample))
        {
            BkgSpc = ShiftedSample;
            Result = true;
        }
    }
    if (!Result)
    {
        BkgSpc = OrigBkgSpc;
    }
    return Result;
}
//---------------------------------------------------------------------------
bool TMainForm::ShiftTh()
{
    bool Result = false;
    const double En1 = Sysutils::StrToFloatDef(Energy1Edit->Text, 0);
    const double En2 = Sysutils::StrToFloatDef(Energy2Edit->Text, 0);
    const double SrcCh1 = Ths[VI].Channel1;
    const double SrcCh2 = Ths[VI].Channel2;
    const double ThCh1 = Sysutils::StrToFloatDef(ThChan1Edit->Text, 0);
    const double ThCh2 = Sysutils::StrToFloatDef(ThChan2Edit->Text, 0);
    if (En1    > 0 && En2    > En1 &&
        SrcCh1 > 0 && SrcCh2 > SrcCh1 &&
        ThCh1  > 0 && ThCh2  > ThCh1 &&
        OrigThSpc.IsValid())
    {
        TSpectrum ShiftedSample;
        if (OrigThSpc.Shift(SrcCh1, SrcCh2, ThCh1, ThCh2, En1, En2, ShiftedSample))
        {
            ThSpc = ShiftedSample;
            Result = true;
        }
    }
    if (!Result)
    {
        ThSpc = OrigThSpc;
    }
    return Result;
}
//---------------------------------------------------------------------------
bool TMainForm::ShiftRa()
{
    bool Result = false;
    const double En1 = Sysutils::StrToFloatDef(Energy1Edit->Text, 0);
    const double En2 = Sysutils::StrToFloatDef(Energy2Edit->Text, 0);
    const double SrcCh1 = Ths[VI].Channel1;
    const double SrcCh2 = Ths[VI].Channel2;
    const double RaCh1 = Sysutils::StrToFloatDef(RaChan1Edit->Text, 0);
    const double RaCh2 = Sysutils::StrToFloatDef(RaChan2Edit->Text, 0);
    if (En1    > 0 && En2    > En1 &&
        SrcCh1 > 0 && SrcCh2 > SrcCh1 &&
        RaCh1  > 0 && RaCh2  > RaCh1 &&
        OrigRaSpc.IsValid())
    {
        TSpectrum ShiftedSample;
        if (OrigRaSpc.Shift(SrcCh1, SrcCh2, RaCh1, RaCh2, En1, En2, ShiftedSample))
        {
            RaSpc = ShiftedSample;
            Result = true;
        }
    }
    if (!Result)
    {
        RaSpc = OrigRaSpc;
    }
    return Result;
}
//---------------------------------------------------------------------------
bool TMainForm::ShiftK()
{
    bool Result = false;
    const double En1 = Sysutils::StrToFloatDef(Energy1Edit->Text, 0);
    const double En2 = Sysutils::StrToFloatDef(Energy2Edit->Text, 0);
    const double SrcCh1 = Ths[VI].Channel1;
    const double SrcCh2 = Ths[VI].Channel2;
    const double KCh1 = Sysutils::StrToFloatDef(KChan1Edit->Text, 0);
    const double KCh2 = Sysutils::StrToFloatDef(KChan2Edit->Text, 0);
    if (En1    > 0 && En2    > En1 &&
        SrcCh1 > 0 && SrcCh2 > SrcCh1 &&
        KCh1   > 0 && KCh2   > KCh1 &&
        OrigKSpc.IsValid())
    {
        TSpectrum ShiftedSample;
        if (OrigKSpc.Shift(SrcCh1, SrcCh2, KCh1, KCh2, En1, En2, ShiftedSample))
        {
            KSpc = ShiftedSample;
            Result = true;
        }
    }
    if (!Result)
    {
        KSpc = OrigKSpc;
    }
    return Result;
}
//---------------------------------------------------------------------------
bool TMainForm::ShiftCs()
{
    bool Result = false;
    const double En1 = Sysutils::StrToFloatDef(Energy1Edit->Text, 0);
    const double En2 = Sysutils::StrToFloatDef(Energy2Edit->Text, 0);
    const double SrcCh1 = Ths[VI].Channel1;
    const double SrcCh2 = Ths[VI].Channel2;
    const double CsCh1 = Sysutils::StrToFloatDef(CsChan1Edit->Text, 0);
    const double CsCh2 = Sysutils::StrToFloatDef(CsChan2Edit->Text, 0);
    if (En1    > 0 && En2    > En1 &&
        SrcCh1 > 0 && SrcCh2 > SrcCh1 &&
        CsCh1  > 0 && CsCh2  > CsCh1 &&
        OrigCsSpc.IsValid())
    {
        TSpectrum ShiftedSample;
        if (OrigCsSpc.Shift(SrcCh1, SrcCh2, CsCh1, CsCh2, En1, En2, ShiftedSample))
        {
            CsSpc = ShiftedSample;
            Result = true;
        }
    }
    if (!Result)
    {
        CsSpc = OrigCsSpc;
    }
    return Result;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::OnShiftingDataChange(TObject *Sender)
{
    if (ShiftingTimer->Enabled)
    {
        ShiftingTimer->Enabled = false;
    }
    TEdit *Edit = dynamic_cast<TEdit*>(Sender);
    if (!Edit->Focused())
    {
        bool Shifted = false;
        if (Edit == SmpChan1Edit || Edit == SmpChan2Edit)
        {
            Shifted = ShiftSrc();
        }
        else if (Edit == BkgChan1Edit || Edit == BkgChan2Edit)
        {
            Shifted = ShiftBkg();
        }
        else if (Edit == ThChan1Edit || Edit == ThChan2Edit)
        {
            Shifted = ShiftTh();
        }
        else if (Edit == RaChan1Edit || Edit == RaChan2Edit)
        {
            Shifted = ShiftRa();
        }
        else if (Edit == KChan1Edit || Edit == KChan2Edit)
        {
            Shifted = ShiftK();
        }
        else if (Edit == CsChan1Edit || Edit == CsChan2Edit)
        {
            Shifted = ShiftCs();
        }
        if (Shifted && SampleSpc.IsValid() && BkgSpc.IsValid() && ThSpc.IsValid() &&
            RaSpc.IsValid() && KSpc.IsValid() && CsSpc.IsValid())
        {
            DecomposeSampleSpectrum();
        }
    }
    else
    {
        ShiftingTimer->Tag = reinterpret_cast<NativeInt>(Edit);
        ShiftingTimer->Enabled = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::OnShiftingTimerTimer(TObject *Sender)
{
    ShiftingTimer->Enabled = false;
    TEdit *Edit = reinterpret_cast<TEdit*>(ShiftingTimer->Tag);
    bool Shifted = false;
    if (Edit == SmpChan1Edit || Edit == SmpChan2Edit)
    {
         Shifted = ShiftSrc();
    }
    else if (Edit == BkgChan1Edit || Edit == BkgChan2Edit)
    {
        Shifted = ShiftBkg();
    }
    else if (Edit == ThChan1Edit || Edit == ThChan2Edit)
    {
        Shifted = ShiftTh();
    }
    else if (Edit == RaChan1Edit || Edit == RaChan2Edit)
    {
        Shifted = ShiftRa();
    }
    else if (Edit == KChan1Edit || Edit == KChan2Edit)
    {
        Shifted = ShiftK();
    }
    else if (Edit == CsChan1Edit || Edit == CsChan2Edit)
    {
        Shifted = ShiftCs();
    }
    if (Shifted && SampleSpc.IsValid() && BkgSpc.IsValid() && ThSpc.IsValid() &&
        RaSpc.IsValid() && KSpc.IsValid() && CsSpc.IsValid())
    {
        DecomposeSampleSpectrum();
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::OnCh1LeftShiftBtnClick(TObject *Sender)
{
    TEdit *DValEdit1;
    TEdit *Chan1Edit;
    if (Sender == SmpCh1LeftShiftBtn)
    {
        DValEdit1 = SmpDValEdit1;
        Chan1Edit = SmpChan1Edit;
    }
    else if (Sender == BkgCh1LeftShiftBtn)
    {
        DValEdit1 = BkgDValEdit1;
        Chan1Edit = BkgChan1Edit;
    }
    else if (Sender == ThCh1LeftShiftBtn)
    {
        DValEdit1 = ThDValEdit1;
        Chan1Edit = ThChan1Edit;
    }
    else if (Sender == RaCh1LeftShiftBtn)
    {
        DValEdit1 = RaDValEdit1;
        Chan1Edit = RaChan1Edit;
    }
    else if (Sender == KCh1LeftShiftBtn)
    {
        DValEdit1 = KDValEdit1;
        Chan1Edit = KChan1Edit;
    }
    else if (Sender == CsCh1LeftShiftBtn)
    {
        DValEdit1 = CsDValEdit1;
        Chan1Edit = CsChan1Edit;
    }
    else
    {
        return;
    }
    if (!DValEdit1->Focused())
    {
        DValEdit1->SetFocus();
    }
    double Val = Sysutils::StrToFloatDef(Chan1Edit->Text, 0);
    if (Val <= 0)
    {
        return;
    }
    double dVal = Sysutils::StrToFloatDef(DValEdit1->Text, 0);
    if (dVal <= 0)
    {
        dVal = 1;
    }
    Val += dVal;
    Chan1Edit->Text = Val;
    OnShiftingDataChange(Chan1Edit);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::OnCh1RightShiftBtnClick(TObject *Sender)
{
    TEdit *DValEdit1;
    TEdit *Chan1Edit;
    if (Sender == SmpCh1RightShiftBtn)
    {
        DValEdit1 = SmpDValEdit1;
        Chan1Edit = SmpChan1Edit;
    }
    else if (Sender == BkgCh1RightShiftBtn)
    {
        DValEdit1 = BkgDValEdit1;
        Chan1Edit = BkgChan1Edit;
    }
    else if (Sender == ThCh1RightShiftBtn)
    {
        DValEdit1 = ThDValEdit1;
        Chan1Edit = ThChan1Edit;
    }
    else if (Sender == RaCh1RightShiftBtn)
    {
        DValEdit1 = RaDValEdit1;
        Chan1Edit = RaChan1Edit;
    }
    else if (Sender == KCh1RightShiftBtn)
    {
        DValEdit1 = KDValEdit1;
        Chan1Edit = KChan1Edit;
    }
    else if (Sender == CsCh1RightShiftBtn)
    {
        DValEdit1 = CsDValEdit1;
        Chan1Edit = CsChan1Edit;
    }
    else
    {
        return;
    }
    if (!DValEdit1->Focused())
    {
        DValEdit1->SetFocus();
    }
    double Val = Sysutils::StrToFloatDef(Chan1Edit->Text, 0);
    if (Val <= 0)
    {
        return;
    }
    double dVal = Sysutils::StrToFloatDef(DValEdit1->Text, 0);
    if (dVal <= 0)
    {
        dVal = 1;
    }
    Val -= dVal;
    Chan1Edit->Text = Val;
    OnShiftingDataChange(Chan1Edit);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::OnCh2LeftShiftBtnClick(TObject *Sender)
{
    TEdit *DValEdit2;
    TEdit *Chan2Edit;
    if (Sender == SmpCh2LeftShiftBtn)
    {
        DValEdit2 = SmpDValEdit2;
        Chan2Edit = SmpChan2Edit;
    }
    else if (Sender == BkgCh2LeftShiftBtn)
    {
        DValEdit2 = BkgDValEdit2;
        Chan2Edit = BkgChan2Edit;
    }
    else if (Sender == ThCh2LeftShiftBtn)
    {
        DValEdit2 = ThDValEdit2;
        Chan2Edit = ThChan2Edit;
    }
    else if (Sender == RaCh2LeftShiftBtn)
    {
        DValEdit2 = RaDValEdit2;
        Chan2Edit = RaChan2Edit;
    }
    else if (Sender == KCh2LeftShiftBtn)
    {
        DValEdit2 = KDValEdit2;
        Chan2Edit = KChan2Edit;
    }
    else if (Sender == CsCh2LeftShiftBtn)
    {
        DValEdit2 = CsDValEdit2;
        Chan2Edit = CsChan2Edit;
    }
    else
    {
        return;
    }
    if (!DValEdit2->Focused())
    {
        DValEdit2->SetFocus();
    }
    double Val = Sysutils::StrToFloatDef(Chan2Edit->Text, 0);
    if (Val <= 0)
    {
        return;
    }
    double dVal = Sysutils::StrToFloatDef(DValEdit2->Text, 0);
    if (dVal <= 0)
    {
        dVal = 1;
    }
    Val += dVal;
    Chan2Edit->Text = Val;
    OnShiftingDataChange(Chan2Edit);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::OnCh2RightShiftBtnClick(TObject *Sender)
{
    TEdit *DValEdit2;
    TEdit *Chan2Edit;
    if (Sender == SmpCh2RightShiftBtn)
    {
        DValEdit2 = SmpDValEdit2;
        Chan2Edit = SmpChan2Edit;
    }
    else if (Sender == BkgCh2RightShiftBtn)
    {
        DValEdit2 = BkgDValEdit2;
        Chan2Edit = BkgChan2Edit;
    }
    else if (Sender == ThCh2RightShiftBtn)
    {
        DValEdit2 = ThDValEdit2;
        Chan2Edit = ThChan2Edit;
    }
    else if (Sender == RaCh2RightShiftBtn)
    {
        DValEdit2 = RaDValEdit2;
        Chan2Edit = RaChan2Edit;
    }
    else if (Sender == KCh2RightShiftBtn)
    {
        DValEdit2 = KDValEdit2;
        Chan2Edit = KChan2Edit;
    }
    else if (Sender == CsCh2RightShiftBtn)
    {
        DValEdit2 = CsDValEdit2;
        Chan2Edit = CsChan2Edit;
    }
    else
    {
        return;
    }
    if (!DValEdit2->Focused())
    {
        DValEdit2->SetFocus();
    }
    double Val = Sysutils::StrToFloatDef(Chan2Edit->Text, 0);
    if (Val <= 0)
    {
        return;
    }
    double dVal = Sysutils::StrToFloatDef(DValEdit2->Text, 0);
    if (dVal <= 0)
    {
        dVal = 1;
    }
    Val -= dVal;
    Chan2Edit->Text = Val;
    OnShiftingDataChange(Chan2Edit);
}
//---------------------------------------------------------------------------
int TMainForm::CalcCenterOfPeak(const TSpectrum &Spc, const double Energy) const
{
    try
    {
        if (Spc.IsValid())
        {
            return Math::Ceil((Energy - Spc.B) / Spc.K);
        }
    }
    catch (Exception &)
    {
    }
    return 0;
}
//---------------------------------------------------------------------------
bool TMainForm::OpenSampleSpectrum(const String &FileName)
{
    TSpectrum Spc;
    if (!Spc.LoadFromFile(FileName))
    {
        return false;
    }
    else if (!Utils::IsEqual(Spc.Volume, Ths[VI].Volume))
    {
        String ErrorMessage = L"Spektrda namuna hajmi noto'g'ri.";
        if (LangID == 1)
        {
            ErrorMessage = L"Sample volume is not valid.";
        }
        Application->MessageBox(ErrorMessage.c_str(), ErrorTitle.c_str(), MB_OK | MB_ICONERROR);
        return false;
    }
    SampleSpc = Spc;
    OrigSampleSpc = SampleSpc;
    SampleFileName = FileName;
    SampleTime->Text = Utils::RoundFloatValue(SampleSpc.Duration);
    const double Weight =
        SameText(SampleSpc.WeightUnit, L"kg") ? (SampleSpc.Weight * 1000) : SampleSpc.Weight;
    SampleMass->Text = Utils::RoundFloatValue(Weight);
    SampleDensity->Text = Utils::RoundFloatValue(SampleSpc.DensityInGramPerLitre);

    SmpChan1Edit->OnChange = 0;
    SmpChan2Edit->OnChange = 0;
    try
    {
        SmpChan1Edit->Text = CalcCenterOfPeak(OrigSampleSpc, Ths[VI].Energy1);
        SmpChan2Edit->Text = CalcCenterOfPeak(OrigSampleSpc, Ths[VI].Energy2);
    }
    __finally
    {
        SmpChan1Edit->OnChange = OnShiftingDataChange;
        SmpChan2Edit->OnChange = OnShiftingDataChange;
    }

    ShiftSrc();
    CreateVirtualSpectra();
    if (SampleSpc.IsValid() && BkgSpc.IsValid() && ThSpc.IsValid() &&
        RaSpc.IsValid() && KSpc.IsValid() && CsSpc.IsValid())
    {
        LOG(L"Decomposing sample spectrum.");
        DecomposeSampleSpectrum();
    }
    Caption = AppName + L" - " + FileName;
    return true;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::OpenButtonClick(TObject *Sender)
{
    OpenSpectrumAction->Execute();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::OpenSpectrumActionExecute(TObject *Sender)
{
    OpenDialog->Filter = Utils::GetDialogBoxFilterForSpectraFiles(true);
    OpenDialog->Options = OpenDialog->Options >> ofAllowMultiSelect;
    OpenDialog->FileName = L"";
    if (!OpenDialog->Execute(Handle))
    {
        return;
    }
    if (!SubtractBkgAction->Checked)
    {
        SubtractBkgAction->Checked = true;
    }
    if (Sysutils::ExtractFileExt(OpenDialog->FileName).LowerCase() == L".par")
    {
        OpenParametersAction->Execute();
    }
    else
    {
        OpenSampleSpectrum(OpenDialog->FileName);
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::OpenParametersActionExecute(TObject *Sender)
{
    std::unique_ptr<TIniFile> IniFile(new TIniFile(OpenDialog->FileName));

    const bool OK = OpenSampleSpectrum(IniFile->ReadString(L"Path", L"FileName", L""));

    ThSnSe2->Text = IniFile->ReadString(L"Input", ThSnSe2->Name, L"");
    RaSnSe2->Text = IniFile->ReadString(L"Input", RaSnSe2->Name, L"");
    KSnSe2->Text = IniFile->ReadString(L"Input", KSnSe2->Name, L"");
    CsSnSe2->Text = IniFile->ReadString(L"Input", CsSnSe2->Name, L"");

    SampleDensity->Text = IniFile->ReadString(L"Input", SampleDensity->Name, L"");
    SampleOrigMass->Text = IniFile->ReadString(L"Input", SampleOrigMass->Name, L"");
    SampleSquare->Text = IniFile->ReadString(L"Input", SampleSquare->Name, L"");

    SmpChan1Edit->Text = IniFile->ReadString(L"Input", SmpChan1Edit->Name, L"");
    SmpChan2Edit->Text = IniFile->ReadString(L"Input", SmpChan2Edit->Name, L"");
    SmpDValEdit1->Text = IniFile->ReadString(L"Input", SmpDValEdit1->Name, L"");
    SmpDValEdit2->Text = IniFile->ReadString(L"Input", SmpDValEdit2->Name, L"");

    BkgChan1Edit->Text = IniFile->ReadString(L"Input", BkgChan1Edit->Name, L"");
    BkgChan2Edit->Text = IniFile->ReadString(L"Input", BkgChan2Edit->Name, L"");
    BkgDValEdit1->Text = IniFile->ReadString(L"Input", BkgDValEdit1->Name, L"");
    BkgDValEdit2->Text = IniFile->ReadString(L"Input", BkgDValEdit2->Name, L"");

    ThChan1Edit->Text = IniFile->ReadString(L"Input", ThChan1Edit->Name, L"");
    ThChan2Edit->Text = IniFile->ReadString(L"Input", ThChan2Edit->Name, L"");
    ThDValEdit1->Text = IniFile->ReadString(L"Input", ThDValEdit1->Name, L"");
    ThDValEdit2->Text = IniFile->ReadString(L"Input", ThDValEdit2->Name, L"");

    RaChan1Edit->Text = IniFile->ReadString(L"Input", RaChan1Edit->Name, L"");
    RaChan2Edit->Text = IniFile->ReadString(L"Input", RaChan2Edit->Name, L"");
    RaDValEdit1->Text = IniFile->ReadString(L"Input", RaDValEdit1->Name, L"");
    RaDValEdit2->Text = IniFile->ReadString(L"Input", RaDValEdit2->Name, L"");

    KChan1Edit->Text = IniFile->ReadString(L"Input", KChan1Edit->Name, L"");
    KChan2Edit->Text = IniFile->ReadString(L"Input", KChan2Edit->Name, L"");
    KDValEdit1->Text = IniFile->ReadString(L"Input", KDValEdit1->Name, L"");
    KDValEdit2->Text = IniFile->ReadString(L"Input", KDValEdit2->Name, L"");

    CsChan1Edit->Text = IniFile->ReadString(L"Input", CsChan1Edit->Name, L"");
    CsChan2Edit->Text = IniFile->ReadString(L"Input", CsChan2Edit->Name, L"");
    CsDValEdit1->Text = IniFile->ReadString(L"Input", CsDValEdit1->Name, L"");
    CsDValEdit2->Text = IniFile->ReadString(L"Input", CsDValEdit2->Name, L"");

    if (OK)
    {
        CreateVirtualSpectra();
        if (SampleSpc.IsValid() && BkgSpc.IsValid() && ThSpc.IsValid() &&
            RaSpc.IsValid() && KSpc.IsValid() && CsSpc.IsValid())
        {
            DecomposeSampleSpectrum();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SaveSpectraButtonClick(TObject *Sender)
{
    SaveSpectraAction->Execute();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SaveSpectraActionExecute(TObject *Sender)
{
    const int __LangID = LangID;
    if (!SampleSpc.IsValid() || SampleSpectrum->Count() == 0)
    {
        String ErrorMsg = L"Namuna spektri mavjud emas, yoki unda xatoliklar bor.";
        if (__LangID == 1)
        {
            ErrorMsg = L"Spectrum does not exist, or there are one or more errors in it.";
        }
        Application->MessageBox(ErrorMsg.c_str(), ErrorTitle.c_str(), MB_OK | MB_ICONERROR);
        return;
    }

    String FolderName;
    PIDLIST_ABSOLUTE pidl = SHBrowseForFolderW(&BrowseInfo);
    if (pidl != nullptr)
    {
        if (SHGetPathFromIDListW(pidl, DispName))
        {
            DispName[MAX_PATH - 1] = 0;
            FolderName = DispName;
        }
        CoTaskMemFree(pidl);
    }
    else
    {
        return;
    }

    if (FolderName.IsEmpty())
    {
        String ErrorMsg = L"Manzil tanlashda xatolik yuz berdi.";
        if (__LangID == 1)
        {
            ErrorMsg = L"An error occurred upon selecting the directory.";
        }
        Application->MessageBox(ErrorMsg.c_str(), ErrorTitle.c_str(), MB_OK | MB_ICONERROR);
        return;
    }

    String Msg0 = L"Quyidagi spektrni yaratib bo'lmadi:\r\n\r\n";
    String ResultMsgText = L"Barcha spektrlar saqlandi.";
    String ResultMsgTitle = L"Ma'lumot";
    String Smp = L"Nam";
    String Bkgn = L"Fon";
    if (__LangID == 1)
    {
        Msg0 = L"The following spectrum couldn't be created:\r\n\r\n";
        ResultMsgText = L"All spectra saved successfully.";
        ResultMsgTitle = L"Information";
        Smp = L"Smp";
        Bkgn = L"Bkg";
    }

    bool AllOK = true;
    const String &FileName = ExtractFileName(SampleFileName);
    const String &S = FolderName + L"\\A_" + FileName + L"." + Smp + L".txt";
    const String &Bkg = FolderName + L"\\B_" + FileName + L"." + Bkgn + L".txt";
    const String &SBkg = FolderName + L"\\C_" + FileName + L"." + Smp + L"-" + Bkgn + L".txt";
    const String &Th = FolderName + L"\\D_" + FileName + L".Th232.txt";
    const String &SBkgTh = FolderName + L"\\E_" + FileName + L"." + Smp + L"-" + Bkgn + L"-Th.txt";
    const String &Ra = FolderName + L"\\F_" + FileName + L".Ra226.txt";
    const String &SBkgThRa = FolderName + L"\\G_" + FileName + L"." + Smp + L"-" + Bkgn + L"-Th-Ra.txt";
    const String &K = FolderName + L"\\H_" + FileName + L".K40.txt";
    const String &SBkgThRaK = FolderName + L"\\I_" + FileName + L"." + Smp + L"-" + Bkgn + L"-Th-Ra-K.txt";
    const String &Cs = FolderName + L"\\J_" + FileName + L".Cs137.txt";
    const String &SBkgThRaKCs = FolderName + L"\\K_" + FileName + L"." + Smp + L"-" + Bkgn + L"-Th-Ra-K-Cs.txt";

    if (SampleSpc.IsValid() && SampleSpectrum->Count() > 0 &&
        !SampleSpc.WriteCountsToTextFile(S, false, true))
    {
        const String &Msg = Msg0 + S;
        Application->MessageBox(Msg.c_str(), ErrorTitle.c_str(), MB_OK | MB_ICONERROR);
        AllOK = false;
    }

    if (BkgSpcWithCoeff.IsValid() && BkgSpectrum->Count() > 0 &&
        !BkgSpcWithCoeff.WriteCountsToTextFile(Bkg, false, true))
    {
        const String &Msg = Msg0 + Bkg;
        Application->MessageBox(Msg.c_str(), ErrorTitle.c_str(), MB_OK | MB_ICONERROR);
        AllOK = false;
    }

    if (Sample_M_Bkg.IsValid() && SampleSpectrum->Count() > 0 && BkgSpectrum->Count() > 0 &&
        !Sample_M_Bkg.WriteCountsToTextFile(SBkg, false, true))
    {
        const String &Msg = Msg0 + SBkg;
        Application->MessageBox(Msg.c_str(), ErrorTitle.c_str(), MB_OK | MB_ICONERROR);
        AllOK = false;
    }

    if (ThSpcWithCoeff.IsValid() && Sysutils::StrToFloatDef(ThSnSe2->Text, 0) > 0 &&
        !ThSpcWithCoeff.WriteCountsToTextFile(Th, false, true))
    {
        const String &Msg = Msg0 + Th;
        Application->MessageBox(Msg.c_str(), ErrorTitle.c_str(), MB_OK | MB_ICONERROR);
        AllOK = false;
    }

    if (Sample_M_Th.IsValid() && Sysutils::StrToFloatDef(ThSnSe2->Text, 0) > 0 &&
        !Sample_M_Th.WriteCountsToTextFile(SBkgTh, false, true))
    {
        const String &Msg = Msg0 + SBkgTh;
        Application->MessageBox(Msg.c_str(), ErrorTitle.c_str(), MB_OK | MB_ICONERROR);
        AllOK = false;
    }

    if (RaSpcWithCoeff.IsValid() && Sysutils::StrToFloatDef(RaSnSe2->Text, 0) > 0 &&
        !RaSpcWithCoeff.WriteCountsToTextFile(Ra, false, true))
    {
        const String &Msg = Msg0 + Ra;
        Application->MessageBox(Msg.c_str(), ErrorTitle.c_str(), MB_OK | MB_ICONERROR);
        AllOK = false;
    }

    if (Sample_M_Ra.IsValid() && Sysutils::StrToFloatDef(RaSnSe2->Text, 0) > 0 &&
        !Sample_M_Ra.WriteCountsToTextFile(SBkgThRa, false, true))
    {
        const String &Msg = Msg0 + SBkgThRa;
        Application->MessageBox(Msg.c_str(), ErrorTitle.c_str(), MB_OK | MB_ICONERROR);
        AllOK = false;
    }

    if (KSpcWithCoeff.IsValid() && Sysutils::StrToFloatDef(KSnSe2->Text, 0) > 0 &&
        !KSpcWithCoeff.WriteCountsToTextFile(K, false, true))
    {
        const String &Msg = Msg0 + K;
        Application->MessageBox(Msg.c_str(), ErrorTitle.c_str(), MB_OK | MB_ICONERROR);
        AllOK = false;
    }

    if (Sample_M_K.IsValid() && Sysutils::StrToFloatDef(KSnSe2->Text, 0) > 0 &&
        !Sample_M_K.WriteCountsToTextFile(SBkgThRaK, false, true))
    {
        const String &Msg = Msg0 + SBkgThRaK;
        Application->MessageBox(Msg.c_str(), ErrorTitle.c_str(), MB_OK | MB_ICONERROR);
        AllOK = false;
    }

    if (CsSpcWithCoeff.IsValid() && Sysutils::StrToFloatDef(CsSnSe2->Text, 0) > 0 &&
        !CsSpcWithCoeff.WriteCountsToTextFile(Cs, false, true))
    {
        const String &Msg = Msg0 + Cs;
        Application->MessageBox(Msg.c_str(), ErrorTitle.c_str(), MB_OK | MB_ICONERROR);
        AllOK = false;
    }

    if (Sample_M_Cs.IsValid() && Sysutils::StrToFloatDef(CsSnSe2->Text, 0) > 0 &&
        !Sample_M_Cs.WriteCountsToTextFile(SBkgThRaKCs, false, true))
    {
        const String Msg = Msg0 + SBkgThRaKCs;
        Application->MessageBox(Msg.c_str(), ErrorTitle.c_str(), MB_OK | MB_ICONERROR);
        AllOK = false;
    }

    Sysutils::DeleteFile(FolderName + L"\\" + FileName + L"." + Smp + L".par");
    SaveParametersFile(FolderName + L"\\" + FileName + L"." + Smp + L".par");

    if (AllOK)
    {
        Application->MessageBox(ResultMsgText.c_str(), ResultMsgTitle.c_str(), MB_OK | MB_ICONINFORMATION);
        ShellExecuteW(Handle, L"explore", FolderName.c_str(), nullptr, nullptr, SW_SHOW);
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SaveParametersActionExecute(TObject *Sender)
{
    const int __LangID = LangID;
    if (!SampleSpc.IsValid() || SampleSpectrum->Count() == 0)
    {
        String ErrorMsg = L"Namuna spektri mavjud emas, yoki unda xatoliklar bor.";
        if (__LangID == 1)
        {
            ErrorMsg = L"Spectrum does not exist, or there are one or more errors in it.";
        }
        Application->MessageBox(ErrorMsg.c_str(), ErrorTitle.c_str(), MB_OK | MB_ICONERROR);
        return;
    }

    SaveDialog->Filter = L"PAR fayllar (*.par)|*.par";
    if (__LangID == 1)
    {
        SaveDialog->Filter = L"PAR files (*.par)|*.par";
    }
    const String &FileName = Sysutils::ExtractFileName(SampleFileName);
    SaveDialog->FileName = !FileName.IsEmpty() ? Sysutils::ChangeFileExt(FileName, L".par") : String();
    if (!SaveDialog->Execute(Handle))
    {
        return;
    }
    SaveParametersFile(SaveDialog->FileName);
}
//---------------------------------------------------------------------------
void TMainForm::SaveParametersFile(const String &FileName)
{
    try
    {
        std::unique_ptr<TIniFile> IniFile(new TIniFile(FileName));
        IniFile->WriteString(L"Path", L"FileName", SampleFileName);

        IniFile->WriteString(L"Input", ThSnSe2->Name, ThSnSe2->Text);
        IniFile->WriteString(L"Input", RaSnSe2->Name, RaSnSe2->Text);
        IniFile->WriteString(L"Input", KSnSe2->Name, KSnSe2->Text);
        IniFile->WriteString(L"Input", CsSnSe2->Name, CsSnSe2->Text);

        IniFile->WriteString(L"Input", SampleDensity->Name, SampleDensity->Text);
        IniFile->WriteString(L"Input", SampleOrigMass->Name, SampleOrigMass->Text);
        IniFile->WriteString(L"Input", SampleSquare->Name, SampleSquare->Text);

        IniFile->WriteString(L"Input", SmpChan1Edit->Name, SmpChan1Edit->Text);
        IniFile->WriteString(L"Input", SmpChan2Edit->Name, SmpChan2Edit->Text);
        IniFile->WriteString(L"Input", SmpDValEdit1->Name, SmpDValEdit1->Text);
        IniFile->WriteString(L"Input", SmpDValEdit2->Name, SmpDValEdit2->Text);

        IniFile->WriteString(L"Input", BkgChan1Edit->Name, BkgChan1Edit->Text);
        IniFile->WriteString(L"Input", BkgChan2Edit->Name, BkgChan2Edit->Text);
        IniFile->WriteString(L"Input", BkgDValEdit1->Name, BkgDValEdit1->Text);
        IniFile->WriteString(L"Input", BkgDValEdit2->Name, BkgDValEdit2->Text);

        IniFile->WriteString(L"Input", ThChan1Edit->Name, ThChan1Edit->Text);
        IniFile->WriteString(L"Input", ThChan2Edit->Name, ThChan2Edit->Text);
        IniFile->WriteString(L"Input", ThDValEdit1->Name, ThDValEdit1->Text);
        IniFile->WriteString(L"Input", ThDValEdit2->Name, ThDValEdit2->Text);

        IniFile->WriteString(L"Input", RaChan1Edit->Name, RaChan1Edit->Text);
        IniFile->WriteString(L"Input", RaChan2Edit->Name, RaChan2Edit->Text);
        IniFile->WriteString(L"Input", RaDValEdit1->Name, RaDValEdit1->Text);
        IniFile->WriteString(L"Input", RaDValEdit2->Name, RaDValEdit2->Text);

        IniFile->WriteString(L"Input", KChan1Edit->Name, KChan1Edit->Text);
        IniFile->WriteString(L"Input", KChan2Edit->Name, KChan2Edit->Text);
        IniFile->WriteString(L"Input", KDValEdit1->Name, KDValEdit1->Text);
        IniFile->WriteString(L"Input", KDValEdit2->Name, KDValEdit2->Text);

        IniFile->WriteString(L"Input", CsChan1Edit->Name, CsChan1Edit->Text);
        IniFile->WriteString(L"Input", CsChan2Edit->Name, CsChan2Edit->Text);
        IniFile->WriteString(L"Input", CsDValEdit1->Name, CsDValEdit1->Text);
        IniFile->WriteString(L"Input", CsDValEdit2->Name, CsDValEdit2->Text);
    }
    catch (const Exception &E)
    {
        LOGEXCEPTION(E);
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SelectFilesActionExecute(TObject *Sender)
{
    OpenDialog->Filter = Utils::GetDialogBoxFilterForSpectraFiles();
    OpenDialog->Options = OpenDialog->Options << ofAllowMultiSelect;
    OpenDialog->FileName = L"";
    if (OpenDialog->Execute(Handle))
    {
        if (BatchProcessingResultsForm != nullptr)
        {
            BatchProcessingResultsForm->Close();
        }
        BatchProcessingResultsForm = new TBatchProcessingResultsForm(Application);
        BatchProcessingThread.reset(new TBatchProcessingThread(
            GetData(), L"", OpenDialog->Files, BatchProcessingResultsForm->Handle));
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::BatchProcessButtonClick(TObject *Sender)
{
    SelectDirectoryAction->Execute();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SelectDirectoryActionExecute(TObject *Sender)
{
    String FolderName;
    PIDLIST_ABSOLUTE pidl = SHBrowseForFolderW(&BrowseInfo);
    if (pidl != nullptr)
    {
        if (SHGetPathFromIDListW(pidl, DispName))
        {
            DispName[MAX_PATH - 1] = 0;
            FolderName = DispName;
        }
        CoTaskMemFree(pidl);
    }
    else
    {
        return;
    }

    if (FolderName.IsEmpty())
    {
        String ErrorMsg = L"Manzil tanlashda xatolik yuz berdi.";
        if (LangID == 1)
        {
            ErrorMsg = L"An error occurred upon selecting the directory.";
        }
        Application->MessageBox(ErrorMsg.c_str(), ErrorTitle.c_str(), MB_OK | MB_ICONERROR);
        return;
    }

    if (BatchProcessingResultsForm != nullptr)
    {
        BatchProcessingResultsForm->Close();
    }
    BatchProcessingResultsForm = new TBatchProcessingResultsForm(Application);
    BatchProcessingThread.reset(new TBatchProcessingThread(
        GetData(), FolderName, OpenDialog->Files, BatchProcessingResultsForm->Handle));
}
//---------------------------------------------------------------------------
void TMainForm::OpenFromBatchResult(
    const String &FileName, const String &ThC, const String &RaC, const String &KC, const String &CsC)
{
    if (OpenSampleSpectrum(FileName))
    {
        ThSnSe2->Text = ThC;
        RaSnSe2->Text = RaC;
        KSnSe2->Text = KC;
        CsSnSe2->Text = CsC;
        CreateVirtualSpectra();
        if (SampleSpc.IsValid() && BkgSpc.IsValid() && ThSpc.IsValid() &&
            RaSpc.IsValid() && KSpc.IsValid() && CsSpc.IsValid())
        {
            DecomposeSampleSpectrum();
        }
    }
}
//---------------------------------------------------------------------------
void TMainForm::ChangeUILanguage()
{
    const int __LangID = LangID;

    if (__LangID == 0)
    {
        ErrorTitle = L"Xato";
        DirSelectionString = L"Manzil tanlash...";

        LanguageAction->Caption = L"  UZ  ";

        OpenButton->Caption = L"Ochish";
        OpenSpectrumAction->Caption = L"Spektrni ochish";
        OpenParametersAction->Caption = L"Parameterlar orqali ochish";

        SaveSpectraButton->Caption = L"Saqlash";
        SaveSpectraAction->Caption = L"Spektralrni saqlash";
        SaveParametersAction->Caption = L"Parameterlarni saqlash";

        BatchProcessButton->Caption = L"Ko'p sonli spektrlar tahlili";
        SelectFilesAction->Caption = L"Fayllarni tanlash";
        SelectDirectoryAction->Caption = L"Manzilni tanlash";

        ShiftingButton->Caption = L"Spektrni siljitish";
        StandardSamplesButton->Caption = L"Etalon namunalar";
        HelpButton->Caption = L"Dastur haqida";

        ThLabel->Caption = L"Etalon namunada";
        RaLabel->Caption = ThLabel->Caption;
        KLabel->Caption = ThLabel->Caption;
        CsLabel->Caption = ThLabel->Caption;

        ThDurLabel->Caption = L"O'lch. vaqti (sek):";
        RaDurLabel->Caption = ThDurLabel->Caption;
        KDurLabel->Caption = ThDurLabel->Caption;
        CsDurLabel->Caption = ThDurLabel->Caption;

        ThPhotoPeakLabel->Caption = L"Fotocho'qqi, Se:";
        RaPhotoPeakLabel->Caption = ThPhotoPeakLabel->Caption;
        KPhotoPeakLabel->Caption = ThPhotoPeakLabel->Caption;
        CsPhotoPeakLabel->Caption = ThPhotoPeakLabel->Caption;

        ThActLabel->Caption = L"Aktivligi (Bk):";
        RaActLabel->Caption = ThActLabel->Caption;
        KActLabel->Caption = ThActLabel->Caption;
        CsActLabel->Caption = ThActLabel->Caption;

        ThMDALabel->Caption = L"AMA (Bk/kg):";
        RaMDALabel->Caption = ThMDALabel->Caption;
        KMDALabel->Caption = ThMDALabel->Caption;
        CsMDALabel->Caption = ThMDALabel->Caption;

        ThSmpLabel->Caption = L"O'rganilayotgan namunada";
        RaSmpLabel->Caption = ThSmpLabel->Caption;
        KSmpLabel->Caption = ThSmpLabel->Caption;
        CsSmpLabel->Caption = ThSmpLabel->Caption;
        BeSmpLabel->Caption = ThSmpLabel->Caption;

        SmpThPhotoPeakLabel->Caption = L"Fotocho'qqi, Sn:";
        SmpRaPhotoPeakLabel->Caption = SmpThPhotoPeakLabel->Caption;
        SmpKPhotoPeakLabel->Caption = SmpThPhotoPeakLabel->Caption;
        SmpCsPhotoPeakLabel->Caption = SmpThPhotoPeakLabel->Caption;

        ThCoeffCalcLabel->Caption = L"Sn / Se:";
        ThCoeffLabel->Caption = ThCoeffCalcLabel->Caption;
        RaCoeffCalcLabel->Caption = ThCoeffCalcLabel->Caption;
        RaCoeffLabel->Caption = ThCoeffCalcLabel->Caption;
        KCoeffCalcLabel->Caption = ThCoeffCalcLabel->Caption;
        KCoeffLabel->Caption = ThCoeffCalcLabel->Caption;
        CsCoeffCalcLabel->Caption = ThCoeffCalcLabel->Caption;
        CsCoeffLabel->Caption = ThCoeffCalcLabel->Caption;

        SmpThActLabel->Caption = L"Aktivligi (Bk/kg):";
        SmpRaActLabel->Caption = SmpThActLabel->Caption;
        SmpKActLabel->Caption = SmpThActLabel->Caption;
        SmpCsActLabel->Caption = SmpThActLabel->Caption;

        SmpThErrorLabel->Caption = L"Xatolik (Bk/kg):";
        SmpRaErrorLabel->Caption = SmpThErrorLabel->Caption;
        SmpKErrorLabel->Caption = SmpThErrorLabel->Caption;
        SmpCsErrorLabel->Caption = SmpThErrorLabel->Caption;

        BePhotoPeakLabel->Caption = L"Fotocho'qqi:";
        if (BeActivityPerKgOrSq->Tag)
        {
            BeActLabel->Caption = L"Aktivligi (Bk/kg):";
            BeErrorLabel->Caption = L"Xatolik (Bk/kg):";
        }
        else
        {
            BeActLabel->Caption = L"Aktivligi (Bk/m^2):";
            BeErrorLabel->Caption = L"Xatolik (Bk/m^2):";
        }
        BeMDALabel->Caption = L"AMA (Bk/kg):";
        SmpLabel->Caption = L"Namuna o'lchamlari";
        SmpDurLabel->Caption = L"O'lch. vaqti (sek):";
        SmpMassLabel->Caption = L"Massasi (Gr):";
        SmpDensityLabel->Caption = L"Zichligi (Gr/L):";
        SmpTotalMassLabel->Caption = L"Um. massasi (Gr):";
        SmpSquareLabel->Caption = L"Yuzasi (Sm^2):";

        FinalSpcChart->Title->Text->Text = L"Natijaviy spektr";
        FinalSpcChart->LeftAxis->Title->Caption = L"Impuls";
        SampleChart->Title->Text->Text = L"Oʻrganilayotgan Namuna";
        SampleChart->LeftAxis->Title->Caption = FinalSpcChart->LeftAxis->Title->Caption;
        BkgChart->Title->Text->Text = L"Tabiiy Fon";
        BkgChart->LeftAxis->Title->Caption = SampleChart->LeftAxis->Title->Caption;
        ThChart->LeftAxis->Title->Caption = SampleChart->LeftAxis->Title->Caption;
        RaChart->LeftAxis->Title->Caption = SampleChart->LeftAxis->Title->Caption;
        KChart->LeftAxis->Title->Caption = SampleChart->LeftAxis->Title->Caption;
        CsChart->LeftAxis->Title->Caption = SampleChart->LeftAxis->Title->Caption;

        SmpCh1Label->Caption = L"K1:";
        SmpCh2Label->Caption = L"K2:";
        BkgCh1Label->Caption = SmpCh1Label->Caption;
        BkgCh2Label->Caption = SmpCh2Label->Caption;
        ThCh1Label->Caption = SmpCh1Label->Caption;
        ThCh2Label->Caption = SmpCh2Label->Caption;
        RaCh1Label->Caption = SmpCh1Label->Caption;
        RaCh2Label->Caption = SmpCh2Label->Caption;
        KCh1Label->Caption = SmpCh1Label->Caption;
        KCh2Label->Caption = SmpCh2Label->Caption;
        CsCh1Label->Caption = SmpCh1Label->Caption;
        CsCh2Label->Caption = SmpCh2Label->Caption;
        SubtractBkgAction->Caption = L"Fon ayriladi";

        const String MDA(L"<MDA");
        const String AMA(L"<AMA");
        if (SampleThActivity->Text == MDA)
        {
            SampleThActivity->Text = AMA;
        }
        if (SampleRaActivity->Text == MDA)
        {
            SampleRaActivity->Text = AMA;
        }
        if (SampleKActivity->Text == MDA)
        {
            SampleKActivity->Text = AMA;
        }
        if (SampleCsActivity->Text == MDA)
        {
            SampleCsActivity->Text = AMA;
        }
        if (BeActivityPerKgOrSq->Text == MDA)
        {
            BeActivityPerKgOrSq->Text = AMA;
        }

        ThCoeffCalcLabel->Hint = L"  Namunadagi fotocho'qqining etalon namunadagi fotocho'qqi yuzasiga nisbati  ";
        RaCoeffCalcLabel->Hint = ThCoeffCalcLabel->Hint;
        KCoeffCalcLabel->Hint = ThCoeffCalcLabel->Hint;
        CsCoeffCalcLabel->Hint = ThCoeffCalcLabel->Hint;

        ThCoeffLabel->Hint = L"  Namunadagi fotocho'qqining etalon namunadagi fotocho'qqi yuzasiga nisbati  \r\n"
                             L"  O'zgartirish mumkin  ";
        RaCoeffLabel->Hint = ThCoeffLabel->Hint;
        KCoeffLabel->Hint = ThCoeffLabel->Hint;
        CsCoeffLabel->Hint = ThCoeffLabel->Hint;

        ThUpButton->Hint = L"  Koeffitsiyentni 0.001 ga orttirish  ";
        ThDownButton->Hint = L"  Koeffitsiyentni 0.001 ga kamaytirish  ";
        RaUpButton->Hint = ThUpButton->Hint;
        RaDownButton->Hint = ThDownButton->Hint;
        KUpButton->Hint = ThUpButton->Hint;
        KDownButton->Hint = ThDownButton->Hint;
        CsUpButton->Hint = ThUpButton->Hint;
        CsDownButton->Hint = ThDownButton->Hint;

        ThMDALabel->Hint = L"  Aniqlanadigan minimal aktivlik  ";
        ThMDA->Hint = ThMDALabel->Hint;
        RaMDALabel->Hint = ThMDALabel->Hint;
        RaMDA->Hint = ThMDALabel->Hint;
        KMDALabel->Hint = ThMDALabel->Hint;
        KMDA->Hint = ThMDALabel->Hint;
        CsMDALabel->Hint = ThMDALabel->Hint;
        CsMDA->Hint = ThMDALabel->Hint;
        BeMDALabel->Hint = ThMDALabel->Hint;
        BeMDA->Hint = ThMDALabel->Hint;

        const String Str = L" energiyaga to'g'ri keluvchi kanal raqami  ";
        const String E1 = Sysutils::StringReplace(ThE1Label->Caption, L":", L"", TReplaceFlags() << rfReplaceAll);
        const String E2 = Sysutils::StringReplace(ThE2Label->Caption, L":", L"", TReplaceFlags() << rfReplaceAll);
        const String keV = L" keV";
        SmpCh1Label->Hint = L"  " + (Energy1Edit->Text.IsEmpty() ? E1 : Energy1Edit->Text + keV) + Str;
        SmpChan1Edit->Hint = SmpCh1Label->Hint;
        SmpCh2Label->Hint = L"  " + (Energy2Edit->Text.IsEmpty() ? E2 : Energy2Edit->Text + keV) + Str;
        SmpChan2Edit->Hint = SmpCh2Label->Hint;

        BkgCh1Label->Hint = L"  " + (Energy1Edit->Text.IsEmpty() ? E1 : Energy1Edit->Text + keV) + Str;
        BkgChan1Edit->Hint = BkgCh1Label->Hint;
        BkgCh2Label->Hint = L"  " + (Energy2Edit->Text.IsEmpty() ? E2 : Energy2Edit->Text + keV) + Str;
        BkgChan2Edit->Hint = BkgCh2Label->Hint;

        RaCh1Label->Hint = L"  " + (Energy1Edit->Text.IsEmpty() ? E1 : Energy1Edit->Text + keV) + Str;
        RaChan1Edit->Hint = RaCh1Label->Hint;
        RaCh2Label->Hint = L"  " + (Energy2Edit->Text.IsEmpty() ? E2 : Energy2Edit->Text + keV) + Str;
        RaChan2Edit->Hint = RaCh2Label->Hint;

        KCh1Label->Hint = L"  " + (Energy1Edit->Text.IsEmpty() ? E1 : Energy1Edit->Text + keV) + Str;
        KChan1Edit->Hint = KCh1Label->Hint;
        KCh2Label->Hint = L"  " + (Energy2Edit->Text.IsEmpty() ? E2 : Energy2Edit->Text + keV) + Str;
        KChan2Edit->Hint = KCh2Label->Hint;

        CsCh1Label->Hint = L"  " + (Energy1Edit->Text.IsEmpty() ? E1 : Energy1Edit->Text + keV) + Str;
        CsChan1Edit->Hint = CsCh1Label->Hint;
        CsCh2Label->Hint = L"  " + (Energy2Edit->Text.IsEmpty() ? E2 : Energy2Edit->Text + keV) + Str;
        CsChan2Edit->Hint = CsCh2Label->Hint;

        ChangeFinalSpcScaleAction->Caption = L"Logarifmli masshtabda";
        SmoothFInalSpectrumAction->Caption = L"Silliqlangan";
    }
    else if (__LangID == 1)
    {
        ErrorTitle = L"Error";
        DirSelectionString = L"Selecting directory...";

        LanguageAction->Caption = L"  ENG  ";

        OpenButton->Caption = L"Open";
        OpenSpectrumAction->Caption = L"Open spectrum";
        OpenParametersAction->Caption = L"Open via parameters";

        SaveSpectraButton->Caption = L"Save";
        SaveSpectraAction->Caption = L"Save spectra";
        SaveParametersAction->Caption = L"Save parameters";

        BatchProcessButton->Caption = L"Batch processing";
        SelectFilesAction->Caption = L"Select files";
        SelectDirectoryAction->Caption = L"Select directory";

        ShiftingButton->Caption = L"Spectrum shifting";
        StandardSamplesButton->Caption = L"Reference samples";
        HelpButton->Caption = L"About";

        ThLabel->Caption = L"In reference sample";
        RaLabel->Caption = ThLabel->Caption;
        KLabel->Caption = ThLabel->Caption;
        CsLabel->Caption = ThLabel->Caption;

        ThDurLabel->Caption = L"Meas. durat. (sec):";
        RaDurLabel->Caption = ThDurLabel->Caption;
        KDurLabel->Caption = ThDurLabel->Caption;
        CsDurLabel->Caption = ThDurLabel->Caption;

        ThPhotoPeakLabel->Caption = L"Photopeak, Sr:";
        RaPhotoPeakLabel->Caption = ThPhotoPeakLabel->Caption;
        KPhotoPeakLabel->Caption = ThPhotoPeakLabel->Caption;
        CsPhotoPeakLabel->Caption = ThPhotoPeakLabel->Caption;

        ThActLabel->Caption = L"Activity (Bq):";
        RaActLabel->Caption = ThActLabel->Caption;
        KActLabel->Caption = ThActLabel->Caption;
        CsActLabel->Caption = ThActLabel->Caption;

        ThMDALabel->Caption = L"MDA (Bq/kg):";
        RaMDALabel->Caption = ThMDALabel->Caption;
        KMDALabel->Caption = ThMDALabel->Caption;
        CsMDALabel->Caption = ThMDALabel->Caption;

        ThSmpLabel->Caption = L"In studying sample";
        RaSmpLabel->Caption = ThSmpLabel->Caption;
        KSmpLabel->Caption = ThSmpLabel->Caption;
        CsSmpLabel->Caption = ThSmpLabel->Caption;
        BeSmpLabel->Caption = ThSmpLabel->Caption;

        SmpThPhotoPeakLabel->Caption = L"Photopeak, Ss:";
        SmpRaPhotoPeakLabel->Caption = SmpThPhotoPeakLabel->Caption;
        SmpKPhotoPeakLabel->Caption = SmpThPhotoPeakLabel->Caption;
        SmpCsPhotoPeakLabel->Caption = SmpThPhotoPeakLabel->Caption;

        ThCoeffCalcLabel->Caption = L"Ss / Sr:";
        ThCoeffLabel->Caption = ThCoeffCalcLabel->Caption;
        RaCoeffCalcLabel->Caption = ThCoeffCalcLabel->Caption;
        RaCoeffLabel->Caption = ThCoeffCalcLabel->Caption;
        KCoeffCalcLabel->Caption = ThCoeffCalcLabel->Caption;
        KCoeffLabel->Caption = ThCoeffCalcLabel->Caption;
        CsCoeffCalcLabel->Caption = ThCoeffCalcLabel->Caption;
        CsCoeffLabel->Caption = ThCoeffCalcLabel->Caption;

        SmpThActLabel->Caption = L"Activity (Bq/kg):";
        SmpRaActLabel->Caption = SmpThActLabel->Caption;
        SmpKActLabel->Caption = SmpThActLabel->Caption;
        SmpCsActLabel->Caption = SmpThActLabel->Caption;

        SmpThErrorLabel->Caption = L"Error (Bq/kg):";
        SmpRaErrorLabel->Caption = SmpThErrorLabel->Caption;
        SmpKErrorLabel->Caption = SmpThErrorLabel->Caption;
        SmpCsErrorLabel->Caption = SmpThErrorLabel->Caption;

        BePhotoPeakLabel->Caption = L"Photopeak:";
        if (BeActivityPerKgOrSq->Tag)
        {
            BeActLabel->Caption = L"Activity (Bq/kg):";
            BeErrorLabel->Caption = L"Error (Bq/kg):";
        }
        else
        {
            BeActLabel->Caption = L"Activity (Bq/m^2):";
            BeErrorLabel->Caption = L"Error (Bq/m^2):";
        }
        BeMDALabel->Caption = L"MDA (Bq/kg):";
        SmpLabel->Caption = L"Sample parameters";
        SmpDurLabel->Caption = L"Meas. durat. (sec):";
        SmpMassLabel->Caption = L"Mass (Gr):";
        SmpDensityLabel->Caption = L"Density (Gr/L):";
        SmpTotalMassLabel->Caption = L"Total mass (Gr):";
        SmpSquareLabel->Caption = L"Square (Sm^2):";

        FinalSpcChart->Title->Text->Text = L"Residual spectrum";
        FinalSpcChart->LeftAxis->Title->Caption = L"Count";
        SampleChart->Title->Text->Text = L"Sample";
        SampleChart->LeftAxis->Title->Caption = FinalSpcChart->LeftAxis->Title->Caption;
        BkgChart->Title->Text->Text = L"Background";
        BkgChart->LeftAxis->Title->Caption = SampleChart->LeftAxis->Title->Caption;
        ThChart->LeftAxis->Title->Caption = SampleChart->LeftAxis->Title->Caption;
        RaChart->LeftAxis->Title->Caption = SampleChart->LeftAxis->Title->Caption;
        KChart->LeftAxis->Title->Caption = SampleChart->LeftAxis->Title->Caption;
        CsChart->LeftAxis->Title->Caption = SampleChart->LeftAxis->Title->Caption;

        SmpCh1Label->Caption = L"C1:";
        SmpCh2Label->Caption = L"C2:";
        BkgCh1Label->Caption = SmpCh1Label->Caption;
        BkgCh2Label->Caption = SmpCh2Label->Caption;
        ThCh1Label->Caption = SmpCh1Label->Caption;
        ThCh2Label->Caption = SmpCh2Label->Caption;
        RaCh1Label->Caption = SmpCh1Label->Caption;
        RaCh2Label->Caption = SmpCh2Label->Caption;
        KCh1Label->Caption = SmpCh1Label->Caption;
        KCh2Label->Caption = SmpCh2Label->Caption;
        CsCh1Label->Caption = SmpCh1Label->Caption;
        CsCh2Label->Caption = SmpCh2Label->Caption;
        SubtractBkgAction->Caption = L"Background subtracted";

        const String MDA(L"<MDA");
        const String AMA(L"<AMA");
        if (SampleThActivity->Text == AMA)
        {
            SampleThActivity->Text = MDA;
        }
        if (SampleRaActivity->Text == AMA)
        {
            SampleRaActivity->Text = MDA;
        }
        if (SampleKActivity->Text == AMA)
        {
            SampleKActivity->Text = MDA;
        }
        if (SampleCsActivity->Text == AMA)
        {
            SampleCsActivity->Text = MDA;
        }
        if (BeActivityPerKgOrSq->Text == AMA)
        {
            BeActivityPerKgOrSq->Text = MDA;
        }

        ThCoeffCalcLabel->Hint = L"  Ratio of the photopeak area in the sample to the photopeak area in the reference sample  ";
        RaCoeffCalcLabel->Hint = ThCoeffCalcLabel->Hint;
        KCoeffCalcLabel->Hint = ThCoeffCalcLabel->Hint;
        CsCoeffCalcLabel->Hint = ThCoeffCalcLabel->Hint;

        ThCoeffLabel->Hint = L"  Ratio of the photopeak area in the sample to the photopeak area in the reference sample  \r\n"
                             L"  Can be modified  ";
        RaCoeffLabel->Hint = ThCoeffLabel->Hint;
        KCoeffLabel->Hint = ThCoeffLabel->Hint;
        CsCoeffLabel->Hint = ThCoeffLabel->Hint;

        ThUpButton->Hint = L"  Increasing the coefficient by 0.001  ";
        ThDownButton->Hint = L"  Decreasing the coefficient by 0.001  ";
        RaUpButton->Hint = ThUpButton->Hint;
        RaDownButton->Hint = ThDownButton->Hint;
        KUpButton->Hint = ThUpButton->Hint;
        KDownButton->Hint = ThDownButton->Hint;
        CsUpButton->Hint = ThUpButton->Hint;
        CsDownButton->Hint = ThDownButton->Hint;

        ThMDALabel->Hint = L"  Minimum detectable activity  ";
        ThMDA->Hint = ThMDALabel->Hint;
        RaMDALabel->Hint = ThMDALabel->Hint;
        RaMDA->Hint = ThMDALabel->Hint;
        KMDALabel->Hint = ThMDALabel->Hint;
        KMDA->Hint = ThMDALabel->Hint;
        CsMDALabel->Hint = ThMDALabel->Hint;
        CsMDA->Hint = ThMDALabel->Hint;
        BeMDALabel->Hint = ThMDALabel->Hint;
        BeMDA->Hint = ThMDALabel->Hint;

        const String Str = L"  Channel number corresponding to ";
        const String E1 = Sysutils::StringReplace(ThE1Label->Caption, L":", L"", TReplaceFlags() << rfReplaceAll);
        const String E2 = Sysutils::StringReplace(ThE2Label->Caption, L":", L"", TReplaceFlags() << rfReplaceAll);
        const String keV = L" keV";
        SmpCh1Label->Hint = Str + (Energy1Edit->Text.IsEmpty() ? E1 : Energy1Edit->Text + keV) + L" energy  ";
        SmpChan1Edit->Hint = SmpCh1Label->Hint;
        SmpCh2Label->Hint = Str + (Energy2Edit->Text.IsEmpty() ? E2 : Energy2Edit->Text + keV) + L" energy  ";
        SmpChan2Edit->Hint = SmpCh2Label->Hint;

        BkgCh1Label->Hint = Str + (Energy1Edit->Text.IsEmpty() ? E1 : Energy1Edit->Text + keV) + L" energy  ";
        BkgChan1Edit->Hint = BkgCh1Label->Hint;
        BkgCh2Label->Hint = Str + (Energy2Edit->Text.IsEmpty() ? E2 : Energy2Edit->Text + keV) + L" energy  ";
        BkgChan2Edit->Hint = BkgCh2Label->Hint;

        RaCh1Label->Hint = Str + (Energy1Edit->Text.IsEmpty() ? E1 : Energy1Edit->Text + keV) + L" energy  ";
        RaChan1Edit->Hint = RaCh1Label->Hint;
        RaCh2Label->Hint = Str + (Energy2Edit->Text.IsEmpty() ? E2 : Energy2Edit->Text + keV) + L" energy  ";
        RaChan2Edit->Hint = RaCh2Label->Hint;

        KCh1Label->Hint = Str + (Energy1Edit->Text.IsEmpty() ? E1 : Energy1Edit->Text + keV) + L" energy  ";
        KChan1Edit->Hint = KCh1Label->Hint;
        KCh2Label->Hint = Str + (Energy2Edit->Text.IsEmpty() ? E2 : Energy2Edit->Text + keV) + L" energy  ";
        KChan2Edit->Hint = KCh2Label->Hint;

        CsCh1Label->Hint = Str + (Energy1Edit->Text.IsEmpty() ? E1 : Energy1Edit->Text + keV) + L" energy  ";
        CsChan1Edit->Hint = CsCh1Label->Hint;
        CsCh2Label->Hint = Str + (Energy2Edit->Text.IsEmpty() ? E2 : Energy2Edit->Text + keV) + L" energy  ";
        CsChan2Edit->Hint = CsCh2Label->Hint;

        ChangeFinalSpcScaleAction->Caption = L"Logarithmic scale";
        SmoothFInalSpectrumAction->Caption = L"Smoothed";
    }
    else
    {
        throw Exception(L"Unknown language.");
    }

    BrowseInfo.lpszTitle = DirSelectionString.c_str();

    /*ThLabel->Left = (ThInfoPanel->Width - ThLabel->Width) / 2;
    RaLabel->Left = (RaInfoPanel->Width - RaLabel->Width) / 2;
    KLabel->Left = (KInfoPanel->Width - KLabel->Width) / 2;
    CsLabel->Left = (CsInfoPanel->Width - CsLabel->Width) / 2;

    ThSmpLabel->Left = (ThInfoPanel->Width - ThSmpLabel->Width) / 2;
    RaSmpLabel->Left = (RaInfoPanel->Width - RaSmpLabel->Width) / 2;
    KSmpLabel->Left = (KInfoPanel->Width - KSmpLabel->Width) / 2;
    CsSmpLabel->Left = (CsInfoPanel->Width - CsSmpLabel->Width) / 2;

    SmpLabel->Left = (SampleInfoPanel->Width - SmpLabel->Width) / 2;*/
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::LanguageActionExecute(TObject *Sender)
{
    if (LanguageAction->Tag == 0)
    {
        LanguageAction->Tag = 1;
    }
    else if (LanguageAction->Tag == 1)
    {
        LanguageAction->Tag = 0;
    }
    LangID = LanguageAction->Tag;
    ChangeUILanguage();
    TSpectrum::SetLanguage();
    ShiftingForm->ChangeUILanguage();
    if (BatchProcessingResultsForm != nullptr)
    {
        BatchProcessingResultsForm->ChangeUILanguage();
    }
    std::unique_ptr<TIniFile> SettingsFile(new TIniFile(L".\\Settings.ini"));
    SettingsFile->WriteInteger(L"UILanguage", L"LangID", LanguageAction->Tag);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ThCoeffCalcLabelClick(TObject *Sender)
{
    const int P = ThSnSe1->Text.Pos(L".");
    String Value = ThSnSe1->Text;
    if (P > 0)
    {
        Value = ThSnSe1->Text.SubString(1, P + 3);
    }
    ThSnSe2->Text = Value;
    ThSnSe2->SetFocus();
    ThSnSe2->SelectAll();
    OnParamChange(ThSnSe2);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::RaCoeffCalcLabelClick(TObject *Sender)
{
    const int P = RaSnSe1->Text.Pos(L".");
    String Value = RaSnSe1->Text;
    if (P > 0)
    {
        Value = RaSnSe1->Text.SubString(1, P + 3);
    }
    RaSnSe2->Text = Value;
    RaSnSe2->SetFocus();
    RaSnSe2->SelectAll();
    OnParamChange(RaSnSe2);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::KCoeffCalcLabelClick(TObject *Sender)
{
    const int P = KSnSe1->Text.Pos(L".");
    String Value = KSnSe1->Text;
    if (P > 0)
    {
        Value = KSnSe1->Text.SubString(1, P + 3);
    }
    KSnSe2->Text = Value;
    KSnSe2->SetFocus();
    KSnSe2->SelectAll();
    OnParamChange(KSnSe2);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::CsCoeffCalcLabelClick(TObject *Sender)
{
    const int P = CsSnSe1->Text.Pos(L".");
    String Value = CsSnSe1->Text;
    if (P > 0)
    {
        Value = CsSnSe1->Text.SubString(1, P + 3);
    }
    CsSnSe2->Text = Value;
    CsSnSe2->SetFocus();
    CsSnSe2->SelectAll();
    OnParamChange(CsSnSe2);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::OnKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if (Key == L',')
    {
        Key = L'.';
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::OnEditUpButtonClick(TObject *Sender)
{
    TComponent *C = dynamic_cast<TComponent*>(Sender);
    TEdit *Edit = reinterpret_cast<TEdit*>(C->Tag);
    if (Trim(Edit->Text).IsEmpty())
    {
        return;
    }
    double Value = Sysutils::StrToFloatDef(Edit->Text, 0);
    Value += 0.001;
    if (Value < 0)
    {
        Value = 0;
    }
    Edit->Text = Value;
    try
    {
        if (SampleSpc.IsValid() && BkgSpc.IsValid() && ThSpc.IsValid() &&
            RaSpc.IsValid() && KSpc.IsValid() && CsSpc.IsValid())
        {
            DecomposeSampleSpectrum();
        }
    }
    catch (const Exception &E)
    {
        LOGEXCEPTION(E);
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::OnEditDownButtonClick(TObject *Sender)
{
    TComponent *C = dynamic_cast<TComponent*>(Sender);
    TEdit *Edit = reinterpret_cast<TEdit*>(C->Tag);
    if (Trim(Edit->Text).IsEmpty())
    {
        return;
    }
    double Value = Sysutils::StrToFloatDef(Edit->Text, 0);
    Value -= 0.001;
    if (Value < 0)
    {
        Value = 0;
    }
    Edit->Text = Value;
    try
    {
        if (SampleSpc.IsValid() && BkgSpc.IsValid() && ThSpc.IsValid() &&
            RaSpc.IsValid() && KSpc.IsValid() && CsSpc.IsValid())
        {
            DecomposeSampleSpectrum();
        }
    }
    catch (const Exception &E)
    {
        LOGEXCEPTION(E);
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SampleChartDblClick(TObject *Sender)
{
    if (!SampleSpc.IsValid() || SampleSpectrum->Count() == 0)
    {
        return;
    }
    ShiftingForm->SaveSpectrum2->OnClick = ShiftingForm->SaveSpectrum2Click;
    ShiftingForm->SaveSpectrum2->DropdownMenu = 0;
    ShiftingForm->Load(
        ThSpc.IsValid() ? ThSpc : Ths[VI],
        OrigSampleSpc,
        Sysutils::StrToFloatDef(Energy1Edit->Text, 0),
        Sysutils::StrToFloatDef(Energy2Edit->Text, 0),
        Sysutils::StrToFloatDef(ThChan1Edit->Text, 0),
        Sysutils::StrToFloatDef(ThChan2Edit->Text, 0),
        Sysutils::StrToFloatDef(SmpChan1Edit->Text, 0),
        Sysutils::StrToFloatDef(SmpChan2Edit->Text, 0));
    ShiftingForm->Show();
}
//---------------------------------------------------------------------------
void TMainForm::SetSampleSpectrum(const TSpectrum &ShiftedSpc, const String &Ch1Str, const String &Ch2Str)
{
    try
    {
        SampleSpc = ShiftedSpc;
        SmpChan1Edit->OnChange = 0;
        SmpChan2Edit->OnChange = 0;
        SmpChan1Edit->Text = Ch1Str;
        SmpChan2Edit->Text = Ch2Str;
        SmpChan1Edit->OnChange = OnShiftingDataChange;
        SmpChan2Edit->OnChange = OnShiftingDataChange;
        if (SampleSpc.IsValid() && BkgSpc.IsValid() && ThSpc.IsValid() &&
            RaSpc.IsValid() && KSpc.IsValid() && CsSpc.IsValid())
        {
            DecomposeSampleSpectrum();
        }
    }
    catch (const Exception &E)
    {
        LOGEXCEPTION(E);
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::BeActLabelClick(TObject *Sender)
{
    const int __LangID = LangID;

    BeActivityPerKgOrSq->Tag = !BeActivityPerKgOrSq->Tag;
    if (BeActivityPerKgOrSq->Tag)
    {
        if (__LangID == 0)
        {
            BeActLabel->Caption = L"Aktivligi (Bk/kg):";
            BeErrorLabel->Caption = L"Xatolik (Bk/kg):";
        }
        else
        {
            BeActLabel->Caption = L"Activity (Bq/kg):";
            BeErrorLabel->Caption = L"Error (Bq/kg):";
        }
        BeActivityPerKgOrSq->Text = BeActivityPerKilogram;
        SampleBeError->Text = BeErrorPerKilogram;
    }
    else
    {
        if (__LangID == 0)
        {
            BeActLabel->Caption = L"Aktivligi (Bk/m^2):";
            BeErrorLabel->Caption = L"Xatolik (Bk/m^2):";
        }
        else
        {
            BeActLabel->Caption = L"Activity (Bq/m^2):";
            BeErrorLabel->Caption = L"Error (Bq/m^2):";
        }
        BeActivityPerKgOrSq->Text = BeActivityPerSquare;
        SampleBeError->Text = BeErrorPerSquare;
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ChangeFinalSpcScaleActionExecute(TObject *Sender)
{
    if (!FinalSpcChart->LeftAxis->Logarithmic)
    {
        FinalSpcChart->LeftAxis->Minimum = 0;
        FinalSpcChart->LeftAxis->Increment = 0;
    }
    FinalSpcChart->LeftAxis->Logarithmic = !FinalSpcChart->LeftAxis->Logarithmic;
    if (!FinalSpcChart->LeftAxis->Logarithmic)
    {
        FinalSpcChart->LeftAxis->Minimum = -300;
        FinalSpcChart->LeftAxis->Increment = 300;
    }
    ChangeFinalSpcScaleAction->Checked = FinalSpcChart->LeftAxis->Logarithmic;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ChangeFinalSpcScaleActionUpdate(TObject *Sender)
{
    ChangeFinalSpcScaleAction->Enabled = FinalSpectrum->Count() > 0;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SubtractBkgActionExecute(TObject *Sender)
{
    SubtractBkgAction->Checked = !SubtractBkgAction->Checked;
    if (SampleSpc.IsValid() && BkgSpc.IsValid() && ThSpc.IsValid() &&
        RaSpc.IsValid() && KSpc.IsValid() && CsSpc.IsValid())
    {
        DecomposeSampleSpectrum();
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SubtractBkgActionUpdate(TObject *Sender)
{
    SubtractBkgAction->Enabled = FinalSpectrum->Count() > 0;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SmoothFInalSpectrumActionExecute(TObject *Sender)
{
    SmoothFInalSpectrumAction->Checked = !SmoothFInalSpectrumAction->Checked;
    if (SampleSpc.IsValid() && BkgSpc.IsValid() && ThSpc.IsValid() &&
        RaSpc.IsValid() && KSpc.IsValid() && CsSpc.IsValid())
    {
        DecomposeSampleSpectrum();
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SmoothFInalSpectrumActionUpdate(TObject *Sender)
{
    SmoothFInalSpectrumAction->Enabled = FinalSpectrum->Count() > 0;
}
//---------------------------------------------------------------------------

