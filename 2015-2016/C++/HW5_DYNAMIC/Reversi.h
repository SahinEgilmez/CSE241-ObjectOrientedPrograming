/* HW5 ŞAHİN EĞİLMEZ 131044059 
 * File:   Reversi.h
 * Author: Şahin Eğilmez
 *
 * Created on 18 Kasım 2015 Pazar, 21:58
 * 
 * NOT:İlk ödevde de aynı mantıkta yaptığımdan ve başlangıçda dizayn ederken 
 * böyle kullandığımdan dolayı x'i her bir satır için, y'yi her bir sütun için
 * kullandım.Yani program içinde x ve y lerin yeri normal matematiğe göre 
 * farklıdır.Ama kullanıcı bunu hissetmez.Buna göre okumanızı rica ederim.
 */


#ifndef REVERSI_H
#define	REVERSI_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <vector>
#include <cctype>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

class Cell {
public:
    Cell(int valX, int valY);
    Cell(); //constructor
    inline char getOwner(); //get cell owner
    inline void setOwner(char ch); //set the owner
    inline int getLivingCell(); //get owner with integer
    inline void setLivingCell(int number); //set owner with integer
    inline int getX()const; //get line number(x)
    inline int getY()const; //get column number(y)
    inline void setX(int number); //set line number(x)
    inline void setY(int number); //set column number(y)
    bool operator<(const Cell &cell);
    bool operator>(const Cell &cell);
    bool operator<=(const Cell &cell);
    bool operator>=(const Cell &cell);
    bool operator==(const Cell &cell);
    bool operator!=(const Cell &cell);
    friend ostream &operator<<(ostream &output, const Cell &cell);
    friend istream &operator>>(istream &input, Cell &cell);

private:
    char owner;
    int cellX;
    int cellY;
    int livingCell;
};

class PlayableCells {
public:
    PlayableCells();
    int x;
    int y;
    int eatablePoints;
    int eatDirections;
};

class Reversi {//this class for the Reversi game
public:
    Reversi(int valX, int valY); //constructors performs (x,y) board
    Reversi(int valX); //constructors performs (x.8) board
    Reversi(); //constructors performs (8,8) board
    void playGame(); //playing game.
    void continueGame(); //continue game that paused
    inline int getHeight(); //get board height
    inline int getWidht(); //get board widht
    inline static int getLiveGame(); //get live game(object) at the moment
    inline int getGameNum(); //get special game number
    bool compareReversi(Reversi game); //comapring another game.It returns true 
    //is the first game is better for the user, otherwise it returns false.
    void readMove(int moveNum); //print to screen entered move
    void operator=(const Reversi &r);
    Reversi &operator++(); //pre
    Reversi &operator++(int); //post
    Reversi &operator--(); //pre
    Reversi &operator--(int); //post
    Cell operator[](string coordinate);
    Cell operator()(string column, int line);
    Reversi &operator+=(Cell &cell);
    friend ostream &operator<<(ostream &output, Reversi &game);
private:
    void menu(); //this functions get table size from player.
    void drawBoard(); //this function draw the table to terminal. 
    void writeFile(int player, int x, int y); //write to file all moves
    bool findOfPlayablePoints(int player, int otherPlayer); //momentarily
    //find of playable all points
    bool checkCells(int x, int y, int player, int otherPlayer); //checks 
    //all neighbors with checkNeighbors function
    bool checkNeighbors(int x, int y, int player, int otherPlayer, int eatDirection,
            char opX, char converseX, char opY, char converseY, char direction); //checks 
    //all neighbors 
    void eatCells(int x, int y, int player, int otherPlayer); //eats all neighbors
    //of Cell with eatNeighbors function
    void eatNeighbors(int x, int y, int player, int otherPlayer, char opX,
            char opY, char direction);
    void playPlayer(); //This function performs player playing.
    void playComputer(); //This function performs computer thinking and playing .
    bool endGame(); //this function check the end of game.
    int howManyDigit(int number); //find to number's digit(for another function)
    int strToInt(string str);
    string intToStr(int number);
    int operation(int num, char op); //it does ++,-- or nothing(0) by char op
    int height; //board height
    int widht; //board widht value
    vector< vector<Cell> > gameCells; //take the living cell(don't take died Cell)
    static int liveObj; //living object number
    int gameNum; //special number for game.Create by liveObj
    int moveNumber; //take the move number each game
    int scoreTable[2]; //take the scores.
    vector<PlayableCells> playableCells; //momentarly take playable Cells.
    //Cells is varied each time so vector size is small
};

