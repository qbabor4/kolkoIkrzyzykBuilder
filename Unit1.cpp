//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
using namespace std;

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#include <fstream>
#include <string>
#include <iostream>
TForm1 *Form1;

/* TODO
- dostac gracza, ktory bedzie mial teraz ruch
- pokazac dane gracza po prawej
- guzik, ktory pokazuje, wyniki ( po zakonczeniu rundy )
- guzik z nowa gra po zakonczneiu rundy
- zapisywanie wynikiow oddzielnych graczy do oddzielnych plikow
- pobieranie wynikow jak nick jest taki jak nazwa pliku ( pytanie czy pobrac )
- labele w miejscach na znak. jak kliknie na label to taka pozycja ( nie z canvas )
*/


class Player{
    string nick;
    char playersChar;
    int numOfwins; // = 0
    int numOfloses; // = 0
    int numOfDraws; // = 0

    public:
    Player(){
        this -> numOfwins = 0;
        this -> numOfloses = 0;
        this -> numOfDraws = 0;
    }

    void set_nick(string playerNick ){
        this->nick = playerNick;
    }

    int get_num_of_wins(){
        return numOfwins;
    }

    int get_num_of_loses(){
        return numOfloses;
    }

    int get_num_of_draws(){
        return numOfDraws;
    }

    char get_players_char(){
        return playersChar;
    }

    string get_nick(){
        return nick;
    }

    void set_players_char(char playersChar){
        this->playersChar = playersChar;
    }

    void round_won(){
        this->numOfwins++;
    }

    void round_lost(){
        this->numOfloses++;
    }

    void round_drawn(){
        this->numOfDraws++;
    }
};

class Board{
    char boardData[9];

    void set_move_on_board(int moveInt, char playersChar){
        boardData[ moveInt ] = playersChar;
    }

    void put_char_on_label(int moveInt, char playersChar){
        if (moveInt == 0){
                Form1 -> Label11 -> Caption = playersChar;
                Form1 -> Label11 -> Width = 89;
                Form1 -> Label11 -> Height = 81;
                Form1 -> Label11 -> Alignment = tlCenter;
                Form1 -> Label11 -> Alignment = taCenter;
                Form1 -> Label11 -> Visible = true;

                //Form1 -> Label11 -> Alignment = taCenter;
        }  else if ( moveInt == 1 ) {
                Form1 -> Label12 -> Caption = playersChar;
                Form1 -> Label12 -> Width = 89;
                Form1 -> Label12 -> Height = 81;
                Form1 -> Label12 -> Alignment = tlCenter;
                Form1 -> Label12 -> Alignment = taCenter;
                Form1 -> Label12 -> Visible = true;
        }  else if ( moveInt == 2 ) {
                Form1 -> Label13 -> Caption = playersChar;
                Form1 -> Label13 -> Width = 89;
                Form1 -> Label13 -> Height = 81;
                Form1 -> Label13 -> Alignment = tlCenter;
                Form1 -> Label13 -> Alignment = taCenter;
                Form1 -> Label13 -> Visible = true;
        }  else if ( moveInt == 3 ) {
                Form1 -> Label14 -> Caption = playersChar;
                Form1 -> Label14 -> Width = 89;
                Form1 -> Label14 -> Height = 74;
                Form1 -> Label14 -> Alignment = tlCenter;
                Form1 -> Label14 -> Alignment = taCenter;
                Form1 -> Label14 -> Visible = true;
        }  else if ( moveInt == 4 ) {
                Form1 -> Label15 -> Caption = playersChar;
                Form1 -> Label15 -> Width = 89;
                Form1 -> Label15 -> Height = 74;
                Form1 -> Label15 -> Alignment = tlCenter;
                Form1 -> Label15 -> Alignment = taCenter;
                Form1 -> Label15 -> Visible = true;
        }  else if ( moveInt == 5 ) {
                Form1 -> Label16 -> Caption = playersChar;
                Form1 -> Label16 -> Width = 89;
                Form1 -> Label16 -> Height = 74;
                Form1 -> Label16 -> Alignment = tlCenter;
                Form1 -> Label16 -> Alignment = taCenter;
                Form1 -> Label16 -> Visible = true;
        }  else if ( moveInt == 6 ) {
                Form1 -> Label17 -> Caption = playersChar;
                Form1 -> Label17 -> Width = 89;
                Form1 -> Label17 -> Height = 74;
                Form1 -> Label17 -> Alignment = tlCenter;
                Form1 -> Label17 -> Alignment = taCenter;
                Form1 -> Label17 -> Visible = true;
        }  else if ( moveInt == 7 ) {
                Form1 -> Label18 -> Caption = playersChar;
                Form1 -> Label18 -> Width = 89;
                Form1 -> Label18 -> Height = 74;
                Form1 -> Label18 -> Alignment = tlCenter;
                Form1 -> Label18 -> Alignment = taCenter;
                Form1 -> Label18 -> Visible = true;
        }  else if ( moveInt == 8 ) {
                Form1 -> Label19 -> Caption = playersChar;
                Form1 -> Label19 -> Width = 89;
                Form1 -> Label19 -> Height = 74;
                Form1 -> Label19 -> Alignment = tlCenter;
                Form1 -> Label19 -> Alignment = taCenter;
                Form1 -> Label19 -> Visible = true;
        } 
    }

