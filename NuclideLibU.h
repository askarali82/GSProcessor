//---------------------------------------------------------------------------
#ifndef NuclideLibUH
#define NuclideLibUH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <vector>
#include <set>
#include "peaks/PhotopeakSearcher.h"
#include "Spectrum.hpp"
//---------------------------------------------------------------------------
struct TGammaLine
{
private:
    static const double dE;

public:
    double Energy;
    String HeadParent;
    String ImmediateParent;
    String ImmediateParentDecayMode;
    String GammaEmitter;
    double GammaYield;
    String Series;

    explicit TGammaLine(
        const double AEnergy = 0,
        const String &AHeadParent = L"",
        const String &AImmediateParent = L"",
        const String &AImmediateParentDecayMode = L"",
        const String &AGammaEmitter = L"",
        const double AGammaYield = 0,
        const String &ASeries = L"")
        :
        Energy(AEnergy),
        HeadParent(AHeadParent),
        ImmediateParent(AImmediateParent),
        ImmediateParentDecayMode(AImmediateParentDecayMode),
        GammaEmitter(AGammaEmitter),
        GammaYield(AGammaYield),
        Series(ASeries)
    {
    }

    bool operator == (const TGammaLine &Other) const
    {
        return std::abs(Energy - Other.Energy) < dE;
    }

    bool operator == (const double &OtherEnergy) const
    {
        return std::abs(Energy - OtherEnergy) < dE;
    }

    bool operator < (const TGammaLine &Other) const
    {
        return Energy < Other.Energy;
    }
};
//---------------------------------------------------------------------------
enum class MatchConfidence
{
    None,
    Tentative,
    Confident
};
//---------------------------------------------------------------------------
struct PeakMatchResult
{
    bool Matched;
    double Score;
    TGammaLine Line;
};
//---------------------------------------------------------------------------
class TNuclideLib
{
private:
    const std::vector<TGammaLine> GammaLines;

    static std::vector<TGammaLine> GetGammaLines();

    TNuclideLib();
    TNuclideLib(const TNuclideLib&) = delete;
    TNuclideLib & operator = (const TNuclideLib&) = delete;
    TNuclideLib(TNuclideLib&&) = delete;
    TNuclideLib & operator = (TNuclideLib&&) = delete;

public:
    static TNuclideLib & GetInstance()
    {
        static TNuclideLib NuclideLib;
        return NuclideLib;
    }

    const std::vector<TGammaLine> & GetAllGammaLines() const
    {
        return GammaLines;
    }

    double SigmaKeV(const PhotopeakInfo &Peak, const TSpectrum &Spc) const;

    bool IsWithinEnergyGate(
        const double PeakEnergy,
        const double LineEnergy,
        const double SigmaE,
        const double GateFactor) const;

    PeakMatchResult MatchPhotopeak(
        PhotopeakInfo &Peak,
        const std::vector<TGammaLine>& GammaLines,
        const std::set<String> &DetectedSeries,
        const TSpectrum &Spc,
        const double GateFactor = 1.5) const;

    double ComputeEnergyScore(const double DeltaE, const double SigmaE) const;

    double ComputeProbabilityScore(const double EmissionProbability) const;

    double ComputeSeriesScore(const String &Series,  const std::set<String> &DetectedSeries) const;

    MatchConfidence GetConfidence(const double Score) const;
};

extern TNuclideLib *NuclideLib;

#endif
