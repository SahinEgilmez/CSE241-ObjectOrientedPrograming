/*HW8_SAHIN_EGILMEZ_131044059
 *
 * File:   main.cpp
 * Author: sahin
 *
 * Created on 20 Aralık 2015 Pazar, 20:17
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include "File.h"
#include "Directory.h"
#include "Executable.h"
#include "TextFile.h"

using namespace std;
using namespace FILES_GTU;
/*
 * 
 */
int main(int argc, char** argv) {
    Directory mydir1("Dir1", "Adminstrator"), mydir2("Dir2", "Adminstrator"), mydir3("Dir3", "Adminstrator");
    File file1("File1", "Sahin", 256), file2("File2", "Sahin", 512), file3("File3", "Sahin", 1024);
    Executable exec1("Exec1", "Sahin", 1024, "gcc"), exec2("Exec2", "Sahin", 512, "cygwin g++"), exec3("Exec3", "Sahin", 2048, "GNU Compiler");
    TextFile text1(".Text1", "Sahin", 512, "ASCII"), text2("Text2", "Sahin", 1024, "BINARY"), text3("Text3", "Sahin", 2048, "UNICODE");
    mydir1.cp(file1);
    mydir1.cp(exec1);
    mydir1.cp(text1);
    mydir2.cp(file2);
    mydir2.cp(exec2);
    mydir2.cp(text2);
    mydir3.cp(file3);
    mydir3.cp(exec3);
    mydir3.cp(text3);
    mydir2.cp(mydir3);
    mydir1.cp(mydir2);
    cout<<"TEST OF LS FUNCTİON (IF YOU WANT TRY DİFFERENT PARAMETERS, CHANGE IT.)"<<endl;
    mydir1.ls("Rl");
    return 0;
}

