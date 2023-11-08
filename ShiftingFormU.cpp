//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ShiftingFormU.h"
#include <Clipbrd.hpp>
#include "Common.h"

#ifndef SEPARATEAPP
#include "MainFormU.h"
#endif
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TShiftingForm *ShiftingForm;
//---------------------------------------------------------------------------
__fastcall TShiftingForm::TShiftingForm(TComponent* Owner)
    : TForm(Owner)
{
	if (Application->OnException == nullptr)
	{
		Application->OnException = OnAppException;
	}
	FormatSettings.DecimalSeparator = L'.';
    DValEdit1->Text = 0.1;
	DValEdit2->Text = 0.1;
    ChangeUILanguage();
}
//---------------------------------------------------------------------------
void __fastcall TShiftingForm::CreateParams(TCreateParams &Params)
{
  TForm::CreateParams(Params);
  Params.Style |= WS_POPUP;
  Params.ExStyle |= WS_EX_APPWINDOW;
}
//---------------------------------------------------------------------------
void __fastcall TShiftingForm::OnAppException(TObject* Sender, Exception* E)
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
	String ErrorTitle = L"Xato";
	String ErrorMsg =
		L"Quyidagi xatolik yuz berdi. Iltimos, dasturchiga xabar bering:\r\n\r\n" + E->Message;
	if (LangID == 1)
	{
		ErrorMsg = L"The following error occurred. Please inform the developer:\r\n\r\n" + E->Message;
		ErrorTitle = L"Error";
	}
	Application->MessageBox(ErrorMsg.c_str(), ErrorTitle.c_str(), MB_OK | MB_ICONERROR);
}
//---------------------------------------------------------------------------
void __fastcall TShiftingForm::LogLinButtonClick(TObject *Sender)
{
	SpcChart->LeftAxis->Logarithmic = !SpcChart->LeftAxis->Logarithmic;
	if (SpcChart->LeftAxis->Logarithmic)
	{
		LogLinButton->Caption = L"Log.";
	}
	else
	{
		if (LangID == 0)
		{
			LogLinButton->Caption = L"Chiz.";
		}
		else if (LangID == 1)
		{
			LogLinButton->Caption = L"Lin.";
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TShiftingForm::Spectrum1ButtonClick(TObject *Sender)
{
	OpenDialog->Filter = Utils::GetDialogBoxFilterForSpectraFiles();
	OpenDialog->FileName = L"";
	TSpectrum Spc;
    if (!OpenDialog->Execute(Handle) || !Spc.LoadFromFile(OpenDialog->FileName))
    {
        return;
    }
	Sample1FileName = OpenDialog->FileName;
	Caption =
		AppName + L" - [1: " + Sysutils::ExtractFileName(Sample1FileName) + L", 2: " +
		Sysutils::ExtractFileName(Sample2FileName) + L"]";
    Sample1 = Spc;
    DrawSpectrum(Sample1, Spectrum1);
    Energy1Edit->Text = Sample1.Energy1;
    Energy2Edit->Text = Sample1.Energy2;
	SrcChan1Edit->Text = Sample1.Channel1;
    SrcChan2Edit->Text = Sample1.Channel2;
    SmpChan1Edit->Text = L"";
	SmpChan2Edit->Text = L"";
	Spectrum1_MI->Checked = true;
	Spectrum1->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TShiftingForm::Spectrum2ButtonClick(TObject *Sender)
{
    OpenDialog->Filter = Utils::GetDialogBoxFilterForSpectraFiles();
	OpenDialog->FileName = L"";
    TSpectrum Spc;
	if (!OpenDialog->Execute(Handle) || !Spc.LoadFromFile(OpenDialog->FileName))
    {
        return;
    }
	Sample2FileName = OpenDialog->FileName;
	Caption =
		AppName + L" - [1: " + Sysutils::ExtractFileName(Sample1FileName) + L", 2: " +
		Sysutils::ExtractFileName(Sample2FileName) + L"]";
    Sample2 = Spc;
    ShiftedSample2 = Sample2;
    DrawSpectrum(Sample2, Spectrum2);
    SmpChan1Edit->Text = L"";
    SmpChan2Edit->Text = L"";
	Spectrum2_MI->Checked = true;
	Spectrum2->Visible = true;
	const String &Ext = Strutils::RightStr(Sample2FileName, 4).LowerCase();
	SaveToASWMI->Visible = Ext == L".asw";
	SaveToGSPMI->Visible = Ext == L".gsp";
}
//---------------------------------------------------------------------------
void TShiftingForm::DrawSpectrum(const TSpectrum &Spc, TLineSeries *LineSeries)
{
	LineSeries->Clear();
	for (size_t i = 0; i < Spc.Counts.size(); i++)
	{
		LineSeries->AddXY(i, Spc.Counts[i] < 0 ? 0 : Spc.Counts[i]);
	}
}
//---------------------------------------------------------------------------
void __fastcall TShiftingForm::Ch1LeftShiftBtnClick(TObject *Sender)
{
    if (!DValEdit1->Focused())
    {
        DValEdit1->SetFocus();
    }
    double Val = Sysutils::StrToFloatDef(SmpChan1Edit->Text, 0);
    if (Val <= 0)
    {
        return;
    }
    double dVal = Sysutils::StrToFloatDef(DValEdit1->Text, 0);
    if (dVal <= 0)
    {
        dVal = 1;
    }
    Val += dVal;
    SmpChan1Edit->Text = Val;
}
//---------------------------------------------------------------------------
void __fastcall TShiftingForm::Ch1RightShiftBtnClick(TObject *Sender)
{
    if (!DValEdit1->Focused())
    {
        DValEdit1->SetFocus();
    }
    double Val = Sysutils::StrToFloatDef(SmpChan1Edit->Text, 0);
    if (Val <= 0)
    {
        return;
    }
    double dVal = Sysutils::StrToFloatDef(DValEdit1->Text, 0);
    if (dVal <= 0)
    {
        dVal = 1;
    }
    Val -= dVal;
    SmpChan1Edit->Text = Val;
}
//---------------------------------------------------------------------------
void __fastcall TShiftingForm::Ch2LeftShiftBtnClick(TObject *Sender)
{
    if (!DValEdit2->Focused())
    {
        DValEdit2->SetFocus();
    }
    double Val = Sysutils::StrToFloatDef(SmpChan2Edit->Text, 0);
    if (Val <= 0)
    {
        return;
    }
    double dVal = Sysutils::StrToFloatDef(DValEdit2->Text, 0);
	if (dVal <= 0)
    {
        dVal = 1;
    }
    Val += dVal;
    SmpChan2Edit->Text = Val;
}
//---------------------------------------------------------------------------
void __fastcall TShiftingForm::Ch2RightShiftBtnClick(TObject *Sender)
{
    if (!DValEdit2->Focused())
    {
        DValEdit2->SetFocus();
    }
    double Val = Sysutils::StrToFloatDef(SmpChan2Edit->Text, 0);
    if (Val <= 0)
    {
        return;
    }
    double dVal = Sysutils::StrToFloatDef(DValEdit2->Text, 0);
    if (dVal <= 0)
    {
        dVal = 1;
    }
    Val -= dVal;
    SmpChan2Edit->Text = Val;
}
//---------------------------------------------------------------------------
void __fastcall TShiftingForm::SpcChartMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y)
{
    if (Spectrum1->Count() <= 0 && Spectrum2->Count() <= 0)
    {
        return;
	}
    if (SpcChart->Tag != X)
    {
        if (X < SpcChart->ChartRect.Left || X > SpcChart->ChartRect.Right ||
            Y < SpcChart->ChartRect.Top  || Y > SpcChart->ChartRect.Bottom)
        {
            return;
        }
        const int Ch = SpcChart->BottomAxis->CalcPosPoint(X);
        if (Ch >= 0 && Ch < Sample1.Energies.size())
        {
			StatusBar->Panels->Items[0]->Text = ChannelStr + String(Ch);
            StatusBar->Panels->Items[1]->Text =
				EnergyStr + Utils::RoundFloatValue(Sample1.Energies[Ch]);
        }
        if (Ch >= 0 && Ch < Sample1.Counts.size())
        {
			StatusBar->Panels->Items[2]->Text = Count1Str + String(Sample1.Counts[Ch]);
		}
        if (Ch >= 0 && Ch < ShiftedSample2.Counts.size())
        {
            StatusBar->Panels->Items[3]->Text = Count2Str + String(ShiftedSample2.Counts[Ch]);
        }
        SpcChart->Canvas->MoveTo(X, SpcChart->ChartRect.Top);
        SpcChart->Canvas->LineTo(X, SpcChart->ChartRect.Bottom);
        RECT R;
        R.left = SpcChart->Tag;
        R.top = 0;
        R.right = SpcChart->Tag + 1;
        R.bottom = SpcChart->ClientHeight;
        InvalidateRect(SpcChart->Handle, &R, TRUE);
        SpcChart->Tag = X;
    }
}
//---------------------------------------------------------------------------
void TShiftingForm::Shift()
{
    const double En1 = Sysutils::StrToFloatDef(Energy1Edit->Text, 0);
    const double En2 = Sysutils::StrToFloatDef(Energy2Edit->Text, 0);
    const double SrcCh1 = Sysutils::StrToFloatDef(SrcChan1Edit->Text, 0);
    const double SrcCh2 = Sysutils::StrToFloatDef(SrcChan2Edit->Text, 0);
    const double SmpCh1 = Sysutils::StrToFloatDef(SmpChan1Edit->Text, 0);
    const double SmpCh2 = Sysutils::StrToFloatDef(SmpChan2Edit->Text, 0);
    if (En1    > 0 && En2    > En1 &&
        SrcCh1 > 0 && SrcCh2 > SrcCh1 &&
        SmpCh1 > 0 && SmpCh2 > SmpCh1 &&
        Sample2.IsValid())
    {
        TSpectrum ShiftedSample2;
        if (Sample2.Shift(SrcCh1, SrcCh2, SmpCh1, SmpCh2, En1, En2, ShiftedSample2))
        {
            this->ShiftedSample2 = ShiftedSample2;
			DrawSpectrum(this->ShiftedSample2, Spectrum2);
        }
    }
    else
    {
        LOG("ERROR! Parameters are not valid to perform shifting.");
    }
}
//---------------------------------------------------------------------------
void __fastcall TShiftingForm::OnDataEditChange(TObject *Sender)
{
    if (ShiftingTimer->Enabled)
    {
        ShiftingTimer->Enabled = false;
    }
    TEdit *Edit = dynamic_cast<TEdit*>(Sender);
    if (!Edit->Focused())
    {
        Shift();
    }
    else
    {
        ShiftingTimer->Enabled = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall TShiftingForm::OnShiftingTimerTimer(TObject *Sender)
{
    ShiftingTimer->Enabled = false;
    Shift();
}
//---------------------------------------------------------------------------
void __fastcall TShiftingForm::Spectrum1_MIClick(TObject *Sender)
{
    if (Spectrum1->Count() > 0)
    {
		Spectrum1_MI->Checked = !Spectrum1_MI->Checked;
		Spectrum1->Visible = Spectrum1_MI->Checked;
	}
}
//---------------------------------------------------------------------------
void __fastcall TShiftingForm::Spectrum2_MIClick(TObject *Sender)
{
    if (Spectrum2->Count() > 0)
    {
		Spectrum2_MI->Checked = !Spectrum2_MI->Checked;
		Spectrum2->Visible = Spectrum2_MI->Checked;
    }
}
//---------------------------------------------------------------------------
void TShiftingForm::SaveToOriginalFile()
{
	try
	{
		if (!Sysutils::FileExists(Sample2FileName) || !ShiftedSample2.IsValid())
		{
			LOG("ERROR: !Sysutils::FileExists(Sample2FileName) || !ShiftedSample2.IsValid()");
			return;
		}
		std::unique_ptr<TStringList> SL(new TStringList());
		SL->LoadFromFile(Sample2FileName);
		bool Found = false;
		for (int i = 0; i < SL->Count; i++)
		{
			const String &Line = Trim(SL->Strings[i]);
			if (!Found && Line.LowerCase() == L"[energy_calibration]")
			{
				Found = true;
				continue;
			}
			if (Found)
			{
				if (!Line.IsEmpty() && Line[1] == L'[')
				{
					break;
				}

				if (Line.LowerCase().Pos(L"channel1") && !SrcChan1Edit->Text.IsEmpty())
				{
					SL->Strings[i] =
						L"Channel1=" + FloatToStr(Sysutils::StrToFloatDef(SrcChan1Edit->Text, 0) + 1);
				}

				if (Line.LowerCase().Pos(L"channel2") && !SrcChan2Edit->Text.IsEmpty())
				{
					SL->Strings[i] =
						L"Channel2=" + FloatToStr(Sysutils::StrToFloatDef(SrcChan2Edit->Text, 0) + 1);
				}

				if (Line.LowerCase().Pos(L"energy1") && !Energy1Edit->Text.IsEmpty())
				{
					SL->Strings[i] = L"Energy1=" + Energy1Edit->Text;
				}

				if (Line.LowerCase().Pos(L"energy2") && !Energy2Edit->Text.IsEmpty())
				{
					SL->Strings[i] = L"Energy2=" + Energy2Edit->Text;
				}
			}
		}
		bool IsBinData = false;
		bool IsTextData = false;
		std::unique_ptr<TMemoryStream> BinaryData(new TMemoryStream());
		for (int i = 0; i < SL->Count; i++)
		{
			AnsiString Line = SL->Strings[i];
			Line += "\r\n";
			BinaryData->WriteBuffer(Line.c_str(), Line.Length());
			if (Line == "[BEGIN]\r\n")
			{
				IsBinData = true;
				break;
			}
			else if (Line == "[SPECTRUM]\r\n")
			{
				IsTextData = true;
                break;
            }
		}
		if (IsBinData)
		{
			for (auto C : ShiftedSample2.Counts)
			{
				const int Count = Math::Ceil(C);
				BinaryData->WriteBuffer(&Count, sizeof(Count));
			}
		}
		else if (IsTextData)
		{
			for (auto C : ShiftedSample2.Counts)
			{
				const AnsiString Line = IntToStr(Math::Ceil(C)) + "\r\n";
				BinaryData->WriteBuffer(Line.c_str(), Line.Length());
			}
		}
		else
		{
			if (LangID == 0)
				throw Exception(L"Faylning formati noto'g'ri.");
			else if (LangID == 1)
				throw Exception(L"File's format is not valid.");
		}
		BinaryData->Position = 0;
		BinaryData->SaveToFile(Sample2FileName);
	}
	catch (const Exception &E)
	{
		LOGEXCEPTION(E);
        String ErrorTitle = L"Xato";
		String ErrorMsg = L"Quyidagi xatolik yuz berdi:\r\n\r\n" + E.Message;
		if (LangID == 1)
		{
			ErrorTitle = L"Error";
			ErrorMsg = L"The following error occurred:\r\n\r\n" + E.Message;
		}
		Application->MessageBox(ErrorMsg.c_str(), ErrorTitle.c_str(), MB_OK | MB_ICONERROR);
	}
}
//---------------------------------------------------------------------------
void __fastcall TShiftingForm::SaveToASWMIClick(TObject *Sender)
{
	SaveToOriginalFile();
}
//---------------------------------------------------------------------------
void __fastcall TShiftingForm::SaveToGSPMIClick(TObject *Sender)
{
	SaveToOriginalFile();
}
//---------------------------------------------------------------------------
void __fastcall TShiftingForm::OpenDialogClose(TObject *Sender)
{
	SetForegroundWindow(Handle);
}
//---------------------------------------------------------------------------
void __fastcall TShiftingForm::AboutButtonClick(TObject *Sender)
{
	String AboutStr = L"Dastur haqida";
	String Copyright = L"Yadro Fizikasi Laboratoriyasi, Samarqand Davlat Universiteti";
    String Developer = L"Dasturchi: Asqarali Azimov";
	if (LangID == 1)
	{
		AboutStr = L"About";
        Copyright = L"Nuclear Physics Laboratory, Samarkand State University";
        Developer = L"Developer: Askarali Azimov";
    }

	String Version = GetVersionString();
	if (!Version.IsEmpty())
	{
		Version = L" v" + Version + L".";
	}
	const String &Message =
		String(AppName + Version + L"\r\n") +
		Char(169) + L" " + Copyright + L", 2021 - 2023.\r\n\r\n" +
        Developer;

	Application->MessageBox(Message.c_str(), AboutStr.c_str(), MB_OK | MB_ICONINFORMATION);
}
//---------------------------------------------------------------------------
void __fastcall TShiftingForm::FormShow(TObject *Sender)
{
	AboutButton->Visible = ShiftingForm == Application->MainForm;
    AboutBtnSeparator->Visible = AboutButton->Visible;
}
//---------------------------------------------------------------------------
String TShiftingForm::GetVersionString(const String &DefaultVal) const
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
void __fastcall TShiftingForm::CopyCountsMIClick(TObject *Sender)
{
    String Str;
    if (ShiftedSample2.IsValid() && ShiftedSample2.WriteCountsToString(Str, false, false))
    {
        Clipboard()->AsText = Str;
    }
}
//---------------------------------------------------------------------------
void __fastcall TShiftingForm::CopyEnergiesAndCountMIClick(TObject *Sender)
{
    String Str;
    if (ShiftedSample2.IsValid() && ShiftedSample2.WriteCountsToString(Str, false, true))
    {
        Clipboard()->AsText = Str;
    }
}
//---------------------------------------------------------------------------
void __fastcall TShiftingForm::SaveCountsMIClick(TObject *Sender)
{
    if (Sysutils::FileExists(Sample2FileName) || ShiftedSample2.IsValid())
    {
        ShiftedSample2.WriteCountsToTextFile(
            Sysutils::ChangeFileExt(Sample2FileName, L".txt"), false, false);
    }
}
//---------------------------------------------------------------------------
void __fastcall TShiftingForm::SaveEnergiesAndCountsMIClick(TObject *Sender)
{
    if (Sysutils::FileExists(Sample2FileName) || ShiftedSample2.IsValid())
    {
        ShiftedSample2.WriteCountsToTextFile(
            Sysutils::ChangeFileExt(Sample2FileName, L".txt"), false, true);
    }
}
//---------------------------------------------------------------------------
void TShiftingForm::ChangeUILanguage()
{
	if (LangID == 0)
	{
		AppName = L"Spektrni siljitish";
		if (!Sample1FileName.IsEmpty() || !Sample2FileName.IsEmpty())
		{
			Caption =
				AppName + L" - [1: " + Sysutils::ExtractFileName(Sample1FileName) + L", 2: " +
				Sysutils::ExtractFileName(Sample2FileName) + L"]";
		}
		else
		{
			Caption = AppName;
		}
		Spectrum1Button->Caption = L"Spektr 1";
		Spectrum2Button->Caption = L"Spektr 2 (Siljitiladigan)";
		SaveSpectrum2->Caption = L"Spektr 2 ni saqlash";
		Spectrum1_MI->Caption = L"Spektr 1";
		Spectrum2_MI->Caption = L"Spektr 2";
		ClipboardMI->Caption = L"Nusxa olish";
		CopyCountsMI->Caption = L"Faqat impulslar soni";
		CopyEnergiesAndCountMI->Caption = L"Energiya va impulslar soni";
		SaveToTXTMI->Caption = L"TXT faylga saqlash";
		SaveCountsMI->Caption = L"Faqat impulslar soni";
		SaveEnergiesAndCountsMI->Caption = L"Energiya va impulslar soni";
		SaveToASWMI->Caption = L"ASW faylga saqlash";
		SaveToGSPMI->Caption = L"GSP faylga saqlash";
		LogLinButton->Caption = SpcChart->LeftAxis->Logarithmic ? L"Log." : L"Chiz.";
		SpcChart->Title->Text->Text = L"Etalon va siljitiladigan spektrlar";
		SpcChart->LeftAxis->Title->Caption = L"Impuls";
		SpcChart->BottomAxis->Title->Caption = L"Kanal";
		Label1->Caption = L"Energiya 1:";
		Label2->Caption = L"Energiya 2:";
		Label7->Caption = L"Spektr 1 da";
		Label4->Caption = L"Kanal 1:";
		Label3->Caption = L"Kanal 2:";
		Label8->Caption = L"Spektr 2 da";
		Label6->Caption = Label4->Caption;
		Label5->Caption = Label3->Caption;
		ChannelStr = L"Kanal: ";
		EnergyStr = L"Energiya: ";
		Count1Str = L"Impuls 1: ";
		Count2Str = L"Impuls 2: ";
	}
	else if (LangID == 1)
	{
		AppName = L"Spectrum shifting";
		if (!Sample1FileName.IsEmpty() || !Sample2FileName.IsEmpty())
		{
			Caption =
				AppName + L" - [1: " + Sysutils::ExtractFileName(Sample1FileName) + L", 2: " +
				Sysutils::ExtractFileName(Sample2FileName) + L"]";
		}
		else
		{
			Caption = AppName;
		}
		Spectrum1Button->Caption = L"Spectrum 1";
		Spectrum2Button->Caption = L"Spectrum 2 (Getting shifted)";
		SaveSpectrum2->Caption = L"Save Spectrum 2";
		Spectrum1_MI->Caption = L"Spectrum 1";
		Spectrum2_MI->Caption = L"Spectrum 2";
		ClipboardMI->Caption = L"Copy";
		CopyCountsMI->Caption = L"Only count";
		CopyEnergiesAndCountMI->Caption = L"Energy and count";
		SaveToTXTMI->Caption = L"Save to TXT file";
		SaveCountsMI->Caption = CopyCountsMI->Caption;
		SaveEnergiesAndCountsMI->Caption = CopyEnergiesAndCountMI->Caption;
		SaveToASWMI->Caption = L"Save to ASW file";
		SaveToGSPMI->Caption = L"Save to GSP file";
		LogLinButton->Caption = SpcChart->LeftAxis->Logarithmic ? L"Log." : L"Lin.";
		SpcChart->Title->Text->Text = L"Reference and target spectra";
		SpcChart->LeftAxis->Title->Caption = L"Count";
		SpcChart->BottomAxis->Title->Caption = L"Channel";
		Label1->Caption = L"Energy 1:";
		Label2->Caption = L"Energy 2:";
		Label7->Caption = L"In spectrum 1";
		Label4->Caption = L"Channel 1:";
		Label3->Caption = L"Channel 2:";
		Label8->Caption = L"In spectrum 2";
		Label6->Caption = Label4->Caption;
		Label5->Caption = Label3->Caption;
		ChannelStr = L"Channel: ";
		EnergyStr = L"Energy: ";
		Count1Str = L"Count 1: ";
		Count2Str = L"Count 2: ";
	}
	else
	{
		throw Exception(L"Unknown language.");
	}
}
//---------------------------------------------------------------------------
void TShiftingForm::Load(
    const TSpectrum &Spc1,
    const TSpectrum &Spc2,
    const double En1,
    const double En2,
    const double Spc1Ch1,
    const double Spc1Ch2,
    const double Spc2Ch1,
    const double Spc2Ch2)
{
    Sample1 = Spc1;
    DrawSpectrum(Sample1, Spectrum1);
	Spectrum1_MI->Checked = true;
	Spectrum1->Visible = true;

    Sample2 = Spc2;
    ShiftedSample2 = Sample2;
    DrawSpectrum(Sample2, Spectrum2);
	Spectrum2_MI->Checked = true;
	Spectrum2->Visible = true;

    Energy1Edit->Text = En1;
    Energy2Edit->Text = En2;
	SrcChan1Edit->Text = Spc1Ch1;
    SrcChan2Edit->Text = Spc1Ch2;
    SmpChan1Edit->Text = Spc2Ch1;
	SmpChan2Edit->Text = Spc2Ch2;

    Shift();
}
//---------------------------------------------------------------------------
void __fastcall TShiftingForm::SaveSpectrum2Click(TObject *Sender)
{
#ifndef SEPARATEAPP
    MainForm->SetSampleSpectrum(ShiftedSample2, SmpChan1Edit->Text, SmpChan2Edit->Text);
    Close();
#endif
}
//---------------------------------------------------------------------------
void TShiftingForm::Reset()
{
    Sample1 = TSpectrum();
    Spectrum1->Clear();
	Sample2 = TSpectrum();
    Spectrum2->Clear();
    ShiftedSample2 = TSpectrum();
	Sample1FileName = L"";
	Sample2FileName = L"";
    Energy1Edit->Text = L"";
    Energy2Edit->Text = L"";
    SrcChan2Edit->Text = L"";
    SrcChan1Edit->Text = L"";
    SmpChan2Edit->Text = L"";
    SmpChan1Edit->Text = L"";
    ChangeUILanguage();
}
