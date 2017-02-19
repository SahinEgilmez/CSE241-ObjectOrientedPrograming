/*HW8_SAHIN_EGILMEZ_131044059
 * File:   Directory.h
 * Author: sahin
 *
 * Created on 21 Aralık 2015 Pazartesi, 22:32
 */

#ifndef DIRECTORY_H
#define	DIRECTORY_H

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

        class Directory : public File {
        public:
            Directory(); //Default Constructor
            Directory(string strName, string strOwner); //Constructor with parameter
            Directory(const Directory &d); //copy constructor
            bool cp(File &f); //deep copy file in this directory
            bool cp(Directory &d); //deep copy directory in this directory
            virtual void ls(string str); //ls function with parameters.If parameter is
            //R, call recersive function and print to all subfolders.If parameter 
            //is l, print just this directory's files and folders.If parameters
            //is a,print just this directory's files and folders with hidden 
            //folder(the first letter is '.').Otherwise, you can use 3 parameters
            // at the same time.In this case, function perform all probabilities
            //in respectively.
            virtual void ls(); //ls function with no parameters
            void lsRec(string str); //ls function at recursivly
        protected:
            vector<Directory> directories; //take the sub directories
            vector<File> files; //take the sub files
        };
    }

#ifdef	__cplusplus
}
#endif

#endif	/* DIRECTORY_H */

