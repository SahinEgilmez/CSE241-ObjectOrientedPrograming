/* 
 * File:   main.cpp
 * Author: sahin
 *
 * Created on 10 Aralık 2015 Perşembe, 19:13
 */

#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <vector>
#include <cctype>
#include <fstream>
#include <sstream>
#include <cmath>
#include "Reversi.h"

using namespace std;
using namespace REVERSI_GTU;
/*
 * 
 */
int main(int argc, char** argv) {
    Reversi game1(8, 8), game2, game3(17, 11), game4(20, 32), game5(30,40);
    game1.playGame();
    game2.playGame();
    
    if (game1.compareReversi(game2))
        cout << "game1 better than game2 for user" << endl;
    else
        cout << "game3 better than game1 for user" << endl;
    
    cout << "display the game3..." << endl;
    cout<<game3;
    game1.continueGame();
    cout<<"Living Reversi game: "<<game5.getLiveGame()<<endl;

    return 0;
}



