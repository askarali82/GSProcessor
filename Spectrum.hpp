#ifndef SpectrumH
#define SpectrumH

#include <vector>
#include <memory>
#include <cmath>
#include <map>
#include <limits>
#include <atomic>
#include <Vcl.Forms.hpp>
#include <System.hpp>
#include <System.Math.hpp>
#include <System.IniFiles.hpp>

// Language ID
// 0 => Uzbek
// 1 => English
extern std::atomic<int> LangID;
//
//
//

struct TPeak
{
    size_t LeftPCh = 0;
    double LeftPEn = 0;

    size_t CenterCh = 0;
    double CenterEn = 0;

    size_t RightPCh = 0;
    double RightPEn = 0;

    String ToString() const
    {
        return
            String(LeftPCh)  + L"->" + Sysutils::FloatToStrF(LeftPEn, ffFixed, 15, 2)  + L"; " +
            String(CenterCh) + L"->" + Sysutils::FloatToStrF(CenterEn, ffFixed, 15, 2) + L"; " +
            String(RightPCh) + L"->" + Sysutils::FloatToStrF(RightPEn, ffFixed, 15, 2);
    }
};

class TSpectrum
{
private:
    static String FileExistenceError;
    static String ErrorHeader;
    static String ErrorBoxTitle;
    static String MeasurementDurationError;
    static String SampleMassError;
    static String SampleVolumeError;
    static String SampleMassUnitError;
    static String SampleVolumeUnitError;
    static String ChannelCountError;
    static String EnergyCalibrationError;
    static String NoSpectrumError;
    static String EnergyChannelValueError;
    static String AddingSpectraChannelsError;
    static String AddingSpectraEnergyCalibrationError;
    static String SubtractingSpectraChannelsError;
    static String SubtractingSpectraEnergyCalibrationError;
    static String SubtractingSpectrumDurationError;
    static String SubtractedSpectrumDurationError;
    static String ShiftingRefSampleChannelNumbersError;
    static String ShiftingSampleChannelNumbersError;
    static String ShiftingEnergyValuesError;
    static String ShiftingChannelsCountError;

public:
    // ******************* Data members *******************
    mutable String ErrorMessage;

    // Sample
    double Duration = 0;
    double Weight = 0;
    double Volume = 0;
    double DensityInGramPerLitre = 0;
    String WeightUnit = 0;
    String VolumeUnit = 0;

    // Energy calibration
    double Channel1 = 0;
    double Channel2 = 0;
    double Energy1 = 0;
    double Energy2 = 0;
    double K = 0;
    double B = 0;

    // Spectrum
    int ChannelCount = 0;
    String BkgFileName;
    std::vector<double> Energies;
    std::vector<double> Counts;

    // Extra fields
    String ExtraStringData;
    double ExtraFloatData = 0;


    // ******************* Member functions *******************

