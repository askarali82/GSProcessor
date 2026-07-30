#ifndef SpectrumEnergyRebinnerUH
#define SpectrumEnergyRebinnerUH

#include "Spectrum.hpp"
#include <vector>

class TSpectrumEnergyRebinner
{
private:
    static String GridSizeError;
    static String ChannelCalibrationError;
    static String NonUniformGridError;
    static String NoEnergyOverlapError;

    std::vector<double> EnergyGridEdges;
    std::vector<double> EnergyGridCenters;
    double BinWidth;

    int FindBinIndex(const double Energy) const;

public:
    static void SetLanguage();

    static std::vector<double> BuildGridFromSpectra(
        const std::vector<const TSpectrum *> &Spectra = std::vector<const TSpectrum *>());

    TSpectrumEnergyRebinner(const std::vector<double> &AEnergyGridEdges = std::vector<double>());

    void SetEnergyGridEdges(const std::vector<double> &AEnergyGridEdges);

    TSpectrum RebinToGrid(const TSpectrum &Src, std::vector<double> &ResultVariance) const;

    double CalculateVarianceByEnergyRange(
        const TSpectrum &Spc, const std::vector<double> &Variance, const double Start, const double End) const;

    int BinCount() const;
};

#endif
