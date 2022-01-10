//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "BatchProcessingResultsFormU.h"
#include "Common.h"
#include <memory>
#include "UxTheme.h"
#include "MainFormU.h"
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TBatchProcessingResultsForm *BatchProcessingResultsForm = nullptr;
//---------------------------------------------------------------------------
__fastcall TBatchProcessingResultsForm::TBatchProcessingResultsForm(TComponent* Owner)
	: TForm(Owner)
{
    ChangeUILanguage();
}
//---------------------------------------------------------------------------
void __fastcall TBatchProcessingResultsForm::CreateParams(TCreateParams &Params)
{
  TForm::CreateParams(Params);
  Params.Style |= WS_POPUP;
  Params.ExStyle |= WS_EX_APPWINDOW;
}
//---------------------------------------------------------------------------
void __fastcall TBatchProcessingResultsForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	CanClose = true;
}
//---------------------------------------------------------------------------
void __fastcall TBatchProcessingResultsForm::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree;
    BatchProcessingResultsForm = nullptr;
}
//---------------------------------------------------------------------------
void __fastcall TBatchProcessingResultsForm::AppEventsMessage(tagMSG &Msg, bool &Handled)
{
	if (Msg.message == WM_POSTRESULT && Msg.hwnd == Handle)
	{
		try
		{
			if (!Visible)
			{
                Show();
            }
			std::unique_ptr<TResultItem> ResultItem(reinterpret_cast<TResultItem*>(Msg.wParam));
			ResultsVector.push_back(*ResultItem);
			TListItem *Item = ResultsList->Items->Add();
			Item->Data = (void*)ResultItem->OK;
			if (!ResultItem->OK)
			{
				ErrorsCount++;
            }
			Item->Caption = String(ResultsList->Items->Count) + L".";
			Item->SubItems->Add(ResultItem->FileName);
			Item->SubItems->Add(ResultItem->ThActivity);
			Item->SubItems->Add(ResultItem->RaActivity);
			Item->SubItems->Add(ResultItem->KActivity);
			Item->SubItems->Add(ResultItem->CsActivity);
			Item->SubItems->Add(ResultItem->BeActivity);
			Item->SubItems->Add(ResultItem->Comment);
			StatusBar->SimpleText =
				StatusSpcsStr + L" " + IntToStr(ResultsList->Items->Count) + L"        " +
				StatusErrsStr + L" " + IntToStr(ErrorsCount);
		}
		catch (const Exception &E)
		{
			LOGEXCEPTION(E);
        }
		Handled = true;
		AppEvents->CancelDispatch();
    }
}
//---------------------------------------------------------------------------
void __fastcall TBatchProcessingResultsForm::ResultsListDrawItem(TCustomListView *Sender,
		  TListItem *Item, TRect &Rect, TOwnerDrawState State)
{
	if (Item->Data)
	{
		Sender->Canvas->Font->Color = clWindowText;
	}
	else
	{
		Sender->Canvas->Font->Color = clRed;
	}

	if (State.Contains(odSelected) || State.Contains(odHotLight))
	{
        HRESULT Res = S_FALSE;
        if (UseThemes())
        {
            HTHEME H = OpenThemeData(Sender->Handle, L"LISTVIEW");
            try
            {
                if (H != 0)
                {
                    Res = DrawThemeBackground(H, Sender->Canvas->Handle, 6, (State.Contains(odSelected) ? 11 : 2), &Rect, 0);
                }
            }
            __finally
            {
                if (H != 0)
                {
                    CloseThemeData(H);
                }
            }
        }
        if (Res != S_OK)
        {
            Sender->Canvas->Brush->Color = clSkyBlue;
            Sender->Canvas->Brush->Style = bsSolid;
            Sender->Canvas->Pen->Color = clSkyBlue;
            Sender->Canvas->Rectangle(Rect);
        }
	}

	try
	{
		TListView *LV = dynamic_cast<TListView *>(Sender);
		SetBkMode(LV->Canvas->Handle, TRANSPARENT);
		for (int i = 0; i < LV->Columns->Count; i++)
		{
			const int j = i - 1;
			String Str;
            if (i == 0)
            {
                Str = Item->Caption;
            }
            else if (j < Item->SubItems->Count)
            {
                Str = Item->SubItems->Strings[j];
			}
            int J = DT_CENTER;
            if (LV->Column[i]->Alignment == taLeftJustify)
			{
				J = DT_LEFT;
			}
			else if (LV->Column[i]->Alignment == taRightJustify)
			{
				J = DT_RIGHT;
			}
			RECT R = {0, 0, 0, 0};
			if (i == 0)
			{
				ListView_GetItemRect(LV->Handle, Item->Index, &R, LVIR_LABEL);
			}
			else
			{
				ListView_GetSubItemRect(LV->Handle, Item->Index, i, LVIR_LABEL, &R);
			}
			DrawText(LV->Canvas->Handle, Str.c_str(), Str.Length(), &R, J | DT_VCENTER | DT_SINGLELINE);
		}
	}
	catch (const Exception &E)
	{
		LOGEXCEPTION(E);
    }
}
//---------------------------------------------------------------------------
void __fastcall TBatchProcessingResultsForm::ResultsListCompare(TObject *Sender, TListItem *Item1,
		  TListItem *Item2, int Data, int &Compare)
{
	try
	{
		if (SortColumnIndex == 0 || SortColumnIndex == 7)
		{
			return;
		}
		else if (SortColumnIndex == 1)
		{
			const int i = SortColumnIndex - 1;
			const String &Str1 = i < Item1->SubItems->Count ? Item1->SubItems->Strings[i] : String();
			const String &Str2 = i < Item2->SubItems->Count ? Item2->SubItems->Strings[i] : String();
			if (Str1 == Str2)
			{
				Compare = 0;
			}
			else if (Str1 > Str2)
			{
				Compare = AscSortOrder ? 1 : -1;
			}
			else
			{
				Compare = AscSortOrder ? -1 : 1;
			}
		}
		else
		{
			const int i = SortColumnIndex - 1;
			String Str1 = i < Item1->SubItems->Count ? Item1->SubItems->Strings[i] : String();
			String Str2 = i < Item2->SubItems->Count ? Item2->SubItems->Strings[i] : String();
			int P = Str1.Pos(L"<");
			if (P > 0)
			{
				Str1 = Trim(Str1.SubString(P + 1, Str1.Length()));
			}
			else if ((P = Str1.Pos(Char(0x00B1))) > 0)
			{
				Str1 = Trim(Str1.SubString(1, P - 1));
			}
			P = Str2.Pos(L"<");
			if (P > 0)
			{
				Str2 = Trim(Str2.SubString(P + 1, Str2.Length()));
			}
			else if ((P = Str2.Pos(Char(0x00B1))) > 0)
			{
				Str2 = Trim(Str2.SubString(1, P - 1));
			}
			const double Val1 = Sysutils::StrToFloatDef(Str1, 0);
			const double Val2 = Sysutils::StrToFloatDef(Str2, 0);
			if (Val1 == Val2)
			{
				Compare = 0;
			}
			else if (Val1 > Val2)
			{
				Compare = AscSortOrder ? 1 : -1;
			}
			else
			{
                Compare = AscSortOrder ? -1 : 1;
            }
		}
	}
	catch (const Exception &E)
	{
		LOGEXCEPTION(E);
	}
}
//---------------------------------------------------------------------------
void __fastcall TBatchProcessingResultsForm::ResultsListColumnClick(TObject *Sender,
          TListColumn *Column)
{
	if (Column->Index == 0 || Column->Index == 7)
	{
		return;
	}
	else if (Column->Index == SortColumnIndex)
	{
		AscSortOrder = !AscSortOrder;
	}
	SortColumnIndex = Column->Index;
	ResultsList->CustomSort(nullptr, 0);
	for (int i = 0; i < ResultsList->Items->Count; i++)
	{
        ResultsList->Items->Item[i]->Caption = String(i + 1) + L".";
    }
}
//---------------------------------------------------------------------------

