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
#pragma comment(lib, "bin/peaks_omf.lib")
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
    : TForm(Owner),
    RecentFiles(new TStringList())
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

    CreateSettingsFile();
    IniFile = std::make_unique<TMemIniFile>(
        Utils::GetAppFolder() + SETTINGS_FILE_NAME, TEncoding::Unicode);

    SpectrumFrame = new TSpectrumFrame(this);
    SpectrumFrame->Parent = this;

    int LangID = IniFile->ReadString(L"UILanguage", L"LangID", L"0").ToIntDef(0);
    if (LangID < 0 || LangID > 1)
    {
        LangID = 0;
    }
    ::LangID = LangID;

    ChangeUILanguage();

    Left = IniFile->ReadInteger(L"Others", Name + L"Left", Left);
    Top = IniFile->ReadInteger(L"Others", Name + L"Top", Top);
    Width = IniFile->ReadInteger(L"Others", Name + L"Width", Width);
    Height = IniFile->ReadInteger(L"Others", Name + L"Height", Height);

    RecentFiles->CaseSensitive = false;
    IniFile->ReadSectionValues(L"RecentFiles", RecentFiles.get());
    while (RecentFiles->Count > 10)
    {
        RecentFiles->Delete(0);
    }
    int NExistingFiles = 0;
    for (int i = RecentFiles->Count - 1; i >= 0; i--)
    {
        const int P = RecentFiles->Strings[i].Pos(L"=");
        if (P > 0)
        {
            const String &FileName =
                RecentFiles->Strings[i].SubString(P + 1, RecentFiles->Strings[i].Length()).Trim();
            RecentFiles->Strings[i] = FileName;
            if (Sysutils::FileExists(FileName))
            {
                TMenuItem *MenuItem = new TMenuItem(ReopenMI);
                MenuItem->OnClick = OpenRecentFile;
                MenuItem->Caption = FileName;
                ReopenMI->Add(MenuItem);
                NExistingFiles++;
            }
        }
    }
    ReopenMI->Visible = NExistingFiles > 0;
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
void TMainForm::CreateSettingsFile()
{
    const String &SettingsFileName = Utils::GetAppFolder() + SETTINGS_FILE_NAME;
    if (!Sysutils::FileExists(SettingsFileName))
    {
        try
        {
            std::unique_ptr<TStringList> TextFile(new TStringList());
            TextFile->DefaultEncoding = TEncoding::Unicode;
            TextFile->Text =
                L"[EnergyRanges]\r\n"
                L"ThEnergy1Edit=2500\r\n"
                L"ThEnergy2Edit=2720\r\n"
                L"RaEnergy1Edit=1677\r\n"
                L"RaEnergy2Edit=1846\r\n"
                L"KEnergy1Edit=1385\r\n"
                L"KEnergy2Edit=1540\r\n"
                L"CsEnergy1Edit=612\r\n"
                L"CsEnergy2Edit=709\r\n"
                L"BeEnergy1Edit=430\r\n"
                L"BeEnergy2Edit=525\r\n\r\n"

                L"[PeakSearch]\r\n"
                L"MinPeakWidth=100\r\n"
                L"MaxEnergyError=0.2\r\n\r\n"

                L"[UILanguage]\r\n"
                L"LangID=0\r\n\r\n"

                L"[Others]\r\n"
                L"ShowResultsWithMDA=1\r\n";
            TextFile->SaveToFile(SettingsFileName);
        }
        catch (Exception &)
        {

        }
    }
}
//---------------------------------------------------------------------------
void TMainForm::ChangeUILanguage()
{
    const int __LangID = LangID;

    TSpectrum::SetLanguage();

    if (__LangID == 0)
    {
        ErrorTitle = L"Xato";

        File->Caption = L"&Fayl";
        OpenAction->Caption = L"&Ochish";
        ReopenMI->Caption = L"&Qaytadan ochish";
        SaveAction->Caption = L"&Saqlash";
        SaveInTextFormatMI->Caption = L"&Matnli formatda saqlash";
        OnlyCountsMI->Caption = L"Faqat impulslar soni";
        CountsInChannelsMI->Caption = L"Impulslar soni kanal masshtabida";
        CountsInEnergiesMI->Caption = L"Impulslar soni energiya masshtabida";
        ExitAction->Caption = L"&Chiqish";

        Analyze->Caption = L"&Tahlil";
        DecompositionMethodAction->Caption = L"Tarkibiy &qismlarga ajratish";
        BatchProcessingMI->Caption = L"&Ko‘p sonli spektrlarni tahlil qilish";
        BatchProcessing_FilesAction->Caption = L"Fayllarni tanlash";
        BatchProcessing_FolderAction->Caption = L"Manzilni tanlash";

        Tools->Caption = L"&Asboblar";
        SettingsAction->Caption = L"&Sozlamalar";
        LinLogAction->Caption = L"&Chiziqli masshtab";
        PhotopeaksAction->Caption = L"&Fotocho‘qqilar";

        Help->Caption = L"&Yordam";
        HelpAction->Caption = L"&Qo‘llanma";
        AboutProgramMI->Caption = APP_NAME + L" &haqida...";
    }
    else if (__LangID == 1)
    {
        ErrorTitle = L"Error";

        File->Caption = L"&File";
        OpenAction->Caption = L"&Open";
        ReopenMI->Caption = L"&Reopen";
        SaveAction->Caption = L"&Save";
        SaveInTextFormatMI->Caption = L"&Save in plain text file";
        OnlyCountsMI->Caption = L"Only counts";
        CountsInChannelsMI->Caption = L"Counts in channel scale";
        CountsInEnergiesMI->Caption = L"Counts in energy scale";
        ExitAction->Caption = L"&Exit";

        Analyze->Caption = L"&Analysis";
        DecompositionMethodAction->Caption = L"&Decomposition method (manual way)";
        BatchProcessingMI->Caption = L"&Batch processing";
        BatchProcessing_FilesAction->Caption = L"Select &files";
        BatchProcessing_FolderAction->Caption = L"Select &directory/folder";

        Tools->Caption = L"&Tools";
        SettingsAction->Caption = L"&Settings";
        LinLogAction->Caption = L"&Linear scale";
        PhotopeaksAction->Caption = L"&Photopeaks";

        Help->Caption = L"&Help";
        HelpAction->Caption = L"&User manual";
        AboutProgramMI->Caption = L"&About " + APP_NAME + L"...";
    }

    SpectrumFrame->ChangeUILanguage();

    if (AnalysisForm != nullptr)
    {
        AnalysisForm->ChangeUILanguage();
    }
}
//---------------------------------------------------------------------------
bool TMainForm::OpenSpectrum(const String &FileName)
{
    TSpectrum Spc;
    if (!Spc.LoadFromFile(FileName))
    {
        return false;
    }
    SpectrumFileName = FileName;
    LOG(L"Opened spectrum \"" + FileName + L"\"");
    LOG(L"Calibration Type: " + String(int(Spc.CalibrationType)) + L", Points: " + String(Spc.CalibrationPoints));
    LOG(L"Calibration: A = " + String(Spc.A) + L", B = " + String(Spc.B) + L", C = " + String(Spc.C));
    Caption = APP_NAME + L" - " + FileName;
    SpectrumFrame->SetSpectrum(Spc);
    SaveInTextFormatMI->Enabled = SpectrumFrame->ValidSpectrumExists();
    return true;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::OpenActionExecute(TObject *Sender)
{
    OpenDialog->Filter = Utils::GetDialogBoxFilterForSpectraFiles(false);
    OpenDialog->Options = OpenDialog->Options >> ofAllowMultiSelect;
    OpenDialog->FileName = L"";
    if (!OpenDialog->Execute(Handle) || !OpenSpectrum(OpenDialog->FileName))
    {
        return;
    }
    if (PhotopeaksAction->Checked)
    {
        PhotopeaksAction->Execute();
    }

    if (RecentFiles->IndexOf(OpenDialog->FileName) == -1)
    {
        RecentFiles->Add(OpenDialog->FileName);
        if (RecentFiles->Count > 10)
        {
            RecentFiles->Delete(0);
        }
        TMenuItem *MenuItem = new TMenuItem(ReopenMI);
        MenuItem->OnClick = OpenRecentFile;
        MenuItem->Caption = OpenDialog->FileName;
        ReopenMI->Insert(0, MenuItem);
        if (ReopenMI->Count > 10)
        {
            ReopenMI->Items[ReopenMI->Count - 1]->Visible = false;
        }
        ReopenMI->Visible = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::OpenRecentFile(TObject *Sender)
{
    TMenuItem *MenuItem = dynamic_cast<TMenuItem *>(Sender);
    OpenSpectrum(Sysutils::StringReplace(MenuItem->Caption, "&", "", TReplaceFlags() << rfReplaceAll));
    if (PhotopeaksAction->Checked)
    {
        PhotopeaksAction->Execute();
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SaveActionExecute(TObject *Sender)
{
    SpectrumFrame->SaveSpectrumToFile(SpectrumFileName);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SaveActionUpdate(TObject *Sender)
{
    SaveAction->Enabled = SpectrumFrame->CanBeSaved();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::LinLogActionExecute(TObject *Sender)
{
    LinLogAction->Checked = SpectrumFrame->SwitchToLinLogScale();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::LinLogActionUpdate(TObject *Sender)
{
    LinLogAction->Enabled = SpectrumFrame->SpectrumLine->Count() > 0;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
    try
    {
        IniFile->WriteInteger(L"Others", Name + L"Left", Left);
        IniFile->WriteInteger(L"Others", Name + L"Top", Top);
        IniFile->WriteInteger(L"Others", Name + L"Width", Width);
        IniFile->WriteInteger(L"Others", Name + L"Height", Height);
        IniFile->EraseSection(L"RecentFiles");
        for (int i = 0; i < RecentFiles->Count; i++)
        {
            IniFile->WriteString(L"RecentFiles", i, RecentFiles->Strings[i]);
        }
        IniFile->UpdateFile();
    }
    catch (const Exception &E)
    {
        LOG(E.Message);
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
    String Copyright = L"Samarqand Davlat Universiteti, Asqarali Azimov";
    String Developer = L"Dasturchi: Asqarali Azimov";
    if (LangID == 1)
    {
        Icons = L"Icons: https://icons8.com";
        AboutStr = L"About";
        Copyright = L"Samarkand State University, Askarali Azimov";
        Developer = L"Developer: Askarali Azimov";
    }

    String Version = GetVersionString();
    if (!Version.IsEmpty())
    {
        Version = L" v" + Version + L".";
    }
    const String &Message =
        String(APP_NAME + Version + L"\r\n") +
        Char(169) + L" " + Copyright + L", 2022 - 2026.\r\n\r\n" +
        Developer + L"\r\n" +
        Icons;
    Application->MessageBox(Message.c_str(), AboutStr.c_str(), MB_OK | MB_ICONINFORMATION);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::OnSaveInTextFormatMIClick(TObject *Sender)
{
    SaveDialog->FileName = SpectrumFileName + L".txt";
    if (!SaveDialog->Execute(Handle))
    {
        return;
    }
    SpectrumFrame->SaveSpectrumToTextFile(
        SaveDialog->FileName, Sender == CountsInChannelsMI, Sender == CountsInEnergiesMI);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::PhotopeaksActionExecute(TObject *Sender)
{
    if (PhotopeaksAction->Checked)
    {
        if (SpectrumFrame->FindPhotopeaks(false))
        {
            PhotopeaksAction->Checked = false;
        }
    }
    else if (SpectrumFrame->FindPhotopeaks(true))
    {
        PhotopeaksAction->Checked = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::PhotopeaksActionUpdate(TObject *Sender)
{
    PhotopeaksAction->Enabled = SpectrumFrame->SpectrumLine->Count() > 0;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::DecompositionMethodActionExecute(TObject *Sender)
{
    if (AnalysisForm == nullptr)
    {
        AnalysisForm = new TAnalysisForm(Application);
        if (!AnalysisForm->Initialize())
        {
            return;
        }
    }
    if (Sysutils::FileExists(SpectrumFileName) && !AnalysisForm->SpectrumExists())
    {
        AnalysisForm->PushFileNameToAnalyze(SpectrumFileName);
    }
    AnalysisForm->Show();
    AnalysisForm->BringToFront();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::BatchProcessing_FilesActionExecute(TObject *Sender)
{
    if (AnalysisForm == nullptr)
    {
        AnalysisForm = new TAnalysisForm(Application);
        if (!AnalysisForm->Initialize())
        {
            return;
        }
    }
    AnalysisForm->SelectFilesAction->Execute();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::BatchProcessing_FolderActionExecute(TObject *Sender)
{
    if (AnalysisForm == nullptr)
    {
        AnalysisForm = new TAnalysisForm(Application);
        if (!AnalysisForm->Initialize())
        {
            return;
        }
    }
    AnalysisForm->SelectDirectoryAction->Execute();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SettingsActionExecute(TObject *Sender)
{
    const int PrevLangID = LangID;
    std::unique_ptr<TSettingsForm> Form(new TSettingsForm(Application, IniFile.get()));
    if (Form->ShowModal() != mrOk)
    {
        return;
    }
    if (AnalysisForm != nullptr)
    {
        AnalysisForm->Initialize();
    }
    if (LangID != PrevLangID)
    {
        ChangeUILanguage();
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ExitActionExecute(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------

