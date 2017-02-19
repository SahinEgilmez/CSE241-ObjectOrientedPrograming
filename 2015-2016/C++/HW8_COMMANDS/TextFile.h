/* HW8_SAHIN_EGILMEZ_131044059
 * File:   TextFile.h
 * Author: sahin
 *
 * Created on 21 Aralık 2015 Pazartesi, 22:38
 */

#ifndef TEXTFILE_H
#define	TEXTFILE_H
#include <cstdlib>
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include "File.h"

using namespace std;

namespace FILES_GTU {
    class TextFile : public File {
    public:
        TextFile();//Default constructors
        TextFile(string strName, string strOwner, double size, string strCode);
        //Constructors with parameters
        TextFile(const TextFile &text);//Copy constructors
        void setCode(string str);//set code type
        string getCode()const;//get code type
    protected:
        string code;//take the code type
    };

}

#endif	/* TEXTFILE_H */

