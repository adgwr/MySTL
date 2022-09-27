#include <iostream>
#include <ctime>
#include <cstdlib>
#define random(x) (rand()%x)

using namespace std;

struct Node {
    int val;
    Node(int val=0):val(val) {}

    bool operator<=(const Node& n) {
        // this->val < n.val 从大至小排序
        // this->val > n.val 从小至大排序
        return this->val <= n.val;
    }
};

class QuickSort {
public:
    static void quickSort(Node *a, int left, int right);
};

int main() {
    srand((int)time(0));

    Node a[100];
    for(int i=0; i<100; i++) {
        a[i].val = random(100);
    }

    QuickSort::quickSort(a,0,100);

    for(int i=0; i<100; i++) {
        cout<<a[i].val<<endl;
    }
    return 0;
}

void QuickSort::quickSort(Node *a, int left, int right) {
    if(left >= right) return;
    int i = left;
    int j = right-1;
    Node key = a[left];
    while(i < j) {
        while(i < j && key <= a[j]) {
            j--;
        }
        a[i] = a[j];
        while(i < j && a[i] <= key) {
            i++;
        }
        a[j] = a[i];
    }
    a[i] = key;
    quickSort(a, left, i);
    quickSort(a, i+1, right);
}