void __fastcall TBatchProcessingResultsForm::SaveToCSVFIleActionExecute(TObject *Sender)
{
	SaveDialog->Filter = L"CSV fayllar (*.csv)|*.csv";
	if (LangID == 1)
	{
		SaveDialog->Filter = L"CSV files (*.csv)|*.csv";
    }
	if (ResultsList->Items->Count == 0 || !SaveDialog->Execute(Handle))
	{
		return;
	}
	try
	{
		std::unique_ptr<TStringList> CSVFile(new TStringList());
		CSVFile->DefaultEncoding = TUnicodeEncoding::Unicode;
		String Line;
		for (int i = 0; i < ResultsList->Columns->Count; i++)
		{
			String Str = ResultsList->Column[i]->Caption;
			if (Str.Pos(L",") > 0)
			{
				Str = L"\"" + Str + L"\"";
			}
			Line = Line.IsEmpty() ? Str : Line + L"," + Str;
		}
		CSVFile->Add(Line);
		for (int i = 0; i < ResultsList->Items->Count; i++)
		{
			TListItem *Item = ResultsList->Items->Item[i];
			Line = L"";
			for (int j = 0; j < ResultsList->Columns->Count; j++)
			{
				String Str;
				if (j == 0)
				{
					Str = Item->Caption;
				}
				else if ((j - 1) < Item->SubItems->Count)
				{
					Str = Item->SubItems->Strings[j - 1];
				}
				if (Str.Pos(L",") > 0)
				{
					Str = L"\"" + Str + L"\"";
				}
				Line = Line.IsEmpty() ? Str : Line + L"," + Str;
			}
			CSVFile->Add(Line);
		}
		CSVFile->SaveToFile(SaveDialog->FileName);
	}
	catch (const Exception &E)
	{
		LOGEXCEPTION(E);
	}
}
//---------------------------------------------------------------------------
void __fastcall TBatchProcessingResultsForm::SaveToCSVFIleActionUpdate(TObject *Sender)
{
	SaveToCSVFIleAction->Enabled = ResultsList->Items->Count > 0;
}
//---------------------------------------------------------------------------
void __fastcall TBatchProcessingResultsForm::MoveToMainWindowActionExecute(TObject *Sender)
{
	const size_t i = ResultsList->Selected->Index;
	if (i < ResultsVector.size())
	{
		MainForm->OpenFromBatchResult(
			ResultsVector[i].FileName,
			ResultsVector[i].ThC,
			ResultsVector[i].RaC,
			ResultsVector[i].KC,
			ResultsVector[i].CsC);
	}
}
//---------------------------------------------------------------------------
void __fastcall TBatchProcessingResultsForm::MoveToMainWindowActionUpdate(TObject *Sender)
{
	MoveToMainWindowAction->Enabled = ResultsList->Selected != nullptr;
}
//---------------------------------------------------------------------------
void TBatchProcessingResultsForm::ChangeUILanguage()
{
	if (LangID == 0)
	{
		Caption = L"Ko'p sonli spektrlar tahlili - Natijalar";
		SaveToCSVFIleAction->Caption = L"CSV faylga saqlash";
		MoveToMainWindowAction->Caption = L"Asosiy oynaga o'tkazish";
		ResultsList->Column[1]->Caption = L"Fayl nomi";
		ResultsList->Column[2]->Caption = L"Th-232 - A, Bk/kg";
		ResultsList->Column[3]->Caption = L"Ra-226 - A, Bk/kg";
		ResultsList->Column[4]->Caption = L"K-40 - A, Bk/kg";
		ResultsList->Column[5]->Caption = L"Cs-137 - A, Bk/kg";
		ResultsList->Column[6]->Caption = L"Be-7 - A, Bk/kg";
		ResultsList->Column[7]->Caption = L"Izohlar";
		StatusSpcsStr = L"Spektrlar";
		StatusErrsStr = L"Xatolar";
		String Str = StatusBar->SimpleText;
		if (!Str.IsEmpty())
		{
			int P = Str.Pos(L"Spectra");
			if (P > 0)
			{
				Str = Sysutils::StringReplace(Str, L"Spectra", StatusSpcsStr, TReplaceFlags() << rfReplaceAll);
			}
			P = Str.Pos(L"Errors");
			if (P > 0)
			{
				Str = Sysutils::StringReplace(Str, L"Errors", StatusErrsStr, TReplaceFlags() << rfReplaceAll);
			}
            StatusBar->SimpleText = Str;
		}
	}
	else if (LangID == 1)
	{
		Caption = L"Batch processing - Results";
		SaveToCSVFIleAction->Caption = L"Save to CSV file";
		MoveToMainWindowAction->Caption = L"Send to main window";
		ResultsList->Column[1]->Caption = L"File name";
		ResultsList->Column[2]->Caption = L"Th-232 - A, Bq/kg";
		ResultsList->Column[3]->Caption = L"Ra-226 - A, Bq/kg";
		ResultsList->Column[4]->Caption = L"K-40 - A, Bq/kg";
		ResultsList->Column[5]->Caption = L"Cs-137 - A, Bq/kg";
		ResultsList->Column[6]->Caption = L"Be-7 - A, Bq/kg";
		ResultsList->Column[7]->Caption = L"Comments / Error messages";
		StatusSpcsStr = L"Spectra";
		StatusErrsStr = L"Errors";
		String Str = StatusBar->SimpleText;
		if (!Str.IsEmpty())
		{
			int P = Str.Pos(L"Spektrlar");
			if (P > 0)
			{
				Str = Sysutils::StringReplace(Str, L"Spektrlar", StatusSpcsStr, TReplaceFlags() << rfReplaceAll);
			}
			P = Str.Pos(L"Xatolar");
			if (P > 0)
			{
				Str = Sysutils::StringReplace(Str, L"Xatolar", StatusErrsStr, TReplaceFlags() << rfReplaceAll);
			}
			StatusBar->SimpleText = Str;
		}
	}
	else
	{
		throw Exception(L"Unknown language.");
	}
}
//---------------------------------------------------------------------------
void __fastcall TBatchProcessingResultsForm::ResultsListAdvancedCustomDrawItem(TCustomListView *Sender,
		  TListItem *Item, TCustomDrawState State, TCustomDrawStage Stage,
          bool &DefaultDraw)
{
	if (Stage != cdPrePaint)
	{
		return;
	}
	if (Item->Data == nullptr)
	{
		Sender->Canvas->Font->Color = clRed;
	}
	else
	{
		Sender->Canvas->Font->Color = clWindowText;
	}
    DefaultDraw = true;
}
//---------------------------------------------------------------------------

