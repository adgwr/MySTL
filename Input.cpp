#include <iostream>
#include <cstdio>
#include <cctype>

using namespace std;

void readLineArrAdjustSize(int& capacity, int* &arr) {
    int newCapacity = capacity << 1;
    if(newCapacity < 0) {
        // overflow
        if(capacity < 0 || capacity+1 < 0) {
            return;
        } else newCapacity = capacity + 1;
    }
    capacity = newCapacity;
    int * newArr = new int[newCapacity];
    for(int i=0; i<capacity; i++) {
        newArr[i] = arr[i];
    }
    delete arr;
    arr = newArr;
}

int readLineToArray(int * &arr) {
    int n = 10;
    arr = new int[n];
    char c;
    int num = 0, len = 0, sign = 1;
    bool lastOneIsDigit = false;
    while((c=getchar()) != '\n') {
        if(c=='-') {
            sign = -1;
        } else if(!isdigit(c)) {
            if(lastOneIsDigit) {
                if(len >= n) readLineArrAdjustSize(n, arr);
                arr[len++] = sign * num;
                //cout<<"num="<<num<<endl;
                num = 0;
                lastOneIsDigit = false;
            }
            sign = 1;
        } else {
            num = num * 10 + c - '0';
            lastOneIsDigit = true;
        }
    }
    if(lastOneIsDigit) arr[len++] = sign * num;
    return len;
}


int main() {
    int * arr;
    int n = readLineToArray(arr);
    int i;
    for(int i=0; i<n; i++)
        cout<<arr[i]<<endl;
    return 0;
}
