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

    typedef void* FSAHandle;

    typedef struct {
        double a;
        double b;
        double c;
    } FSACalibration;

    FSA_API FSAHandle FSA_Create(double energyMin, double energyMax,
        double energyStep, int numNuclides);

    FSA_API void FSA_Destroy(FSAHandle handle);

    FSA_API int FSA_AddReferenceSpectrum(
        FSAHandle handle,
        int nuclideIdx,
        const double* spectrum,
        int spectrumSize,
        const FSACalibration* calibration,
        double activity,
        double measTime
    );

    FSA_API int FSA_SetBackground(
        FSAHandle handle,
        const double* background,
        int backgroundSize,
        const FSACalibration* calibration,
        double measTime
    );

    FSA_API int FSA_Analyze(
        FSAHandle handle,
        const double* measuredSpectrum,
        int spectrumSize,
        const FSACalibration* calibration,
        double measTime,
        double* activities,
        int activitiesSize
    );

    /*
    * NOTE: This function allocates memory for interpSpectrum.
    * The caller is responsible for freeing this memory by calling FSA_FreeMemory.
    */
    FSA_API double FSA_GetInterpolatedTotalCounts(
        FSAHandle handle,
        const double* spectrum,
        int spectrumSize,
        const FSACalibration* calibration,
        double** interpSpectrum,
        int* interpSpectrumSize
    );

    FSA_API double FSA_GetBackgroundScale(
        FSAHandle handle,
        const double* measuredSpectrum,
        double measTime
    );

    FSA_API double FSA_CalculateChiSquare(
        FSAHandle handle,
        const double* measuredSpectrum,
        const double* activities,
        double measTime
    );

    FSA_API int FSA_CalculateUncertainties(
        FSAHandle handle,
        const double* measuredSpectrum,
        double* uncertainties
    );

    FSA_API const char* FSA_GetLastError();

    FSA_API void FSA_FreeMemory(void* buffer);


#ifdef __cplusplus
}
#endif

#endif // FSA_H