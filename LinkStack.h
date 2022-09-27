#ifndef LINKSTACK_H_INCLUDED
#define LINKSTACK_H_INCLUDED
#include <iostream>

/**
 * 自定义栈，基于链表实现
 */
template<typename T>
class LinkStack {
private:
    // 链表节点
    struct ListNode {
        T val;
        ListNode *next;
        ListNode(T val):val(val), next(NULL) {}
        ListNode():next(NULL) {}
    };
    ListNode *head;
    int sSize;

public:
    LinkStack();             // 构造函数
    ~LinkStack();            // 析构函数
    bool isEmpty();          // 判断栈是否为空
    void pop();              // 出栈
    void push(T node);       // 压栈
    T getTop();              // 取得栈顶元素
    int getSize();           // 获得栈中的元素个数
};

/**
 * 构造函数
 */
template<typename T>
LinkStack<T>::LinkStack() {
    head = new ListNode();
    sSize = 0;
}

/**
 * 析构函数
 */
template<typename T>
LinkStack<T>::~LinkStack() {
    ListNode* p = head->next;
    while(p) {
        delete head;
        head = p;
        p = p->next;
    }
    delete head;
}

/**
 * 判断栈是否为空
 */
template<typename T>
bool LinkStack<T>::isEmpty() {
    return sSize == 0;
}

/**
 * 出栈
 */
template<typename T>
void LinkStack<T>::pop() {
    ListNode *p = head->next;
    if(!p) return;
    head->next = p->next;
    delete p;
    --sSize;
}

/**
 * 压栈
 */
template<typename T>
void LinkStack<T>::push(T val) {
    ListNode* t = new ListNode(val);
    t->next = head->next;
    head->next = t;
    ++sSize;
}

/**
 * 取得栈顶元素
 */
template<typename T>
T LinkStack<T>::getTop() {
    if(!head->next) {
        std::cout<<"ERROR:Empty Stack!\n";
        return head->val;
    }
    return head->next->val;
}

/**
 * 获得栈中的元素个数
 */
template<typename T>
int LinkStack<T>::getSize() {
    return sSize;
}

#endif // LINKSTACK_H_INCLUDED
