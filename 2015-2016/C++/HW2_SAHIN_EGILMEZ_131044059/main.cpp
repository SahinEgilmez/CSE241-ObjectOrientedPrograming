/* HW2_SAHİN_EGILMEZ_131044059
 * 
 * File:   main.cpp
 * Author: ŞAHİN EĞİLMEZ 131044059
 *
 * Created on October 15, 2015, 2:22 PM
 */

#include <iostream>

using namespace std;

class DayOfYear  //keep to day of year
    {	
    public:
	int month;
	int day;
    };
    
class Person   //keep to person name and age
    {
    public:
        char name;
        int age;
    };
//This function returns the array index of the first mode element of a given array.
int return_mode (const void * base, size_t num, size_t size, 
        bool (* equals) (const void *, const void *));

//This function perform comparing integers
bool compareInt(const void* el1,const void* el2);

//This function perform comparing to doubles
bool compareDouble(const void* el1,const void* el2);

//This function perform comparing to chars
bool compareChar(const void* el1,const void* el2);

//This function perform comparing to DayOfYear classes
bool compareDayOfYear(const void* el1,const void* el2);

//This function perform comparing to Person classes
bool comparePerson(const void* el1,const void* el2);

int main(int argc, char** argv) {
    cout<<"TEST OF FUNCTİONS"<<endl;
    //Testing compare integer
    int integers[] = {0, 1, 5, 2, 2};
    int res = return_mode(integers, 5, sizeof (int), compareInt);
    if (res == -1) {
        cout << "Could not found mode of integer array! No recurring elements" << endl;
    } else{        
        cout <<"Index of mode integer array is = "<< res << endl;
    }
    
    //Testing compare double
    double doubles[] = {5.0, 1.0 , 2.0, 3.0, 2.0};
    res = return_mode(doubles, 5, sizeof (double), compareDouble);
    if (res == -1) {
        cout << "Could not found mode of double array! No recurring elements" << endl;
    } else{        
        cout <<"Index of mode double array is = "<< res << endl;
    }
    
    //Testing compare char
    char chars[5]={'a','g','c','a','c'};
    res = return_mode(chars, 5, sizeof (char), compareChar);
    if (res == -1) {
        cout << "Could not found mode of char array! No recurring elements" << endl;
    } else{        
        cout <<"Index of mode char array is = "<< res << endl;
    }
    
    //Testing compare DayOfYear class
    DayOfYear days[5];
    days[0].day=5,days[0].month=5;
    days[1].day=2,days[1].month=10;
    days[2].day=5,days[2].month=7;
    days[3].day=2,days[3].month=10;
    days[4].day=5,days[4].month=7;
    res = return_mode(days, 5, sizeof (DayOfYear), compareDayOfYear);
    if (res == -1) {
        cout << "Could not found mode of DayOfYear array! No recurring elements" << endl;
    } else{        
        cout <<"Index of mode DayOfYear array is = "<< res << endl;
    }
    
    //Testing compare Person class
    Person people[5];
    people[0].age=15, people[0].name='A';
    people[1].age=11, people[1].name='B';
    people[2].age=20, people[2].name='F';
    people[3].age=25, people[3].name='C';
    people[4].age=25, people[4].name='E';
    res = return_mode(people, 5, sizeof (Person), comparePerson);
    if (res == -1) {
        cout << "Could not found mode of Person array! No recurring elements" << endl;
    } else{        
        cout <<"Index of mode Person array is = "<< res << endl;
    }
    
    return 0;
}
//This function returns the array index of the first mode element of a given array.
int return_mode (const void * base, size_t num, size_t size, 
    bool (* equals) (const void *, const void *)){
    int arr[num];//This array keeps occorounce of each elements
    for(int i=0;i<num;i++){
        arr[i]=0;
    }
    
    unsigned char* elem = (unsigned char*) base;//First adress of array
    unsigned char* end = (unsigned char*) base + (size* num);//Last adress of array
    unsigned char* temp = (unsigned char*) base;//First adress of array

    for (int j = -1; elem < end; elem += size) {
        j++;//index
        temp = (unsigned char*) base;//assing adress of element
        while(temp < end){//Checks end of array
            if (equals(temp,elem) == true) {//Call equals functions
                arr[j]++;//if elements are equal,arr+1
            }
            temp+=size;//Go to next adress
        }    
    }
    int max=1;//take the maximum occoruence of element
    int index=-1;
    for(int k=0;k<num;k++){
        if(arr[k]>max){//if find mode,assign this
            max=arr[k];
            index=k;
        }    
    }
    
    return index;//return index of first occorounce
}
//This function perform comparing integers
bool compareInt(const void* el1,const void* el2) {

    int* p1 = (int*) el1;
    int* p2 = (int*) el2;

    if (*p1 != *p2) {
        return false;
    } else if (*p1 == *p2) {
        return true;
    }
}

//This function perform comparing to doubles
bool compareDouble(const void* el1,const void* el2){

    double* p1 = (double*) el1;
    double* p2 = (double*) el2;
    
    if (*p1 != *p2) {
        return false;
    } else if (*p1 == *p2) {
        return true;
    }
}
//This function perform comparing to chars
bool compareChar(const void* el1,const void* el2){
    
    char* p1 = (char*) el1;
    char* p2 = (char*) el2;

    if (*p1 != *p2) {
        return false;
    } else if (*p1 == *p2) {
        return true;
    }
}

//This function perform comparing to DayOfYear classes
bool compareDayOfYear(const void* el1,const void* el2){
    DayOfYear* p1 = (DayOfYear*) el1;
    DayOfYear* p2 = (DayOfYear*) el2;
    
    if ( (p1->day == p2->day) && (p1->month == p2->month ) ) {
        return true;
    } else{
        return false;
    }
}

//This function perform comparing to Person classes
bool comparePerson(const void* el1,const void* el2){
    Person* p1 = (Person*) el1;
    Person* p2 = (Person*) el2;
    
    if ( (p1->age == p2->age) && (p1->name == p2->name ) ) {

        return true;

    } else{

        return false;
    }
}
