//---------------------------------------------------------------------------
#ifndef SpectrumFrameUH
#define SpectrumFrameUH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Grids.hpp>
#include "Spectrum.hpp"
#include <Vcl.Menus.hpp>
#include <unordered_map>
#include "peaks/PhotopeakSearcher.h"
#include "NuclideLibU.h"
//---------------------------------------------------------------------------
extern std::atomic<int> LangID;
//---------------------------------------------------------------------------
class TSpectrumFrame : public TFrame
{
__published:
    TChart *SpcChart;
    TLineSeries *SpectrumLine;
    TPageControl *PageControl;
    TSplitter *Splitter;
    TTabSheet *ParametersTab;
    TEdit *LiveTimeEdit;
    TEdit *RealTimeEdit;
    TEdit *SampleMassEdit;
    TEdit *SampleVolumeEdit;
    TComboBox *SampleMassUnitBox;
    TComboBox *SampleVolumeUnitBox;
    TGroupBox *EnCalGroupBox;
    TEdit *Energy1Edit;
    TEdit *Channel1Edit;
    TEdit *Energy2Edit;
    TEdit *Channel2Edit;
    TEdit *Energy4Edit;
    TEdit *Channel4Edit;
    TEdit *Energy3Edit;
    TEdit *Channel3Edit;
    TEdit *Energy5Edit;
    TEdit *Channel5Edit;
    TLabel *PointsLabel;
    TComboBox *PointsBox;
    TTabSheet *RawDataTab;
    TEdit *CPSEdit;
    TEdit *TotalCountEdit;
    TStringGrid *RawDataTable;
    TStatusBar *StatusBar;
    TPanel *SpectrumPanel;
    TLabel *LiveTimeLabel;
    TLabel *RealTimeLabel;
    TLabel *TotalCountLabel;
    TLabel *SampleVolumeLabel;
    TLabel *SampleMassLabel;
    TLabel *IntensityLabel;
    TLabel *Chan1Label;
    TLabel *Chan2Label;
    TLabel *Chan3Label;
    TLabel *Chan4Label;
    TLabel *Chan5Label;
    TLabel *Label13;
    TLabel *Label14;
    TLabel *Label15;
    TLabel *Label16;
    TLabel *Label17;
    TLabel *Energy1Label;
    TLabel *Energy2Label;
    TLabel *Energy3Label;
    TLabel *Energy4Label;
    TLabel *Energy5Label;
    TPanel *Panel1;
    TButton *CalibrateButton;
    TTabSheet *PeakInfoTab;
    TPanel *Panel2;
    TLabel *EnergyLabel;
    TLabel *EnergyValueLabel;
    TLabel *NucleusNameLabel;
    TLabel *NucleusLabel;
    TLabel *EmitterLabel;
    TLabel *EmitterNameLabel;
    TLabel *SeriesNameLabel;
    TLabel *SeriesLabel;
    TLabel *GammaYieldLabel;
    TLabel *GammaYieldValueLabel;
    TPopupMenu *TablePopupMenu;
    TMenuItem *CopyMI;
    void __fastcall SpcChartMouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y);
    void __fastcall SpcChartAfterDraw(TObject *Sender);
    void __fastcall PointsBoxChange(TObject *Sender);
    void __fastcall OnDataChange(TObject *Sender);
    void __fastcall CalibrateButtonClick(TObject *Sender);
    void __fastcall OnFValueEditKeyPress(TObject *Sender, System::WideChar &Key);
    void __fastcall RawDataTableMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
    void __fastcall RawDataTableKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall PageControlDrawTab(TCustomTabControl *Control, int TabIndex,
          const TRect &Rect, bool Active);
    void __fastcall PeakInfoTabShow(TObject *Sender);
    void __fastcall CopyMIClick(TObject *Sender);
    void __fastcall RawDataTableMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);





private:
    TSpectrum Spectrum;
    bool Modified;
    std::unordered_map<TEdit*, String> LastValidTexts;
    std::vector<PhotopeakInfo> Photopeaks;

    void CopySelectedCells();
    void OnEditBoxChange(TEdit *Edit);
    void ShowPeakDetails(const PhotopeakInfo &Peak);
    void ClearPeakDetails();

public:
    __fastcall TSpectrumFrame(TComponent* Owner);
    void SetSpectrum(const TSpectrum &ASpectrum);
    bool SaveSpectrumToFile(const String &FileName);
    bool SaveSpectrumToTextFile(
        const String &FileName, const bool IncludeChannels, const bool IncludeEnergies) const;
    bool CanBeSaved() const
    {
        return Spectrum.IsValid() && Modified;
    }
    bool ValidSpectrumExists() const
    {
        return Spectrum.IsValid();
    }
    bool SwitchToLinLogScale();
    bool FindPhotopeaks(const bool NeedsFound);
    void ChangeUILanguage();
};
//---------------------------------------------------------------------------
#endif