    void reset_board_data(){
        for (int i = 0; i < 9; i++ ){
            boardData[i] = ' ';
        }
    }

    void reset_board_labels(){
        Form1 -> Label11 -> Visible = false;
        Form1 -> Label12 -> Visible = false;
        Form1 -> Label13 -> Visible = false;
        Form1 -> Label14 -> Visible = false;
        Form1 -> Label15 -> Visible = false;
        Form1 -> Label16 -> Visible = false;
        Form1 -> Label17 -> Visible = false;
        Form1 -> Label18 -> Visible = false;
        Form1 -> Label19 -> Visible = false;
    }

    public:
    void reset_board(){
        reset_board_data();
        reset_board_labels();
    }

    bool is_full_board(){
        bool fullBoard = true;
        for (int i = 0; i < 9; i++){
            if (boardData[i] == ' '){
                fullBoard = false;
                break;
            }
        }
        return fullBoard;
    }


    void move(int moveLocation, Player p){
        char playersChar = p.get_players_char();
        set_move_on_board( moveLocation, playersChar );
        put_char_on_label( moveLocation, playersChar );
    }

    bool is_win( Player p ){
        bool win = false;
        char playersChar = p.get_players_char();
        if ( (boardData[0] == playersChar && boardData[1] == playersChar && boardData[2] == playersChar) ||
             (boardData[3] == playersChar && boardData[4] == playersChar && boardData[5] == playersChar) ||
             (boardData[6] == playersChar && boardData[7] == playersChar && boardData[8] == playersChar) ||

             (boardData[0] == playersChar && boardData[3] == playersChar && boardData[6] == playersChar) ||
             (boardData[1] == playersChar && boardData[4] == playersChar && boardData[7] == playersChar) ||
             (boardData[2] == playersChar && boardData[5] == playersChar && boardData[8] == playersChar) ||

             (boardData[0] == playersChar && boardData[4] == playersChar && boardData[8] == playersChar) ||
             (boardData[2] == playersChar && boardData[4] == playersChar && boardData[6] == playersChar)
            )
            {
                win = true;
            }
        return win;
    }

};


