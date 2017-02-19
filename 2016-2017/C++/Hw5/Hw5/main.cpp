/* 
 * File:   main.cpp
 * Author: Şahin Eğilmez
 *
 * Created on 13 Kasım 2016 Pazar, 15:22
 */
#include "requiredIncs.h"

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
    //command line parameters
    const char* filename = argv[1];
    int option = atoi(argv[2]);
    //////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////
    //Testing class CPUProgram
    //op []
    CPUProgram myCPUProgram(option);
    myCPUProgram.ReadFile(filename);
    cout << myCPUProgram[0] << endl;
    cout << "Size : " << myCPUProgram[myCPUProgram.size() - 1] << endl;

    //op +
    CPUProgram newCpuProgram(option);
    //op +
    cout << ((myCPUProgram + "MOV R1, #45")[myCPUProgram.size() - 1]) << endl;

    //op +=
    myCPUProgram += "MOV R2, #50";
    cout << myCPUProgram[myCPUProgram.size() - 1] << endl;

    //op + <<
    CPUProgram myOtherCPUProgram(option);
    myOtherCPUProgram.ReadFile(filename);
    cout << (myCPUProgram + myOtherCPUProgram) << endl;

    myOtherCPUProgram += "MOV R2, #20"; //Bu olmazsa == FAİL olur hocam
    //op COMP--
    cout << (myCPUProgram == myOtherCPUProgram ? "DONE" : "FAIL") << endl;
    cout << (myCPUProgram >= myOtherCPUProgram ? "DONE" : "FAIL") << endl;
    cout << (myCPUProgram < myOtherCPUProgram ? "FAIL" : "DONE") << endl;


    --myOtherCPUProgram;
    cout << (myCPUProgram != myOtherCPUProgram ? "DONE" : "FAIL") << endl;
    cout << (myCPUProgram >= myOtherCPUProgram ? "DONE" : "FAIL") << endl;
    cout << (myCPUProgram < myOtherCPUProgram ? "FAIL" : "DONE") << endl;

    //op ()
    cout << myCPUProgram(5, 10) << endl;

    //error check
    cout << myCPUProgram[myCPUProgram.size()] << endl;
    myCPUProgram += "";
    cout << myCPUProgram[myCPUProgram.size() - 1 ] << endl;
    //////////////////////////////////////////////////////////////////////////

    return 1;
}







