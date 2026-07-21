// PhotopeakSearcher.cpp
// Implementation of photopeak searching using ROOT TSpectrum

#define PHOTOPEAKSEARCHER_EXPORTS
#include "PhotopeakSearcher_Internal.h"  // Internal class declaration
#include <TH1F.h>
#include <TSpectrum.h>
#include <TF1.h>
#include <TMath.h>
#include <memory>
#include <algorithm>
#include <cmath>
#include <atomic>

// Constructor
CPhotopeakSearcher::CPhotopeakSearcher()
    : FChannelCount(0)
    , FCalibrationA0(0.0)
    , FCalibrationA1(1.0)
    , FCalibrationA2(0.0)
    , FIsCalibrated(false)
    , FResolutionA(0.0)
    , FResolutionB(0.0)
    , FResolutionCalibrated(false)
    , FSigma(6.5)              // Default sigma for TSpectrum in channels
    , FThreshold(0.005)         // 0.5% threshold
    , FMaxPeaks(200)            // Search up to 50 peaks
    , FUseBackground(true)
    , FBackgroundIterations(20)
    , FPerformGaussianFit(false)
    , FFitRangeSigma(3.0)      // Fit ±3 sigma around peak
    , FUseHighResSearch(true)  // Use SearchHighRes by default (better for gamma spectra)
{
}

// Destructor
CPhotopeakSearcher::~CPhotopeakSearcher()
{
    Clear();
}

// Load spectrum from double array
bool CPhotopeakSearcher::LoadSpectrum(const double* spectrumData, int channelCount)
{
    if (spectrumData == nullptr || channelCount <= 0)
    {
        return false;
    }

    FChannelCount = channelCount;
    FSpectrumData.assign(spectrumData, spectrumData + channelCount);
    FFoundPeaks.clear();

    return true;
}

// Load spectrum from integer array
bool CPhotopeakSearcher::LoadSpectrum(const int* spectrumData, int channelCount)
{
    if (spectrumData == nullptr || channelCount <= 0)
    {
        return false;
    }

    FChannelCount = channelCount;
    FSpectrumData.resize(channelCount);

    for (int i = 0; i < channelCount; i++)
    {
        FSpectrumData[i] = static_cast<double>(spectrumData[i]);
    }

    FFoundPeaks.clear();
    return true;
}

// Set energy calibration (supports linear and quadratic)
void CPhotopeakSearcher::SetCalibration(double a0, double a1, double a2)
{
    FCalibrationA0 = a0;
    FCalibrationA1 = a1;
    FCalibrationA2 = a2;
    FIsCalibrated = true;
}

// Clear calibration
void CPhotopeakSearcher::ClearCalibration()
{
    FCalibrationA0 = 0.0;
    FCalibrationA1 = 1.0;
    FCalibrationA2 = 0.0;
    FIsCalibrated = false;
}

// Set resolution parameters directly
void CPhotopeakSearcher::SetResolution(double a, double b)
{
    FResolutionA = a;
    FResolutionB = b;
    FResolutionCalibrated = true;
}

// Calculate resolution parameters from two measurements
void CPhotopeakSearcher::SetResolutionFromMeasurements(double fwhm1_keV, double energy1_keV,
    double fwhm2_keV, double energy2_keV)
{
    // FWHM² = a + b×E
    // Solve for a and b from two points
    double fwhm1_sq = fwhm1_keV * fwhm1_keV;
    double fwhm2_sq = fwhm2_keV * fwhm2_keV;

    FResolutionB = (fwhm2_sq - fwhm1_sq) / (energy2_keV - energy1_keV);
    FResolutionA = fwhm1_sq - FResolutionB * energy1_keV;

    FResolutionCalibrated = true;
}

// Set resolution from percentage at reference energy (simplified)
void CPhotopeakSearcher::SetResolutionFromPercentage(double resolutionPercent, double referenceEnergy)
{
    // For simplified case, assume a ≈ 0 and calculate b
    // FWHM = resolution% × energy
    double fwhm_ref = (resolutionPercent / 100.0) * referenceEnergy;

    // Use two points for better accuracy
    // Point 1: Low energy (assume resolution degrades)
    double e1 = referenceEnergy * 0.3;  // 30% of reference
    double fwhm1 = fwhm_ref * 1.2;      // Assume 20% worse at low E

    // Point 2: Reference energy
    double e2 = referenceEnergy;
    double fwhm2 = fwhm_ref;

    SetResolutionFromMeasurements(fwhm1, e1, fwhm2, e2);
}

