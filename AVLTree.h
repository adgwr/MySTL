#ifndef AVLTREE_H_INCLUDED
#define AVLTREE_H_INCLUDED

#ifndef ARRAY_H_INCLUDED
#include "Array.h"
#endif // ARRAY_H_INCLUDED

/**
 * 实现了AVL树，并提供了插入、删除、查找的基本功能
 */
template<typename T>
class AVLTree {
private:
    // 树节点的数据结构
    struct TreeNode {
        T val;
        TreeNode *left, *right;
        int h;
        TreeNode() {}
        TreeNode(T val):val(val), left(NULL), right(NULL), h(0) {}
        TreeNode(T val, TreeNode* l, TreeNode* r, int h):val(val), left(l), right(r), h(h) {}
    };

    TreeNode *root; // AVL树的根节点

    void rotateLeft(TreeNode *& k2);        // 对k2所指向的节点进行左单旋转
    void rotateRight(TreeNode *& k2);       // 对k2所指向的节点进行右单旋转
    void doubleRotateLeft(TreeNode *& k3);  // 对k3所指向的节点进行左双旋转
    void doubleRotateRight(TreeNode *& k3); // 对k3所指向的节点进行右双旋转
    int getHeight(TreeNode *p);             // 获取指针p指向的子树的高度
    void clearTree(TreeNode *& p);          // 清空树中的节点
    bool add(T e, TreeNode *& node);        // 向以node所指的子树添加元素e
    void remove(T e, TreeNode *& node);     // 从以node所指的子树中删除元素e
    void inOrder(TreeNode* root, Array<T>& arr);   // 中序遍历，将结果保存在arr中
    void preOrder(TreeNode* root, Array<T>& arr);  // 先序遍历，将结果保存在arr中
    void postOrder(TreeNode* root, Array<T>& arr); // 后序遍历，将结果保存在arr中

public:
    AVLTree();                          // 初始化AVL树
    ~AVLTree();                         // 释放AVL树的内存
    bool add(T e);                      // 向树中添加元素e
    void remove(T e);                   // 删除树中的元素e
    bool contains(T e);                 // 检查树中是否有元素e
    bool isEmpty();                     // 检查树是否为空
    Array<T> traverse(int mode = 0);    // 遍历AVL树
};

/**
 * 初始化AVL树
 */
template<typename T>
AVLTree<T>::AVLTree() {
    root = NULL;
}

/**
 * 释放AVL树的内存
 */
template<typename T>
AVLTree<T>::~AVLTree() {
    clearTree(root);
}

/**
 * 向AVL树中添加元素e
 */
template<typename T>
bool AVLTree<T>::add(T e) {
    return add(e, root);
}

/**
 * 内部方法，向AVL树中添加元素e
 */
template<typename T>
bool AVLTree<T>::add(T e, TreeNode *& node) {
    if(node == NULL) {
        // 找到插入位置
        node = new TreeNode(e);
    }
    else if(node->val < e) {
        // 插入值比当前节点大，插入到右子树中
        if(!add(e, node->right)) return false;
        // 自下而上调整高度h
        if(getHeight(node->right) - getHeight(node->left) == 2) {
            if(node->right->val < e) {
                rotateRight(node);
            }
            else {
                doubleRotateRight(node);
            }
        }
    }
    else if(e < node->val) {
        // 插入值比当前节点小，插入到左子树中
        if(!add(e, node->left)) return false;
        // 自下而上调整高度h
        if(getHeight(node->left) - getHeight(node->right) == 2) {
            if(e < node->left->val) {
                rotateLeft(node);
            }
            else {
                doubleRotateLeft(node);
            }
        }
    }
    else {
        return false;
    }
    int leftH = getHeight(node->left);
    int rightH = getHeight(node->right);
    node->h = (leftH > rightH ? leftH : rightH) + 1;
    return true;
}

/**
 * 删除AVL树中的元素e
 */
template<typename T>
void AVLTree<T>::remove(T e) {
    remove(e, root);
}

/**
 * 内部方法，删除AVL树中的元素e
 */
template<typename T>
void AVLTree<T>::remove(T e, TreeNode *& node) {
    if(node == NULL) return;
    if(node->val < e) {
        // 要删除的节点比当前节点大，在右子树中删除
        remove(e, node->right);
        // 自下而上调整高度h
        if(getHeight(node->left) - getHeight(node->right) == 2) {
            if(getHeight(node->left->left) > getHeight(node->left->right)) {
                rotateLeft(node);
            }
            else {
                doubleRotateLeft(node);
            }
        }
    }
    else if(e < node->val) {
        // 要删除的节点比当前节点小，在左子树中删除
        remove(e, node->left);
        // 自下而上调整高度h
        if(getHeight(node->right) - getHeight(node->left) == 2) {
            if(getHeight(node->right->right) > getHeight(node->right->left)) {
                rotateRight(node);
            }
            else {
                doubleRotateRight(node);
            }
        }
    }
    else {
        // 找到要删除的节点
        if(node->left != NULL && node->right != NULL) {
            // 若左右子树都不为空，维护AVL
            TreeNode *pmax = node->left;
            // 使用左子树中的最大值代替当前节点
            while(pmax->right != NULL) {
                pmax = pmax->right;
            }
            node->val = pmax->val;
            remove(node->val, node->left);
        }
        else {
            // 删除节点
            TreeNode *p = (node->left == NULL ? node->right : node->left);
            delete node;
            node = p;
        }
    }
    if(node != NULL) {
        int leftH = getHeight(node->left);
        int rightH = getHeight(node->right);
        node->h = (leftH > rightH ? leftH : rightH) + 1;
    }
}

