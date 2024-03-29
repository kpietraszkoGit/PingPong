//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "mmsystem.h"
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPingPong *PingPong;

int x = -8;//poziom
int y = -8;//pion
int wygranaLewaStrona = 0;
int wygranaPrawaStrona = 0;
int iloscOdbic = 0;
bool gra_rozpoczeta = false;

void sekwencja()
{
   //Application->ProcessMessages(); Sleep(1000);  //zeby napis doskonale nam nie znikn<B9><B3> od razu

   PingPong->Label4->Caption = "Start rundy za 2";    //2 sekundy do rozpoczecia
   Application->ProcessMessages(); Sleep(1000);//ze jakies funcke aplikacji beda dzialac jak ja uspimy
   PingPong->Label4->Caption = "Start rundy za 1";  //jedna sekunda do rozpoczecia
   Application->ProcessMessages(); Sleep(1000);

   PingPong->Label4->Caption = "Start!";
   Application->ProcessMessages(); Sleep(1000);
   sndPlaySound("snd/start.wav",SND_ASYNC);
   PingPong->Timer_pilka->Enabled = true;
   PingPong->b->Visible = true;
   PingPong->Label4->Visible = false;
   PingPong->Label5->Visible = false;
}

//---------------------------------------------------------------------------
__fastcall TPingPong::TPingPong(TComponent* Owner)
        : TForm(Owner)
{

}
//---------------------------------------------------------------------------
void __fastcall TPingPong::FormCreate(TObject *Sender)
{

  char * w; //stary string
  w="Witam w grze PingPong.\nLewy gracz startuje naciskaj�c klawisze Q-g�ra, A-d�, a prawy normalnie pos�uguje sie strza�kami (g�ra, d�).\n\nKiedy odbijesz pi�k� na �rodku, ona przy�piesza i zmienia k�t. Im d�u�ej grasz, pi�ka bedzie przy�piesza�a.\nMi�ej gry! :) ";
  Application->MessageBox(w,"PingPong", MB_OK);
       /*      AnsiString strMessage = "Your record has been registered";
       AnsiString strCountry = "Country Name: Australia";
       AnsiString strCity = "City to visit: Melbourne";
      AnsiString strFinal = "Have a nice strip.";

       ShowMessage(strMessage + sLineBreak + strCountry + sLineBreak +                      strCity + sLineBreak + strFinal); */
}
//---------------------------------------------------------------------------

