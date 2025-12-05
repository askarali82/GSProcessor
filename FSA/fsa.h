#ifndef FSA_H
#define FSA_H

#define WIN32_LEAN_AND_MEAN

#ifdef FSA_EXPORTS
#define FSA_API __declspec(dllexport)
#else
#define FSA_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

    typedef void* FSAHandle;

    FSA_API FSAHandle __cdecl FSA_Create(int numChannels, int numNuclides);

    FSA_API void __cdecl FSA_Destroy(FSAHandle handle);

    FSA_API int __cdecl FSA_AddReferenceSpectrum(
        FSAHandle handle,
        int nuclideIdx,
        const double* spectrum,
        const double* refBackground,
        int spectrumSize,
        double activity,
        double measTime,
        const char* name
    );

    FSA_API int __cdecl FSA_AddNormalizedReference(
        FSAHandle handle,
        int nuclideIdx,
        const double* normalizedSpectrum,
        int spectrumSize,
        const char* name
    );

    FSA_API int __cdecl FSA_SetBackground(
        FSAHandle handle,
        const double* background,
        int size
    );

    FSA_API int __cdecl FSA_Analyze(
        FSAHandle handle,
        const double* measuredSpectrum,
        int spectrumSize,
        double measTime,
        double* activities,
        int activitiesSize
    );

    FSA_API int __cdecl FSA_AnalyzeQR(
        FSAHandle handle,
        const double* measuredSpectrum,
        int spectrumSize,
        double measTime,
        double* activities,
        int activitiesSize
    );

    FSA_API double __cdecl FSA_CalculateChiSquare(
        FSAHandle handle,
        const double* measuredSpectrum,
        int spectrumSize,
        const double* activities,
        int activitiesSize,
        double measTime
    );

    FSA_API int __cdecl FSA_CalculateUncertainties(
        FSAHandle handle,
        const double* measuredSpectrum,
        int spectrumSize,
        double* uncertainties,
        int uncertaintiesSize
    );

    FSA_API const char* __cdecl FSA_GetLastError();

#ifdef __cplusplus
}
#endif

#endif