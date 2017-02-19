/* 
 * File:   cpu.cpp
 * Author: Şahin Eğilmez
 *
 * Created on 09 Ekim 2016 Pazar, 18:14
 */

#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include "cpu.h"

using namespace std;

/*read instruction from file and execute by using registers array*/
bool run(string fileName, int option, int registers[5], uint8_t memory[50]) {
    fstream file; //file stream
    string line; //each line 
    string instructions[3]; //instruction and register or constant
    string err = "Please use only MOV, SUB, ADD, JMP,JPN PRN, HLT instructions and"
            " R1, R2, R3, R4, R5 registers and memory adress by following the rules.";
    int optReg[4]; //opt[0] and opt[1] represeintation reg1,reg2. opt[3] for jmp
    /*file operation*/
    file.open(fileName.c_str());
    if (!file.is_open()) {
        cout << "Unable to open file";
        return false;
    } else {
        while (getline(file, line)) {//read each line
            /*set default value for strings*/
            instructions[0] = ".";
            instructions[1] = ".";
            instructions[2] = ".";
            /*line parsing and set instructions strings*/
            if (parser(line, instructions) < 0) {
                //cout<<"BURDAAAA"<<endl;

                cout << "ERROR: " << line << endl << err << endl;
                file.close();
                return false;
            }

            /*if instructions[2] is ".", instruction can't be prn,hlt*/
            if (instructions[2] != ".") {
                /*for mov,sub,add operation set optReg, because optRegwhich
                 *decides to use register*/
                if (!arithmetics(instructions[1], instructions[2], optReg)) {
                    cout << "ERROR: " << line << endl << err << endl;
                    file.close();
                    return false;
                }
                if (instructions[0] == "MOV") {//move
                    mov(registers, optReg, memory);
                } else if (instructions[0] == "ADD") {//addition
                    add(registers, optReg, memory);
                } else if (instructions[0] == "SUB") {//substract
                    sub(registers, optReg, memory);
                } else if (instructions[0] == "JMP" || instructions[0] == "JPN") { /*jumping diferent line,
                                                       * if register is zero*/
                    jmp(&file, fileName, instructions, registers, optReg, memory);
                } else {//error
                    cout << "ERROR:\n " << line << endl << err << endl;
                    file.close();
                    return false;
                }
                /*if instructions[1] is ".", instruction can't be mov,sub,add,hlt*/
            } else if (instructions[1] != ".") {//print
                if (instructions[0] == "PRN") {
                    prn(instructions[1], registers, memory);
                } else if (instructions[0] == "JMP" ) {//jumping different line
                    jmp(&file, fileName, instructions, registers, optReg, memory);
                } else {//error
                    cout << "ERROR:\n " << line << endl << err << endl;
                    file.close();
                    return false;
                }

            } else if (instructions[0] == "HLT") {//halting
                if (option == 1) {//display each instruction
                    cout << (line.substr(0, line.find(";"))) << " - ";
                    for (int i = 0; i < 5; i++)
                        cout << "R" << i + 1 << "=" << registers[i] << ", ";
                } else if (option == 2) {
                    cout << (line.substr(0, line.find(";"))) << " - ";
                    for (int i = 0; i < 50; i++)
                        cout << "#" << i + 1 << "=" << (int) memory[i] << ", ";
                }
                hlt(registers, memory);
                break;
            } else {//error
                cout << "ERROR:\n " << line << endl << err << endl;
                file.close();
                return false;
            }
            if (option == 1) {//display each instruction
                cout << (line.substr(0, line.find(";"))) << " - ";
                for (int i = 0; i < 5; i++)
                    cout << "R" << i + 1 << "=" << registers[i] << ", ";
                cout << endl;
            } else if (option == 2) {
                cout << (line.substr(0, line.find(";"))) << " - ";
                if (instructions[1].substr(0, 1) == "#")
                    cout << instructions[1].substr(0, instructions[1].size()) <<
                    "=" << (int) memory[strToInt(instructions[1].substr(1,
                        instructions[1].size() - 1)) - 1] << ", ";
                if (instructions[2].substr(0, 1) == "#")
                    cout << instructions[2].substr(0, instructions[2].size()) <<
                    "=" << (int) memory[strToInt(instructions[2].substr(1,
                        instructions[2].size() - 1)) - 1] << ", ";
                cout << endl;
            }

        }
        file.close(); //close file
    }

    return true;
}

