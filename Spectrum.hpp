#ifndef SpectrumH
#define SpectrumH

#include <vector>
#include <memory>
#include <cmath>
#include <map>
#include <array>
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
    static String SampleDensityError;
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

    String ReadString(const String &Section, const String &Ident, const String &DefaultValue = L"") const;
    void WriteString(const String &Section, const String &Ident, const String &Value);
    bool InvertMatrix3x3(const double Matrix[3][3], double Inverse[3][3]) const;

public:
    enum TCalibrationType {Linear, Quadratic};


    // ******************* Data members *******************
    mutable String ErrorMessage;

    // Sample
    double Duration = 0;
    double DurationReal = 0;
    double Weight = 0;
    double Volume = 0;
    double DensityInGramPerLitre = 0;
    String WeightUnit = 0;
    String VolumeUnit = 0;

    // Energy calibration
    TCalibrationType CalibrationType = Linear;
    double Channel1 = 0;
    double Channel2 = 0;
    double Channel3 = 0;
    double Channel4 = 0;
    double Channel5 = 0;
    double Energy1 = 0;
    double Energy2 = 0;
    double Energy3 = 0;
    double Energy4 = 0;
    double Energy5 = 0;
    double A = 0;
    double B = 0;
    double C = 0;
    int CalibrationPoints = 0;

    // Spectrum
    int ChannelCount = 0;
    String BkgFileName;
    std::vector<double> Energies;
    std::vector<double> Counts;

    // Extra fields
    String ExtraStringData;
    double ExtraFloatData = 0;

    // Raw Data
    std::unique_ptr<TStringList> StringPart;
    std::unique_ptr<TMemoryStream> BinaryPart;


    // ******************* Member functions *******************
    static double EnergyToChannel(const double e, const double a, const double b, const double c);

    static void SetLanguage();

    static void CheckError(const bool OK, const String &Message = L"")
    {
        if (!OK)
        {
            throw Exception(Message);
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

    TSpectrum(const TSpectrum &Other);

    TSpectrum & operator = (const TSpectrum &Other);

    void CalibrateWithQuadraticFunction();

    std::array<double, 5> GetCalPointsChannels() const
    {
        return std::array<double, 5> {Channel1, Channel2, Channel3, Channel4, Channel5};
    }

    std::array<double, 5> GetCalPointsEnergies() const
    {
        return std::array<double, 5> {Energy1, Energy2, Energy3, Energy4, Energy5};
    }

    bool IsValid() const;

    bool LoadFromFile(const String &FileName, const bool ShowExceptionMsg = true);

    double CalculateCountByEnergyRange(const double Start, const double End) const;

    double CalculateCountByChannelRange(const size_t Start, const size_t End) const;

    double CalculateNetCountByChannelRange(const size_t Start, const size_t End) const;

    std::pair<double, double> CalculateCentroidByChannelRange(const size_t Start, const size_t End) const;

    double CalculateTotalCount() const;

    bool WriteCountsToTextFile(
        const String &FileName, const bool IncludeChannels, const bool IncludeEnergies) const;

    bool WriteCountsToString(String &Str, const bool IncludeChannels, const bool IncludeEnergies) const;

    bool Add(const TSpectrum &Spc, TSpectrum &ResultSpc, const bool ByEnergy = false) const;

    bool Subtract(
        const TSpectrum &Spc, TSpectrum &ResultSpc,
        const bool ByEnergy = false, const bool ByDuration = false) const;

    TSpectrum Multiply(const double To) const;

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

    TSpectrum SavitzkyGolaySmooth(const int windowSize = 7, const int polyOrder = 2) const;

    TSpectrum FirstDerivative() const;

    double GetEnergyValueByIndex(const size_t I) const;

    double GetCountValueByIndex(const size_t I) const;
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
String TSpectrum::SampleDensityError;
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
TSpectrum::TSpectrum(const TSpectrum &Other)
{
    ErrorMessage = Other.ErrorMessage;
    Duration = Other.Duration;
    DurationReal = Other.DurationReal;
    Weight = Other.Weight;
    Volume = Other.Volume;
    DensityInGramPerLitre = Other.DensityInGramPerLitre;
    WeightUnit = Other.WeightUnit;
    VolumeUnit = Other.VolumeUnit;
    CalibrationType = Other.CalibrationType;
    Channel1 = Other.Channel1;
    Channel2 = Other.Channel2;
    Channel3 = Other.Channel3;
    Channel4 = Other.Channel4;
    Channel5 = Other.Channel5;
    Energy1 = Other.Energy1;
    Energy2 = Other.Energy2;
    Energy3 = Other.Energy3;
    Energy4 = Other.Energy4;
    Energy5 = Other.Energy5;
    A = Other.A;
    B = Other.B;
    C = Other.C;
    CalibrationPoints = Other.CalibrationPoints;
    ChannelCount = Other.ChannelCount;
    BkgFileName = Other.BkgFileName;
    Energies = Other.Energies;
    Counts = Other.Counts;
    ExtraStringData = Other.ExtraStringData;
    ExtraFloatData = Other.ExtraFloatData;
    if (Other.StringPart)
    {
        StringPart = std::make_unique<TStringList>();
        StringPart->Assign(Other.StringPart.get());
    }
    else
    {
        StringPart.reset();
    }
    if (Other.BinaryPart)
    {
        BinaryPart = std::make_unique<TMemoryStream>();
        Other.BinaryPart->Position = 0;
        BinaryPart->CopyFrom(Other.BinaryPart.get(), Other.BinaryPart->Size);
        BinaryPart->Position = 0;
    }
    else
    {
        BinaryPart.reset();
    }
}
//---------------------------------------------------------------------------
TSpectrum & TSpectrum::operator = (const TSpectrum &Other)
{
    if (this == &Other)
    {
        return *this;
    }
    ErrorMessage = Other.ErrorMessage;
    Duration = Other.Duration;
    DurationReal = Other.DurationReal;
    Weight = Other.Weight;
    Volume = Other.Volume;
    DensityInGramPerLitre = Other.DensityInGramPerLitre;
    WeightUnit = Other.WeightUnit;
    VolumeUnit = Other.VolumeUnit;
    CalibrationType = Other.CalibrationType;
    Channel1 = Other.Channel1;
    Channel2 = Other.Channel2;
    Channel3 = Other.Channel3;
    Channel4 = Other.Channel4;
    Channel5 = Other.Channel5;
    Energy1 = Other.Energy1;
    Energy2 = Other.Energy2;
    Energy3 = Other.Energy3;
    Energy4 = Other.Energy4;
    Energy5 = Other.Energy5;
    A = Other.A;
    B = Other.B;
    C = Other.C;
    CalibrationPoints = Other.CalibrationPoints;
    ChannelCount = Other.ChannelCount;
    BkgFileName = Other.BkgFileName;
    Energies = Other.Energies;
    Counts = Other.Counts;
    ExtraStringData = Other.ExtraStringData;
    ExtraFloatData = Other.ExtraFloatData;
    if (Other.StringPart)
    {
        StringPart = std::make_unique<TStringList>();
        StringPart->Assign(Other.StringPart.get());
    }
    else
    {
        StringPart.reset();
    }
    if (Other.BinaryPart)
    {
        BinaryPart = std::make_unique<TMemoryStream>();
        Other.BinaryPart->Position = 0;
        BinaryPart->CopyFrom(Other.BinaryPart.get(), Other.BinaryPart->Size);
        BinaryPart->Position = 0;
    }
    else
    {
        BinaryPart.reset();
    }
    return *this;
}
//---------------------------------------------------------------------------
bool TSpectrum::LoadFromFile(const String &FileName, const bool ShowExceptionMsg)
{
    try
    {
        ErrorMessage = L"";
        CheckError(Sysutils::FileExists(FileName), L"\"" + FileName + L"\"" + FileExistenceError);

        if (!BinaryPart)
        {
            BinaryPart = std::make_unique<TMemoryStream>();
        }
        BinaryPart->LoadFromFile(FileName);
        BinaryPart->Position = 0;
        if (!StringPart)
        {
            StringPart = std::make_unique<TStringList>();
        }
        StringPart->CaseSensitive = false;
        StringPart->Text = reinterpret_cast<char *>(BinaryPart->Memory);

        Duration = wcstod(ReadString(L"Exposition", L"Live", L"0").c_str(), nullptr);
        CheckError(Duration > 0, MeasurementDurationError);

        DurationReal = wcstod(ReadString(L"Exposition", L"Real", L"0").c_str(), nullptr);
        if (DurationReal <= 0)
        {
            DurationReal = Duration;
        }

        Weight = wcstod(ReadString(L"Sample", L"Weight", L"0").c_str(), nullptr);
        CheckError(Weight > 0, SampleMassError);

        Volume = wcstod(ReadString(L"Sample", L"Volume", L"0").c_str(), nullptr);
        CheckError(Volume > 0, SampleVolumeError);

        WeightUnit = ReadString(L"Sample", L"Unit_weight", L"");
        CheckError(SameText(WeightUnit, L"g") || SameText(WeightUnit, L"kg"), SampleMassUnitError);

        VolumeUnit = ReadString(L"Sample", L"Unit_volume", L"");
        CheckError(
            SameText(VolumeUnit, L"l") || SameText(VolumeUnit, L"ml") || SameText(VolumeUnit, L"m^3"),
            SampleVolumeUnitError);

        if (SameText(VolumeUnit, L"ml"))
        {
            Volume /= 1000.0;
        }
        else if (SameText(VolumeUnit, L"m^3"))
        {
            Volume *= 1000.0;
        }

        DensityInGramPerLitre = SameText(WeightUnit, L"kg") ? ((Weight * 1000) / Volume) : (Weight / Volume);
        CheckError(DensityInGramPerLitre > 0, SampleDensityError);

        ChannelCount = ReadString(L"Channel_count", L"N", L"0").ToIntDef(0);
        CheckError(ChannelCount == 1024 || ChannelCount == 4096, ChannelCountError);

        Channel1 = wcstod(ReadString(L"Energy_calibration", L"Channel1", L"0").c_str(), nullptr) - 1;
        Channel2 = wcstod(ReadString(L"Energy_calibration", L"Channel2", L"0").c_str(), nullptr) - 1;
        Channel3 = wcstod(ReadString(L"Energy_calibration", L"Channel3", L"0").c_str(), nullptr) - 1;
        Channel4 = wcstod(ReadString(L"Energy_calibration", L"Channel4", L"0").c_str(), nullptr) - 1;
        Channel5 = wcstod(ReadString(L"Energy_calibration", L"Channel5", L"0").c_str(), nullptr) - 1;
        Energy1 = wcstod(ReadString(L"Energy_calibration", L"Energy1", L"0").c_str(), nullptr);
        Energy2 = wcstod(ReadString(L"Energy_calibration", L"Energy2", L"0").c_str(), nullptr);
        Energy3 = wcstod(ReadString(L"Energy_calibration", L"Energy3", L"0").c_str(), nullptr);
        Energy4 = wcstod(ReadString(L"Energy_calibration", L"Energy4", L"0").c_str(), nullptr);
        Energy5 = wcstod(ReadString(L"Energy_calibration", L"Energy5", L"0").c_str(), nullptr);
        CheckError(Channel1 > 0 && Channel2 > 0 && Energy1 > 0 && Energy2 > 0, EnergyCalibrationError);
        CalibrationPoints = 2;
        if (Channel3 > 0 && Energy3 > 0)
        {
            CalibrationPoints++;
        }
        if (Channel4 > 0 && Energy4 > 0)
        {
            CheckError(CalibrationPoints > 2, EnergyCalibrationError);
            CalibrationPoints++;
        }
        if (Channel5 > 0 && Energy5 > 0)
        {
            CheckError(CalibrationPoints > 3, EnergyCalibrationError);
            CalibrationPoints++;
        }
        if (CalibrationPoints > 2)
        {
            CalibrationType = Quadratic;
        }
        BkgFileName = ReadString(L"Filenames", L"Bkg", L"");

        int SectionIndex = StringPart->IndexOf(L"[BEGIN]");
        if (SectionIndex > -1)
        {
            static const AnsiString BEGIN_CRLF = "[BEGIN]\r\n";
            static const AnsiString BEGIN_LF   = "[BEGIN]\n";
            static const AnsiString BEGIN_CR   = "[BEGIN]\r";
            const char *Pos = (const char*)BinaryPart->Memory;
            BinaryPart->Position = 0;
            while ((Pos - (const char*)BinaryPart->Memory) < BinaryPart->Size)
            {
                bool Found = false;
                if (BEGIN_CRLF == AnsiString(Pos, BEGIN_CRLF.Length()))
                {
                    BinaryPart->Position += BEGIN_CRLF.Length();
                    Found = true;
                }
                else if (BEGIN_LF == AnsiString(Pos, BEGIN_LF.Length()))
                {
                    BinaryPart->Position += BEGIN_LF.Length();
                    Found = true;
                }
                else if (BEGIN_CR == AnsiString(Pos, BEGIN_CR.Length()))
                {
                    BinaryPart->Position += BEGIN_CR.Length();
                    Found = true;
                }
                if (Found)
                {
                    Counts.resize(ChannelCount);
                    std::vector<int> IntCounts(ChannelCount, 0);
                    char *Buffer = reinterpret_cast<char *>(IntCounts.data());
                    BinaryPart->Read(Buffer, IntCounts.size() * sizeof(int));
                    for (size_t i = 0; i < IntCounts.size(); i++)
                    {
                        Counts[i] = IntCounts[i];
                    }
                    break;
                }
                Pos++;
                BinaryPart->Position++;
            }
        }
        else if ((SectionIndex = StringPart->IndexOf(L"[SPECTRUM]")) > -1)
        {
            Counts.resize(0);
            for (int i = SectionIndex + 1; i < StringPart->Count; i++)
            {
                const auto &Line = StringPart->Strings[i];
                if (Line.IsEmpty() || Line[1] == L'[' || Counts.size() == ChannelCount)
                {
                    break;
                }
                Counts.push_back(wcstod(Line.c_str(), nullptr));
            }
        }

        CheckError(Counts.size() == ChannelCount, NoSpectrumError);
        Counts[ChannelCount - 1] = Counts[ChannelCount - 2];
        Energies.resize(ChannelCount);
        if (CalibrationType == Linear)
        {
            B = (Energy1 - Energy2) / (Channel1 - Channel2);
            A = Energy1 - B * Channel1;
            int X = 0;
            for (auto &E : Energies)
            {
                E = A + B * (X++);
            }
        }
        else
        {
            CalibrateWithQuadraticFunction();
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
        CheckError(SameText(VolumeUnit, L"l") || SameText(VolumeUnit, L"ml") || SameText(VolumeUnit, L"m^3"));
        CheckError(Channel1 > 0 && Channel2 > 0 && Energy1 > 0 && Energy2 > 0);
        CheckError(CalibrationType == Linear || CalibrationType == Quadratic);
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
double TSpectrum::CalculateCountByChannelRange(const size_t Start, const size_t End) const
{
    double Result = 0;
    for (size_t i = Start; i <= End && i < Counts.size(); i++)
    {
        Result += Counts[i];
    }
    return Result;
}
//---------------------------------------------------------------------------
double TSpectrum::CalculateNetCountByChannelRange(const size_t Start, const size_t End) const
{
    double Result = 0;
    double Bkg = 0;
    if (Start < Counts.size() && End < Counts.size() && End > Start)
    {
        Bkg = ((Counts[Start] + Counts[End]) / 2.0) * (End - Start);
    }
    for (size_t i = Start; i <= End && i < Counts.size(); i++)
    {
        Result += Counts[i];
    }
    return Result - Bkg;
}
//---------------------------------------------------------------------------
std::pair<double, double> TSpectrum::CalculateCentroidByChannelRange(const size_t Start, const size_t End) const
{
    double SumOfMulCh = 0;
    double SumOfMulEn = 0;
    double Sum = 0;
    for (size_t i = Start; i <= End && i < Counts.size(); i++)
    {
        SumOfMulCh += (i * Counts[i]);
        SumOfMulEn += (Energies[i] * Counts[i]);
        Sum += Counts[i];
    }
    if (Sum != 0)
    {
        return std::make_pair(SumOfMulCh / Sum, SumOfMulEn / Sum);
    }
    else
    {
        return std::make_pair(0.0, 0.0);
    }
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
            CheckError(
                Energies.size() == Counts.size() &&
                Energies.size() == Spc.Energies.size() &&
                B != 0 && Spc.B != 0,
                AddingSpectraEnergyCalibrationError);
        }
        NewSpc.Counts.resize(Counts.size());
        for (size_t i = 0; i < Counts.size(); i++)
        {
            int X = (int)i;
            if (ByEnergy)
            {
                X = Math::Ceil(EnergyToChannel(Energies[i], Spc.A, Spc.B, Spc.C));
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
            CheckError(
                Energies.size() == Counts.size() &&
                Energies.size() == Spc.Energies.size() &&
                B != 0 && Spc.B != 0,
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
                X = Math::Ceil(EnergyToChannel(Energies[i], Spc.A, Spc.B, Spc.C));
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
        const double SrcB = (En2 - En1) / (SrcCh2 - SrcCh1);
        const double SmpB = (En2 - En1) / (SmpCh2 - SmpCh1);
        const double SrcA = En1 - SrcB * SrcCh1;
        const double SmpA = En1 - SmpB * SmpCh1;

        for (size_t i = 0; i < Counts.size(); i++)
        {
            ResultSpc.Counts[i] = 0;
            const double SrcCal = SrcA + SrcB * i;
            int X = Math::Ceil((SrcCal - SmpA) / SmpB);
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
                const int En = Math::Ceil(1000 * (SmpA + SmpB * (X + d)));
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
        ResultSpc.Channel3 = 0;
        ResultSpc.Channel4 = 0;
        ResultSpc.Channel5 = 0;
        ResultSpc.Energy1 = En1;
        ResultSpc.Energy2 = En2;
        ResultSpc.Energy3 = 0;
        ResultSpc.Energy4 = 0;
        ResultSpc.Energy5 = 0;
        ResultSpc.A = SrcA;
        ResultSpc.B = SrcB;
        ResultSpc.C = 0;
        ResultSpc.CalibrationType = Linear;
        int X = 0;
        for (auto &E : ResultSpc.Energies)
        {
            E = ResultSpc.A + ResultSpc.B * (X++);
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
double TSpectrum::GetEnergyValueByIndex(const size_t I) const
{
    if (I < Energies.size())
    {
        return Energies[I];
    }
    else
    {
        return 0.0;
    }
}
//---------------------------------------------------------------------------
double TSpectrum::GetCountValueByIndex(const size_t I) const
{
    if (I < Counts.size())
    {
        return Counts[I];
    }
    else
    {
        return 0.0;
    }
}
//---------------------------------------------------------------------------
// Savitzky–Golay smoothing
// windowSize - must be odd (e.g., 5, 7, 9)
// polyOrder  - polynomial order (usually 2 or 3)
TSpectrum TSpectrum::SavitzkyGolaySmooth(const int windowSize, const int polyOrder) const
{
    try
    {
        if (windowSize % 2 == 0 || windowSize < 3)
        {
            throw Exception("Window size must be odd and >= 3");
        }
        if (polyOrder >= windowSize)
        {
            throw Exception("Polynomial order must be less than window size");
        }

        int halfWindow = windowSize / 2;
        TSpectrum Result = *this;
        const int n = Counts.size();

        std::vector<double> coeff(windowSize, 0.0);

        std::vector<std::vector<double>> A(windowSize, std::vector<double>(polyOrder + 1, 0.0));
        for (int i = -halfWindow; i <= halfWindow; ++i)
        {
            double val = 1.0;
            for (int j = 0; j <= polyOrder; ++j)
            {
                A[i + halfWindow][j] = val;
                val *= i;
            }
        }

        std::vector<std::vector<double>> ATA(polyOrder + 1, std::vector<double>(polyOrder + 1, 0.0));
        for (int i = 0; i <= polyOrder; ++i)
        {
            for (int j = 0; j <= polyOrder; ++j)
            {
                double sum = 0.0;
                for (int k = 0; k < windowSize; ++k)
                {
                    sum += A[k][i] * A[k][j];
                }
                ATA[i][j] = sum;
            }
        }

        std::vector<std::vector<double>> invATA = ATA;
        int m = polyOrder + 1;
        std::vector<std::vector<double>> I(m, std::vector<double>(m, 0.0));
        for (int i = 0; i < m; ++i)
        {
            I[i][i] = 1.0;
        }

        for (int i = 0; i < m; ++i)
        {
            double pivot = invATA[i][i];
            if (pivot == 0.0)
            {
                throw std::runtime_error("Singular matrix in Savitzky-Golay");
            }
            double invPivot = 1.0 / pivot;
            for (int j = 0; j < m; ++j)
            {
                invATA[i][j] *= invPivot;
                I[i][j] *= invPivot;
            }
            for (int k = 0; k < m; ++k)
            {
                if (k == i) continue;
                double factor = invATA[k][i];
                for (int j = 0; j < m; ++j)
                {
                    invATA[k][j] -= factor * invATA[i][j];
                    I[k][j] -= factor * I[i][j];
                }
            }
        }

        for (int k = 0; k < windowSize; ++k)
        {
            coeff[k] = 0.0;
            for (int j = 0; j <= polyOrder; ++j)
            {
                coeff[k] += I[0][j] * A[k][j];
            }
        }

        for (int i = 0; i < n; ++i)
        {
            double sum = 0.0;
            for (int j = -halfWindow; j <= halfWindow; ++j)
            {
                int idx = i + j;
                if (idx < 0)
                {
                    idx = 0;
                }
                else if (idx >= n)
                {
                    idx = n - 1;
                }
                sum += coeff[j + halfWindow] * Counts[idx];
            }
            Result.Counts[i] = sum;
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
void TSpectrum::CalibrateWithQuadraticFunction()
{
    const double Channels[5] = {Channel1, Channel2, Channel3, Channel4, Channel5};
    const double Energies[5] = {Energy1, Energy2, Energy3, Energy4, Energy5};

    double SumC0 = 0.0;
    double SumC1 = 0.0;
    double SumC2 = 0.0;
    double SumC3 = 0.0;
    double SumC4 = 0.0;

    double SumE0 = 0.0;
    double SumE1 = 0.0;
    double SumE2 = 0.0;

    for (int i = 0; i < CalibrationPoints; ++i)
    {
        double C = Channels[i];
        double E = Energies[i];

        double C2 = C * C;
        double C3 = C2 * C;
        double C4 = C2 * C2;

        SumC0 += 1.0;
        SumC1 += C;
        SumC2 += C2;
        SumC3 += C3;
        SumC4 += C4;

        SumE0 += E;
        SumE1 += E * C;
        SumE2 += E * C2;
    }

    const double NormalMatrix[3][3] =
    {
        {SumC0, SumC1, SumC2},
        {SumC1, SumC2, SumC3},
        {SumC2, SumC3, SumC4}
    };

    const double RightHandSide[3] = {SumE0, SumE1, SumE2};

    double InverseMatrix[3][3];
    if (!InvertMatrix3x3(NormalMatrix, InverseMatrix))
    {
        throw Exception(L"Matrix inversion failed - singular matrix");
    }

    A = InverseMatrix[0][0] * RightHandSide[0]
             + InverseMatrix[0][1] * RightHandSide[1]
             + InverseMatrix[0][2] * RightHandSide[2];

    B = InverseMatrix[1][0] * RightHandSide[0]
             + InverseMatrix[1][1] * RightHandSide[1]
             + InverseMatrix[1][2] * RightHandSide[2];

    C = InverseMatrix[2][0] * RightHandSide[0]
             + InverseMatrix[2][1] * RightHandSide[1]
             + InverseMatrix[2][2] * RightHandSide[2];

    for (size_t i = 0; i < this->Energies.size(); i++)
    {
        const double ChannelVal = static_cast<double>(i);
        this->Energies[i] = A + B * ChannelVal + C * ChannelVal * ChannelVal;
    }
}
//---------------------------------------------------------------------------
double TSpectrum::EnergyToChannel(const double e, const double a, const double b, const double c)
{
    const double Const = a - e;
    if (std::abs(c) < 1e-10)
    {
        if (std::abs(b) < 1e-10)
        {
            throw Exception(EnergyCalibrationError);
        }
        return -Const / b;
    }
    const double Discriminant = b * b - 4.0 * c * Const;
    if (Discriminant < 0.0)
    {
        throw Exception(EnergyCalibrationError);
    }
    const double SqrtDiscriminant = std::sqrt(Discriminant);
    const double Ch1 = (-b + SqrtDiscriminant) / (2.0 * c);
    const double Ch2 = (-b - SqrtDiscriminant) / (2.0 * c);
    if (Ch1 >= 0.0 && Ch2 >= 0.0)
    {
        return (Ch1 < Ch2) ? Ch1 : Ch2;
    }
    else if (Ch1 >= 0.0)
    {
        return Ch1;
    }
    else if (Ch2 >= 0.0)
    {
        return Ch2;
    }
    else
    {
        throw Exception(EnergyCalibrationError);
    }
}
//---------------------------------------------------------------------------
void TSpectrum::SetLanguage()
{
    FileExistenceError = L" fayli mavjud emas.";
    ErrorHeader = L"Quyidagi xatolik yuz berdi:\r\n\r\n";
    ErrorBoxTitle = L"Xato";
    MeasurementDurationError = L"O‘lchash davomiyligi noma'lum.";
    SampleMassError = L"Namuna massasi noma'lum.";
    SampleVolumeError = L"Namuna hajmi noma'lum.";
    SampleMassUnitError = L"Namuna massasining o‘lchov birligi noma'lum.";
    SampleVolumeUnitError = L"Namuna hajmining o‘lchov birligi noma'lum.";
    SampleDensityError = L"Namunaning zichligi noma'lum.";
    ChannelCountError = L"Kanallar soni noma'lum.";
    EnergyCalibrationError = L"Energiya bo‘yicha kalibrovka bajarilmagan.";
    NoSpectrumError = L"Faylda spektr mavjud emas.";
    EnergyChannelValueError = L"Kanal va energiya qiymatlari 0 dan katta bo‘lishi shart.";
    AddingSpectraChannelsError = L"Qo‘shiluvchi va qo‘shuvchi spektrlarda kanallar soni teng emas.";
    AddingSpectraEnergyCalibrationError = L"Qo‘shiluvchi yoki qo‘shuvchi spektrda energiya bo‘yicha kalibrovka noto‘g‘ri.";
    SubtractingSpectraChannelsError = L"Ayriluvchi va ayiruvchi spektrlarda kanallar soni teng emas.";
    SubtractingSpectraEnergyCalibrationError = L"Ayriluvchi yoki ayiruvchi spektrda energiya bo‘yicha kalibrovka noto‘g‘ri.";
    SubtractedSpectrumDurationError = L"Ayriluvchi spektrning o‘lchash davomiyligi noto‘g‘ri.";
    SubtractingSpectrumDurationError = L"Ayiruvchi spektrning o‘lchash davomiyligi noto‘g‘ri.";
    ShiftingRefSampleChannelNumbersError = L"Siljitish: etalon namuna spektri uchun kanallar qiymatlari noto‘g‘ri.";
    ShiftingSampleChannelNumbersError = L"Siljitish: siljitiladigan spektr uchun kanallar qiymatlari noto‘g‘ri.";
    ShiftingEnergyValuesError = L"Siljitish: energiya qiymatlari noto‘g‘ri.";
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
        SampleDensityError = L"The sample density is unknown.";
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
//---------------------------------------------------------------------------
String TSpectrum::ReadString(
    const String &Section, const String &Ident, const String &DefaultValue) const
{
    const int SectionIndex = StringPart->IndexOf(L"[" + Section + L"]");
    if (SectionIndex > -1)
    {
        const auto &IdentL = Ident.LowerCase();
        for (int i = SectionIndex + 1; i < StringPart->Count; i++)
        {
            const auto &Line = StringPart->Strings[i];
            if (!Line.IsEmpty() && Line[1] == L'[')
            {
                break;
            }
            if (StringPart->KeyNames[i].LowerCase() == IdentL)
            {
                const auto &Val = StringPart->ValueFromIndex[i].Trim();
                return Val.IsEmpty() ? DefaultValue : Val;
            }
        }
    }
    return DefaultValue;
}
//---------------------------------------------------------------------------
void TSpectrum::WriteString(const String &Section, const String &Ident, const String &Value)
{
    const int SectionIndex = StringPart->IndexOf(L"[" + Section + L"]");
    if (SectionIndex > -1)
    {
        const auto &IdentL = Ident.LowerCase();
        for (int i = SectionIndex + 1; i < StringPart->Count; i++)
        {
            const auto &Line = StringPart->Strings[i];
            if (!Line.IsEmpty() && Line[1] == L'[')
            {
                break;
            }
            if (StringPart->KeyNames[i].LowerCase() == IdentL)
            {
                StringPart->ValueFromIndex[i] = Value;
                return;
            }
        }
    }
}
//---------------------------------------------------------------------------
bool TSpectrum::InvertMatrix3x3(const double Matrix[3][3], double Inverse[3][3]) const
{
    const double Det =
        Matrix[0][0] * (Matrix[1][1] * Matrix[2][2] - Matrix[1][2] * Matrix[2][1]) -
        Matrix[0][1] * (Matrix[1][0] * Matrix[2][2] - Matrix[1][2] * Matrix[2][0]) +
        Matrix[0][2] * (Matrix[1][0] * Matrix[2][1] - Matrix[1][1] * Matrix[2][0]);

    if (std::abs(Det) < 1e-10)
    {
        return false;
    }

    const double InvDet = 1.0 / Det;

    Inverse[0][0] = (Matrix[1][1] * Matrix[2][2] - Matrix[1][2] * Matrix[2][1]) * InvDet;
    Inverse[0][1] = (Matrix[0][2] * Matrix[2][1] - Matrix[0][1] * Matrix[2][2]) * InvDet;
    Inverse[0][2] = (Matrix[0][1] * Matrix[1][2] - Matrix[0][2] * Matrix[1][1]) * InvDet;

    Inverse[1][0] = (Matrix[1][2] * Matrix[2][0] - Matrix[1][0] * Matrix[2][2]) * InvDet;
    Inverse[1][1] = (Matrix[0][0] * Matrix[2][2] - Matrix[0][2] * Matrix[2][0]) * InvDet;
    Inverse[1][2] = (Matrix[0][2] * Matrix[1][0] - Matrix[0][0] * Matrix[1][2]) * InvDet;

    Inverse[2][0] = (Matrix[1][0] * Matrix[2][1] - Matrix[1][1] * Matrix[2][0]) * InvDet;
    Inverse[2][1] = (Matrix[0][1] * Matrix[2][0] - Matrix[0][0] * Matrix[2][1]) * InvDet;
    Inverse[2][2] = (Matrix[0][0] * Matrix[1][1] - Matrix[0][1] * Matrix[1][0]) * InvDet;

    return true;
}

#endif
