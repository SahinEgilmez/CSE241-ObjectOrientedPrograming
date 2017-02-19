/* HW6 ŞAHİN EĞİLMEZ 131044059 
 * File:   Reversi.h
 * Author: Şahin Eğilmez
 *
 * Created on 10 Aralık 2015 Perşembe, 21:58
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
namespace REVERSI_GTU {

    class Cell {
    public:
        Cell(int valX, int valY);
        Cell(); //constructor
        char getOwner(); //get cell owner
        void setOwner(char ch); //set the owner
        int getLivingCell(); //get owner with integer
        void setLivingCell(int number); //set owner with integer
        int getX()const; //get line number(x)
        int getY()const; //get column number(y)
        void setX(int number); //set line number(x)
        void setY(int number); //set column number(y)
        void operator=(const Cell &c);
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
        void operator=(const PlayableCells &p);
    };

    class Reversi {//this class for the Reversi game
    public:
        Reversi(int valX, int valY); //constructors performs (x,y) board
        Reversi(); //constructors performs (8,8) board
        Reversi(const Reversi &game);
        ~Reversi();
        void playGame(); //playing game.
        void continueGame(); //continue game that paused
        int getHeight(); //get board height
        int getWidht(); //get board widht
        static int getLiveGame(); //get live game(object) at the moment
        int getGameNum(); //get special game number
        bool compareReversi(Reversi &game)const; //comapring another game.It returns true 
        //is the first game is better for the user, otherwise it returns false.
        void drawBoard(); //this function draw the table to terminal. 
        int scoreTable[2]; //take the scores.
        void operator=(const Reversi &r);
        Reversi &operator++(); //pre
        Reversi &operator++(int); //post
        friend std::ostream &operator<<(std::ostream &output, Reversi &game) {
            game.drawBoard();
            output << "Computer: " << game.scoreTable[0] << "  User: " << game.scoreTable[1] << endl;
        }
    private:
        void menu(); //this functions get table size from player.
        bool findOfPlayablePoints(int player, int otherPlayer); //momentarily
        //find of playable all points
        bool checkCells(int num, int player, int otherPlayer); //checks 
        //all neighbors with checkNeighbors function
        bool checkNeighbors(int num, int player, int otherPlayer, int eatDirection,
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
        int operation(int num, char op, char coordinate); //it does ++,-- or nothing(0) by char op
        int operation(int num, char op); //it does ++,-- or nothing(0) by char op
        int height; //board height
        int widht; //board widht value
        int cellSize;
        Cell *gameCells; //take the living cell(don't take died Cell)
        static int liveObj; //living object number
        int gameNum; //special number for game.Create by liveObj
        int moveNumber; //take the move number each game
        PlayableCells *playableCells; //momentarly take playable Cells.
        //Cells is varied each time so  size is small
    };



}


#endif	/* REVERSI_H */

