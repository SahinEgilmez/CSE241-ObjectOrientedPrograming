/*HW8_SAHIN_EGILMEZ_131044059
 * File:   Directory.cpp
 * Author: sahin
 *
 * Created on 21 Aralık 2015 Pazartesi, 22:32
 */
#include <cstdlib>
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include "File.h"
#include "Directory.h"

using namespace std;


namespace FILES_GTU {

    Directory::Directory() : File() {
        this->name = ("Directory");
    }

    Directory::Directory(string strName, string strOwner) : File(strName, strOwner, 0) {
    }

    Directory::Directory(const Directory &d) : File() {
        this->files.resize(d.files.size());
        this->directories.resize(d.directories.size());
        for (int i = 0; i < d.files.size(); i++) {
            files[i] = d.files[i];
            this->files[i].setOwnDirectory(this);
        }
        for (int i = 0; i < d.directories.size(); i++) {
            directories[i] = d.directories[i];
            this->directories[i].setOwnDirectory(this);
        }

        this->name = d.getName();
        this->size = d.getSize();
        this->owner = d.getOwner();
        this->ownDirectory = (d.getOwnDirectory());
    }

    bool Directory::cp(File &f) {
        File file(f);
        file.setOwnDirectory(this);
        this->setSize(file.getSize() + this->getSize());
        this->files.push_back(file);
        return true;
    }

    bool Directory::cp(Directory &d) {
        Directory dir(d);
        dir.setOwnDirectory(this);
        this->setSize(dir.getSize() + this->getSize());
        this->directories.push_back(dir);
        return true;
    }

    void Directory::ls(string str) {
        for (int i = 0; i < str.size(); i++) {
            if (str.c_str()[i] == 'R') {
                cout << this->path() << " : " << endl;
                for (int i = 1; i <= this->files.size(); i++) {
                    if (files[i - 1].getName().c_str()[0] != '.') {
                        cout << files[i - 1].getName() << " " << files[i - 1].getOwner() <<
                                " " << files[i - 1].getSize() << " " << files[i - 1].getLastModification() << endl;
                    }
                }
                for (int i = 1; i <= this->directories.size(); i++) {
                    if (directories[i - 1].getName().c_str()[0] != '.') {
                        cout << directories[i - 1].getName() << " " << directories[i - 1].getOwner() <<
                                " " << directories[i - 1].getSize() << " " << directories[i - 1].getLastModification() << endl;
                    }
                    directories[i - 1].lsRec(str);

                }
            } else if (str.c_str()[i] == 'l') {
                cout << this->path() << " : " << endl;
                for (int i = 1; i <= this->files.size(); i++) {
                    if (files[i - 1].getName().c_str()[0] != '.') {
                        cout << files[i - 1].getName() << " -rwx " << files[i - 1].getOwner() <<
                                " " << files[i - 1].getSize() << " " << files[i - 1].getLastModification() << endl;
                    }
                }
                for (int i = 1; i <= this->directories.size(); i++) {
                    if (directories[i - 1].getName().c_str()[0] != '.') {
                        cout << directories[i - 1].getName() << " -rwx " << directories[i - 1].getOwner() <<
                                " " << directories[i - 1].getSize() << " " << directories[i - 1].getLastModification() << endl;
                    }
                }

            } else if (str.c_str()[i] == 'a') {
                cout << this->path() << " : " << endl;
                for (int i = 1; i <= this->files.size(); i++) {
                    cout << files[i - 1].getName() << " " << files[i - 1].getOwner() <<
                            " " << files[i - 1].getSize() << " " << files[i - 1].getLastModification() << endl;
                }
                for (int i = 1; i <= this->directories.size(); i++) {

                    cout << directories[i - 1].getName() << " " << directories[i - 1].getOwner() <<
                            " " << directories[i - 1].getSize() << " " << directories[i - 1].getLastModification() << endl;
                }

            }else{
                cout<<"Yanlış parametre girdiniz.Lütfen R,l ve ya a parametrelerinden "<<
                        "seçtikleriniz giriniz!"<<endl;
            }
        }
    }

    void Directory::ls() {
        cout << this->path() << " : " << endl;
        for (int i = 1; i <= this->files.size(); i++) {
            if (files[i - 1].getName().c_str()[0] != '.') {
                cout << files[i - 1].getName() << "  " << files[i - 1].getOwner() <<
                        " " << files[i - 1].getSize() << " " << files[i - 1].getLastModification() << endl;
            }
        }
        for (int i = 1; i <= this->directories.size(); i++) {
            if (directories[i - 1].getName().c_str()[0] != '.') {
                cout << directories[i - 1].getName() << "  " << directories[i - 1].getOwner() <<
                        " " << directories[i - 1].getSize() << " " << directories[i - 1].getLastModification() << endl;
            }
        }
    }

    void Directory::lsRec(string str) {
        cout << this->path() << " : " << endl;
        for (int i = 1; i <= this->files.size(); i++) {
            if (files[i - 1].getName().c_str()[0] != '.') {
                cout << files[i - 1].getName() << " " << files[i - 1].getOwner() <<
                        " " << files[i - 1].getSize() << " " << files[i - 1].getLastModification() << endl;
            }
        }
        for (int i = 1; i <= this->directories.size(); i++) {
            if (directories[i - 1].getName().c_str()[0] != '.') {
                cout << directories[i - 1].getName() << " " << directories[i - 1].getOwner() <<
                        " " << directories[i - 1].getSize() << " " << directories[i - 1].getLastModification() << endl;
            }
            directories[i - 1].lsRec(str);

        }
    }

}