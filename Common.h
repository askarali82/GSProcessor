//---------------------------------------------------------------------------
#ifndef CommonH
#define CommonH

#include <SyncObjs.hpp>
#include <DateUtils.hpp>
#include <StrUtils.hpp>
#include <memory>
#include <atomic>
#include <cmath>
#include <vector>
#include <windows.h>
#include "Spectrum.hpp"
//---------------------------------------------------------------------------
#define LOG(Msg)                Utils::Log(__FUNC__, __LINE__, Msg)
#define LOGEXCEPTION(E)         Utils::LogException(E, __FUNC__, __LINE__)
//---------------------------------------------------------------------------

// Language ID
// 0 => Uzbek
// 1 => English
extern std::atomic<int> LangID;
//
//
//

class TScopeLock
{
private:
    TCriticalSection *FSection;
    
public:
    TScopeLock(TCriticalSection *Section): FSection(Section)
    {
        try
        {
            FSection->Acquire();
        }
        catch (const Exception &)
        {
        }
    }
    //--------------------------------------------------------------
    virtual ~TScopeLock()
    {
        try
        {
            FSection->Release();
        }
        catch (const Exception &)
        {
        }
    }
};
//---------------------------------------------------------------------------
class Utils
{
private:

public:
    static void Log(const AnsiString &Func, const AnsiString &Line, AnsiString Msg);

    static void LogException(const Exception &E, const AnsiString &Func, const AnsiString &Line);

    static String RoundFloatValue(const double Value, const int D = 2, const bool DeleteZeroes = true);

    static void NormalizeStandardSources(const TSpectrum &Spc1, TSpectrum &Spc2, const double Energy1, const double Energy2);

    static inline double Sqr(const double F)
    {
        return F * F;
    }

    static bool IsEqual(const double a, const double b, const double epsilon = 0.001)
    {
        return std::abs(a - b) < epsilon;
    }

    static void CheckError(const bool Error, String Msg)
    {
        if (Msg == "")
        {
            Msg = "Unknown error.";
        }
        if (Error)
        {
            throw Exception(Msg);
        }
    }

    static String GetDialogBoxFilterForSpectraFiles(const bool IncludeParFiles = false);

    static double CalcBe7Effectivity(const double Eff1, const double Eff2, const double Eff3, const double SmpDensity);

    static std::vector<String> CreateStringVectorFromDelimitedStr(
        const String &Str, const wchar_t Delimiter, const bool NonEmpty = true, const wchar_t QuoteChar = L'\0');
};
//---------------------------------------------------------------------------
#endif
