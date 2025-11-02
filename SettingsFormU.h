//---------------------------------------------------------------------------
#ifndef SettingsFormUH
#define SettingsFormUH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <System.IniFiles.hpp>
#include <memory>
//---------------------------------------------------------------------------
// Language ID
// 0 => Uzbek
// 1 => English
extern std::atomic<int> LangID;
//
//
//

//---------------------------------------------------------------------------
class TSettingsForm : public TForm
{
__published:
    TButton *SaveButton;
    TButton *CloseButton;
    TScrollBox *ScrollBox;
    TEdit *BeEnergy1Edit;
    TEdit *BeEnergy2Edit;
    TButton *Bkg1Button;
    TEdit *Bkg1FileName;
    TButton *Bkg2Button;
    TEdit *Bkg2FileName;
    TButton *Bkg3Button;
    TEdit *Bkg3FileName;
    TEdit *Cs1ActivityEdit;
    TButton *Cs1Button;
    TDateTimePicker *Cs1Date;
    TEdit *Cs1ErrorEdit;
    TEdit *Cs1FileName;
    TDateTimePicker *Cs1MesDate;
    TEdit *Cs2ActivityEdit;
    TButton *Cs2Button;
    TDateTimePicker *Cs2Date;
    TEdit *Cs2ErrorEdit;
    TEdit *Cs2FileName;
    TDateTimePicker *Cs2MesDate;
    TEdit *Cs3ActivityEdit;
    TButton *Cs3Button;
    TDateTimePicker *Cs3Date;
    TEdit *Cs3ErrorEdit;
    TEdit *Cs3FileName;
    TDateTimePicker *Cs3MesDate;
    TEdit *CsEnergy1Edit;
    TEdit *CsEnergy2Edit;
    TImage *ImageCorrect;
    TImage *ImageIncorrect;
    TEdit *K1ActivityEdit;
    TButton *K1Button;
    TDateTimePicker *K1Date;
    TEdit *K1ErrorEdit;
    TEdit *K1FileName;
    TDateTimePicker *K1MesDate;
    TEdit *K2ActivityEdit;
    TButton *K2Button;
    TDateTimePicker *K2Date;
    TEdit *K2ErrorEdit;
    TEdit *K2FileName;
    TDateTimePicker *K2MesDate;
    TEdit *K3ActivityEdit;
    TButton *K3Button;
    TDateTimePicker *K3Date;
    TEdit *K3ErrorEdit;
    TEdit *K3FileName;
    TDateTimePicker *K3MesDate;
    TEdit *KEnergy1Edit;
    TEdit *KEnergy2Edit;
    TLabel *Label1;
    TLabel *Label10;
    TLabel *Label11;
    TLabel *Label12;
    TLabel *Label13;
    TLabel *Label14;
    TLabel *Label16;
    TLabel *Label18;
    TLabel *Label19;
    TLabel *Label20;
    TLabel *Label21;
    TLabel *Label22;
    TLabel *Label23;
    TLabel *Label24;
    TLabel *Label25;
    TLabel *Label26;
    TLabel *Label27;
    TLabel *Label28;
    TLabel *Label29;
    TLabel *Label3;
    TLabel *Label30;
    TLabel *Label31;
    TLabel *Label32;
    TLabel *Label33;
    TLabel *Label34;
    TLabel *Label35;
    TLabel *Label36;
    TLabel *Label37;
    TLabel *Label4;
    TLabel *Label40;
    TLabel *Label5;
    TLabel *Label6;
    TLabel *Label7;
    TLabel *Label8;
    TLabel *Label9;
    TOpenDialog *OpenDialog;
    TEdit *Ra1ActivityEdit;
    TButton *Ra1Button;
    TDateTimePicker *Ra1Date;
    TEdit *Ra1ErrorEdit;
    TEdit *Ra1FileName;
    TDateTimePicker *Ra1MesDate;
    TEdit *Ra2ActivityEdit;
    TButton *Ra2Button;
    TDateTimePicker *Ra2Date;
    TEdit *Ra2ErrorEdit;
    TEdit *Ra2FileName;
    TDateTimePicker *Ra2MesDate;
    TEdit *Ra3ActivityEdit;
    TButton *Ra3Button;
    TDateTimePicker *Ra3Date;
    TEdit *Ra3ErrorEdit;
    TEdit *Ra3FileName;
    TDateTimePicker *Ra3MesDate;
    TEdit *RaEnergy1Edit;
    TEdit *RaEnergy2Edit;
    TEdit *Th1ActivityEdit;
    TButton *Th1Button;
    TDateTimePicker *Th1Date;
    TEdit *Th1ErrorEdit;
    TEdit *Th1FileName;
    TDateTimePicker *Th1MesDate;
    TEdit *Th2ActivityEdit;
    TButton *Th2Button;
    TDateTimePicker *Th2Date;
    TEdit *Th2ErrorEdit;
    TEdit *Th2FileName;
    TDateTimePicker *Th2MesDate;
    TEdit *Th3ActivityEdit;
    TButton *Th3Button;
    TDateTimePicker *Th3Date;
    TEdit *Th3ErrorEdit;
    TEdit *Th3FileName;
    TDateTimePicker *Th3MesDate;
    TEdit *ThEnergy1Edit;
    TEdit *ThEnergy2Edit;
    TLabel *Title1Label;
    TLabel *Title2Label;
    TLabel *Title3Label;
    TLabel *EnergiesTitleLabel;
    TLabel *SamplesTitleLabel;
    TLabel *OtherSettingsTitleLabel;
    TCheckBox *ShowResultsWithMDA;
    TLabeledEdit *Be7PhotopeakEffEdit;
    TLabeledEdit *Be7SystematicErrorEdit;
    void __fastcall SaveButtonClick(TObject *Sender);
    void __fastcall BrowseButtonClick(TObject *Sender);
    void __fastcall FileNameChange(TObject *Sender);
    void __fastcall ScrollBoxMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta,
          TPoint &MousePos, bool &Handled);

