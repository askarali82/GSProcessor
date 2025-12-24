//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "MainFormU.h"
#include "Common.h"
#include "SpectrumFrameU.h"
#include "Spectrum.hpp"
#include "AnalysisFormU.h"
#include "SettingsFormU.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "SpectrumFrameU"
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
    : TForm(Owner),
    IniFile(new TMemIniFile(L".\\Settings.ini", TEncoding::Unicode))
{
    Application->Title = APP_NAME;
    Application->ModalPopupMode = pmAuto;
    Application->OnException = OnAppException;
    Application->HintHidePause = 8000;
    Application->HintPause = 300;
    FormatSettings.DateSeparator = L'.';
    FormatSettings.DecimalSeparator = L'.';
    FormatSettings.ShortDateFormat = L"dd.mm.yyyy";
    Caption = APP_NAME;

    SpectrumFrame = new TSpectrumFrame(this);
    SpectrumFrame->Parent = this;

    ChangeUILanguage();

    Left = IniFile->ReadInteger(L"Others", Name + L"Left", Left);
    Top = IniFile->ReadInteger(L"Others", Name + L"Top", Top);
    Width = IniFile->ReadInteger(L"Others", Name + L"Width", Width);
    Height = IniFile->ReadInteger(L"Others", Name + L"Height", Height);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::OnAppException(TObject* Sender, Exception* E)
{
    const String &Time = Now().FormatString("dd.mm.yyyy - hh:nn:ss");
    const String SenderClassName = Sender->ClassName();
    TControl *C = dynamic_cast<TControl *>(Sender);
    const String SenderName = C == 0 ? String("N/A") : C->Name;
    String SenderParentClassName("N/A");
    String SenderParentName("N/A");
    if (C != 0 && C->Parent != 0)
    {
        SenderParentClassName = C->Parent->ClassName();
        SenderParentName = C->Parent->Name;
    }
    const String ExceptionClassName = E->ClassName();
    LOG("\r\n\r\n"
         "Time: " + Time + L"\r\n"
         "Sender class: " + SenderClassName + L"\r\n"
         "Sender name: " + SenderName + L"\r\n"
         "Sender parent class: " + SenderParentClassName + L"\r\n"
         "Sender parent name: " + SenderParentName + L"\r\n"
         "Exception class: " + ExceptionClassName + L"\r\n"
         "Exception message: " + E->Message + L"\r\n");
    String ErrorMsg =
        L"Quyidagi xatolik yuz berdi. Iltimos, dasturchiga xabar bering:\r\n\r\n" + E->Message;
    if (LangID == 1)
    {
        ErrorMsg = L"The following error occurred. Please inform the developer:\r\n\r\n" + E->Message;
    }
    Application->MessageBox(ErrorMsg.c_str(), ErrorTitle.c_str(), MB_OK | MB_ICONERROR);
}
//---------------------------------------------------------------------------
void TMainForm::ChangeUILanguage()
{
    const int __LangID = LangID;

    if (__LangID == 0)
    {
        ErrorTitle = L"Xato";
    }
    else if (__LangID == 1)
    {
        ErrorTitle = L"Error";
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::OpenFileActionExecute(TObject *Sender)
{
    OpenDialog->Filter = Utils::GetDialogBoxFilterForSpectraFiles(false);
    OpenDialog->Options = OpenDialog->Options >> ofAllowMultiSelect;
    OpenDialog->FileName = L"";
    if (!OpenDialog->Execute(Handle))
    {
        return;
    }
    TSpectrum Spc;
    if (!Spc.LoadFromFile(OpenDialog->FileName))
    {
        return;
    }
    LOG(L"Opened spectrum \"" + OpenDialog->FileName + L"\"");
    LOG(L"Calibration Type: " + String(int(Spc.CalibrationType)) + L", Points: " + String(Spc.CalibrationPoints));
    Caption = APP_NAME + L" - " + OpenDialog->FileName;

    SpectrumFrame->SetSpectrum(Spc);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ReopenFileActionExecute(TObject *Sender)
{
    //
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SaveActionExecute(TObject *Sender)
{
    //
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SaveActionUpdate(TObject *Sender)
{
    SaveAction->Enabled = SpectrumFrame->CanBeSaved();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SaveAsCSVActionExecute(TObject *Sender)
{
    //
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SaveAsCSVActionUpdate(TObject *Sender)
{
    SaveAsCSVAction->Enabled = SpectrumFrame->ValidSpectrumExists();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ExitMIClick(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::DecompositionMethodActionExecute(TObject *Sender)
{
    if (AnalysisForm == nullptr)
    {
        AnalysisForm = new TAnalysisForm(Application);
    }
    AnalysisForm->Show();
    AnalysisForm->BringToFront();
    if (Sysutils::FileExists(OpenDialog->FileName) && !AnalysisForm->SpectrumExists())
    {
        AnalysisForm->PushFileNameToAnalyze(OpenDialog->FileName);
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::LinLogActionExecute(TObject *Sender)
{
    SpectrumFrame->SwitchToLinLogScale();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
    IniFile->WriteInteger(L"Others", Name + L"Left", Left);
    IniFile->WriteInteger(L"Others", Name + L"Top", Top);
    IniFile->WriteInteger(L"Others", Name + L"Width", Width);
    IniFile->WriteInteger(L"Others", Name + L"Height", Height);
    IniFile->UpdateFile();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SettingsMIClick(TObject *Sender)
{
    std::unique_ptr<TSettingsForm> Form(new TSettingsForm(Application, IniFile.get()));
    if (Form->ShowModal() != mrOk)
    {
        return;
    }
}
//---------------------------------------------------------------------------
String TMainForm::GetVersionString(const String &DefaultVal) const
{
    try
    {
        const String &FileName = Sysutils::GetModuleName(unsigned(HInstance));
        DWORD Hnd, Size = GetFileVersionInfoSizeW(FileName.c_str(), &Hnd);
        if (Size > 0)
        {
            unsigned char *Buffer = new unsigned char[Size];
            try
            {
                void *Data = nullptr;
                UINT Len = 0;
                if (GetFileVersionInfoW(FileName.c_str(), Hnd, Size, Buffer) != 0 &&
                    VerQueryValueW(Buffer, L"\\", &Data, &Len) != 0)
                {
                    VS_FIXEDFILEINFO FI;
                    CopyMemory(&FI, Data, sizeof(VS_FIXEDFILEINFO));
                    const String s1((int)HIWORD(FI.dwProductVersionMS));
                    const String s2((int)LOWORD(FI.dwProductVersionMS));
                    const String s3((int)HIWORD(FI.dwProductVersionLS));
                    return s1 + "." + s2 + "." + s3;
                }
            }
            __finally
            {
                delete [] Buffer;
            }
        }
    }
    catch (Exception &)
    {
    }
    return DefaultVal;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::AboutProgramMIClick(TObject *Sender)
{
    String Icons = L"Piktogrammalar: https://icons8.com";
    String AboutStr = L"Dastur haqida";
    String Copyright = L"Samarqand Davlat Universiteti";
    String Developer = L"Dasturchi: Asqarali Azimov";
    if (LangID == 1)
    {
        Icons = L"Icons: https://icons8.com";
        AboutStr = L"About";
        Copyright = L"Samarkand State University";
        Developer = L"Developer: Askarali Azimov";
    }

    String Version = GetVersionString();
    if (!Version.IsEmpty())
    {
        Version = L" v" + Version + L".";
    }
    const String &Message =
        String(APP_NAME + Version + L"\r\n") +
        Char(169) + L" " + Copyright + L", 2021 - 2025.\r\n\r\n" +
        Developer + L"\r\n" +
        Icons;
    Application->MessageBox(Message.c_str(), AboutStr.c_str(), MB_OK | MB_ICONINFORMATION);
}
//---------------------------------------------------------------------------

