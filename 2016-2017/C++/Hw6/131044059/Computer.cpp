/* 
 * File:   Computer.cpp
 * Author: segilmez
 *
 * Created on 06 Kasım 2016 Pazar, 18:59
 */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Memory.h"
#include "CPU.h"
#include "CPUProgramDyn.h"
#include "Computer.h"


using namespace std;
using namespace cpuprogram;


Computer::Computer(CPU processor, CPUProgramDyn prog, Memory mem, int opt) {
    cpu = processor;
    program = prog;
    memory = mem;
    option = opt;
}

Computer::Computer(int opt) {
    option = opt;
}

bool Computer::execute() {
    CPU exeCpu=getCPU();
    CPUProgramDyn exeProgram= getCPUProgram();
    Memory exeMemory= getMemory();
    if (!(exeProgram.isOpen()))//check file opening
        return false;
    if (!(exeCpu.getOption() >= 0 && exeCpu.getOption() <= 2)) {//check option
        cout << exeCpu.getOption() << "Option must be 0 ,1 or 2. " << endl;
        return false;
    }
    while (!exeCpu.halted()) {//check HLT
        string instruction = exeProgram.getLine(exeCpu.getPC()); //get instruction
        if (!(exeCpu.execute(instruction, exeMemory)))//runtime error
            return false; //
    }
    return true;
}

CPU Computer::getCPU() {
    return cpu;
}

CPUProgramDyn &Computer::getCPUProgram() {
    return program;
}

Memory Computer::getMemory() {
    return memory;
}

void Computer::setCPU(CPU processor) {
    cpu = processor;
}

void Computer::setCPUProgram(CPUProgramDyn prog) {
    program = prog;
}

void Computer::setMemory(Memory mem) {
    memory = mem;
}