// Clear resolution calibration
void CPhotopeakSearcher::ClearResolution()
{
    FResolutionA = 0.0;
    FResolutionB = 0.0;
    FResolutionCalibrated = false;
}

// Calculate FWHM at given energy using resolution function
double CPhotopeakSearcher::CalculateFWHMAtEnergy(double energy_keV) const
{
    if (!FResolutionCalibrated || energy_keV <= 0.0)
    {
        // Fallback: use simplified sqrt(E) scaling
        if (FIsCalibrated && FCalibrationA1 > 0.0)
        {
            // Estimate from FSigma (which is in channels)
            double sigma_keV_ref = FSigma * FCalibrationA1;  // Convert to keV at reference
            double fwhm_ref = sigma_keV_ref * 2.355;
            return fwhm_ref * std::sqrt(energy_keV / 662.0);
        }
        else
        {
            // Very rough estimate
            return (energy_keV * 0.07);  // Assume 7% resolution
        }
    }

    // Use proper resolution function: FWHM(E) = √(a + b×E)
    double value = FResolutionA + FResolutionB * energy_keV;

    if (value < 0.0)
    {
        value = 0.0;  // Prevent negative values
    }

    return std::sqrt(value);
}

// Convert channel to energy (quadratic calibration)
double CPhotopeakSearcher::ChannelToEnergy(double channel) const
{
    return FCalibrationA0 + FCalibrationA1 * channel + FCalibrationA2 * channel * channel;
}

// Convert energy to channel (quadratic calibration - uses quadratic formula)
double CPhotopeakSearcher::EnergyToChannel(double energy) const
{
    if (FCalibrationA2 != 0.0)
    {
        // Quadratic: A2*ch^2 + A1*ch + (A0 - E) = 0
        // Solution: ch = (-A1 + sqrt(A1^2 - 4*A2*(A0-E))) / (2*A2)
        double discriminant = FCalibrationA1 * FCalibrationA1 -
            4.0 * FCalibrationA2 * (FCalibrationA0 - energy);

        if (discriminant >= 0.0)
        {
            // Take positive root for physical solution
            return (-FCalibrationA1 + std::sqrt(discriminant)) / (2.0 * FCalibrationA2);
        }
        return 0.0;
    }
    else if (FCalibrationA1 != 0.0)
    {
        // Linear case
        return (energy - FCalibrationA0) / FCalibrationA1;
    }

    return 0.0;
}

// Calculate FWHM from sigma
double CPhotopeakSearcher::CalculateFWHM(double sigma)
{
    // FWHM = 2.355 * sigma for Gaussian peaks
    return 2.355 * sigma;
}

// Calculate peak area using integration
double CPhotopeakSearcher::CalculatePeakArea(const std::vector<double>& data,
    double position, double sigma)
{
    int posInt = static_cast<int>(position);
    int leftBound = std::max(0, posInt - static_cast<int>(3.0 * sigma));
    int rightBound = std::min(static_cast<int>(data.size()) - 1,
        posInt + static_cast<int>(3.0 * sigma));

    double area = 0.0;
    for (int i = leftBound; i <= rightBound; i++)
    {
        area += data[i];
    }

    return area;
}

