/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BigramMap.h
 * Author: segilmez
 *
 * Created on 28 Aralık 2016 Çarşamba, 20:57
 */

#ifndef BIGRAMMAP_H
#define BIGRAMMAP_H
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <type_traits>
#include <vector>


#include "Bigram.h"

using namespace std;
/*implemented Bigram abstract class with using map*/
template <class T>
class BigramMap : public Bigram<T> {
public:
    BigramMap(int type);
    ~BigramMap();
    bool readFile(const string filename) override;
    int numGrams()const override;
    int numOfGrams(T elem1, T elem2) override;
    pair<T, T> maxGrams() override;
    void print(std::ostream& str) override;
    void setBg(const pair<T, T> p);
private:
    vector<T> datas;
    map<pair<T, T>, int> bigrams;
    int elemCount = 0;
    int dataType;

};


#endif /* BIGRAMMAP_H */

