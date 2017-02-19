// HW01_131044059_Sahin_Egilmez
// main.cpp
//
// Created on 28/09/2015 by Abdullah_Akay
//
// Description
//
// The c++ program performs reversi game.

//Includes && Defines

#include <iostream>
using namespace std;
const int MAXSIZE = 20;

//Function Prototypes

int menu(); //this functions get table size from player. 
void firstFillInArray(int array[MAXSIZE][MAXSIZE], int size); //this function 
//first fill in table array.
void drawTable(int array[MAXSIZE][MAXSIZE], int size); //this function draw the 
//table to terminal. 
int controlTopLeft(int point[MAXSIZE][MAXSIZE], int x, int y, int player,
        int otherPlayer, int size); //checks neighnors of top left of point.
int controlTop(int array[MAXSIZE][MAXSIZE], int x, int y, int player,
        int otherPlayer, int size); //checks neighnors of top of point.
int controlTopRight(int array[MAXSIZE][MAXSIZE], int x, int y, int player,
        int otherPlayer, int size); //checks neighnors of top right of point.
int controlRight(int array[MAXSIZE][MAXSIZE], int x, int y, int player,
        int otherPlayer, int size); //checks neighnors of right of point.
int controlBottomRight(int array[MAXSIZE][MAXSIZE], int x, int y, int player,
        int otherPlayer, int size); //checks neighnors of bottom right of point.
int controlBottom(int array[MAXSIZE][MAXSIZE], int x, int y, int player,
        int otherPlayer, int size); //checks neighnors of bottom of point.
int controlBottomLeft(int array[MAXSIZE][MAXSIZE], int x, int y, int player,
        int otherPlayer, int size); //checks neighnors of  bottom left of point.
int controlLeft(int array[MAXSIZE][MAXSIZE], int x, int y, int player,
        int otherPlayer, int size); //checks neighnors of left of point.
void checkNeighbors(int array[MAXSIZE][MAXSIZE], int x, int y, int player,
        int otherPlayer, int earnedPoint[8], int size); //checks all neighbors 
//of point using above 8 functions
void eatPointOfTopLeft(int array[MAXSIZE][MAXSIZE], int x, int y, int player,
        int otherPlayer, int size); //eat neighbors of top left of point.
void eatPointOfTop(int array[MAXSIZE][MAXSIZE], int x, int y, int player,
        int otherPlayer, int size); //eat neighbors of top  of point.
void eatPointOfTopRight(int array[MAXSIZE][MAXSIZE], int x, int y, int player,
        int otherPlayer, int size); //eat neighbors of top right of point.
void eatPointOfRight(int array[MAXSIZE][MAXSIZE], int x, int y, int player,
        int otherPlayer, int size); //eat neighbors of right of point.
void eatPointOfBottomRight(int array[MAXSIZE][MAXSIZE], int x, int y, int player,
        int otherPlayer, int size); //eat neighbors of bottom right of point.
void eatPointOfBottom(int array[MAXSIZE][MAXSIZE], int x, int y, int player,
        int otherPlayer, int size); //eat neighbors of bottom of point.
void eatPointOfBottomLeft(int array[MAXSIZE][MAXSIZE], int x, int y, int player,
        int otherPlayer, int size); //eat neighbors of bottom left of point.
void eatPointOfLeft(int array[MAXSIZE][MAXSIZE], int x, int y, int player,
        int otherPlayer, int size); //eat neighbors of left of point.
void eatPoints(int array[MAXSIZE][MAXSIZE], int x, int y, int player, 
        int otherPlayer, int earnedNeighbors[8], int size); //eats all neighbors
//of point using above 8 functions 
bool findOfPlayablePoints(int array[MAXSIZE][MAXSIZE], int player, int otherPlayer,
        int iValue[100], int jValue[100], int eatValue[100], int size);//momentarily
//find of playable all points and fill coordinates to iValue and jValue array and 
//if play to these points, fill eatable points to eatValue array.
int charToInt(char ch); //take a char and convert int.
char intToChar(int number); //take a int and convert char
void playPlayer(int array[MAXSIZE][MAXSIZE], int player, int otherPlayer,
        int size); //This function performs player playing.
