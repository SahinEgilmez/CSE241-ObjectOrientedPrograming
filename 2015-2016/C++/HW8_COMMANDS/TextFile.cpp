/* HW8_SAHIN_EGILMEZ_131044059
 * File:   TextFile.cpp
 * Author: sahin
 *
 * Created on 21 Aralık 2015 Pazartesi, 22:38
 */
#include <cstdlib>
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include "File.h"
#include "TextFile.h"

using namespace std;

namespace FILES_GTU {

    TextFile::TextFile() : File() {
        this->code = "ASCII";
    }

    TextFile::TextFile(string strName, string strOwner, double size, string strCode) : File(strName, strOwner, size) {
        this->code = strCode;
    }

    TextFile::TextFile(const TextFile &text) : File(text) {
        this->code = text.getCode();
    }

    void TextFile::setCode(string str) {
        this->code = str;
    }

    string TextFile::getCode() const {
        return this->code;
    }

}