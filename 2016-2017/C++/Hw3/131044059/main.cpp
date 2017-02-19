/* 
 * File:   main.cpp
 * Author: Şahin Eğilmez
 *
 * Created on 25 Eylül 2016 Pazar, 15:22
 */

#include <iostream>
#include <string>
#include <fstream>
#include "CPU.h"
#include "CPUProgram.h"
#include "Math.h"
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    if (argc != 3 ) {
        cout << "Usage : yourProg filename option.\n  filename is txt file "
                "containing instruction.\n  option is 0 or 1.\n";
        return 0;
    } 
    Math math;//for string to int
    CPUProgram myProg(argv[1]);//my program
    CPU myCPU(math.strToInt(argv[2]));//mycpu
    if (!(myProg.isOpen()))//check file opening
        return 0;
    if (!(myCPU.getOption() == 0 || myCPU.getOption() == 1)) {//check option
        cout << "Option must be 0 or 1 " << endl;
        return 0;
    }
    while (!myCPU.halted()) {//check HLT
        string instruction = myProg.getLine(myCPU.getPC());//ger instruction
        if (!(myCPU.execute(instruction)))//runtime error
            return 0; //
    }

    return 1;
}