void __fastcall TPingPong::Label4Click(TObject *Sender)
{
       if (gra_rozpoczeta == false)
        {
         gra_rozpoczeta = true; //gra sie zaczela
         //sndPlaySound("snd/start.wav",SND_ASYNC);
         sekwencja(); //wywo<B3>anie funckji
       }
}
//---------------------------------------------------------------------------
void __fastcall TPingPong::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
   if (gra_rozpoczeta == true)
  {
    if (Key == 'Q') lewoGora->Enabled = false;
    if (Key == 'A') lewoDol->Enabled = false;
    if (Key == VK_UP) prawoGora->Enabled = false;
    if (Key == VK_DOWN) prawoDol->Enabled = false;
  }

}
//---------------------------------------------------------------------------
void __fastcall TPingPong::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
   if (gra_rozpoczeta == true)
   {
    if (Key == 'Q') lewoGora->Enabled = true;
    if (Key == 'A') lewoDol->Enabled = true;
    if (Key == VK_UP) prawoGora->Enabled = true;
    if (Key == VK_DOWN) prawoDol->Enabled = true;
   }
}
//---------------------------------------------------------------------------
void __fastcall TPingPong::Button1Click(TObject *Sender)//jeszcze raz
{

   b->Left = 800;
   b->Top = 300;
   b->Visible = true;
   x = -8; y = -8;
   Timer_pilka->Enabled = true;
   Button1->Visible = false;
   Button2->Visible = false;
   iloscOdbic = 0; //wstawic to na plansze
   Label1->Visible = false;
   Label2->Visible = false;
   Label3->Visible = false;
   Timer_pilka->Interval = 17;

}
//---------------------------------------------------------------------------
void __fastcall TPingPong::lewoGoraTimer(TObject *Sender)
{
        if (pLewa->Top > 5) pLewa->Top -= 10;
}
//---------------------------------------------------------------------------
void __fastcall TPingPong::lewoDolTimer(TObject *Sender)
{
        if (pLewa->Top+pLewa->Height < tlo->Height - 5) pLewa->Top += 10;        
}
//---------------------------------------------------------------------------
void __fastcall TPingPong::prawoDolTimer(TObject *Sender)
{
        if (pPrawa->Top+pPrawa->Height < tlo->Height - 5) pPrawa->Top += 10;        
}
//---------------------------------------------------------------------------
void __fastcall TPingPong::prawoGoraTimer(TObject *Sender)
{
        if (pPrawa->Top > 5) pPrawa->Top -= 10;
}
//---------------------------------------------------------------------------
void __fastcall TPingPong::Button2Click(TObject *Sender)  //nowa gra
{
    b->Left = 200;
    b->Top = 300;
    x = 8; y = 8;
    Timer_pilka->Enabled = true;
    Button1->Visible = false;
    Button2->Visible = false;
    Label1->Visible = false;
    Label2->Visible = false;
    Label3->Visible = false;
    iloscOdbic = 0; //wstawic to na plansze
    wygranaLewaStrona = 0;
    wygranaPrawaStrona = 0;//rester ilosci wygranej prawej i lewej strony
    b->Visible = true;
    Timer_pilka->Interval = 17;
}
//---------------------------------------------------------------------------
void __fastcall TPingPong::Timer_pilkaTimer(TObject *Sender)
{
        b->Left += x;
        b->Top += y;

        //odbij od gornej sciany
         if (b->Top-5 <= tlo->Top) y = -y;

        //odbij od dolnej sciany
         if (b->Top+b->Height+5 >= tlo->Height) y = -y;

         //skucie lewa strona
         if (b->Left <= pLewa->Left-pLewa->Width-10)
         {
            Timer_pilka->Enabled = false;
            b->Visible = false;
            Button1->Caption = "Wygral gracz prawy! Jeszcze raz gramy?";
            Button1->Visible = true;
            Button2->Visible = true;
            wygranaPrawaStrona++;
            Label1->Visible = true;   //ilosc odbic
            Label1->Caption = "Ilosc odbic: "+IntToStr(iloscOdbic)+" ";
            //iloscOdbic = 0;
            Label2->Visible = true;    //ilosc punktow lewy gracz
            Label2->Caption = "Ilosc punktow, gracz lewy: "+IntToStr(wygranaLewaStrona)+" ";
            Label3->Visible = true;    //ilosc punktow prawy gracz
            Label3->Caption = "Ilosc punktow, gracz prawy: "+IntToStr(wygranaPrawaStrona)+" ";
         }
        /*else if (b->Top > pLewa->Top-b->Width/2 && b->Top < pLewa->Top+pLewa->Height
        else if (b->Top > pLewa->Top-b->Width/2 && b->Top < pLewa->Top+pLewa->Height
                 && b->Left-b->Width < pLewa->Left-pLewa->Width)     //-pLewa->Width nowe         //odbicie od lewej paletki
                 {
                 if (x < 0) x = -x;
                 iloscOdbic++;
                }    */
        else if ((b->Top > pLewa->Top-b->Width/2 && b->Top < pLewa->Top+pLewa->Height
                && b->Left-b->Width < pLewa->Left-pLewa->Width) - (b->Top > pLewa->Top+pLewa->Height-160+65 && b->Top < pLewa->Top+pLewa->Height-75
                && b->Left-b->Width < pLewa->Left-pLewa->Width))    //-pLewa->Width nowe         //odbicie od lewej paletki
                {
                if (x < 0) x = -x;
                iloscOdbic++;
                sndPlaySound("snd/odbicie.wav",SND_ASYNC);
                 }
        /*else if (b->Top > pLewa->Top+pLewa->Height-160+95 && b->Top < pLewa->Top+pLewa->Height-160+55*/
        else if (b->Top > pLewa->Top-b->Width/2+pLewa->Height-160+65 && b->Top < pLewa->Top+pLewa->Height-75
                 && b->Left-b->Width < pLewa->Left-pLewa->Width)     //-pLewa->Width nowe         //odbicie od lewej paletki srodka
                {
                 if (x < 0) x = -x;
                 iloscOdbic++;
                 Timer_pilka->Interval--;
                 x++;
                 sndPlaySound("snd/odbicie.wav",SND_ASYNC);
                }
        //skucie prawa strona
        if (b->Left >= pPrawa->Left+pPrawa->Width+10)
         {
            Timer_pilka->Enabled = false;
            b->Visible = false;
            Button1->Caption = "Wygral gracz lewy! Jeszcze raz gramy?";
            Button1->Visible = true;
            Button2->Visible = true;
            wygranaLewaStrona++;
           Label1->Visible = true;
           Label1->Caption = "Ilosc odbic: "+IntToStr(iloscOdbic)+" ";
            //iloscOdbic = 0;
           Label2->Visible = true;    //ilosc punktow lewy gracz
           Label2->Caption = "Ilosc punktow, gracz lewy: "+IntToStr(wygranaLewaStrona)+" ";
           Label3->Visible = true;    //ilosc punktow prawy gracz
           Label3->Caption = "Ilosc punktow, gracz prawy: "+IntToStr(wygranaPrawaStrona)+" ";
         }
        /*else if (b->Top > pPrawa->Top-b->Width/2 && b->Top < pPrawa->Top+pPrawa->Height //odbicie od prawej paletki
        else if (b->Top > pPrawa->Top-b->Width/2 && b->Top < pPrawa->Top+pPrawa->Height //odbicie od prawej paletki
                 && b->Left+b->Width > pPrawa->Left)

                {
                if (x > 0) x = -x;
                iloscOdbic++;
                }     */
        else if ((b->Top > pPrawa->Top-b->Width/2 && b->Top < pPrawa->Top+pPrawa->Height //odbicie od prawej paletki
                && b->Left+b->Width > pPrawa->Left) - (b->Top > pPrawa->Top-b->Width/2+pPrawa->Height-160+65 && b->Top < pPrawa->Top+pPrawa->Height-75
                && b->Left+b->Width > pPrawa->Left))
                {
                if (x > 0) x = -x;
                iloscOdbic++;
                sndPlaySound("snd/odbicie.wav",SND_ASYNC);
                }
        else if (b->Top > pPrawa->Top-b->Width/2+pPrawa->Height-160+65 && b->Top < pPrawa->Top+pPrawa->Height-75
                && b->Left+b->Width > pPrawa->Left)     //-pLewa->Width nowe         //odbicie od prawej paletki srodka
                 {
                  if (x > 0) x = -x;
                  iloscOdbic++;
                  sndPlaySound("snd/odbicie.wav",SND_ASYNC);
                  Timer_pilka->Interval--;
                  x++;
                 }

        if (iloscOdbic >= 10 && iloscOdbic < 20)//przyspieszenie pilki
         {
          Timer_pilka->Interval = 15;
         }
        else if ( iloscOdbic >= 20)
         {
          Timer_pilka->Interval = 14;
         }


}
//---------------------------------------------------------------------------