// Fit Gaussian function to a peak
bool CPhotopeakSearcher::FitGaussianToPeak(PhotopeakInfo& peak)
{
    if (FSpectrumData.empty() || FChannelCount <= 0)
    {
        return false;
    }

    // Define fit range
    double fitRangeHalfWidth = FFitRangeSigma * peak.Sigma;
    int leftBin = std::max(0, static_cast<int>(peak.Position - fitRangeHalfWidth));
    int rightBin = std::min(FChannelCount - 1,
        static_cast<int>(peak.Position + fitRangeHalfWidth));

    if (rightBin <= leftBin + 3)
    {
        return false; // Not enough points for fitting
    }

    // Calculate sum of data in the region to validate
    double sumData = 0.0;
    for (int i = leftBin; i <= rightBin; i++)
    {
        sumData += FSpectrumData[i];
    }

    if (sumData < 10.0)
    {
        return false; // Too few counts for reliable fitting
    }

    // Manual Gaussian fit using least squares (avoid ROOT GUI issues)
    // This is more stable for batch processing without graphics

    int nPoints = rightBin - leftBin + 1;
    std::vector<double> x(nPoints);
    std::vector<double> y(nPoints);
    std::vector<double> w(nPoints);

    // Prepare data points
    for (int i = 0; i < nPoints; i++)
    {
        x[i] = leftBin + i;
        y[i] = FSpectrumData[leftBin + i];
        w[i] = (y[i] > 0) ? 1.0 / std::sqrt(y[i]) : 1.0; // Poisson weights
    }

    // Estimate background as average of edge regions
    int edgeWidth = std::max(2, nPoints / 10);
    double bgLeft = 0.0, bgRight = 0.0;

    for (int i = 0; i < edgeWidth; i++)
    {
        bgLeft += y[i];
        bgRight += y[nPoints - 1 - i];
    }
    bgLeft /= edgeWidth;
    bgRight /= edgeWidth;

    double bg0 = (bgLeft + bgRight) / 2.0;
    double bg1 = (bgRight - bgLeft) / (rightBin - leftBin);

    // Subtract background estimate
    std::vector<double> y_nobg(nPoints);
    for (int i = 0; i < nPoints; i++)
    {
        y_nobg[i] = y[i] - (bg0 + bg1 * x[i]);
        if (y_nobg[i] < 0) y_nobg[i] = 0;
    }

    // Find peak maximum in background-subtracted data
    double maxVal = 0.0;
    int maxIdx = nPoints / 2;
    for (int i = 0; i < nPoints; i++)
    {
        if (y_nobg[i] > maxVal)
        {
            maxVal = y_nobg[i];
            maxIdx = i;
        }
    }

    if (maxVal < 5.0)
    {
        return false; // Peak too weak after background subtraction
    }

    // Initial parameters
    double A = maxVal;                    // Amplitude
    double mu = x[maxIdx];                // Mean
    double sigma = peak.Sigma;            // Sigma

    // Simple iterative fitting (3-5 iterations usually sufficient)
    for (int iter = 0; iter < 5; iter++)
    {
        double sumWgt = 0.0;
        double sumWgtDiff2 = 0.0;
        double sumWgtX = 0.0;
        double sumWgtXDiff2 = 0.0;

        for (int i = 0; i < nPoints; i++)
        {
            double diff = x[i] - mu;
            double gauss = A * std::exp(-0.5 * diff * diff / (sigma * sigma));
            double residual = y_nobg[i] - gauss;

            if (gauss > 0.1 * A)  // Only use points near peak
            {
                double wgt = gauss;
                sumWgt += wgt;
                sumWgtDiff2 += wgt * diff * diff;
                sumWgtX += wgt * x[i];
                sumWgtXDiff2 += wgt * x[i] * diff * diff;
            }
        }

        if (sumWgt > 0)
        {
            mu = sumWgtX / sumWgt;
            if (sumWgtDiff2 > 0)
            {
                double newSigma = std::sqrt(sumWgtDiff2 / sumWgt);
                if (newSigma > 0.5 && newSigma < peak.Sigma * 3.0)
                {
                    sigma = newSigma;
                }
            }
        }
    }

    // Recalculate amplitude with final parameters
    A = 0.0;
    int countNearPeak = 0;
    for (int i = 0; i < nPoints; i++)
    {
        double diff = x[i] - mu;
        if (std::abs(diff) < 2.0 * sigma)
        {
            A += y_nobg[i];
            countNearPeak++;
        }
    }
    if (countNearPeak > 0)
    {
        A = A / (countNearPeak * std::sqrt(2.0 * TMath::Pi()) * sigma);
    }

    // Calculate chi-square
    double chi2 = 0.0;
    int ndf = 0;
    for (int i = 0; i < nPoints; i++)
    {
        double diff = x[i] - mu;
        double expected = bg0 + bg1 * x[i] + A * std::exp(-0.5 * diff * diff / (sigma * sigma));
        double residual = y[i] - expected;
        if (y[i] > 0)
        {
            chi2 += residual * residual / y[i];
            ndf++;
        }
    }
    ndf -= 5; // Subtract number of fitted parameters
    if (ndf < 1) ndf = 1;

    // Validate results
    if (sigma > 0.5 && sigma < peak.Sigma * 3.0 &&
        A > 0.0 &&
        mu > leftBin && mu < rightBin &&
        chi2 / ndf < 100.0)  // Reject very poor fits
    {
        peak.IsFitted = true;
        peak.FitAmplitude = A;
        peak.FitMean = mu;
        peak.FitSigma = sigma;
        peak.FitChi2 = chi2;
        peak.FitNDF = static_cast<double>(ndf);

        // Update peak parameters with fitted values
        peak.Position = peak.FitMean;
        peak.Sigma = peak.FitSigma;
        peak.FWHM = CalculateFWHM(peak.FitSigma);

        // Recalculate energy if calibrated
        if (FIsCalibrated)
        {
            peak.Energy = ChannelToEnergy(peak.Position);
        }

        // Calculate fitted peak area (integral of Gaussian part only)
        peak.Area = peak.FitAmplitude * peak.FitSigma * std::sqrt(2.0 * TMath::Pi());

        // Update boundaries
        peak.LeftBound = peak.Position - FFitRangeSigma * peak.Sigma;
        peak.RightBound = peak.Position + FFitRangeSigma * peak.Sigma;

        return true;
    }

    return false;
}

