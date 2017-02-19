/* 
 * File:   CPUProgram.h
 * Author: Şahin Eğilmez
 *
 * Created on 27 Ekim 2016 Perşembe, 11:21
 */

#ifndef CPUPROGRAMDYN_H
#define CPUPROGRAMDYN_H
#include <iostream>
#include <string>
#include <fstream>


using namespace std;



namespace cpuprogram {

    class CPUProgramDyn {
    public:
        CPUProgramDyn(int opt); //constructor take option
        CPUProgramDyn(const int opt, const string fileName); //constructor take filename
        CPUProgramDyn(int opt, string* insArr); //constructor take filename
        CPUProgramDyn(); //default constructor
        CPUProgramDyn(CPUProgramDyn &prog); //copy constructor
        //read each line and add to instructions vector    
        bool ReadFile(const string fileName); //read file and fill instructions vector
        string getLine(int lineNum)const; //get instructions[line]
        int size()const; //get line of reading
        void setSize(const int newSize);
        bool isOpen() const; //is file open
        int getOpt()const; //get option
        string* &getIns(); //get instrotions
        void setIns(string* insArr, int arrSize); //set instructions
        string operator[](int index) const; //get line of index
        const CPUProgramDyn operator+(const string line); //plus op
        const CPUProgramDyn operator+(CPUProgramDyn &prog); //plus op
        const CPUProgramDyn operator+=(const string line); //plus & assign op
        CPUProgramDyn &operator=(CPUProgramDyn &prog); //assign op
        friend ostream & operator << (ostream &output, const CPUProgramDyn &prog);
        bool operator==(const CPUProgramDyn &prog); //==
        bool operator!=(const CPUProgramDyn &prog); //!=
        bool operator<(const CPUProgramDyn &prog); //<
        bool operator>(const CPUProgramDyn &prog); //>
        bool operator<=(const CPUProgramDyn &prog); //<=
        bool operator>=(const CPUProgramDyn &prog); //>=
        CPUProgramDyn &operator--(); //dicrement
        const CPUProgramDyn operator()(const int i1, const int i2); //func call
    private:
        string* instructions; //storage each line in file
        bool isOpenFile; //is open file for reading
        int option; //opt
        int lenght; //size
        void push(const string &line);
        string pop();
    };
}


#endif /* CPUPROGRAMDYN_H */

