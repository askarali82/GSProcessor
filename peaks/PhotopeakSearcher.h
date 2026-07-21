// PhotopeakSearcher.h
// Public DLL interface for gamma spectrum photopeak detection
// Allman style coding convention

#ifndef PHOTOPEAK_SEARCHER_H
#define PHOTOPEAK_SEARCHER_H

#ifdef PHOTOPEAKSEARCHER_EXPORTS
#define PHOTOPEAK_API __declspec(dllexport)
#else
#define PHOTOPEAK_API __declspec(dllimport)
#endif

// Structure to hold photopeak information
struct PhotopeakInfo
{
    double Position;        // Channel position of the peak
    double Energy;          // Energy in keV (if calibrated)
    double Height;          // Peak height (counts)
    double Area;            // Peak area (integrated counts)
    double FWHM;            // Full Width at Half Maximum
    double Sigma;           // Gaussian sigma
    double LeftBound;       // Left boundary of the peak
    double RightBound;      // Right boundary of the peak
    bool IsFitted;          // Whether Gaussian fit was performed
    double FitAmplitude;    // Fitted Gaussian amplitude
    double FitMean;         // Fitted Gaussian mean
    double FitSigma;        // Fitted Gaussian sigma
    double FitChi2;         // Chi-square of the fit
    double FitNDF;          // Number of degrees of freedom
    bool Highlighted;       // Whether the peak is highlighted (for UI purposes)
    int LineIndex;          // Associated line index (for UI purposes)

    PhotopeakInfo()
        : Position(0.0), Energy(0.0), Height(0.0), Area(0.0),
        FWHM(0.0), Sigma(0.0), LeftBound(0.0), RightBound(0.0),
        IsFitted(false), FitAmplitude(0.0), FitMean(0.0), FitSigma(0.0),
        FitChi2(0.0), FitNDF(0.0), Highlighted(false), LineIndex(-1)
    {
    }
};

// C-style interface for C++ Builder compatibility
extern "C"
{
    // Handle-based interface
    typedef void* HPeakSearcher;

    // Lifecycle management
    PHOTOPEAK_API HPeakSearcher __stdcall CreatePeakSearcher();
    PHOTOPEAK_API void __stdcall DestroyPeakSearcher(HPeakSearcher handle);

    // Data loading
    PHOTOPEAK_API bool __stdcall LoadSpectrumDouble(HPeakSearcher handle,
        const double* data, int channelCount);
    PHOTOPEAK_API bool __stdcall LoadSpectrumInt(HPeakSearcher handle,
        const int* data, int channelCount);

    // Energy calibration (quadratic: Energy = a0 + a1*ch + a2*ch²)
    PHOTOPEAK_API void __stdcall SetCalibration(HPeakSearcher handle,
        double a0, double a1, double a2);
    PHOTOPEAK_API void __stdcall ClearCalibration(HPeakSearcher handle);

    // Resolution calibration (FWHM(E) = √(a + b×E) in keV)
    PHOTOPEAK_API void __stdcall SetResolution(HPeakSearcher handle, double a, double b);
    PHOTOPEAK_API void __stdcall SetResolutionFromMeasurements(HPeakSearcher handle,
        double fwhm1_keV, double energy1_keV, double fwhm2_keV, double energy2_keV);
    PHOTOPEAK_API void __stdcall SetResolutionFromPercentage(HPeakSearcher handle,
        double resolutionPercent, double referenceEnergy);
    PHOTOPEAK_API void __stdcall ClearResolution(HPeakSearcher handle);

    // Search parameters
    // IMPORTANT: sigma is in CHANNELS (bins), NOT keV!
    // For example: SetSearchSigma(Handle, 2.5) means sigma = 2.5 channels
    PHOTOPEAK_API void __stdcall SetSearchSigma(HPeakSearcher handle, double sigma);
    PHOTOPEAK_API void __stdcall SetSearchThreshold(HPeakSearcher handle, double threshold);
    PHOTOPEAK_API void __stdcall SetSearchMaxPeaks(HPeakSearcher handle, int maxPeaks);
    PHOTOPEAK_API void __stdcall SetUseBackground(HPeakSearcher handle, bool useBackground);
    PHOTOPEAK_API void __stdcall SetPerformGaussianFit(HPeakSearcher handle, bool performFit);
    PHOTOPEAK_API void __stdcall SetFitRangeSigma(HPeakSearcher handle, double rangeSigma);
    PHOTOPEAK_API void __stdcall SetUseHighResSearch(HPeakSearcher handle, bool useHighRes);

    // Peak search and fitting
    PHOTOPEAK_API int __stdcall SearchPhotopeaks(HPeakSearcher handle);
    PHOTOPEAK_API bool __stdcall FitPeakByIndex(HPeakSearcher handle, int peakIndex);

    // Results retrieval
    PHOTOPEAK_API int __stdcall GetPeakCount(HPeakSearcher handle);
    PHOTOPEAK_API bool __stdcall GetPeakInfo(HPeakSearcher handle, int index,
        PhotopeakInfo* peakInfo);

    // Utility
    PHOTOPEAK_API void __stdcall ClearSearcher(HPeakSearcher handle);

    // Helper function to calculate optimal sigma parameter
    // All parameters are in energy units (keV), returns sigma in CHANNELS
    // resolutionPercent: detector resolution at referenceEnergy (e.g., 7.0 for 7%)
    // referenceEnergy: energy where resolution is known (e.g., 662.0 keV)
    // calibrationSlope: keV per channel (e.g., 3.0 keV/ch)
    // Returns: recommended sigma value in CHANNELS for TSpectrum
    //
    // Example: CalculateOptimalSigma(7.0, 662.0, 3.0)
    //   Input: 7% resolution at 662 keV with 3 keV/channel calibration
    //   Output: ~2.8 channels (optimal for TSpectrum algorithm)
    PHOTOPEAK_API double __stdcall CalculateOptimalSigma(
        double resolutionPercent,
        double referenceEnergy,
        double calibrationSlope);
}

#endif // PHOTOPEAK_SEARCHER_H