void playComputer(int array[MAXSIZE][MAXSIZE], int player, int otherPlayer,
        int size); //This function performs computer thinking and playing .
int* scoreTable(int array[MAXSIZE][MAXSIZE], int size); //this function take the score
bool endOfGame(int array[MAXSIZE][MAXSIZE], int player, int otherPlayer,
        int size, int score[2]); //this function check the end of game.

//The Main Function

int main() {
    int gameTable[MAXSIZE][MAXSIZE]; //game table
    int size = 0; //size of game table
    int* score;//score array
    size = menu(); //to determines size of table
    firstFillInArray(gameTable, size); //fill in game table
    drawTable(gameTable, size); //first darawing of game table
    while (endOfGame(gameTable, 2, 1, size, score) == false) {//game to continue
    //until end of game;
        //score[0]=0;
        //score[1]=0;
        playPlayer(gameTable, 2, 1, size); //player plays
        score=scoreTable(gameTable,size); //take the score and print screen
        if (endOfGame(gameTable, 2, 1, size, score))//if game over, exit loop
            break;
        //score[0]=0;
        //score[1]=0;
        playComputer(gameTable, 1, 2, size); //computer plays
        score=scoreTable(gameTable, size); //take the score and print screen
    }
    return 0;
}

//Functions Implementation

int menu() {
    int lenght = 0;
    bool acceptLenght = false;
    cout << "Please enter to lenght of table side .Lenght can be only "
            "4,6,8,10,12,14,16,18,20 ." << endl;
    //this block run until entering acceptable number
    while (acceptLenght == false) {
        cout << "Lenght:";
        cin>>lenght;
        cin.clear();
        cin.ignore(10000, '\n');
        //accept to only 4 betweeen 20 and even number
        if (lenght % 2 == 0 && lenght >= 4 && lenght <= 20) {
            acceptLenght = true;
        } else {
            cout << "Please only 4,6,8,10,12,14,16,18,20 ." << endl;
        }
    }
    return lenght;
}

void firstFillInArray(int array[MAXSIZE][MAXSIZE], int size) {
    //this blocks fill in array for game
    for (int i = 0; i < MAXSIZE; i++) {
        for (int j = 0; j < MAXSIZE; j++) {
            array[i][j] = 0;
        }
    }
    array[size / 2 - 1][size / 2 - 1] = 1;
    array[size / 2][size / 2] = 1;
    array[size / 2][size / 2 - 1] = 2;
    array[size / 2 - 1][size / 2] = 2;
}

void drawTable(int array[MAXSIZE][MAXSIZE], int size) {
    //this blocks draw the array according to size 
    char ch = 'a';
    cout << "  a";
    for (int k = 1; k < size; k++) {
        ch = ch + 1;
        cout << ch;
    }
    cout << endl;
    for (int i = 0; i < size; i++) {
        if (i < 9)
            cout << "0";
        cout << i + 1;
        for (int j = 0; j < size; j++) {
            if (array[i][j] == 0)
                cout << ".";
            else if (array[i][j] == 1)
                cout << "X";
            else if (array[i][j] == 2)
                cout << "O";
        }
        cout << endl;
    }
}

int controlTopLeft(int point[MAXSIZE][MAXSIZE], int x, int y, int player, 
        int otherPlayer, int size) {
    int result = 0;
    bool playable = false;
    //this block check top left of the point(x,y) 
    while (x > 0 && y > 0) {
        if (point[x - 1][y - 1] == otherPlayer)
            result++;
        else if (point[x - 1][y - 1] == 0) {
            result = 0;
            break;
        } else if (point[x - 1][y - 1] == player) {
            playable = true;
            break;
        }
        x--;
        y--;
    }
    if (playable == false)
        result = 0;
    return result;
}