Reversi &Reversi::operator++() {
    playComputer();
    return (*this);
}

Reversi &Reversi::operator++(int) {
    Reversi oldGame(this->height, this->widht);
    oldGame = (*this);
    playComputer();
    return oldGame;
}

void Reversi::operator=(const Reversi &r) {
    height = r.height;
    widht = r.widht;
    liveObj = r.liveObj;
    gameNum = r.gameNum;
    scoreTable[0] = r.scoreTable[0];
    scoreTable[1] = r.scoreTable[1];
    gameCells = r.gameCells;
    playableCells = r.playableCells;
    moveNumber = r.moveNumber;
}

Reversi &Reversi::operator--() {
    char* temp = new char(5);
    strcpy(temp, ".txt");
    char* str = new char(100);
    std::sprintf(str, "%d", getGameNum());
    strcat(str, temp);
    ifstream file(str, ios::app);
    ofstream tempFile("temp.txt", ios::out);
    vector<vector < string> > gameData;
    string line;
    while (getline(file, line)) {
        if (!(line.empty())) {
            string data;
            stringstream stream(line);
            vector<string> datas;
            while (getline(stream, data, ' ')) {
                datas.push_back(data);
            }
            gameData.push_back(datas);
            if (!(file.eof())) {
                tempFile << endl << line;

            }
        }
    }
    remove(str);
    rename("temp.txt", str);
    int lastLine = gameData.size() - 1;
    bool first = true;
    for (int i = 2; i < gameData[lastLine].size(); i++) {
        string move = gameData[lastLine][i];
        string strX, strY;
        stringstream stream(move);
        getline(stream, strX, '*');
        getline(stream, strY, ' ');
        int xNum = atoi(strX.c_str());
        int yNum = atoi(strY.c_str());
        for (int m = 0; m < gameCells.size(); m++) {
            for (int n = 0; n < gameCells[m].size(); n++) {
                if (xNum == gameCells[m][n].getX() && yNum == gameCells[m][n].getY()) {
                    if (i == 2) {
                        if (gameCells[m].size() == 1) {
                            gameCells.erase(gameCells.begin() + m);
                            first = false;
                        } else {
                            gameCells[m].erase(gameCells[m].begin() + (n));
                            first = false;
                        }
                    } else {
                        if (gameData[lastLine][1] == "U") {
                            gameCells[m][n].setLivingCell(1);
                            gameCells[m][n].setOwner('O');
                        } else if (gameData[lastLine][1] == "C") {

                            gameCells[m][n].setLivingCell(2);
                            gameCells[m][n].setOwner('X');
                        }
                    }
                }
            }
        }
    }
    file.close();
    tempFile.close();
    delete temp, str;
    gameData.clear();
    gameData.resize(0);
    return (*this);
}

Reversi &Reversi::operator--(int) {
    Reversi newReversi = (*this);
    char* temp = new char(5);
    strcpy(temp, ".txt");
    char* str = new char(100);
    std::sprintf(str, "%d", getGameNum());
    strcat(str, temp);
    ifstream file(str, ios::app);
    ofstream tempFile("temp.txt", ios::out);
    vector<vector < string> > gameData;
    string line;
    while (getline(file, line)) {
        if (!(line.empty())) {
            string data;
            stringstream stream(line);
            vector<string> datas;
            while (getline(stream, data, ' ')) {
                datas.push_back(data);
            }
            gameData.push_back(datas);
            if (!(file.eof())) {
                tempFile << endl << line;

            }
        }
    }
    remove(str);
    rename("temp.txt", str);
    int lastLine = gameData.size() - 1;
    bool first = true;
    for (int i = 2; i < gameData[lastLine].size(); i++) {
        string move = gameData[lastLine][i];
        string strX, strY;
        stringstream stream(move);
        getline(stream, strX, '*');
        getline(stream, strY, ' ');
        int xNum = atoi(strX.c_str());
        int yNum = atoi(strY.c_str());
        for (int m = 0; m < gameCells.size(); m++) {
            for (int n = 0; n < gameCells[m].size(); n++) {
                if (xNum == gameCells[m][n].getX() && yNum == gameCells[m][n].getY()) {
                    if (i == 2) {

                        if (gameCells[m].size() == 1) {
                            gameCells.erase(gameCells.begin());
                            first = false;
                        } else {
                            gameCells[m].erase(gameCells[m].begin() + (n));
                            first = false;
                        }
                    } else {
                        if (gameData[lastLine][1] == "U") {
                            gameCells[m][n].setLivingCell(1);
                            gameCells[m][n].setOwner('O');
                        } else if (gameData[lastLine][1] == "C") {

                            gameCells[m][n].setLivingCell(2);
                            gameCells[m][n].setOwner('X');
                        }
                    }
                }
            }
        }
    }
    file.close();
    tempFile.close();
    gameData.clear();
    gameData.resize(0);
    delete temp, str;
    return newReversi;
}

