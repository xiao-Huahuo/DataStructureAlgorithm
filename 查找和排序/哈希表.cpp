#include <iostream>
#include <vector>
#include <list>
#include <string>

using namespace std;
// 哈希表__链地址法
class HashTable
{
    vector<list<int>> table;
    int size;

public:
    // 构造函数，初始化哈希桶数量
    HashTable(int size) : size(size), table(size) {}

    // 哈希函数：将整数 key 映射到 [0, size-1] 范围
    int hash(int key)
    {
        return key % size;
    }

    // 插入：防止重复插入
    void insert(int key)
    {
        int idx = hash(key);
        for (int num : table[idx])
        {
            if (num == key)
            {
                // 已存在，跳过插入
                return;
            }
        }
        table[idx].push_back(key);
    }

    // 查找：返回是否存在 key
    bool search(int key)
    {
        int idx = hash(key);
        for (int num : table[idx])
        {
            if (num == key)
            {
                return true;
            }
        }
        return false;
    }

    // 删除指定 key
    void remove(int key)
    {
        int idx = hash(key);
        table[idx].remove(key); // list 自带 remove，自动删除所有匹配元素
    }

};
// 哈希表__线性探测法(∈开放寻址法)(低配版)
class HashTable2
{
private:
    static const int SIZE = 10; // 固定大小
    vector<int> table;

public:
    HashTable2() : table(SIZE, -1) {} // 用-1表示空位

    // 最简单的哈希函数：取模
    int hash(int key)
    {
        return key % SIZE;
    }

    // 插入键值
    void insert(int key)
    {
        int idx = hash(key);

        // 线性探测解决冲突
        while (table[idx] != -1)
            idx = (idx + 1) % SIZE; // 移动到下一个位置

        table[idx] = key;
    }

    // 查找键
    bool search(int key)
    {
        int idx = hash(key);
        int start = idx;
        idx++;

        while (idx != start && table[idx] != -1)
        {
            if (table[idx] == key)
                return true;
            idx = (idx + 1) % SIZE;
        }
        if (table[idx] == key)
            return true;
        return false;
    }
};

// 哈希表__线性探测法(高级版本)
class HashTable3
{
    enum Status
    {
        EMPTY,    // 空
        OCCUPIED, // 已占用
        DELETED   // 已删除
    };

    struct Entry
    {
        int key;
        int len; // 查找长度（探测次数）
        Status status;

        Entry() : key(0), len(0), status(EMPTY) {}
    };

    vector<Entry> table;
    int size;

    int hash(int key)
    {
        return key % size;
    }

public:
    HashTable3(int size) : size(size), table(size) {}

    // 插入
    void insert(int key)
    {
        int idx = hash(key);
        for (int i = 0; i < size; ++i)
        {
            int id = (idx + i) % size;

            if (table[id].status == OCCUPIED && table[id].key == key)
                return; // 已存在，跳过插入

            if (table[id].status == EMPTY || table[id].status == DELETED)
            {
                table[id].key = key;
                table[id].len = i + 1; // 插入用了 i+1 次探测
                table[id].status = OCCUPIED;
                return;
            }
        }
        cout << "哈希表已满，无法插入 key=" << key << endl;
    }

    // 查找（返回是否存在，并显示查找长度）
    bool search(int key)
    {
        int idx = hash(key);
        for (int i = 0; i < size; ++i)
        {
            int id = (idx + i) % size;

            //遇到EMPTY桶的时候应该结束查找
            if (table[id].status == EMPTY)
                return false;

            if (table[id].status == OCCUPIED && table[id].key == key)
            {
                cout << "查找 key=" << key << " 时用了 " << i + 1 << " 次探测" << endl;
                return true;
            }
        }
        return false;
    }

    // 删除
    void remove(int key)
    {
        int idx = hash(key);
        for (int i = 0; i < size; ++i)
        {
            int id = (idx + i) % size;

            if (table[id].status == EMPTY)
                return;

            if (table[id].status == OCCUPIED && table[id].key == key)
            {
                table[id].status = DELETED;
                return;
            }
        }
    }

};