// Fit individual peak by index
bool CPhotopeakSearcher::FitPeak(int peakIndex)
{
    if (peakIndex < 0 || peakIndex >= static_cast<int>(FFoundPeaks.size()))
    {
        return false;
    }

    return FitGaussianToPeak(FFoundPeaks[peakIndex]);
}

// Estimate background using TSpectrum
void CPhotopeakSearcher::EstimateBackground(std::vector<double>& background)
{
    if (FSpectrumData.empty())
    {
        return;
    }

    // Create temporary histogram using smart pointer
    std::unique_ptr<TH1F> hist(new TH1F("temp_hist", "Temporary Histogram",
        FChannelCount, 0, FChannelCount));

    for (int i = 0; i < FChannelCount; i++)
    {
        hist->SetBinContent(i + 1, FSpectrumData[i]);
    }

    // Create TSpectrum object for background estimation using smart pointer
    std::unique_ptr<TSpectrum> spectrum(new TSpectrum(FMaxPeaks));

    // Estimate background - ROOT 6.32 uses histogram method
    TH1* bgHist = (TH1*)spectrum->Background(hist.get(), FBackgroundIterations, "same");

    if (bgHist != nullptr)
    {
        background.resize(FChannelCount);
        for (int i = 0; i < FChannelCount; i++)
        {
            background[i] = bgHist->GetBinContent(i + 1);
        }
        delete bgHist;
    }
    else
    {
        // Fallback: no background subtraction
        background = FSpectrumData;
    }

    // Smart pointers automatically clean up hist and spectrum
}

// Main photopeak search method
int CPhotopeakSearcher::SearchPhotopeaks()
{
    if (FSpectrumData.empty() || FChannelCount <= 0)
    {
        return 0;
    }

    FFoundPeaks.clear();

    int nPeaksFound = 0;
    Double_t* xPeaks = nullptr;
    Double_t* yPeaks = nullptr;

    if (FUseHighResSearch)
    {
        // Use SearchHighRes for better resolution (recommended for gamma spectroscopy)
        std::vector<double> destVector(FChannelCount);

        // Create TSpectrum object with unique configuration
        std::unique_ptr<TSpectrum> spectrum(new TSpectrum(FMaxPeaks));

        // IMPORTANT: Make a clean copy of data to avoid TSpectrum modifying original
        std::vector<double> workingData = FSpectrumData;

        nPeaksFound = spectrum->SearchHighRes(
            workingData.data(),
            destVector.data(),
            FChannelCount,
            FSigma,
            FThreshold,
            FUseBackground,     // backgroundRemove
            3,                  // deconIterations
            false,              // markov
            3);                 // averWindow

        if (nPeaksFound > 0)
        {
            xPeaks = spectrum->GetPositionX();
            yPeaks = spectrum->GetPositionY();

            // Copy peak positions immediately before TSpectrum is destroyed
            // This prevents issues with ROOT's internal memory management
            std::vector<double> xPeaksCopy(xPeaks, xPeaks + nPeaksFound);
            std::vector<double> yPeaksCopy(yPeaks, yPeaks + nPeaksFound);

            // Process peaks using the copies
            ProcessFoundPeaks(xPeaksCopy, yPeaksCopy, nPeaksFound);
        }
    }
    else
    {
        // Use original Search method (faster but less accurate)
        // Generate unique histogram name to avoid ROOT global directory conflicts
        static std::atomic<unsigned int> callCounter(0);
        callCounter++;

        char histName[128];
        sprintf_s(histName, "spectrum_%lu_%p_%u",
            static_cast<unsigned long>(time(nullptr)),
            this,
            callCounter.load());

        std::unique_ptr<TH1F> hist(new TH1F(histName, "Gamma Spectrum",
            FChannelCount, 0, FChannelCount));

        // Prevent ROOT from adding histogram to global directory
        hist->SetDirectory(nullptr);

        for (int i = 0; i < FChannelCount; i++)
        {
            hist->SetBinContent(i + 1, FSpectrumData[i]);
        }

        std::unique_ptr<TSpectrum> spectrum(new TSpectrum(FMaxPeaks));

        nPeaksFound = spectrum->Search(hist.get(), FSigma,
            FUseBackground ? "nodraw" : "nobackground nodraw",
            FThreshold);

        if (nPeaksFound > 0)
        {
            xPeaks = spectrum->GetPositionX();
            yPeaks = spectrum->GetPositionY();

            // Copy peak positions immediately
            std::vector<double> xPeaksCopy(xPeaks, xPeaks + nPeaksFound);
            std::vector<double> yPeaksCopy(yPeaks, yPeaks + nPeaksFound);

            // Process peaks using the copies
            ProcessFoundPeaks(xPeaksCopy, yPeaksCopy, nPeaksFound);
        }
    }

    return static_cast<int>(FFoundPeaks.size());
}

