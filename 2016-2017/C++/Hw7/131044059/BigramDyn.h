/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BigramDyn.h
 * Author: segilmez
 *
 * Created on 29 Aralık 2016 Perşembe, 15:03
 */

#ifndef BIGRAMDYN_H
#define BIGRAMDYN_H

#include <iostream>
#include <string>
#include <fstream>
#include <type_traits>
#include <exception>

#include "Bigram.h"

/*structre for dynamic memory */
template <class T>
struct bigram {
    pair<T, T> p;
    int count = 0;
    bool isSet = false;
};

using namespace std;

/*implemented Bigram abstract class with using dynamic memory*/
template <class T>
class BigramDyn : public Bigram<T> {
public:
    BigramDyn(int type);
    ~BigramDyn();
    bool readFile(const string filename) override;
    int numGrams()const override;
    int numOfGrams(T elem1, T elem2) override;
    pair<T, T> maxGrams() override;
    void print(std::ostream& output) override;
    bool setBg(const pair<T, T> p);
private:
    string erase(const string str, const char ch);
    T *datas;
    bigram<T> *bigrams;
    int elemCount = 0;
    int dataType;

};


#endif /* BIGRAMDYN_H */