int controlTop(int array[MAXSIZE][MAXSIZE], int x, int y, int player, 
        int otherPlayer, int size) {
    int result = 0;
    bool playable = false;
    //this block check top of the point(x,y) 
    while (x > 0) {
        if (array[x - 1][y] == otherPlayer) {
            result++;
        } else if (array[x - 1][y] == 0) {
            result = 0;
            break;
        } else if (array[x - 1][y] == player) {
            playable = true;
            break;
        }
        x--;
    }
    if (playable == false)
        result = 0;
    return result;
}

int controlTopRight(int array[MAXSIZE][MAXSIZE], int x, int y, int player, 
        int otherPlayer, int size) {
    int result = 0;
    bool playable = false;
    //this block check top right of the point(x,y) 
    while (x > 0 && y < size - 1) {
        if (array[x - 1][y + 1] == otherPlayer) {
            result++;
        } else if (array[x - 1][y + 1] == 0) {
            result = 0;
            break;
        } else if (array[x - 1][y + 1] == player) {
            playable = true;
            break;
        }
        x--;
        y++;
    }
    if (playable == false)
        result = 0;
    return result;
}

int controlRight(int array[MAXSIZE][MAXSIZE], int x, int y, int player, 
        int otherPlayer, int size) {
    int result = 0;
    bool playable = false;
    //this block check right of the point(x,y) 
    while (y < size - 1) {
        if (array[x][y + 1] == otherPlayer) {
            result++;
        } else if (array[x][y + 1] == 0) {
            result = 0;
            break;
        } else if (array[x][y + 1] == player) {
            playable = true;
            break;
        }
        y++;
    }
    if (playable == false)
        result = 0;
    return result;
}

int controlBottomRight(int array[MAXSIZE][MAXSIZE], int x, int y, int player, 
        int otherPlayer, int size) {
    int result = 0;
    bool playable = false;
    //this block check bottom right of the point(x,y) 
    while (x < size - 1 && y < size - 1) {
        if (array[x + 1][y + 1] == otherPlayer) {
            result++;
        } else if (array[x + 1][y + 1] == 0) {
            result = 0;
            break;
        } else if (array[x + 1][y + 1] == player) {
            playable = true;
            break;
        }
        x++;
        y++;
    }
    if (playable == false)
        result = 0;
    return result;
}

int controlBottom(int array[MAXSIZE][MAXSIZE], int x, int y, int player,
        int otherPlayer, int size) {
    int result = 0;
    bool playable = false;
    //this block check bottom of the point(x,y) 
    while (x < size - 1) {
        if (array[x + 1][y] == otherPlayer) {
            result++;
        } else if (array[x + 1][y] == 0) {
            result = 0;
            break;
        } else if (array[x + 1][y] == player) {
            playable = true;
            break;
        }
        x++;
    }
    if (playable == false)
        result = 0;
    return result;
}

int controlBottomLeft(int array[MAXSIZE][MAXSIZE], int x, int y, int player, 
        int otherPlayer, int size) {
    int result = 0;
    bool playable = false;
    //this block check bottom left of the point(x,y) 
    while (x < size - 1 && y > 0) {
        if (array[x + 1][y - 1] == otherPlayer) {
            result++;
        } else if (array[x + 1][y - 1] == 0) {
            result = 0;
            break;
        } else if (array[x + 1][y - 1] == player) {
            playable = true;
            break;
        }
        x++;
        y--;
    }
    if (playable == false)
        result = 0;
    return result;
}

int controlLeft(int array[MAXSIZE][MAXSIZE], int x, int y, int player,
        int otherPlayer, int size) {
    int result = 0;
    bool playable = false;
    //this block check left of the point(x,y) 
    while (y > 0) {
        if (array[x][y - 1] == otherPlayer) {
            result++;
        } else if (array[x][y - 1] == 0) {
            result = 0;
            break;
        } else if (array[x][y - 1] == player) {
            playable = true;
            break;
        }
        y--;
    }
    if (playable == false)
        result = 0;
    return result;
}

