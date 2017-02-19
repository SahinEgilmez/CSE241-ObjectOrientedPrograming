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
    CPUProgram(const string fileName);//constructor take filename
    //read each line and add to instructions vector    
    bool readFile(const string fileName);
    string getLine(const int lineNum)const;//get instructions[line]
    int size()const;//get line of reading
    bool isOpen() const;

private:
    vector<string> instructions;//storage each line in file
    bool isOpenFile;
};


#endif /* CPUPROGRAM_H */

