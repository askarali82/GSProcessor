#include "FSA.h"
#include <Eigen/Dense>
#include <string>
#include <vector>
#include <stdexcept>
#include <cmath>
#include <algorithm>
#include <map>

using Eigen::MatrixXd;
using Eigen::VectorXd;

static thread_local std::string g_LastError;

void SetLastError(const std::string& error)
{
    g_LastError = error;
}

class EnergyCalibration
{
public:
    double a, b, c;  // E = a + b*C + c*C²

    EnergyCalibration() : a(0), b(1), c(0) {}
    EnergyCalibration(double a_, double b_, double c_) : a(a_), b(b_), c(c_) {}

    double ChannelToEnergy(int channel) const
    {
        return a + b * channel + c * channel * channel;
    }

    // Inverse: Energy to channel (for binary search)
    double EnergyToChannel(double energy) const
    {
        if (std::abs(c) < 1e-12)  // Linear calibration
        {
            return (energy - a) / b;
        }

        // Quadratic formula: C = (-b ± sqrt(b² - 4c(a-E))) / (2c)
        double discriminant = b * b - 4.0 * c * (a - energy);

        if (discriminant < 0)
        {
            return -1;
        }

        // Take positive root
        double ch1 = (-b + std::sqrt(discriminant)) / (2.0 * c);
        double ch2 = (-b - std::sqrt(discriminant)) / (2.0 * c);

        if (ch1 >= 0 && ch1 < 100000) return ch1;
        if (ch2 >= 0 && ch2 < 100000) return ch2;

        return -1;
    }
};

// Structure to hold a spectrum with its calibration
struct SpectrumWithCalibration
{
    std::vector<double> Counts;
    EnergyCalibration Cal;
    int NumChannels;

    SpectrumWithCalibration() : NumChannels(0) {}

    SpectrumWithCalibration(const double* counts, int size, const EnergyCalibration& cal)
        : Counts(counts, counts + size), Cal(cal), NumChannels(size) {
    }

    double GetEnergyStart(int channel) const
    {
        return Cal.ChannelToEnergy(channel);
    }

    double GetEnergyEnd(int channel) const
    {
        return Cal.ChannelToEnergy(channel + 1);
    }
};

// Energy-aware overlap calculator
class EnergyOverlapCalculator
{
private:
    static const double EPSILON;

public:
    struct OverlapInfo
    {
        int RefChannel;
        double Fraction;
    };

    static std::vector<OverlapInfo> FindOverlaps(
        double energyStart,
        double energyEnd,
        const SpectrumWithCalibration& reference)
    {
        std::vector<OverlapInfo> overlaps;

        int startChannel = FindStartChannel(reference, energyStart);
        int endChannel = FindEndChannel(reference, energyEnd);

        for (int refCh = startChannel; refCh <= endChannel && refCh < reference.NumChannels; refCh++)
        {
            double refStart = reference.GetEnergyStart(refCh);
            double refEnd = reference.GetEnergyEnd(refCh);

            double overlapStart = std::max(energyStart, refStart);
            double overlapEnd = std::min(energyEnd, refEnd);

            if (overlapEnd > overlapStart + EPSILON)
            {
                double overlapWidth = overlapEnd - overlapStart;
                double refWidth = refEnd - refStart;

                if (refWidth > EPSILON)
                {
                    OverlapInfo info;
                    info.RefChannel = refCh;
                    info.Fraction = overlapWidth / refWidth;
                    overlaps.push_back(info);
                }
            }
        }

        return overlaps;
    }

private:
    static int FindStartChannel(const SpectrumWithCalibration& spectrum, double energy)
    {
        double approxChannel = spectrum.Cal.EnergyToChannel(energy);

        if (approxChannel < 0)
        {
            return 0;
        }

        int start = std::max(0, (int)approxChannel - 10);
        int end = std::min(spectrum.NumChannels - 1, (int)approxChannel + 10);

        while (start < end)
        {
            int mid = (start + end) / 2;
            double midEnergy = spectrum.GetEnergyEnd(mid);

            if (midEnergy < energy)
            {
                start = mid + 1;
            }
            else
            {
                end = mid;
            }
        }

        return std::max(0, start - 1);
    }

    static int FindEndChannel(const SpectrumWithCalibration& spectrum, double energy)
    {
        double approxChannel = spectrum.Cal.EnergyToChannel(energy);

        if (approxChannel < 0 || approxChannel >= spectrum.NumChannels)
        {
            return spectrum.NumChannels - 1;
        }

        int start = std::max(0, (int)approxChannel - 10);
        int end = std::min(spectrum.NumChannels - 1, (int)approxChannel + 10);

        while (start < end)
        {
            int mid = (start + end + 1) / 2;
            double midEnergy = spectrum.GetEnergyStart(mid);

            if (midEnergy <= energy)
            {
                start = mid;
            }
            else
            {
                end = mid - 1;
            }
        }

        return std::min(spectrum.NumChannels - 1, end + 1);
    }
};

