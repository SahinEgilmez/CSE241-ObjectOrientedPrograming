/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Math.h
 * Author: segilmez
 *
 * Created on 27 Ekim 2016 Perşembe, 22:22
 */

#ifndef MATH_H
#define MATH_H

#include <string>

using namespace std;

class Math {
public:
    /*Bu fonksiyonlar argv[2] yi integer a çevirmek içindir. Hoca atoi
  kullandırtmadığı için yazılmıştır*/
    /* 
     * take the integer mathemetics power. i1^i2. alternative cmath's pow
     * I don't want to <cmath>
     */
    int pow(int i1, int i2);
    /*converts string to integer. alternative atoi*/
    int strToInt(const string str);
};


#endif /* MATH_H */

