#include <iostream>
#include "HashTable.h"
#include "Array.h"

using namespace std;

struct Key {
    char *str;
    Key(char *str = NULL):str(str) {}
    Key(const Key& other) {
        this->str = other.str;
    }
    bool operator==(const Key& other) {
        int i;
        for(i = 0; str[i] != '\0' && other.str[i] != '\0'; ++i) {
            if(str[i] != other.str[i]) return false;
        }
        return str[i] == '\0' && other.str[i] == '\0';
    }

};

struct HashFunc {
    int operator()(const Key& key) const{
        int hash_val = 0;
        for(int i = 0; key.str[i] != '\0'; ++i) {
            hash_val = hash_val * 31 + key.str[i];
        }
        return hash_val;
    }
};

int main() {
    //char[][10] = {"100", "101", "111", "123"};
    Array<Entry<Key, int>> arr;
    if(1 > 0 ) {
        HashTable<Key, int, HashFunc> h;
        h.insert(Key("12345"), 5);
        h.insert(Key("12333"), 1);
        h.insert(Key("dash"), 3);
        arr = h.traverse();
        h = HashTable<Key, int, HashFunc>();
    }

    for(int i=0; i<arr.getSize(); ++i) {
        cout<<arr[i].key.str<<" "<<arr[i].val<<endl;
    }

    return 0;
}
