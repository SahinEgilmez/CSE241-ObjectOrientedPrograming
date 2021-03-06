/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   cpu.h
 * Author: segilmez
 *
 * Created on 09 Ekim 2016 Pazar, 18:14
 */

#ifndef CPU_H
#define CPU_H
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

/*read instruction from file and execute by using registers array*/
bool run(string fileName, int option, int registers[5], uint8_t memory[50]);
/*read and parse each line to instructions array */
int parser(string line, string instructions[3]);
/*this function for mov,sub,add operation.optReg which decides to use register*/
bool arithmetics(string regFirst, string regSecond, int optReg[4]);
/*this function execute mov instruction.optReg which decides to use register */
void mov(int registers[5], int optReg[4], uint8_t memory[50]);
/*this function execute add instruction.optReg which decides to use register */
void add(int registers[5], int optReg[4], uint8_t memory[50]);
/*this function execute sub instruction.optReg which decides to use register */
void sub(int registers[5], int optReg[4], uint8_t memory[50]);
/*this function print to register or any integer value*/
void prn(string reg, int registers[5], uint8_t memory[50]);
/*jmp close file and open again.then go to the line by reading.*/
void jmp(fstream *file, string filename, string instructions[3], int registers[5],
        int optReg[4], uint8_t memory[50]);
/*this function finish program, show memory and registers and exit*/
void hlt(int registers[5], uint8_t memory[50]);
/*erase 'ch' in the oid hlt(int registers[5],uint8_t memory[50]);str string.alternative string.erase*/
string erase(string str, char ch);
/*converts string to integer. alternative atoi*/
int strToInt(string str);
/*take the integer mathemetics power. i1^i2. alternative cmath's pow*/
int pow(int i1, int i2);




#endif /* CPU_H */

