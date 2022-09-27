#include <iostream>
#include <cstdio>
#include "LinkQueue.h"

using namespace std;

// 树的节点
struct TreeNode{
    int val;                // 该节点的值
    TreeNode *left, *right; // 指向左子树和右子树
    TreeNode(int x = 0):val(x), left(NULL), right(NULL) {}
};

// 自定义二叉树数据结构
class BinaryTree {
private:
    TreeNode *root; // 二叉树的根节点

    void deleteNodes(TreeNode *root);                    // 使用递归方法释放树中节点的内存，由析构函数调用
    bool isTwoTreesEquals(TreeNode *t1, TreeNode *t2);   // 使用递归方法判断两个树是否完全相同
    TreeNode* deserialize(char* str);                    // 从serialize函数生成的字符串中解析并构建树
    TreeNode* copyTree(TreeNode* root);                  // 深拷贝root指针所指的树，并返回新树的根节点

public:
    BinaryTree();                               // 默认构造函数，创建一个空树
    BinaryTree(char* str);                      // str为serialize函数生成的字符串，从字符串中解析并构建树
    BinaryTree(const BinaryTree& tree);         // 拷贝构造函数
    ~BinaryTree();                              // 释放树的内存
    bool isEquals(const BinaryTree& tree);      // 判断该树是否与tree完全相同
    char* serialize();                          // 将树的信息序列化为字符串，并可根据该字符串重新生成树
    static bool checkSerializeFormat(char* str);// 检查反序列化的字符串是否符合正确的格式
};

// 将存储在字符串中的整型数转化为int并返回，当溢出时返回INT_MAX或INT_MIN
int myAtoi(char* str);

int main() {
    /***测试用例1***/
    char test1str[100] = "[1,3,null,null,2]";
    char ans1strp[100] = "[3,1,null,null,2]";
    BinaryTree test1(test1str);
    BinaryTree ans1(ans1strp);


    return 0;
}


// 默认构造函数，创建一个空树
BinaryTree::BinaryTree() {
    root = NULL;
}

// str为serialize函数生成的字符串，从字符串中解析并构建树
BinaryTree::BinaryTree(char* str) {
    if(!checkSerializeFormat(str)) {
        cout<<"字符串格式错误，请勿包含空格等非法字符\n";
        root = NULL;
    }
    else root = deserialize(str);
}

// 拷贝构造函数
BinaryTree::BinaryTree(const BinaryTree& tree) {
    root = copyTree(tree.root);
}

// 深拷贝复制root指针所指的树，并返回新树的根节点
TreeNode* BinaryTree::copyTree(TreeNode* root) {
    if(!root) return NULL;
    TreeNode* newRoot = new TreeNode(root->val);
    newRoot->left = copyTree(root->left);
    newRoot->right = copyTree(root->right);
    return newRoot;
}

// 释放树的内存
BinaryTree::~BinaryTree() {
    deleteNodes(root);
}

// 使用递归方法释放树中节点的内存，由析构函数调用
void BinaryTree::deleteNodes(TreeNode *root) {
    if(!root) return;
    deleteNodes(root->left);
    deleteNodes(root->right);
    //cout<<"delete"<<root->val<<endl;
    delete root;
}

// 判断该树是否与tree完全相同
bool BinaryTree::isEquals(const BinaryTree& tree) {
    return isTwoTreesEquals(this->root, tree.root);
}

// 使用递归方法判断两个树是否完全相同
bool BinaryTree::isTwoTreesEquals(TreeNode *t1, TreeNode *t2) {
    if(t1 == NULL && t2 == NULL) return true;
    else if(t1 != NULL && t2 != NULL) {
        return t1->val == t2->val &&
                isTwoTreesEquals(t1->left, t2->left) &&
                isTwoTreesEquals(t1->right, t2->right);
    }
    return false;
}

// 将树的信息序列化为字符串，并可根据该字符串重新生成树
char* BinaryTree::serialize() {
    char *str = new char[10005];
    int pos = 0;
    str[pos++] = '[';
    // 若树为空，则直接返回"[]"
    if(root == NULL) {
        str[pos++] = ']';
        str[pos++] = '\0';
        return str;
    }
    // BFS进行层次序遍历
    LinkQueue<TreeNode*> que;
    que.push(root);

    while(!que.isEmpty()) {
        // 取出队首元素对其进行处理并拓展子节点
        TreeNode *t = que.getFront();
        que.pop();
        if(t != NULL) {
            // 添加子节点
            que.push(t->left);
            que.push(t->right);
            char numStr[15];
            sprintf(numStr, "%d", t->val);
            for(int i=0; numStr[i] != '\0'; ++i) {
                str[pos++] = numStr[i];
            }
        }
        else {
            str[pos++] = 'n';
            str[pos++] = 'u';
            str[pos++] = 'l';
            str[pos++] = 'l';
        }
        str[pos++] = ',';
    }
    // 去除字符串尾部多余的null
    while(str[pos] < '0' || str[pos] > '9') --pos;
    str[++pos] = ']';
    str[++pos] = '\0';

    return str;
}