Cell Reversi::operator[](string coordinate) {
    char* column = new char(coordinate.size());
    string strCol;
    char* line = new char(coordinate.size());
    int j = 0, k = 0;
    for (int i = 0; i < coordinate.size(); i++) {
        if (((int) coordinate[i]) >= 65 && ((int) coordinate[i]) <= 74) {
            strCol[j] = coordinate[i];
            j++;
        } else if (((int) coordinate[i]) >= 48 && ((int) coordinate[i]) <= 57) {
            line[k] = coordinate[i];
            k++;
        }
    }
    for (int m = 0; m < gameCells.size(); m++) {
        for (int n = 0; n < gameCells[m].size(); n++) {
            if (gameCells[m][n].getX() == atoi(line) && gameCells[m][n].getY() == strToInt(strCol)) {
                return gameCells[m][n];
            }
        }
    }

    return Cell(-1000, -1000);
}

Cell Reversi::operator()(string column, int line) {
    for (int m = 0; m < gameCells.size(); m++) {
        for (int n = 0; n < gameCells[m].size(); n++) {
            if (gameCells[m][n].getX() == line && gameCells[m][n].getY() == strToInt(column)) {
                return gameCells[m][n];
            }
        }
    }
    return Cell(-1000, -1000);

}

Reversi &Reversi::operator+=(Cell& cell) {
    bool playCell = false;
    if (findOfPlayablePoints(2, 1) == true) {
        for (int i = 0; i < playableCells.size(); i++) {
            if (playableCells[i].x == cell.getX() && playableCells[i].y == cell.getY()) {
                eatCells(cell.getX(), cell.getY(), 2, 1);
                playCell = true;
                break;
            }
        }
        if (playCell == false)
            cout << "These cell object isn't playable! " << endl;
    } else {

        cout << "These cell object isn't playable! " << endl;
    }
    drawBoard();
}

ostream &operator<<(ostream &output, Reversi &game) {

    game.drawBoard();
    output << "Computer: " << game.scoreTable[0] << "  User: " << game.scoreTable[1] << endl;
}

bool Cell::operator<(const Cell & cell) {
    if (this->getX() == cell.getX()) {
        if (this->getY() < cell.getY())
            return true;
        else
            return false;
    } else if (this->getX() < cell.getX())
        return true;

    else
        return false;
}

bool Cell::operator>(const Cell & cell) {
    if (this->getX() == cell.getX()) {
        if (this->getY() > cell.getY())
            return true;
        else
            return false;
    } else if (this->getX() > cell.getX())
        return true;

    else
        return false;
}

bool Cell::operator<=(const Cell & cell) {
    if (this->getX() == cell.getX()) {
        if (this->getY() <= cell.getY())
            return true;
        else
            return false;
    } else if (this->getX() <= cell.getX())
        return true;

    else
        return false;
}

bool Cell::operator>=(const Cell & cell) {
    if (this->getX() == cell.getX()) {
        if (this->getY() >= cell.getY())
            return true;
        else
            return false;
    } else if (this->getX() >= cell.getX())
        return true;

    else
        return false;
}

bool Cell::operator==(const Cell & cell) {
    if (this->getX() == cell.getX()) {
        if (this->getY() == cell.getY())
            return true;
        else
            return false;
    } else
        return false;
}

bool Cell::operator!=(const Cell & cell) {
    if (this->getX() == cell.getX()) {
        if (this->getY() == cell.getY())
            return false;
        else
            return true;
    } else
        return true;
}

ostream &operator<<(ostream &output, const Cell & cell) {

    output << "Line(x) : " << cell.getX() << " Column(y) : " << cell.getY();
    return output;
}