private:
    std::unique_ptr<TMemIniFile> IniFile;
    std::unique_ptr<TControlCanvas> ScrollBoxCanvas;
    System::Classes::TWndMethod OldScrollBoxProc;

    void LoadEnergyRanges();
    void LoadBe7Params();
    void LoadDensity_1_Data();
    void LoadDensity_2_Data();
    void LoadDensity_3_Data();

    void SaveEnergyRanges();
    void SaveBe7Params();
    void SaveDensity_1_Data();
    void SaveDensity_2_Data();
    void SaveDensity_3_Data();

    void ChangeUILanguage();

    void __fastcall NewScrollBoxProc(Winapi::Messages::TMessage &Message);

public:
    __fastcall TSettingsForm(TComponent* Owner);

    bool EnergyRangesValid() const
    {
        return
            Sysutils::StrToFloatDef(ThEnergy1Edit->Text, 0) > 0 &&
            Sysutils::StrToFloatDef(RaEnergy1Edit->Text, 0) > 0 &&
            Sysutils::StrToFloatDef(KEnergy1Edit->Text, 0) > 0 &&
            Sysutils::StrToFloatDef(CsEnergy1Edit->Text, 0) > 0 &&

            Sysutils::StrToFloatDef(ThEnergy2Edit->Text, 0) > 0 &&
            Sysutils::StrToFloatDef(RaEnergy2Edit->Text, 0) > 0 &&
            Sysutils::StrToFloatDef(KEnergy2Edit->Text, 0) > 0 &&
            Sysutils::StrToFloatDef(CsEnergy2Edit->Text, 0) > 0 &&

            (Sysutils::StrToFloatDef(ThEnergy2Edit->Text, 0) > Sysutils::StrToFloatDef(ThEnergy1Edit->Text, 0)) &&
            (Sysutils::StrToFloatDef(RaEnergy2Edit->Text, 0) > Sysutils::StrToFloatDef(RaEnergy1Edit->Text, 0)) &&
            (Sysutils::StrToFloatDef(KEnergy2Edit->Text, 0) > Sysutils::StrToFloatDef(KEnergy1Edit->Text, 0))   &&
            (Sysutils::StrToFloatDef(CsEnergy2Edit->Text, 0) > Sysutils::StrToFloatDef(CsEnergy1Edit->Text, 0));
    }

    bool Density_1_SamplesValid() const
    {
        return
            EnergyRangesValid() &&
            !(Sysutils::StrToFloatDef(Th1ActivityEdit->Text, 0) <= 0 || Sysutils::StrToFloatDef(Th1ErrorEdit->Text, 0) <= 0 ||
            Sysutils::StrToFloatDef(Ra1ActivityEdit->Text, 0) <= 0 || Sysutils::StrToFloatDef(Ra1ErrorEdit->Text, 0) <= 0 ||
            Sysutils::StrToFloatDef(K1ActivityEdit->Text, 0) <= 0 || Sysutils::StrToFloatDef(K1ErrorEdit->Text, 0) <= 0 ||
            Sysutils::StrToFloatDef(Cs1ActivityEdit->Text, 0) <= 0 || Sysutils::StrToFloatDef(Cs1ErrorEdit->Text, 0) <= 0 ||

            Th1Date->Date >= Now() ||
            Ra1Date->Date >= Now() ||
            K1Date->Date >= Now() ||
            Cs1Date->Date >= Now() ||

            Th1MesDate->Date < Th1Date->Date || Th1MesDate->Date >= Now() ||
            Ra1MesDate->Date < Ra1Date->Date || Ra1MesDate->Date >= Now() ||
            K1MesDate->Date < K1Date->Date || K1MesDate->Date >= Now() ||
            Cs1MesDate->Date < Cs1Date->Date || Cs1MesDate->Date >= Now() ||

            !Sysutils::FileExists(Th1FileName->Text) ||
            !Sysutils::FileExists(Ra1FileName->Text) ||
            !Sysutils::FileExists(K1FileName->Text) ||
            !Sysutils::FileExists(Cs1FileName->Text) ||
            !Sysutils::FileExists(Bkg1FileName->Text));
    }

    bool Density_2_SamplesValid() const
    {
        return
            EnergyRangesValid() &&
            !(Sysutils::StrToFloatDef(Th2ActivityEdit->Text, 0) <= 0 || Sysutils::StrToFloatDef(Th2ErrorEdit->Text, 0) <= 0 ||
            Sysutils::StrToFloatDef(Ra2ActivityEdit->Text, 0) <= 0 || Sysutils::StrToFloatDef(Ra2ErrorEdit->Text, 0) <= 0 ||
            Sysutils::StrToFloatDef(K2ActivityEdit->Text, 0) <= 0 || Sysutils::StrToFloatDef(K2ErrorEdit->Text, 0) <= 0 ||
            Sysutils::StrToFloatDef(Cs2ActivityEdit->Text, 0) <= 0 || Sysutils::StrToFloatDef(Cs2ErrorEdit->Text, 0) <= 0 ||

            Th2Date->Date >= Now() ||
            Ra2Date->Date >= Now() ||
            K2Date->Date >= Now() ||
            Cs2Date->Date >= Now() ||

            Th2MesDate->Date < Th2Date->Date || Th2MesDate->Date >= Now() ||
            Ra2MesDate->Date < Ra2Date->Date || Ra2MesDate->Date >= Now() ||
            K2MesDate->Date < K2Date->Date || K2MesDate->Date >= Now() ||
            Cs2MesDate->Date < Cs2Date->Date || Cs2MesDate->Date >= Now() ||

            !Sysutils::FileExists(Th2FileName->Text) ||
            !Sysutils::FileExists(Ra2FileName->Text) ||
            !Sysutils::FileExists(K2FileName->Text) ||
            !Sysutils::FileExists(Cs2FileName->Text) ||
            !Sysutils::FileExists(Bkg2FileName->Text));
    }

    bool Density_3_SamplesValid() const
    {
        return
            EnergyRangesValid() &&
            !(Sysutils::StrToFloatDef(Th3ActivityEdit->Text, 0) <= 0 || Sysutils::StrToFloatDef(Th3ErrorEdit->Text, 0) <= 0 ||
            Sysutils::StrToFloatDef(Ra3ActivityEdit->Text, 0) <= 0 || Sysutils::StrToFloatDef(Ra3ErrorEdit->Text, 0) <= 0 ||
            Sysutils::StrToFloatDef(K3ActivityEdit->Text, 0) <= 0 || Sysutils::StrToFloatDef(K3ErrorEdit->Text, 0) <= 0 ||
            Sysutils::StrToFloatDef(Cs3ActivityEdit->Text, 0) <= 0 || Sysutils::StrToFloatDef(Cs3ErrorEdit->Text, 0) <= 0 ||

            Th3Date->Date >= Now() ||
            Ra3Date->Date >= Now() ||
            K3Date->Date >= Now() ||
            Cs3Date->Date >= Now() ||

            Th3MesDate->Date < Th3Date->Date || Th3MesDate->Date >= Now() ||
            Ra3MesDate->Date < Ra3Date->Date || Ra3MesDate->Date >= Now() ||
            K3MesDate->Date < K3Date->Date || K3MesDate->Date >= Now() ||
            Cs3MesDate->Date < Cs3Date->Date || Cs3MesDate->Date >= Now() ||

            !Sysutils::FileExists(Th3FileName->Text) ||
            !Sysutils::FileExists(Ra3FileName->Text) ||
            !Sysutils::FileExists(K3FileName->Text) ||
            !Sysutils::FileExists(Cs3FileName->Text) ||
            !Sysutils::FileExists(Bkg3FileName->Text));
    }

    String GetSetting(const String &Section, const String &Name) const;

    bool VolumesAreValid(String &ErrorMessage) const;
};
//---------------------------------------------------------------------------
#endif
