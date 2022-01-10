//---------------------------------------------------------------------------
#ifndef BatchProcessingResultsFormUH
#define BatchProcessingResultsFormUH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.AppEvnts.hpp>
#include <Vcl.Dialogs.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <vector>
//---------------------------------------------------------------------------
#define WM_POSTRESULT WM_USER + 100

// Language ID
// 0 => Uzbek
// 1 => English
extern std::atomic<int> LangID;
//
//
//

struct TResultItem
{
	bool OK = true;
	String FileName;
	String ThActivity = L"---";
	String ThC;
	String RaActivity = L"---";
	String RaC;
	String KActivity = L"---";
	String KC;
	String CsActivity = L"---";
	String CsC;
	String BeActivity = L"---";
	String Comment;
};

class TBatchProcessingResultsForm : public TForm
{
__published:	// IDE-managed Components
	TListView *ResultsList;
	TStatusBar *StatusBar;
	TToolBar *ToolBar1;
	TImageList *ImageList;
	TApplicationEvents *AppEvents;
	TToolButton *SaveToCSVButton;
	TSaveDialog *SaveDialog;
	TActionList *ActionList;
	TAction *SaveToCSVFIleAction;
	TAction *MoveToMainWindowAction;
	TToolButton *MoveToMainButton;
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall AppEventsMessage(tagMSG &Msg, bool &Handled);
	void __fastcall ResultsListDrawItem(TCustomListView *Sender, TListItem *Item, TRect &Rect,
          TOwnerDrawState State);
	void __fastcall ResultsListCompare(TObject *Sender, TListItem *Item1, TListItem *Item2,
          int Data, int &Compare);
	void __fastcall ResultsListColumnClick(TObject *Sender, TListColumn *Column);
	void __fastcall SaveToCSVFIleActionExecute(TObject *Sender);
	void __fastcall SaveToCSVFIleActionUpdate(TObject *Sender);
	void __fastcall MoveToMainWindowActionExecute(TObject *Sender);
	void __fastcall MoveToMainWindowActionUpdate(TObject *Sender);
	void __fastcall ResultsListAdvancedCustomDrawItem(TCustomListView *Sender, TListItem *Item,
          TCustomDrawState State, TCustomDrawStage Stage, bool &DefaultDraw);


private:
	int SortColumnIndex = 0;
	bool AscSortOrder = true;
	int ErrorsCount = 0;
	String StatusSpcsStr;
	String StatusErrsStr;
	std::vector<TResultItem> ResultsVector;

protected:
	void __fastcall CreateParams(TCreateParams &Params);

public:
	__fastcall TBatchProcessingResultsForm(TComponent* Owner);
	void ChangeUILanguage();
};
//---------------------------------------------------------------------------
extern PACKAGE TBatchProcessingResultsForm *BatchProcessingResultsForm;
//---------------------------------------------------------------------------
#endif
