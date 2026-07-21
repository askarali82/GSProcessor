//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "SpectrumFrameU.h"
#include "Common.h"
#include "MainFormU.h"
#include "NuclideLibU.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TSpectrumFrame::TSpectrumFrame(TComponent* Owner):
    TFrame(Owner),
    Modified(false)
{
    if (NuclideLib == nullptr)
    {
        NuclideLib = &(TNuclideLib::GetInstance());
    }
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
    PageControl->ActivePage = ParametersTab;
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
    LiveTimeEdit->Text = Utils::RoundFloatValue(Spectrum.Duration) + L" s";
    RealTimeEdit->Text = Utils::RoundFloatValue(Spectrum.DurationReal) + L" s";

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
    String CountStr = L"Impulslar soni: ";
    if (LangID == 1)
    {
        ChannelStr = L"Channel: ";
        EnergyStr = L"Energy: ";
        CountStr = L"Count: ";
    }

    const double Energy = SpectrumLine->XScreenToValue(X);
    StatusBar->Panels->Items[1]->Text = EnergyStr + Utils::RoundFloatValue(Energy);
    const int Ch = Utils::FindChannelByEnergy(Energy, SpectrumLine);
    if (Ch >= 0 && Ch < SpectrumLine->Count())
    {
        const double Counts = SpectrumLine->YValues->Value[Ch];
        StatusBar->Panels->Items[0]->Text = ChannelStr + IntToStr(Ch);
        StatusBar->Panels->Items[2]->Text = CountStr + Utils::RoundFloatValue(Counts);
    }

    SpcChart->Tag = X;
    const double YValue = SpcChart->LeftAxis->CalcPosPoint(Y);
    PhotopeakInfo TargetPeak;
    for (auto &Peak : Photopeaks)
    {
        const bool InsideX =
            (Energy >= Spectrum.ChannelToEnergy(Peak.LeftBound)) &&
            (Energy <= Spectrum.ChannelToEnergy(Peak.RightBound));
        bool InsideY = false;
        if (InsideX && Ch >= 0 && Ch < SpectrumLine->Count())
        {
            const double Counts = SpectrumLine->YValues->Value[Ch];
            InsideY = (YValue <= Counts);
        }
        const bool NewState = InsideX && InsideY;
        if (Peak.Highlighted != NewState)
        {
            Peak.Highlighted = NewState;
        }
        if (Peak.Highlighted)
        {
            TargetPeak = Peak;
        }
    }
    if (TargetPeak.Highlighted)
    {
        ShowPeakDetails(TargetPeak);
    }
    else
    {
        ClearPeakDetails();
    }

    SpcChart->Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TSpectrumFrame::SpcChartAfterDraw(TObject *Sender)
{
    if (SpectrumLine->Count() == 0)
    {
        return;
    }

    auto Canvas = SpcChart->Canvas;
    if (!Photopeaks.empty())
    {
        for (auto &Peak : Photopeaks)
        {
            if (!Peak.Highlighted)
            {
                continue;
            }
            Canvas->Brush->Style = bsSolid;
            Canvas->Brush->Color = SpectrumLine->Color;
            std::vector<TPoint> Poly;

            const auto LeftEnergy = Spectrum.ChannelToEnergy(Peak.LeftBound);
            const auto RightEnergy = Spectrum.ChannelToEnergy(Peak.RightBound);

            Poly.push_back({
                SpcChart->BottomAxis->CalcXPosValue(LeftEnergy),
                SpcChart->LeftAxis->CalcYPosValue(0.0)
            });

            for (int i = 0; i < SpectrumLine->Count(); ++i)
            {
                const double E = SpectrumLine->XValue[i];
                if (E >= LeftEnergy && E <= RightEnergy)
                {
                    Poly.push_back({
                        SpcChart->BottomAxis->CalcXPosValue(E),
                        SpcChart->LeftAxis->CalcYPosValue(SpectrumLine->YValue[i])
                    });
                }
            }

            Poly.push_back({
                SpcChart->BottomAxis->CalcXPosValue(RightEnergy),
                SpcChart->LeftAxis->CalcYPosValue(0.0)
            });

            if (Poly.size() >= 3)
            {
                Canvas->Polygon(&Poly[0], Poly.size() - 1);
            }
        }

        Canvas->Pen->Color = SpectrumLine->Color;
        Canvas->Pen->Width = 3;
        for (const auto &Peak : Photopeaks)
        {
            const int Ch = Utils::FindChannelByEnergy(Peak.Energy, SpectrumLine);
            if (Ch >= 0 && Ch < SpectrumLine->Count())
            {
                const int Xpx = SpcChart->BottomAxis->CalcXPosValue(Peak.Energy);
                const double Yval = SpectrumLine->YValues->Value[Ch];
                const int Y0 = SpcChart->LeftAxis->CalcYPosValue(0.0);
                const int Y1 = SpcChart->LeftAxis->CalcYPosValue(Yval);
                Canvas->MoveTo(Xpx, Y0);
                Canvas->LineTo(Xpx, Y1);
            }
        }
    }

    if (SpcChart->Tag >= SpcChart->ChartRect.Left &&
        SpcChart->Tag <= SpcChart->ChartRect.Right)
    {
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
//---------------------------------------------------------------------------
void __fastcall TSpectrumFrame::RawDataTableMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
    int Row;
    int Col;
    RawDataTable->MouseToCell(X, Y, Col, Row);
    if (Row == 0)
    {
        const TGridRect GridRect{Col, RawDataTable->FixedRows, Col, RawDataTable->RowCount - 1};
        RawDataTable->Selection = GridRect;
    }
}
//---------------------------------------------------------------------------
void __fastcall TSpectrumFrame::RawDataTableMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
    if (Button == mbRight && ValidSpectrumExists())
    {
        const TGridRect &Sel = RawDataTable->Selection;
        if (Sel.Left > Sel.Right || Sel.Top > Sel.Bottom)
        {
            return;
        }
        const TPoint &P = RawDataTable->ClientToScreen(TPoint(X, Y));
        TablePopupMenu->Popup(P.X, P.Y);
    }
}
//---------------------------------------------------------------------------
void TSpectrumFrame::CopySelectedCells()
{
    String Result;
    const TGridRect &Sel = RawDataTable->Selection;
    for (int Row = Sel.Top; Row <= Sel.Bottom; ++Row)
    {
        for (int Col = Sel.Left; Col <= Sel.Right; ++Col)
        {
            Result += RawDataTable->Cells[Col][Row];

            if (Col < Sel.Right)
            {
                Result += L'\t';
            }
        }

        if (Row < Sel.Bottom)
        {
            Result += L"\r\n";
        }
    }
    Clipboard()->AsText = Result;
}
//---------------------------------------------------------------------------
void __fastcall TSpectrumFrame::RawDataTableKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if (Shift.Contains(ssCtrl) && Key == 'C' && ValidSpectrumExists())
    {
        const TGridRect &Sel = RawDataTable->Selection;
        if (Sel.Left > Sel.Right || Sel.Top > Sel.Bottom)
        {
            return;
        }
        CopySelectedCells();
        Key = 0;
    }
}
//---------------------------------------------------------------------------
bool TSpectrumFrame::FindPhotopeaks(const bool NeedsFound)
{
    if (!NeedsFound)
    {
        Photopeaks.clear();
        SpcChart->Repaint();
        return true;
    }
    if (!Spectrum.IsValid())
    {
        return false;
    }
    HPeakSearcher Handle = CreatePeakSearcher();
    if (Handle == nullptr)
    {
        return false;
    }
    try
    {
        if (!LoadSpectrumDouble(Handle, Spectrum.Counts.data(), Spectrum.Counts.size()))
        {
            return false;
        }
        SetCalibration(Handle, Spectrum.A, Spectrum.B, Spectrum.C);
        SetResolutionFromMeasurements(Handle, 45.8, 661, 72, 1460);
        SetSearchSigma(Handle, 6.5);
        SetSearchThreshold(Handle, 0.005);
        SetSearchMaxPeaks(Handle, 200);
        SetUseBackground(Handle, true);
        SetPerformGaussianFit(Handle, true);
        SetUseHighResSearch(Handle, true);

        LOG(L"Searching photopeaks...");
        const int PeakCount = SearchPhotopeaks(Handle);
        Photopeaks.clear();

        if (PeakCount > 0)
        {
            LOG(L"Found " + IntToStr(PeakCount) + L" photopeaks!");
            std::vector<PhotopeakInfo> Photopeaks;
            for (int i = 0; i < PeakCount; i++)
            {
                PhotopeakInfo Peak;
                if (GetPeakInfo(Handle, i, &Peak) && Peak.Energy > 50)
                {
                    Photopeaks.push_back(Peak);
                    LOG(L"\r\nFound Peak.Energy: " + Utils::RoundFloatValue(Peak.Energy) +
                        L"\r\nSigma: " + Utils::RoundFloatValue(Peak.Sigma) + L"\r\n");
                }
            }

            const auto &GammaLines = NuclideLib->GetAllGammaLines();
            std::set<String> DetectedSeries;
            for (auto& Peak : Photopeaks)
            {
                PeakMatchResult Result =
                    NuclideLib->MatchPhotopeak(
                    Peak, GammaLines, DetectedSeries, Spectrum,  1.5 + 0.001 * Peak.Position);
                if (Result.Matched)
                {
                    const MatchConfidence Conf = NuclideLib->GetConfidence(Result.Score);
                    if (Conf == MatchConfidence::Confident)
                    {
                        DetectedSeries.insert(Result.Line.Series);
                        this->Photopeaks.push_back(Peak);
                    }
                    LOG(L"\r\nPeak.Energy: " + Utils::RoundFloatValue(Peak.Energy) +
                        L"\r\nLine.Energy: " + Utils::RoundFloatValue(Result.Line.Energy) +
                        L"\r\nScore: " + Utils::RoundFloatValue(Result.Score) + L"\r\n");
                }
            }
        }
        else
        {
            LOG(L"Photopeaks not found.");
        }
    }
    __finally
    {
        DestroyPeakSearcher(Handle);
    }
    SpcChart->Repaint();
    if (!Photopeaks.empty())
    {
        PageControl->ActivePage = PeakInfoTab;
        ClearPeakDetails();
    }
    return !Photopeaks.empty();
}
//---------------------------------------------------------------------------
void TSpectrumFrame::ShowPeakDetails(const PhotopeakInfo &Peak)
{
    const auto &GammaLines = NuclideLib->GetAllGammaLines();
    if (Peak.LineIndex < GammaLines.size())
    {
        const auto &Line = GammaLines[Peak.LineIndex];
        EnergyValueLabel->Caption = Utils::RoundFloatValue(Line.Energy, 1, false) + L" keV";
        NucleusNameLabel->Caption = Line.HeadParent;
        EmitterNameLabel->Caption =
            Line.ImmediateParent + L"  →  " + Line.ImmediateParentDecayMode + L"  →  " + Line.GammaEmitter;
        GammaYieldValueLabel->Caption = Utils::RoundFloatValue(Line.GammaYield * 100, 1, false) + L"%";
        SeriesNameLabel->Caption = Line.Series;
    }
}
//---------------------------------------------------------------------------
void TSpectrumFrame::ClearPeakDetails()
{
    EnergyValueLabel->Caption = L"";
    NucleusNameLabel->Caption = L"";
    EmitterNameLabel->Caption = L"";
    GammaYieldValueLabel->Caption = L"";
    SeriesNameLabel->Caption = L"";
}
//---------------------------------------------------------------------------
void __fastcall TSpectrumFrame::PageControlDrawTab(TCustomTabControl *Control, int TabIndex,
          const TRect &Rect, bool Active)
{
    TCanvas *C = Control->Canvas;
    const TColor TextColor = clBlack;
    TColor BackColor;
    if (Active)
        BackColor = clSkyBlue;
    else
        BackColor = clBtnFace;
    C->Brush->Color = BackColor;
    C->FillRect(Rect);
    C->Brush->Style = bsClear;
    C->Font->Color = TextColor;
    const String &Caption = PageControl->Pages[TabIndex]->Caption;
    C->TextOut(Rect.Left + 6, Rect.Top + 4, Caption);
}
//---------------------------------------------------------------------------
void __fastcall TSpectrumFrame::PeakInfoTabShow(TObject *Sender)
{
    ClearPeakDetails();
}
//---------------------------------------------------------------------------
void __fastcall TSpectrumFrame::CopyMIClick(TObject *Sender)
{
    const TGridRect &Sel = RawDataTable->Selection;
    if (Sel.Left > Sel.Right || Sel.Top > Sel.Bottom)
    {
        return;
    }
    CopySelectedCells();
}
//---------------------------------------------------------------------------
void TSpectrumFrame::ChangeUILanguage()
{
    const int __LangID = LangID;

    if (__LangID == 0)
    {
        SpcChart->LeftAxis->Title->Caption = L"Impulslar soni";
        SpcChart->BottomAxis->Title->Caption = L"Energiya, keV";

        ParametersTab->Caption = L"  Parametrlar  ";
        LiveTimeLabel->Caption = L"Foydali vaqt (Live):";
        RealTimeLabel->Caption = L"Haqiqiy vaqt (Real):";
        TotalCountLabel->Caption = L"Jami impulslar soni:";
        IntensityLabel->Caption = L"Intensivlik (CPS):";
        SampleMassLabel->Caption = L"Namuna massasi:";
        SampleVolumeLabel->Caption = L"Namuna hajmi:";
        EnCalGroupBox->Caption = L" Energiya bo‘yicha kalibrovka ";
        PointsLabel->Caption = L"Nuqtalar soni:";
        Chan1Label->Caption = L"Kanal 1:";
        Energy1Label->Caption = L"Energiya 1:";
        Chan2Label->Caption = L"Kanal 2:";
        Energy2Label->Caption = L"Energiya 2:";
        Chan3Label->Caption = L"Kanal 3:";
        Energy3Label->Caption = L"Energiya 3:";
        Chan4Label->Caption = L"Kanal 4:";
        Energy4Label->Caption = L"Energiya 4:";
        Chan5Label->Caption = L"Kanal 5:";
        Energy5Label->Caption = L"Energiya 5:";
        CalibrateButton->Caption = L"Kalibrovka qilish";

        RawDataTab->Caption = L"  Spektr ma’lumotlari  ";
        if (ValidSpectrumExists())
        {
            RawDataTable->Cells[0][0] = L"Kanal";
            RawDataTable->Cells[1][0] = L"Energiya";
            RawDataTable->Cells[2][0] = L"Impulslar soni";
        }

        PeakInfoTab->Caption = L"  Fotocho‘qqi  ";
        EnergyLabel->Caption = L"Energiya:";
        NucleusLabel->Caption = L"Bosh / Ona yadro:";
        EmitterLabel->Caption = L"γ-nurlanuvchi yadro:";
        GammaYieldLabel->Caption = L"γ-nurlanish ehtimoliyati:";
        SeriesLabel->Caption = L"Radioaktiv qator:";
    }
    else if (__LangID == 1)
    {
        SpcChart->LeftAxis->Title->Caption = L"Counts per Channel:";
        SpcChart->BottomAxis->Title->Caption = L"Energy, keV";

        ParametersTab->Caption = L"  Parameters  ";
        LiveTimeLabel->Caption = L"Live Time:";
        RealTimeLabel->Caption = L"Real Time:";
        TotalCountLabel->Caption = L"Total counts:";
        IntensityLabel->Caption = L"Intensity (CPS):";
        SampleMassLabel->Caption = L"Sample mass:";
        SampleVolumeLabel->Caption = L"Sample volume:";
        EnCalGroupBox->Caption = L" Energy calibration ";
        PointsLabel->Caption = L"Number of points:";
        Chan1Label->Caption = L"Channel 1:";
        Energy1Label->Caption = L"Energy 1:";
        Chan2Label->Caption = L"Channel 2:";
        Energy2Label->Caption = L"Energy 2:";
        Chan3Label->Caption = L"Channel 3:";
        Energy3Label->Caption = L"Energy 3:";
        Chan4Label->Caption = L"Channel 4:";
        Energy4Label->Caption = L"Energy 4:";
        Chan5Label->Caption = L"Channel 5:";
        Energy5Label->Caption = L"Energy 5:";
        CalibrateButton->Caption = L"Calibrate";

        RawDataTab->Caption = L"  Spectrum Data  ";
        if (ValidSpectrumExists())
        {
            RawDataTable->Cells[0][0] = L"Channel";
            RawDataTable->Cells[1][0] = L"Energy";
            RawDataTable->Cells[2][0] = L"Counts";
        }

        PeakInfoTab->Caption = L"  Photopeak  ";
        EnergyLabel->Caption = L"Energy:";
        NucleusLabel->Caption = L"Parent nucleus:";
        EmitterLabel->Caption = L"γ-emitting nucleus:";
        GammaYieldLabel->Caption = L"γ-emission yield:";
        SeriesLabel->Caption = L"Radioactive series:";
    }

    PointsBox->Left = PointsLabel->Left + PointsLabel->Width + 5;
}
