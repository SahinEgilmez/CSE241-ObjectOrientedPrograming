/* HW7_SAHIN_EGILMEZ_131044059
 * File:   Numbers.h
 * Author: sahin
 *
 * Created on 16 Aralık 2015 Çarşamba, 13:57
 */

#ifndef NUMBERS_H
#define	NUMBERS_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>

using namespace std;
namespace NUMBERS_GTU_SAHIN_EGILMEZ {
    //This class of namespace represent all numbers.The base class is Complex 
    //Numbers.Others are derived class.
   
    class ComplexNumber {//this class represent complex numbers
    public:
        ComplexNumber(double a, double b);//constructor for complex number
        virtual ~ComplexNumber();//destructor for numbers
        void setReal(const double num);//setter function for real part from number
        double getReal()const;//getter function for imaginary part from number
        void setImag(const double num);//setter for imaginary part from number
        double getImag()const;//getter for imaginary part from number
        virtual ComplexNumber operator+(const ComplexNumber &num)const;//add
        virtual ComplexNumber operator-(const ComplexNumber &num)const;//sub
        bool operator<(const ComplexNumber &num);//comparison overloaded
        bool operator>(const ComplexNumber &num);//comparision overloaded
        friend ostream &operator<<(ostream &output, const ComplexNumber &num);//
        //stream insertiom operator overloading for complex number
    protected:
        double real;//represent real number
        double imaginary;//represent imaginary number
    };

    class ImaginaryNumber : public ComplexNumber {//this class only imaginary 
        //number in complex number
    public:
        ImaginaryNumber(double b);//constructor
    };

    class RealNumber : public ComplexNumber {//this class represent real numbers
        //imaginary part is zero(0)
    public:
        RealNumber(double a);//constructor
    };

    class RationalNumber : public RealNumber {//this class represent rational 
        //numbers in real numbers
    public:
        RationalNumber(int x, int y);//constructor
        void setNumerator(const int x);//setter for numerator
        int getNumerator()const;//getter for numerator
        void setDenominator(const int y);//setter for denominator
        int getDenominator()const;//getter for denominator
        void simplification();//this function converts the simple fraction
        RationalNumber operator+(const RationalNumber &num)const;//add
        RationalNumber operator-(const RationalNumber &num)const;//sub
        friend ostream &operator<<(ostream &output, const RationalNumber &num);//
        //stream insertion operator overloaded for rational number
    protected:
        int numerator;//represent numerator part
        int denominator;//represent denominator part
    };

    class Integer : public RationalNumber {//this class represent ıntegers in
        //Rational numbers
    public:
        Integer(int num);//constructor
    };

    class NaturalNumber : public RationalNumber {//this class represent natural
        //numbers(included 0) in Rational numbers
        NaturalNumber(int num);//constructor
    };

    class IrrationalNumber : public RealNumber {//this class represent irrarional
        //numbers in real numbers
    public:
        IrrationalNumber(double num);//constructor
        friend ostream &operator<<(ostream &output, const IrrationalNumber &num);//
        //stream insertion operator overloaded for irrational numbers
    };

}


#endif	/* NUMBERS_H */