// Helper method to process found peaks (avoid code duplication)
void CPhotopeakSearcher::ProcessFoundPeaks(const std::vector<double>& xPeaks,
    const std::vector<double>& yPeaks,
    int nPeaksFound)
{
    // Sort peaks by position
    std::vector<int> indices(nPeaksFound);
    for (int i = 0; i < nPeaksFound; i++)
    {
        indices[i] = i;
    }

    std::sort(indices.begin(), indices.end(),
        [&xPeaks](int a, int b) { return xPeaks[a] < xPeaks[b]; });

    // Process each peak
    for (int i = 0; i < nPeaksFound; i++)
    {
        int idx = indices[i];
        PhotopeakInfo peak;

        peak.Position = xPeaks[idx];
        peak.Height = yPeaks[idx];

        // Calculate energy if calibrated (supports quadratic)
        if (FIsCalibrated)
        {
            peak.Energy = ChannelToEnergy(peak.Position);
        }
        else
        {
            peak.Energy = peak.Position;
        }

        // Calculate FWHM and sigma using proper resolution function
        double fwhm_keV = CalculateFWHMAtEnergy(peak.Energy);
        double sigma_keV = fwhm_keV / 2.355;

        // Convert sigma from keV to channels
        // For linear calibration: sigma_ch = sigma_keV / slope
        // For quadratic: use local derivative
        double localSigma;
        if (FIsCalibrated)
        {
            if (std::abs(FCalibrationA2) < 1e-10)
            {
                // Linear calibration
                if (FCalibrationA1 > 0.0)
                {
                    localSigma = sigma_keV / FCalibrationA1;
                }
                else
                {
                    localSigma = FSigma;  // Fallback
                }
            }
            else
            {
                // Quadratic calibration: use derivative dE/dCh at peak position
                // dE/dCh = A1 + 2×A2×Ch
                double derivative = FCalibrationA1 + 2.0 * FCalibrationA2 * peak.Position;
                if (derivative > 0.0)
                {
                    localSigma = sigma_keV / derivative;
                }
                else
                {
                    localSigma = sigma_keV / FCalibrationA1;  // Fallback to linear
                }
            }
        }
        else
        {
            // No calibration: work in channels directly
            localSigma = FSigma;
        }

        // Ensure reasonable sigma value
        if (localSigma < 0.5)
        {
            localSigma = 0.5;
        }
        else if (localSigma > 50.0)
        {
            localSigma = 50.0;
        }

        peak.Sigma = localSigma;
        peak.FWHM = localSigma * 2.355;  // FWHM in channels

        // Calculate boundaries (±3 sigma)
        peak.LeftBound = peak.Position - 3.0 * localSigma;
        peak.RightBound = peak.Position + 3.0 * localSigma;

        // Calculate peak area
        peak.Area = CalculatePeakArea(FSpectrumData, peak.Position, localSigma);

        FFoundPeaks.push_back(peak);
    }

    // Perform Gaussian fitting if requested
    if (FPerformGaussianFit)
    {
        for (size_t i = 0; i < FFoundPeaks.size(); i++)
        {
            // Fit each peak individually with error handling
            try
            {
                FitGaussianToPeak(FFoundPeaks[i]);
            }
            catch (...)
            {
                // Silently continue if fit fails for this peak
            }
        }
    }
}