const double EnergyOverlapCalculator::EPSILON = 1e-9;

// Main FSA class
class FullSpectrumAnalysis
{
private:
    int NumNuclides;
    std::vector<SpectrumWithCalibration> References;
    std::vector<double> Activities;
    std::vector<double> MeasTimes;
    SpectrumWithCalibration Background;

public:
    FullSpectrumAnalysis(int numNuclides)
        : NumNuclides(numNuclides)
    {
        References.resize(numNuclides);
        Activities.resize(numNuclides, 0.0);
        MeasTimes.resize(numNuclides, 0.0);
    }

    void AddReference(int nuclideIdx,
        const double* spectrum,
        int spectrumSize,
        const EnergyCalibration& calibration,
        double activity,
        double measTime)
    {
        if (nuclideIdx < 0 || nuclideIdx >= NumNuclides)
        {
            throw std::out_of_range("Nuclide index out of range");
        }

        References[nuclideIdx] = SpectrumWithCalibration(spectrum, spectrumSize, calibration);
        Activities[nuclideIdx] = activity;
        MeasTimes[nuclideIdx] = measTime;
    }

    void SetBackground(const double* background,
        int backgroundSize,
        const EnergyCalibration& calibration)
    {
        Background = SpectrumWithCalibration(background, backgroundSize, calibration);
    }

    MatrixXd BuildDesignMatrix(const SpectrumWithCalibration& measured, double measTime)
    {
        int M = measured.NumChannels;
        int N = NumNuclides;

        MatrixXd A(M, N);

        for (int m = 0; m < M; m++)
        {
            double measEnergyStart = measured.GetEnergyStart(m);
            double measEnergyEnd = measured.GetEnergyEnd(m);

            for (int n = 0; n < N; n++)
            {
                const SpectrumWithCalibration& ref = References[n];
                double refActivity = Activities[n];
                double refMeasTime = MeasTimes[n];

                auto overlaps = EnergyOverlapCalculator::FindOverlaps(
                    measEnergyStart, measEnergyEnd, ref);

                double totalContribution = 0.0;

                for (const auto& overlap : overlaps)
                {
                    int refCh = overlap.RefChannel;
                    double fraction = overlap.Fraction;

                    double refCounts = ref.Counts[refCh];
                    double normalizedCounts = refCounts / (refActivity * refMeasTime);

                    totalContribution += fraction * normalizedCounts;
                }

                A(m, n) = totalContribution * measTime;
            }
        }

        return A;
    }

    VectorXd CalculateBackgroundContribution(const SpectrumWithCalibration& measured)
    {
        int M = measured.NumChannels;
        VectorXd bgContribution(M);

        if (Background.NumChannels == 0)
        {
            bgContribution.setZero();
            return bgContribution;
        }

        for (int m = 0; m < M; m++)
        {
            double measEnergyStart = measured.GetEnergyStart(m);
            double measEnergyEnd = measured.GetEnergyEnd(m);

            auto overlaps = EnergyOverlapCalculator::FindOverlaps(
                measEnergyStart, measEnergyEnd, Background);

            double totalBg = 0.0;

            for (const auto& overlap : overlaps)
            {
                int bgCh = overlap.RefChannel;
                double fraction = overlap.Fraction;

                totalBg += fraction * Background.Counts[bgCh];
            }

            bgContribution(m) = totalBg;
        }

        return bgContribution;
    }

