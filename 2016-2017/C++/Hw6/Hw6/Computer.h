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
#include "Memory.h"
#include "CPU.h"
#include "CPUProgramDyn.h"

using namespace std;
using namespace cpuprogram;

class Computer {
public:
    //take CPU,CPUProgramDyn Memory classes and option
    Computer(CPU processor, CPUProgramDyn prog, Memory mem, int opt);
    Computer(int opt);//take just option
    bool execute();//main execute function
    CPU getCPU();//get CPU member class
    CPUProgramDyn &getCPUProgram();//get CPUProgramDyn member class
    Memory getMemory();//get Memory member class
    void setCPU(CPU processor);//set CPU member class
    void setCPUProgram(CPUProgramDyn prog);//set CPUProgramDyn membver class
    void setMemory(Memory mem);//set Memory member class
private:
    CPU cpu;
    CPUProgramDyn program;
    Memory memory;
    int option;
    
};


#endif /* COMPUTER_H */