istream &operator>>(istream &input, Cell & cell) {

    int numX, numY;
    input >> numX>>numY;
    cell.setX(numX);
    cell.setY(numY);
    return input;
}

Cell::Cell() {
}

Cell::Cell(int valX, int valY) {

    this->cellX = valX;
    this->cellY = valY;
    this->livingCell = 0;
    this->owner = '.';
}

PlayableCells::PlayableCells() {

    x = -2, y = -2;
    eatDirections = -2;
    eatablePoints = -2;
}

inline int Cell::getX()const {

    return cellX;
}

inline int Cell::getY()const {

    return cellY;
}

inline void Cell::setX(int number) {

    cellX = number;
}

inline void Cell::setY(int number) {

    cellY = number;
}

inline char Cell::getOwner() {

    return owner;
}

inline void Cell::setOwner(char ch) {

    owner = ch;
}

inline int Cell::getLivingCell() {

    return livingCell;
}

inline void Cell::setLivingCell(int number) {

    livingCell = number;
}

Reversi::Reversi(int valX, int valY) : height(valX), widht(valY) {
    gameCells.resize(2);
    for (int i = 0; i < 2; ++i) {

        gameCells[i].resize(2);
    }
    gameCells[0][0].setOwner('O');
    gameCells[0][0].setLivingCell(1);
    gameCells[0][0].setX(valX / 2 - 1);
    gameCells[0][0].setY(valY / 2 - 1);

    gameCells[0][1].setOwner('X');
    gameCells[0][1].setLivingCell(2);
    gameCells[0][1].setX(valX / 2 - 1);
    gameCells[0][1].setY(valY / 2);

    gameCells[1][0].setOwner('X');
    gameCells[1][0].setLivingCell(2);
    gameCells[1][0].setX(valX / 2);
    gameCells[1][0].setY(valY / 2 - 1);

    gameCells[1][1].setOwner('O');
    gameCells[1][1].setLivingCell(1);
    gameCells[1][1].setX(valX / 2);
    gameCells[1][1].setY(valY / 2);
    scoreTable [0] = 2; //takes computer
    scoreTable [1] = 2; //takes user

    ++liveObj;
    gameNum = liveObj;
    moveNumber = 1;

}

Reversi::Reversi(int valX) : height(valX) {
    gameCells.resize(2);
    for (int i = 0; i < 2; ++i) {

        gameCells[i].resize(2);
    }
    gameCells[0][0].setOwner('O');
    gameCells[0][0].setLivingCell(1);
    gameCells[0][0].setX(valX / 2 - 1);
    gameCells[0][0].setY(8 / 2 - 1);

    gameCells[0][1].setOwner('X');
    gameCells[0][1].setLivingCell(2);
    gameCells[0][1].setX(valX / 2 - 1);
    gameCells[0][1].setY(8 / 2);

    gameCells[1][0].setOwner('X');
    gameCells[1][0].setLivingCell(2);
    gameCells[1][0].setX(valX / 2);
    gameCells[1][0].setY(8 / 2 - 1);

    gameCells[1][1].setOwner('O');
    gameCells[1][1].setLivingCell(1);
    gameCells[1][1].setX(valX / 2);
    gameCells[1][1].setY(8 / 2);
    scoreTable [0] = 2; //takes computer
    scoreTable [1] = 2; //takes user

    widht = 8;
    ++liveObj;
    gameNum = liveObj;
    moveNumber = 1;
}

Reversi::Reversi() {
    gameCells.resize(2);
    for (int i = 0; i < 2; ++i) {

        gameCells[i].resize(2);
    }
    gameCells[0][0].setOwner('O');
    gameCells[0][0].setLivingCell(1);
    gameCells[0][0].setX(8 / 2 - 1);
    gameCells[0][0].setY(8 / 2 - 1);

    gameCells[0][1].setOwner('X');
    gameCells[0][1].setLivingCell(2);
    gameCells[0][1].setX(8 / 2 - 1);
    gameCells[0][1].setY(8 / 2);

    gameCells[1][0].setOwner('X');
    gameCells[1][0].setLivingCell(2);
    gameCells[1][0].setX(8 / 2);
    gameCells[1][0].setY(8 / 2 - 1);

    gameCells[1][1].setOwner('O');
    gameCells[1][1].setLivingCell(1);
    gameCells[1][1].setX(8 / 2);
    gameCells[1][1].setY(8 / 2);
    scoreTable [0] = 2; //takes computer
    scoreTable [1] = 2; //takes user

    height = 8;
    widht = 8;
    ++liveObj;
    gameNum = liveObj;
    moveNumber = 1;
}

