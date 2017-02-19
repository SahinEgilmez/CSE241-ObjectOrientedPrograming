/* 
 * File:   CPUProgram.h
 * Author: Şahin Eğilmez
 *
 * Created on 27 Ekim 2016 Perşembe, 11:21
 */

#ifndef CPUPROGRAM_H
#define CPUPROGRAM_H
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class CPUProgram {
public:
    CPUProgram(int opt); //constructor take option
    CPUProgram(const int opt, const string fileName); //constructor take filename
    CPUProgram(int opt, vector<string> ins); //constructor take filename
    CPUProgram(); //default constructor
    CPUProgram(CPUProgram &prog); //copy constructor
    //read each line and add to instructions vector    
    bool ReadFile(const string fileName); //read file and fill instructions vector
    string getLine(int lineNum)const; //get instructions[line]
    int size()const; //get line of reading
    bool isOpen() const; //is file open
    int getOpt()const; //get option
    vector<string> &getIns(); //get instrotions
    void setIns(vector<string> vec); //set instructions
    string operator[](int index) const; //get line of index
    const CPUProgram operator+(const string line); //plus op
    const CPUProgram operator+(CPUProgram &prog); //plus op
    const CPUProgram operator+=(const string line); //plus & assign op
    CPUProgram &operator=(CPUProgram &prog); //assign op
    friend ostream &operator<<(ostream &output, const CPUProgram &prog);
    bool operator==(const CPUProgram &prog); //==
    bool operator!=(const CPUProgram &prog); //!=
    bool operator<(const CPUProgram &prog); //<
    bool operator>=(const CPUProgram &prog); //>=
    CPUProgram &operator--(); //dicrement
    const CPUProgram operator()(const int i1, const int i2); //func call
private:
    vector<string> instructions; //storage each line in file
    bool isOpenFile;//is open file for reading
    int option;//opt

};


#endif /* CPUPROGRAM_H */

