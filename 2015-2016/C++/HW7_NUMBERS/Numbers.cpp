/* HW7_SAHIN_EGILMEZ_131044059
 * File:   Numbers.cpp
 * Author: sahin
 *
 * Created on 16 Aralık 2015 Çarşamba, 12:35
 */

#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>
#include "Numbers.h"

using namespace std;
namespace NUMBERS_GTU_SAHIN_EGILMEZ {
    
    ComplexNumber::ComplexNumber(double a, double b) : real(a), imaginary(b) {
    }

    ComplexNumber::~ComplexNumber() {
    }

    void ComplexNumber::setReal(const double num) {
        this->real = num;
    }

    double ComplexNumber::getReal()const {
        return this->real;
    }

    void ComplexNumber::setImag(const double num) {
        this->imaginary = num;
    }

    double ComplexNumber::getImag()const {
        return this->imaginary;
    }

    ComplexNumber ComplexNumber::operator+(const ComplexNumber &num)const {
        return ComplexNumber((this->getReal() + num.getReal()), (this->getImag() + num.getImag()));
    }

    ComplexNumber ComplexNumber::operator-(const ComplexNumber &num)const {
        return ComplexNumber((this->getReal() - num.getReal()), (this->getImag() - num.getImag()));
    }

    bool ComplexNumber::operator<(const ComplexNumber& num) {
        if (this->getImag() == 0 || num.imaginary == 0) {
            if (this->getReal() < num.getReal())
                return true;
            else
                return false;
        } else {
            double coke1 = sqrt(pow(this->getReal(), 2) + pow(this->getImag(), 2));
            double coke2 = sqrt(pow(num.getReal(), 2) + pow(num.getImag(), 2));
            if (coke1 < coke2)
                return true;
            else
                return false;
        }
    }

    bool ComplexNumber::operator>(const ComplexNumber& num) {
        if (this->getImag() == 0 || num.imaginary == 0) {
            if (this->getReal() > num.getReal())
                return true;
            else
                return false;
        } else {
            double coke1 = sqrt(pow(this->getReal(), 2) + pow(this->getImag(), 2));
            double coke2 = sqrt(pow(num.getReal(), 2) + pow(num.getImag(), 2));
            if (coke1 > coke2)
                return true;
            else
                return false;
        }
    }

    ostream &operator<<(ostream &output, const ComplexNumber & num) {
        if (num.getImag() == 0)
            output << num.getReal();
        else if (num.getReal() == 0)
            output << num.getImag() << "i";
        else if (num.getImag() < 0)
            output << num.getReal() << num.getImag() << "i";
        else
            output << num.getReal() << "+" << num.getImag() << "i";

        return output;
    }

    ImaginaryNumber::ImaginaryNumber(double b) : ComplexNumber(0.0, b) {

    }

    RealNumber::RealNumber(double a) : ComplexNumber(a, 0.0) {

    }

    RationalNumber::RationalNumber(int x, int y) : RealNumber((double) x / (double) y) {
        this->setNumerator(x);
        this->setDenominator(y);
    }

    void RationalNumber::setNumerator(const int x) {
        this->numerator = x;
    }

    int RationalNumber::getNumerator()const {
        return this->numerator;
    }

    void RationalNumber::setDenominator(const int y) {
        this-> denominator = y;
    }

    int RationalNumber::getDenominator()const {
        return this->denominator;
    }

    void RationalNumber::simplification() {
        int sum = 1;
        int i = (this->getNumerator() >this->getDenominator() ?
                 this->getNumerator() : this->getDenominator());
        while (i > 0) {
            if ((this->getNumerator() % i == 0)&& (this->getDenominator() % i == 0)) {
                sum = i;
                break;
            }
            i--;
        }
        this->setNumerator(this->getNumerator() / sum);
        this->setDenominator(this->getDenominator() / sum);
    }

    RationalNumber RationalNumber::operator+(const RationalNumber& num) const {
        int x = (this->getNumerator() * num.getDenominator())+(num.getNumerator() * this->getDenominator());
        int y = this->getDenominator() * num.getDenominator();
        RationalNumber result(x, y);
        result.simplification();
        return result;
    }

    RationalNumber RationalNumber::operator-(const RationalNumber& num) const {
        int x = (this->getNumerator() * num.denominator)-(num.getNumerator() * this->getDenominator());
        int y = this->getDenominator() * num.getDenominator();
        RationalNumber result(x, y);
        result.simplification();
        return result;
    }

    ostream &operator<<(ostream &output, const RationalNumber & num) {
        if (num.getDenominator() == 0)
            output << "Tanımsız sayı";
        else if (num.getNumerator() == 0)
            output << num.getNumerator();
        else if (num.getDenominator() == 1)
            output << num.getNumerator();
        else
            output << num.getNumerator() << "/" << num.getDenominator();
    }

    Integer::Integer(int num) : RationalNumber(num, 1) {

    }

    NaturalNumber::NaturalNumber(int num) : RationalNumber(num, 1) {
        if (num < 0) {
            cout << "Bu bir NaturalNumber değildir!Programdan çıkılıyor..." << endl;
            exit(1);
        }
    }

    IrrationalNumber::IrrationalNumber(double num) : RealNumber(num) {

    }

    ostream &operator<<(ostream &output, const IrrationalNumber & num) {
        output << num.getReal() << "d"; //devreden manasında
    }
}
