/* HW8_SAHIN_EGILMEZ_131044059
 * File:   Executable.h
 * Author: sahin
 *
 * Created on 21 Aralık 2015 Pazartesi, 22:34
 */

#ifndef EXECUTABLE_H
#define	EXECUTABLE_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <cstdlib>
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include "File.h"

    using namespace std;

    namespace FILES_GTU {
        class Executable : public File {
        public:
            Executable();//Default constructors
            Executable(string strName, string strOwner, double size, string strCompiler);
            //Constructor with parameters
            Executable(const Executable &exec);//Copy constructor
            void setCompiler(string str);//set compiler type that compiling this file
            string getCompiler()const;//get compiler type
        protected:
            string compiler;//take the compiler type
        };
    }

#ifdef	__cplusplus
}
#endif

#endif	/* EXECUTABLE_H */

