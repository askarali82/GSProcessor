//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "SpectrumFrameU.h"
#include "Common.h"
#include "MainFormU.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TSpectrumFrame::TSpectrumFrame(TComponent* Owner):
    TFrame(Owner),
    Modified(false)
{
    if (LangID == 0)
    {
        RawDataTable->Cells[0][0] = L"Kanal";
        RawDataTable->Cells[1][0] = L"Energiya";
        RawDataTable->Cells[2][0] = L"Impulslar soni";
    }
    else if (LangID == 1)
    {
        RawDataTable->Cells[0][0] = L"Channel";
        RawDataTable->Cells[1][0] = L"Energy";
        RawDataTable->Cells[2][0] = L"Counts";
    }
    SpcChart->LeftAxis->Title->Font->Size = 10;
    SpcChart->BottomAxis->Title->Font->Size = 10;
}
//---------------------------------------------------------------------------
void TSpectrumFrame::SetSpectrum(const TSpectrum &ASpectrum)
{
    Spectrum = ASpectrum;
    SpectrumLine->Clear();
    for (size_t i = 0; i < Spectrum.Counts.size(); i++)
    {
        SpectrumLine->AddXY(Spectrum.Energies[i], Spectrum.Counts[i]);
    }
    LiveTimeEdit->Text = Utils::RoundFloatValue(Spectrum.Duration);
    RealTimeEdit->Text = Utils::RoundFloatValue(Spectrum.DurationReal);

    SampleMassEdit->Text = Utils::RoundFloatValue(Spectrum.Weight);
    SampleMassUnitBox->ItemIndex = SampleMassUnitBox->Items->IndexOf(Spectrum.WeightUnit.LowerCase());

    SampleVolumeEdit->Text = Utils::RoundFloatValue(Spectrum.Volume);
    SampleVolumeUnitBox->ItemIndex = SampleVolumeUnitBox->Items->IndexOf(Spectrum.VolumeUnit.LowerCase());

    const auto Total = Spectrum.CalculateTotalCount();
    TotalCountEdit->Text = Utils::RoundFloatValue(Total);
    CPSEdit->Text = Utils::RoundFloatValue(Total / Spectrum.Duration);

    PointsBox->ItemIndex = PointsBox->Items->IndexOf(Spectrum.CalibrationPoints);
    PointsBoxChange(PointsBox);
    TEdit *ChanEdits[] = {Channel1Edit, Channel2Edit, Channel3Edit, Channel4Edit, Channel5Edit};
    TEdit *EnEdits[] = {Energy1Edit, Energy2Edit, Energy3Edit, Energy4Edit, Energy5Edit};
    const auto &Chans = Spectrum.GetCalPointsChannels();
    const auto &Ens = Spectrum.GetCalPointsEnergies();
    for (int i = 0; i < 5; i++)
    {
        ChanEdits[i]->Text = ChanEdits[i]->Enabled ? Utils::RoundFloatValue(Chans[i]) : String();
        EnEdits[i]->Text = EnEdits[i]->Enabled ? Utils::RoundFloatValue(Ens[i]) : String();
    }

    RawDataTable->RowCount = Spectrum.Counts.size() + 1;
    if (LangID == 0)
    {
        RawDataTable->Cells[0][0] = L"Kanal";
        RawDataTable->Cells[1][0] = L"Energiya";
        RawDataTable->Cells[2][0] = L"Impulslar soni";
    }
    else if (LangID == 1)
    {
        RawDataTable->Cells[0][0] = L"Channel";
        RawDataTable->Cells[1][0] = L"Energy";
        RawDataTable->Cells[2][0] = L"Counts";
    }
    for (size_t i = 0; i < Spectrum.Counts.size(); i++)
    {
        const int I = i + 1;
        RawDataTable->Cells[0][I] = i;
        RawDataTable->Cells[1][I] = Utils::RoundFloatValue(Spectrum.Energies[i]);
        RawDataTable->Cells[2][I] = Utils::RoundFloatValue(Spectrum.Counts[i]);
    }
}
//---------------------------------------------------------------------------
void __fastcall TSpectrumFrame::SpcChartMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y)
{
    if (SpectrumLine->Count() <= 0 || X < SpcChart->ChartRect.Left || X > SpcChart->ChartRect.Right ||
        Y < SpcChart->ChartRect.Top  || Y > SpcChart->ChartRect.Bottom)
    {
        return;
    }

    String ChannelStr = L"Kanal: ";
    String EnergyStr = L"Energiya: ";
    String CountStr = L"Impuls: ";
    if (LangID == 1)
    {
        ChannelStr = L"Channel: ";
        EnergyStr = L"Energy: ";
        CountStr = L"Count: ";
    }

    const double En = SpectrumLine->XScreenToValue(X);
    StatusBar->Panels->Items[1]->Text = EnergyStr + Utils::RoundFloatValue(En);
    const int Ch = Utils::FindChannelByEnergy(En, SpectrumLine);
    if (Ch >= 0 && Ch < SpectrumLine->Count())
    {
        const double N = SpectrumLine->YValues->Value[Ch];
        StatusBar->Panels->Items[0]->Text = ChannelStr + IntToStr(Ch);
        StatusBar->Panels->Items[2]->Text = CountStr + Utils::RoundFloatValue(N);
    }

    SpcChart->Tag = X;
    SpcChart->Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TSpectrumFrame::SpcChartAfterDraw(TObject *Sender)
{
    if (SpectrumLine->Count() > 0 && SpcChart->Tag >= SpcChart->ChartRect.Left &&
        SpcChart->Tag <= SpcChart->ChartRect.Right)
    {
        auto Canvas = SpcChart->Canvas;
        Canvas->Pen->Color = clBlack;
        Canvas->Pen->Width = 1;

        Canvas->MoveTo(SpcChart->Tag, SpcChart->ChartRect.Top);
        Canvas->LineTo(SpcChart->Tag, SpcChart->ChartRect.Bottom);
    }
}
//---------------------------------------------------------------------------
void __fastcall TSpectrumFrame::PointsBoxChange(TObject *Sender)
{
    const int CalibrationPoints = PointsBox->Text.ToIntDef(-1);
    TLabel *ChanLabels[] = {Chan1Label, Chan2Label, Chan3Label, Chan4Label, Chan5Label};
    TEdit *ChanEdits[] = {Channel1Edit, Channel2Edit, Channel3Edit, Channel4Edit, Channel5Edit};
    TLabel *EnLabels[] = {Energy1Label, Energy2Label, Energy3Label, Energy4Label, Energy5Label};
    TEdit *EnEdits[] = {Energy1Edit, Energy2Edit, Energy3Edit, Energy4Edit, Energy5Edit};
    for (int i = 0; i < 5; i++)
    {
        ChanLabels[i]->Enabled = i < CalibrationPoints;
        ChanEdits[i]->Enabled = i < CalibrationPoints;
        EnLabels[i]->Enabled = i < CalibrationPoints;
        EnEdits[i]->Enabled = i < CalibrationPoints;
    }
    OnDataChange(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TSpectrumFrame::OnDataChange(TObject *Sender)
{
    TWinControl *Ctrl = dynamic_cast<TWinControl *>(Sender);
    Modified = Ctrl->Focused() && Spectrum.IsValid();
    if (Ctrl == PointsBox ||
        Ctrl == Channel1Edit ||
        Ctrl == Channel2Edit ||
        Ctrl == Channel3Edit ||
        Ctrl == Channel4Edit ||
        Ctrl == Channel5Edit ||
        Ctrl == Energy1Edit ||
        Ctrl == Energy2Edit ||
        Ctrl == Energy3Edit ||
        Ctrl == Energy4Edit ||
        Ctrl == Energy5Edit)
    {
        CalibrateButton->Enabled = CalibrateButton->Enabled || Modified;
    }
    if (Ctrl == SampleMassEdit ||
        Ctrl == SampleVolumeEdit ||
        Ctrl == Channel1Edit ||
        Ctrl == Channel2Edit ||
        Ctrl == Channel3Edit ||
        Ctrl == Channel4Edit ||
        Ctrl == Channel5Edit ||
        Ctrl == Energy1Edit ||
        Ctrl == Energy2Edit ||
        Ctrl == Energy3Edit ||
        Ctrl == Energy4Edit ||
        Ctrl == Energy5Edit)
    {
        OnEditBoxChange(dynamic_cast<TEdit *>(Sender));
    }
}
//---------------------------------------------------------------------------
bool TSpectrumFrame::SwitchToLinLogScale()
{
    if (SpectrumLine->Count() <= 0)
    {
        return true;
    }
    if (!SpcChart->LeftAxis->Logarithmic)
    {
        SpcChart->LeftAxis->Increment = 0;
    }
    SpcChart->LeftAxis->Logarithmic = !SpcChart->LeftAxis->Logarithmic;
    if (!SpcChart->LeftAxis->Logarithmic)
    {
        SpcChart->LeftAxis->Increment = 100;
    }
    return !SpcChart->LeftAxis->Logarithmic;
}
//---------------------------------------------------------------------------
void __fastcall TSpectrumFrame::CalibrateButtonClick(TObject *Sender)
{
    auto TMPSpc = Spectrum;
    TMPSpc.CalibrationPoints = PointsBox->Text.ToIntDef(2);
    TMPSpc.Channel1 = Sysutils::StrToFloatDef(Channel1Edit->Text, 0);
    TMPSpc.Channel2 = Sysutils::StrToFloatDef(Channel2Edit->Text, 0);
    TMPSpc.Channel3 = Channel3Edit->Enabled ? Sysutils::StrToFloatDef(Channel3Edit->Text, 0) : 0;
    TMPSpc.Channel4 = Channel4Edit->Enabled ? Sysutils::StrToFloatDef(Channel4Edit->Text, 0) : 0;
    TMPSpc.Channel5 = Channel5Edit->Enabled ? Sysutils::StrToFloatDef(Channel5Edit->Text, 0) : 0;
    TMPSpc.Energy1 = Sysutils::StrToFloatDef(Energy1Edit->Text, 0);
    TMPSpc.Energy2 = Sysutils::StrToFloatDef(Energy2Edit->Text, 0);
    TMPSpc.Energy3 = Energy3Edit->Enabled ? Sysutils::StrToFloatDef(Energy3Edit->Text, 0) : 0;
    TMPSpc.Energy4 = Energy4Edit->Enabled ? Sysutils::StrToFloatDef(Energy4Edit->Text, 0) : 0;
    TMPSpc.Energy5 = Energy5Edit->Enabled ? Sysutils::StrToFloatDef(Energy5Edit->Text, 0) : 0;
    TMPSpc.CheckError(
        TMPSpc.Channel1 > 0 && TMPSpc.Channel2 > 0 &&
        TMPSpc.Channel2 > TMPSpc.Channel1 &&
        TMPSpc.Energy1 > 0 && TMPSpc.Energy2 > 0 &&
        TMPSpc.Energy2 > TMPSpc.Energy1 &&
        L"1 yoki 2-nuqtalarning kanal yoki energiya qiymatlari noto‘g‘ri.");
    if (TMPSpc.CalibrationPoints > 2)
    {
        if (TMPSpc.Channel3 > 0 || TMPSpc.Energy3 > 0)
        {
            TMPSpc.CheckError(
                TMPSpc.Channel3 > 0 && TMPSpc.Energy3 > 0 &&
                TMPSpc.Channel3 > TMPSpc.Channel2 && TMPSpc.Energy3 > TMPSpc.Energy2,
                L"3-nuqtaning kanal yoki energiya qiymati noto‘g‘ri.");
        }
        if (TMPSpc.Channel4 > 0 || TMPSpc.Energy4 > 0)
        {
            TMPSpc.CheckError(
                TMPSpc.Channel3 > 0 && TMPSpc.Energy3 > 0 &&
                TMPSpc.Channel4 > 0 && TMPSpc.Energy4 > 0 &&
                TMPSpc.Channel4 > TMPSpc.Channel3 && TMPSpc.Energy4 > TMPSpc.Energy3,
                L"3 yoki 4-nuqtalarning kanal yoki energiya qiymatlari noto‘g‘ri.");
        }
        if (TMPSpc.Channel5 > 0 || TMPSpc.Energy5 > 0)
        {
            TMPSpc.CheckError(
                TMPSpc.Channel3 > 0 && TMPSpc.Energy3 > 0 &&
                TMPSpc.Channel4 > 0 && TMPSpc.Energy4 > 0 &&
                TMPSpc.Channel5 > 0 && TMPSpc.Energy5 > 0 &&
                TMPSpc.Channel5 > TMPSpc.Channel4 && TMPSpc.Energy5 > TMPSpc.Energy4,
                L"Nuqtalarning kanal yoki energiya qiymatlari noto‘g‘ri.");
        }
        TMPSpc.CalibrationType = TSpectrum::TCalibrationType::Quadratic;
        TMPSpc.CalibrateWithQuadraticFunction();
    }
    else
    {
        TMPSpc.CalibrationType = TSpectrum::TCalibrationType::Linear;
        TMPSpc.B = (TMPSpc.Energy1 - TMPSpc.Energy2) / (TMPSpc.Channel1 - TMPSpc.Channel2);
        TMPSpc.A = TMPSpc.Energy1 - TMPSpc.B * TMPSpc.Channel1;
        TMPSpc.C = 0;
        int X = 0;
        for (auto &E : TMPSpc.Energies)
        {
            E = TMPSpc.A + TMPSpc.B * (X++);
        }
    }
    Spectrum = TMPSpc;
    SpectrumLine->Clear();
    for (size_t i = 0; i < Spectrum.Counts.size(); i++)
    {
        SpectrumLine->AddXY(Spectrum.Energies[i], Spectrum.Counts[i]);
        RawDataTable->Cells[1][i + 1] = Utils::RoundFloatValue(Spectrum.Energies[i]);
    }
}
//---------------------------------------------------------------------------
void __fastcall TSpectrumFrame::OnFValueEditKeyPress(TObject *Sender, System::WideChar &Key)
{
    TEdit *Edit = static_cast<TEdit*>(Sender);
    if (Key < 32 || Key == VK_BACK || (Key >= L'0' && Key <= L'9'))
    {
        return;
    }
    else if (Key == L'.')
    {
        if (Edit->Text.IsEmpty())
            Key = 0;
        else if (Edit->Text.Pos(L'.') > 0)
            Key = 0;
        return;
    }
    Key = 0;
}
//---------------------------------------------------------------------------
void TSpectrumFrame::OnEditBoxChange(TEdit *Edit)
{
    UnicodeString &LastValidText = LastValidTexts[Edit];
    const UnicodeString &S = Edit->Text;
    if (S.IsEmpty())
    {
        LastValidText = S;
        return;
    }
    int DotCount = 0;
    for (int i = 1; i <= S.Length(); ++i)
    {
        wchar_t c = S[i];
        if (c == L'.')
        {
            if (++DotCount > 1)
            {
                goto Invalid;
            }
        }
        else if (c < L'0' || c > L'9')
        {
            goto Invalid;
        }
    }
    if (S[1] == L'.')
    {
        goto Invalid;
    }
    LastValidText = S;
    return;

    Invalid:
        Edit->Text = LastValidText;
        Edit->SelStart = Edit->Text.Length();
}
//---------------------------------------------------------------------------
bool TSpectrumFrame::SaveSpectrumToFile(const String &FileName)
{
    try
    {
        Spectrum.WriteRawData(L"Sample", L"Weight", SampleMassEdit->Text);
        Spectrum.WriteRawData(L"Sample", L"Unit_weight", SampleMassUnitBox->Text);
        Spectrum.WriteRawData(L"Sample", L"Volume", SampleVolumeEdit->Text);
        Spectrum.WriteRawData(L"Sample", L"Unit_volume", SampleVolumeUnitBox->Text);
        TEdit *ChanEdits[] = {Channel1Edit, Channel2Edit, Channel3Edit, Channel4Edit, Channel5Edit};
        TEdit *EnEdits[] = {Energy1Edit, Energy2Edit, Energy3Edit, Energy4Edit, Energy5Edit};
        Spectrum.ClearRawDataSection(L"Energy_calibration");
        const int N = PointsBox->Text.ToIntDef(2);
        if (Spectrum.FileType == TSpectrum::asw)
        {
            Spectrum.WriteRawData(L"Energy_calibration", L"Point", N);
        }
        for (int i = 0; i < N; i++)
        {
            Spectrum.WriteRawData(L"Energy_calibration", L"Channel" + IntToStr(i + 1), ChanEdits[i]->Text);
        }
        for (int i = 0; i < N; i++)
        {
            Spectrum.WriteRawData(L"Energy_calibration", L"Energy" + IntToStr(i + 1), EnEdits[i]->Text);
        }
        if (Spectrum.SaveToFile(FileName))
        {
            Modified = false;
            return true;
        }
        else
        {
            throw Exception(Spectrum.ErrorMessage);
        }
    }
    catch (const Exception &E)
    {
        LOG(E.Message);
        Application->MessageBox(E.Message.c_str(), L"Error", MB_OK | MB_ICONERROR);
    }
    return false;
}
//---------------------------------------------------------------------------
bool TSpectrumFrame::SaveSpectrumToTextFile(
    const String &FileName, const bool IncludeChannels, const bool IncludeEnergies) const
{
    if (!Spectrum.WriteCountsToTextFile(FileName, IncludeChannels, IncludeEnergies))
    {
        Application->MessageBox(Spectrum.ErrorMessage.c_str(), L"Error", MB_OK | MB_ICONERROR);
        return false;
    }
    return true;
}

