/*HW8_SAHIN_EGILMEZ_131044059
 *  
 * File:   File.h
 * Author: sahin
 *
 * Created on 20 Aralık 2015 Pazar, 21:22
 */

#ifndef FILE_H
#define	FILE_H


#include <cstdlib>
#include <iostream>
#include <string>
#include <ctime>
#include <vector>

using namespace std;

namespace FILES_GTU {

    class File {
    public:
        File();//Default Construtor
        File(string strName, string strOwner, double valSize);//Construtor with
        File(const File &f);//Copy constructor
        void setName(string str);//set name
        string getName()const;//get name
        void setOwner(string str);//set owner name
        string getOwner()const;//get owner name
        void setSize(double sizeNum);//set file size
        double getSize()const;//get file size
        void setLastModification();//set last modification time at automatically
        string getLastModification()const;//get last modification time
        string path();//get file path in computer
        virtual void ls(string str);//ls function dont call in file,just for directory
        File* cd();//return the this pointer
        virtual bool cp(File &f);//cp dont call in file,just for directory
        void setOwnDirectory(File* f);//set owner directory pointer
        File* getOwnDirectory()const;//get owner directory pointer
    protected:
        string name;//take name
        string owner;//take owner name
        double size;//take size
        string lastModification;//take last modification time
        File* ownDirectory;//take the owner directory pointer
    };
}

#endif	/* FILE_H */