Player p1;
Player p2;
Board b1;
int playerNumber = 0;
int moveNumber = 0;
bool win = false;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner): TForm(Owner){


            p1.set_players_char( 'X' );
            p2.set_players_char( 'O' );
            b1.reset_board();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button1Click(TObject *Sender)
{
        string nick = (Edit1 -> Text).c_str();
        if (playerNumber == 0){
                p1.set_nick( nick );

                playerNumber++;
                Label4 -> Caption = "Gracz 2";
        }
        else if (playerNumber == 1){
                p2.set_nick( nick );
                p2.set_players_char( 'O' );
                playerNumber++;
                delete Label2;
                delete Label3;
                delete Label4;
                //delete Edit1;
                //delete Button1;
                Button1 ->  Visible  = false;
                Edit1 -> Visible = false;
                delete Panel1;
                // tu poczatek gry
                Label20 -> Visible = true;
                Label21 -> Caption = p1.get_nick().c_str();
                Label21 -> Visible = true;

                Label22 -> Visible = true;
                Label23 -> Caption = p1.get_players_char();
                Label23 -> Visible = true;


        }
        //Label5 -> Caption  = nick.c_str();
        Edit1->Clear();
}
//---------------------------------------------------------------------------
int get_mouse_position(){
        POINT p;
        GetCursorPos(&p);
        int posX = p.x - Form1 -> Left;
        int posY = p.y - Form1 -> Top - 30;
        // a1 = x 50-127 y 50 - 116
        // a2 = x 138 224
        // a3 = x 234 310
        // b1 = x 50-127 y 127 - 198
        // b2 = x 138 224
        // b3 = x 234 310
        // c1 = x 50-127 y = 208 278
        // c2 = x 138 224
        // c3 = x 234 310
        int num;
        int add;
        int position;
        if (posX > 50 && posX < 127){
                num = 1;
        } else if ( posX > 138 && posX < 224 ){
                num = 2;
        } else if ( posX > 234 && posX < 310 ){
                num = 3;                                                      
        }
        if ( posY > 50 && posY < 116 && posX < 310 && posX > 50) {
                add = 0;
        } else if ( posY > 127 && posY < 198 && posX < 310 && posX > 50 ){
                add = 3;
        } else if ( posY > 208 && posY < 278 && posX < 310 && posX > 50 ){
                add = 6;
        }
        position = num + add -1;
        if (position > -1 && position < 9 ){
                //Form1 -> Label6 -> Caption = posY;
                return position;
        }

}


void __fastcall TForm1::put_character(TObject *Sender)
{
        int position = get_mouse_position();
        if (!win) {
                if (position > -1 && position < 9){

                        if (moveNumber % 2 == 0){
                        // gracz 1
                                b1.move( position , p1 );
                                Label21 -> Caption = p2.get_nick().c_str();
                                Label23 -> Caption = p2.get_players_char();

                                if( b1.is_win( p1 )){
                                        win = true;
                                        Label5 -> Visible = true;
                                        Label5 -> Caption =  p1.get_nick().c_str();
                                        p1.round_won();
                                        p2.round_lost();
                                        Label1 -> Visible = true;
                                        Label1 -> Caption = "Wygral gracz ";
                                        Button2 -> Visible = true;
                                        Button3 -> Visible = true;
                                        // zapisywanie do pliku

                                }

                        } else {
                        // gracz 2

                                b1.move( position , p2 );
                                Label21 -> Caption = p1.get_nick().c_str();
                                Label23 -> Caption = p1.get_players_char();
                                if( b1.is_win( p2 )){
                                        win = true;
                                        Label5 -> Visible = true;
                                        Label5 -> Caption = p2.get_nick().c_str();
                                        p2.round_won();
                                        p1.round_lost();
                                        Label1 -> Visible = true;
                                        Label1 -> Caption = "Wygral gracz ";
                                        Button2 -> Visible = true;
                                        Button3 -> Visible = true;
                                }
                        }

                        if (!win){
                                if (b1.is_full_board()){
                                        Label1 -> Visible = true;
                                        Label1 -> Caption = "Remis";
                                        p1.round_drawn();
                                        p2.round_drawn();
                                        Button2 -> Visible = true;
                                        Button3 -> Visible = true;
                                }
                        }


                        moveNumber++;
                }
        }

        
}

//---------------------------------------------------------------------------


void __fastcall TForm1::Button3Click(TObject *Sender)
{
        b1.reset_board();
        win = false;
        Label1 -> Visible = false;
        Label5 -> Visible = false;

        Label6 -> Visible = false;
        Label24 -> Visible = false;
        Label25 -> Visible = false;
        Label26 -> Visible = false;
        Label27 -> Visible = false;
        Label28 -> Visible = false;
        Label29 -> Visible = false;
        Label30 -> Visible = false;
        Label31 -> Visible = false;
        Label32 -> Visible = false;
        Label33 -> Visible = false;
        Label34 -> Visible = false;
        Label35 -> Visible = false;
        Label36 -> Visible = false;
        Button2 -> Visible = false;
        Button3 -> Visible = false;

}
//---------------------------------------------------------------------------



void __fastcall TForm1::Button2Click(TObject *Sender)
{
        Label6 -> Visible = true;
        Label6 -> Caption = p1.get_nick().c_str();
        Label24 -> Visible = true;
        Label25 -> Visible = true;
        Label26 -> Visible = true;
        Label27 -> Visible = true;
        Label27 -> Caption = p2.get_nick().c_str();
        Label28 -> Visible = true;
        Label29 -> Visible = true;
        Label30 -> Visible = true;
        Label31 -> Visible = true;
        Label31 -> Caption = p1.get_num_of_wins();
        Label32 -> Visible = true;
        Label32 -> Caption = p1.get_num_of_loses();
        Label33 -> Visible = true;
        Label33 -> Caption = p1.get_num_of_draws();
        Label34 -> Visible = true;
        Label34 -> Caption = p2.get_num_of_wins();
        Label35 -> Visible = true;
        Label35 -> Caption = p2.get_num_of_loses();
        Label36 -> Visible = true;
        Label36 -> Caption = p2.get_num_of_draws();
}
//---------------------------------------------------------------------------

