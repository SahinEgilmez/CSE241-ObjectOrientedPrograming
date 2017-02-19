/* 
 * File:   Computer.h
 * Author: segilmez
 *
 * Created on 06 Kasım 2016 Pazar, 18:59
 */

#ifndef COMPUTER_H
#define COMPUTER_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Math.h"
#include "Memory.h"
#include "CPU.h"
#include "CPUProgram.h"

using namespace std;

class Computer {
public:
    //take CPU,CPUProgram Memory classes and option
    Computer(CPU processor, CPUProgram prog, Memory mem, int opt);
    Computer(int opt);//take just option
    bool execute();//main execute function
    CPU getCPU();//get CPU member class
    CPUProgram getCPUProgram();//get CPUProgram member class
    Memory getMemory();//get Memory member class
    void setCPU(CPU processor);//set CPU member class
    void setCPUProgram(CPUProgram prog);//set CPUProgram membver class
    void setMemory(Memory mem);//set Memory member class
private:
    CPU cpu;
    CPUProgram program;
    Memory memory;
    int option;
    
};


#endif /* COMPUTER_H */

