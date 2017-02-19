/* HW3_SAHİN_EGILMEZ_131044059
 * 
 * File:   main.cpp
 * Author: ŞAHİN EĞİLMEZ 131044059
 *
 * Created on October 30, 2015, 2:22 PM
 */
#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

class Triangle {
public:
    Triangle(double valueSideA, double valueSideB, double valueSideC);
    Triangle(double valueSideA, double valueSideB);
    Triangle(double valueSideA);
    Triangle();
    void input();
    void output();
    void setTriangle(double valueSideA, double valueSideB, double valueSideC);
    void setAngleA(double a);
    void setAngleB(double b);
    void setAngleC(double c);
    double getSideA();
    double getSideB();
    double getSideC();
    bool rightAngle();
    double perimeter();
    double area();
    double angleA();
    double angleB();
    double angleC();
private:
    double sideA;
    double sideB;
    double sideC;
};

bool isEqual(Triangle t1, Triangle t2);
void redoubleTriangle(Triangle &t);

main() {
    /*********TEST 1********/
    cout << "TEST 1 IS STARTİNG" << endl << endl;
    Triangle test1(30, 40, 50);
    cout << "Side A:" << test1.getSideA() << "  Corner A: " << test1.angleA() << endl;
    cout << "Side B:" << test1.getSideB() << "  Corner B: " << test1.angleB() << endl;
    cout << "Side C:" << test1.getSideC() << "  Corner C: " << test1.angleC() << endl;
    cout << "Triangle's perimeter is : " << test1.perimeter() << endl;
    cout << "Triangle's area is : " << test1.area() << endl;
    cout << "RightAngle function value is : " << test1.rightAngle() << endl;
    test1.input();
    test1.output();
    test1.setTriangle(12, 15, 20);
    test1.output();
    test1.setAngleA(9);
    test1.setAngleB(12);
    test1.setAngleC(10);
    test1.output();
    cout << "Test 2 call by reference function(redoubleTriangle):" << endl;
    redoubleTriangle(test1);
    test1.output();
    /*********TEST 2*********/
    cout << "TEST 2 IS STARTİNG" << endl << endl;
    Triangle test2(15, 20, 25);
    cout << "Side A:" << test2.getSideA() << "  Corner A: " << test2.angleA() << endl;
    cout << "Side B:" << test2.getSideB() << "  Corner B: " << test2.angleB() << endl;
    cout << "Side C:" << test2.getSideC() << "  Corner C: " << test2.angleC() << endl;
    cout << "Triangle's perimeter is : " << test2.perimeter() << endl;
    cout << "Triangle's area is : " << test2.area() << endl;
    cout << "RightAngle function value is : " << test2.rightAngle() << endl;
    test2.input();
    test2.output();
    test2.setTriangle(10, 8, 16);
    test2.output();
    test2.setAngleA(8);
    test2.setAngleB(15);
    test2.setAngleC(13);
    test2.output();
    cout << "Test 2 call by reference function(redoubleTriangle):" << endl;
    redoubleTriangle(test2);
    test2.output();
    cout << "Test call by value function(isEqual)" << endl;
    if (isEqual(test1, test2))
        cout << "Test1 and test 2 objects are equal" << endl;
    else
        cout << "Test1 and test 2 objects are not equal" << endl;

    return 0;
}

Triangle::Triangle(double valueSideA, double valueSideB, double valueSideC) {
    if (((valueSideA + valueSideB) > valueSideC) && valueSideC > 0 &&
        ((valueSideB + valueSideC) > valueSideA) && valueSideA > 0 &&
        ((valueSideC + valueSideA) > valueSideB) && valueSideB > 0) {
        sideA = valueSideA;
        sideB = valueSideB;
        sideC = valueSideC;
    } else {
        cerr << "Object cannot created, because it didn't provide triangle conditions!" << endl;
        exit;
    }
}

Triangle::Triangle(double valueSideA, double valueSideB) {
    if (((valueSideB + 1) > valueSideA) && valueSideA > 0 &&
        ((valueSideA + 1) > valueSideB) && valueSideB > 0 &&
        ((valueSideA + valueSideB) > 1)) {
        sideA = valueSideA;
        sideB = valueSideB;
        sideC = 1;
    } else {
        cerr << "Object cannot created, because it didn't provide triangle conditions!" << endl;
        exit(1);
    }
}

