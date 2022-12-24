//---------------------------------------------------------------------------
#ifndef MainFormUH
#define MainFormUH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <VCLTee.Chart.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.Series.hpp>
#include <Vcl.Dialogs.hpp>
#include "Spectrum.hpp"
#include <Vcl.Menus.hpp>
#include "shlobj.h"
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Buttons.hpp>
#include "BatchProcessingThreadU.h"
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
//---------------------------------------------------------------------------
// Language ID
// 0 => Uzbek
// 1 => English
extern std::atomic<int> LangID;
//
//
//
class TSettingsForm;
class TMainForm : public TForm
{
__published:
    TPanel *SamplePanel;
    TChart *SampleChart;
    TPanel *BkgPanel;
    TPanel *ThPanel;
    TPanel *RaPanel;
    TPanel *KPanel;
    TLineSeries *SampleSpectrum;
    TChart *BkgChart;
    TLineSeries *BkgSpectrum;
    TChart *ThChart;
    TLineSeries *ThSpectrum;
    TChart *RaChart;
    TLineSeries *RaSpectrum;
    TChart *KChart;
    TLineSeries *KSpectrum;
    TLineSeries *CsSpectrum;
    TLineSeries *FinalSpectrum;
    TPanel *CsPanel;
    TChart *CsChart;
    TChart *FinalSpcChart;
    TPanel *ThInfoPanel;
	TLabel *ThDurLabel;
	TLabel *ThPhotoPeakLabel;
	TLabel *ThActLabel;
	TLabel *ThMDALabel;
	TLabel *ThLabel;
	TLabel *ThSmpLabel;
    TLabel *ThCoeffLabel;
    TLabel *ThCoeffCalcLabel;
	TLabel *SmpThPhotoPeakLabel;
	TLabel *SmpThErrorLabel;
	TLabel *SmpThActLabel;
    TEdit *ThTime;
    TEdit *ThSum;
    TEdit *ThActivity;
    TEdit *ThMDA;
    TEdit *SampleThActivity;
    TEdit *ThSnSe2;
    TEdit *ThSnSe1;
    TEdit *SampleThSum;
    TEdit *SampleThError;
    TPanel *RaInfoPanel;
	TLabel *RaDurLabel;
	TLabel *RaPhotoPeakLabel;
	TLabel *RaActLabel;
	TLabel *RaMDALabel;
	TLabel *RaLabel;
	TLabel *RaSmpLabel;
    TLabel *RaCoeffLabel;
    TLabel *RaCoeffCalcLabel;
	TLabel *SmpRaPhotoPeakLabel;
	TLabel *SmpRaErrorLabel;
	TLabel *SmpRaActLabel;
    TEdit *RaTime;
    TEdit *RaSum;
    TEdit *RaActivity;
    TEdit *RaMDA;
    TEdit *SampleRaActivity;
    TEdit *RaSnSe2;
    TEdit *RaSnSe1;
    TEdit *SampleRaSum;
    TEdit *SampleRaError;
    TPanel *KInfoPanel;
	TLabel *KDurLabel;
	TLabel *KPhotoPeakLabel;
	TLabel *KActLabel;
	TLabel *KMDALabel;
	TLabel *KLabel;
	TLabel *KSmpLabel;
    TLabel *KCoeffLabel;
    TLabel *KCoeffCalcLabel;
	TLabel *SmpKPhotoPeakLabel;
	TLabel *SmpKErrorLabel;
	TLabel *SmpKActLabel;
    TEdit *KTime;
    TEdit *KSum;
    TEdit *KActivity;
    TEdit *KMDA;
    TEdit *SampleKActivity;
    TEdit *KSnSe2;
    TEdit *KSnSe1;
    TEdit *SampleKSum;
    TEdit *SampleKError;
    TPanel *CsInfoPanel;
	TLabel *CsDurLabel;
	TLabel *CsPhotoPeakLabel;
	TLabel *CsActLabel;
	TLabel *CsMDALabel;
	TLabel *CsLabel;
	TLabel *CsSmpLabel;
    TLabel *CsCoeffLabel;
    TLabel *CsCoeffCalcLabel;
	TLabel *SmpCsPhotoPeakLabel;
	TLabel *SmpCsErrorLabel;
	TLabel *SmpCsActLabel;
    TEdit *CsTime;
    TEdit *CsSum;
    TEdit *CsActivity;
    TEdit *CsMDA;
    TEdit *SampleCsActivity;
    TEdit *CsSnSe2;
    TEdit *CsSnSe1;
    TEdit *SampleCsSum;
    TEdit *SampleCsError;
    TPanel *SampleInfoPanel;
	TLabel *BePhotoPeakLabel;
    TLabel *BeActLabel;
	TLabel *BeMDALabel;
	TLabel *SmpDensityLabel;
    TEdit *BeSum;
    TEdit *BeActivityPerKgOrSq;
    TEdit *BeMDA;
    TEdit *SampleDensity;
    TEdit *SampleBeError;
	TLabel *BeErrorLabel;
    TEdit *SampleOrigMass;
	TLabel *SmpTotalMassLabel;
    TEdit *SampleSquare;
	TLabel *SmpSquareLabel;
	TLabel *SmpLabel;
    TOpenDialog *OpenDialog;
    TEdit *SampleMass;
	TLabel *SmpMassLabel;
    TEdit *SampleTime;
	TLabel *SmpDurLabel;
    TTimer *SpectraLoadTimer;
    TStatusBar *StatusBar;
    TImageList *ImageList;
    TEdit *SmpChan1Edit;
    TEdit *SmpDValEdit1;
    TEdit *SmpDValEdit2;
    TEdit *SmpChan2Edit;
    TSpeedButton *SmpCh2RightShiftBtn;
    TSpeedButton *SmpCh2LeftShiftBtn;
    TSpeedButton *SmpCh1RightShiftBtn;
    TSpeedButton *SmpCh1LeftShiftBtn;
	TLabel *SmpCh1Label;
	TLabel *SmpCh2Label;
    TTimer *ShiftingTimer;
    TSpeedButton *BkgCh1LeftShiftBtn;
    TSpeedButton *BkgCh2RightShiftBtn;
    TSpeedButton *BkgCh2LeftShiftBtn;
    TEdit *BkgDValEdit2;
    TSpeedButton *BkgCh1RightShiftBtn;
    TEdit *BkgDValEdit1;
    TEdit *BkgChan2Edit;
	TLabel *BkgCh2Label;
    TEdit *BkgChan1Edit;
	TLabel *BkgCh1Label;
    TEdit *ThDValEdit1;
    TSpeedButton *ThCh1LeftShiftBtn;
    TSpeedButton *ThCh1RightShiftBtn;
    TEdit *ThDValEdit2;
    TSpeedButton *ThCh2LeftShiftBtn;
    TSpeedButton *ThCh2RightShiftBtn;
    TEdit *ThChan2Edit;
    TLabel *ThCh2Label;
    TEdit *ThChan1Edit;
    TLabel *ThCh1Label;
    TEdit *RaDValEdit1;
    TSpeedButton *RaCh1LeftShiftBtn;
    TSpeedButton *RaCh1RightShiftBtn;
    TEdit *RaDValEdit2;
    TSpeedButton *RaCh2LeftShiftBtn;
    TSpeedButton *RaCh2RightShiftBtn;
    TEdit *RaChan2Edit;
	TLabel *RaCh2Label;
    TEdit *RaChan1Edit;
	TLabel *RaCh1Label;
    TEdit *KDValEdit1;
    TSpeedButton *KCh1LeftShiftBtn;
    TSpeedButton *KCh1RightShiftBtn;
    TEdit *KDValEdit2;
    TSpeedButton *KCh2LeftShiftBtn;
    TSpeedButton *KCh2RightShiftBtn;
    TEdit *KChan2Edit;
	TLabel *KCh2Label;
    TEdit *KChan1Edit;
	TLabel *KCh1Label;
    TEdit *CsDValEdit1;
    TSpeedButton *CsCh1LeftShiftBtn;
    TSpeedButton *CsCh1RightShiftBtn;
    TEdit *CsDValEdit2;
    TSpeedButton *CsCh2LeftShiftBtn;
    TSpeedButton *CsCh2RightShiftBtn;
    TEdit *CsChan2Edit;
	TLabel *CsCh2Label;
    TEdit *CsChan1Edit;
	TLabel *CsCh1Label;
    TEdit *Energy2Edit;
	TLabel *ThE2Label;
    TEdit *Energy1Edit;
	TLabel *ThE1Label;
	TPopupMenu *BatchProcessingPopupMenu;
	TMenuItem *SelectFilesMI;
	TMenuItem *SelectFolderMI;
	TPopupMenu *OpenPopupMenu;
	TPopupMenu *SavePopupMenu;
	TActionList *ActionList;
	TAction *OpenSpectrumAction;
	TAction *OpenParametersAction;
	TAction *SaveSpectraAction;
	TAction *SaveParametersAction;
	TMenuItem *Spektrniochish1;
	TMenuItem *Parameterlarorqaliochish1;
	TMenuItem *Spektralrnisaqlash1;
	TMenuItem *Parameterlarnisaqlash1;
	TSaveDialog *SaveDialog;
	TAction *SelectFilesAction;
	TAction *SelectDirectoryAction;
	TPanel *ToolBarPanel;
	TToolBar *ToolBar;
	TToolButton *OpenButton;
	TToolButton *SaveSpectraButton;
	TToolButton *BatchProcessButton;
	TToolButton *ShiftingButton;
	TToolButton *StandardSamplesButton;
	TAction *LanguageAction;
	TSpeedButton *SpeedButton1;
    TToolButton *HelpButton;
    TSpeedButton *ThUpButton;
    TSpeedButton *ThDownButton;
    TSpeedButton *RaDownButton;
    TSpeedButton *RaUpButton;
    TSpeedButton *KDownButton;
    TSpeedButton *KUpButton;
    TSpeedButton *CsDownButton;
    TSpeedButton *CsUpButton;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TLabel *Label5;
    TLabel *BeSmpLabel;
    void __fastcall FormResize(TObject *Sender);
    void __fastcall StandardSamplesButtonClick(TObject *Sender);
    void __fastcall SpectraLoadTimerTimer(TObject *Sender);
    void __fastcall OnParamChange(TObject *Sender);
    void __fastcall OnChartMouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y);
    void __fastcall ParamEditClick(TObject *Sender);
    void __fastcall HelpButtonClick(TObject *Sender);
    void __fastcall ShiftingButtonClick(TObject *Sender);
    void __fastcall OnShiftingDataChange(TObject *Sender);
    void __fastcall OnCh1LeftShiftBtnClick(TObject *Sender);
    void __fastcall OnCh1RightShiftBtnClick(TObject *Sender);
    void __fastcall OnCh2LeftShiftBtnClick(TObject *Sender);
    void __fastcall OnCh2RightShiftBtnClick(TObject *Sender);
    void __fastcall OnShiftingTimerTimer(TObject *Sender);
	void __fastcall OpenSpectrumActionExecute(TObject *Sender);
	void __fastcall OpenParametersActionExecute(TObject *Sender);
	void __fastcall SaveSpectraActionExecute(TObject *Sender);
	void __fastcall SaveParametersActionExecute(TObject *Sender);
	void __fastcall SelectFilesActionExecute(TObject *Sender);
	void __fastcall SelectDirectoryActionExecute(TObject *Sender);
	void __fastcall LanguageActionExecute(TObject *Sender);
	void __fastcall OpenButtonClick(TObject *Sender);
	void __fastcall SaveSpectraButtonClick(TObject *Sender);
	void __fastcall BatchProcessButtonClick(TObject *Sender);
    void __fastcall ThCoeffCalcLabelClick(TObject *Sender);
    void __fastcall RaCoeffCalcLabelClick(TObject *Sender);
    void __fastcall KCoeffCalcLabelClick(TObject *Sender);
    void __fastcall CsCoeffCalcLabelClick(TObject *Sender);
    void __fastcall OnEditUpButtonClick(TObject *Sender);
    void __fastcall OnKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall OnEditDownButtonClick(TObject *Sender);
    void __fastcall SampleChartDblClick(TObject *Sender);
    void __fastcall BeActLabelClick(TObject *Sender);


