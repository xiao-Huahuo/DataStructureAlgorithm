#include <iostream>
#include <algorithm>
#include<functional>
using namespace std;

class RBT
{
public:
    enum Color
    {
        RED,
        BLACK
    };

    struct Node
    {
        int val;
        Node *left;
        Node *right;
        Node *parent;
        Color color;
        Node(int x) : val(x), left(nullptr), right(nullptr), parent(nullptr), color(RED) {}
    };

    Node *root;
    Node *nil; // 哨兵节点（代替 nullptr，表示叶子节点）

    RBT()
    {
        nil = new Node(0);
        nil->color = BLACK;
        root = nil;
    }

    // 左旋（与 AVL 类似，但需处理 parent 指针）
    void leftRotate(Node *x)
    {
        Node *y = x->right;
        x->right = y->left;
        if (y->left != nil)
            y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == nil)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    // 右旋（与 AVL 类似，但需处理 parent 指针）
    void rightRotate(Node *y)
    {
        Node *x = y->left;
        y->left = x->right;
        if (x->right != nil)
            x->right->parent = y;
        x->parent = y->parent;
        if (y->parent == nil)
            root = x;
        else if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
        x->right = y;
        y->parent = x;
    }

    // 插入修复（处理红黑树性质）
    void insertFixup(Node *z)
    {
        while (z->parent->color == RED)
        {
            if (z->parent == z->parent->parent->left)
            {
                Node *y = z->parent->parent->right;
                if (y->color == RED)
                { // Case 1: 叔叔是红色
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->right)
                    { // Case 2: 叔叔是黑色，且 z 是右孩子
                        z = z->parent;
                        leftRotate(z);
                    }
                    // Case 3: 叔叔是黑色，且 z 是左孩子
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rightRotate(z->parent->parent);
                }
            }
            else
            { // 对称情况（父节点是右孩子）
                Node *y = z->parent->parent->left;
                if (y->color == RED)
                {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->left)
                    {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    // 插入节点
    void insert(int val)
    {
        Node *z = new Node(val);
        Node *y = nil;
        Node *x = root;
        while (x != nil)
        {
            y = x;
            if (z->val < x->val)
                x = x->left;
            else
                x = x->right;
        }
        z->parent = y;
        if (y == nil)
            root = z;
        else if (z->val < y->val)
            y->left = z;
        else
            y->right = z;
        z->left = nil;
        z->right = nil;
        z->color = RED;
        insertFixup(z);
    }

    // 查找节点（与 BST 相同）
    Node *search(Node *x, int val)
    {
        if (x == nil)
            return nil;
        if (val == x->val)
            return x;
        return val < x->val ? search(x->left, val) : search(x->right, val);
    }

    // 检查是否为有效的红黑树
    bool isValidRedBlackTree()
    {
        if (root->color != BLACK)
            return false; // 性质 2: 根是黑色
        int blackCount = -1;
        function<bool(Node *, int)> check = [&](Node *node, int currentBlackCount)
        {
            if (node == nil)
            {
                if (blackCount == -1)
                    blackCount = currentBlackCount;
                else if (currentBlackCount != blackCount)
                    return false;
                return true;
            }
            if (node->color == RED && node->parent->color == RED) // 性质 4: 红节点的子节点必须是黑色
                return false;
            if (node->color == BLACK)
                currentBlackCount++;
            return check(node->left, currentBlackCount) && check(node->right, currentBlackCount);
        };
        return check(root, 0);
    }
};