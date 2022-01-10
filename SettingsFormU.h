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
	TLabel *Title1Label;
    TEdit *Th1ActivityEdit;
    TLabel *Label7;
    TDateTimePicker *Th1Date;
    TEdit *ThEnergy1Edit;
    TEdit *ThEnergy2Edit;
    TButton *SaveButton;
    TButton *CloseButton;
    TLabel *Label34;
    TEdit *Th1FileName;
    TButton *Th1Button;
    TLabel *Label4;
    TLabel *Label40;
    TLabel *Label8;
    TButton *Ra1Button;
    TEdit *Ra1FileName;
    TEdit *RaEnergy2Edit;
    TEdit *RaEnergy1Edit;
    TDateTimePicker *Ra1Date;
    TEdit *Ra1ActivityEdit;
    TLabel *Label10;
    TButton *K1Button;
    TEdit *K1FileName;
    TEdit *KEnergy2Edit;
    TEdit *KEnergy1Edit;
    TDateTimePicker *K1Date;
    TEdit *K1ActivityEdit;
    TLabel *Label11;
    TButton *Cs1Button;
    TEdit *Cs1FileName;
    TEdit *CsEnergy2Edit;
    TEdit *CsEnergy1Edit;
    TDateTimePicker *Cs1Date;
    TEdit *Cs1ActivityEdit;
    TEdit *Cs2ActivityEdit;
    TDateTimePicker *Cs2Date;
    TEdit *Cs2FileName;
    TButton *Cs2Button;
    TLabel *Label3;
    TEdit *K2ActivityEdit;
    TDateTimePicker *K2Date;
    TEdit *K2FileName;
    TButton *K2Button;
    TLabel *Label5;
    TEdit *Ra2ActivityEdit;
    TDateTimePicker *Ra2Date;
    TEdit *Ra2FileName;
    TButton *Ra2Button;
    TLabel *Label6;
    TLabel *Label12;
    TLabel *Label13;
    TButton *Th2Button;
    TEdit *Th2FileName;
    TLabel *Label14;
    TDateTimePicker *Th2Date;
    TLabel *Label16;
    TEdit *Th2ActivityEdit;
    TEdit *Th3ActivityEdit;
    TLabel *Label19;
    TDateTimePicker *Th3Date;
    TLabel *Label21;
    TEdit *Th3FileName;
    TButton *Th3Button;
    TLabel *Label23;
    TLabel *Label24;
    TLabel *Label25;
    TButton *Ra3Button;
    TEdit *Ra3FileName;
    TDateTimePicker *Ra3Date;
    TEdit *Ra3ActivityEdit;
    TLabel *Label26;
    TButton *K3Button;
    TEdit *K3FileName;
    TDateTimePicker *K3Date;
    TEdit *K3ActivityEdit;
    TLabel *Label27;
    TButton *Cs3Button;
    TEdit *Cs3FileName;
    TDateTimePicker *Cs3Date;
    TEdit *Cs3ActivityEdit;
    TEdit *Bkg1FileName;
    TButton *Bkg1Button;
    TLabel *Label29;
    TEdit *Bkg2FileName;
    TButton *Bkg2Button;
    TLabel *Label30;
    TEdit *Bkg3FileName;
    TButton *Bkg3Button;
    TLabel *Label31;
    TOpenDialog *OpenDialog;
	TLabel *Title2Label;
	TLabel *Title3Label;
	TLabel *Title4Label;
    TLabel *Label18;
    TLabel *Label20;
    TLabel *Label22;
    TLabel *Label28;
    TLabel *Label9;
    TLabel *Label32;
    TLabel *Label33;
    TImage *ImageCorrect;
    TImage *ImageIncorrect;
    TDateTimePicker *Th1MesDate;
    TLabel *Label35;
    TDateTimePicker *Ra1MesDate;
    TDateTimePicker *K1MesDate;
    TDateTimePicker *Cs1MesDate;
    TDateTimePicker *Th2MesDate;
    TDateTimePicker *Ra2MesDate;
    TDateTimePicker *K2MesDate;
    TDateTimePicker *Cs2MesDate;
    TDateTimePicker *Th3MesDate;
    TDateTimePicker *Ra3MesDate;
    TDateTimePicker *K3MesDate;
    TDateTimePicker *Cs3MesDate;
    TLabel *Label36;
    TLabel *Label37;
	TBevel *Bevel1;
	TEdit *BeEnergy2Edit;
	TEdit *BeEnergy1Edit;
	TLabel *Label1;
	TLabel *Label2;
	TEdit *Be7PhotopeakEffEdit;
    void __fastcall SaveButtonClick(TObject *Sender);
    void __fastcall BrowseButtonClick(TObject *Sender);
    void __fastcall FormPaint(TObject *Sender);
    void __fastcall FileNameChange(TObject *Sender);

private:
    std::unique_ptr<TMemIniFile> IniFile;
    void LoadEnergyRanges();
    void LoadDensity_1_Data();
    void LoadDensity_2_Data();
    void LoadDensity_3_Data();

    void SaveEnergyRanges();
    void SaveDensity_1_Data();
    void SaveDensity_2_Data();
	void SaveDensity_3_Data();

	void ChangeUILanguage();

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
            !(Sysutils::StrToFloatDef(Th1ActivityEdit->Text, 0) <= 0 ||
            Sysutils::StrToFloatDef(Ra1ActivityEdit->Text, 0) <= 0 ||
            Sysutils::StrToFloatDef(K1ActivityEdit->Text, 0) <= 0 ||
            Sysutils::StrToFloatDef(Cs1ActivityEdit->Text, 0) <= 0 ||

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
            !(Sysutils::StrToFloatDef(Th2ActivityEdit->Text, 0) <= 0 ||
            Sysutils::StrToFloatDef(Ra2ActivityEdit->Text, 0) <= 0 ||
            Sysutils::StrToFloatDef(K2ActivityEdit->Text, 0) <= 0 ||
            Sysutils::StrToFloatDef(Cs2ActivityEdit->Text, 0) <= 0 ||

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
            !(Sysutils::StrToFloatDef(Th3ActivityEdit->Text, 0) <= 0 ||
            Sysutils::StrToFloatDef(Ra3ActivityEdit->Text, 0) <= 0 ||
            Sysutils::StrToFloatDef(K3ActivityEdit->Text, 0) <= 0 ||
            Sysutils::StrToFloatDef(Cs3ActivityEdit->Text, 0) <= 0 ||

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
