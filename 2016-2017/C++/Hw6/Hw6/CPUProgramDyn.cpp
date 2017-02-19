/* 
 * File:   CPUProgramDyn.cpp
 * Author: Şahin Eğilmez
 *
 * Created on 27 Ekim 2016 Perşembe, 11:21
 */

#include <iostream>
#include <string>
#include <fstream>
#include "CPUProgramDyn.h"

using namespace std;
namespace cpuprogram {

    CPUProgramDyn::CPUProgramDyn(const int opt, const string fileName) {
        if (ReadFile(fileName))
            isOpenFile = true;
        else
            isOpenFile = false;
        option = opt;
        lenght = 0;
        instructions = new string[1];
    }

    CPUProgramDyn::CPUProgramDyn(int opt, string* insArr) {
        isOpenFile = true;
        lenght = 0;
        option = opt;
        instructions = insArr;
    }

    CPUProgramDyn::CPUProgramDyn(int opt) {
        option = opt;
        isOpenFile = true;
        lenght = 0;
        instructions = new string[1];
    }

    CPUProgramDyn::CPUProgramDyn() {
        option = 0;
        lenght = 0;
        instructions = new string[1];
        isOpenFile = true;
    }

    CPUProgramDyn::CPUProgramDyn(CPUProgramDyn &prog) {
        option = prog.getOpt();
        isOpenFile = prog.isOpen();
        lenght = prog.size();
        instructions = new string[lenght];
        for (int i = 0; i < lenght; i++) {
            instructions[i] = prog.getLine(i + 1); //i+1 because lineNum start 1
        }
    }

    bool CPUProgramDyn::ReadFile(const string fileName) {
        delete []instructions;
        instructions = NULL;
        instructions = new string[1];
        fstream file; //file stream
        string line; //each line 

        file.open(fileName);

        if (!file.is_open()) {
            cout << "Unable to open file";
            isOpenFile = false;
            return false;
        } else {
            while (getline(file, line)) {//read each line
                push(line);
            }
        }
        file.close();

        return true;
    }

    string CPUProgramDyn::getLine(int lineNum)const {
        return instructions[lineNum - 1];
    }

    int CPUProgramDyn::size()const {
        return lenght;
    }

    void CPUProgramDyn::setSize(const int newSize) {
        lenght = newSize;
    }

    bool CPUProgramDyn::isOpen() const {
        return isOpenFile;
    }

    int CPUProgramDyn::getOpt() const {
        return option;
    }

    string* &CPUProgramDyn::getIns() {
        return instructions;
    }

    void CPUProgramDyn::setIns(string* strArr, int arrSize) {
        delete []instructions;
        instructions = NULL;
        instructions = new string[arrSize];
        for (int i = 0; i < arrSize; i++)
            instructions[i] = strArr[i];
    }

    string CPUProgramDyn::operator[](int index) const {
        if (index >= size() || index < 0) {
            cout << "Index Not Found Of CPUProgramDyn!" << endl;
            return "";
        }
        return (instructions[index]);
    }

    const CPUProgramDyn CPUProgramDyn::operator+(const string line) {
        if (line.empty()) {
            cout << "Not appended empty line!" << endl;
            CPUProgramDyn program;
            return program;
        }
        CPUProgramDyn prog(*this);
        prog.push(line);
        return prog;
    }

    const CPUProgramDyn CPUProgramDyn::operator+(CPUProgramDyn &prog) {
        if (prog.size() == 0) {
            cout << "Not appended empty program!" << endl;
            CPUProgramDyn program;
            return program;
        }
        CPUProgramDyn program(*this);
        for (int i = 1; i <= prog.size(); i++)
            program.push(prog.getLine(i));
        return program;
    }

    const CPUProgramDyn CPUProgramDyn::operator+=(const string line) {
        if (line.empty()) {
            cout << "Not appended empty line!" << endl;
            return *this;
        }
        push(line);
        return *this;
    }

    CPUProgramDyn &CPUProgramDyn::operator=(CPUProgramDyn &prog) {
        if (this == &prog) {
            return *this;
        } else {
            option = prog.getOpt();
            setIns(prog.getIns(), prog.size());
            setSize(prog.size());
            isOpenFile = isOpen();
            return *this;
        }
    }

    ostream &operator<<(ostream &output, const CPUProgramDyn &prog) {
        for (int i = 1; i <= prog.size(); i++)
            output << prog.getLine(i) << endl;
        return output;
    }

    bool CPUProgramDyn::operator==(const CPUProgramDyn& prog) {
        return (size() == prog.size());
    }

    bool CPUProgramDyn::operator!=(const CPUProgramDyn& prog) {
        return (size() != prog.size());
    }

    bool CPUProgramDyn::operator<(const CPUProgramDyn& prog) {
        return (size() < prog.size());
    }

    bool CPUProgramDyn::operator>(const CPUProgramDyn& prog) {
        return (size() > prog.size());
    }

    bool CPUProgramDyn::operator<=(const CPUProgramDyn& prog) {
        return (size() <= prog.size());
    }

    bool CPUProgramDyn::operator>=(const CPUProgramDyn& prog) {
        return (size() >= prog.size());
    }

    CPUProgramDyn &CPUProgramDyn::operator--() {
        if (size() != 0)
            pop();
        return (*this);
    }

    const CPUProgramDyn CPUProgramDyn::operator()(const int i1, const int i2) {
        if (i1 < 0 || i1 >= size() || i2 < 0 || i2 >= size() || i1 > i2) {
            cout << "Not running function call because indexes not acceptable!" << endl;
            CPUProgramDyn program;
            return program;
        }
        CPUProgramDyn prog;
        for (int i = i1; i <= i2; i++)
            prog.push(getLine(i));
        return prog;
    }

    void CPUProgramDyn::push(const string& line) {
        if (size() != 0) {
            string* temp = new string[size()];
            for (int j = 0; j < size(); j++) {
                temp[j] = instructions[j];
            }
            delete []instructions;
            instructions = new string[size() + 1];
            for (int k = 0; k < size(); k++) {
                instructions[k] = temp[k];
            }
            delete []temp;
            instructions[size()] = line;
            setSize(size() + 1);
        } else {
            instructions[size()] = line;
            setSize(size() + 1);
        }
    }

    string& CPUProgramDyn::pop() {
        if (size() > 0) {
            setSize(size() - 1);
            string popLine = instructions[size()];
            string* temp = new string[size() ];
            for (int j = 0; j < size(); j++) {
                temp[j] = instructions[j];
            }
            delete []instructions;
            instructions = new string[size()];
            for (int k = 0; k < size(); k++) {
                instructions[k] = temp[k];
            }
            delete []temp;
            return popLine;
        }
        string res = "Size 0, so not pop line.\n";
        return res;
    }
}