void checkNeighbors(int array[MAXSIZE][MAXSIZE], int x, int y, int player, 
        int otherPlayer, int earnedPoint[8], int size) {
    //this block check the neighbors of point(x,y) starting from the top left 
    //between left with clockwise.
    earnedPoint[0] = controlTopLeft(array, x, y, player, otherPlayer, size);
    earnedPoint[1] = controlTop(array, x, y, player, otherPlayer, size);
    earnedPoint[2] = controlTopRight(array, x, y, player, otherPlayer, size);
    earnedPoint[3] = controlRight(array, x, y, player, otherPlayer, size);
    earnedPoint[4] = controlBottomRight(array, x, y, player, otherPlayer, size);
    earnedPoint[5] = controlBottom(array, x, y, player, otherPlayer, size);
    earnedPoint[6] = controlBottomLeft(array, x, y, player, otherPlayer, size);
    earnedPoint[7] = controlLeft(array, x, y, player, otherPlayer, size);
}

void eatPointOfTopLeft(int array[MAXSIZE][MAXSIZE], int x, int y, int player, 
        int otherPlayer, int size) {
    bool eatComplete = false;
    array[x][y] = player;
    //this block eats all points to top left of the point(x,y) 
    while (eatComplete == false) {
        if (array[x - 1][y - 1] == otherPlayer) {
            array[x - 1][y - 1] = player;
        } else if (array[x - 1][y - 1] == player)
            eatComplete = true;
        x--;
        y--;
    }
}

void eatPointOfTop(int array[MAXSIZE][MAXSIZE], int x, int y, int player, 
        int otherPlayer, int size) {
    bool eatComplete = false;
    array[x][y] = player;
    //this block eats all points to top of the point(x,y) 
    while (eatComplete == false) {
        if (array[x - 1][y] == otherPlayer) {
            array[x - 1][y] = player;
        } else if (array[x - 1][y] == player)
            eatComplete = true;
        x--;
    }
}

void eatPointOfTopRight(int array[MAXSIZE][MAXSIZE], int x, int y, int player, 
        int otherPlayer, int size) {
    bool eatComplete = false;
    array[x][y] = player;
    //this block eats all points to top right of the point(x,y) 
    while (eatComplete == false) {
        if (array[x - 1][y + 1] == otherPlayer) {
            array[x - 1][y + 1] = player;
        } else if (array[x - 1][y + 1] == player)
            eatComplete = true;
        x--;
        y++;
    }
}

void eatPointOfRight(int array[MAXSIZE][MAXSIZE], int x, int y, int player, 
        int otherPlayer, int size) {
    bool eatComplete = false;
    array[x][y] = player;
    //this block eats all points to right of the point(x,y) 
    while (eatComplete == false) {
        if (array[x][y + 1] == otherPlayer) {
            array[x][y + 1] = player;
        } else if (array[x][y + 1] == player)
            eatComplete = true;
        y++;
    }
}

void eatPointOfBottomRight(int array[MAXSIZE][MAXSIZE], int x, int y, int player,
        int otherPlayer, int size) {
    bool eatComplete = false;
    array[x][y] = player;
    //this block eats all points to bottom right of the point(x,y) 
    while (eatComplete == false) {
        if (array[x + 1][y + 1] == otherPlayer) {
            array[x + 1][y + 1] = player;
        } else if (array[x + 1][y + 1] == player)
            eatComplete = true;
        x++;
        y++;
    }
}

void eatPointOfBottom(int array[MAXSIZE][MAXSIZE], int x, int y, int player,
        int otherPlayer, int size) {
    bool eatComplete = false;
    array[x][y] = player;
    //this block eats all points to bottom of the point(x,y) 
    while (eatComplete == false) {
        if (array[x + 1][y] == otherPlayer) {
            array[x + 1][y] = player;
        } else if (array[x + 1][y] == player)
            eatComplete = true;
        x++;
    }
}

void eatPointOfBottomLeft(int array[MAXSIZE][MAXSIZE], int x, int y, int player,
        int otherPlayer, int size) {
    bool eatComplete = false;
    array[x][y] = player;
    //this block eats all points to bottom left of the point(x,y) 
    while (eatComplete == false) {
        if (array[x + 1][y - 1] == otherPlayer) {
            array[x + 1][y - 1] = player;
        } else if (array[x + 1][y - 1] == player)
            eatComplete = true;
        x++;
        y--;
    }
}

