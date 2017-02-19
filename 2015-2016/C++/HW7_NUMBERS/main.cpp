/* HW7_SAHIN_EGILMEZ_131044059
 * File:   main.cpp
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
using namespace NUMBERS_GTU_SAHIN_EGILMEZ;

/*
 * 
 */
int main(int argc, char** argv) {
    //TEST FİELD
    ComplexNumber num1(5, 2), num2(4, -3);
    ImaginaryNumber num3(7), num4(-10);
    RealNumber num5(8.158), num6(18.576);
    RationalNumber num7(8, 3), num8(27, 5);
    Integer num9(5), num10(167);
    IrrationalNumber num11(1.16548432482213658462);
    //TEST OPERATOR
    cout << "num1 + num2 = " << num1 + num2 << endl;
    if (num1 > num2)
        cout << "num1 bigger than num2" << endl;
    cout << "num3 - num4 = " << num3 - num4 << endl;
    if (num3 < num4)
        cout << "num4 bigger than num3" << endl;
    cout << "num6 - num5 = " << num6 - num5 << endl;
    if (num5 < num6)
        cout << "num6 bigger than num5" << endl;
    cout << "num7 + num8 = " << num7 + num8 << endl;
    if (num7 < num8)
        cout << "num8 bigger than num7" << endl;
    cout << "num10 - num9 = " << num10 - num9 << endl;
    if (num9 < num10)
        cout << "num10 bigger than num9" << endl;
    cout << "num11 = "<<num11;

    return 0;
}

