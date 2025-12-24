//---------------------------------------------------------------------------

#ifndef MainFormUH
#define MainFormUH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ComCtrls.hpp>
#include "SpectrumFrameU.h"
#include <Vcl.Dialogs.hpp>
#include <System.IniFiles.hpp>
//---------------------------------------------------------------------------
// Language ID
// 0 => Uzbek
// 1 => English
extern std::atomic<int> LangID;
//
//
//
//---------------------------------------------------------------------------
class TSpectrumFrame;
class TMainForm : public TForm
{
__published:	// IDE-managed Components
    TMainMenu *MainMenu;
    TActionList *ActionList;
    TAction *OpenFileAction;
    TMenuItem *File;
    TMenuItem *Analyze;
    TMenuItem *Help;
    TAction *ReopenFileAction;
    TMenuItem *OpenMI;
    TMenuItem *ReopenMI;
    TMenuItem *N1;
    TMenuItem *FileName1_MI;
    TMenuItem *Tools;
    TAction *SaveAction;
    TAction *SaveAsCSVAction;
    TMenuItem *SaveMI;
    TMenuItem *SaveAsCSVMI;
    TMenuItem *N2;
    TMenuItem *ExitMI;
    TOpenDialog *OpenDialog;
    TAction *DecompositionMethodAction;
    TMenuItem *DecompositionMI;
    TMenuItem *SettingsMI;
    TMenuItem *UserManualMI;
    TMenuItem *AboutProgramMI;
    TAction *LinLogAction;
    TMenuItem *est1;
    void __fastcall OpenFileActionExecute(TObject *Sender);
    void __fastcall ReopenFileActionExecute(TObject *Sender);
    void __fastcall SaveActionExecute(TObject *Sender);
    void __fastcall SaveActionUpdate(TObject *Sender);
    void __fastcall SaveAsCSVActionExecute(TObject *Sender);
    void __fastcall ExitMIClick(TObject *Sender);
    void __fastcall DecompositionMethodActionExecute(TObject *Sender);
    void __fastcall SaveAsCSVActionUpdate(TObject *Sender);
    void __fastcall LinLogActionExecute(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall SettingsMIClick(TObject *Sender);
    void __fastcall AboutProgramMIClick(TObject *Sender);

private:
    String ErrorTitle;
    TSpectrumFrame *SpectrumFrame;
    std::unique_ptr<TMemIniFile> IniFile;

    void __fastcall OnAppException(TObject* Sender, Exception* E);
    void ChangeUILanguage();
    String GetVersionString(const String &DefaultVal = L"") const;

public:
    __fastcall TMainForm(TComponent* Owner);
    TMemIniFile *GetIniFile()
    {
        return IniFile.get();
    }
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