/**
 * 在AVL树中查找是否包含元素e，若包含则返回true，否则返回false
 */
template<typename T>
bool AVLTree<T>::contains(T e) {
    TreeNode *p = root;
    while(p != NULL) {
        if(p->val < e) {
            p = p->right;
        }
        else if(e < p->val) {
            p = p->left;
        }
        else {
            return true;
        }
    }
    return false;
}

/**
 * 检查AVL树是否为空
 */
template<typename T>
bool AVLTree<T>::isEmpty() {
    return root == NULL;
}

/**
 * 遍历AVL并将中的元素存储在Array中返回
 * 参数traverseMode指定了以何种方式进行遍历，默认为中序遍历
 * 0:中序遍历
 * 1:先序遍历
 * 2:后序遍历
 */
template<typename T>
Array<T> AVLTree<T>::traverse(int traverseMode) {
    Array<T> arr;
    switch(traverseMode) {
    case 0:
        inOrder(root, arr);
        break;
    case 1:
        preOrder(root, arr);
        break;
    case 2:
        postOrder(root, arr);
        break;
    }
    return arr;
}


/**
 * 获取节点p的高度信息，若p为NULL则返回-1
 */
template<typename T>
int AVLTree<T>::getHeight(TreeNode *p) {
    return p == NULL ? 0 : p->h;
}

/**
 * 对节点k2进行左单旋转
 */
template<typename T>
void AVLTree<T>::rotateLeft(TreeNode *& k2) {
    // 旋转节点
    TreeNode* k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    // 更新高度
    int k1LeftH = getHeight(k1->left);
    int k1RightH = getHeight(k1->right);
    int k2LeftH = getHeight(k2->left);
    int k2RightH = getHeight(k2->right);
    k1->h = (k1LeftH > k1RightH ? k1LeftH : k1RightH) + 1;
    k2->h = (k2LeftH > k2RightH ? k2LeftH : k2RightH) + 1;
    // 将k1与原k2的父节点进行连接
    k2 = k1;
}

/**
 * 对节点k2进行单旋转
 */
template<typename T>
void AVLTree<T>::rotateRight(TreeNode *& k2) {
    // 旋转节点
    TreeNode* k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;
    // 更新高度
    int k1LeftH = getHeight(k1->left);
    int k1RightH = getHeight(k1->right);
    int k2LeftH = getHeight(k2->left);
    int k2RightH = getHeight(k2->right);
    k1->h = (k1LeftH > k1RightH ? k1LeftH : k1RightH) + 1;
    k2->h = (k2LeftH > k2RightH ? k2LeftH : k2RightH) + 1;
    // 将k1与原k2的父节点进行连接
    k2 = k1;
}

/**
 * 对节点k3进行左双旋转
 */
template<typename T>
void AVLTree<T>::doubleRotateLeft(TreeNode *& k3) {
    rotateRight(k3->left);
    rotateLeft(k3);
}

/**
 * 对节点k3进行右双旋转
 */
template<typename T>
void AVLTree<T>::doubleRotateRight(TreeNode *& k3) {
    rotateLeft(k3->right);
    rotateRight(k3);
}

/**
 * 释放以节点p为根节点的子树的内存
 */
template<typename T>
void AVLTree<T>::clearTree(TreeNode *& p) {
    if(!p) return;
    clearTree(p->left);
    clearTree(p->right);
    delete p;
    p = NULL;
}

/**
 * 以中序遍历的方式将AVL树中的节点保存在arr数组中
 */
template<typename T>
void AVLTree<T>::inOrder(TreeNode* root, Array<T>& arr) {
    if(!root) return;
    inOrder(root->left, arr);
    arr.pushBack(root->val);
    inOrder(root->right, arr);
}

/**
 * 以先序遍历的方式将AVL树中的节点保存在arr数组中
 */
template<typename T>
void AVLTree<T>::preOrder(TreeNode* root, Array<T>& arr) {
    if(!root) return;
    arr.pushBack(root->val);
    inOrder(root->left, arr);
    inOrder(root->right, arr);
}

/**
 * 以后序遍历的方式将AVL树中的节点保存在arr数组中
 */
template<typename T>
void AVLTree<T>::postOrder(TreeNode* root, Array<T>& arr) {
    if(!root) return;
    inOrder(root->left, arr);
    inOrder(root->right, arr);
    arr.pushBack(root->val);
}


#endif // AVLTREE_H_INCLUDED
