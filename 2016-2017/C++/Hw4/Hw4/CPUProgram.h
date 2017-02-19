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
    CPUProgram(const int opt); //constructor take option
    CPUProgram(const int opt, const string fileName); //constructor take filename
    CPUProgram();//default constructor
    //read each line and add to instructions vector    
    bool ReadFile(const string fileName);//read file and fill instructions vector
    string getLine(const int lineNum)const; //get instructions[line]
    int size()const; //get line of reading
    bool isOpen() const;//is file open

private:
    vector<string> instructions; //storage each line in file
    bool isOpenFile;
    int option;
};


#endif /* CPUPROGRAM_H */

