#include "FSA.h"
#include <Eigen/Dense>
#include <string>
#include <stdexcept>

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
    double a, b, c;

    EnergyCalibration() : a(0), b(1), c(0) {}
    EnergyCalibration(double a_, double b_, double c_) : a(a_), b(b_), c(c_) {}

    double ChannelToEnergy(int channel) const
    {
        return a + b * channel + c * channel * channel;
    }
};

// Area-preserving interpolation to common energy grid
class SpectrumInterpolator
{
private:
    std::vector<double> EnergyGrid;  // Common energy grid (bin edges)
    int NumBins;

public:
    SpectrumInterpolator(double energyMin, double energyMax, double energyStep)
    {
        NumBins = static_cast<int>((energyMax - energyMin) / energyStep) + 1;
        EnergyGrid.resize(NumBins);

        for (int i = 0; i < NumBins; i++)
        {
            EnergyGrid[i] = energyMin + i * energyStep;
        }
    }

    // Area-preserving interpolation
    std::vector<double> Interpolate(const double* spectrum, int spectrumSize,
        const EnergyCalibration& calibration)
    {
        size_t SourceChannels = static_cast<size_t>(spectrumSize);
        for (size_t i = 1; i < EnergyGrid.size(); ++i)
        {
            if (EnergyGrid[i] <= EnergyGrid[i - 1])
            {
                throw std::invalid_argument("Energy Grid must be strictly increasing.");
            }
        }

        size_t TargetBins = EnergyGrid.size() - 1;
        std::vector<double> TargetCounts(TargetBins, 0.0);
        std::vector<double> SourceEdges(SourceChannels + 1, 0.0);
        for (size_t ch = 0; ch <= SourceChannels; ++ch)
        {
            SourceEdges[ch] = calibration.ChannelToEnergy(static_cast<int>(ch));
        }

        // For each source bin, distribute its counts into overlapping target bins
        for (size_t src = 0; src < SourceChannels; ++src)
        {
            double SLo = SourceEdges[src];
            double SHi = SourceEdges[src + 1];

            // If degenerate or inverted (should not happen with monotonic calibration), skip
            if (!(SHi > SLo))
            {
                continue;
            }

            double SourceCounts = spectrum[src];

            // Quick rejection: if source bin entirely left or right of target grid, skip
            if (SHi <= EnergyGrid.front() || SLo >= EnergyGrid.back())
            {
                continue;
            }

            // Find starting target bin index:
            // lower_bound finds first edge >= SLo, we subtract 1 to get bin containing SLo
            auto It = std::lower_bound(EnergyGrid.begin(), EnergyGrid.end(), SLo);
            long StartBin = static_cast<long>(It - EnergyGrid.begin()) - 1;
            if (StartBin < 0)
            {
                StartBin = 0;
            }

            // Iterate target bins from StartBin until no overlap
            for (long tgt = StartBin; tgt < static_cast<long>(TargetBins); ++tgt)
            {
                double TLo = EnergyGrid[static_cast<size_t>(tgt)];
                double THi = EnergyGrid[static_cast<size_t>(tgt + 1)];

                // If target bin starts >= source high edge, no further overlaps
                if (TLo >= SHi)
                {
                    break;
                }

                // Compute overlap
                double OverlapLo = std::max(SLo, TLo);
                double OverlapHi = std::min(SHi, THi);
                double Overlap = OverlapHi - OverlapLo;

                if (Overlap > 0.0)
                {
                    double SourceBinWidth = SHi - SLo;
                    double Fraction = Overlap / SourceBinWidth;
                    TargetCounts[static_cast<size_t>(tgt)] += SourceCounts * Fraction;
                }
            }
        }
        return TargetCounts;
    }

    int GetNumBins() const { return NumBins; }

    const std::vector<double>& GetEnergyGrid() const { return EnergyGrid; }

    double GetTotalCounts(const std::vector<double>& spectrum) const
    {
        double total = 0.0;
        for (size_t i = 0; i < spectrum.size(); i++)
        {
            total += spectrum[i];
        }
        return total;
    }
};