// 从serialize函数生成的字符串中解析并构建树
TreeNode* BinaryTree::deserialize(char* str) {
    int strLen = 0, nodeNum = 1;
    // 计算字符串长度及其中的节点数量
    while(str[strLen] != '\0') {
        if(str[strLen] == ',') ++nodeNum;
        ++strLen;
    }
    if(nodeNum == 1 && strLen == 2) return NULL;
    TreeNode** nodes = new TreeNode*[nodeNum];
    // 识别字符串中的树节点，并将其存储在nodes数组中
    char t[25];
    int tPos = 0, nCnt = 0;
    --strLen;
    for(int i=1; i<strLen; ++i) {
        // 提取出一个节点对应的字符串
        if(str[i] == ',') {
            t[tPos] = '\0';
            TreeNode * tmp = NULL;
            // 若不为NULL则说明是数字
            if(t[0] != 'n') {
                tmp = new TreeNode(myAtoi(t));
            }
            nodes[nCnt++] = tmp;
            tPos = 0;
        }
        else {
            t[tPos++] = str[i];
        }
    }
    t[tPos] = '\0';
    // 处理最后一个数据，当其为数字时需要添加进nodes数组
    if(tPos != 0 && t[0] != 'n') {
        nodes[nCnt++] = new TreeNode(myAtoi(t));
    }
    // 构建树中节点的关系
    // cur指向当前处理的节点
    // left指向当前处理节点的左子节点，left+1即为当前节点的右子节点
    int cur = 0, left = 1;
    while(left < nCnt) {
        // 跳过NULL
        if(nodes[cur] == NULL) ++cur;
        else {
            // 找到当前节点的左子节点
            if(left < nCnt)
                nodes[cur]->left = nodes[left];
            // 找到当前节点的右子节点
            if(left+1 < nCnt)
                nodes[cur]->right = nodes[left+1];
            ++cur;
            left += 2;
        }
    }
    return nodes[0];
}

// 检查反序列化的字符串是否符合正确的格式
bool BinaryTree::checkSerializeFormat(char* str) {
    int strLen = 0;
    bool lastComma = false;
    while(str[strLen] != '\0') {
        if(str[strLen] == ',') {
            if(lastComma) return false;
            lastComma = true;
        }
        else lastComma = false;
        ++strLen;
    }

    // 检查是否有中括号
    if(str[0] != '[' || str[strLen-1] != ']')
        return false;
    // 空树
    if(strLen == 2) return true;

    --strLen;
    bool curIsNull = false, firstAlpha = true;
    for(int i=1; i<strLen; ++i) {

        // 新节点第一个字母
        if(firstAlpha) {
            curIsNull = (str[i] == 'n');
            firstAlpha = false;
            // 去除负号
            if(str[i]!='-') --i;
        }
        else if(str[i] == ',') {
            firstAlpha = true;
        }
        else if(curIsNull) {
            // 当前应为null
            if(i + 3 >= strLen) return false;
            if(str[i] != 'n' || str[i+1] != 'u' || str[i+2] != 'l' || str[i+3] != 'l')
                return false;
            i += 3;
            // null只能出现一次
            if(i+1 < strLen && str[i+1] != ',')
                return false;
        }
        else {
            // 当前应为数字
            if(str[i] < '0' || str[i] > '9')
                return false;
        }
    }
    // 最后一个为逗号或null
    if(curIsNull || firstAlpha) {
        cout<<"最后一个节点不应为NULL\n";
        return false;
    }
    return true;
}

// 构造函数
template<typename T>
LinkQueue<T>::LinkQueue() {
    head = new ListNode();
    rear = head;
    qSize = 0;
}

// 析构函数
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

// 判断队列是否为空
template<typename T>
bool LinkQueue<T>::isEmpty() {
    return qSize == 0;
}

// 将队首元素删除
template<typename T>
void LinkQueue<T>::pop() {
    ListNode *p = head->next;
    if(!p) return;
    if(p == rear) rear = head;
    head->next = p->next;
    delete p;
    qSize--;
}

// 向队尾添加元素
template<typename T>
void LinkQueue<T>::push(T val) {
    rear->next = new ListNode(val);
    rear = rear->next;
    qSize++;
}

// 取出队首元素
template<typename T>
T LinkQueue<T>::getFront() {
    if(!head->next) {
        cout<<"ERROR:Empty Queue!\n";
        return head->val;
    }
    return head->next->val;
}

// 获得队列中的元素个数
template<typename T>
int LinkQueue<T>::getSize() {
    return qSize;
}


// 将存储在字符串中的整型数转化为int并返回，当溢出时返回INT_MAX或INT_MIN
int myAtoi(char* str) {
    if(!str || str[0] == '\0') return 0;
    int i=0;
    while(str[i] != '\0' && str[i] == ' ') i++;
    // flag为整型树的符号，sum为数字的绝对值
    int flag = 1, sum = 0;
    // 判断是否为负数
    if(str[i] == '-') {
        flag = -1;
        i++;
    }else if(str[i] == '+') i++;
    else if(str[i] < '0' || str[i] > '9') return 0;
    // exceedMax为溢出的标志
    // exceedMax=1说明超出INT_MAX
    // exceedMax=-1说明小于INT_MIN
    int exceedMax = 0, t;
    // pThreshold为溢出前sum的临界值
    int pThreshold = INT_MAX / 10;
    // pLast为正数溢出的临界值的个位数，mLast为负数溢出的临界值的个位数
    int pLast = INT_MAX % 10, mLast = pLast + 1;
    // 对字符串中的数字进行提取
    while(str[i] != '\0' && str[i] >= '0' && str[i] <= '9') {
        t = str[i] - '0';
        // 溢出判断
        if(flag==1 && (sum>pThreshold || sum==pThreshold && t>=pLast)) {
            // 超出INT_MAX
            exceedMax = 1;
            break;
        }else if(flag==-1 && (sum>pThreshold || sum==pThreshold && t>=mLast)) {
            // 小于INT_MIN
            exceedMax = -1;
            break;
        }
        sum = sum*10 + t;
        i++;
    }
    if(exceedMax != 0) cout<<"int数据溢出!\n";
    // 若溢出则返回INT_MAX或INT_MIN
    // 否则返回数字绝对值乘以其符号，即数字本身
    return exceedMax==1? INT_MAX : exceedMax==-1? INT_MIN : sum*flag;
}
