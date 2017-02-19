/* 
 * File:   main.cpp
 * Author: sahin
 *
 * Created on 18 Kasım 2015 Pazar, 21:58
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

/*
 * 
 */
int main(int argc, char** argv) {
    Reversi game1(8, 8), game2(20), game3, game4(17, 11), game5(20, 32);
    game1.playGame();
    cout << "2 times undo moves..." << endl;
    game1--;
    game1--;
    game1.continueGame();
    game1++;
    ++game1;
    cout << game1 << endl;
    cout << game1("C", 4) << endl;
    cout << game1["C4"] << endl;
    Cell c1(3, 2), c2(4, 5), c3(5, 6), c4(1, 5);
    cout << "game3..." << endl;
    cout << game3 << endl;
    cout << "Game 3 += c1 and c2..." << endl;
    game3 += c1;
    game3 += c2;
    cout << game3 << endl;
    if (game1.compareReversi(game3))
        cout << "game1 better than game3 for user" << endl;
    else
        cout << "game3 better than game1 for user" << endl;

    if (c3 < c4)
        cout << "c4 bigger than c3" << endl;
    else if (c3 > c4)
        cout << "c3 bigger than c4" << endl;
    else if (c3 == c4)
        cout << "c3 and c4 are equal" << endl;

    if (c1 <= c2)
        cout << "c1<=c2" << endl;
    else if (c1 >= c2)
        cout << "c1>=c2" << endl;
    if (c2 != c4)
        cout << "c2 != c4" << endl;

    return 0;
}

/*
 *
 */
