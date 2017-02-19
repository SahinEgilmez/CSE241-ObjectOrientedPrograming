/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Exception.h
 * Author: segilmez
 *
 * Created on 29 Aralık 2016 Perşembe, 20:49
 */

#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <iostream>
#include <string>
#include <exception>

using namespace std;

/*special exception*/
class MyException :public exception {
public:
    MyException(string str) {
        message = str;
    }

    virtual const char* what() const throw () {
        return message.c_str();
    }
    virtual ~MyException(){
        
    }
private:
    string message;
};


#endif /* EXCEPTION_H */

