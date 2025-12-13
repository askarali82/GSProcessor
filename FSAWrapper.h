#ifndef FSAWrapperH
#define FSAWrapperH

#include <System.hpp>
#include <vector>
#include "FSA/fsa.h"

class TCalibration
{
public:
    double A;  // Offset (keV)
    double B;  // Linear coefficient (keV/channel)
    double C;  // Quadratic coefficient (keV/channel²)

    TCalibration() : A(0), B(1), C(0) {}
    TCalibration(double a, double b, double c) : A(a), B(b), C(c) {}

    // Calculate energy for a given channel
    double ChannelToEnergy(int channel) const
    {
        return A + B * channel + C * channel * channel;
    }

    // Convert to C structure
    FSACalibration ToCStruct() const
    {
        FSACalibration cal;
        cal.a = A;
        cal.b = B;
        cal.c = C;
        return cal;
    }

    // Create from linear calibration (a + b*C)
    static TCalibration Linear(double offset, double gain)
    {
        return TCalibration(offset, gain, 0.0);
    }

    // Create from quadratic calibration (a + b*C + c*C²)
    static TCalibration Quadratic(double offset, double gain, double quadratic)
    {
        return TCalibration(offset, gain, quadratic);
    }
};

class TFullSpectrumAnalysis
{
private:
    FSAHandle FHandle;
    int FNumNuclides;

public:
    // Constructor for energy-based mode
    TFullSpectrumAnalysis(double energyMin, double energyMax,
                          double energyStep, int numNuclides)
        : FNumNuclides(numNuclides)
    {
        FHandle = FSA_Create(energyMin, energyMax, energyStep, numNuclides);
        if (!FHandle)
        {
            throw Exception("Failed to create FSA instance: " +
                          String(FSA_GetLastError()));
        }
    }

    ~TFullSpectrumAnalysis()
    {
        if (FHandle)
        {
            FSA_Destroy(FHandle);
        }
    }

    void AddReferenceSpectrum(
        int nuclideIdx,
        const std::vector<double>& spectrum,
        const TCalibration& calibration,
        double activity,
        double measTime)
    {
        FSACalibration cal = calibration.ToCStruct();

        int result = FSA_AddReferenceSpectrum(
            FHandle, nuclideIdx,
            spectrum.data(), spectrum.size(),
            &cal, activity, measTime);

        if (!result)
        {
            throw Exception("Failed to add reference spectrum: " +
                          String(FSA_GetLastError()));
        }
    }

    void SetBackground(
        const std::vector<double>& background,
        const TCalibration& calibration,
        double measTime)
    {
        FSACalibration cal = calibration.ToCStruct();

        int result = FSA_SetBackground(
            FHandle, background.data(), background.size(), &cal, measTime);

        if (!result)
        {
            throw Exception("Failed to set background: " +
                          String(FSA_GetLastError()));
        }
    }

    std::vector<double> Analyze(
        const std::vector<double>& measuredSpectrum,
        const TCalibration& calibration,
        double measTime)
    {
        std::vector<double> activities(FNumNuclides);
        FSACalibration cal = calibration.ToCStruct();

        int result = FSA_Analyze(
            FHandle,
            measuredSpectrum.data(),
            measuredSpectrum.size(),
            &cal,
            measTime,
            activities.data(),
            activities.size());

        if (!result)
        {
            throw Exception("NNLS Analysis failed: " + String(FSA_GetLastError()));
        }

        return activities;
    }

    double GetInterpolatedTotalCounts(
        const std::vector<double>& spectrum,
        const TCalibration& calibration,
        std::vector<double>& interpolatedSpectrum)
    {
        FSACalibration cal = calibration.ToCStruct();

        double *interpSpc;
        int interpSpcSize = 0;
        double total = FSA_GetInterpolatedTotalCounts(
            FHandle, spectrum.data(), spectrum.size(), &cal, &interpSpc, &interpSpcSize);

        if (total < 0)
        {
            throw Exception("Failed to get interpolated counts: " +
                          String(FSA_GetLastError()));
        }

        interpolatedSpectrum.resize(interpSpcSize);
        for (int i = 0; i < interpSpcSize; i++)
        {
            interpolatedSpectrum[i] = interpSpc[i];
        }

        return total;
    }

    double GetBackgroundScale(const std::vector<double>& measuredSpectrum,
                             double measTime)
    {
        double scale = FSA_GetBackgroundScale(
            FHandle,
            measuredSpectrum.data(),
            measTime
        );

        if (scale < 0)
        {
            throw Exception("Failed to get background scale: " +
                          String(FSA_GetLastError()));
        }

        return scale;
    }

    double CalculateChiSquare(const std::vector<double>& measuredSpectrum,
                             const std::vector<double>& activities,
                             double measTime)
    {
        double chi2 = FSA_CalculateChiSquare(
            FHandle,
            measuredSpectrum.data(),
            activities.data(),
            measTime
        );

        if (chi2 < 0)
        {
            throw Exception("Chi-square calculation failed: " +
                          String(FSA_GetLastError()));
        }

        return chi2;
    }

    std::vector<double> CalculateUncertainties(const std::vector<double>& measuredSpectrum)
    {
        std::vector<double> uncertainties(FNumNuclides);

        int result = FSA_CalculateUncertainties(
            FHandle,
            measuredSpectrum.data(),
            uncertainties.data()
        );

        if (!result)
        {
            throw Exception("Uncertainty calculation failed: " +
                          String(FSA_GetLastError()));
        }

        return uncertainties;
    }

    int GetNumNuclides() const { return FNumNuclides; }
};

#endif
