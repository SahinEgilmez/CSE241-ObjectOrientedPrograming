
/* 
 * File:   Math.h
 * Author: segilmez
 *
 * Created on 27 Ekim 2016 Perşembe, 22:22
 */

#include <string>
#include "Math.h"

using namespace std;

/* 
 * take the integer mathemetics power. i1^i2. alternative cmath's pow
 * I don't want to <cmath>
 */
int Math::pow(int i1, int i2) {
    int num = i1;
    if (i2 != 0) {//if power is 0, result is 1
        for (int i = i2; i > 1; i--) {
            i1 = i1* num;
        }
        return i1;
    } else
        return 1;

}
/*converts string to integer. alternative atoi*/
int Math::strToInt(const string str) {
    int result = 0;
    for (int i = 0; i < str.size(); i++) {
        result = result + ((((int) str[i]) - '0') * pow(10, (str.size() - i - 1)));
    }
    return result;
}


