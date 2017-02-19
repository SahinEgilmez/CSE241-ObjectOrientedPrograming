/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Bigram.h
 * Author: segilmez
 *
 * Created on 28 Aralık 2016 Çarşamba, 20:18
 */

#ifndef BIGRAM_H
#define BIGRAM_H
#include <iostream>
#include <string>
#include <fstream>
#include <exception>
#include "Exception.h"
#include <typeinfo>
using namespace std;



/*This is template Bigram pure abstract class*/
template <class T>
class Bigram {
public:
    /*read file and set data */
    virtual bool readFile(const string filename) = 0;
    /*return count of numbers*/
    virtual int numGrams() const = 0;
    /*return maximum Bigram pair*/
    virtual std::pair<T, T> maxGrams()  = 0;
    /*retturn(elem1,elem2) Bigrams pair*/
    virtual int numOfGrams(T elem1, T elem2) = 0;
    /*ostream operator helper*/
    virtual void print(std::ostream& output) = 0;
    /*operator overloaded*/
    friend std::ostream& operator<<(std::ostream& str, Bigram & bg) {
        bg.print(str);
        return str;
    }
    
};





#endif /* BIGRAM_H */

