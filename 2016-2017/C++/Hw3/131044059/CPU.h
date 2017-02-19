/* 
 * File:   CPU.h
 * Author: Şahin Eğilmez
 *
 * Created on 27 Ekim 2016 Perşembe, 11:20
 */

#ifndef CPU_H
#define CPU_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Math.h"
using namespace std;

class CPU {
public:
    CPU(); //default constructor
    CPU(const int opt); //constructor take option
    bool execute(string line); //main function
    bool halted()const; //if take HLT, return true
    void print()const; //print all registers and Program Counter
    int* const getRegisters(); //get all registers to int array
    int getRegWithPos(const int reg) const; //get registers[reg]
    int getR1()const; //get R1 register
    int getR2()const; //get R2 register
    int getR3()const; //get R3 register
    int getR4()const; //get R4 register
    int getR5()const; //get R5 register
    int getOption()const; //get option
    int getPC()const; //get Program Counter
    bool getHlt() const; //if take HLT, return true
    Math getMath();//get math object
    //set registers 0<=index<=4
    void setRegisters(const int r1, const int r2, const int r3, const int r4, const int r5);
    //set registers[reg] =num
    bool setRegWithPos(const int reg, const int num);
    void setR1(const int num); //set R1 =num
    void setR2(const int num); //set R2 =num
    void setR3(const int num); //set R3 =num
    void setR4(const int num); //set R4 =num
    void setR5(const int num); //set R5 =num
    void setPC(const int num); //set PC =num
    void setHlt(const bool val); //set HLT =true or false
    

private:
    int registers[5];//all registers
    int PC, option;//Program Counter and option
    bool hlt;//check take HLT
    Math math;
    /*read and parse each line to instructions array */
    int parser(string line, string instructions[3]);
    /*this function for mov,sub,add operation.optReg which decides to use register*/
    bool checkError(string line);
    bool arithmetics(const string regFirst, const string regSecond, int optReg[3]);
    /*this function execute mov instruction.optReg which decides to use register */
    void mov(const int optReg[3]);
    /*this function execute add instruction.optReg which decides to use register */
    void add(const int optReg[3]);
    /*this function execute sub instruction.optReg which decides to use register */
    void sub(const int optReg[3]);
    /*this function print to register or any integer value*/
    void prn(const string reg);
    /*jmp  go to the line.*/
    void jmp(const string instructions[3], const int optReg[3]);
    /*erase 'ch' in the str string.alternative string.erase*/
    string erase(const string str, const char ch);
};


#endif /* CPU_H */

