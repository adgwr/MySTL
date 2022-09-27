#ifndef DEQUE_H_INCLUDED
#define DEQUE_H_INCLUDED
#include <iostream>

/**
 * 自定义双端队列，基于双向链表实现
 */
template<typename T>
class Deque{
private:
    // 链表节点
    struct ListNode {
        T val;
        ListNode *next, *last;
        ListNode(T x):val(x), next(NULL), last(NULL) {}
        ListNode():next(NULL), last(NULL) {}
    };
    ListNode *head, *tail;    // head指向链表头结点，tail指向链表中最后一个节点
    int dsize;                // dSzie为当前队列中的元素个数
public:
    Deque();                  // 构造函数
    ~Deque();                 // 析构函数
    int getSize();            // 获取双端队列长度
    bool isEmpty();           // 判断双端队列是否为空
    void pushBack(T x);       // 在尾部添加节点
    void pushFront(T x);      // 在头部添加节点
    void popBack();           // 删除最后一个节点
    void popFront();          // 删除第一个节点
    T getFront();             // 返回第一个节点
    T getBack();              // 返回最后一个节点
    void traverse();          // 遍历输出双端队列中的元素
};

/**
 * 构造函数
 */
template<typename T>
Deque<T>::Deque() {
    head = new ListNode(0);
    tail = head;
    dsize = 0;
}

/**
 * 析构函数
 */
template<typename T>
Deque<T>::~Deque() {
    ListNode *t;
    while(tail != head) {
        t = tail;
        tail = tail->last;
        delete t;
    }
    delete head;
}

/**
 * 获取双端队列长度
 */
template<typename T>
int Deque<T>::getSize() {
    return dsize;
}

/**
 * 判断双端队列是否为空
 */
template<typename T>
bool Deque<T>::isEmpty() {
    return dsize == 0;
}

//
/**
 * 在尾部添加节点
 */
template<typename T>
void Deque<T>::pushBack(T x) {
    ListNode *t = new ListNode(x);
    tail->next = t;
    t->last = tail;
    tail = t;
    ++dsize;
}

/**
 * 在头部添加节点
 */
template<typename T>
void Deque<T>::pushFront(T x) {
    ListNode *t = head->next;
    head->next = new ListNode(x);
    head->next->last = head;
    head->next->next = t;
    if(t != NULL) {
        t->last = head->next;
    } else {
        tail = head->next;
    }
    ++dsize;
}

/**
 * 删除最后一个节点
 */
template<typename T>
void Deque<T>::popBack(){
    if(!dsize) return;
    ListNode *t = tail;
    tail = tail->last;
    tail->next = NULL;
    delete t;
    --dsize;
}

/**
 * 删除第一个节点
 */
template<typename T>
void Deque<T>::popFront(){
    if(!dsize) return;
    ListNode *t = head->next;
    head->next = t->next;

    if(t == tail) {
        tail = head;
    }else {
        t->next->last = head;
    }
    delete t;
    --dsize;
}

/**
 * 返回第一个节点
 */
template<typename T>
T Deque<T>::getFront(){
    if(!dsize) {
        std::cout<<"Deque Empty!\n";
        return -1;
    }
    return head->next->val;
}

/**
 * 返回最后一个节点
 */
template<typename T>
T Deque<T>::getBack(){
    if(!dsize) {
        std::cout<<"Deque Empty!\n";
        return -1;
    }
    return tail->val;
}

/**
 * 遍历输出双端队列中的元素
 */
template<typename T>
void Deque<T>::traverse() {
    if(!dsize) {
        std::cout<<"Empty!\n";
        return;
    }
    ListNode * t = head->next;
    while(t!=NULL) {
        std::cout<<t->val<<" ";
        t = t->next;
    }
    std::cout<<std::endl;
}

#endif // DEQUE_H_INCLUDED
