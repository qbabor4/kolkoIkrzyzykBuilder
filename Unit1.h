//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TShape *Shape1;
        TShape *Shape2;
        TShape *Shape3;
        TShape *Shape4;
        TLabel *Label1;
        TLabel *Label2;
        TEdit *Edit1;
        TLabel *Label3;
        TLabel *Label4;
        TButton *Button1;
        TLabel *Label5;
        TLabel *Label6;
        TPanel *Panel1;
        TLabel *Label7;
        TLabel *Label8;
        TLabel *Label9;
        TLabel *Label10;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall put_character(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
