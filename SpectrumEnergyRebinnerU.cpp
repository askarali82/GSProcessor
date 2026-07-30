#include <algorithm>
#include <limits>
#pragma hdrstop

#include "SpectrumEnergyRebinnerU.h"
#include "Common.h"

//---------------------------------------------------------------------------
String TSpectrumEnergyRebinner::GridSizeError;
String TSpectrumEnergyRebinner::ChannelCalibrationError;
String TSpectrumEnergyRebinner::NonUniformGridError;
String TSpectrumEnergyRebinner::NoEnergyOverlapError;
//---------------------------------------------------------------------------
void TSpectrumEnergyRebinner::SetLanguage()
{
    GridSizeError = L"Energiya to‘ri qatorida kamida ikkita chegara bo‘lishi shart.";
    ChannelCalibrationError = L"Spektrning energiya bo‘yicha kalibrovkasi noto‘g‘ri.";
    NonUniformGridError = L"Energiya to‘ri bir xil kenglikdagi kutilarga ega bo‘lishi shart.";
    NoEnergyOverlapError = L"Spektrlarning energiya diapazonlari kesishmaydi.";

    if (LangID == 1)
    {
        GridSizeError = L"Energy grid must contain at least two edges.";
        ChannelCalibrationError = L"Spectrum energy calibration is not valid.";
        NonUniformGridError = L"Energy grid must have uniform bin width.";
        NoEnergyOverlapError = L"Spectra energy ranges do not overlap.";
    }
}
//---------------------------------------------------------------------------
TSpectrumEnergyRebinner::TSpectrumEnergyRebinner(const std::vector<double> &AEnergyGridEdges)
    : EnergyGridEdges(AEnergyGridEdges), BinWidth(0)
{
    if (GridSizeError.IsEmpty())
    {
        SetLanguage();
    }

    if (!EnergyGridEdges.empty())
    {
        SetEnergyGridEdges(EnergyGridEdges);
    }
}
//---------------------------------------------------------------------------
void TSpectrumEnergyRebinner::SetEnergyGridEdges(const std::vector<double> &AEnergyGridEdges)
{
    TSpectrum::CheckError(AEnergyGridEdges.size() >= 2, GridSizeError);
    EnergyGridEdges = AEnergyGridEdges;
    BinWidth = EnergyGridEdges[1] - EnergyGridEdges[0];
    TSpectrum::CheckError(BinWidth > 0, NonUniformGridError);
    for (size_t i = 1; i < EnergyGridEdges.size(); i++)
    {
        const double Width = EnergyGridEdges[i] - EnergyGridEdges[i - 1];
        TSpectrum::CheckError(std::abs(Width - BinWidth) < (BinWidth * 1e-6), NonUniformGridError);
    }
    EnergyGridCenters.resize(EnergyGridEdges.size() - 1);
    for (size_t i = 0; i < EnergyGridCenters.size(); i++)
    {
        EnergyGridCenters[i] = (EnergyGridEdges[i] + EnergyGridEdges[i + 1]) / 2.0;
    }
}
//---------------------------------------------------------------------------
int TSpectrumEnergyRebinner::BinCount() const
{
    return static_cast<int>(EnergyGridCenters.size());
}
//---------------------------------------------------------------------------
int TSpectrumEnergyRebinner::FindBinIndex(const double Energy) const
{
    if (Energy <= EnergyGridEdges.front())
    {
        return 0;
    }
    if (Energy >= EnergyGridEdges.back())
    {
        return BinCount() - 1;
    }
    auto It = std::upper_bound(EnergyGridEdges.begin(), EnergyGridEdges.end(), Energy);
    return static_cast<int>(It - EnergyGridEdges.begin()) - 1;
}
//---------------------------------------------------------------------------
TSpectrum TSpectrumEnergyRebinner::RebinToGrid(
    const TSpectrum &Src, std::vector<double> &ResultVariance) const
{
    TSpectrum::CheckError(Src.Energies.size() == Src.Counts.size() && Src.B != 0, ChannelCalibrationError);

    const int TargetBinCount = BinCount();
    TSpectrum ResultSpc = Src;
    ResultSpc.Counts.assign(TargetBinCount, 0.0);
    ResultVariance.assign(TargetBinCount, 0.0);

    for (size_t i = 0; i < Src.Counts.size(); i++)
    {
        double ELow = Src.ChannelToEnergy(static_cast<double>(i));
        double EHigh = Src.ChannelToEnergy(static_cast<double>(i + 1));

        if (EHigh < ELow)
        {
            std::swap(ELow, EHigh);
        }

        const double SourceWidth = EHigh - ELow;
        if (SourceWidth <= 0.0)
        {
            continue;
        }

        const int StartBin = FindBinIndex(ELow);
        const int EndBin = FindBinIndex(EHigh);

        for (int j = StartBin; j <= EndBin && j < TargetBinCount; j++)
        {
            if (j < 0)
            {
                continue;
            }

            const double BinLow = EnergyGridEdges[j];
            const double BinHigh = EnergyGridEdges[j + 1];
            const double OverlapLow = std::max(ELow, BinLow);
            const double OverlapHigh = std::min(EHigh, BinHigh);
            const double Overlap = OverlapHigh - OverlapLow;

            if (Overlap <= 0.0)
            {
                continue;
            }

            const double Weight = Overlap / SourceWidth;
            ResultSpc.Counts[j] += Weight * Src.Counts[i];
            ResultVariance[j] += Weight * Weight * Src.Counts[i];
        }
    }

    ResultSpc.ChannelCount = TargetBinCount;
    ResultSpc.Energies = EnergyGridCenters;
    ResultSpc.CalibrationType = TSpectrum::Linear;
    ResultSpc.CalibrationPoints = 2;
    ResultSpc.Channel1 = 0;
    ResultSpc.Channel2 = static_cast<double>(TargetBinCount - 1);
    ResultSpc.Channel3 = 0;
    ResultSpc.Channel4 = 0;
    ResultSpc.Channel5 = 0;
    ResultSpc.Energy1 = EnergyGridCenters.front();
    ResultSpc.Energy2 = EnergyGridCenters.back();
    ResultSpc.Energy3 = 0;
    ResultSpc.Energy4 = 0;
    ResultSpc.Energy5 = 0;
    ResultSpc.B = BinWidth;
    ResultSpc.A = EnergyGridCenters.front() - ResultSpc.B * ResultSpc.Channel1;
    ResultSpc.C = 0;

    LOG(L"\r\nSize of Counts: " + String(ResultSpc.Counts.size()) +
        L", Size of Energies: " + String(ResultSpc.Energies.size()) +
        L", ChannelCount: " + String(ResultSpc.ChannelCount) + L"\r\n");

    return ResultSpc;
}
//---------------------------------------------------------------------------
double TSpectrumEnergyRebinner::CalculateVarianceByEnergyRange(
    const TSpectrum &Spc, const std::vector<double> &Variance, const double Start, const double End) const
{
    double Result = 0;
    for (size_t i = 0; i < Spc.Energies.size(); i++)
    {
        const auto &E = Spc.Energies[i];
        if (E >= Start && E <= End && i < Variance.size())
        {
            Result += Variance[i];
        }
    }
    return Result;
}
//---------------------------------------------------------------------------
std::vector<double> TSpectrumEnergyRebinner::BuildGridFromSpectra(const std::vector<const TSpectrum *> &Spectra)
{
    if (Spectra.empty())
    {
        std::vector<double> Edges;
        const double MinEnergy = 0;
        const double MaxEnergy = 3000;
        const double BinWidth = 3.0;
        const int EdgeCount = static_cast<int>((MaxEnergy - MinEnergy) / BinWidth) + 1;

        Edges.resize(EdgeCount);
        for (int i = 0; i < EdgeCount; i++)
        {
            Edges[i] = MinEnergy + i * BinWidth;
        }
        return Edges;
    }

    double RangeStart = -std::numeric_limits<double>::max();
    double RangeEnd = std::numeric_limits<double>::max();
    double WorstBinWidth = 0;

    for (const auto *Spc : Spectra)
    {
        TSpectrum::CheckError(Spc->ChannelCount > 0 && Spc->B != 0, ChannelCalibrationError);

        const double SpcEnergyMin = Spc->ChannelToEnergy(0);
        const double SpcEnergyMax = Spc->ChannelToEnergy(Spc->ChannelCount - 1);
        const double AverageChannelWidth = (SpcEnergyMax - SpcEnergyMin) / Spc->ChannelCount;

        RangeStart = std::max(RangeStart, SpcEnergyMin);
        RangeEnd = std::min(RangeEnd, SpcEnergyMax);
        WorstBinWidth = std::max(WorstBinWidth, AverageChannelWidth);
    }

    TSpectrum::CheckError(RangeEnd > RangeStart, NoEnergyOverlapError);

    const int BinCount = static_cast<int>((RangeEnd - RangeStart) / WorstBinWidth);
    TSpectrum::CheckError(BinCount > 0, NoEnergyOverlapError);

    std::vector<double> Edges(BinCount + 1);
    for (int i = 0; i <= BinCount; i++)
    {
        Edges[i] = RangeStart + i * WorstBinWidth;
    }
    return Edges;
}
