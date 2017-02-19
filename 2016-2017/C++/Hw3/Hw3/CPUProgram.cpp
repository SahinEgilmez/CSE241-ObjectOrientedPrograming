/* 
 * File:   CPUProgram.cpp
 * Author: Şahin Eğilmez
 *
 * Created on 27 Ekim 2016 Perşembe, 11:21
 */

#include <iostream>
#include <string>
#include <fstream>
#include "CPUProgram.h"

using namespace std;

CPUProgram::CPUProgram(const string fileName) {
    if(readFile(fileName))
        isOpenFile = true;
    else
        isOpenFile =false;
}

bool CPUProgram::isOpen() const{
    return isOpenFile;
}

bool CPUProgram::readFile(const string fileName) {
    instructions.clear();
    fstream file; //file stream
    string line; //each line 
    file.open(fileName);
    if (!file.is_open()) {
        cout << "Unable to open file";
        return false;
    } else {
        while (getline(file, line)) {//read each line
            instructions.push_back(line);//add storage
        }
    }
    file.close();
    
    return true;
}

string CPUProgram::getLine(const int lineNum)const {
    return instructions[lineNum -1];
}

int CPUProgram::size()const {
    return instructions.size();
}