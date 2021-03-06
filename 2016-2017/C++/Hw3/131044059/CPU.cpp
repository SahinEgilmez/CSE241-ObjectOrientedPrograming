/* 
 * File:   CPU.cpp
 * Author: Şahin Eğilmez
 *
 * Created on 27 Ekim 2016 Perşembe, 11:21
 */

#include <iostream>
#include <string>
#include <fstream>
#include "CPU.h"
#include "Math.h"

using namespace std;

CPU::CPU() {
    for (int i = 0; i < 5; i++)
        registers[i] = 0;
    PC = 1;
    option = 0;
    hlt = false;

}

CPU::CPU(const int opt) {
    for (int i = 0; i < 5; i++)
        registers[i] = 0;
    PC = 1;
    option = opt;
    hlt = false;
}

bool CPU::execute(string line) {
    string instructions[3]; //instruction and register or constant
    string err = "Please use only MOV, SUB, ADD, JMP, PRN, HLT instructions and"
            " R1, R2, R3, R4, R5 registers by following the rules.";
    int optReg[3]; //opt[0] and opt[1] represeintation reg1,reg2. opt[3] for jmp
    /*file operation*/
    /*set default value for strings*/
    instructions[0] = ".";
    instructions[1] = ".";
    instructions[2] = ".";
    /*line parsing and set instructions strings*/
    if (parser(line, instructions) < 0) {
        cout << "ERROR IN LINE " << getPC() << " : " << endl << line << endl << err << endl;
        return false;
    }
    /*if instructions[2] is ".", instruction can't be prn,hlt*/
    if (instructions[2] != ".") {
        /*for mov,sub,add operation set optReg, because optRegwhich
         *decides to use register*/
        if (!arithmetics(instructions[1], instructions[2], optReg)) {
            cout << "ERROR IN LINE " << getPC() << " : " << endl << line << endl << err << endl;
            return false;
        }
        if (instructions[0] == "MOV") {//move
            mov(optReg);
        } else if (instructions[0] == "ADD") {//addition
            add(optReg);
        } else if (instructions[0] == "SUB") {//substract
            sub(optReg);
        } else if (instructions[0] == "JMP") {//jumping different line
            //cout << "girdik" << endl;
            jmp(instructions, optReg);

        } else {//error
            cout << "ERROR IN LINE " << getPC() << " : " << endl << line << endl << err << endl;
            return false;
        }
        /*if instructions[1] is ".", instruction can't be mov,sub,add,hlt*/
    } else if (instructions[1] != ".") {//print
        if (instructions[0] == "PRN") {
            prn(instructions[1]);
        } else if (instructions[0] == "JMP") {/*jumping diferent line,
                                                       * if register is zero*/
            jmp(instructions, optReg);

        } else {//error
            cout << "ERROR IN LINE " << getPC() << " : " << endl << line << endl << err << endl;
            return false;
        }

    } else if (instructions[0] == "HLT") {//halting
        setHlt(true);
        if (getOption() == 1)//display each instruction
            cout << (line.substr(0, line.find(";"))) << " - R1=" <<
            getR1() << ", R2=" << getR2() << ", R3=" <<
            getR3() << ", " "R4=" << getR4() << ", R5=" <<
            getR5() << "\n";

    } else {//error
        cout << "ERROR IN LINE " << getPC() << " : " << endl << line << endl << err << endl;
        return false;
    }
    optReg[2] = 0; //for jmp
    if (getOption() == 1)//display each instruction
        cout << (line.substr(0, line.find(";"))) << " - R1=" <<
        getR1() << ", R2=" << getR2() << ", R3=" <<
        getR3() << ", " "R4=" << getR4() << ", R5=" <<
        getR5() << endl;

    setPC(getPC() + 1); //increase Program Counter

    return true;
}

bool CPU::halted()const {
    return getHlt();
}

void CPU::print()const {
    cout << "R1=" << getR1() << ", R2=" << getR2() << ", R3=" <<
            getR3() << ", " "R4=" << getR4() << ", R5=" <<
            getR5() << ", PC= " << getPC() << endl;
}

int* const CPU::getRegisters() {
    return registers;
}

int CPU::getRegWithPos(const int reg) const {
    if (reg >= 1 && reg <= 5) {
        return registers[reg - 1];
    } else
        return -1;

}

int CPU::getR1()const {
    return registers[0];
}

int CPU::getR2()const {
    return registers[1];
}

int CPU::getR3()const {
    return registers[2];
}

int CPU::getR4()const {
    return registers[3];
}

int CPU::getR5()const {
    return registers[4];
}

int CPU::getOption()const {
    return option;
}

int CPU::getPC()const {
    return PC;
}

bool CPU::getHlt() const {
    return hlt;
}
Math CPU::getMath(){
    return math;
}

void CPU::setRegisters(const int r1, const int r2, const int r3, const int r4, const int r5) {
    registers[0] = r1;
    registers[1] = r2;
    registers[2] = r3;
    registers[3] = r4;
    registers[4] = r5;
}

bool CPU::setRegWithPos(const int reg, const int num) {
    if (reg >= 1 && reg <= 5) {
        registers[reg - 1] = num;
        return true;
    } else
        return false;
}

void CPU::setR1(const int num) {
    registers[0] = num;
}

void CPU::setR2(const int num) {
    registers[1] = num;
}

void CPU::setR3(const int num) {
    registers[2] = num;
}

void CPU::setR4(const int num) {
    registers[3] = num;
}

void CPU::setR5(const int num) {
    registers[4] = num;
}

