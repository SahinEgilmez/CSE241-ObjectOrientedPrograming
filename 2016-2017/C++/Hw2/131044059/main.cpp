
/* 
 * File:   main.cpp
 * Author: Şahin Eğilmez 
 *
 * Created on 15 Ekim 2016 Cumartesi, 15:22
 */

#include <iostream>
#include <string>
#include <fstream>
#include "cpu.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    if (argc != 3 || (strToInt(argv[2]) != 0 && strToInt(argv[2]) != 1) &&
            strToInt(argv[2]) != 2) {
        cout << "Usage : ./cpu filename option.\n  filename is txt file "
                "containing instruction.\n  option is 0 , 1 or 2.\n";
        return 1;
    } else {
        int registers[5];
        uint8_t memory[50];
        for (int i = 0; i < 5; i++)
            registers[i] = 0;
        for (int i = 0; i < 50; i++)
            memory[i] = 0;
        run(argv[1], strToInt(argv[2]), registers, memory);

        return 0;
    }
}

