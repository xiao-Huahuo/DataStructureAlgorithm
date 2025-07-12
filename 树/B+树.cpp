#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class BPlusTree
{
private:
    // B+树节点
    struct Node
    {
        bool is_leaf;            // 是否为叶子节点
        vector<int> keys;        // 关键字（有序）
        vector<Node *> children; // 子节点（非叶子节点专用）
        Node *next;              // 叶子节点的链表指针（B+树特有）
        Node *parent;            // 父节点（可选，用于简化实现）

        Node(bool leaf = false) : is_leaf(leaf), next(nullptr), parent(nullptr) {}
    };

    Node *root;
    int order; // B+树的阶（每个节点最多 order 个子节点）

public:
    BPlusTree(int m) : root(nullptr), order(m) {}

    // 查找关键字
    bool search(int key)
    {
        if (!root)
            return false;
        Node *node = root;
        while (!node->is_leaf)
        {
            auto it = upper_bound(node->keys.begin(), node->keys.end(), key);
            int idx = it - node->keys.begin();
            node = node->children[idx];
        }
        return binary_search(node->keys.begin(), node->keys.end(), key);
    }

    // 插入关键字
    void insert(int key)
    {
        if (!root)
        {
            root = new Node(true);
            root->keys.push_back(key);
            return;
        }

        Node *leaf = findLeaf(key);
        insertIntoLeaf(leaf, key);

        if (leaf->keys.size() >= order)
        {
            splitLeaf(leaf);
        }
    }

    // 删除关键字
    void remove(int key)
    {
        if (!root)
            return;
        Node *leaf = findLeaf(key);
        auto it = find(leaf->keys.begin(), leaf->keys.end(), key);
        if (it == leaf->keys.end())
            return; // 不存在

        leaf->keys.erase(it);
        if (leaf != root && leaf->keys.size() < (order + 1) / 2 - 1)
        {
            mergeOrRedistribute(leaf);
        }
    }

private:
    // 辅助函数
    Node *findLeaf(int key)
    {
        Node *node = root;
        while (!node->is_leaf)
        {
            auto it = upper_bound(node->keys.begin(), node->keys.end(), key);
            int idx = it - node->keys.begin();
            node = node->children[idx];
        }
        return node;
    }

    void insertIntoLeaf(Node *leaf, int key)
    {
        auto it = upper_bound(leaf->keys.begin(), leaf->keys.end(), key);
        leaf->keys.insert(it, key);
    }

    void splitLeaf(Node *leaf)
    {
        Node *new_leaf = new Node(true);
        int split_pos = leaf->keys.size() / 2;
        new_leaf->keys.assign(leaf->keys.begin() + split_pos, leaf->keys.end());
        leaf->keys.resize(split_pos);

        new_leaf->next = leaf->next;
        leaf->next = new_leaf;
        new_leaf->parent = leaf->parent;

        insertIntoParent(leaf, new_leaf->keys[0], new_leaf);
    }

    void insertIntoParent(Node *old_node, int key, Node *new_node)
    {
        // 实现父节点插入和分裂（递归）
        // （略去详细实现，逻辑类似B树的分裂）
    }

    void mergeOrRedistribute(Node *node)
    {
        // 合并或重新分配关键字（递归）
        // （略去详细实现，逻辑类似B树的合并）
    }
};