inline int Reversi::getHeight() {

    return height;
}

inline int Reversi::getWidht() {

    return widht;
}

int Reversi::liveObj = 0;

inline int Reversi::getLiveGame() {

    return liveObj;
}

inline int Reversi::getGameNum() {

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
            gameCells[0][0].setOwner('O');
            gameCells[0][0].setLivingCell(1);
            gameCells[0][0].setX(height / 2 - 1);
            gameCells[0][0].setY(widht / 2 - 1);

            gameCells[0][1].setOwner('X');
            gameCells[0][1].setLivingCell(2);
            gameCells[0][1].setX(height / 2 - 1);
            gameCells[0][1].setY(widht / 2);

            gameCells[1][0].setOwner('X');
            gameCells[1][0].setLivingCell(2);
            gameCells[1][0].setX(height / 2);
            gameCells[1][0].setY(widht / 2 - 1);

            gameCells[1][1].setOwner('O');
            gameCells[1][1].setLivingCell(1);
            gameCells[1][1].setX(height / 2);
            gameCells[1][1].setY(widht / 2);

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
            if ((i == gameCells[m][n].getX()) && (j == gameCells[m][n].getY())) {
                cout.fill(' ');
                cout.width(sizeY + 1);
                cout << gameCells[m][n].getOwner();
                n++;
                if (gameCells[m].size() == n) {
                    n = 0;
                    if (gameCells.size() > m + 1)
                        m++;
                }
            } else {

                cout.fill(' ');
                cout.width(sizeY + 1);
                cout << ".";
            }
        }
        cout << endl;
    }
}

bool Reversi::findOfPlayablePoints(int player, int otherPlayer) {
    bool playable = false;
    int m = 0, n = 0;
    int i, j;
    playableCells.clear();
    playableCells.resize(0);
    for (m = 0; m < gameCells.size(); m++) {
        for (n = 0; n < gameCells[m].size(); n++) {
            checkCells(m, n, player, otherPlayer);
        }
    }

    if (playableCells.size() > 0)
        playable = true;
    return playable;
}

bool Reversi::checkCells(int x, int y, int player, int otherPlayer) {
    bool playable = false;
    if (gameCells[x][y].getX() >= 0 && gameCells[x][y].getX() <= height - 1 &&
        gameCells[x][y].getY() >= 0 && gameCells[x][y].getY() <= widht - 1) {
        if (gameCells[x][y].getY() > 0) {
            if (checkNeighbors(x, y, player, otherPlayer, 3, '0', '0', '+', '-', '+') == true)
                playable = true;
        }
        if (gameCells[x][y].getY() < widht - 1) {
            if (checkNeighbors(x, y, player, otherPlayer, 7, '0', '0', '-', '+', '-') == true)
                playable = true;
        }
        if (gameCells[x][y].getX() > 0 && gameCells[x][y].getX() < height - 1 &&
            gameCells[x][y].getY() > 0 && gameCells[x][y].getY() < widht - 1) {
            if (checkNeighbors(x, y, player, otherPlayer, 0, '-', '+', '-', '+', '-') == true)
                playable = true;
            if (checkNeighbors(x, y, player, otherPlayer, 1, '-', '+', '0', '0', '-') == true)
                playable = true;
            if (checkNeighbors(x, y, player, otherPlayer, 2, '-', '+', '+', '-', '-') == true)
                playable = true;
            if (checkNeighbors(x, y, player, otherPlayer, 4, '+', '-', '+', '-', '+') == true)
                playable = true;
            if (checkNeighbors(x, y, player, otherPlayer, 5, '+', '-', '0', '0', '+') == true)
                playable = true;

            if (checkNeighbors(x, y, player, otherPlayer, 6, '+', '-', '-', '+', '+') == true)
                playable = true;
        }
    }

    return playable;
}

