//---------------------------------------------------------------------------
#ifndef BatchProcessingThreadUH
#define BatchProcessingThreadUH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <memory>
#include "Spectrum.hpp"
//---------------------------------------------------------------------------

// Language ID
// 0 => Uzbek
// 1 => English
extern std::atomic<int> LangID;
//
//
//

struct TData
{
    // Experimental spectra
    TSpectrum Bkgs[3];
    TSpectrum Ths[3];
    TSpectrum Ras[3];
    TSpectrum Ks[3];
    TSpectrum Css[3];

    // Energy ranges
    double ThEn1;
    double ThEn2;
    double RaEn1;
    double RaEn2;
    double KEn1;
    double KEn2;
    double CsEn1;
    double CsEn2;
    double BeEn1;
    double BeEn2;

    double BePhotopeakEff1;
    double BePhotopeakEff2;
    double BePhotopeakEff3;

    //Search peaks
    double MinPeakWidth;
    double MaxEnergyError;

    // Std samples activity errors
    double ThActivityErrors[3];
    double RaActivityErrors[3];
    double KActivityErrors[3];
    double CsActivityErrors[3];

    bool ValidSpectra(const int Idx) const
    {
        return
            Idx >= 0 && Idx <= 2 &&
            Bkgs[Idx].IsValid() &&
            Ths[Idx].IsValid() &&
            Ras[Idx].IsValid() &&
            Ks[Idx].IsValid() &&
            Css[Idx].IsValid();
    }
};
//---------------------------------------------------------------------------
class TBatchProcessingThread : public TThread
{
private:
    const TData BaseData;
    const String DirectoryName;
    const int LangID;
    std::unique_ptr<TStringList> FileNames;
    HWND WindowToNotify;

    // Virtual Spectra
    TSpectrum BkgSpc;
    TSpectrum ThSpc;
    TSpectrum RaSpc;
    TSpectrum KSpc;
    TSpectrum CsSpc;

    // Counts in virtual spectra
    double ThCount;
    double RaThCount_sa;
    double KThCount_sa;
    double CsThCount_sa;
    double BeThCount_sa;

    double RaCount;
    double KRaCount_sa;
    double CsRaCount_sa;
    double BeRaCount_sa;

    double KCount;
    double CsKCount_sa;
    double BeKCount_sa;

    double CsCount;
    double BeCsCount_sa;

    // Activities of Std samples
    double ThActivity;
    double RaActivity;
    double KActivity;
    double CsActivity;

    bool Be7IsCalculated;

    void GetFilesList();
    bool CreateVirtualSpectra(const TSpectrum &Spectrum);

    void CalculateCountsAndActivitiesInStdSamples();
    void CalculateActivities(
        const TSpectrum &Spectrum,
        String &ThStr,
        String &ThCstr,
        String &RaStr,
        String &RaCstr,
        String &KStr,
        String &KCstr,
        String &CsStr,
        String &CsCs,
        String &BeStr);

protected:
    void __fastcall Execute();

public:
    __fastcall TBatchProcessingThread(
        const TData &BData, const String &DirName, TStrings *Files, HWND WndToNotify);
};
//---------------------------------------------------------------------------
#endif