class FullSpectrumAnalysis
{
private:
    int NumChannels;
    int NumNuclides;
    MatrixXd ReferenceMatrix;
    VectorXd Background;
    SpectrumInterpolator* Interpolator;

    // Lawson-Hanson Non-Negative Least Squares algorithm
    VectorXd SolveLawsonHansonNNLS(const MatrixXd& A, const VectorXd& b, bool useQR = true)
    {
        const int m = A.rows();  // Number of channels
        const int n = A.cols();  // Number of nuclides
        const double tolerance = 1e-10;
        const int maxIterations = 3 * n;

        VectorXd x = VectorXd::Zero(n);  // Solution vector
        std::vector<bool> passiveSet(n, false);  // True if variable is in passive set

        for (int mainIter = 0; mainIter < maxIterations; mainIter++)
        {
            // Step 1: Compute gradient w = A^T * (b - A*x)
            VectorXd residual = b - A * x;
            VectorXd w = A.transpose() * residual;

            // Step 2: Check optimality conditions
            // Find maximum gradient component in active set (where x = 0)
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

            // If all gradients for active constraints are <= 0, we're done
            if (maxGradIdx == -1)
            {
                break;
            }

            // Step 3: Move variable with largest gradient to passive set
            passiveSet[maxGradIdx] = true;

            // Step 4: Solve least squares with passive variables
            while (true)
            {
                // Build list of passive indices
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

                // Build submatrix with only passive columns
                MatrixXd Ap(m, np);
                for (int i = 0; i < np; i++)
                {
                    Ap.col(i) = A.col(passiveIdx[i]);
                }

                // Solve unconstrained least squares for passive variables
                VectorXd sp;
                if (useQR)
                {
                    // QR decomposition - more stable, especially for ill-conditioned problems
                    sp = Ap.colPivHouseholderQr().solve(b);
                }
                else
                {
                    // Normal equations - faster but less stable
                    sp = (Ap.transpose() * Ap).ldlt().solve(Ap.transpose() * b);
                }

                // Check if all passive variables are non-negative
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
                    // Accept solution
                    x.setZero();
                    for (int i = 0; i < np; i++)
                    {
                        x(passiveIdx[i]) = sp(i);
                    }
                    break;
                }

                // Step 5: Interpolation to find constraint that blocks the way
                // Find alpha = min { x_i / (x_i - s_i) : s_i < 0 }
                double alpha = 1.0;
                int blockingIdx = -1;

                for (int i = 0; i < np; i++)
                {
                    int idx = passiveIdx[i];
                    if (sp(i) <= 0)
                    {
                        double denominator = x(idx) - sp(i);
                        if (std::abs(denominator) < 1e-15) continue;
                        double ratio = x(idx) / denominator;
                        if (ratio < alpha)
                        {
                            alpha = ratio;
                            blockingIdx = idx;
                        }
                    }
                }

                // Interpolate: x_new = x + alpha * (s - x)
                VectorXd xNew = VectorXd::Zero(n);
                for (int i = 0; i < np; i++)
                {
                    int idx = passiveIdx[i];
                    xNew(idx) = x(idx) + alpha * (sp(i) - x(idx));

                    // Ensure numerical stability
                    if (std::abs(xNew(idx)) < tolerance)
                    {
                        xNew(idx) = 0.0;
                    }
                }
                x = xNew;

                // Move blocking variable back to active set
                if (blockingIdx >= 0)
                {
                    passiveSet[blockingIdx] = false;
                }
                else
                {
                    // Shouldn't happen, but safety break
                    break;
                }
            }
        }

        // Final cleanup: ensure all values are non-negative
        for (int i = 0; i < n; i++)
        {
            if (x(i) < 0)
            {
                x(i) = 0.0;
            }
        }

        return x;
    }

    void AnalyzeNNLS(const double* measuredSpectrum, double measTime, double* activities)
    {
        VectorXd measured(NumChannels);
        for (int i = 0; i < NumChannels; i++)
        {
            measured(i) = measuredSpectrum[i];
        }
        MatrixXd scaledReference = ReferenceMatrix * measTime;
        MatrixXd designMatrix = MatrixXd(NumChannels, NumNuclides + 1);
        designMatrix.leftCols(NumNuclides) = scaledReference;
        designMatrix.col(NumNuclides) = Background * measTime;
        const VectorXd result = SolveLawsonHansonNNLS(designMatrix, measured, true);
        for (int i = 0; i < NumNuclides; i++)
        {
            activities[i] = result(i);
        }
    }

