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

CPUProgram::CPUProgram(const int opt,const string fileName) {
    if(ReadFile(fileName))
        isOpenFile = true;
    else
        isOpenFile =false;
    option=opt;
}

CPUProgram::CPUProgram(const int opt) {
    option=opt;
    isOpenFile = true;
}

CPUProgram::CPUProgram(){
    option = 0;
    isOpenFile = true;
}


bool CPUProgram::isOpen() const{
    return isOpenFile;
}

bool CPUProgram::ReadFile(const string fileName) {
    
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