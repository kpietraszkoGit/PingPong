//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TPingPong : public TForm
{
__published:	// IDE-managed Components
        TImage *tlo;
        TTimer *Timer_pilka;
        TLabel *Label4;
        TImage *b;
        TLabel *Label5;
        TButton *Button1;
        TButton *Button2;
        TImage *pLewa;
        TImage *pPrawa;
        TTimer *lewoDol;
        TTimer *lewoGora;
        TTimer *prawoGora;
        TTimer *prawoDol;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall Label4Click(TObject *Sender);
        void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall lewoGoraTimer(TObject *Sender);
        void __fastcall lewoDolTimer(TObject *Sender);
        void __fastcall prawoDolTimer(TObject *Sender);
        void __fastcall prawoGoraTimer(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Timer_pilkaTimer(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TPingPong(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPingPong *PingPong;
//---------------------------------------------------------------------------
#endif
