#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>
using namespace std;
class BTree
{
private:
    // B-树节点
    struct Node
    {
        bool is_leaf;            // 是否为叶子节点
        vector<int> keys;        // 关键字（有序）
        vector<Node *> children; // 子节点
        Node *parent;            // 父节点

        Node(bool leaf = false) : is_leaf(leaf), parent(nullptr) {}
    };

    Node *root;
    int order; // B-树的阶（每个节点最多 order 个子节点）

public:
    BTree(int m) : root(nullptr), order(m) {}

    // 查找关键字
    bool search(int key)
    {
        Node *node = root;
        while (node)
        {
            auto it = lower_bound(node->keys.begin(), node->keys.end(), key);
            if (it != node->keys.end() && *it == key)
                return true;
            if (node->is_leaf)
                return false;
            int idx = it - node->keys.begin();
            node = node->children[idx];
        }
        return false;
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

        Node *node = root;
        while (!node->is_leaf)
        {
            auto it = upper_bound(node->keys.begin(), node->keys.end(), key);
            int idx = it - node->keys.begin();
            node = node->children[idx];
        }

        insertIntoNode(node, key);
        if (node->keys.size() >= order)
        {
            splitNode(node);
        }
    }

    // 删除关键字
    void remove(int key)
    {
        if (!root)
            return;
        Node *node = findNode(key);
        auto it = find(node->keys.begin(), node->keys.end(), key);
        if (it == node->keys.end())
            return; // 不存在

        if (node->is_leaf)
        {
            node->keys.erase(it);
            if (node != root && node->keys.size() < (order - 1) / 2)
            {
                mergeOrRedistribute(node);
            }
        }
        else
        {
            // 非叶子节点删除（替换前驱/后继）
            // （略去详细实现）
        }
    }

private:
    // 辅助函数
    Node *findNode(int key)
    {
        Node *node = root;
        while (node)
        {
            auto it = lower_bound(node->keys.begin(), node->keys.end(), key);
            if (it != node->keys.end() && *it == key)
                return node;
            if (node->is_leaf)
                return nullptr;
            int idx = it - node->keys.begin();
            node = node->children[idx];
        }
        return nullptr;
    }

    void insertIntoNode(Node *node, int key)
    {
        auto it = upper_bound(node->keys.begin(), node->keys.end(), key);
        node->keys.insert(it, key);
    }

    void splitNode(Node *node)
    {
        Node *new_node = new Node(node->is_leaf);
        int split_pos = node->keys.size() / 2;
        new_node->keys.assign(node->keys.begin() + split_pos + 1, node->keys.end());
        node->keys.resize(split_pos);

        if (!node->is_leaf)
        {
            new_node->children.assign(node->children.begin() + split_pos + 1, node->children.end());
            node->children.resize(split_pos + 1);
        }

        insertIntoParent(node, node->keys[split_pos], new_node);
    }

    void insertIntoParent(Node *old_node, int key, Node *new_node)
    {
        // 父节点插入和分裂（递归）
        // （略去详细实现）
    }

    void mergeOrRedistribute(Node *node)
    {
        // 合并或重新分配关键字（递归）
        // （略去详细实现）
    }
};