    static void SetLanguage()
    {
        FileExistenceError = L" fayli mavjud emas.";
        ErrorHeader = L"Quyidagi xatolik yuz berdi:\r\n\r\n";
        ErrorBoxTitle = L"Xato";
        MeasurementDurationError = L"O'lchash davomiyligi noma'lum.";
        SampleMassError = L"Namuna massasi noma'lum.";
        SampleVolumeError = L"Namuna hajmi noma'lum.";
        SampleMassUnitError = L"Namuna massasining o'lchov birligi noma'lum.";
        SampleVolumeUnitError = L"Namuna hajmining o'lchov birligi noma'lum.";
        ChannelCountError = L"Kanallar soni noma'lum.";
        EnergyCalibrationError = L"Energiya bo'yicha kalibrovka bajarilmagan.";
        NoSpectrumError = L"Faylda spektr mavjud emas.";
        EnergyChannelValueError = L"Kanal va energiya qiymatlari 0 dan katta bo'lishi shart.";
        AddingSpectraChannelsError = L"Qo'shiluvchi va qo'shuvchi spektrlarda kanallar soni teng emas.";
        AddingSpectraEnergyCalibrationError = L"Qo'shiluvchi yoki qo'shuvchi spektrda energiya bo'yicha kalibrovka noto'g'ri.";
        SubtractingSpectraChannelsError = L"Ayriluvchi va ayiruvchi spektrlarda kanallar soni teng emas.";
        SubtractingSpectraEnergyCalibrationError = L"Ayriluvchi yoki ayiruvchi spektrda energiya bo'yicha kalibrovka noto'g'ri.";
        SubtractedSpectrumDurationError = L"Ayriluvchi spektrning o'lchash davomiyligi noto'g'ri.";
        SubtractingSpectrumDurationError = L"Ayiruvchi spektrning o'lchash davomiyligi noto'g'ri.";
        ShiftingRefSampleChannelNumbersError = L"Siljitish: etalon namuna spektri uchun kanallar qiymatlari noto'g'ri.";
        ShiftingSampleChannelNumbersError = L"Siljitish: siljitiladigan spektr uchun kanallar qiymatlari noto'g'ri.";
        ShiftingEnergyValuesError = L"Siljitish: energiya qiymatlari noto'g'ri.";
        ShiftingChannelsCountError = L"Siljitish: siljitiladigan spektrda kanallar soni noma'lum.";

        if (LangID == 1)
        {
            FileExistenceError = L" doesn't exist.";
            ErrorHeader = L"The following error occurred:\r\n\r\n";
            ErrorBoxTitle = L"Error";
            MeasurementDurationError = L"Measurement duration is unknown.";
            SampleMassError = L"The sample mass is unknown.";
            SampleVolumeError = L"The sample volume is unknown.";
            SampleMassUnitError = L"The unit of measurement of the sample mass is unknown.";
            SampleVolumeUnitError = L"The unit of measurement of the sample volume is unknown.";
            ChannelCountError = L"The count of channels is unknown.";
            EnergyCalibrationError = L"Energy calibration not performed.";
            NoSpectrumError = L"The file doesn't contain a valid spectrum.";
            EnergyChannelValueError = L"The value of channel number and energy must be greater than 0.";
            AddingSpectraChannelsError = L"The count of channels in both spectra (adding and being added) is not the same.";
            AddingSpectraEnergyCalibrationError = L"Energy calibration in one or both of spectra (adding and/or being added) is not correct.";
            SubtractingSpectraChannelsError = L"The count of channels in both spectra (subtracting and being subtracted) is not the same.";
            SubtractingSpectraEnergyCalibrationError = L"Energy calibration in one or both of spectra (subtracting and/or being subtracted) is not correct.";
            SubtractedSpectrumDurationError = L"Measurement duration in spectrum being subtracted is not correct.";
            SubtractingSpectrumDurationError = L"Measurement duration in subtracting spectrum is not correct.";
            ShiftingRefSampleChannelNumbersError = L"Shifting: channel numbers in reference sample spectrum are not correct.";
            ShiftingSampleChannelNumbersError = L"Shifting: channel numbers in sample spectrum being shifted are not correct.";
            ShiftingEnergyValuesError = L"Shifting: energy values are not correct.";
            ShiftingChannelsCountError = L"Shifting: count of channels in spectrum being shifted is unknown.";
        }
    }

    TSpectrum()
    {
        if (FileExistenceError.IsEmpty())
        {
            SetLanguage();
        }
    }

    virtual ~TSpectrum()
    {
    }

    TSpectrum(const TSpectrum &Other) = default;
    TSpectrum(TSpectrum &&Other) = default;
    TSpectrum & operator = (const TSpectrum &Other) = default;
    TSpectrum & operator = (TSpectrum &&Other) = default;

    static void CheckError(const bool OK, const String &Message = L"")
    {
        if (!OK)
        {
            throw Exception(Message);
        }
    }

    bool IsValid() const;

    bool LoadFromFile(const String &FileName, const bool ShowExceptionMsg = true);