    // Lawson-Hanson NNLS algorithm
    VectorXd SolveLawsonHansonNNLS(const MatrixXd& A, const VectorXd& b)
    {
        const int m = A.rows();
        const int n = A.cols();
        const double tolerance = 1e-10;
        const int maxIterations = 3 * n;

        VectorXd x = VectorXd::Zero(n);
        std::vector<bool> passiveSet(n, false);

        for (int mainIter = 0; mainIter < maxIterations; mainIter++)
        {
            VectorXd residual = b - A * x;
            VectorXd w = A.transpose() * residual;

            int maxGradIdx = -1;
            double maxGrad = tolerance;

            for (int i = 0; i < n; i++)
            {
                if (!passiveSet[i] && w(i) > maxGrad)
                {
                    maxGrad = w(i);
                    maxGradIdx = i;
                }
            }

            if (maxGradIdx == -1)
            {
                break;
            }

            passiveSet[maxGradIdx] = true;

            while (true)
            {
                std::vector<int> passiveIdx;
                for (int i = 0; i < n; i++)
                {
                    if (passiveSet[i])
                    {
                        passiveIdx.push_back(i);
                    }
                }

                int np = passiveIdx.size();
                if (np == 0) break;

                MatrixXd Ap(m, np);
                for (int i = 0; i < np; i++)
                {
                    Ap.col(i) = A.col(passiveIdx[i]);
                }

                VectorXd sp = Ap.colPivHouseholderQr().solve(b);

                bool allPositive = true;
                for (int i = 0; i < np; i++)
                {
                    if (sp(i) < -tolerance)
                    {
                        allPositive = false;
                        break;
                    }
                }

                if (allPositive)
                {
                    x.setZero();
                    for (int i = 0; i < np; i++)
                    {
                        x(passiveIdx[i]) = sp(i);
                    }
                    break;
                }

                double alpha = 1.0;
                int blockingIdx = -1;

                for (int i = 0; i < np; i++)
                {
                    int idx = passiveIdx[i];
                    if (sp(i) <= 0)
                    {
                        double ratio = x(idx) / (x(idx) - sp(i));
                        if (ratio < alpha)
                        {
                            alpha = ratio;
                            blockingIdx = idx;
                        }
                    }
                }

                VectorXd xNew = VectorXd::Zero(n);
                for (int i = 0; i < np; i++)
                {
                    int idx = passiveIdx[i];
                    xNew(idx) = x(idx) + alpha * (sp(i) - x(idx));

                    if (std::abs(xNew(idx)) < tolerance)
                    {
                        xNew(idx) = 0.0;
                    }
                }
                x = xNew;

                if (blockingIdx >= 0)
                {
                    passiveSet[blockingIdx] = false;
                }
                else
                {
                    break;
                }
            }
        }

        for (int i = 0; i < n; i++)
        {
            if (x(i) < 0)
            {
                x(i) = 0.0;
            }
        }

        return x;
    }

    void Analyze(const double* measuredSpectrum,
        int spectrumSize,
        const EnergyCalibration& calibration,
        double measTime,
        double* activities)
    {
        SpectrumWithCalibration measured(measuredSpectrum, spectrumSize, calibration);
        MatrixXd A = BuildDesignMatrix(measured, measTime);
        VectorXd bgContribution = CalculateBackgroundContribution(measured);

        VectorXd b(spectrumSize);
        for (int i = 0; i < spectrumSize; i++)
        {
            b(i) = measuredSpectrum[i];
        }

        // Always use background as component
        MatrixXd designMatrix(spectrumSize, NumNuclides + 1);
        designMatrix.leftCols(NumNuclides) = A;
        designMatrix.col(NumNuclides) = bgContribution;

        VectorXd result = SolveLawsonHansonNNLS(designMatrix, b);

        for (int i = 0; i < NumNuclides; i++)
        {
            activities[i] = result(i);
        }
    }

    double GetBackgroundScale(const double* measuredSpectrum,
        int spectrumSize,
        const EnergyCalibration& calibration,
        double measTime)
    {
        SpectrumWithCalibration measured(measuredSpectrum, spectrumSize, calibration);
        MatrixXd A = BuildDesignMatrix(measured, measTime);
        VectorXd bgContribution = CalculateBackgroundContribution(measured);

        VectorXd b(spectrumSize);
        for (int i = 0; i < spectrumSize; i++)
        {
            b(i) = measuredSpectrum[i];
        }

        MatrixXd designMatrix(spectrumSize, NumNuclides + 1);
        designMatrix.leftCols(NumNuclides) = A;
        designMatrix.col(NumNuclides) = bgContribution;

        VectorXd result = SolveLawsonHansonNNLS(designMatrix, b);

        return result(NumNuclides);  // Last element is background scale
    }

    double CalculateChiSquare(const double* measuredSpectrum,
        int spectrumSize,
        const EnergyCalibration& calibration,
        const double* activities,
        double measTime)
    {
        SpectrumWithCalibration measured(measuredSpectrum, spectrumSize, calibration);
        MatrixXd A = BuildDesignMatrix(measured, measTime);
        VectorXd bgContribution = CalculateBackgroundContribution(measured);

        // Recalculate to get background scale
        VectorXd b(spectrumSize);
        for (int i = 0; i < spectrumSize; i++)
        {
            b(i) = measuredSpectrum[i];
        }

        MatrixXd designMatrix(spectrumSize, NumNuclides + 1);
        designMatrix.leftCols(NumNuclides) = A;
        designMatrix.col(NumNuclides) = bgContribution;

        VectorXd result = SolveLawsonHansonNNLS(designMatrix, b);
        double bgScale = result(NumNuclides);

        // Calculate expected spectrum
        VectorXd act(NumNuclides);
        for (int i = 0; i < NumNuclides; i++)
        {
            act(i) = activities[i];
        }

        VectorXd expected = A * act + bgScale * bgContribution;

        // Chi-square
        double chi2 = 0.0;
        for (int i = 0; i < spectrumSize; i++)
        {
            double diff = measured.Counts[i] - expected(i);
            double variance = std::max(measured.Counts[i], 1.0);
            chi2 += (diff * diff) / variance;
        }

        return chi2;
    }
};

