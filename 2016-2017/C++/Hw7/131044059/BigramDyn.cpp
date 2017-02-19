#include "BigramDyn.h"

template<class T>
BigramDyn<T>::BigramDyn(int type) {
    
    dataType = type;
    if(dataType <1 ||dataType>2)
       throw MyException("Data type must be 1 or 2. ");
    bigrams = new bigram<T>[1];
    datas = new T[1];
}

template<class T>
BigramDyn<T>::~BigramDyn() {
    delete[] bigrams;
    delete[] datas;
}

template <class T>
bool BigramDyn<T>::readFile(const string filename) {
    delete[] datas;
    delete[] bigrams;
    ifstream file; //file stream
    string str = ""; //each line 
    size_t pos;
    file.open(filename);
    if (!file.is_open()) {
        throw MyException("Unable to open file");
        return false;
    } else {
        while (file >> str) {
            if ((dataType == 1 && is_same<int, T>::value) ||
                    (dataType == 2 && is_same<string, T>::value) ||
                    (dataType == 3 && is_same<double, T>::value)) {
                elemCount++;
                continue;
            } else {
                file.close();
                throw MyException("Data type not acceptable!\n");
                return false;
            }
        }
        file.close();
    }



    file.open(filename);
    if (!file.is_open()) {
        throw MyException("Unable to open file");
        return false;
    } else {
        bigrams = new bigram<T>[elemCount ];
        datas = new T[elemCount];
        T temp;
        int i = 0;
        while (file >> temp && i < elemCount) {
            datas[i] = temp;
            i++;
        }
        if (elemCount == 0) {
            //throw (MyException("Empty file."));
            return false;
        }
        if (i != (elemCount) || i == 1) {
            throw (MyException("Bad data."));
            file.close();
            return false;
        }
        
        
        int count = 0;
        for (int i = 0; i < elemCount - 1; i++) {
            pair<T, T> tempp;
            tempp.first = datas[i];
            tempp.second = datas[i + 1];
            setBg(tempp);
        }
        file.close();
    }
    return true;

}

template <class T>
int BigramDyn<T>::numGrams() const {
    return this->elemCount - 1;
}

template <class T>
int BigramDyn<T>::numOfGrams(T elem1, T elem2) {
    for (int i = 0; elemCount - 1; i++) {
        if (bigrams[i].isSet) {
            if (bigrams[i].p.first == elem1 && bigrams[i].p.second == elem2) {
                return bigrams[i].count;
            }
        } else {
            return 0;
        }
    }
}

template <class T>
pair<T, T> BigramDyn<T>::maxGrams() {
    int max = 0;
    pair<T, T> p;
    for (int i = 0; i < elemCount - 1; i++) {
        if (bigrams[i].isSet) {
            if (bigrams[i].count > max) {
                p.first = bigrams[i].p.first;
                p.second = bigrams[i].p.second;
                max = bigrams[i].count;
            }
        } else {
            break;
        }
    }
    return p;
}

template <class T>
void BigramDyn<T>::print(std::ostream& output) {
    int num = elemCount;
    while (num > 0) {
        for (int i = 0; i < elemCount; i++) {
            if (num == bigrams[i].count) {
                output << bigrams[i].p.first << " , " << bigrams[i].p.second << " : " << num << endl;
            }
        }
        num--;
    }
}

template <class T>
bool BigramDyn<T>::setBg(const pair<T, T> p) {
    for (int i = 0; elemCount - 1; i++) {
        if (bigrams[i].isSet) {
            if (bigrams[i].p.first == p.first && bigrams[i].p.second == p.second) {
                bigrams[i].count = (bigrams[i].count + 1);
                return true;
            }
        } else {
            bigrams[i].p = p;
            bigrams[i].count = 1;
            bigrams[i].isSet = true;
            return true;
        }
    }

    return false;
}