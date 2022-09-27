#ifndef HASHTABLE_H_INCLUDED
#define HASHTABLE_H_INCLUDED

#ifndef ARRAY_H_INCLUDED
#include "Array.h"
#endif // ARRAY_H_INCLUDED

/**
 * 该模板类实现了键值对链表的结构，用于存储哈希表中的键值对
 */
template<typename K, typename V>
class Entry {
public:
	K key;  // 键key
	V val;  // 值value
	Entry<K, V> *next;  // 指向下一个键值对的指针
	Entry() {}          // 默认构造函数
	Entry(K key) :key(key), val(), next(NULL) {}             // 构造函数
	Entry(K key, V val) :key(key), val(val), next(NULL) {}  // 构造函数
	Entry<K, V>& operator=(const Entry<K, V>& other);   // 重载等于操作符，用于赋值
};

/**
 * 该模板类实现了哈希表，使用链地址法解决冲突
 * 模板中K为键，V为值，HashFunc为K的哈希函数
 * 使用该哈希表的Key必须重载==操作符
 */
template<typename K, typename V, class HashFunc>
class HashTable {
private:
	static const int DEFAULT_CAPACITY = 10000;  // 默认容量
	Entry<K, V> ** table;                      // 哈希表数组的指针
	int capacity, size;                         // 哈希表数组的容量与当前键值对的数量
	HashFunc hashFunc;                          // 哈希函数
public:
	HashTable(int capacity = DEFAULT_CAPACITY); // 构造函数
	~HashTable();                               // 释放哈希表的内存
	bool insert(const K& key, const V& val);    // 向哈希表中插入键值对
	bool remove(const K& key);                  // 删除哈希表中以key作为键的键值对
	bool contains(const K& key);                // 检查哈希表中是否包含以key作为键的键值对
	const V& operator[](const K& key) const;    // 访问哈希表中以key作为的键的键值对的value
	/*V& operator[](const K& key);*/
	Array<Entry<K, V>> traverse();              // 遍历哈希表，将键值对保存在数组中返回
	Array<K> getKeys();                         // 遍历哈希表，返回哈希表中的所有键值
	int getSize();                              // 返回哈希表中键值对的数量
	bool isEmpty();                             // 判断哈希表是否为空
	void clear();								// 清空哈希表
};

/**
 * 重载等于操作符，用于赋值
 */
template<typename K, typename V>
Entry<K, V>& Entry<K, V>::operator=(const Entry<K, V>& other) {
	this->key = other.key;
	this->val = other.val;
	this->next = other.next;
	return *this;
}

/**
 * 初始化哈希表，默认容量为DEFAULT_CAPACITY
 */
template<typename K, typename V, class HashFunc>
HashTable<K, V, HashFunc>::HashTable(int capacity) {
	table = new Entry<K, V>*[capacity];
	this->capacity = capacity;
	this->size = 0;
	for (int i = 0; i < capacity; ++i) {
		table[i] = NULL;
	}
}

/**
 * 释放哈希表的内存
 */
template<typename K, typename V, class HashFunc>
HashTable<K, V, HashFunc>::~HashTable() {
	clear();
	delete[] table;
}

/**
 * 向哈希表中插入(key,val)的键值对，若哈希表中
 * 已存在key则插入失败返回false，插入成功返回true
 */
template<typename K, typename V, class HashFunc>
bool HashTable<K, V, HashFunc>::insert(const K& key, const V& val) {
	// 若key已存在则插入失败
	if (contains(key)) {
		return false;
	}
	int index = hashFunc(key) % capacity;
	Entry<K, V> * entry = new Entry<K, V>(key, val);
	// 采用头插法将新的键值对插入到table[index]的链表中
	entry->next = table[index];
	table[index] = entry;
	++size;
	return true;
}

/**
 * 删除哈希表中键为key的键值对，若哈希表中没有
 * 该key则返回false，删除成功返回true
 */
template<typename K, typename V, class HashFunc>
bool HashTable<K, V, HashFunc>::remove(const K& key) {
	int index = hashFunc(key) % capacity;
	Entry<K, V> *p = table[index], *prev = NULL;
	while (p != NULL) {
		if (p->key == key) {
			if (prev == NULL) {
				// 删除的是第一个节点
				table[index] = p->next;
			}
			else {
				prev->next = p->next;
			}
			delete p;
			--size;
			return true;
		}
		prev = p;
		p = p->next;
	}
	// 没有找到key，无法删除
	return false;
}

/**
 * 判断哈希表中是否含有键为key的键值对
 */
template<typename K, typename V, class HashFunc>
bool HashTable<K, V, HashFunc>::contains(const K& key) {
	int index = hashFunc(key) % capacity;
	Entry<K, V> * p = table[index];
	while (p != NULL) {
		if (p->key == key) {
			return true;
		}
		p = p->next;
	}
	return false;
}

/**
 * 返回哈希表中键为key的键值对的value
 */
template<typename K, typename V, class HashFunc>
const V& HashTable<K, V, HashFunc>::operator[](const K& key) const {
	int index = hashFunc(key) % capacity;
	Entry<K, V> * p = table[index];
	while (p != NULL) {
		if (p->key == key) {
			return p->val;
		}
		p = p->next;
	}
	return *(new V());
}


/*template<typename K, typename V, class HashFunc>
V& HashTable<K, V, HashFunc>::operator[](const K& key) {
	int index = hashFunc(key) & capacity;
	Entry<K, V> * p = table[index];
	// 在table中查找key，若存在则返回其cal
	while(p != NULL) {
		if(p->key == key) {
			return p->val;
		}
		p = p->next;
	}
	// 若不存在则插入key，并返回其val，令size加一
	Entry<K, V> * entry = new Entry<K, V>(key);
	// 采用头插法将新的键值对插入到table[index]的链表中
	entry->next = table[index];
	table[index] = entry;
	++size;
	return entry->val;
}*/

/**
 * 返回哈希表中键值对的数量
 */
template<typename K, typename V, class HashFunc>
int HashTable<K, V, HashFunc>::getSize() {
	return this->size;
}

/**
 * 判断哈希表是否为空
 */
template<typename K, typename V, class HashFunc>
bool HashTable<K, V, HashFunc>::isEmpty() {
	return this->size == 0;
}

/**
 * 判断哈希表是否为空
 */
template<typename K, typename V, class HashFunc>
void HashTable<K, V, HashFunc>::clear() {
	for (int i = 0; i < capacity; ++i) {
		Entry<K, V> *p = table[i], *temp;
		while (p != NULL) {
			temp = p;
			p = p->next;
			delete temp;
		}
		table[i] = NULL;
	}
	size = 0;
}

/**
 * 遍历哈希表，将哈希表中的键值对存在Array数组中返回
 */
template<typename K, typename V, class HashFunc>
Array<Entry<K, V>> HashTable<K, V, HashFunc>::traverse() {
	Array<Entry<K, V>> arr;
	for (int i = 0; i < capacity; ++i) {
		Entry<K, V> *p = table[i];
		while (p != NULL) {
			Entry<K, V> e(p->key, p->val);
			arr.pushBack(e);
			p = p->next;
		}
	}
	return arr;
}

/**
 * 遍历哈希表，返回哈希表中的所有键值
 */
template<typename K, typename V, class HashFunc>
Array<K> HashTable<K, V, HashFunc>::getKeys() {
	Array<K> arr;
	for (int i = 0; i < capacity; ++i) {
		Entry<K, V> *p = table[i];
		while (p != NULL) {
			arr.pushBack(p->key);
			p = p->next;
		}
	}
	return arr;
}

#endif // HASHTABLE_H_INCLUDED
