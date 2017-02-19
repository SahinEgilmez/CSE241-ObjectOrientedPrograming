#include "BigramMap.h"

template<class T>
BigramMap<T>::BigramMap(int type) {
    dataType = type;
    if(dataType <1 ||dataType>3)
       throw MyException("Data type must be 1 or 2. ");
}

template<class T>
BigramMap<T>::~BigramMap() {
}

template <class T>
bool BigramMap<T>::readFile(const string filename) {
    datas.clear();
    bigrams.clear();
    ifstream file; //file stream
    string str = ""; //each line 
    int i = 0;
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
                throw "Data type not acceptable!\n";
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
        T temp;
        while (file >> temp) {
            datas.push_back(temp);
        }
        if (elemCount == 0) {
            throw MyException("Empty file.");
            file.close();
            return false;
        } else if (datas.size() != elemCount || datas.size() < 2) {
            throw (MyException("Bad data."));
            file.close();
            return false;
        } 
            for (int i = 0; i < datas.size() - 1; i++) {
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
int BigramMap<T>::numGrams()const {
    return this->elemCount - 1;
}

template <class T>
int BigramMap<T>::numOfGrams(T elem1, T elem2) {
    if (bigrams.find(pair<T, T> (elem1, elem2)) != bigrams.end()) {
        return this->bigrams[pair<T, T>(elem1, elem2)];
    } else
        return 0;
}

template <class T>
pair<T, T> BigramMap<T>::maxGrams() {
    int max = 0, i = 0;
    pair<T, T> p;
    for (int i = 0; i < datas.size() - 1; i++) {
        if (max < bigrams[pair<T, T>(datas[i], datas[i + 1])]) {
            max = bigrams[pair<T, T>(datas[i], datas[i + 1])];
            p.first = datas[i];
            p.second = datas[i + 1];
        }
    }
    return p;
}

template <class T>
void BigramMap<T>::print(std::ostream& output) {
    int num = elemCount;
    bool isCheck=false;
    while (num > 0) {
        for (int i = 0; i < datas.size() - 1; i++) {
            if (num == bigrams[std::pair<T, T>(datas[i], datas[i + 1])] && !isCheck) {
                output << datas[i] << " , " << datas[i + 1] << " : " << num << endl;
                isCheck=true;
            }
        }
        isCheck=false;
        num--;
    }
}


template <class T>
void BigramMap<T>::setBg(const pair<T, T> p) {
    if (bigrams.find(p) == bigrams.end()) {
        bigrams[p] = 1;
    } else {
        int count = bigrams[p];
        bigrams[p] = (count + 1);
    }
}

