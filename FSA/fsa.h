#ifndef FSA_H
#define FSA_H

#ifdef FSA_EXPORTS
#define FSA_API __declspec(dllexport)
#else
#define FSA_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

    // Opaque handle to the FSA object
    typedef void* FSAHandle;

    // Energy calibration structure
    typedef struct {
        double a;  // Offset (keV)
        double b;  // Linear coefficient (keV/channel)
        double c;  // Quadratic coefficient (keV/channel²)
    } FSACalibration;

    // Create FSA in energy-aware mode (no rebinning)
    FSA_API FSAHandle FSA_Create(int numNuclides);

    // Destroy an FSA instance
    FSA_API void FSA_Destroy(FSAHandle handle);

    // Add reference spectrum with energy calibration
    FSA_API int FSA_AddReference(
        FSAHandle handle,
        int nuclideIdx,
        const double* spectrum,
        int spectrumSize,
        const FSACalibration* calibration,
        double activity,
        double measTime
    );

    // Set background spectrum with energy calibration
    FSA_API int FSA_SetBackground(
        FSAHandle handle,
        const double* background,
        int backgroundSize,
        const FSACalibration* calibration
    );

    // Analyze using NNLS (background always as component)
    FSA_API int FSA_Analyze(
        FSAHandle handle,
        const double* measuredSpectrum,
        int spectrumSize,
        const FSACalibration* calibration,
        double measTime,
        double* activities,
        int activitiesSize
    );

    // Get background scale factor
    FSA_API double FSA_GetBackgroundScale(
        FSAHandle handle,
        const double* measuredSpectrum,
        int spectrumSize,
        const FSACalibration* calibration,
        double measTime
    );

    // Calculate chi-square goodness of fit
    FSA_API double FSA_CalculateChiSquare(
        FSAHandle handle,
        const double* measuredSpectrum,
        int spectrumSize,
        const FSACalibration* calibration,
        const double* activities,
        int activitiesSize,
        double measTime
    );

    // Get last error message
    FSA_API const char* FSA_GetLastError();

#ifdef __cplusplus
}
#endif

#endif // FSA_H