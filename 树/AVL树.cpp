#include <iostream>
#include <algorithm>
#include <functional>
using namespace std;

class AVL
{
public:
    struct Node
    {
        int val;
        Node *left;
        Node *right;
        int height; // 结点高度
        Node(int x) : val(x), left(nullptr), right(nullptr), height(1) {}
    };

    // 计算结点高度
    int height(Node *node)
    {
        if (!node)
            return 0;
        return node->height;
    }

    // 计算平衡因子（左子树高度 - 右子树高度）
    int balanceFactor(Node *node)
    {
        if (!node)
            return 0;
        return height(node->left) - height(node->right);
    }

    // 更新结点高度
    void updateHeight(Node *node)
    {
        if (!node)
            return;
        node->height = 1 + max(height(node->left), height(node->right));
    }

    // 右旋（LL型不平衡）
    Node *rightRotate(Node *y)
    {
        Node *x = y->left;
        Node *T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    // 左旋（RR型不平衡）
    Node *leftRotate(Node *x)
    {
        Node *y = x->right;
        Node *T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    // 插入结点（自动平衡）
    Node *insert(Node *root, int val)
    {
        if (!root)
            return new Node(val);

        if (val < root->val)
            root->left = insert(root->left, val);
        else if (val > root->val)
            root->right = insert(root->right, val);
        else
            return root; // 重复值不插入

        updateHeight(root); // 更新高度

        int bf = balanceFactor(root); // 计算平衡因子

        // LL 情况（左子树高，且新结点在左子树的左子树）
        if (bf > 1 && val < root->left->val)
            return rightRotate(root);

        // RR 情况（右子树高，且新结点在右子树的右子树）
        if (bf < -1 && val > root->right->val)
            return leftRotate(root);

        // LR 情况（左子树高，但新结点在左子树的右子树）
        if (bf > 1 && val > root->left->val)
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        // RL 情况（右子树高，但新结点在右子树的左子树）
        if (bf < -1 && val < root->right->val)
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root; // 无需调整
    }

    // 删除结点（自动平衡）
    Node *remove(Node *root, int val)
    {
        if (!root)
            return root;

        if (val < root->val)
            root->left = remove(root->left, val);
        else if (val > root->val)
            root->right = remove(root->right, val);
        else
        {
            // 如果没有左子树则用右子树为新的根结点
            if (!root->left)
                return root->right;
            // 如果没有右子树则用左子树为新的根结点
            if (!root->right)
                return root->left;
            // 左右子树均存在，则找到右子树的最小结点，覆盖当前根结点
            Node *min = root->right;
            while (min->left)
                min = min->left;
            root->val = min->val;
            root->right = remove(root->right, min->val);
        }

        updateHeight(root); // 更新高度

        int bf = balanceFactor(root); // 计算平衡因子

        // LL 情况（左子树高，且删除后左子树仍然更高）
        if (bf > 1 && balanceFactor(root->left) >= 0)
            return rightRotate(root);

        // RR 情况（右子树高，且删除后右子树仍然更高）
        if (bf < -1 && balanceFactor(root->right) <= 0)
            return leftRotate(root);

        // LR 情况（左子树高，但删除后左子树的右子树更高）
        if (bf > 1 && balanceFactor(root->left) < 0)
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        // RL 情况（右子树高，但删除后右子树的左子树更高）
        if (bf < -1 && balanceFactor(root->right) > 0)
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root; // 无需调整
    }

    // 查找结点（与BST相同）
    bool search(Node *root, int val)
    {
        if (!root)
            return false;
        if (val == root->val)
            return true;
        return val < root->val ? search(root->left, val) : search(root->right, val);
    }

    // 检查是否为有效的AVL树（BST + 平衡）
    bool isValidAVL(Node *root)
    {
        function<bool(Node *, long, long)> check = [&](Node *node, long min_val, long max_val)
        {
            if (!node)
                return true;
            if (node->val <= min_val || node->val >= max_val)
                return false;
            if (abs(balanceFactor(node)) > 1)
                return false; // 检查平衡因子
            return check(node->left, min_val, node->val) && check(node->right, node->val, max_val);
        };
        return check(root, LONG_MIN, LONG_MAX);
    }
};