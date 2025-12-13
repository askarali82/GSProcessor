//---------------------------------------------------------------------------
#ifndef AxisMinMaxFormUH
#define AxisMinMaxFormUH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TAxisMinMaxForm : public TForm
{
__published:	// IDE-managed Components
    TButton *Button1;
    TLabeledEdit *MinEdit;
    TLabeledEdit *MaxEdit;
    TButton *Button2;
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
    __fastcall TAxisMinMaxForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
