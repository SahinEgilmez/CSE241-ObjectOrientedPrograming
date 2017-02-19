/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Memory.h
 * Author: segilmez
 *
 * Created on 06 Kasım 2016 Pazar, 14:35
 */

#ifndef MEMORY_H
#define MEMORY_H
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class Memory {
public:
    Memory(); //default constructor
    Memory(const int opt); //take option. must be 0,1 or 2
    void printAll()const ; //print all memory
    uint8_t getMem(const int index)const; //get memory of index
    void setMem(const int index, const uint8_t value); //set value to memory[index]
    int getOpt()const; //get option
    void setOpt(const int value); //set option, it' not necessary

private:
    uint8_t memory[50]; //storage
    int option; //option

};



#endif /* MEMORY_H */

