#include "FSA.h"
#include <Eigen/Dense>
#include <string>
#include <stdexcept>

using Eigen::MatrixXd;
using Eigen::VectorXd;

// Thread-local error message storage
static thread_local std::string g_LastError;

void SetLastError(const std::string& error)
{
    g_LastError = error;
}

class FullSpectrumAnalysis
{
private:
    int NumChannels;
    int NumNuclides;
    MatrixXd ReferenceMatrix;
    VectorXd Background;
    std::vector<std::string> NuclideNames;

public:
    FullSpectrumAnalysis(int channels, int nuclides)
        : NumChannels(channels), NumNuclides(nuclides)
    {
        ReferenceMatrix = MatrixXd::Zero(channels, nuclides);
        Background = VectorXd::Zero(channels);
        NuclideNames.resize(nuclides);
    }

    void AddReferenceSpectrum(int nuclideIdx,
        const double* spectrum,
        const double* refBackground,
        double activity,
        double measTime,
        const std::string& name)
    {
        if (nuclideIdx < 0 || nuclideIdx >= NumNuclides)
        {
            throw std::out_of_range("Nuclide index out of range");
        }

        for (int i = 0; i < NumChannels; i++)
        {
            double netCounts = spectrum[i] - refBackground[i];
            ReferenceMatrix(i, nuclideIdx) = netCounts / (activity * measTime);
        }
        NuclideNames[nuclideIdx] = name;
    }

    void AddNormalizedReference(int nuclideIdx,
        const double* normalizedSpectrum,
        const std::string& name)
    {
        if (nuclideIdx < 0 || nuclideIdx >= NumNuclides)
        {
            throw std::out_of_range("Nuclide index out of range");
        }

        for (int i = 0; i < NumChannels; i++)
        {
            ReferenceMatrix(i, nuclideIdx) = normalizedSpectrum[i];
        }
        NuclideNames[nuclideIdx] = name;
    }

    void SetBackground(const double* bg)
    {
        for (int i = 0; i < NumChannels; i++)
        {
            Background(i) = bg[i];
        }
    }

    void Analyze(const double* measuredSpectrum, double measTime, double* activities)
    {
        VectorXd measured(NumChannels);
        for (int i = 0; i < NumChannels; i++)
        {
            measured(i) = measuredSpectrum[i];
        }

        VectorXd netSpectrum = measured - Background;
        MatrixXd scaledReference = ReferenceMatrix * measTime;

        VectorXd result = (scaledReference.transpose() * scaledReference)
            .ldlt()
            .solve(scaledReference.transpose() * netSpectrum);

        for (int i = 0; i < NumNuclides; i++)
        {
            activities[i] = result(i);
        }
    }

    void AnalyzeQR(const double* measuredSpectrum, double measTime, double* activities)
    {
        VectorXd measured(NumChannels);
        for (int i = 0; i < NumChannels; i++)
        {
            measured(i) = measuredSpectrum[i];
        }

        VectorXd netSpectrum = measured - Background;
        MatrixXd scaledReference = ReferenceMatrix * measTime;

        VectorXd result = scaledReference.colPivHouseholderQr().solve(netSpectrum);

        for (int i = 0; i < NumNuclides; i++)
        {
            activities[i] = result(i);
        }
    }

    double CalculateChiSquare(const double* measuredSpectrum,
        const double* activities,
        double measTime)
    {
        VectorXd measured(NumChannels);
        VectorXd act(NumNuclides);

        for (int i = 0; i < NumChannels; i++)
        {
            measured(i) = measuredSpectrum[i];
        }

        for (int i = 0; i < NumNuclides; i++)
        {
            act(i) = activities[i];
        }

        MatrixXd scaledReference = ReferenceMatrix * measTime;
        VectorXd expected = Background + scaledReference * act;

        double chi2 = 0.0;
        for (int i = 0; i < NumChannels; i++)
        {
            double diff = measured(i) - expected(i);
            double variance = std::max(measured(i), 1.0);
            chi2 += (diff * diff) / variance;
        }

        return chi2;
    }

    void CalculateUncertainties(const double* measuredSpectrum, double* uncertainties)
    {
        MatrixXd W = MatrixXd::Zero(NumChannels, NumChannels);
        for (int i = 0; i < NumChannels; i++)
        {
            double variance = std::max(measuredSpectrum[i], 1.0);
            W(i, i) = 1.0 / variance;
        }

        MatrixXd covariance = (ReferenceMatrix.transpose() * W * ReferenceMatrix).inverse();

        for (int i = 0; i < NumNuclides; i++)
        {
            uncertainties[i] = std::sqrt(covariance(i, i));
        }
    }
};

// ============================================================================
// C API Implementation
// ============================================================================

FSA_API FSAHandle FSA_Create(int numChannels, int numNuclides)
{
    try
    {
        FullSpectrumAnalysis* fsa = new FullSpectrumAnalysis(numChannels, numNuclides);
        return static_cast<FSAHandle>(fsa);
    }
    catch (const std::exception& e)
    {
        SetLastError(std::string("FSA_Create failed: ") + e.what());
        return nullptr;
    }
}

