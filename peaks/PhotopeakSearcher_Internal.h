// PhotopeakSearcher_Internal.h
// Internal class declaration - NOT distributed with DLL
// Only used within the DLL project itself

#ifndef PHOTOPEAK_SEARCHER_INTERNAL_H
#define PHOTOPEAK_SEARCHER_INTERNAL_H

#include "PhotopeakSearcher.h"  // Include public header for PhotopeakInfo
#include <vector>

// Internal implementation class
class CPhotopeakSearcher
{
private:
    int FChannelCount;
    std::vector<double> FSpectrumData;
    std::vector<PhotopeakInfo> FFoundPeaks;

    // Calibration parameters (quadratic: Energy = A0 + A1 * Channel + A2 * Channel^2)
    double FCalibrationA0;
    double FCalibrationA1;
    double FCalibrationA2;
    bool FIsCalibrated;

    // Resolution parameters (FWHM(E) = √(a + b×E) in keV)
    double FResolutionA;        // Constant term (keV²)
    double FResolutionB;        // Energy-dependent term (keV)
    bool FResolutionCalibrated; // Whether resolution is calibrated

    // Search parameters
    double FSigma;              // Expected peak width in CHANNELS (not keV)
    double FThreshold;          // Threshold for peak detection (0.0 - 1.0)
    int FMaxPeaks;              // Maximum number of peaks to search
    bool FUseBackground;        // Use background subtraction
    int FBackgroundIterations;  // Background estimation iterations
    bool FPerformGaussianFit;   // Perform Gaussian fit on found peaks
    double FFitRangeSigma;      // Fit range in units of sigma (default: 3.0)
    bool FUseHighResSearch;     // Use SearchHighRes instead of Search

    // Helper methods
    double CalculateFWHM(double sigma);
    double CalculatePeakArea(const std::vector<double>& data, double position, double sigma);
    void EstimateBackground(std::vector<double>& background);
    bool FitGaussianToPeak(PhotopeakInfo& peak);
    void ProcessFoundPeaks(const std::vector<double>& xPeaks,
        const std::vector<double>& yPeaks,
        int nPeaksFound);

public:
    CPhotopeakSearcher();
    ~CPhotopeakSearcher();

    // Initialization and data loading
    bool LoadSpectrum(const double* spectrumData, int channelCount);
    bool LoadSpectrum(const int* spectrumData, int channelCount);

    // Calibration
    void SetCalibration(double a0, double a1, double a2 = 0.0);
    void ClearCalibration();
    bool IsCalibrated() const { return FIsCalibrated; }

    // Resolution calibration
    // For NaI(Tl): FWHM(E) = √(a + b×E) where E is in keV
    // Set from two measured points or calculated from resolution percentage
    void SetResolution(double a, double b);
    void SetResolutionFromMeasurements(double fwhm1_keV, double energy1_keV,
        double fwhm2_keV, double energy2_keV);
    void SetResolutionFromPercentage(double resolutionPercent, double referenceEnergy);
    void ClearResolution();
    bool IsResolutionCalibrated() const { return FResolutionCalibrated; }

    // Calculate FWHM at given energy using resolution function
    double CalculateFWHMAtEnergy(double energy_keV) const;

    // Search parameters
    void SetSigma(double sigma) { FSigma = sigma; }
    void SetThreshold(double threshold) { FThreshold = threshold; }
    void SetMaxPeaks(int maxPeaks) { FMaxPeaks = maxPeaks; }
    void SetUseBackground(bool useBackground) { FUseBackground = useBackground; }
    void SetBackgroundIterations(int iterations) { FBackgroundIterations = iterations; }
    void SetPerformGaussianFit(bool performFit) { FPerformGaussianFit = performFit; }
    void SetFitRangeSigma(double rangeSigma) { FFitRangeSigma = rangeSigma; }
    void SetUseHighResSearch(bool useHighRes) { FUseHighResSearch = useHighRes; }

    double GetSigma() const { return FSigma; }
    double GetThreshold() const { return FThreshold; }
    int GetMaxPeaks() const { return FMaxPeaks; }
    bool GetUseBackground() const { return FUseBackground; }
    bool GetPerformGaussianFit() const { return FPerformGaussianFit; }
    bool GetUseHighResSearch() const { return FUseHighResSearch; }

    // Main search method
    int SearchPhotopeaks();

    // Results retrieval
    int GetPeakCount() const { return static_cast<int>(FFoundPeaks.size()); }
    PhotopeakInfo GetPeak(int index) const;
    const std::vector<PhotopeakInfo>& GetAllPeaks() const { return FFoundPeaks; }

    // Fit individual peak
    bool FitPeak(int peakIndex);

    // Utility methods
    void Clear();
    double ChannelToEnergy(double channel) const;
    double EnergyToChannel(double energy) const;
};

#endif // PHOTOPEAK_SEARCHER_INTERNAL_H