/*read and parse each line to instructions array */
int parser(string line, string instructions[3]) {
    if (line.find(";") != string::npos)
        line = line.substr(0, line.find(";")); //erase comment
    line = erase(line, ' '); //erase white space
    instructions[0] = line.substr(0, 3); //instruction 1
    /*move, addition or substract*/

    if (instructions[0] == "MOV" || instructions[0] == "ADD" || instructions[0] == "SUB") {
        if (instructions[0] == "MOV" && line.substr(3, 1) == "#") {

            instructions[1] = line.substr(3, line.find(",") - 3);
            if (strToInt(instructions[1].substr(1, instructions[1].size() - 1)) > 49
                    || strToInt(instructions[1].substr(1, instructions[1].size() - 1)) < 1){
                    
                return -5;
        }
            instructions[2] = line.substr(line.find(",") + 1, line.size() - (instructions[1].size() + 4));
        } else if (line.substr(5, 1) == "," && line.substr(3, 1) != "#") {//pass ','
            instructions[1] = line.substr(3, 2);
            instructions[2] = line.substr(6, (line.size() - 6));
        } else {//error

            return -2;
        }
    } else if (instructions[0] == "JMP" || instructions[0] == "JPN") {//jumping
        if (line.size() >= 5 && line.substr(5, 1) == ",") {//pass ','
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

/*this function for mov,sub,add operation.optReg which decides to use register*/
bool arithmetics(string regFirst, string regSecond, int optReg[4]) {

    /*check which register and set optReg[0]*/
    if (regFirst.substr(0, 1) == "#") {
        optReg[0] = strToInt(regFirst.substr(1, regFirst.size() - 1)) - 1;
        optReg[2] = 1; //that means first command is adress.
    } else {
        optReg[2] = 0; //that means first command is register.
        if (regFirst == "R1") {
            optReg[0] = 0;
        } else if (regFirst == "R2")
            optReg[0] = 1;
        else if (regFirst == "R3")
            optReg[0] = 2;
        else if (regFirst == "R4")
            optReg[0] = 3;
        else if (regFirst == "R5")
            optReg[0] = 4;
        else//error
            return false;
    }
    /*check which register and set optReg[1].if it is integer, set optReg[2] is 1*/
    if (regSecond.substr(0, 1) == "#") {
        optReg[1] = strToInt(regSecond.substr(1, regSecond.size() - 1)) - 1;
        optReg[3] = 1; //that means second command is adress.
    } else {
        optReg[3] = 0; //that means second command is register.
        if (regSecond == "R1")
            optReg[1] = 0;
        else if (regSecond == "R2") {
            optReg[1] = 1;
        } else if (regSecond == "R3")
            optReg[1] = 2;
        else if (regSecond == "R4")
            optReg[1] = 3;
        else if (regSecond == "R5")
            optReg[1] = 4;
        else if (regSecond.find_first_not_of("0123456789") == string::npos) {
            optReg[3] = 2; //that means second command is constant.
            optReg[1] = strToInt(regSecond);
        } else//error
            return false;
    }
    return true; //succes
}

/*this function execute mov instruction.optReg which decides to use register */
void mov(int registers[5], int optReg[4], uint8_t memory[50]) {
    /*
    if (optReg[2] == 0 && optReg[3] == 0)
        registers[optReg[0]] = registers[optReg[1]]; //register = register
    else if (optReg[2] == 0 && optReg[3] == 1)
        registers[optReg[0]] = memory[optReg[1]]; //register = adress
    else if (optReg[2] == 0 && optReg[3] == 2)
        registers[optReg[0]] = optReg[1]; //register= constant
    else if (optReg[2] == 1 && optReg[3] == 0)
        memory[optReg[0]] = registers[optReg[1]]; // adress = register
    else if (optReg[2] == 1 && optReg[3] == 2)
        memory[optReg[0]] = optReg[1]; // adress = constant
    
    */
    if (optReg[2] == 0 && optReg[3] == 0)
        registers[optReg[1]] =registers[optReg[0]];
    else if (optReg[2] == 0 && optReg[3] == 1)
        memory[optReg[1]] = registers[optReg[0]];
    else if (optReg[2] == 0 && optReg[3] == 2)
        registers[optReg[0]] =optReg[1];
    else if (optReg[2] == 1 && optReg[3] == 0) {
        registers[optReg[1]] =memory[optReg[0]];  
    } else if (optReg[2] == 1 && optReg[3] == 2) {
        memory[optReg[0]] =optReg[1];
    }
    
}

/*this function execute add instruction.optReg which decides to use register */
void add(int registers[5], int optReg[4], uint8_t memory[50]) {
    if (optReg[2] == 0 && optReg[3] == 0)
        registers[optReg[0]] += registers[optReg[1]]; //register += register
    else if (optReg[2] == 0 && optReg[3] == 1)
        registers[optReg[0]] += memory[optReg[1]]; //register += adress
    else if (optReg[2] == 0 && optReg[3] == 2)
        registers[optReg[0]] += optReg[1]; //register += constant

}

/*this function execute sub instruction.optReg which decides to use register */
void sub(int registers[5], int optReg[4], uint8_t memory[50]) {
    if (optReg[2] == 0 && optReg[3] == 0)
        registers[optReg[0]] -= registers[optReg[1]]; //register -= register
    else if (optReg[2] == 0 && optReg[3] == 1)
        registers[optReg[0]] -= memory[optReg[1]]; //register -= adress
    else if (optReg[2] == 0 && optReg[3] == 2)
        registers[optReg[0]] -= optReg[1]; //register -= constant

}

/*jmp close file and open again.then go to the line by reading.*/
void jmp(fstream *file, string filename, string instructions[3], int registers[5], int optReg[4], uint8_t memory[50]) {
    string line; //each line
    int lineNum = 0; //number of row
    /*chaeck rules*/
    if ((instructions[0] == "JMP" && (instructions[2] == "." || (registers[optReg[0]] == 0)))
            || (instructions[0] == "JPN" && (instructions[2] == "." || (registers[optReg[0]] <= 0)))) {
        /*first of all, file close.in this way, file pointer is null */
        file->close();
        if (instructions[2] == ".")//Example : JMP 5
            lineNum = (strToInt(instructions[1]));
        else //Example : JMP R1, 5
            lineNum = strToInt(instructions[2]);
        /*open file. in this way, file read from the beginning */
        file->open(filename.c_str());
        for (int i = 1; i < lineNum; i++)
            if (getline(*file, line)) {//read each line until desired line number
                continue;
            }
    }
}

void hlt(int registers[5], uint8_t memory[50]) {
    cout << "   REGISTERS: ";
    for (int i = 0; i < 5; i++) {
        cout << "R" << i + 1 << "=" << registers[i] << ", ";
    }
    cout << "   MEMORY: ";
    for (int i = 0; i < 50; i++) {
        cout << "#" << i + 1 << "=" << (int) memory[i] << ", ";
    }
}

/*this function print to register or any integer value*/
void prn(string reg, int registers[5], uint8_t memory[50]) {
    /*check which register and print it. or print integer value*/
    if (reg.substr(0, 1) == "#") {
        cout << ((int) memory[strToInt(reg.substr(1, reg.size() - 1)) - 1 ]) << endl;
    } else if (reg == "R1")
        cout << (registers[0]) << endl;
    else if (reg == "R2")
        cout << (registers[1]) << endl;
    else if (reg == "R3")
        cout << (registers[2]) << endl;
    else if (reg == "R4")
        cout << (registers[3]) << endl;
    else if (reg == "R5")
        cout << (registers[4]) << endl;
    else if (reg.find_first_not_of("0123456789") == string::npos) {
        cout << strToInt(reg) << "\n";
    }
}

/*erase 'ch' in the str string following INSTRUCTIONS RULES*/
string erase(string str, char ch) {
    string res;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] != ch) {//parse each character and check it 
            res += str[i];
        }
    }

    return res;
}

/*converts string to integer. alternative atoi*/
int strToInt(string str) {
    int result = 0;
    for (int i = 0; i < str.size(); i++) {
        result = result + ((((int) str[i]) - '0') * pow(10, (str.size() - i - 1)));
    }
    return result;
}

/* 
 * take the integer mathemetics power. i1^i2. alternative cmath's pow
 * I don't want to <cmath>
 */
int pow(int i1, int i2) {
    int num = i1;
    if (i2 != 0) {//if power is 0, result is 1
        for (int i = i2; i > 1; i--) {
            i1 = i1* num;
        }
        return i1;
    } else
        return 1;

}
