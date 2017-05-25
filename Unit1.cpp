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
- jak nacisnie na canvas to spradza lokacje nacisniecia i potem robi cos na wybranym polu, albo nic nie robi

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
    string correctMoves[9];

    Board(){
        //// JEZU DLACZEGO???
        this -> correctMoves[0] = "a1";
        this -> correctMoves[1] = "a2";
        this -> correctMoves[2] = "a3";
        this -> correctMoves[3] = "b1";
        this -> correctMoves[4] = "b2";
        this -> correctMoves[5] = "b3";
        this -> correctMoves[6] = "c1";
        this -> correctMoves[7] = "c2";
        this -> correctMoves[8] = "c3";
    
    }
    
    int get_int_move(string moveLocation){
        int moveInt;
        char moveLocationLetter = moveLocation[0];
        if ( moveLocationLetter == 'a' ) {
            moveInt = (int)moveLocation[1] - '0' -1;
        }
        else if ( moveLocationLetter == 'b'){
            moveInt = ((int)moveLocation[1] - '0') + 2;
        }
        else if ( moveLocationLetter == 'c'){
            moveInt = ((int)moveLocation[1] - '0') + 5;
        }

        return moveInt;
    }

    void set_move_on_board(int moveInt, char playersChar){
        boardData[ moveInt ] = playersChar;
    }

    public:


    void fill_board(){
        for (int i = 0; i < 9; i++ ){
            boardData[i] = '_';
        }
    }

    bool is_full_board(){
        bool fullBoard = true;
        for (int i = 0; i < 9; i++){
            if (boardData[i] == '_'){
                fullBoard = false;
                break;
            }
        }
        return fullBoard;
    }

    void draw_board(){
        cout << endl << "  1 2 3 " << endl;
        cout << "A ";
        for (int i = 0; i < 3; i++){
            cout << boardData[i] << " ";
        }
        cout << endl;
        cout << "B ";
        for (int i = 3; i < 6; i++){
            cout << boardData[i] << " ";
        }
        cout << endl;
        cout << "C ";
        for (int i = 6; i < 9; i++){
            cout << boardData[i] << " ";
        }
        cout << endl << endl;
    }

    // returns true if moveLocation is correct
    bool check_move(string moveLocation){
        bool correctMove = false;
        for (int i = 0; i < 9; i++){
            if ( moveLocation == correctMoves[i]){
                if ( boardData[i] == '_'){
                    correctMove = true;
                    break;
                }
            }
        }
        return correctMove;
    }

    void move(string moveLocation, Player p){
        char playersChar = p.get_players_char();
        int moveInt = get_int_move( moveLocation );
        set_move_on_board( moveInt, playersChar );
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
int playerNumber = 0;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner): TForm(Owner){

            p1.set_players_char( 'x' );
            char playersChar = p1.get_players_char();

            Label1 ->  Caption = playersChar;
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Button1Click(TObject *Sender)
{
        string nick = (Edit1 -> Text).c_str();
        if (playerNumber == 0){
                p1.set_nick( nick );
                p1.set_players_char( 'x' );
                playerNumber++;
                Label4 -> Caption = "Gracz 2";
        }
        else if (playerNumber == 1){
                p2.set_nick( nick );
                p1.set_players_char( 'O' );
                playerNumber++;
                delete Label2;
                delete Label3;
                delete Label4;
                //delete Edit1;
                //delete Button1;
                Button1 ->  Visible  = false;
                Edit1 -> Visible = false;
                delete Panel1;
        }
        //Label5 -> Caption  = nick.c_str();
        Edit1->Clear();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::putCharacter(TObject *Sender)
{
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
        // c1 = x 50-127 y = 208 293
        // c2 = x 138 224
        // c3 = x 234 310
        if (posX > 50 && posX < 127 && posY > 50 && posY < 116 ){
                Label5 -> Caption = posX;
                Label6 -> Caption = posY;
        }        
}
//---------------------------------------------------------------------------

