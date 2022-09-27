#ifndef LINKQUEUE_H_INCLUDED
#define LINKQUEUE_H_INCLUDED
#include <iostream>

/**
 * 自定义队列，基于链表实现
 */
template<typename T>
class LinkQueue{
private:
    // 链表节点
    struct ListNode {
        T val;
        ListNode *next;
        ListNode(T val):val(val), next(NULL) {}
        ListNode():next(NULL) {};
    };
    ListNode *head, *rear;
    int qSize;

public:
    LinkQueue();                 // 构造函数
    ~LinkQueue();                // 析构函数
    bool isEmpty();              // 判断队列是否为空
    void pop();                  // 将队首元素删除
    void push(T node);           // 向队尾添加元素
    T getFront();                // 取出队首元素
    int getSize();               // 获得队列中的元素个数
};

/**
 * 构造函数
 */
template<typename T>
LinkQueue<T>::LinkQueue() {
    head = new ListNode();
    rear = head;
    qSize = 0;
}

/**
 * 析构函数
 */
template<typename T>
LinkQueue<T>::~LinkQueue() {
    ListNode* p = head->next;
    while(p) {
        delete head;
        head = p;
        p = p->next;
    }
    delete head;
}

/**
 * 判断队列是否为空
 */
template<typename T>
bool LinkQueue<T>::isEmpty() {
    return qSize == 0;
}

/**
 * 将队首元素删除
 */
template<typename T>
void LinkQueue<T>::pop() {
    ListNode *p = head->next;
    if(!p) return;
    if(p == rear) rear = head;
    head->next = p->next;
    delete p;
    qSize--;
}

/**
 * 向队尾添加元素
 */
template<typename T>
void LinkQueue<T>::push(T val) {
    rear->next = new ListNode(val);
    rear = rear->next;
    qSize++;
}

/**
 * 取出队首元素
 */
template<typename T>
T LinkQueue<T>::getFront() {
    if(!head->next) {
        std::cout<<"ERROR:Empty Queue!\n";
        return head->val;
    }
    return head->next->val;
}

/**
 * 获得队列中的元素个数
 */
template<typename T>
int LinkQueue<T>::getSize() {
    return qSize;
}


#endif // LINKQUEUE_H_INCLUDED