bool Reversi::checkNeighbors(int x, int y, int player, int otherPlayer, int eatDirection, char opX, char converseX, char opY, char converseY, char direction) {
    int result = 0;
    bool playable = false, exitLoop = false;
    int line = gameCells[x][y].getX(), col = gameCells[x][y].getY();
    int lineX = line, colY = col;

    if ((gameCells.size() > x + 1 && direction == '-') || (x > 0 && direction == '+')) {
        for (int n = 0; gameCells[operation(x, converseX)].size() > n; n++) {
            if (operation(line, converseX) == gameCells[operation(x, converseX)][n].getX() && operation(col, converseY) == gameCells[operation(x, converseX)][n].getY()) {
                playable = false;
                break;
            } else
                playable = true;
        }
    } else
        playable = true;

    if (playable == true && direction == '-') {
        for (int m = x; m >= 0; m--) {
            if (opY == '-') {
                for (int n = y; n >= 0; n--) {
                    if (gameCells[m][n].getX() == line && gameCells[m][n].getY() == col) {
                        if (gameCells[m ][n ].getLivingCell() == otherPlayer) {
                            result++;
                            line = operation(line, opX);
                            col = operation(col, opY);
                        } else if (gameCells[m ][n ].getLivingCell() == player) {
                            exitLoop = true;
                            break;
                        }
                    }
                }
            } else {
                for (int n = 0; gameCells[m].size() > n; n++) {
                    if (gameCells[m][n].getX() == line && gameCells[m][n].getY() == col) {
                        if (gameCells[m ][n ].getLivingCell() == otherPlayer) {
                            result++;
                            line = operation(line, opX);
                            col = operation(col, opY);
                        } else if (gameCells[m ][n ].getLivingCell() == player) {
                            exitLoop = true;
                            break;
                        }
                    }
                }
            }
            if (exitLoop == true)
                break;
        }
    }

    if (playable == true && direction == '+') {
        for (int m = x; m < gameCells.size(); m++) {
            for (int n = 0; gameCells[m].size() > n; n++) {
                if (gameCells[m][n].getX() == line && gameCells[m][n].getY() == col) {
                    if (gameCells[m ][n ].getLivingCell() == otherPlayer) {
                        result++;
                        playable = false;
                    } else if (gameCells[m ][n ].getLivingCell() == player) {
                        exitLoop = true;
                        break;
                    }
                    if (playable == false && opX == '0') {
                        line = operation(line, opX);
                        col = operation(col, opY);
                        playable = true;
                    }
                }
            }
            if (exitLoop == true)
                break;
            if (opX != '0' && playable == false) {
                line = operation(line, opX);
                col = operation(col, opY);
                playable = true;
            } else
                break;
        }
    }

    if (result > 0 && exitLoop == true && playable == true) {

        PlayableCells newPoint;
        newPoint.x = operation(lineX, converseX);
        newPoint.y = operation(colY, converseY);
        newPoint.eatablePoints = result;
        newPoint.eatDirections = eatDirection;
        playableCells.push_back(newPoint);
    }
    return playable;
}

