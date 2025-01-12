//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "SettingsFormU.h"
#include <System.Win.Registry.hpp>
#include <memory>
#include "Spectrum.hpp"
#include "Common.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TSettingsForm::TSettingsForm(TComponent* Owner):
    TForm(Owner),
    IniFile(new TMemIniFile(L".\\Settings.ini", TEncoding::Unicode))
{
    IniFile->CaseSensitive = false;
    Th1Button->Tag = reinterpret_cast<NativeInt>(Th1FileName);
    Ra1Button->Tag = reinterpret_cast<NativeInt>(Ra1FileName);
    K1Button->Tag = reinterpret_cast<NativeInt>(K1FileName);
    Cs1Button->Tag = reinterpret_cast<NativeInt>(Cs1FileName);
    Bkg1Button->Tag = reinterpret_cast<NativeInt>(Bkg1FileName);

    Th2Button->Tag = reinterpret_cast<NativeInt>(Th2FileName);
    Ra2Button->Tag = reinterpret_cast<NativeInt>(Ra2FileName);
    K2Button->Tag = reinterpret_cast<NativeInt>(K2FileName);
    Cs2Button->Tag = reinterpret_cast<NativeInt>(Cs2FileName);
    Bkg2Button->Tag = reinterpret_cast<NativeInt>(Bkg2FileName);

    Th3Button->Tag = reinterpret_cast<NativeInt>(Th3FileName);
    Ra3Button->Tag = reinterpret_cast<NativeInt>(Ra3FileName);
    K3Button->Tag = reinterpret_cast<NativeInt>(K3FileName);
    Cs3Button->Tag = reinterpret_cast<NativeInt>(Cs3FileName);
    Bkg3Button->Tag = reinterpret_cast<NativeInt>(Bkg3FileName);

    LoadDensity_1_Data();
    LoadDensity_2_Data();
    LoadDensity_3_Data();
    LoadEnergyRanges();
    LoadBe7Params();

    ChangeUILanguage();
}
//---------------------------------------------------------------------------
void TSettingsForm::LoadEnergyRanges()
{
    try
    {
        ThEnergy1Edit->Text = IniFile->ReadFloat(L"EnergyRanges", ThEnergy1Edit->Name, 2500);
        ThEnergy2Edit->Text = IniFile->ReadFloat(L"EnergyRanges", ThEnergy2Edit->Name, 2720);
        RaEnergy1Edit->Text = IniFile->ReadFloat(L"EnergyRanges", RaEnergy1Edit->Name, 1677);
        RaEnergy2Edit->Text = IniFile->ReadFloat(L"EnergyRanges", RaEnergy2Edit->Name, 1846);
        KEnergy1Edit->Text = IniFile->ReadFloat(L"EnergyRanges", KEnergy1Edit->Name, 1385);
        KEnergy2Edit->Text = IniFile->ReadFloat(L"EnergyRanges", KEnergy2Edit->Name, 1540);
        CsEnergy1Edit->Text = IniFile->ReadFloat(L"EnergyRanges", CsEnergy1Edit->Name, 612);
        CsEnergy2Edit->Text = IniFile->ReadFloat(L"EnergyRanges", CsEnergy2Edit->Name, 709);
        BeEnergy1Edit->Text = IniFile->ReadFloat(L"EnergyRanges", BeEnergy1Edit->Name, 430);
        BeEnergy2Edit->Text = IniFile->ReadFloat(L"EnergyRanges", BeEnergy2Edit->Name, 525);
    }
    catch (Exception &)
    {
    }
}
//---------------------------------------------------------------------------
void TSettingsForm::SaveEnergyRanges()
{
    try
    {
        IniFile->WriteFloat(L"EnergyRanges", ThEnergy1Edit->Name, Sysutils::StrToFloatDef(ThEnergy1Edit->Text, 0));
        IniFile->WriteFloat(L"EnergyRanges", ThEnergy2Edit->Name, Sysutils::StrToFloatDef(ThEnergy2Edit->Text, 0));
        IniFile->WriteFloat(L"EnergyRanges", RaEnergy1Edit->Name, Sysutils::StrToFloatDef(RaEnergy1Edit->Text, 0));
        IniFile->WriteFloat(L"EnergyRanges", RaEnergy2Edit->Name, Sysutils::StrToFloatDef(RaEnergy2Edit->Text, 0));
        IniFile->WriteFloat(L"EnergyRanges", KEnergy1Edit->Name, Sysutils::StrToFloatDef(KEnergy1Edit->Text, 0));
        IniFile->WriteFloat(L"EnergyRanges", KEnergy2Edit->Name, Sysutils::StrToFloatDef(KEnergy2Edit->Text, 0));
        IniFile->WriteFloat(L"EnergyRanges", CsEnergy1Edit->Name, Sysutils::StrToFloatDef(CsEnergy1Edit->Text, 0));
        IniFile->WriteFloat(L"EnergyRanges", CsEnergy2Edit->Name, Sysutils::StrToFloatDef(CsEnergy2Edit->Text, 0));
        IniFile->WriteFloat(L"EnergyRanges", BeEnergy1Edit->Name, Sysutils::StrToFloatDef(BeEnergy1Edit->Text, 0));
        IniFile->WriteFloat(L"EnergyRanges", BeEnergy2Edit->Name, Sysutils::StrToFloatDef(BeEnergy2Edit->Text, 0));
    }
    catch (Exception &)
    {
    }
}
//---------------------------------------------------------------------------
void TSettingsForm::LoadBe7Params()
{
    try
    {
        Be7PhotopeakEffEdit->Text = IniFile->ReadString(L"Be7", Be7PhotopeakEffEdit->Name, L"");
        Be7SystematicErrorEdit->Text = IniFile->ReadString(L"Be7", Be7SystematicErrorEdit->Name, L"10");
    }
    catch (Exception &)
    {
    }
}
//---------------------------------------------------------------------------
void TSettingsForm::SaveBe7Params()
{
    try
    {
        IniFile->WriteString(L"Be7", Be7PhotopeakEffEdit->Name, Be7PhotopeakEffEdit->Text);
        IniFile->WriteString(L"Be7", Be7SystematicErrorEdit->Name, Be7SystematicErrorEdit->Text);
    }
    catch (Exception &)
    {
    }
}
//---------------------------------------------------------------------------
void TSettingsForm::LoadDensity_1_Data()
{
    try
    {
        Th1ActivityEdit->Text = IniFile->ReadFloat(L"Density_1", Th1ActivityEdit->Name, 6180);
        Th1Date->Date = IniFile->ReadDate(L"Density_1", Th1Date->Name, TDateTime(1995, 9, 1));
        Th1MesDate->Date = IniFile->ReadDate(L"Density_1", Th1MesDate->Name, TDateTime(1995, 9, 1));
        Th1FileName->Text = IniFile->ReadString(L"Density_1", Th1FileName->Name, L"");
        Th1FileName->Tag = Sysutils::FileExists(Th1FileName->Text);

        Ra1ActivityEdit->Text = IniFile->ReadFloat(L"Density_1", Ra1ActivityEdit->Name, 5440);
        Ra1Date->Date = IniFile->ReadDate(L"Density_1", Ra1Date->Name, TDateTime(1995, 9, 1));
        Ra1MesDate->Date = IniFile->ReadDate(L"Density_1", Ra1MesDate->Name, TDateTime(1995, 9, 1));
        Ra1FileName->Text = IniFile->ReadString(L"Density_1", Ra1FileName->Name, L"");
        Ra1FileName->Tag = Sysutils::FileExists(Ra1FileName->Text);

        K1ActivityEdit->Text = IniFile->ReadFloat(L"Density_1", K1ActivityEdit->Name, 3100);
        K1Date->Date = IniFile->ReadDate(L"Density_1", K1Date->Name, TDateTime(1995, 9, 1));
        K1MesDate->Date = IniFile->ReadDate(L"Density_1", K1MesDate->Name, TDateTime(1995, 9, 1));
        K1FileName->Text = IniFile->ReadString(L"Density_1", K1FileName->Name, L"");
        K1FileName->Tag = Sysutils::FileExists(K1FileName->Text);

        Cs1ActivityEdit->Text = IniFile->ReadFloat(L"Density_1", Cs1ActivityEdit->Name, 3220);
        Cs1Date->Date = IniFile->ReadDate(L"Density_1", Cs1Date->Name, TDateTime(1995, 9, 1));
        Cs1MesDate->Date = IniFile->ReadDate(L"Density_1", Cs1MesDate->Name, TDateTime(1995, 9, 1));
        Cs1FileName->Text = IniFile->ReadString(L"Density_1", Cs1FileName->Name, L"");
        Cs1FileName->Tag = Sysutils::FileExists(Cs1FileName->Text);

        Bkg1FileName->Text = IniFile->ReadString(L"Density_1", Bkg1FileName->Name, L"");
        Bkg1FileName->Tag = Sysutils::FileExists(Bkg1FileName->Text);
    }
    catch (Exception &)
    {
    }
}
//---------------------------------------------------------------------------
void TSettingsForm::LoadDensity_2_Data()
{
    try
    {
        Th2ActivityEdit->Text = IniFile->ReadFloat(L"Density_2", Th2ActivityEdit->Name, 7350);
        Th2Date->Date = IniFile->ReadDate(L"Density_2", Th2Date->Name, TDateTime(1995, 9, 1));
        Th2MesDate->Date = IniFile->ReadDate(L"Density_2", Th2MesDate->Name, TDateTime(1995, 9, 1));
        Th2FileName->Text = IniFile->ReadString(L"Density_2", Th2FileName->Name, L"");
        Th2FileName->Tag = Sysutils::FileExists(Th2FileName->Text);

        Ra2ActivityEdit->Text = IniFile->ReadFloat(L"Density_2", Ra2ActivityEdit->Name, 8180);
        Ra2Date->Date = IniFile->ReadDate(L"Density_2", Ra2Date->Name, TDateTime(1995, 9, 1));
        Ra2MesDate->Date = IniFile->ReadDate(L"Density_2", Ra2MesDate->Name, TDateTime(1995, 9, 1));
        Ra2FileName->Text = IniFile->ReadString(L"Density_2", Ra2FileName->Name, L"");
        Ra2FileName->Tag = Sysutils::FileExists(Ra2FileName->Text);

        K2ActivityEdit->Text = IniFile->ReadFloat(L"Density_2", K2ActivityEdit->Name, 13790);
        K2Date->Date = IniFile->ReadDate(L"Density_2", K2Date->Name, TDateTime(1995, 9, 1));
        K2MesDate->Date = IniFile->ReadDate(L"Density_2", K2MesDate->Name, TDateTime(1995, 9, 1));
        K2FileName->Text = IniFile->ReadString(L"Density_2", K2FileName->Name, L"");
        K2FileName->Tag = Sysutils::FileExists(K2FileName->Text);

        Cs2ActivityEdit->Text = IniFile->ReadFloat(L"Density_2", Cs2ActivityEdit->Name, 2570);
        Cs2Date->Date = IniFile->ReadDate(L"Density_2", Cs2Date->Name, TDateTime(1995, 9, 1));
        Cs2MesDate->Date = IniFile->ReadDate(L"Density_2", Cs2MesDate->Name, TDateTime(1995, 9, 1));
        Cs2FileName->Text = IniFile->ReadString(L"Density_2", Cs2FileName->Name, L"");
        Cs2FileName->Tag = Sysutils::FileExists(Cs2FileName->Text);

        Bkg2FileName->Text = IniFile->ReadString(L"Density_2", Bkg2FileName->Name, L"");
        Bkg2FileName->Tag = Sysutils::FileExists(Bkg2FileName->Text);
    }
    catch (Exception &)
    {
    }
}
//---------------------------------------------------------------------------
void TSettingsForm::LoadDensity_3_Data()
{
    try
    {
        Th3ActivityEdit->Text = IniFile->ReadFloat(L"Density_3", Th3ActivityEdit->Name, 6430);
        Th3Date->Date = IniFile->ReadDate(L"Density_3", Th3Date->Name, TDateTime(1995, 9, 1));
        Th3MesDate->Date = IniFile->ReadDate(L"Density_3", Th3MesDate->Name, TDateTime(1995, 9, 1));
        Th3FileName->Text = IniFile->ReadString(L"Density_3", Th3FileName->Name, L"");
        Th3FileName->Tag = Sysutils::FileExists(Th3FileName->Text);

        Ra3ActivityEdit->Text = IniFile->ReadFloat(L"Density_3", Ra3ActivityEdit->Name, 5490);
        Ra3Date->Date = IniFile->ReadDate(L"Density_3", Ra3Date->Name, TDateTime(1995, 9, 1));
        Ra3MesDate->Date = IniFile->ReadDate(L"Density_3", Ra3MesDate->Name, TDateTime(1995, 9, 1));
        Ra3FileName->Text = IniFile->ReadString(L"Density_3", Ra3FileName->Name, L"");
        Ra3FileName->Tag = Sysutils::FileExists(Ra3FileName->Text);

        K3ActivityEdit->Text = IniFile->ReadFloat(L"Density_3", K3ActivityEdit->Name, 13700);
        K3Date->Date = IniFile->ReadDate(L"Density_3", K3Date->Name, TDateTime(1995, 9, 1));
        K3MesDate->Date = IniFile->ReadDate(L"Density_3", K3MesDate->Name, TDateTime(1995, 9, 1));
        K3FileName->Text = IniFile->ReadString(L"Density_3", K3FileName->Name, L"");
        K3FileName->Tag = Sysutils::FileExists(K3FileName->Text);

        Cs3ActivityEdit->Text = IniFile->ReadFloat(L"Density_3", Cs3ActivityEdit->Name, 3150);
        Cs3Date->Date = IniFile->ReadDate(L"Density_3", Cs3Date->Name, TDateTime(1995, 9, 1));
        Cs3MesDate->Date = IniFile->ReadDate(L"Density_3", Cs3MesDate->Name, TDateTime(1995, 9, 1));
        Cs3FileName->Text = IniFile->ReadString(L"Density_3", Cs3FileName->Name, L"");
        Cs3FileName->Tag = Sysutils::FileExists(Cs3FileName->Text);

        Bkg3FileName->Text = IniFile->ReadString(L"Density_3", Bkg3FileName->Name, L"");
        Bkg3FileName->Tag = Sysutils::FileExists(Bkg3FileName->Text);
    }
    catch (Exception &)
    {
    }
}
//---------------------------------------------------------------------------
void TSettingsForm::SaveDensity_1_Data()
{
    try
    {
        IniFile->WriteFloat(L"Density_1", Th1ActivityEdit->Name, Sysutils::StrToFloatDef(Th1ActivityEdit->Text, 0));
        IniFile->WriteFloat(L"Density_1", Th1ErrorEdit->Name, Sysutils::StrToFloatDef(Th1ErrorEdit->Text, 0));
        IniFile->WriteDate(L"Density_1", Th1Date->Name, Th1Date->Date);
        IniFile->WriteDate(L"Density_1", Th1MesDate->Name, Th1MesDate->Date);
        IniFile->WriteString(L"Density_1", Th1FileName->Name, Th1FileName->Text);

        IniFile->WriteFloat(L"Density_1", Ra1ActivityEdit->Name, Sysutils::StrToFloatDef(Ra1ActivityEdit->Text, 0));
        IniFile->WriteFloat(L"Density_1", Ra1ErrorEdit->Name, Sysutils::StrToFloatDef(Ra1ErrorEdit->Text, 0));
        IniFile->WriteDate(L"Density_1", Ra1Date->Name, Ra1Date->Date);
        IniFile->WriteDate(L"Density_1", Ra1MesDate->Name, Ra1MesDate->Date);
        IniFile->WriteString(L"Density_1", Ra1FileName->Name, Ra1FileName->Text);

        IniFile->WriteFloat(L"Density_1", K1ActivityEdit->Name, Sysutils::StrToFloatDef(K1ActivityEdit->Text, 0));
        IniFile->WriteFloat(L"Density_1", K1ErrorEdit->Name, Sysutils::StrToFloatDef(K1ErrorEdit->Text, 0));
        IniFile->WriteDate(L"Density_1", K1Date->Name, K1Date->Date);
        IniFile->WriteDate(L"Density_1", K1MesDate->Name, K1MesDate->Date);
        IniFile->WriteString(L"Density_1", K1FileName->Name, K1FileName->Text);

        IniFile->WriteFloat(L"Density_1", Cs1ActivityEdit->Name, Sysutils::StrToFloatDef(Cs1ActivityEdit->Text, 0));
        IniFile->WriteFloat(L"Density_1", Cs1ErrorEdit->Name, Sysutils::StrToFloatDef(Cs1ErrorEdit->Text, 0));
        IniFile->WriteDate(L"Density_1", Cs1Date->Name, Cs1Date->Date);
        IniFile->WriteDate(L"Density_1", Cs1MesDate->Name, Cs1MesDate->Date);
        IniFile->WriteString(L"Density_1", Cs1FileName->Name, Cs1FileName->Text);

        IniFile->WriteString(L"Density_1", Bkg1FileName->Name, Bkg1FileName->Text);
    }
    catch (Exception &E)
    {
        Application->ShowException(&E);
    }
}
//---------------------------------------------------------------------------
void TSettingsForm::SaveDensity_2_Data()
{
    try
    {
        IniFile->WriteFloat(L"Density_2", Th2ActivityEdit->Name, Sysutils::StrToFloatDef(Th2ActivityEdit->Text, 0));
        IniFile->WriteFloat(L"Density_1", Th2ErrorEdit->Name, Sysutils::StrToFloatDef(Th2ErrorEdit->Text, 0));
        IniFile->WriteDate(L"Density_2", Th2Date->Name, Th2Date->Date);
        IniFile->WriteDate(L"Density_2", Th2MesDate->Name, Th2MesDate->Date);
        IniFile->WriteString(L"Density_2", Th2FileName->Name, Th2FileName->Text);

        IniFile->WriteFloat(L"Density_2", Ra2ActivityEdit->Name, Sysutils::StrToFloatDef(Ra2ActivityEdit->Text, 0));
        IniFile->WriteFloat(L"Density_1", Ra2ErrorEdit->Name, Sysutils::StrToFloatDef(Ra2ErrorEdit->Text, 0));
        IniFile->WriteDate(L"Density_2", Ra2Date->Name, Ra2Date->Date);
        IniFile->WriteDate(L"Density_2", Ra2MesDate->Name, Ra2MesDate->Date);
        IniFile->WriteString(L"Density_2", Ra2FileName->Name, Ra2FileName->Text);

        IniFile->WriteFloat(L"Density_2", K2ActivityEdit->Name, Sysutils::StrToFloatDef(K2ActivityEdit->Text, 0));
        IniFile->WriteFloat(L"Density_1", K2ErrorEdit->Name, Sysutils::StrToFloatDef(K2ErrorEdit->Text, 0));
        IniFile->WriteDate(L"Density_2", K2Date->Name, K2Date->Date);
        IniFile->WriteDate(L"Density_2", K2MesDate->Name, K2MesDate->Date);
        IniFile->WriteString(L"Density_2", K2FileName->Name, K2FileName->Text);

        IniFile->WriteFloat(L"Density_2", Cs2ActivityEdit->Name, Sysutils::StrToFloatDef(Cs2ActivityEdit->Text, 0));
        IniFile->WriteFloat(L"Density_1", Cs2ErrorEdit->Name, Sysutils::StrToFloatDef(Cs2ErrorEdit->Text, 0));
        IniFile->WriteDate(L"Density_2", Cs2Date->Name, Cs2Date->Date);
        IniFile->WriteDate(L"Density_2", Cs2MesDate->Name, Cs2MesDate->Date);
        IniFile->WriteString(L"Density_2", Cs2FileName->Name, Cs2FileName->Text);

        IniFile->WriteString(L"Density_2", Bkg2FileName->Name, Bkg2FileName->Text);
    }
    catch (Exception &)
    {
    }
}
//---------------------------------------------------------------------------
void TSettingsForm::SaveDensity_3_Data()
{
    try
    {
        IniFile->WriteFloat(L"Density_3", Th3ActivityEdit->Name, Sysutils::StrToFloatDef(Th3ActivityEdit->Text, 0));
        IniFile->WriteFloat(L"Density_3", Th3ErrorEdit->Name, Sysutils::StrToFloatDef(Th3ErrorEdit->Text, 0));
        IniFile->WriteDate(L"Density_3", Th3Date->Name, Th3Date->Date);
        IniFile->WriteDate(L"Density_3", Th3MesDate->Name, Th3MesDate->Date);
        IniFile->WriteString(L"Density_3", Th3FileName->Name, Th3FileName->Text);

        IniFile->WriteFloat(L"Density_3", Ra3ActivityEdit->Name, Sysutils::StrToFloatDef(Ra3ActivityEdit->Text, 0));
        IniFile->WriteFloat(L"Density_3", Ra3ErrorEdit->Name, Sysutils::StrToFloatDef(Ra3ErrorEdit->Text, 0));
        IniFile->WriteDate(L"Density_3", Ra3Date->Name, Ra3Date->Date);
        IniFile->WriteDate(L"Density_3", Ra3MesDate->Name, Ra3MesDate->Date);
        IniFile->WriteString(L"Density_3", Ra3FileName->Name, Ra3FileName->Text);

        IniFile->WriteFloat(L"Density_3", K3ActivityEdit->Name, Sysutils::StrToFloatDef(K3ActivityEdit->Text, 0));
        IniFile->WriteFloat(L"Density_3", K3ErrorEdit->Name, Sysutils::StrToFloatDef(K3ErrorEdit->Text, 0));
        IniFile->WriteDate(L"Density_3", K3Date->Name, K3Date->Date);
        IniFile->WriteDate(L"Density_3", K3MesDate->Name, K3MesDate->Date);
        IniFile->WriteString(L"Density_3", K3FileName->Name, K3FileName->Text);

        IniFile->WriteFloat(L"Density_3", Cs3ActivityEdit->Name, Sysutils::StrToFloatDef(Cs3ActivityEdit->Text, 0));
        IniFile->WriteFloat(L"Density_3", Cs3ErrorEdit->Name, Sysutils::StrToFloatDef(Cs3ErrorEdit->Text, 0));
        IniFile->WriteDate(L"Density_3", Cs3Date->Name, Cs3Date->Date);
        IniFile->WriteDate(L"Density_3", Cs3MesDate->Name, Cs3MesDate->Date);
        IniFile->WriteString(L"Density_3", Cs3FileName->Name, Cs3FileName->Text);

        IniFile->WriteString(L"Density_3", Bkg3FileName->Name, Bkg3FileName->Text);
    }
    catch (Exception &)
    {
    }
}
//---------------------------------------------------------------------------
bool TSettingsForm::VolumesAreValid(String &ErrorMessage) const
{
    ErrorMessage = L"";
    std::vector<String> FileNames;
    FileNames.push_back(Th1FileName->Text);
    FileNames.push_back(Ra1FileName->Text);
    FileNames.push_back(K1FileName->Text);
    FileNames.push_back(Cs1FileName->Text);
    FileNames.push_back(Bkg1FileName->Text);

    FileNames.push_back(Th2FileName->Text);
    FileNames.push_back(Ra2FileName->Text);
    FileNames.push_back(K2FileName->Text);
    FileNames.push_back(Cs2FileName->Text);
    FileNames.push_back(Bkg2FileName->Text);

    FileNames.push_back(Th3FileName->Text);
    FileNames.push_back(Ra3FileName->Text);
    FileNames.push_back(K3FileName->Text);
    FileNames.push_back(Cs3FileName->Text);
    FileNames.push_back(Bkg3FileName->Text);
    double Volume = 0;
    for (size_t i = 0; i < FileNames.size(); i++)
    {
        TSpectrum Spc;
        if (!Spc.LoadFromFile(FileNames[i]))
        {
            ErrorMessage = QuotedStr(FileNames[i]) + L" faylini o'qishning imkoni bo'lmadi.";
            if (LangID == 1)
            {
                ErrorMessage = L"Couldn't load file " + QuotedStr(FileNames[i]) + L".";
            }
            return false;
        }
        if (i == 0)
        {
            Volume = Spc.Volume;
        }
        else if (!Utils::IsEqual(Spc.Volume, Volume))
        {
            ErrorMessage =
                QuotedStr(FileNames[i]) + L" spektrida namuna hajmi noto'g'ri.";
            if (LangID == 1)
            {
                ErrorMessage = L"In spectrum " + QuotedStr(FileNames[i]) + L", sample volume is not valid.";
            }
            return false;
        }
    }
    return true;
}
//---------------------------------------------------------------------------
void __fastcall TSettingsForm::SaveButtonClick(TObject *Sender)
{
    String ErrorMessage =
        L"3 xil zichlikli etalon va fon namunalarining barcha ma'lumotlari to'ldirilishi shart.";
    String Title = L"Xato";
    if (LangID == 1)
    {
        ErrorMessage = L"Please fill in the all fields.";
        Title = L"Error";
    }
    if (!Density_1_SamplesValid() || !Density_2_SamplesValid() || !Density_3_SamplesValid())
    {
        Application->MessageBox(ErrorMessage.c_str(), Title.c_str(), MB_OK | MB_ICONERROR);
        return;
    }
    if (!VolumesAreValid(ErrorMessage))
    {
        Application->MessageBox(ErrorMessage.c_str(), Title.c_str(), MB_OK | MB_ICONERROR);
        return;
    }
    if (Density_1_SamplesValid())
    {
        SaveDensity_1_Data();
    }
    if (Density_2_SamplesValid())
    {
        SaveDensity_2_Data();
    }
    if (Density_3_SamplesValid())
    {
        SaveDensity_3_Data();
    }
    SaveEnergyRanges();
    SaveBe7Params();
    IniFile->UpdateFile();
    ModalResult = mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TSettingsForm::BrowseButtonClick(TObject *Sender)
{
    OpenDialog->Filter = Utils::GetDialogBoxFilterForSpectraFiles();
    OpenDialog->FileName = L"";
    if (!OpenDialog->Execute(Handle))
    {
        return;
    }
    TButton *Button = dynamic_cast<TButton*>(Sender);
    TEdit *FileName = reinterpret_cast<TEdit*>(Button->Tag);
    const String &MyPath = Sysutils::ExtractFilePath(GetModuleName(unsigned(HInstance)));
    if (SameText(MyPath, Sysutils::ExtractFilePath(OpenDialog->FileName)))
    {
        FileName->Text = L".\\" + Sysutils::ExtractFileName(OpenDialog->FileName);
    }
    else
    {
        FileName->Text = OpenDialog->FileName;
    }
    FileName->Tag = 1;
    Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TSettingsForm::FormPaint(TObject *Sender)
{
    if (Th1FileName->Tag == 1)
    {
        Canvas->Draw(Th1Button->Left + Th1Button->Width + 5, Th1Button->Top, ImageCorrect->Picture->Graphic);
    }
    else
    {
        Canvas->Draw(Th1Button->Left + Th1Button->Width + 5, Th1Button->Top, ImageIncorrect->Picture->Graphic);
    }
    if (Ra1FileName->Tag == 1)
    {
        Canvas->Draw(Ra1Button->Left + Ra1Button->Width + 5, Ra1Button->Top, ImageCorrect->Picture->Graphic);
    }
    else
    {
        Canvas->Draw(Ra1Button->Left + Ra1Button->Width + 5, Ra1Button->Top, ImageIncorrect->Picture->Graphic);
    }
    if (K1FileName->Tag == 1)
    {
        Canvas->Draw(K1Button->Left + K1Button->Width + 5, K1Button->Top, ImageCorrect->Picture->Graphic);
    }
    else
    {
        Canvas->Draw(K1Button->Left + K1Button->Width + 5, K1Button->Top, ImageIncorrect->Picture->Graphic);
    }
    if (Cs1FileName->Tag == 1)
    {
        Canvas->Draw(Cs1Button->Left + Cs1Button->Width + 5, Cs1Button->Top, ImageCorrect->Picture->Graphic);
    }
    else
    {
        Canvas->Draw(Cs1Button->Left + Cs1Button->Width + 5, Cs1Button->Top, ImageIncorrect->Picture->Graphic);
    }
    if (Bkg1FileName->Tag == 1)
    {
        Canvas->Draw(Bkg1Button->Left + Bkg1Button->Width + 5, Bkg1Button->Top, ImageCorrect->Picture->Graphic);
    }
    else
    {
        Canvas->Draw(Bkg1Button->Left + Bkg1Button->Width + 5, Bkg1Button->Top, ImageIncorrect->Picture->Graphic);
    }

    if (Th2FileName->Tag == 1)
    {
        Canvas->Draw(Th2Button->Left + Th2Button->Width + 5, Th2Button->Top, ImageCorrect->Picture->Graphic);
    }
    else
    {
        Canvas->Draw(Th2Button->Left + Th2Button->Width + 5, Th2Button->Top, ImageIncorrect->Picture->Graphic);
    }
    if (Ra2FileName->Tag == 1)
    {
        Canvas->Draw(Ra2Button->Left + Ra2Button->Width + 5, Ra2Button->Top, ImageCorrect->Picture->Graphic);
    }
    else
    {
        Canvas->Draw(Ra2Button->Left + Ra2Button->Width + 5, Ra2Button->Top, ImageIncorrect->Picture->Graphic);
    }
    if (K2FileName->Tag == 1)
    {
        Canvas->Draw(K2Button->Left + K2Button->Width + 5, K2Button->Top, ImageCorrect->Picture->Graphic);
    }
    else
    {
        Canvas->Draw(K2Button->Left + K2Button->Width + 5, K2Button->Top, ImageIncorrect->Picture->Graphic);
    }
    if (Cs2FileName->Tag == 1)
    {
        Canvas->Draw(Cs2Button->Left + Cs2Button->Width + 5, Cs2Button->Top, ImageCorrect->Picture->Graphic);
    }
    else
    {
        Canvas->Draw(Cs2Button->Left + Cs2Button->Width + 5, Cs2Button->Top, ImageIncorrect->Picture->Graphic);
    }
    if (Bkg2FileName->Tag == 1)
    {
        Canvas->Draw(Bkg2Button->Left + Bkg2Button->Width + 5, Bkg2Button->Top, ImageCorrect->Picture->Graphic);
    }
    else
    {
        Canvas->Draw(Bkg2Button->Left + Bkg2Button->Width + 5, Bkg2Button->Top, ImageIncorrect->Picture->Graphic);
    }

    if (Th3FileName->Tag == 1)
    {
        Canvas->Draw(Th3Button->Left + Th3Button->Width + 5, Th3Button->Top, ImageCorrect->Picture->Graphic);
    }
    else
    {
        Canvas->Draw(Th3Button->Left + Th3Button->Width + 5, Th3Button->Top, ImageIncorrect->Picture->Graphic);
    }
    if (Ra3FileName->Tag == 1)
    {
        Canvas->Draw(Ra3Button->Left + Ra3Button->Width + 5, Ra3Button->Top, ImageCorrect->Picture->Graphic);
    }
    else
    {
        Canvas->Draw(Ra3Button->Left + Ra3Button->Width + 5, Ra3Button->Top, ImageIncorrect->Picture->Graphic);
    }
    if (K3FileName->Tag == 1)
    {
        Canvas->Draw(K3Button->Left + K3Button->Width + 5, K3Button->Top, ImageCorrect->Picture->Graphic);
    }
    else
    {
        Canvas->Draw(K3Button->Left + K3Button->Width + 5, K3Button->Top, ImageIncorrect->Picture->Graphic);
    }
    if (Cs3FileName->Tag == 1)
    {
        Canvas->Draw(Cs3Button->Left + Cs3Button->Width + 5, Cs3Button->Top, ImageCorrect->Picture->Graphic);
    }
    else
    {
        Canvas->Draw(Cs3Button->Left + Cs3Button->Width + 5, Cs3Button->Top, ImageIncorrect->Picture->Graphic);
    }
    if (Bkg3FileName->Tag == 1)
    {
        Canvas->Draw(Bkg3Button->Left + Bkg3Button->Width + 5, Bkg3Button->Top, ImageCorrect->Picture->Graphic);
    }
    else
    {
        Canvas->Draw(Bkg3Button->Left + Bkg3Button->Width + 5, Bkg3Button->Top, ImageIncorrect->Picture->Graphic);
    }
}
//---------------------------------------------------------------------------
void __fastcall TSettingsForm::FileNameChange(TObject *Sender)
{
    TEdit *Edit = dynamic_cast<TEdit *>(Sender);
    Edit->Tag = Sysutils::FileExists(Edit->Text);
    RECT R;
    R.left = Th1Button->Left + Th1Button->Width + 3;
    R.top = Edit->Top - 2;
    R.right = R.left + ImageCorrect->Width + 4;
    R.bottom = R.top + ImageCorrect->Height + 4;
    InvalidateRect(Handle, &R, 1);
}
//---------------------------------------------------------------------------
String TSettingsForm::GetSetting(const String &Section, const String &Name) const
{
    try
    {
        return IniFile->ReadString(Section, Name, L"");
    }
    catch (const Exception &)
    {
    }
    return L"";
}
//---------------------------------------------------------------------------
void TSettingsForm::ChangeUILanguage()
{
    if (LangID == 0)
    {
        Caption = L"Etalon va fon namunalari";

        Title1Label->Caption = L"Zichligi 200 Gr/L dan 500 Gr/L gacha bo'lgan namunalar.";
        Label40->Caption = L"Namuna";
        Label7->Caption = L"Aktivligi (Bk), xatoligi (%) va qayd qilingan sanasi";
        Label35->Caption = L"Spektr o'lchangan kun";
        Label34->Caption = L"Spektr faylining nomi";
        Label29->Caption = L"Tabiiy fon";

        Title2Label->Caption = L"Zichligi 800 Gr/L dan 1100 Gr/L gacha bo'lgan namunalar.";
        Label12->Caption = Label40->Caption;
        Label16->Caption = Label7->Caption;
        Label36->Caption = Label35->Caption;
        Label14->Caption = Label34->Caption;
        Label30->Caption = Label29->Caption;

        Title3Label->Caption = L"Zichligi 1500 Gr/L dan 1800 Gr/L gacha bo'lgan namunalar.";
        Label24->Caption = Label40->Caption;
        Label19->Caption = Label7->Caption;
        Label37->Caption = Label35->Caption;
        Label21->Caption = Label34->Caption;
        Label31->Caption = Label29->Caption;

        Title4Label->Caption = L"Foydalaniluvchi fotocho'qqilar sohalari (chap va o'ng nuqtalari).";
        Label33->Caption = Label40->Caption;
        Label9->Caption = L"keV dan";
        Label32->Caption = L"keV gacha";
        Be7EffLabel->Caption = L"Be-7 uchun fotocho'qqi effektivligi, %:";
        Be7PhotopeakEffEdit->TextHint = L"Mas: 4.1; 3.5; 3";
        Be7PhotopeakEffEdit->Hint = L"Uch xil zichliklar uchun. Har birini nuqta-vergul (;) bilan ajrating.";
        Be7SystematicErrorLabel->Caption = L"Be-7 uchun sistematik xatolik, %:";

        SaveButton->Caption = L"&Saqlash";
        CloseButton->Caption = L"&Yopish";
    }
    else if (LangID == 1)
    {
        Caption = L"Reference and background samples";

        Title1Label->Caption = L"Samples with density of 200 Gr / L to 500 Gr / L.";
        Label40->Caption = L"Sample";
        Label7->Caption = L"Activity (Bq), error (%) and registered date";
        Label35->Caption = L"Date the spectrum measured";
        Label34->Caption = L"Name of the spectrum file";
        Label29->Caption = L"Background";

        Title2Label->Caption = L"Samples with density of 800 Gr / L to 1100 Gr / L.";
        Label12->Caption = Label40->Caption;
        Label16->Caption = Label7->Caption;
        Label36->Caption = Label35->Caption;
        Label14->Caption = Label34->Caption;
        Label30->Caption = Label29->Caption;

        Title3Label->Caption = L"Samples with density of 1500 Gr / L to 1800 Gr / L.";
        Label24->Caption = Label40->Caption;
        Label19->Caption = Label7->Caption;
        Label37->Caption = Label35->Caption;
        Label21->Caption = Label34->Caption;
        Label31->Caption = Label29->Caption;

        Title4Label->Caption = L"Areas of photopeaks used (left and right points).";
        Label33->Caption = Label40->Caption;
        Label9->Caption = L"From keV";
        Label32->Caption = L"To keV";
        Be7EffLabel->Caption = L"Photopeak efficiency for Be-7, %:";
        Be7PhotopeakEffEdit->TextHint = L"Ex: 4.1; 3.5; 3";
        Be7PhotopeakEffEdit->Hint = L"For three densities. Separate them by semicolon (;).";
        Be7SystematicErrorLabel->Caption = L"Systematic error for Be-7, %:";

        SaveButton->Caption = L"&Save";
        CloseButton->Caption = L"&Close";
    }
    else
    {
        throw Exception(L"Unknown language.");
    }
}
