/* 
 * File:   Reversi.cpp
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

Cell::Cell() {
    this->cellX = -100;
    this->cellY = -100;
    this->livingCell = 0;
    this->owner = '.';
}

Cell::Cell(int valX, int valY) {

    this->cellX = valX;
    this->cellY = valY;
    this->livingCell = 0;
    this->owner = '.';
}

void Cell::operator=(const Cell& c) {
    this->cellX = c.cellX;
    this->cellY = c.cellY;
    this->livingCell = c.livingCell;
    this->owner = c.owner;
}

PlayableCells::PlayableCells() {

    x = -2, y = -2;
    eatDirections = -2;
    eatablePoints = -2;
}

void PlayableCells::operator=(const PlayableCells& p) {
    this->eatDirections = p.eatDirections;
    this->eatablePoints = p.eatablePoints;
    this->x = p.x;
    this->y = p.y;
}

Reversi::Reversi(int valX, int valY) : height(valX), widht(valY) {
    gameCells = new Cell[height * widht];
    playableCells = new PlayableCells[100];
    cellSize = (valX * valY);
    int m = 0, n = 0;
    for (int i = 0; i < cellSize; i++) {
        gameCells[i].setOwner('.');
        gameCells[i].setLivingCell(0);
        gameCells[i].setX(m);
        gameCells[i].setY(n);
        if (n == widht) {
            m++;
            n = 0;
        }
        n++;
    }
    gameCells[(height / 2 - 1)*(widht) + widht / 2 - 1].setOwner('O');
    gameCells[(height / 2 - 1)*(widht) + widht / 2 - 1].setLivingCell(1);
    gameCells[(height / 2 - 1)*(widht) + widht / 2 - 1].setX(valX / 2 - 1);
    gameCells[(height / 2 - 1)*(widht) + widht / 2 - 1].setY(valY / 2 - 1);

    gameCells[(height / 2 - 1)*(widht) + widht / 2 ].setOwner('X');
    gameCells[(height / 2 - 1)*(widht) + widht / 2 ].setLivingCell(2);
    gameCells[(height / 2 - 1)*(widht) + widht / 2 ].setX(valX / 2 - 1);
    gameCells[(height / 2 - 1)*(widht) + widht / 2 ].setY(valY / 2);

    gameCells[(height / 2)*(widht) + widht / 2 - 1].setOwner('X');
    gameCells[(height / 2)*(widht) + widht / 2 - 1].setLivingCell(2);
    gameCells[(height / 2)*(widht) + widht / 2 - 1].setX(valX / 2);
    gameCells[(height / 2)*(widht) + widht / 2 - 1].setY(valY / 2 - 1);

    gameCells[(height / 2)*(widht) + widht / 2 ].setOwner('O');
    gameCells[(height / 2)*(widht) + widht / 2 ].setLivingCell(1);
    gameCells[(height / 2)*(widht) + widht / 2 ].setX(valX / 2);
    gameCells[(height / 2)*(widht) + widht / 2 ].setY(valY / 2);
    scoreTable [0] = 2; //takes computer
    scoreTable [1] = 2; //takes user

    ++liveObj;
    gameNum = liveObj;
    moveNumber = 1;

}

Reversi::Reversi() {
    int valX = 8, valY = 8;
    height = valX;
    widht = valY;
    gameCells = new Cell[height * widht];
    playableCells = new PlayableCells[100];
    cellSize = (valX * valY);
    int m = 0, n = 0;
    for (int i = 0; i < cellSize; i++) {
        gameCells[i].setOwner('.');
        gameCells[i].setLivingCell(0);
        gameCells[i].setX(m);
        gameCells[i].setY(n);
        if (n == widht) {
            m++;
            n = 0;
        }
        n++;
    }
    gameCells[(height / 2 - 1)*(widht) + widht / 2 - 1].setOwner('O');
    gameCells[(height / 2 - 1)*(widht) + widht / 2 - 1].setLivingCell(1);
    gameCells[(height / 2 - 1)*(widht) + widht / 2 - 1].setX(valX / 2 - 1);
    gameCells[(height / 2 - 1)*(widht) + widht / 2 - 1].setY(valY / 2 - 1);

    gameCells[(height / 2 - 1)*(widht) + widht / 2 ].setOwner('X');
    gameCells[(height / 2 - 1)*(widht) + widht / 2 ].setLivingCell(2);
    gameCells[(height / 2 - 1)*(widht) + widht / 2 ].setX(valX / 2 - 1);
    gameCells[(height / 2 - 1)*(widht) + widht / 2 ].setY(valY / 2);

    gameCells[(height / 2)*(widht) + widht / 2 - 1].setOwner('X');
    gameCells[(height / 2)*(widht) + widht / 2 - 1].setLivingCell(2);
    gameCells[(height / 2)*(widht) + widht / 2 - 1].setX(valX / 2);
    gameCells[(height / 2)*(widht) + widht / 2 - 1].setY(valY / 2 - 1);

    gameCells[(height / 2)*(widht) + widht / 2 ].setOwner('O');
    gameCells[(height / 2)*(widht) + widht / 2 ].setLivingCell(1);
    gameCells[(height / 2)*(widht) + widht / 2 ].setX(valX / 2);
    gameCells[(height / 2)*(widht) + widht / 2 ].setY(valY / 2);
    scoreTable [0] = 2; //takes computer
    scoreTable [1] = 2; //takes user

    ++liveObj;
    gameNum = liveObj;
    moveNumber = 1;

}

Reversi::Reversi(const Reversi &r) {
    (*this) = r;
}

Reversi::~Reversi() {
    delete []gameCells;
    delete []playableCells;
    //Object is being deleted.
}

void Reversi::operator=(const Reversi &r) {
    cellSize = r.cellSize;
    height = r.height;
    widht = r.widht;
    liveObj = r.liveObj;
    gameNum = r.gameNum;
    scoreTable[0] = r.scoreTable[0];
    scoreTable[1] = r.scoreTable[1];
    delete [] gameCells;
    gameCells = new Cell[cellSize];
    for (int i = 0; i < cellSize; i++)
        gameCells[i] = r.gameCells[i];
    delete [] playableCells;
    playableCells = new PlayableCells[100];
    for (int i = 0; i < 100; i++)
        this->playableCells[i] = r.playableCells[i];
    moveNumber = r.moveNumber;
}

Reversi &Reversi::operator++() {//POST(ÖNCE )
    Reversi oldGame(height, widht);
    oldGame = (*this);
    playComputer();
    return oldGame;
}

Reversi &Reversi::operator++(int) {//PRE(SONRA)

    playComputer();
    return (*this);
}


int Cell::getX()const {

    return cellX;
}

int Cell::getY()const {

    return cellY;
}

void Cell::setX(int number) {

    cellX = number;
}

void Cell::setY(int number) {

    cellY = number;
}

char Cell::getOwner() {

    return owner;
}

void Cell::setOwner(char ch) {

    owner = ch;
}

int Cell::getLivingCell() {

    return livingCell;
}

void Cell::setLivingCell(int number) {

    livingCell = number;
}

int Reversi::getHeight() {

    return height;
}

int Reversi::getWidht() {

    return widht;
}

int Reversi::liveObj = 0;

int Reversi::getLiveGame() {

    return liveObj;
}

int Reversi::getGameNum() {

    return gameNum;
}

void Reversi::menu() {
    int lenghtX = 0;
    int lenghtY = 0;
    bool accepted = false;
    char input;
    cout << "Want you change to lenght?(İf want it enter Y) : ";
    cin>>input;
    if (input != 'Y')
        accepted = true;
    //this block run until entering acceptable number
    while (accepted == false) {
        cout << "Please enter to lenght of Height:" << endl;
        cin>>lenghtX;
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Please enter to lenght of Widht:" << endl;
        cin>>lenghtY;
        cin.clear();
        cin.ignore(10000, '\n');
        if ((lenghtX > 3) && (lenghtY > 3)) {
            accepted = true;
            height = lenghtX;
            widht = lenghtY;
            cellSize = (height * widht);
            delete [] gameCells;
            gameCells = new Cell[cellSize];
            int m = 0, n = 0;
            for (int i = 0; i < cellSize; i++) {
                gameCells[i].setOwner('.');
                gameCells[i].setLivingCell(0);
                gameCells[i].setX(m);
                gameCells[i].setY(n);
                if (n == widht) {
                    m++;
                    n = 0;
                }
                n++;
            }
            gameCells[(height / 2 - 1)*(widht) + widht / 2 - 1].setOwner('O');
            gameCells[(height / 2 - 1)*(widht) + widht / 2 - 1].setLivingCell(1);
            gameCells[(height / 2 - 1)*(widht) + widht / 2 - 1].setX(height / 2 - 1);
            gameCells[(height / 2 - 1)*(widht) + widht / 2 - 1].setY(widht / 2 - 1);

            gameCells[(height / 2 - 1)*(widht) + widht / 2 ].setOwner('X');
            gameCells[(height / 2 - 1)*(widht) + widht / 2 ].setLivingCell(2);
            gameCells[(height / 2 - 1)*(widht) + widht / 2 ].setX(height / 2 - 1);
            gameCells[(height / 2 - 1)*(widht) + widht / 2 ].setY(widht / 2);

            gameCells[(height / 2)*(widht) + widht / 2 - 1].setOwner('X');
            gameCells[(height / 2)*(widht) + widht / 2 - 1].setLivingCell(2);
            gameCells[(height / 2)*(widht) + widht / 2 - 1].setX(height / 2);
            gameCells[(height / 2)*(widht) + widht / 2 - 1].setY(widht / 2 - 1);

            gameCells[(height / 2)*(widht) + widht / 2 ].setOwner('O');
            gameCells[(height / 2)*(widht) + widht / 2 ].setLivingCell(1);
            gameCells[(height / 2)*(widht) + widht / 2 ].setX(height / 2);
            gameCells[(height / 2)*(widht) + widht / 2 ].setY(widht / 2);

        } else {

            cout << "Lenght x and y must be minimum 4  ." << endl;
        }
    }
}

void Reversi::drawBoard() {
    int sizeX, sizeY;
    sizeX = howManyDigit(height);
    sizeY = howManyDigit(widht);
    char* str = new char(10);
    for (int i = 0; i < sizeX; i++) {
        cout << " ";
    }
    int digit = 0;
    for (int i = 0; i < getWidht(); i++) {
        for (int k = 0; k <= (sizeY - howManyDigit(i)); k++)
            cout << " ";
        for (int j = 0; j < howManyDigit(i); j++) {
            std::sprintf(str, "%d", i);
            int num = ((int) (str[j] + 17));
            char ch = ((char) num);
            cout << ch;
        }
    }
    delete str;
    cout << endl;
    int m = 0, n = 0;
    for (int i = 0; i < getHeight(); i++) {
        cout.fill('0');
        cout.width(sizeX);
        cout << i + 1;
        for (int j = 0; j < getWidht(); j++) {
            //if ((i == gameCells[m].getX()) && (j == gameCells[m].getY())) {
            cout.fill(' ');
            cout.width(sizeY + 1);
            cout << gameCells[m].getOwner();
            m++;
            //} 
        }
        cout << endl;
    }
}

string Reversi::intToStr(int number) {
    char* strNum = new char(10);
    std::sprintf(strNum, "%d", number);
    int size = strlen(strNum);
    string str;
    int result = 0;
    for (int i = 0; i < size; i++) {

        int num = (((int) strNum[i]) + 17);
        char ch = ((char) num);
        str += ch;
    }
    return (str);

}

bool Reversi::findOfPlayablePoints(int player, int otherPlayer) {
    bool playable = false;
    int m = 0;
    for (int i = 0; i < 100; i++) {
        playableCells[i].x = -2, playableCells[i].y = -2;
        playableCells[i].eatDirections = -2;
        playableCells[i].eatablePoints = -2;
    }
    for (m = 0; m < cellSize; m++) {
        if ((gameCells[m].getLivingCell() == otherPlayer))
            checkCells(m, player, otherPlayer);
    }
    if (playableCells[0].eatablePoints > 0)
        playable = true;
    return playable;
}

bool Reversi::checkCells(int num, int player, int otherPlayer) {
    bool playable = false;
    if (gameCells[num].getX() >= 0 && gameCells[num].getX() <= height - 1 &&
        gameCells[num].getY() >= 0 && gameCells[num].getY() <= widht - 1) {
        if (gameCells[num].getY() > 0) {
            if (checkNeighbors(num, player, otherPlayer, 3, '0', '0', '+', '-', '+') == true)
                playable = true;
        }
        if (gameCells[num].getY() < widht - 1) {
            if (checkNeighbors(num, player, otherPlayer, 7, '0', '0', '-', '+', '-') == true)
                playable = true;
        }
        if (gameCells[num].getX() > 0 && gameCells[num].getX() < height - 1 &&
            gameCells[num].getY() > 0 && gameCells[num].getY() < widht - 1) {
            if (checkNeighbors(num, player, otherPlayer, 0, '-', '+', '-', '+', '-') == true)
                playable = true;
            if (checkNeighbors(num, player, otherPlayer, 1, '-', '+', '0', '0', '-') == true)
                playable = true;
            if (checkNeighbors(num, player, otherPlayer, 2, '-', '+', '+', '-', '-') == true)
                playable = true;
            if (checkNeighbors(num, player, otherPlayer, 4, '+', '-', '+', '-', '+') == true)
                playable = true;
            if (checkNeighbors(num, player, otherPlayer, 5, '+', '-', '0', '0', '+') == true)
                playable = true;
            if (checkNeighbors(num, player, otherPlayer, 6, '+', '-', '-', '+', '+') == true)
                playable = true;
        }
    }

    return playable;
}

bool Reversi::checkNeighbors(int num, int player, int otherPlayer, int eatDirection, char opX, char converseX, char opY, char converseY, char direction) {
    int result = 0;
    bool playable = false;
    int line = gameCells[num].getX(), col = gameCells[num].getY();
    int lineX = line, colY = col;
    int m = (operation(line, converseX) * getWidht()) + operation(col, converseY);
    if (m >= 0 && m < cellSize) {
        if (gameCells[m].getX() == operation(line, converseX) &&
            gameCells[m].getY() == operation(col, converseY) &&
            gameCells[m].getLivingCell() == 0) {
            playable = true;
        }
    }
    if (playable == true) {
        playable = false;
        int m = num;
        while (cellSize > m && m >= 0) {
            if (gameCells[m].getX() == line && gameCells[m].getY() == col) {
                if (gameCells[m].getLivingCell() == otherPlayer) {
                    result++;
                    line = operation(line, opX);
                    col = operation(col, opY);
                } else if (gameCells[m].getLivingCell() == player) {
                    playable = true;
                    break;
                } else {
                    playable = false;
                    result = 0;
                    break;
                }
            }
            m = operation(m, opX, 'x');
            m = operation(m, opY);
        }
    }
    if (result > 0 && playable == true) {
        for (int i = 0; i < 100; i++) {
            if (playableCells[i].eatablePoints == (-2)) {
                playableCells[i].x = operation(lineX, converseX);
                playableCells[i].y = operation(colY, converseY);
                playableCells[i].eatablePoints = result;
                playableCells[i].eatDirections = eatDirection;
                break;
            }
        }
    }
    return playable;
}

void Reversi::eatCells(int x, int y, int player, int otherPlayer) {
    //this block eats the neighbors of point(x,y) starting from the top left 
    //between left with clockwise.
    for (int m = 0; m < cellSize; m++) {
        if (gameCells[m].getX() == x && gameCells[m].getY() == y) {
            gameCells[m].setLivingCell(player);
            if (player == 2)
                gameCells[m].setOwner('X');
            if (player == 1)
                gameCells[m].setOwner('O');
            break;
        }
    }

    for (int i = 0; i < 100; i++) {
        if (playableCells[i].eatablePoints == -2)
            break;
        else if (playableCells[i].x == x && playableCells[i].y == y) {
            if (playableCells[i].eatDirections == 0)
                eatNeighbors(x, y, player, otherPlayer, '-', '-', '-');
            else if (playableCells[i].eatDirections == 1)
                eatNeighbors(x, y, player, otherPlayer, '-', '0', '-');
            else if (playableCells[i].eatDirections == 2)
                eatNeighbors(x, y, player, otherPlayer, '-', '+', '-');
            else if (playableCells[i].eatDirections == 3)
                eatNeighbors(x, y, player, otherPlayer, '0', '+', '+');
            else if (playableCells[i].eatDirections == 4)
                eatNeighbors(x, y, player, otherPlayer, '+', '+', '+');
            else if (playableCells[i].eatDirections == 5)
                eatNeighbors(x, y, player, otherPlayer, '+', '0', '+');
            else if (playableCells[i].eatDirections == 6)
                eatNeighbors(x, y, player, otherPlayer, '+', '-', '+');
            else if (playableCells[i].eatDirections == 7)
                eatNeighbors(x, y, player, otherPlayer, '0', '-', '-');
            if (player == 1) {
                scoreTable[0] += playableCells[i].eatablePoints;
                scoreTable[1] -= playableCells[i].eatablePoints;
            } else {
                scoreTable[1] += playableCells[i].eatablePoints;
                scoreTable[0] -= playableCells[i].eatablePoints;

            }
        }
    }
}

void Reversi::eatNeighbors(int x, int y, int player, int otherPlayer, char opX, char opY, char direction) {
    int line = operation(x, opX);
    int col = operation(y, opY);
    int m = (line * getWidht()) + col;
    while (cellSize > m && m >= 0) {
        if (gameCells[m].getX() == line && gameCells[m].getY() == col) {
            if (gameCells[m].getLivingCell() == otherPlayer) {
                gameCells[m].setLivingCell(player);
                if (player == 2)
                    gameCells[m].setOwner('X');
                if (player == 1)
                    gameCells[m].setOwner('O');
                line = operation(line, opX);
                col = operation(col, opY);
            } else if (gameCells[m].getLivingCell() == player) {
                break;
            }
        } else
            break;
        m = operation(m, opX, 'x');
        m = operation(m, opY);
    }
}

void Reversi::playPlayer() {
    int playX, playY;
    bool playCell = false;
    if (findOfPlayablePoints(2, 1) == true) {
        cout << "Playable cells are: ";
        for (int i = 0; i < 100; i++) {
            if (playableCells[i].eatablePoints == -2)
                break;
            else
                cout << playableCells[i].x + 1 << "x" << intToStr(playableCells[i].y) << " ";
        }
        cout << endl;
        while (playCell == false) {
            cout << "Please enter line coordinate: ";
            cin >> playX;
            cin.clear();
            cin.ignore(100000, '\n');
            cout << "Please enter column coordinate: ";
            string strY;
            cin>>strY;
            cin.clear();
            cin.ignore(100000, '\n');
            playY = strToInt(strY);
            for (int i = 0; i < 100; i++) {
                if (playableCells[i].eatablePoints == -2)
                    break;
                else if (playableCells[i].x == playX - 1 && playableCells[i].y == playY - 1) {
                    eatCells(playX - 1, playY - 1, 2, 1);
                    playCell = true;
                    break;
                }
            }
            if (playCell == false)
                cout << "These cell isn't playable! Choice another cell. ";
        }

    } else {

        cout << "No playable cell!Computer will play." << endl;
    }
    drawBoard();

}

void Reversi::playComputer() {
    int playX, playY, max = 0;
    bool playCell = false;
    if (findOfPlayablePoints(1, 2) == true) {
        for (int i = 0; i < 100; i++) {
            if (playableCells[i].eatablePoints == -2)
                break;
            else {
                if ((playableCells[i].x == 0 || playableCells[i].x == height - 1) &&
                    (playableCells[i].y == 0 || playableCells[i].y == widht) - 1) {
                    eatCells(playableCells[i].x, playableCells[i].y, 1, 2);
                    playCell = true;
                    break;
                } else if (playableCells[i].eatablePoints > max) {
                    max = playableCells[i].eatablePoints;
                    playX = playableCells[i].x;
                    playY = playableCells[i].y;
                } else if (playableCells[i].eatablePoints >= max &&
                           (playableCells[i].x == playableCells[i].y ||
                            (playableCells[i].x + playableCells[i].y) == 7)) {
                    max = playableCells[i].eatablePoints;
                    playX = playableCells[i].x;
                    playY = playableCells[i].y;
                }
            }
        }
        if (playCell == false) {
            eatCells(playX, playY, 1, 2);
        }
    } else {

        cout << "Cannot playable cell!User will play." << endl;
    }
    drawBoard();
}

void Reversi::playGame() {
    menu();
    drawBoard();
    string choice = "E";
    while (endGame() == false && (choice != "E" || choice != "e")) {
        playPlayer();
        cout << "Computer: " << scoreTable[0] << "  You: " << scoreTable[1] << endl;
        cout << "İf you want to quit game and continue another time, please " <<
                "enter E .For continue playing game, enter another key: " << endl;
        cin>>choice;
        cin.clear();
        cin.ignore(10000, '\n');
        if (endGame() == false && !(choice == "E" || choice == "e"))
            playComputer();

        else
            break;
        cout << "Computer: " << scoreTable[0] << "  You: " << scoreTable[1] << endl;
    }
}

bool Reversi::endGame() {
    if (findOfPlayablePoints(1, 2) == false && findOfPlayablePoints(2, 1) == false) {
        cout << "GAME OVER" << endl; //print to scree GAME OVER
        if (scoreTable[1] > scoreTable[0])
            cout << "Congrulation!You Wins" << endl;
        else if (scoreTable[0] > scoreTable[1])
            cout << "Computer Wins!" << endl;
        else if (scoreTable[0] == scoreTable[1])
            cout << "The Game Ended In A Draw!" << endl;
        return true;
    } else
        return false;
}

void Reversi::continueGame() {
    cout << "Continue game" << this->gameNum << "..." << endl;
    drawBoard();
    string choice = "E";
    while (endGame() == false && (choice != "E" || choice != "e")) {
        playPlayer();
        cout << "Computer: " << scoreTable[0] << "  You: " << scoreTable[1] << endl;
        cout << "İf you want to quit game and continue another time, please " <<
                "enter E .For continue playing game, enter another key: " << endl;
        cin>>choice;
        cin.clear();
        cin.ignore(10000, '\n');
        if (endGame() == false && !(choice == "E" || choice == "e"))
            playComputer();

        else
            break;
        cout << "Computer: " << scoreTable[0] << "  You: " << scoreTable[1] << endl;
    }
}

bool Reversi::compareReversi(Reversi &game)const {
    if (this->scoreTable[1] > this->scoreTable[0] && game.scoreTable[1] > game.scoreTable[0]) {
        if (this->scoreTable[1] >= game.scoreTable[1])
            return true;
        else
            return false;
    } else if (this->scoreTable[1] >= this->scoreTable[0])//other game's user is negative
        return true;
    else if (this->scoreTable[1] >= game.scoreTable[1])
        return true;
    else
        return false;

}

int Reversi::operation(int num, char op, char coordinate) {
    if (coordinate == 'x') {
        if (op == '+')
            num = num + getWidht();
        else
            if (op == '-')
            num = num - getWidht();
    } else {
        if (op == '+')
            ++num;
        else
            if (op == '-')
            --num;
    }
    return num;
}

int Reversi::operation(int num, char op) {
    if (op == '+')
        ++num;
    else
        if (op == '-')
        --num;
    return num;
}

int Reversi::strToInt(string str) {
    int result = 0;
    int size = strlen(str.c_str());
    char* cStr = new char(size);
    int num = 0;
    for (int i = size; i > 0; i--) {
        result += ((int) (str[i - 1] - 65)) * pow(10, num);
        num++;
    }
    return (result + 1);
}

int Reversi::howManyDigit(int number) {
    int digit = 1;
    while (number >= 10) {

        number = number / 10;
        digit++;
    }
    return digit;
}
