/* HW4 ŞAHİN EĞİLMEZ 131044059 
 * File:   main.cpp
 * Author: Şahin Eğilmez
 *
 * Created on 08 Kasım 2015 Pazar, 21:58
 * 
 */

#include <cstring>
#include <vector>
#include <cctype>
#include <fstream>
#include <sstream>
#include "Reversi.h"

using namespace std;

int main(int argc, char** argv) {
    //TESTİNG REVERSİ GAMES
    int num = 0;
    Reversi game1(8, 8), game2(20), game3, game4(17, 11), game5(25, 32);
    game1.playGame();
    game2.playGame();
    game3.playGame();
    game4.playGame();
    game5.playGame();
    //FOR JUST TEST THE CONTİNUE GAME OF YOU WANTED
    cout << endl << "Please enter that want continue game's number(gameNum).";
    cin>>num;
    if (num == 1)
        game1.continueGame();
    if (num == 2)
        game2.continueGame();
    if (num == 3)
        game3.continueGame();
    if (num == 4)
        game4.continueGame();
    if (num == 5)
        game5.continueGame();
    //FOR JUST TEST THE READ ANY MOVES OF FILE
    game1.readMove(5);
    game2.readMove(1);
    game3.readMove(3);
    game4.readMove(2);
    game5.readMove(1);
    //LİVİNG OBJECT TEST
    cout << "Living object are : " << game5.getLiveGame() << endl;
    if (game5.compareReversi(game3))
        cout << "Game 5 better than game3 for user." << endl;
    else
        cout << "Game 3 better than game5 for user." << endl;
    
    return 0;
}

/*
 *
 */