public:
    FullSpectrumAnalysis(double energyMin, double energyMax, double energyStep, int nuclides)
        : NumNuclides(nuclides)
    {
        Interpolator = new SpectrumInterpolator(energyMin, energyMax, energyStep);
        NumChannels = Interpolator->GetNumBins();
        ReferenceMatrix = MatrixXd::Zero(NumChannels, nuclides);
        Background = VectorXd::Zero(NumChannels);
    }

    ~FullSpectrumAnalysis()
    {
        if (Interpolator)
        {
            delete Interpolator;
        }
    }

    void AddReferenceSpectrum(
        int nuclideIdx,
        const double* spectrum,
        int spectrumSize,
        const EnergyCalibration& calibration,
        double activity,
        double measTime)
    {
        if (!Interpolator)
        {
            throw std::runtime_error("Energy mode not enabled");
        }
        if (nuclideIdx < 0 || nuclideIdx >= NumNuclides)
        {
            throw std::out_of_range("Nuclide index out of range");
        }
        std::vector<double> interpSpec = Interpolator->Interpolate(spectrum, spectrumSize, calibration);
        for (int i = 0; i < NumChannels; i++)
        {
            ReferenceMatrix(i, nuclideIdx) = interpSpec[i] < 0 ? 0 : (interpSpec[i] / (activity * measTime));
        }
    }

    void SetBackground(
        const double* background,
        int backgroundSize,
        const EnergyCalibration& calibration,
        double measTime)
    {
        if (!Interpolator)
        {
            throw std::runtime_error("Energy mode not enabled");
        }
        std::vector<double> interpBg = Interpolator->Interpolate(background, backgroundSize, calibration);
        for (int i = 0; i < NumChannels; i++)
        {
            Background(i) = interpBg[i] < 0 ? 0 : (interpBg[i] / measTime);
        }
    }

    void Analyze(
        const double* measuredSpectrum,
        int spectrumSize,
        const EnergyCalibration& calibration,
        double measTime,
        double* activities)
    {
        if (!Interpolator)
        {
            throw std::runtime_error("Energy mode not enabled");
        }

        const std::vector<double> &interpSpec = Interpolator->Interpolate(measuredSpectrum, spectrumSize, calibration);

        AnalyzeNNLS(interpSpec.data(), measTime, activities);
    }

    double GetInterpolatedTotalCounts(
        const double* spectrum,
        int spectrumSize,
        const EnergyCalibration& calibration,
        double** interpSpectrum,
        int* interpSpectrumSize)
    {
        if (!Interpolator)
        {
            SetLastError("Energy mode not enabled");
            return -1.0;
        }

        const std::vector<double> &interpSpec = Interpolator->Interpolate(spectrum, spectrumSize, calibration);
        *interpSpectrumSize = static_cast<int>(interpSpec.size());
        *interpSpectrum = new double[interpSpec.size()];
        for (size_t i = 0; i < interpSpec.size(); i++)
        {
            (*interpSpectrum)[i] = interpSpec[i];
        }

        return Interpolator->GetTotalCounts(interpSpec);
    }

    double GetBackgroundScale(const double* measuredSpectrum, double measTime)
    {
        VectorXd measured(NumChannels);
        for (int i = 0; i < NumChannels; i++)
        {
            measured(i) = measuredSpectrum[i];
        }

        MatrixXd scaledReference = ReferenceMatrix * measTime;
        MatrixXd designMatrix(NumChannels, NumNuclides + 1);
        designMatrix.leftCols(NumNuclides) = scaledReference;
        designMatrix.col(NumNuclides) = Background * measTime;

        VectorXd result = (designMatrix.transpose() * designMatrix)
            .ldlt()
            .solve(designMatrix.transpose() * measured);

        return result(NumNuclides);
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
        MatrixXd designMatrix(NumChannels, NumNuclides + 1);
        designMatrix.leftCols(NumNuclides) = scaledReference;
        designMatrix.col(NumNuclides) = Background * measTime;
        const VectorXd &llsq_coeffs = (designMatrix.transpose() * designMatrix)
            .ldlt()
            .solve(designMatrix.transpose() * measured);

        // Build the expected spectrum using the LLSQ-derived coefficients
        // llsq_coeffs contains activities for nuclides (0 to NumNuclides-1) and background scale (NumNuclides)
        const VectorXd expected = designMatrix * llsq_coeffs;

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
        g_LastError.clear();
        SetLastError("Uncertainty calculation for NNLS is not supported with current implementation.");
        for (int i = 0; i < NumNuclides; ++i) {
            uncertainties[i] = 0.0; // Or some other default/error value
        }
    }
};

