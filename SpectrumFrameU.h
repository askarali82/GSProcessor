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
#include <unordered_map>
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
    TTabSheet *InformationTab;
    TEdit *LiveTimeEdit;
    TEdit *RealTimeEdit;
    TEdit *SampleMassEdit;
    TEdit *SampleVolumeEdit;
    TComboBox *SampleMassUnitBox;
    TComboBox *SampleVolumeUnitBox;
    TGroupBox *GroupBox1;
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
    TLabel *Label1;
    TComboBox *PointsBox;
    TTabSheet *RawDataTab;
    TEdit *CPSEdit;
    TEdit *TotalCountEdit;
    TStringGrid *RawDataTable;
    TStatusBar *StatusBar;
    TPanel *SpectrumPanel;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TLabel *Label5;
    TLabel *Label6;
    TLabel *Label7;
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
    void __fastcall SpcChartMouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y);
    void __fastcall SpcChartAfterDraw(TObject *Sender);
    void __fastcall PointsBoxChange(TObject *Sender);
    void __fastcall OnDataChange(TObject *Sender);
    void __fastcall CalibrateButtonClick(TObject *Sender);
    void __fastcall OnFValueEditKeyPress(TObject *Sender, System::WideChar &Key);



private:
    TSpectrum Spectrum;
    bool Modified;
    std::unordered_map<TEdit*, String> LastValidTexts;

    void OnEditBoxChange(TEdit *Edit);

public:
    __fastcall TSpectrumFrame(TComponent* Owner);
    void SetSpectrum(const TSpectrum &ASpectrum);
    bool CanBeSaved() const
    {
        return Spectrum.IsValid() && Modified;
    }
    bool ValidSpectrumExists() const
    {
        return Spectrum.IsValid();
    }
    void SwitchToLinLogScale();
};
//---------------------------------------------------------------------------
#endif
