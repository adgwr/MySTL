#ifndef ARRAY_H_INCLUDED
#define ARRAY_H_INCLUDED

#ifndef INT_MAX
#define INT_MAX 2147483647
#endif // INT_MAX

#include <iostream>

/**
 * 自定义动态数组，可自动扩容
 */
template<typename T>
class Array{
private:
    T *arr;                                           // 对象的数组
    int size, capacity;                               // size为当前大小， capacity为数组容量
    void ensureCapacity(int minCapacity);             // 确保数组空间大于minCapacity， 若不够则扩容
    static const int MAX_ARR_CAPACITY = INT_MAX >> 2; // 数组最大容量
public:
    Array();                            // 默认构造函数
    Array(int n, const T& a);           // 利用数组构建对象
    Array(const Array<T>& anotherArr);  // 拷贝构造函数
    ~Array();                           // 销毁对象
    Array<T>& operator=(const Array<T>& anotherArr); // 赋值函数
    const T& operator[](int pos) const; // 重载[]操作符用于const对象的访问与赋值
    T& operator[](int pos);             // 重载[]操作符用于访问
    void assign(int n, const T& val);   // 重置数组，并将前n个位置置为val
    int getSize();                      // 取得数组当前大小
    void pushBack(const T& val);        // 将元素添加到数组后部
    T get(int pos);                     // 取得数组下标为pos的元素
    void put(int pos, const T& val);    // 将数组中下标为pos的单元置为val
    bool isEquals(const Array<T>& a);   // 判断this指针所指向的对象是否与a相等
};


/**
 * 默认构造函数
 */
template<typename T>
Array<T>::Array() {
    arr = new T[10];
    size = 0;
    capacity = 10;
}

/**
 * 利用数组构建对象
 */
template<typename T>
Array<T>::Array(int n, const T& a) {
    this->arr = new T[n];
    size = capacity = n;
    for(int i=0; i<n; i++) {
        this->arr[i] = a;
    }
}

/**
 * 拷贝构造函数
 */
template<typename T>
Array<T>::Array(const Array<T> & anotherArr) {
    this->arr = new T[anotherArr.capacity];
    this->capacity = anotherArr.capacity;
    this->size = anotherArr.size;
    for(int i=0; i<this->size; i++) {
        this->arr[i] = anotherArr.arr[i];
    }
}

/**
 * 重载等于操作符，赋值函数
 */
template<typename T>
Array<T>& Array<T>::operator=(const Array<T> & anotherArr) {
    this->arr = new T[anotherArr.capacity];
    this->capacity = anotherArr.capacity;
    this->size = anotherArr.size;
    for(int i=0; i<this->size; i++) {
        this->arr[i] = anotherArr.arr[i];
    }
    return *this;
}

/**
 * 销毁对象
 */
template<typename T>
Array<T>::~Array() {
    delete [] arr;
}

/**
 * 重载[]操作符用于const对象的访问
 */
template<typename T>
const T& Array<T>::operator[](int pos) const {
    // 若下标非法则报错
    if(pos < 0 || pos >= size) {
        std::cout<<"ERROR:Exceed Array Boundary!\n";
        return arr[0];
    }
    else return arr[pos];
}

/**
 * 重载[]操作符用于访问与赋值
 */
template<typename T>
T& Array<T>::operator[](int pos) {
    // 若下标非法则报错
    if(pos < 0 || pos >= size) {
        std::cout<<"ERROR:Exceed Array Boundary!\n";
        return arr[0];
    }
    else return arr[pos];
}

/**
 * 重置数组，并将前n个位置置为val
 */
template<typename T>
void Array<T>::assign(int n, const T& val) {
    ensureCapacity(n);
    size = n;
    for(int i=0; i<n; i++) {
        arr[i] = val;
    }
}

/**
 * 取得数组当前大小
 */
template<typename T>
int Array<T>::getSize() {
    return size;
}

/**
 * 将元素添加到数组后部
 */
template<typename T>
void Array<T>::pushBack(const T& val) {
    // 先判断容量是否足够，若不够则扩容
    ensureCapacity(size + 1);
    arr[size++] = val;
}

/**
 * 取得数组下标为pos的元素
 */
template<typename T>
T Array<T>::get(int pos) {
    // 若下标非法则报错
    if(pos < 0 || pos >= size) {
        std::cout<<"ERROR:Exceed Array Boundary!\n";
        return arr[0];
    }
    else return arr[pos];
}

/**
 * 将数组中下标为pos的单元置为val
 */
template<typename T>
void Array<T>::put(int pos, const T& val) {
    if(pos < 0 || pos >= size) {
        std::cout<<"ERROR:Exceed Array Boundary!\n";
    }
    else arr[pos] = val;
}

/**
 * 判断this指针所指向的对象是否与a相等
 */
template<typename T>
bool Array<T>::isEquals(const Array<T>& a) {
    // 若大小不同则一定不等
    if(this->size != a.size) return false;
    for(int i=0; i<this->size; i++) {
        if(!(this->arr[i] == a.arr[i])) {
            return false;
        }
    }
    return true;
}

/**
 * 确保数组空间大于minCapacity， 若不够则扩容
 */
template<typename T>
void Array<T>::ensureCapacity(int minCapacity) {
    // 若数组容量不够则扩容
    if(capacity < minCapacity) {
        // 容量翻倍
        int newCapacity = capacity << 1;
        // 若仍不够，则取所需的容量值
        // 相减后再比较可防止溢出
        if(newCapacity - minCapacity < 0) {
            newCapacity = minCapacity;
        }
        // 超出最大容量
        if(newCapacity - MAX_ARR_CAPACITY > 0) {
            if(minCapacity < 0) {
                // 溢出
                return;
            }
            newCapacity = (minCapacity > MAX_ARR_CAPACITY ? INT_MAX : MAX_ARR_CAPACITY);
        }
        capacity = newCapacity;
        // 分配新数组
        T * newArr = new T[capacity];
        // 复制原数组元素
        for(int i=0; i<size; i++) {
            newArr[i] = arr[i];
        }
        // 释放原数组空间
        delete [] arr;
        arr = newArr;
    }
}


#endif // ARRAY_H_INCLUDED