// ============================================================================
// C API Implementation
// ============================================================================

FSA_API FSAHandle FSA_Create(double energyMin, double energyMax,
    double energyStep, int numNuclides)
{
    g_LastError.clear();
    try
    {
        FullSpectrumAnalysis* fsa = new FullSpectrumAnalysis(
            energyMin, energyMax, energyStep, numNuclides);
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
    g_LastError.clear();
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
    int spectrumSize,
    const FSACalibration* calibration,
    double activity,
    double measTime)
{
    g_LastError.clear();
    if (!handle || !calibration)
    {
        SetLastError("Invalid handle or calibration");
        return 0;
    }

    try
    {
        FullSpectrumAnalysis* fsa = static_cast<FullSpectrumAnalysis*>(handle);
        EnergyCalibration cal(calibration->a, calibration->b, calibration->c);
        fsa->AddReferenceSpectrum(nuclideIdx, spectrum, spectrumSize, cal, activity, measTime);
        return 1;
    }
    catch (const std::exception& e)
    {
        SetLastError(std::string("FSA_AddReferenceSpectrumWithCalibration failed: ") + e.what());
        return 0;
    }
}

FSA_API int FSA_SetBackground(
    FSAHandle handle,
    const double* background,
    int backgroundSize,
    const FSACalibration* calibration,
    double measTime)
{
    g_LastError.clear();
    if (!handle || !calibration)
    {
        SetLastError("Invalid handle or calibration");
        return 0;
    }

    try
    {
        FullSpectrumAnalysis* fsa = static_cast<FullSpectrumAnalysis*>(handle);
        EnergyCalibration cal(calibration->a, calibration->b, calibration->c);
        fsa->SetBackground(background, backgroundSize, cal, measTime);
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
    g_LastError.clear();
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

FSA_API double FSA_GetInterpolatedTotalCounts(
    FSAHandle handle,
    const double* spectrum,
    int spectrumSize,
    const FSACalibration* calibration,
    double** interpSpectrum,
    int* interpSpectrumSize)
{
    g_LastError.clear();
    if (!handle || !calibration)
    {
        SetLastError("Invalid handle or calibration");
        return -1.0;
    }

    try
    {
        FullSpectrumAnalysis* fsa = static_cast<FullSpectrumAnalysis*>(handle);
        EnergyCalibration cal(calibration->a, calibration->b, calibration->c);
        return fsa->GetInterpolatedTotalCounts(spectrum, spectrumSize, cal, interpSpectrum, interpSpectrumSize);
    }
    catch (const std::exception& e)
    {
        SetLastError(std::string("FSA_GetInterpolatedTotalCounts failed: ") + e.what());
        return -1.0;
    }
}

FSA_API double FSA_GetBackgroundScale(
    FSAHandle handle,
    const double* measuredSpectrum,
    double measTime)
{
    g_LastError.clear();
    if (!handle)
    {
        SetLastError("Invalid handle");
        return -1.0;
    }

    try
    {
        FullSpectrumAnalysis* fsa = static_cast<FullSpectrumAnalysis*>(handle);
        return fsa->GetBackgroundScale(measuredSpectrum, measTime);
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
    const double* activities,
    double measTime)
{
    g_LastError.clear();
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
    double* uncertainties)
{
    g_LastError.clear();
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

FSA_API void FSA_FreeMemory(void* buffer)
{
    g_LastError.clear();
    delete[] static_cast<double*>(buffer);
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