// Get peak information by index
PhotopeakInfo CPhotopeakSearcher::GetPeak(int index) const
{
    if (index >= 0 && index < static_cast<int>(FFoundPeaks.size()))
    {
        return FFoundPeaks[index];
    }
    return PhotopeakInfo();
}

// Clear all data
void CPhotopeakSearcher::Clear()
{
    FSpectrumData.clear();
    FFoundPeaks.clear();
    FChannelCount = 0;
}

// ============================================================================
// C-style interface implementation
// ============================================================================

extern "C"
{
    HPeakSearcher __stdcall CreatePeakSearcher()
    {
        try
        {
            return static_cast<HPeakSearcher>(new CPhotopeakSearcher());
        }
        catch (...)
        {
            return nullptr;
        }
    }

    void __stdcall DestroyPeakSearcher(HPeakSearcher handle)
    {
        if (handle != nullptr)
        {
            try
            {
                delete static_cast<CPhotopeakSearcher*>(handle);
            }
            catch (...)
            {
            }
        }
    }

    bool __stdcall LoadSpectrumDouble(HPeakSearcher handle,
        const double* data, int channelCount)
    {
        if (handle == nullptr)
        {
            return false;
        }

        try
        {
            return static_cast<CPhotopeakSearcher*>(handle)->LoadSpectrum(data, channelCount);
        }
        catch (...)
        {
            return false;
        }
    }

    bool __stdcall LoadSpectrumInt(HPeakSearcher handle,
        const int* data, int channelCount)
    {
        if (handle == nullptr)
        {
            return false;
        }

        try
        {
            return static_cast<CPhotopeakSearcher*>(handle)->LoadSpectrum(data, channelCount);
        }
        catch (...)
        {
            return false;
        }
    }

    void __stdcall SetCalibration(HPeakSearcher handle, double a0, double a1, double a2)
    {
        if (handle != nullptr)
        {
            try
            {
                static_cast<CPhotopeakSearcher*>(handle)->SetCalibration(a0, a1, a2);
            }
            catch (...)
            {
            }
        }
    }

    void __stdcall ClearCalibration(HPeakSearcher handle)
    {
        if (handle != nullptr)
        {
            try
            {
                static_cast<CPhotopeakSearcher*>(handle)->ClearCalibration();
            }
            catch (...)
            {
            }
        }
    }

    void __stdcall SetResolution(HPeakSearcher handle, double a, double b)
    {
        if (handle != nullptr)
        {
            try
            {
                static_cast<CPhotopeakSearcher*>(handle)->SetResolution(a, b);
            }
            catch (...)
            {
            }
        }
    }

    void __stdcall SetResolutionFromMeasurements(HPeakSearcher handle,
        double fwhm1_keV, double energy1_keV, double fwhm2_keV, double energy2_keV)
    {
        if (handle != nullptr)
        {
            try
            {
                static_cast<CPhotopeakSearcher*>(handle)->SetResolutionFromMeasurements(
                    fwhm1_keV, energy1_keV, fwhm2_keV, energy2_keV);
            }
            catch (...)
            {
            }
        }
    }

    void __stdcall SetResolutionFromPercentage(HPeakSearcher handle,
        double resolutionPercent, double referenceEnergy)
    {
        if (handle != nullptr)
        {
            try
            {
                static_cast<CPhotopeakSearcher*>(handle)->SetResolutionFromPercentage(
                    resolutionPercent, referenceEnergy);
            }
            catch (...)
            {
            }
        }
    }

    void __stdcall ClearResolution(HPeakSearcher handle)
    {
        if (handle != nullptr)
        {
            try
            {
                static_cast<CPhotopeakSearcher*>(handle)->ClearResolution();
            }
            catch (...)
            {
            }
        }
    }

    void __stdcall SetSearchSigma(HPeakSearcher handle, double sigma)
    {
        if (handle != nullptr)
        {
            try
            {
                static_cast<CPhotopeakSearcher*>(handle)->SetSigma(sigma);
            }
            catch (...)
            {
            }
        }
    }

    void __stdcall SetSearchThreshold(HPeakSearcher handle, double threshold)
    {
        if (handle != nullptr)
        {
            try
            {
                static_cast<CPhotopeakSearcher*>(handle)->SetThreshold(threshold);
            }
            catch (...)
            {
            }
        }
    }

    void __stdcall SetSearchMaxPeaks(HPeakSearcher handle, int maxPeaks)
    {
        if (handle != nullptr)
        {
            try
            {
                static_cast<CPhotopeakSearcher*>(handle)->SetMaxPeaks(maxPeaks);
            }
            catch (...)
            {
            }
        }
    }

    void __stdcall SetUseBackground(HPeakSearcher handle, bool useBackground)
    {
        if (handle != nullptr)
        {
            try
            {
                static_cast<CPhotopeakSearcher*>(handle)->SetUseBackground(useBackground);
            }
            catch (...)
            {
            }
        }
    }

    void __stdcall SetPerformGaussianFit(HPeakSearcher handle, bool performFit)
    {
        if (handle != nullptr)
        {
            try
            {
                static_cast<CPhotopeakSearcher*>(handle)->SetPerformGaussianFit(performFit);
            }
            catch (...)
            {
            }
        }
    }

    void __stdcall SetFitRangeSigma(HPeakSearcher handle, double rangeSigma)
    {
        if (handle != nullptr)
        {
            try
            {
                static_cast<CPhotopeakSearcher*>(handle)->SetFitRangeSigma(rangeSigma);
            }
            catch (...)
            {
            }
        }
    }

    void __stdcall SetUseHighResSearch(HPeakSearcher handle, bool useHighRes)
    {
        if (handle != nullptr)
        {
            try
            {
                static_cast<CPhotopeakSearcher*>(handle)->SetUseHighResSearch(useHighRes);
            }
            catch (...)
            {
            }
        }
    }

    int __stdcall SearchPhotopeaks(HPeakSearcher handle)
    {
        if (handle == nullptr)
        {
            return 0;
        }

        try
        {
            return static_cast<CPhotopeakSearcher*>(handle)->SearchPhotopeaks();
        }
        catch (...)
        {
            return 0;
        }
    }

    bool __stdcall FitPeakByIndex(HPeakSearcher handle, int peakIndex)
    {
        if (handle == nullptr)
        {
            return false;
        }

        try
        {
            return static_cast<CPhotopeakSearcher*>(handle)->FitPeak(peakIndex);
        }
        catch (...)
        {
            return false;
        }
    }

    int __stdcall GetPeakCount(HPeakSearcher handle)
    {
        if (handle == nullptr)
        {
            return 0;
        }

        try
        {
            return static_cast<CPhotopeakSearcher*>(handle)->GetPeakCount();
        }
        catch (...)
        {
            return 0;
        }
    }

    bool __stdcall GetPeakInfo(HPeakSearcher handle, int index,
        PhotopeakInfo* peakInfo)
    {
        if (handle == nullptr || peakInfo == nullptr)
        {
            return false;
        }

        try
        {
            CPhotopeakSearcher* searcher = static_cast<CPhotopeakSearcher*>(handle);
            if (index >= 0 && index < searcher->GetPeakCount())
            {
                *peakInfo = searcher->GetPeak(index);
                return true;
            }
            return false;
        }
        catch (...)
        {
            return false;
        }
    }

    void __stdcall ClearSearcher(HPeakSearcher handle)
    {
        if (handle != nullptr)
        {
            try
            {
                static_cast<CPhotopeakSearcher*>(handle)->Clear();
            }
            catch (...)
            {
            }
        }
    }

    double __stdcall CalculateOptimalSigma(
        double resolutionPercent,
        double referenceEnergy,
        double calibrationSlope)
    {
        // Calculate FWHM in keV at reference energy
        double fwhm_keV = (resolutionPercent / 100.0) * referenceEnergy;

        // Convert to channels
        double fwhm_channels = fwhm_keV / calibrationSlope;

        // Calculate theoretical sigma
        double theoretical_sigma = fwhm_channels / 2.355;

        // TSpectrum works best with sigma values between 1.5 and 4.0
        // Scale down theoretical sigma for optimal performance
        double optimal_sigma = theoretical_sigma / 2.5;

        // Clamp to reasonable range
        if (optimal_sigma < 1.5)
            optimal_sigma = 1.5;
        else if (optimal_sigma > 4.0)
            optimal_sigma = 4.0;

        return optimal_sigma;
    }
}