// ============================================================================
// C API Implementation
// ============================================================================

FSA_API FSAHandle FSA_Create(int numNuclides)
{
    try
    {
        FullSpectrumAnalysis* fsa = new FullSpectrumAnalysis(numNuclides);
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

FSA_API int FSA_AddReference(
    FSAHandle handle,
    int nuclideIdx,
    const double* spectrum,
    int spectrumSize,
    const FSACalibration* calibration,
    double activity,
    double measTime)
{
    if (!handle || !calibration)
    {
        SetLastError("Invalid handle or calibration");
        return 0;
    }

    try
    {
        FullSpectrumAnalysis* fsa = static_cast<FullSpectrumAnalysis*>(handle);
        EnergyCalibration cal(calibration->a, calibration->b, calibration->c);
        fsa->AddReference(nuclideIdx, spectrum, spectrumSize, cal, activity, measTime);
        return 1;
    }
    catch (const std::exception& e)
    {
        SetLastError(std::string("FSA_AddReference failed: ") + e.what());
        return 0;
    }
}

FSA_API int FSA_SetBackground(
    FSAHandle handle,
    const double* background,
    int backgroundSize,
    const FSACalibration* calibration)
{
    if (!handle || !calibration)
    {
        SetLastError("Invalid handle or calibration");
        return 0;
    }

    try
    {
        FullSpectrumAnalysis* fsa = static_cast<FullSpectrumAnalysis*>(handle);
        EnergyCalibration cal(calibration->a, calibration->b, calibration->c);
        fsa->SetBackground(background, backgroundSize, cal);
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
    const FSACalibration* calibration,
    double measTime,
    double* activities,
    int activitiesSize)
{
    if (!handle || !calibration)
    {
        SetLastError("Invalid handle or calibration");
        return 0;
    }

    try
    {
        FullSpectrumAnalysis* fsa = static_cast<FullSpectrumAnalysis*>(handle);
        EnergyCalibration cal(calibration->a, calibration->b, calibration->c);
        fsa->Analyze(measuredSpectrum, spectrumSize, cal, measTime, activities);
        return 1;
    }
    catch (const std::exception& e)
    {
        SetLastError(std::string("FSA_Analyze failed: ") + e.what());
        return 0;
    }
}

FSA_API double FSA_GetBackgroundScale(
    FSAHandle handle,
    const double* measuredSpectrum,
    int spectrumSize,
    const FSACalibration* calibration,
    double measTime)
{
    if (!handle || !calibration)
    {
        SetLastError("Invalid handle or calibration");
        return -1.0;
    }

    try
    {
        FullSpectrumAnalysis* fsa = static_cast<FullSpectrumAnalysis*>(handle);
        EnergyCalibration cal(calibration->a, calibration->b, calibration->c);
        return fsa->GetBackgroundScale(measuredSpectrum, spectrumSize, cal, measTime);
    }
    catch (const std::exception& e)
    {
        SetLastError(std::string("FSA_GetBackgroundScale failed: ") + e.what());
        return -1.0;
    }
}

FSA_API double FSA_CalculateChiSquare(
    FSAHandle handle,
    const double* measuredSpectrum,
    int spectrumSize,
    const FSACalibration* calibration,
    const double* activities,
    int activitiesSize,
    double measTime)
{
    if (!handle || !calibration)
    {
        SetLastError("Invalid handle or calibration");
        return -1.0;
    }

    try
    {
        FullSpectrumAnalysis* fsa = static_cast<FullSpectrumAnalysis*>(handle);
        EnergyCalibration cal(calibration->a, calibration->b, calibration->c);
        return fsa->CalculateChiSquare(measuredSpectrum, spectrumSize, cal,
            activities, measTime);
    }
    catch (const std::exception& e)
    {
        SetLastError(std::string("FSA_CalculateChiSquare failed: ") + e.what());
        return -1.0;
    }
}

FSA_API const char* FSA_GetLastError()
{
    return g_LastError.c_str();
}

// ============================================================================
// DLL Entry Point
// ============================================================================
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