void CPU::setPC(const int num) {
    PC = num;
}

void CPU::setHlt(const bool val) {
    hlt = val;
}

bool CPU::checkError(string line) {
    int i = 0;
    string str = "";
    while (i < line.size()) {
        if (line[i] != ' ') {
            break;
        }
        i++;
    }
    str = line.substr(i, 3);
    if (!(str == "MOV" || str == "ADD" || str == "SUB" || str == "JMP" ||
            str == "PRN" || str == "HLT"))
        return true;
    i = i + 3;
    while (i < line.size()) {
        if (line[i] != ' ') {
            break;
        }
        i++;
    }
    if (line[i] == 'R' && !((getMath().strToInt(line.substr(i + 1, 1)) > 0) && (getMath().strToInt(line.substr(i + 1, 1)) < 6))) {
        return true;
    }

    return false;
}

int CPU::parser(string line, string instructions[3]) {
    if (checkError(line))
        return -5;
    if (line.find(";") != string::npos)
        line = line.substr(0, line.find(";")); //erase comment
    line = erase(line, ' '); //erase white space
    instructions[0] = line.substr(0, 3); //instruction 1
    /*move, addition or substract*/
    if (instructions[0] == "MOV" || instructions[0] == "ADD" || instructions[0] == "SUB") {
        if (line.substr(5, 1) == ",") {//pass ','
            instructions[1] = line.substr(3, 2);
            instructions[2] = line.substr(6, (line.size() - 6));
        } else {//error
            return -2;
        }
    } else if (instructions[0] == "JMP") {//jumping
        if (line.size() >= 5 && line.substr(5, 1) == ",") {//pass','
            instructions[1] = line.substr(3, 2);
            if (line.substr(6, (line.size() - 6)).find_first_not_of("0123456789") == string::npos)
                instructions[2] = line.substr(6, (line.size() - 6));
            else//error
                return -3;
        } else {//check second register is integer for jumping
            if (line.substr(3, (line.size() - 3)).find_first_not_of("0123456789") == string::npos)
                instructions[1] = line.substr(3, (line.size() - 3));
            else//error
                return -4;
        }
    } else if (instructions[0] == "PRN") {//print
        instructions[1] = line.substr(3, (line.size() - 3));
    } else if (instructions[0] == "HLT") {//halting
    } else {//error
        return -1;
    }
    return 1; //succes
}

bool CPU::arithmetics(const string regFirst, const string regSecond, int optReg[]) {
    /*check which register and set optReg[0]*/
    if (regFirst == "R1") {
        optReg[0] = 1;
    } else if (regFirst == "R2")
        optReg[0] = 2;
    else if (regFirst == "R3")
        optReg[0] = 3;
    else if (regFirst == "R4")
        optReg[0] = 4;
    else if (regFirst == "R5")
        optReg[0] = 5;
    else//error
        return false;
    /*check which register and set optReg[1].if it is integer set optReg[2] is 1*/
    if (regSecond == "R1")
        optReg[1] = 1;
    else if (regSecond == "R2") {
        optReg[1] = 2;
    } else if (regSecond == "R3")
        optReg[1] = 3;
    else if (regSecond == "R4")
        optReg[1] = 4;
    else if (regSecond == "R5")
        optReg[1] = 5;
    else if (regSecond.find_first_not_of("0123456789") == string::npos) {
        optReg[2] = 1;
        optReg[1] = getMath().strToInt(regSecond);
    } else//error
        return false;
    return true; //succes
}

void CPU::mov(const int optReg[]) {
    if (optReg[2] != 1)
        setRegWithPos(optReg[0], getRegWithPos(optReg[1])); //register = register
    else
        setRegWithPos(optReg[0], optReg[1]); //register= integer
}

void CPU::add(const int optReg[]) {
    if (optReg[2] != 1)//register =+register
        setRegWithPos(optReg[0], getRegWithPos(optReg[0]) + getRegWithPos(optReg[1]));
    else//register+ integer
        setRegWithPos(optReg[0], getRegWithPos(optReg[0]) + optReg[1]);
}

void CPU::sub(const int optReg[]) {
    if (optReg[2] != 1)//register =+register
        setRegWithPos(optReg[0], getRegWithPos(optReg[0]) - getRegWithPos(optReg[1]));
    else//register+ integer
        setRegWithPos(optReg[0], getRegWithPos(optReg[0]) - optReg[1]);
}

void CPU::jmp(const string instructions[], const int optReg[]) {
    /*chaeck rules*/
    if (instructions[2] == "." || (getRegWithPos(optReg[0]) == 0)) {
        if (instructions[2] == ".")//Example : JMP 5
            setPC(getMath().strToInt(instructions[1]) - 1);
        else //Example : JMP R1, 5
            setPC(getMath().strToInt(instructions[2]) - 1);
    }
}

void CPU::prn(string reg) {
    /*check which register and print it. or print integer value*/
    if (reg == "R1")
        cout << getR1() << "\n";
    else if (reg == "R2")
        cout << getR2() << "\n";
    else if (reg == "R3")
        cout << getR3() << "\n";
    else if (reg == "R4")
        cout << getR4() << "\n";
    else if (reg == "R5")
        cout << getR5() << "\n";
    else if (reg.find_first_not_of("0123456789") == string::npos) {
        cout << getMath().strToInt(reg) << endl;
    }
}

/*erase 'ch' in the str string.alternative string.erase*/
string CPU::erase(const string str, const char ch) {
    string res;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] != ch) {//parse each character and check it 
            res += str[i];
        }
    }
    return res;
}