FSA_API void FSA_Destroy(FSAHandle handle)
{
    if (handle)
    {
        FullSpectrumAnalysis* fsa = static_cast<FullSpectrumAnalysis*>(handle);
        delete fsa;
    }
}

FSA_API int FSA_AddReferenceSpectrum(
    FSAHandle handle,
    int nuclideIdx,
    const double* spectrum,
    const double* refBackground,
    int spectrumSize,
    double activity,
    double measTime,
    const char* name)
{
    if (!handle)
    {
        SetLastError("Invalid handle");
        return 0;
    }

    try
    {
        FullSpectrumAnalysis* fsa = static_cast<FullSpectrumAnalysis*>(handle);
        fsa->AddReferenceSpectrum(nuclideIdx, spectrum, refBackground,
            activity, measTime, name);
        return 1;
    }
    catch (const std::exception& e)
    {
        SetLastError(std::string("FSA_AddReferenceSpectrum failed: ") + e.what());
        return 0;
    }
}

FSA_API int FSA_AddNormalizedReference(
    FSAHandle handle,
    int nuclideIdx,
    const double* normalizedSpectrum,
    int spectrumSize,
    const char* name)
{
    if (!handle)
    {
        SetLastError("Invalid handle");
        return 0;
    }

    try
    {
        FullSpectrumAnalysis* fsa = static_cast<FullSpectrumAnalysis*>(handle);
        fsa->AddNormalizedReference(nuclideIdx, normalizedSpectrum, name);
        return 1;
    }
    catch (const std::exception& e)
    {
        SetLastError(std::string("FSA_AddNormalizedReference failed: ") + e.what());
        return 0;
    }
}

FSA_API int FSA_SetBackground(
    FSAHandle handle,
    const double* background,
    int size)
{
    if (!handle)
    {
        SetLastError("Invalid handle");
        return 0;
    }

    try
    {
        FullSpectrumAnalysis* fsa = static_cast<FullSpectrumAnalysis*>(handle);
        fsa->SetBackground(background);
        return 1;
    }
    catch (const std::exception& e)
    {
        SetLastError(std::string("FSA_SetBackground failed: ") + e.what());
        return 0;
    }
}

FSA_API int FSA_Analyze(
    FSAHandle handle,
    const double* measuredSpectrum,
    int spectrumSize,
    double measTime,
    double* activities,
    int activitiesSize)
{
    if (!handle)
    {
        SetLastError("Invalid handle");
        return 0;
    }

    try
    {
        FullSpectrumAnalysis* fsa = static_cast<FullSpectrumAnalysis*>(handle);
        fsa->Analyze(measuredSpectrum, measTime, activities);
        return 1;
    }
    catch (const std::exception& e)
    {
        SetLastError(std::string("FSA_Analyze failed: ") + e.what());
        return 0;
    }
}

FSA_API int FSA_AnalyzeQR(
    FSAHandle handle,
    const double* measuredSpectrum,
    int spectrumSize,
    double measTime,
    double* activities,
    int activitiesSize)
{
    if (!handle)
    {
        SetLastError("Invalid handle");
        return 0;
    }

    try
    {
        FullSpectrumAnalysis* fsa = static_cast<FullSpectrumAnalysis*>(handle);
        fsa->AnalyzeQR(measuredSpectrum, measTime, activities);
        return 1;
    }
    catch (const std::exception& e)
    {
        SetLastError(std::string("FSA_AnalyzeQR failed: ") + e.what());
        return 0;
    }
}

FSA_API double FSA_CalculateChiSquare(
    FSAHandle handle,
    const double* measuredSpectrum,
    int spectrumSize,
    const double* activities,
    int activitiesSize,
    double measTime)
{
    if (!handle)
    {
        SetLastError("Invalid handle");
        return -1.0;
    }

    try
    {
        FullSpectrumAnalysis* fsa = static_cast<FullSpectrumAnalysis*>(handle);
        return fsa->CalculateChiSquare(measuredSpectrum, activities, measTime);
    }
    catch (const std::exception& e)
    {
        SetLastError(std::string("FSA_CalculateChiSquare failed: ") + e.what());
        return -1.0;
    }
}

FSA_API int FSA_CalculateUncertainties(
    FSAHandle handle,
    const double* measuredSpectrum,
    int spectrumSize,
    double* uncertainties,
    int uncertaintiesSize)
{
    if (!handle)
    {
        SetLastError("Invalid handle");
        return 0;
    }

    try
    {
        FullSpectrumAnalysis* fsa = static_cast<FullSpectrumAnalysis*>(handle);
        fsa->CalculateUncertainties(measuredSpectrum, uncertainties);
        return 1;
    }
    catch (const std::exception& e)
    {
        SetLastError(std::string("FSA_CalculateUncertainties failed: ") + e.what());
        return 0;
    }
}

FSA_API const char* FSA_GetLastError()
{
    return g_LastError.c_str();
}

#ifdef _WIN32
#include <windows.h>

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
#endif