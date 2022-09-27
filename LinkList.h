#ifndef LINKLIST_H_INCLUDED
#define LINKLIST_H_INCLUDED
#include <iostream>

/**
 * 实现了单链表，并提供插入删除等操作
 */
template<typename T>
class LinkList{
private:
    // 链表节点
    struct ListNode {
        T val;
        ListNode *next;
        ListNode(T x):val(x), next(NULL) {}
        ListNode():next(NULL) {}
    };
    ListNode *head;
    int lsize;
public:
    LinkList();                   // 构造函数
    ~LinkList();                  // 析构函数
    int getLength();              // 获取链表长度
    bool isEmpty();               // 判断链表是否为空
    bool isEquals(const LinkList& l);// 判断链表是否相等
    void pushBack(T val);         // 在尾部添加节点
    void traverse();              // 遍历链表
    void popBack();               // 删除最后一个节点
    bool deleteNode(int pos);     // 删除指定位置的节点，返回true删除成功，返回false删除失败
    void insertNode(int pos, T val); // 在指定位置插入节点
};

/**
 * 初始化链表
 */
template<typename T>
LinkList<T>::LinkList() {
    head = new ListNode;
    lsize = 0;
}

/**
 * 销毁单链表
 */
template<typename T>
LinkList<T>::~LinkList() {
    if(!head) return;
    ListNode* p = head->next;
    while(p) {
        delete head;
        head = p;
        p = p->next;
    }
    delete head;
}


/**
 * 获取单链表的长度
 */
template<typename T>
int LinkList<T>::getLength() {
    return lsize;
}

/**
 * 判断单链表是否为空
 */
template<typename T>
bool LinkList<T>::isEmpty() {
    return lsize == 0;
}

/**
 * 判断两个链表是否相等
 */
template<typename T>
bool LinkList<T>::isEquals(const LinkList& l) {
    if(this->size != l.size) return false;
    ListNode *p = this->head, *q = l.head;
    while(p!=NULL && q!=NULL) {
        if(p->val != p->val) return false;
        p = p->next;
        q = q->next;
    }
    return !p && !q;
}

/**
 * 在链表后添加节点
 */
template<typename T>
void LinkList<T>::pushBack(T val) {
    ListNode* p = head;
    while(p->next) {
        p = p->next;
    }
    p->next = new ListNode(val);
    lsize++;
}

/**
 * 遍历链表节点并输出
 */
template<typename T>
void LinkList<T>::traverse() {
    ListNode* p = head->next;
    if(!p) std::cout<<"链表为空";
    while(p) {
        std::cout<<p->val;
        if(p->next) std::cout<<"->";
        p = p->next;
    }
    std::cout<<std::endl;
}

/**
 * 删除最后一个节点
 */
template<typename T>
void LinkList<T>::popBack() {
    if(!head->next) return;
    ListNode *p = head->next;
    while(p->next && p->next->next) {
        p = p->next;
    }
    ListNode *t = p->next;
    delete t;
    p->next = NULL;
    lsize--;
}

/**
 * 删除指定位置的节点，下标从0开始
 */
template<typename T>
bool LinkList<T>::deleteNode(int pos) {
    if(!head->next || pos >= lsize || pos < 0) return false;
    ListNode *p = head->next, *last = head;
    for(int i=0; i<pos; ++i) {
        p = p->next;
        last = last->next;
    }
    last->next = p->next;
    delete p;
    lsize--;
    return true;
}

/**
 * 在指定位置前插入值为val的节点，下标从0开始
 */
template<typename T>
void LinkList<T>::insertNode(int pos, T val) {
    if(!head->next || pos >= lsize || pos < 0) return;
    ListNode *p = head->next, *last = head;
    for(int i=0; i<pos; ++i) {
        p = p->next;
        last = last->next;
    }
    last->next = new ListNode(val);
    last->next->next = p;
    lsize++;
}


#endif // LINKLIST_H_INCLUDED
