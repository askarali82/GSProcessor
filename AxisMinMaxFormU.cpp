//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "AxisMinMaxFormU.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TAxisMinMaxForm::TAxisMinMaxForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TAxisMinMaxForm::FormClose(TObject *Sender, TCloseAction &Action)
{
    Action = caFree;
}
//---------------------------------------------------------------------------
