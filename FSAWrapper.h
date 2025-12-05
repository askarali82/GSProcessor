#ifndef FSAWrapperH
#define FSAWrapperH

#include <System.hpp>
#include <vector>
#include "FSA/fsa.h"

class TFullSpectrumAnalysis
{
private:
    FSAHandle FHandle;
    int FNumChannels;
    int FNumNuclides;

public:
    TFullSpectrumAnalysis(int numChannels, int numNuclides)
        : FNumChannels(numChannels), FNumNuclides(numNuclides)
    {
        FHandle = FSA_Create(numChannels, numNuclides);
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

    void AddReferenceSpectrum(int nuclideIdx,
                             const std::vector<double>& spectrum,
                             const std::vector<double>& refBackground,
                             double activity,
                             double measTime,
                             const String& name)
    {
        AnsiString ansiName(name);
        int result = FSA_AddReferenceSpectrum(
            FHandle,
            nuclideIdx,
            spectrum.data(),
            refBackground.data(),
            spectrum.size(),
            activity,
            measTime,
            ansiName.c_str()
        );

        if (!result)
        {
            throw Exception("Failed to add reference spectrum: " +
                          String(FSA_GetLastError()));
        }
    }

    void AddNormalizedReference(int nuclideIdx,
                               const std::vector<double>& normalizedSpectrum,
                               const String& name)
    {
        AnsiString ansiName(name);
        int result = FSA_AddNormalizedReference(
            FHandle,
            nuclideIdx,
            normalizedSpectrum.data(),
            normalizedSpectrum.size(),
            ansiName.c_str()
        );

        if (!result)
        {
            throw Exception("Failed to add normalized reference: " +
                          String(FSA_GetLastError()));
        }
    }

    void SetBackground(const std::vector<double>& background)
    {
        int result = FSA_SetBackground(
            FHandle,
            background.data(),
            background.size()
        );

        if (!result)
        {
            throw Exception("Failed to set background: " +
                          String(FSA_GetLastError()));
        }
    }

    std::vector<double> Analyze(const std::vector<double>& measuredSpectrum,
                                double measTime)
    {
        std::vector<double> activities(FNumNuclides);

        int result = FSA_Analyze(
            FHandle,
            measuredSpectrum.data(),
            measuredSpectrum.size(),
            measTime,
            activities.data(),
            activities.size()
        );

        if (!result)
        {
            throw Exception("Analysis failed: " + String(FSA_GetLastError()));
        }

        return activities;
    }

    std::vector<double> AnalyzeQR(const std::vector<double>& measuredSpectrum,
                                  double measTime)
    {
        std::vector<double> activities(FNumNuclides);

        int result = FSA_AnalyzeQR(
            FHandle,
            measuredSpectrum.data(),
            measuredSpectrum.size(),
            measTime,
            activities.data(),
            activities.size()
        );

        if (!result)
        {
            throw Exception("QR Analysis failed: " + String(FSA_GetLastError()));
        }

        return activities;
    }

    double CalculateChiSquare(const std::vector<double>& measuredSpectrum,
                             const std::vector<double>& activities,
                             double measTime)
    {
        double chi2 = FSA_CalculateChiSquare(
            FHandle,
            measuredSpectrum.data(),
            measuredSpectrum.size(),
            activities.data(),
            activities.size(),
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
            measuredSpectrum.size(),
            uncertainties.data(),
            uncertainties.size()
        );

        if (!result)
        {
            throw Exception("Uncertainty calculation failed: " +
                          String(FSA_GetLastError()));
        }

        return uncertainties;
    }

    int GetNumChannels() const { return FNumChannels; }
    int GetNumNuclides() const { return FNumNuclides; }
};

#endif