void Reversi::eatCells(int x, int y, int player, int otherPlayer) {
    //this block eats the neighbors of point(x,y) starting from the top left 
    //between left with clockwise.
    Cell newCell;
    newCell.setX(x);
    newCell.setY(y);
    newCell.setLivingCell(player);
    if (player == 1) {
        newCell.setOwner('O');
        scoreTable[0]++;
    } else {
        newCell.setOwner('X');
        scoreTable[1]++;
    }
    writeFile(player, x, y);
    for (int m = 0; m < gameCells.size(); m++) {
        if (gameCells[m][0].getX() == x) {
            if (gameCells[m][0].getY() > y) {
                gameCells[m].insert(gameCells[m].begin(), newCell);
                break;
            } else if (gameCells[m][gameCells[m].size() - 1].getY() < y) {
                gameCells[m].push_back(newCell);
                break;
            } else {
                for (int n = 0; n < gameCells[m].size(); n++) {
                    if (gameCells[m][n].getY() < y && gameCells[m][n + 1].getY() > y) {
                        gameCells[m].insert(gameCells[m].begin() + (n + 1), newCell);
                        break;
                    }
                }
            }
            break;
        } else if (gameCells[0][0].getX() > x) {
            vector<Cell> newVec;
            newVec.push_back(newCell);
            gameCells.insert(gameCells.begin(), newVec);
            break;
        } else if (gameCells[gameCells.size() - 1][0].getX() < x) {
            vector<Cell> newVec;
            newVec.push_back(newCell);
            gameCells.push_back(newVec);
            break;
        }
    }
    for (int i = 0; i < playableCells.size(); i++) {
        if (playableCells[i].x == x && playableCells[i].y == y) {
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

int Reversi::operation(int num, char op) {
    if (op == '+')
        ++num;
    else

        if (op == '-')
        --num;
    return num;
}

void Reversi::eatNeighbors(int x, int y, int player, int otherPlayer, char opX, char opY, char direction) {
    x = operation(x, opX);
    y = operation(y, opY);
    if (direction == '-') {
        for (int m = gameCells.size() - 1; m >= 0; m--) {
            for (int n = gameCells[m].size() - 1; n >= 0; n--) {
                if (gameCells[m][n].getX() == x && gameCells[m][n].getY() == y
                    && gameCells[m][n].getLivingCell() == otherPlayer) {
                    gameCells[m][n].setLivingCell(player);
                    if (player == 2)
                        gameCells[m][n].setOwner('X');
                    else
                        gameCells[m][n].setOwner('O');
                    writeFile(0, x, y);
                    x = operation(x, opX);
                    y = operation(y, opY);
                }
            }
        }
    } else if (direction == '+') {
        for (int m = 0; m < gameCells.size(); m++) {
            for (int n = 0; n < gameCells[m].size(); n++) {
                if (gameCells[m][n].getX() == x && gameCells[m][n].getY() == y
                    && gameCells[m][n].getLivingCell() == otherPlayer) {
                    gameCells[m][n].setLivingCell(player);
                    if (player == 2)
                        gameCells[m][n].setOwner('X');

                    else
                        gameCells[m][n].setOwner('O');
                    writeFile(0, x, y);
                    x = operation(x, opX);
                    y = operation(y, opY);
                }
            }
        }
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

int Reversi::strToInt(string str) {
    int result = 0;
    int size = strlen(str.c_str());
    char* cStr = new char(size);
    int num = 0;
    for (int i = size; i > 0; i--) {

        result += ((int) (str[i - 1] - 65)) * pow(10, num);
        //result += ((int) str[i] - 64)+ digit;
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

void Reversi::playPlayer() {
    int playX, playY;
    bool playCell = false;
    if (findOfPlayablePoints(2, 1) == true) {
        cout << "Playable cells are: ";
        for (int i = 0; i < playableCells.size(); i++) {
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
            for (int i = 0; i < playableCells.size(); i++) {
                if (playableCells[i].x == playX - 1 && playableCells[i].y == playY - 1) {
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
        for (int i = 0; i < playableCells.size(); i++) {
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

void Reversi::writeFile(int player, int x, int y) {
    char* temp = new char(5);
    strcpy(temp, ".txt");
    char* str = new char(100);
    std::sprintf(str, "%d", getGameNum());
    strcat(str, temp);
    if (moveNumber == 1)
        ofstream file(str, ios::out);
    ofstream file(str, ios::app);
    if (player == 2) {
        file << "\n" << moveNumber << " U ";
        moveNumber++;
    } else if (player == 1) {

        file << "\n" << moveNumber << " C ";
        moveNumber++;
    }
    file << x << "*" << y << " ";
    file.close();
    delete temp, str;
}

void Reversi::readMove(int moveNum) {
    char* temp = new char(5);
    strcpy(temp, ".txt");
    char* str = new char(100);
    std::sprintf(str, "%d", getGameNum());
    strcat(str, temp);
    ifstream file(str, ios::app);
    string line, x, y, number, player;
    int num;
    while (getline(file, line)) {
        stringstream stream(line);
        getline(stream, number, ' ');
        num = atoi(number.c_str());
        if (num == moveNum) {

            getline(stream, player, ' ');
            getline(stream, x, '*');
            getline(stream, y, ' ');
            int xNum = atoi(x.c_str());
            int yNum = atoi(y.c_str());
            cout << number << ". move made to " << xNum + 1 << "*" <<
                    this->intToStr(yNum) << " cells by " << player << endl;
            break;
        }
    }
    file.close();
    delete temp, str;
}

bool Reversi::compareReversi(Reversi game) {
    if (scoreTable[1] > scoreTable[0] && game.scoreTable[1] > game.scoreTable[0]) {
        if (scoreTable[1] >= game.scoreTable[1])
            return true;
        else
            return false;
    } else if (scoreTable[1] >= scoreTable[0])//other game's user is negative
        return true;
    else if (scoreTable[1] >= game.scoreTable[1])
        return true;
    else
        return false;
}


#endif	/* REVERSI_H */

