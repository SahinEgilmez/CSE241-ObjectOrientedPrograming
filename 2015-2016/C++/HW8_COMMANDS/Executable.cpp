/* HW8_SAHIN_EGILMEZ_131044059
 * File:   Executable.cpp
 * Author: sahin
 *
 * Created on 21 Aralık 2015 Pazartesi, 22:34
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include "File.h"
#include "Executable.h"

using namespace std;

namespace FILES_GTU {

    Executable::Executable() : File() {
        this->compiler = "g++ 5.0.1";
    }

    Executable::Executable(string strName, string strOwner, double size, string strCompiler) : File(strName, strOwner, size) {
        this->compiler = strCompiler;
    }

    Executable::Executable(const Executable& exec) : File(exec) {
        this->compiler = exec.getCompiler();
    }

    void Executable::setCompiler(string str) {
        this->compiler = str;
    }

    string Executable::getCompiler() const {
        return this->compiler;
    }

}