void eatPointOfLeft(int array[MAXSIZE][MAXSIZE], int x, int y, int player, 
        int otherPlayer, int size) {
    bool eatComplete = false;
    array[x][y] = player;
    //this block eats all points to left of the point(x,y) 
    while (eatComplete == false) {
        if (array[x][y - 1] == otherPlayer) {
            array[x][y - 1] = player;
        } else if (array[x][y - 1] == player)
            eatComplete = true;
        y--;
    }
}

void eatPoints(int array[MAXSIZE][MAXSIZE], int x, int y, int player, 
        int otherPlayer, int earnedNeighbors[8], int size) {
    //this block eats the neighbors of point(x,y) starting from the top left 
    //between left with clockwise.
    for (int k = 0; k < 8; k++) {
        if (earnedNeighbors[k] > 0) {
            if (k == 0)
                eatPointOfTopLeft(array, x, y, player, otherPlayer, size);
            else if (k == 1)
                eatPointOfTop(array, x, y, player, otherPlayer, size);
            else if (k == 2)
                eatPointOfTopRight(array, x, y, player, otherPlayer, size);
            else if (k == 3)
                eatPointOfRight(array, x, y, player, otherPlayer, size);
            else if (k == 4)
                eatPointOfBottomRight(array, x, y, player, otherPlayer, size);
            else if (k == 5)
                eatPointOfBottom(array, x, y, player, otherPlayer, size);
            else if (k == 6)
                eatPointOfBottomLeft(array, x, y, player, otherPlayer, size);
            else if (k == 7)
                eatPointOfLeft(array, x, y, player, otherPlayer, size);
        }
    }
}

bool findOfPlayablePoints(int array[MAXSIZE][MAXSIZE], int player, int otherPlayer,
        int iValue[100], int jValue[100], int eatValue[100], int size) {
    int earnedPoints[8];
    bool playable = false;
    int num = 0, m = 0, max = 0;
    while (num == 0) {//thid loop run only once
        //this two loops performs enter in array
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (array[i][j] == 0) {//if point playable,condition is provided
                    checkNeighbors(array, i, j, player, otherPlayer, earnedPoints,
                                   size); //check and fill earned points array
                    for (int k = 0; k < 8; k++) {
                        if (earnedPoints[k] > 0) {//find max value
                            playable = true;
                            max += earnedPoints[k];
                        }
                    }
                    if (max > 0) {//if max any point is playable fill arrays
                        iValue[m] = i;
                        jValue[m] = j;
                        eatValue[m] = max;
                        m++;
                        max = 0;
                    }
                }
            }
        }
        num++;
    }
    return playable;
}

int charToInt(char ch) {
    int number;
    number = ch - 97; //if enter a,number is 0 and if enter b number is 1...
    return number;
}

char intToChar(int number) {
    char ch;
    ch = number + 97; //if enter 97 ,number is a and if enter 97 number is b...
    return ch;
}

void playPlayer(int array[MAXSIZE][MAXSIZE], int player, int otherPlayer, 
        int size) {
    int x, y;
    bool playable = false;
    int i = 0, earnedNeighbors[8], iValue[100], jValue[100], eatValue[100];
    char charY;
    for (int i = 0; i < 100; i++) {//first of all fill in arrays as empty
        eatValue[i] = 0;
        iValue[i] = 0;
        jValue[i] = 0;
    }
    while (playable == false) {//runs until player enter playable coordinate
        if (findOfPlayablePoints(array, player, otherPlayer, iValue, jValue, 
            eatValue, size) == false)//if cannot playable point,exit loop 
            break;
        while (eatValue[i] > 0) {//print to playable point
            charY = intToChar(jValue[i]);
            cout << iValue[i] + 1 << charY << " ";
            jValue[i] = charToInt(charY);
            i++;
        }
        i = 0;
        cout << "points is playable.";
        cout << "Please enter you want to play point coordinates: " << endl;
        cin >> x>>charY;//player enter the point coordinates
        cin.clear();
        cin.ignore(1000, '\n');
        x = x - 1;
        y = charToInt(charY);
        //check entered coordinates
        checkNeighbors(array, x, y, player, otherPlayer, earnedNeighbors, size);
        for (int k = 0; k < 8; k++) {
            if (earnedNeighbors[k] > 0) {//find to playable point
                playable = true;
                break;
            }
        }
        if (playable == false) {//if entered point isn't playable, again enter
            cout <<"The coordinates that you enter isn't playable!Please enter "
                   "again!" << endl;
        } else if (playable == true) {//if entered point isn playable,eat points
            eatPoints(array, x, y, player, otherPlayer, earnedNeighbors, size);
            drawTable(array, size);
        }
    }
}

