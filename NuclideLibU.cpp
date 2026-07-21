//---------------------------------------------------------------------------
#include <vcl.h>
#include <System.IniFiles.hpp>
#include <memory>
#include <algorithm>
#include <set>
#include <cmath>
#pragma hdrstop

#include "NuclideLibU.h"
#include "Common.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
TNuclideLib *NuclideLib;
const double TGammaLine::dE = 8.0;
//---------------------------------------------------------------------------
std::vector<TGammaLine> TNuclideLib::GetGammaLines()
{
    std::vector<TGammaLine> GammaLines;
    try
    {
        std::unique_ptr<TMemIniFile> File(
            new TMemIniFile(L".\\nuclide.dat", TEncoding::Unicode));
        std::unique_ptr<TStringList> Sections(new TStringList());
        File->ReadSections(Sections.get());
        for (int i = 0; i < Sections->Count; i++)
        {
            std::unique_ptr<TStringList> Values(new TStringList());
            File->ReadSectionValues(Sections->Strings[i], Values.get());
            for (int j = 0; j < Values->Count; j++)
            {
                String Value = Values->Strings[j];
                const int P = Value.Pos(L"=");
                if (P > 1)
                {
                    Value = Value.SubString(P + 1, Value.Length()).Trim();
                    const auto &Strs = Utils::CreateStringVectorFromDelimitedStr(Value, L',');
                    if (Strs.size() >= 6)
                    {
                        const TGammaLine GammaLine(
                            Sysutils::StrToFloat(Strs[0]),
                            Sections->Strings[i],
                            Strs[1],
                            Strs[2],
                            Strs[3],
                            Sysutils::StrToFloat(Strs[4]),
                            Strs[5]);
                        GammaLines.push_back(GammaLine);
                    }
                }
            }
        }

        std::sort(GammaLines.begin(), GammaLines.end());
    }
    catch (const Exception &E)
    {
        LOG(L"Exception: " + E.Message);
        GammaLines.clear();
    }
    catch (const std::exception &E)
    {
        LOG(L"Exception: " + String(E.what()));
        GammaLines.clear();
    }
    return GammaLines;
}
//---------------------------------------------------------------------------
TNuclideLib::TNuclideLib():
    GammaLines(std::move(GetGammaLines()))
{
}
//---------------------------------------------------------------------------
double TNuclideLib::SigmaKeV(const PhotopeakInfo &Peak, const TSpectrum &Spc) const
{
    const double Slope = Spc.SlopeAt(Peak.Position);
    if (Peak.Sigma > 0.0)
    {
        return Peak.Sigma * Slope;
    }
    if (Peak.FWHM > 0.0)
    {
        return (Peak.FWHM / 2.355) * Slope;
    }
    return 0.0;
}
//---------------------------------------------------------------------------
bool TNuclideLib::IsWithinEnergyGate(
    const double PeakEnergy,
    const double LineEnergy,
    const double SigmaE,
    const double GateFactor) const
{
    if (SigmaE <= 0.0)
    {
        return false;
    }
    return fabs(PeakEnergy - LineEnergy) <= GateFactor * 2.355 * SigmaE;
}
//---------------------------------------------------------------------------
PeakMatchResult TNuclideLib::MatchPhotopeak(
    PhotopeakInfo &Peak,
    const std::vector<TGammaLine> &GammaLines,
    const std::set<String> &DetectedSeries,
    const TSpectrum &Spc,
    const double GateFactor) const
{
    const double wE = 0.65;
    const double wP = 0.25;
    const double wS = 0.10;

    PeakMatchResult BestResult;
    BestResult.Matched = false;
    BestResult.Score = 0.0;
    size_t LineIndex = size_t(-1);

    const double SigmaE = SigmaKeV(Peak, Spc);

    for (size_t i = 0; i < GammaLines.size(); i++)
    {
        const auto& Line = GammaLines[i];
        if (!IsWithinEnergyGate(Peak.Energy, Line.Energy, SigmaE, GateFactor))
        {
            continue;
        }

        const double DeltaE = fabs(Peak.Energy - Line.Energy);
        const double EScore = ComputeEnergyScore(DeltaE, SigmaE);
        const double PScore = ComputeProbabilityScore(Line.GammaYield);
        const double SScore = ComputeSeriesScore(Line.Series, DetectedSeries);
        const double Score = wE * EScore + wP * PScore + wS * SScore;
        if (Score > BestResult.Score)
        {
            BestResult.Matched = true;
            BestResult.Score = Score;
            BestResult.Line = Line;
            LineIndex = i;
        }
    }

    if (BestResult.Matched)
    {
        Peak.LineIndex = LineIndex;
    }

    return BestResult;
}
//---------------------------------------------------------------------------
double TNuclideLib::ComputeEnergyScore(double DeltaE, double SigmaE) const
{
    if (SigmaE <= 0.0)
    {
        return 0.0;
    }
    const double X = DeltaE / SigmaE;
    return exp(-X * X);
}
//---------------------------------------------------------------------------
double TNuclideLib::ComputeProbabilityScore(double EmissionProbability) const
{
    if (EmissionProbability <= 0.0)
    {
        return 0.0;
    }
    return sqrt(EmissionProbability);
}
//---------------------------------------------------------------------------
double TNuclideLib::ComputeSeriesScore(
    const String& Series, const std::set<String>& DetectedSeries) const
{
    if (DetectedSeries.count(Series) > 0)
    {
        return 1.2;
    }
    return 1.0;
}
//---------------------------------------------------------------------------
MatchConfidence TNuclideLib::GetConfidence(const double Score) const
{
    if (Score >= 0.50)
    {
        return MatchConfidence::Confident;
    }
    if (Score >= 0.30)
    {
        return MatchConfidence::Tentative;
    }
    return MatchConfidence::None;
}

