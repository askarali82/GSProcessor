//---------------------------------------------------------------------------
#ifndef ShiftingFormUH
#define ShiftingFormUH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <Vcl.Buttons.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Dialogs.hpp>
#include "Spectrum.hpp"
#include <Vcl.Menus.hpp>
//---------------------------------------------------------------------------
// Language ID
// 0 => Uzbek
// 1 => English
extern std::atomic<int> LangID;
//
//
//
class TShiftingForm : public TForm
{
__published:	// IDE-managed Components
    TToolBar *ToolBar;
    TToolButton *Spectrum1Button;
    TToolButton *Spectrum2Button;
    TChart *SpcChart;
    TLineSeries *Spectrum1;
    TSpeedButton *LogLinButton;
    TLineSeries *Spectrum2;
    TImageList *ImageList1;
    TOpenDialog *OpenDialog;
    TEdit *Energy1Edit;
    TEdit *Energy2Edit;
    TEdit *SrcChan2Edit;
    TEdit *SrcChan1Edit;
    TEdit *SmpChan2Edit;
    TEdit *SmpChan1Edit;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TLabel *Label5;
    TLabel *Label6;
    TLabel *Label7;
    TLabel *Label8;
    TSpeedButton *Ch1LeftShiftBtn;
    TSpeedButton *Ch1RightShiftBtn;
    TSpeedButton *Ch2LeftShiftBtn;
    TSpeedButton *Ch2RightShiftBtn;
    TEdit *DValEdit2;
    TEdit *DValEdit1;
    TStatusBar *StatusBar;
    TPopupMenu *PopupMenu;
	TMenuItem *Spectrum1_MI;
	TMenuItem *Spectrum2_MI;
    TToolButton *SaveSpectrum2;
    TPopupMenu *SaveButtonPopupMenu;
	TMenuItem *SaveToTXTMI;
	TMenuItem *SaveToASWMI;
	TMenuItem *ClipboardMI;
    TTimer *ShiftingTimer;
    TToolButton *AboutBtnSeparator;
    TToolButton *AboutButton;
    TMenuItem *CopyCountsMI;
    TMenuItem *CopyEnergiesAndCountMI;
    TMenuItem *SaveCountsMI;
    TMenuItem *SaveEnergiesAndCountsMI;
	TToolButton *ToolButton1;
	TToolButton *ToolButton2;
	TMenuItem *SaveToGSPMI;
    void __fastcall LogLinButtonClick(TObject *Sender);
    void __fastcall Spectrum1ButtonClick(TObject *Sender);
    void __fastcall Spectrum2ButtonClick(TObject *Sender);
    void __fastcall Ch1LeftShiftBtnClick(TObject *Sender);
    void __fastcall Ch1RightShiftBtnClick(TObject *Sender);
    void __fastcall Ch2LeftShiftBtnClick(TObject *Sender);
    void __fastcall Ch2RightShiftBtnClick(TObject *Sender);
    void __fastcall SpcChartMouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y);
    void __fastcall OnDataEditChange(TObject *Sender);
    void __fastcall Spectrum1_MIClick(TObject *Sender);
    void __fastcall Spectrum2_MIClick(TObject *Sender);
    void __fastcall SaveToASWMIClick(TObject *Sender);
    void __fastcall OnShiftingTimerTimer(TObject *Sender);
    void __fastcall OpenDialogClose(TObject *Sender);
    void __fastcall AboutButtonClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall CopyCountsMIClick(TObject *Sender);
    void __fastcall CopyEnergiesAndCountMIClick(TObject *Sender);
    void __fastcall SaveCountsMIClick(TObject *Sender);
    void __fastcall SaveEnergiesAndCountsMIClick(TObject *Sender);
	void __fastcall SaveToGSPMIClick(TObject *Sender);

protected:
    void __fastcall CreateParams(TCreateParams &Params);

private:
    String AppName;
    TSpectrum Sample1;
	TSpectrum Sample2;
    TSpectrum ShiftedSample2;
	String Sample1FileName;
	String Sample2FileName;
	String ChannelStr;
	String EnergyStr;
	String Count1Str;
	String Count2Str;
	String GetVersionString(const String &DefaultVal = L"") const;
	void DrawSpectrum(const TSpectrum &Spc, TLineSeries *LineSeries);
	void Shift();
    void SaveToOriginalFile();
    void __fastcall OnAppException(TObject* Sender, Exception* E);

public:
	__fastcall TShiftingForm(TComponent* Owner);
    void ChangeUILanguage();
};
//---------------------------------------------------------------------------
extern PACKAGE TShiftingForm *ShiftingForm;
//---------------------------------------------------------------------------
#endif
