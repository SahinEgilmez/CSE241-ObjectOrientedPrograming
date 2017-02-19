/*HW8_SAHIN_EGILMEZ_131044059
 *  
 * File:   File.cpp
 * Author: sahin
 *
 * Created on 20 Aralık 2015 Pazar, 21:22
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include "File.h"

using namespace std;

namespace FILES_GTU {

    File::File() {
        this->name = "File";
        this->owner = "Not Owner";
        this->size = 0;
        time_t t = time(0);
        this->lastModification = ctime(&t);
        this->ownDirectory = NULL;
    }

    File::File(string strName, string strOwner, double valSize) {
        this->name = strName;
        this->owner = strOwner;
        this->size = valSize;
        time_t t = time(0);
        this->lastModification = ctime(&t);
        this->ownDirectory = NULL;
    }

    File::File(const File &f) {
        this->name = f.getName();
        this->owner = f.getOwner();
        this->size = f.getSize();
        this->lastModification = f.getLastModification();
        this->ownDirectory = f.getOwnDirectory();
    }

    void File::setName(string str) {
        this->name = str;
    }

    string File::getName()const {
        return this->name;
    }

    void File::setOwner(string str) {
        this->owner = str;
    }

    string File::getOwner()const {
        return this->owner;
    }

    void File::setSize(double sizeNum) {
        this->size = sizeNum;
    }

    double File::getSize()const {
        return this->size;
    }

    void File::setLastModification() {
        time_t t = time(0);
        this->lastModification = ctime(&t);
    }

    string File::getLastModification()const {
        return this->lastModification;
    }

    string File::path() {
        string strPath;
        if (this->ownDirectory == NULL) {
            strPath = ("./" + this->getName());
            return strPath;
        } else {
            strPath = ((*ownDirectory).path() + "/" + this->getName());
            return strPath;
        }
    }

    void File::ls(string str) {
        cout << "This is not directory!This function use only directory." << endl;
    }

    File* File::cd() {
        return this;
    }

    bool File::cp(File &f) {
        cout << "This is not directory!This function use only directory." << endl;
    }

    void File::setOwnDirectory(File* f) {
        this->ownDirectory = f;
    }

    File* File::getOwnDirectory()const {
        return (this->ownDirectory);
    }

}
