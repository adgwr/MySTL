#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED
#ifndef INT_MAX
#define INT_MAX 2147483647
#endif // INT_MAX
#include <iostream>

/**
 * 实现了最小堆的数据结构，使用数组存储元素节点，可自动扩容
 * 若需要最大堆则需自定义T将小于操作符重载为大于操作符
 */
template<typename T>
class Heap {
private:
    static const int MAX_HEAP_CAPACITY = INT_MAX>>2;

    int size, capacity;                   // size为堆中的元素个数， capacity为存放元素的数组的容量
    T *arr;                               // 存放堆中元素的数组
    void ensureCapacity(int minCapacity); // 确保数组空间足够，若不够则扩容，策略为容量翻倍
    void filterUp(int start);             // 自上而下调整
    void filterDown(int start, int end);  // 自下而上调整

public:
    Heap();                    // 默认构造函数，默认capacity为100
    Heap(T* arr, int n);    // 根据传入的数组构造堆
    ~Heap();                   // 析构函数
    bool isEmpty();            // 判断堆是否为空
    void push(T val);          // 向堆中添加节点
    T getTop();                // 取得堆的堆顶元素
    void popTop();             // 删除堆的堆顶元素
    int getSize();             // 获得堆中的元素个数
};


/**
 * 默认构造函数，默认capacity为100
 */
template<typename T>
Heap<T>::Heap() {
    size = 0;
    capacity = 100;
    arr = new T[capacity];
}

/**
 * 根据传入的数组构造堆
 */
template<typename T>
Heap<T>::Heap(T* arr, int n) {
    this->arr = new T[n];
    size = capacity = n;
    for(int i=0; i<n; i++) {
        this->arr[i] = arr[i];
    }
    // 找到最后一个非叶节点
    int lastNonLeafNode = (size-2)/2;
    // 从下到上逐步调整为堆
    while(lastNonLeafNode >= 0) {
        filterDown(lastNonLeafNode, size-1);
        --lastNonLeafNode;
    }
}

/**
 * 析构函数，释放堆的数组空间
 */
template<typename T>
Heap<T>::~Heap() {
    delete [] arr;
}

/**
 * 确保数组空间足够，若不够则扩容，策略为容量翻倍
 */
template<typename T>
void Heap<T>::ensureCapacity(int minCapacity) {
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
        if(newCapacity - MAX_HEAP_CAPACITY > 0) {
            if(minCapacity < 0) {
                // 溢出
                std::cout<<"Overflow!";
            }
            newCapacity = (minCapacity > MAX_HEAP_CAPACITY ? INT_MAX : MAX_HEAP_CAPACITY);
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

/**
 * 自上而下调整
 */
template<typename T>
void Heap<T>::filterUp(int start) {
    int j = start, i = (j-1)/2; // i是j的父节点
    T temp = arr[j];
    while(j > 0) {
        if(arr[i] < temp) {
            break;
        }
        else {
            // 调整
            arr[j] = arr[i];
            j = i;
            i = (j-1)/2;
        }
    }
    arr[j] = temp;
}

/**
 * 自下而上调整
 */
template<typename T>
void Heap<T>::filterDown(int start, int end) {
    int i = start, j = 2*i + 1; // j是i的左子女
    T temp = arr[i];
    while(j <= end) {
        // 取两子女中的最小者
        if(j < end && arr[j+1] < arr[j]) {
            ++j;
        }
        if(temp < arr[j]) {
            break;
        }
        else {
            // 调整
            arr[i] = arr[j];
            i = j;
            j = 2*i + 1;
        }

    }
    arr[i] = temp;
}

/**
 * 判断堆是否为空
 */
template<typename T>
bool Heap<T>::isEmpty() {
    return size==0;
}

/**
 * 向堆中添加节点
 */
template<typename T>
void Heap<T>::push(T node) {
    ensureCapacity(size+1);
    arr[size] = node;
    filterUp(size);
    ++size;
}

/**
 * 取得堆的堆顶元素
 */
template<typename T>
T Heap<T>::getTop() {
    return arr[0];
}

/**
 * 删除堆的堆顶元素
 */
template<typename T>
void Heap<T>::popTop() {
    if(!size) return;
    // 将最后一个元素填补至第一个元素的位置
    arr[0] = arr[--size];
    filterDown(0, size-1);
}

/**
 * 获得堆中的元素个数
 */
template<typename T>
int Heap<T>::getSize() {
    return size;
}


#endif // HEAP_H_INCLUDED
