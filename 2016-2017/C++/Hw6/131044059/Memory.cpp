/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include "Memory.h"

using namespace std;

Memory::Memory() {
    option = 0;
    for (int i = 0; i < 50; i++)
        memory[i] = 0;
}

Memory::Memory(const int opt) {
    option = option;
    for (int i = 0; i < 50; i++)
        memory[i] = 0;
}

void Memory::setOpt(const int value) {
    option = value;
}

int Memory::getOpt()const  {
    return option;
}

void Memory::setMem(const int index,const uint8_t value) {
    memory[index] =  value;
}

uint8_t Memory::getMem(const int index)const  {
    return (memory[index]);
}

void Memory::printAll()const {
    for (int i = 0; i < 50; i++)
        cout << "#" << i << " -> " << (int)getMem(i) << ", ";
    cout << endl;
}