private:
    const String AppName;
    // Experimental spectra
    TSpectrum OrigSampleSpc;
    TSpectrum SampleSpc;
    TSpectrum Bkgs[3];
    TSpectrum Ths[3];
    TSpectrum Ras[3];
    TSpectrum Ks[3];
    TSpectrum Css[3];

    // Virtual spectra
    TSpectrum OrigBkgSpc;
    TSpectrum BkgSpc;
    TSpectrum BkgSpcWithCoeff;
    TSpectrum Sample_M_Bkg;

    TSpectrum OrigThSpc;
    TSpectrum ThSpc;
    TSpectrum ThSpcWithCoeff;
    TSpectrum Sample_M_Th;

    TSpectrum OrigRaSpc;
    TSpectrum RaSpc;
    TSpectrum RaSpcWithCoeff;
    TSpectrum Sample_M_Ra;

    TSpectrum OrigKSpc;
    TSpectrum KSpc;
    TSpectrum KSpcWithCoeff;
    TSpectrum Sample_M_K;

    TSpectrum OrigCsSpc;
    TSpectrum CsSpc;
    TSpectrum CsSpcWithCoeff;
    TSpectrum Sample_M_Cs;

    // Sums
	double ThCount = 0;
	double RaCount = 0;
	double KCount = 0;
	double CsCount = 0;

    // Std samples activity errors
	double ThActivityErrors[3] = {0, 0, 0};
	double RaActivityErrors[3] = {0, 0, 0};
	double KActivityErrors[3]  = {0, 0, 0};
	double CsActivityErrors[3] = {0, 0, 0};

    // Energy ranges
    double ThEn1 = 0;
    double ThEn2 = 0;
    double RaEn1 = 0;
    double RaEn2 = 0;
    double KEn1 = 0;
    double KEn2 = 0;
    double CsEn1 = 0;
    double CsEn2 = 0;
	double BeEn1 = 0;
	double BeEn2 = 0;

    double BePhotopeakEff1;
    double BePhotopeakEff2;
    double BePhotopeakEff3;

	//Search peaks
	double MinPeakWidth;
    double MaxEnergyError;

    // Coefficients
    double ThC = 0;
    double RaC = 0;
    double KC = 0;
    double CsC = 0;

    // Miscl.
	wchar_t DispName[MAX_PATH];
	BROWSEINFOW BrowseInfo;
	String SampleFileName;

	std::unique_ptr<TBatchProcessingThread> BatchProcessingThread;
	TData GetData() const;

	// Strings
	String ErrorTitle;
	String DirSelectionString;

    String BeActivityPerKilogram;
    String BeActivityPerSquare;

    String BeErrorPerKilogram;
    String BeErrorPerSquare;


	void InitStdSamples(TSettingsForm *Form);
    void SubtractBkgFromStandardSources(const int Idx);
	void CreateVirtualSpectra();
    void CalculateCountsInStdSamples();
	void DrawSpectrum(const TSpectrum &Spc, TLineSeries *LineSeries);
    bool OpenSampleSpectrum(const String &FileName);
    void DecomposeSampleSpectrum();
    void PopulateStandardSourcesInfo(TSettingsForm *Settings);
    void SetEnergyRanges(TSettingsForm *Settings);
    bool ValidSpectra(const int Idx) const;
    int FindChannelByEnergy(const double En, TLineSeries *Spc) const;
    void CalculateMDAs(const TSpectrum &Bkg, double &MDATh, double &MDARa, double &MDAK, double &MDACs, double &MDABe) const;
    String GetVersionString(const String &DefaultVal = L"") const;
    bool ShiftSrc();
    bool ShiftBkg();
    bool ShiftTh();
    bool ShiftRa();
    bool ShiftK();
    bool ShiftCs();
	int CalcCenterOfPeak(const TSpectrum &Spc, const double Energy) const;
	void SaveParametersFile(const String &FileName);
	void ChangeUILanguage();
    void __fastcall OnAppException(TObject* Sender, Exception* E);

public:
    __fastcall TMainForm(TComponent* Owner);
	__fastcall ~TMainForm();
	void OpenFromBatchResult(
		const String &FileName,
		const String &ThC,
		const String &RaC,
		const String &KC,
		const String &CsC);
    void SetSampleSpectrum(const TSpectrum &ShiftedSpc, const String &Ch1Str, const String &Ch2Str);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
