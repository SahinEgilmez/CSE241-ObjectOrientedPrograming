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

CPUProgram::CPUProgram(const int opt, const string fileName) {
    if (ReadFile(fileName))
        isOpenFile = true;
    else
        isOpenFile = false;
    option = opt;

}

CPUProgram::CPUProgram(int opt, vector<string> ins) {

    isOpenFile = true;

    option = opt;
    instructions.insert(instructions.end(), ins.begin(), ins.end());
}

CPUProgram::CPUProgram(int opt) {
    option = opt;
    isOpenFile = true;
}

CPUProgram::CPUProgram() {
    option = 0;
    isOpenFile = true;
}

CPUProgram::CPUProgram(CPUProgram &prog) {
    option = prog.getOpt();
    isOpenFile = prog.isOpen();
    instructions.insert(instructions.end(), prog.getIns().begin(), prog.getIns().end());
}

bool CPUProgram::ReadFile(const string fileName) {

    instructions.clear();
    fstream file; //file stream
    string line; //each line 

    file.open(fileName);

    if (!file.is_open()) {
        cout << "Unable to open file";
        isOpenFile = false;
        return false;
    } else {
        while (getline(file, line)) {//read each line
            instructions.push_back(line); //add storage
        }
    }
    file.close();

    return true;
}

string CPUProgram::getLine(int lineNum)const {
    return instructions[lineNum - 1];
}

int CPUProgram::size()const {
    return instructions.size();
}

bool CPUProgram::isOpen() const {
    return isOpenFile;
}

int CPUProgram::getOpt() const {
    return option;
}

vector<string> &CPUProgram::getIns() {
    return instructions;
}

void CPUProgram::setIns(vector<string> vec) {
    instructions.swap(vec);
}

string CPUProgram::operator[](int index) const {
    if (index >= size() || index < 0) {
        cout << "Index Not Found Of CPUProgram!" << endl;
        return "";
    }
    return (instructions[index]);
}

const CPUProgram CPUProgram::operator+(const string line) {
    if (line.empty()) {
        cout << "Not appended empty line!" << endl;
        CPUProgram program;
        return program;
    }
    CPUProgram prog = (*this);
    prog.getIns().push_back(line);
    return prog;
}

const CPUProgram CPUProgram::operator+(CPUProgram &prog) {
    if (prog.size() == 0) {
        cout << "Not appended empty program!" << endl;
        CPUProgram program;
        return program;
    }
    CPUProgram program = (*this);
    for (int i = 1; i <= prog.size(); i++)
        program.getIns().push_back(prog.getLine(i));
    return program;
}

const CPUProgram CPUProgram::operator+=(const string line) {
    if (line.empty()) {
        cout << "Not appended empty line!" << endl;
        return *this;
    }
    getIns().push_back(line);
    return *this;
}

CPUProgram &CPUProgram::operator=(CPUProgram &prog) {
    if (this == &prog) {
        return *this;
    } else {
        option = prog.getOpt();
        setIns(prog.getIns());
        isOpenFile = isOpen();
        return *this;
    }
}

ostream &operator<<(ostream &output, const CPUProgram &prog) {

    for (int i = 1; i <= prog.size(); i++)
        output << prog.getLine(i) << endl;

    return output;
}

bool CPUProgram::operator==(const CPUProgram& prog) {
    return (size() == prog.size());
}

bool CPUProgram::operator!=(const CPUProgram& prog) {
    return (size() != prog.size());
}

bool CPUProgram::operator<(const CPUProgram& prog) {
    return (size() < prog.size());
}

bool CPUProgram::operator>=(const CPUProgram& prog) {
    return (size() >= prog.size());
}

CPUProgram &CPUProgram::operator--() {
    if (size() != 0)
        getIns().pop_back();

    return (*this);
}

const CPUProgram CPUProgram::operator()(const int i1, const int i2) {
    if (i1 < 0 || i1 >= size() || i2 < 0 || i2 >= size() || i1 > i2) {
        cout << "Not running function call because indexes not acceptable!" << endl;
        CPUProgram program;
        return program;
    }
    vector<string> v;
    CPUProgram prog = (*this);

    for (int i = i1; i <= i2; i++)
        v.push_back(getLine(i));
    prog.getIns().clear();
    for (int i = 0; i < v.size(); i++)
        prog.getIns().push_back(v[i]);
    return prog;
}