Triangle::Triangle(double valueSide) {
    if (valueSide > 0) {
        sideA = valueSide;
        sideB = valueSide;
        sideC = valueSide;
    } else {
        cerr << "Object cannot created, because it didn't provide triangle conditions!" << endl;
        exit(1);
    }
}

Triangle::Triangle() :
sideA(1.0), sideB(1.0), sideC(1.0) {
    /*Body initially empty*/
}

void Triangle::input() {
    double a, b, c;
    bool possibleSide = false;
    while (possibleSide == false) {
        cout << "Please enter to triangle sides." << endl << "Side A: ";
        cin>>a;
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Side B: ";
        cin>>b;
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Side C: ";
        cin>>c;
        cin.clear();
        cin.ignore(10000, '\n');
        if (a > 0 && (b + c) > a && b > 0 && (a + c) > b && c > 0 && (a + b) > c) {
            sideA = a;
            sideB = b;
            sideC = c;
            possibleSide = true;
        } else
            cerr << "Not assigned triangle's sides. Because they didn't provide triangle conditions!" << endl;
    }
}

void Triangle::output() {
    cout << "This triangle's sides are A:" << sideA << "  B:" << sideB << "  C:" << sideC << endl;
}

void Triangle::setTriangle(double valueSideA, double valueSideB, double valueSideC) {
    if (((valueSideA + valueSideB) > valueSideC) && valueSideC > 0 &&
        ((valueSideB + valueSideC) > valueSideA) && valueSideA > 0 &&
        ((valueSideC + valueSideA) > valueSideB) && valueSideB > 0) {
        sideA = valueSideA;
        sideB = valueSideB;
        sideC = valueSideC;
    } else {
        cerr << "Object could not modify , because it didn't provide triangle conditions!" << endl;
        exit;
    }
}

void Triangle::setAngleA(double a) {
    sideA = a;
}

void Triangle::setAngleB(double b) {
    sideB = b;
}

void Triangle::setAngleC(double c) {
    sideC = c;
}

double Triangle::getSideA() {
    return sideA;
}

double Triangle::getSideB() {
    return sideB;
}

double Triangle::getSideC() {
    return sideC;
}

bool Triangle::rightAngle() {
    if (pow(sideA, 2) == (pow(sideB, 2) + pow(sideC, 2)))
        return true;
    else if (pow(sideB, 2) == (pow(sideA, 2) + pow(sideC, 2)))
        return true;
    else if (pow(sideC, 2) == (pow(sideA, 2) + pow(sideB, 2)))
        return true;
    else
        return false;
}

double Triangle::perimeter() {
    return (sideA + sideB + sideC);
}

double Triangle::area() {
    double halfPerimeter = (sideA + sideB + sideC) / 2;
    return sqrt(halfPerimeter * (halfPerimeter - sideA) * (halfPerimeter - sideB) * (halfPerimeter - sideC));
}

double Triangle::angleA() {
    const double PI = 3.141592653589793238463;
    return acos(-((pow(sideA, 2) - pow(sideC, 2) - pow(sideB, 2)) / (2 * sideC * sideB))) * (180 / PI);
}

double Triangle::angleB() {
    const double PI = 3.141592653589793238463;
    return acos(-((pow(sideB, 2) - pow(sideA, 2) - pow(sideC, 2)) / (2 * sideA * sideC))) * (180 / PI);
}

double Triangle::angleC() {
    const double PI = 3.141592653589793238463;
    return acos(-((pow(sideC, 2) - pow(sideA, 2) - pow(sideB, 2)) / (2 * sideA * sideB))) * (180 / PI);
}

bool isEqual(Triangle t1, Triangle t2) {
    if (t1.getSideA() == t2.getSideA() &&
        t1.getSideB() == t2.getSideB() &&
        t1.getSideC() == t2.getSideC())
        return true;
    else
        return false;
}

void redoubleTriangle(Triangle &t) {
    double a, b, c;
    a = t.getSideA();
    b = t.getSideB();
    c = t.getSideC();
    t.setTriangle(2 * a, 2 * b, 2 * c);
}