    double CalculateCountByEnergyRange(const double Start, const double End) const;

    double CalculateTotalCount() const;

    bool WriteCountsToTextFile(
        const String &FileName, const bool IncludeChannels, const bool IncludeEnergies) const;

    bool WriteCountsToString(String &Str, const bool IncludeChannels, const bool IncludeEnergies) const;

    bool Add(const TSpectrum &Spc, TSpectrum &ResultSpc, const bool ByEnergy = false) const;

    bool Subtract(
        const TSpectrum &Spc, TSpectrum &ResultSpc,
        const bool ByEnergy = false, const bool ByDuration = false) const;

    TSpectrum Multiply(const double To) const;

    bool CorrectToCalibration(TSpectrum &SpcToCorrect) const;

    void Recalibrate(
        const double Ch1, const double En1, const double Ch2,
        const double En2, const bool ShowExceptionMsg = true);

    bool Shift(
        const double SrcCh1,
        const double SrcCh2,
        const double SmpCh1,
        const double SmpCh2,
        const double En1,
        const double En2,
        TSpectrum &ResultSpc) const;

    TSpectrum Smooth(size_t m) const;

    TSpectrum Smooth() const;

    TSpectrum FirstDerivative() const;

    std::vector<TPeak> FindPeaks(const double WidthThreshold) const;
};
//---------------------------------------------------------------------------
String TSpectrum::FileExistenceError;
String TSpectrum::ErrorHeader;
String TSpectrum::ErrorBoxTitle;
String TSpectrum::MeasurementDurationError;
String TSpectrum::SampleMassError;
String TSpectrum::SampleVolumeError;
String TSpectrum::SampleMassUnitError;
String TSpectrum::SampleVolumeUnitError;
String TSpectrum::ChannelCountError;
String TSpectrum::EnergyCalibrationError;
String TSpectrum::NoSpectrumError;
String TSpectrum::EnergyChannelValueError;
String TSpectrum::AddingSpectraChannelsError;
String TSpectrum::AddingSpectraEnergyCalibrationError;
String TSpectrum::SubtractingSpectraChannelsError;
String TSpectrum::SubtractingSpectraEnergyCalibrationError;
String TSpectrum::SubtractingSpectrumDurationError;
String TSpectrum::SubtractedSpectrumDurationError;
String TSpectrum::ShiftingRefSampleChannelNumbersError;
String TSpectrum::ShiftingSampleChannelNumbersError;
String TSpectrum::ShiftingEnergyValuesError;
String TSpectrum::ShiftingChannelsCountError;
//---------------------------------------------------------------------------
bool TSpectrum::LoadFromFile(const String &FileName, const bool ShowExceptionMsg)
{
    try
    {
        ErrorMessage = L"";
        CheckError(Sysutils::FileExists(FileName), L"\"" + FileName + L"\"" + FileExistenceError);

        std::unique_ptr<TMemIniFile> Lines(new TMemIniFile(FileName));
        Lines->CaseSensitive = false;

        Duration = wcstod(Lines->ReadString(L"Exposition", L"Live", L"0").c_str(), nullptr);
        CheckError(Duration > 0, MeasurementDurationError);

        Weight = wcstod(Lines->ReadString(L"Sample", L"Weight", L"0").c_str(), nullptr);
        CheckError(Weight > 0, SampleMassError);

        Volume = wcstod(Lines->ReadString(L"Sample", L"Volume", L"0").c_str(), nullptr);
        CheckError(Volume > 0, SampleVolumeError);

        WeightUnit = Lines->ReadString(L"Sample", L"Unit_weight", L"");
        CheckError(SameText(WeightUnit, L"g") || SameText(WeightUnit, L"kg"), SampleMassUnitError);

        VolumeUnit = Lines->ReadString(L"Sample", L"Unit_volume", L"");
        CheckError(SameText(VolumeUnit, L"l") || SameText(VolumeUnit, L"ml"), SampleVolumeUnitError);

        if (SameText(VolumeUnit, L"ml"))
        {
            Volume /= 1000.0;
        }

        DensityInGramPerLitre = SameText(WeightUnit, L"kg") ? ((Weight * 1000) / Volume) : (Weight / Volume);

        ChannelCount = Lines->ReadInteger(L"Channel_count", L"N", 0);
        CheckError(ChannelCount == 1024 || ChannelCount == 4096, ChannelCountError);

        Channel1 = wcstod(Lines->ReadString(L"Energy_calibration", L"Channel1", L"0").c_str(), nullptr) - 1;
        Channel2 = wcstod(Lines->ReadString(L"Energy_calibration", L"Channel2", L"0").c_str(), nullptr) - 1;
        Energy1 = wcstod(Lines->ReadString(L"Energy_calibration", L"Energy1", L"0").c_str(), nullptr);
        Energy2 = wcstod(Lines->ReadString(L"Energy_calibration", L"Energy2", L"0").c_str(), nullptr);
        CheckError(Channel1 > 0 && Channel2 > 0 && Energy1 > 0 && Energy2 > 0, EnergyCalibrationError);

        BkgFileName = Lines->ReadString(L"Filenames", L"Bkg", L"");

        if (Lines->SectionExists(L"BEGIN"))
        {
            Lines.reset();
            std::unique_ptr<TMemoryStream> BinaryData(new TMemoryStream());
            BinaryData->LoadFromFile(FileName);
            static const AnsiString BEGIN_CRLF = "[BEGIN]\r\n";
            static const AnsiString BEGIN_LF   = "[BEGIN]\n";
            static const AnsiString BEGIN_CR   = "[BEGIN]\r";
            const char *Pos = (const char*)BinaryData->Memory;
            BinaryData->Position = 0;
            while ((Pos - (const char*)BinaryData->Memory) < BinaryData->Size)
            {
                bool Found = false;
                if (BEGIN_CRLF == AnsiString(Pos, BEGIN_CRLF.Length()))
                {
                    BinaryData->Position += BEGIN_CRLF.Length();
                    Found = true;
                }
                else if (BEGIN_LF == AnsiString(Pos, BEGIN_LF.Length()))
                {
                    BinaryData->Position += BEGIN_LF.Length();
                    Found = true;
                }
                else if (BEGIN_CR == AnsiString(Pos, BEGIN_CR.Length()))
                {
                    BinaryData->Position += BEGIN_CR.Length();
                    Found = true;
                }
                if (Found)
                {
                    Counts.resize(ChannelCount);
                    Energies.resize(ChannelCount);
                    std::vector<int> IntCounts(ChannelCount, 0);
                    char *Buffer = reinterpret_cast<char *>(IntCounts.data());
                    BinaryData->Read(Buffer, IntCounts.size() * sizeof(int));
                    for (size_t i = 0; i < IntCounts.size(); i++)
                    {
                        Counts[i] = IntCounts[i];
                    }
                    break;
                }
                Pos++;
                BinaryData->Position++;
            }
        }
        else if (Lines->SectionExists(L"SPECTRUM"))
        {
            std::unique_ptr<TStringList> Data(new TStringList());
            Lines->ReadSection(L"SPECTRUM", Data.get());
            CheckError(Data->Count == ChannelCount, NoSpectrumError);
            Counts.resize(ChannelCount);
            Energies.resize(ChannelCount);
            for (int i = 0; i < ChannelCount; i++)
            {
                Counts[i] = wcstod(Data->Strings[i].c_str(), nullptr);
            }
        }

        CheckError(Counts.size() == ChannelCount, NoSpectrumError);
        Counts[ChannelCount - 1] = Counts[ChannelCount - 2];
        K = (Energy1 - Energy2) / (Channel1 - Channel2);
        B = Energy1 - K * Channel1;
        int X = 0;
        for (auto &E : Energies)
        {
            E = K * (X++) + B;
        }

        return true;
    }
    catch (const Exception &E)
    {
        ErrorMessage = E.Message;
        if (ShowExceptionMsg)
        {
            const String &Msg = ErrorHeader + ErrorMessage;
            Application->MessageBox(Msg.c_str(), ErrorBoxTitle.c_str(), MB_OK | MB_ICONERROR);
        }
    }
    return false;
}
//---------------------------------------------------------------------------
bool TSpectrum::IsValid() const
{
    try
    {
        CheckError(Duration > 0);
        CheckError(Weight > 0);
        CheckError(Volume > 0);
        CheckError(SameText(WeightUnit, L"g") || SameText(WeightUnit, L"kg"));
        CheckError(SameText(VolumeUnit, L"l") || SameText(VolumeUnit, L"ml"));
        CheckError(Channel1 > 0 && Channel2 > 0 && Energy1 > 0 && Energy2 > 0);
        CheckError(ChannelCount == 1024 || ChannelCount == 4096);
        CheckError(Counts.size() == ChannelCount && Energies.size() == ChannelCount);
    }
    catch (Exception &)
    {
        return false;
    }
    return true;
}
//---------------------------------------------------------------------------
void TSpectrum::Recalibrate(
    const double Ch1, const double En1, const double Ch2,
    const double En2, const bool ShowExceptionMsg)
{
    try
    {
        CheckError(ChannelCount == 1024 || ChannelCount == 4096, ChannelCountError);
        CheckError(Ch1 > 0 && En1 > 0 && Ch2 > 0 && En2 > 0, EnergyChannelValueError);
        const double k = (En1 - En2) / (Ch1 - Ch2);
        const double b = En1 - k * Ch1;
        int x = 0;
        std::vector<double> Ens(ChannelCount, 0);
        for (auto &e : Ens)
        {
            e = k * (x++) + b;
        }
        Energy1 = En1;
        Energy2 = En2;
        Channel1 = Ch1;
        Channel2 = Ch2;
        K = k;
        B = b;
        Energies = Ens;
    }
    catch (const Exception &E)
    {
        ErrorMessage = E.Message;
        if (ShowExceptionMsg)
        {
            const String &Msg = ErrorHeader + ErrorMessage;
            Application->MessageBox(Msg.c_str(), ErrorBoxTitle.c_str(), MB_OK | MB_ICONERROR);
        }
    }
}
//---------------------------------------------------------------------------
double TSpectrum::CalculateCountByEnergyRange(const double Start, const double End) const
{
    double Result = 0;
    for (size_t i = 0; i < Energies.size(); i++)
    {
        const auto &E = Energies[i];
        if (E >= Start && E <= End && i < Counts.size())
        {
            Result += Counts[i];
        }
    }
    return Result;
}
//---------------------------------------------------------------------------
double TSpectrum::CalculateTotalCount() const
{
    double Result = 0;
    for (auto Count : Counts)
    {
        Result += Count;
    }
    return Result;
}
//---------------------------------------------------------------------------
bool TSpectrum::WriteCountsToTextFile(
    const String &FileName, const bool IncludeChannels, const bool IncludeEnergies) const
{
    try
    {
        ErrorMessage = L"";
        std::unique_ptr<TStringList> List(new TStringList());
        for (size_t i = 0; i < Counts.size(); i++)
        {
            String Line;
            if (IncludeChannels)
            {
                Line = i;
            }
            if (IncludeEnergies)
            {
                const String &En = Sysutils::FloatToStrF(Energies[i], ffFixed, 15, 2);
                Line = Line == L"" ? En : (Line + L"    " + En);
            }
            const String &Count = String(Math::Ceil(Counts[i]));
            Line = Line == L"" ? Count : (Line + L"    " + Count);
            List->Add(Line);
        }
        List->SaveToFile(FileName);
        return true;
    }
    catch (const Exception &E)
    {
        ErrorMessage = E.Message;
    }
    return false;
}
//---------------------------------------------------------------------------
bool TSpectrum::WriteCountsToString(
    String &Str, const bool IncludeChannels, const bool IncludeEnergies) const
{
    try
    {
        ErrorMessage = L"";
        Str = L"";
        for (size_t i = 0; i < Counts.size(); i++)
        {
            String Line;
            if (IncludeChannels)
            {
                Line = i;
            }
            if (IncludeEnergies)
            {
                const String &En = Sysutils::FloatToStrF(Energies[i], ffFixed, 15, 2);
                Line = Line == L"" ? En : (Line + L"    " + En);
            }
            const String &Count = String(Math::Ceil(Counts[i]));
            Line = Line == L"" ? Count : (Line + L"    " + Count);
            Str = Str == L"" ? Line : (Str + L"\r\n" + Line);
        }
        return true;
    }
    catch (const Exception &E)
    {
        ErrorMessage = E.Message;
    }
    return false;
}
//---------------------------------------------------------------------------
bool TSpectrum::Add(const TSpectrum &Spc, TSpectrum &ResultSpc, const bool ByEnergy) const
{
    bool Result = false;
    ErrorMessage = L"";
    try
    {
        TSpectrum NewSpc = *this;
        NewSpc.Counts.clear();
        CheckError(Counts.size() == Spc.Counts.size(), AddingSpectraChannelsError);
        if (ByEnergy)
        {
            CheckError(Energies.size() == Counts.size() && Energies.size() == Spc.Energies.size() && K != 0 && Spc.K != 0,
                AddingSpectraEnergyCalibrationError);
        }
        NewSpc.Counts.resize(Counts.size());
        for (size_t i = 0; i < Counts.size(); i++)
        {
            int X = (int)i;
            if (ByEnergy)
            {
                X = Math::Ceil((Energies[i] - Spc.B) / Spc.K);
                if (X < 0)
                {
                    X = 0;
                }
                else if (X >= Counts.size())
                {
                    X = Counts.size() - 1;
                }
            }
            NewSpc.Counts[i] = Counts[i] + Spc.Counts[X];
        }
        ResultSpc = NewSpc;
        Result = true;
    }
    catch (const Exception &E)
    {
        ErrorMessage = E.Message;
    }
    return Result;
}
//---------------------------------------------------------------------------
bool TSpectrum::Subtract(
    const TSpectrum &Spc, TSpectrum &ResultSpc, const bool ByEnergy, const bool ByDuration) const
{
    bool Result = false;
    ErrorMessage = L"";
    try
    {
        TSpectrum NewSpc = *this;
        NewSpc.Counts.clear();
        CheckError(Counts.size() == Spc.Counts.size(), SubtractingSpectraChannelsError);
        if (ByEnergy)
        {
            CheckError(Energies.size() == Counts.size() && Energies.size() == Spc.Energies.size() && K != 0 && Spc.K != 0,
                AddingSpectraEnergyCalibrationError);
        }
        if (ByDuration)
        {
            CheckError(Duration > 0, SubtractedSpectrumDurationError);
            CheckError(Spc.Duration > 0, SubtractingSpectrumDurationError);
        }
        NewSpc.Counts.resize(Counts.size());
        for (size_t i = 0; i < Counts.size(); i++)
        {
            int X = (int)i;
            if (ByEnergy)
            {
                X = Math::Ceil((Energies[i] - Spc.B) / Spc.K);
                if (X < 0)
                {
                    X = 0;
                }
                else if (X >= Counts.size())
                {
                    X = Counts.size() - 1;
                }
            }
            NewSpc.Counts[i] =
                ByDuration ? (Counts[i] - Spc.Counts[X] * (Duration / Spc.Duration)) : (Counts[i] - Spc.Counts[X]);
        }
        ResultSpc = NewSpc;
        Result = true;
    }
    catch (const Exception &E)
    {
        ErrorMessage = E.Message;
    }
    return Result;
}
//---------------------------------------------------------------------------
TSpectrum TSpectrum::Multiply(const double To) const
{
    TSpectrum Result;
    ErrorMessage = L"";
    try
    {
        Result = *this;
        for (auto &Count : Result.Counts)
        {
            Count *= To;
        }
    }
    catch (const Exception &E)
    {
        ErrorMessage = E.Message;
    }
    return Result;
}
//---------------------------------------------------------------------------
bool TSpectrum::CorrectToCalibration(TSpectrum &Spc) const
{
    bool Result = false;
    ErrorMessage = L"";
    try
    {
        CheckError(Counts.size() == Spc.Counts.size(),
            L"To'g'irlovchi va to'g'irlanuvchi spektrlarda kanallar soni teng emas.");
        CheckError(Energies.size() == Counts.size() && Energies.size() == Spc.Energies.size() && K != 0 && Spc.K != 0,
            L"To'g'irlovchi yoki to'g'irlanuvchi spektrda energiya bo'yicha kalibrovka noto'g'ri.");
        std::vector<double> TMPCounts(Counts.size(), 0);
        for (size_t i = 0; i < Counts.size(); i++)
        {
            int X = Math::Ceil((Energies[i] - Spc.B) / Spc.K);
            if (X < 0)
            {
                X = 0;
            }
            else if (X >= Counts.size())
            {
                X = Counts.size() - 1;
            }
            TMPCounts[i] = Spc.Counts[X];
        }
        Spc.Channel1 = Channel1;
        Spc.Channel2 = Channel2;
        Spc.Energy1 = Energy1;
        Spc.Energy2 = Energy2;
        Spc.B = B;
        Spc.K = K;
        Spc.Energies = Energies;
        Spc.Counts = TMPCounts;
        Result = true;
    }
    catch (const Exception &E)
    {
        ErrorMessage = E.Message;
    }
    return Result;
}
//---------------------------------------------------------------------------
bool TSpectrum::Shift(const double SrcCh1, const double SrcCh2, const double SmpCh1,
    const double SmpCh2, const double En1, const double En2, TSpectrum &ResultSpc) const
{
    bool Result = false;
    ErrorMessage = L"";
    try
    {
        CheckError(SrcCh1 > 0 && SrcCh2 > SrcCh1, ShiftingRefSampleChannelNumbersError);
        CheckError(SmpCh1 > 0 && SmpCh2 > SmpCh1, ShiftingSampleChannelNumbersError);
        CheckError(En1 > 0 && En2 > En1, ShiftingEnergyValuesError);
        CheckError(Counts.size() == 1024 || Counts.size() == 4096, ShiftingChannelsCountError);
        ResultSpc = *this;
        const double SrcK = (En2 - En1) / (SrcCh2 - SrcCh1);
        const double SmpK = (En2 - En1) / (SmpCh2 - SmpCh1);
        const double SrcB = En1 - SrcK * SrcCh1;
        const double SmpB = En1 - SmpK * SmpCh1;

        for (size_t i = 0; i < Counts.size(); i++)
        {
            ResultSpc.Counts[i] = 0;
            const double SrcCal = SrcK * i + SrcB;
            int X = Math::Ceil((SrcCal - SmpB) / SmpK);
            if (X < 0)
            {
                X = 0;
            }
            else if (X >= Counts.size())
            {
                X = Counts.size() - 2;
            }
            int I = 0;
            while (I < 1000)
            {
                const double d = double(I) / 1000.0;
                const int En = Math::Ceil(1000 * (SmpK * (X + d) + SmpB));
                ResultSpc.Counts[i] = Counts[X] + Math::Ceil(d * (Counts[X + 1] - Counts[X]));
                if (En > Math::Ceil(1000 * SrcCal))
                {
                    break;
                }
                I++;
            }
        }
        ResultSpc.Channel1 = SrcCh1;
        ResultSpc.Channel2 = SrcCh2;
        ResultSpc.Energy1 = En1;
        ResultSpc.Energy2 = En2;
        ResultSpc.K = SrcK;
        ResultSpc.B = SrcB;
        int X = 0;
        for (auto &E : ResultSpc.Energies)
        {
            E = ResultSpc.K * (X++) + ResultSpc.B;
        }
        Result = true;
    }
    catch (const Exception &E)
    {
        ErrorMessage = E.Message;
    }
    return Result;
}
//---------------------------------------------------------------------------
TSpectrum TSpectrum::Smooth(size_t m) const
{
    try
    {
        ErrorMessage = L"";
        auto Result = *this;
        if ((m % 2) == 0)
        {
            m++;
        }
        const size_t k = m / 2;
        for (size_t i = k; i < Result.Counts.size(); i++)
        {
            double Sum = 0;
            for (size_t j = i - k; j <= (i + k); j++)
            {
                if (j < Counts.size())
                {
                    Sum += Counts[j];
                }
            }
            Result.Counts[i] = Sum / m;
        }
        return Result;
    }
    catch (const Exception &E)
    {
        ErrorMessage = E.Message;
    }

    return *this;
}
//---------------------------------------------------------------------------
TSpectrum TSpectrum::Smooth() const
{
    try
    {
        ErrorMessage = L"";
        auto Result = *this;
        for (size_t i = 2; i < Result.Counts.size(); i++)
        {
            Result.Counts[i] =
                (Counts[i - 2] + 2 * Counts[i - 1] + 3 * Counts[i] + 2 * Counts[i + 1] + Counts[i + 2]) / 9.0;
        }
        return Result;
    }
    catch (const Exception &E)
    {
        ErrorMessage = E.Message;
    }
    return *this;
}
//---------------------------------------------------------------------------
TSpectrum TSpectrum::FirstDerivative() const
{
    try
    {
        ErrorMessage = L"";
        auto Result = *this;
        for (size_t i = 0; i < Counts.size() - 1; i++)
        {
            Result.Counts[i] = Math::Ceil(Counts[i + 1] - Counts[i]);
        }
        return Result;
    }
    catch (const Exception &E)
    {
        ErrorMessage = E.Message;
    }
    return *this;
}
//---------------------------------------------------------------------------
std::vector<TPeak> TSpectrum::FindPeaks(const double WidthThreshold) const
{
    std::vector<TPeak> Result;
    try
    {
        ErrorMessage = L"";
        TSpectrum Spc = *this;
        for (int i = 0; i < 16; i++)
        {
            Spc = Spc.Smooth(3);
        }
        Spc = Spc.FirstDerivative();
        bool N_Current = false;
        for (size_t i = 0; i < Spc.Counts.size(); i++)
        {
            if (Spc.Counts[i] < 0)
            {
                if (!N_Current)
                {
                    N_Current = true;
                    TPeak P;
                    P.CenterCh = i;
                    P.CenterEn = Spc.Energies[i];
                    for (int j = int(i - 1); j >= 0; j--)
                    {
                        if (Spc.Counts[j] < 0)
                        {
                            P.LeftPCh = j;
                            P.LeftPEn = Spc.Energies[j];
                            break;
                        }
                    }
                    for (size_t j = i + 1; j < Spc.Counts.size(); j++)
                    {
                        if (Spc.Counts[j] >= 0)
                        {
                            P.RightPCh = j;
                            P.RightPEn = Spc.Energies[j];
                            break;
                        }
                    }
                    const double DW = WidthThreshold / 2.0;
                    if (P.RightPEn > 0 && P.LeftPEn > 0 && (P.RightPEn - P.LeftPEn) > WidthThreshold &&
                        (P.CenterEn - P.LeftPEn) > DW && (P.RightPEn - P.CenterEn) > DW)
                    {
                        Result.push_back(P);
                    }
                }
            }
            else if (N_Current)
            {
                N_Current = false;
            }
        }
    }
    catch (const Exception &E)
    {
        ErrorMessage = E.Message;
    }
    return Result;
}

#endif
