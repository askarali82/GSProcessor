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
    TMenuItem *OpenMI;
    TMenuItem *ReopenMI;
    TMenuItem *N1;
    TMenuItem *Tools;
    TAction *SaveAction;
    TMenuItem *SaveMI;
    TMenuItem *SaveInTextFormatMI;
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
    TMenuItem *OnlyCountsMI;
    TMenuItem *CountsInChannelsMI;
    TMenuItem *CountsInEnergiesMI;
    TSaveDialog *SaveDialog;
    TMenuItem *Chiziqlimasshtab1;
    void __fastcall OpenFileActionExecute(TObject *Sender);
    void __fastcall SaveActionExecute(TObject *Sender);
    void __fastcall SaveActionUpdate(TObject *Sender);
    void __fastcall ExitMIClick(TObject *Sender);
    void __fastcall DecompositionMethodActionExecute(TObject *Sender);
    void __fastcall LinLogActionExecute(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall SettingsMIClick(TObject *Sender);
    void __fastcall AboutProgramMIClick(TObject *Sender);
    void __fastcall OnSaveInTextFormatMIClick(TObject *Sender);
    void __fastcall LinLogActionUpdate(TObject *Sender);

private:
    String ErrorTitle;
    String SpectrumFileName;
    TSpectrumFrame *SpectrumFrame;
    std::unique_ptr<TMemIniFile> IniFile;
    std::unique_ptr<TStringList> RecentFiles;

    void __fastcall OnAppException(TObject* Sender, Exception* E);
    void ChangeUILanguage();
    String GetVersionString(const String &DefaultVal = L"") const;
    bool OpenSpectrum(const String &FileName);
    void __fastcall OpenRecentFile(TObject* Sender);

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