void playComputer(int array[MAXSIZE][MAXSIZE], int player, int otherPlayer, 
        int size) {
    int max = 0, x, y, m = 0, coordinate = -1;
    bool playable = false;
    int earnedNeighbors[8], iValue[100], jValue[100], eatValue[100];
    char charY;
    for (int i = 0; i < 100; i++) {//first of all fill in arrays as empty
        eatValue[i] = 0;
        iValue[i] = 0;
        jValue[i] = 0;
    }
    findOfPlayablePoints(array, player, otherPlayer, iValue, jValue, eatValue, 
                         size);
    while (eatValue[m] > 0) {//this loop process all playable points
        //if point is corner of table,computer plays here
        if ((iValue[m] == 0 || iValue[m] == size) && (jValue[m] == 0 ||
                                                      jValue[m] == size)) {
            max = eatValue[m];
            coordinate = m;
            break;
        }
        //if point is bring the max score,computer plays here
        else if (eatValue[m] > max) {
            max = eatValue[m];
            coordinate = m;
        }
        //if point's bring to score is equal and point is located on the diogonal
        //computer plays here
        else if (eatValue[m] == max && (iValue[m] == jValue[m])) {
            max = eatValue[m];
            coordinate = m;
        }
        m++;
    }
    if (max > 0) {//determine to points will be played 
        playable = true;
        x = iValue[coordinate];
        y = jValue[coordinate];
    }
    if (playable == true) {//if computer can play,process to eating points
        checkNeighbors(array, x, y, player, otherPlayer, earnedNeighbors, size);
        eatPoints(array, x, y, player, otherPlayer, earnedNeighbors, size);
        charY = intToChar(y);
        cout << "Computer play to " << x + 1 << charY << " point." << endl;
        y = charToInt(charY);
        drawTable(array, size);
    } else//if computer cannot play, print to information
        cout << "Computer could play!" << endl;
}

int* scoreTable(int array[MAXSIZE][MAXSIZE], int size) {
    int score[2]={0,0};
    //This block check the array and get score
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (array[i][j] == 1)
                score[0]++;
            if (array[i][j] == 2)
                score[1]++;
        }
    }
    //print score in screen
    cout << "Player:" << score[1] << " Computer:" << score[0] << endl;
    return score;
}

bool endOfGame(int array[MAXSIZE][MAXSIZE], int player, int otherPlayer,
        int size, int score[2]) {
    bool gameOver = false;
    int iValue[100], jValue[100], eatValue[100];
    //if we come the end of the game,game over.
    if (findOfPlayablePoints(array ,player, otherPlayer, iValue, jValue,
                             eatValue, size) == false &&
        findOfPlayablePoints(array, otherPlayer, player, iValue, jValue,
                             eatValue, size) == false) {
        gameOver = true;
        cout << "GAME OVER" << endl;//print to scree GAME OVER
        if(score[1]>score[0])
            cout<<"Congrulation!You Wins"<<endl;
        else if(score[0]>score[1])
            cout<<"Computer Wins!"<<endl;
        else if(score[0]==score[1])
            cout<<"The Game Ended In A Draw!"<<endl;
    }
    return gameOver;
}