/* 
 * File:   main.cpp
 * Author: Şahin Eğilmez
 *
 * Created on 25 Ekim 2016 Pazar, 15:22
 */
#include <iostream>
#include <string>
#include <fstream>
#include "CPU.h"
#include "CPUProgram.h"
#include "Math.h"
#include "Memory.h"
#include "Computer.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    if (argc != 3) {
        cout << "Usage : yourProg filename option.\n  filename is txt file "
                "containing instruction.\n  option is 0, 1 or 2.\n";
        return 0;
    }
    Math math;//using strToInt. it is alternative to atoi. because teacher forbade.
    
    cout << "----TEST OF MEMORY CLASS------" << endl;
    Memory testMemory(math.strToInt(argv[2]));
    //Testing class Memory
    cout << "#0-> 100 : " << endl;
    testMemory.setMem(0, 100);
    testMemory.printAll();
    
    
    cout << "----TEST OF CPU CLASS------" << endl;
    CPU testCPU(math.strToInt(argv[2])); //mycpu
    cout << "execute 2 instructions = MOV #0,R2 and MOV R2,#1  : " << endl;
    testCPU.execute("MOV #0,R2", testMemory);
    testCPU.execute("MOV R2,#1", testMemory);
    testCPU.print();
    testMemory.printAll();
    
    cout << "----TEST OF CPUPROGRAM CLASS------" << endl;
    CPUProgram testProgram(0);
    //Testing class CPUProgram
    cout << "read instructions.txt and print first three line." << endl;
    testProgram.ReadFile("instructions.txt");
    for (int i = 0; i < 3; i++)
        cout << testProgram.getLine(i+1) << endl;

    Memory myMemory(math.strToInt(argv[2]));
    CPU myCPU(math.strToInt(argv[2]));
    CPUProgram myCPUProgram(math.strToInt(argv[2]));
    myCPUProgram.ReadFile(argv[1]);

    cout <<endl<< "----TEST OF COMPUTER MAIN CLASS------" << endl;
    //Testing class Computer
    cout << "read argv[2] and execute sort 10 number : " << endl<<endl;
    Computer myComputer1(myCPU, myCPUProgram, myMemory, math.strToInt(argv[2]));
    Computer myComputer2(math.strToInt(argv[2]));
    myComputer2.setCPU(myComputer1.getCPU());
    myComputer2.setCPUProgram(myComputer1.getCPUProgram());
    myComputer2.setMemory(myComputer1.getMemory());
    myComputer2.execute();

    return 1;
}







