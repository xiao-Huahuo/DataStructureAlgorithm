#include <iostream>
#include <stack>
#include <cmath>
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>
using namespace std;
// 二叉搜索树
class BST
{
public:
    // 二叉搜索树: left<=root<=right
    struct Node
    {
        int val;
        Node *left;
        Node *right;
        Node(int x) : val(x), left(NULL), right(NULL) {}
    };

    // 从有序数组创建平衡BST
    Node *create(const vector<int> &vec, int start, int end)
    {
        if (start > end)
            return NULL;
        int mid = (start + end) / 2;
        Node *node = new Node(vec[mid]);
        node->left = create(vec, start, mid - 1);
        node->right = create(vec, mid + 1, end);
        return node;
    }

    // 插入节点
    Node *insert(Node *root, int val)
    {
        if (!root)
            return new Node(val);
        if (val < root->val)
            root->left = insert(root->left, val);
        else if (val > root->val)
            root->right = insert(root->right, val);
        return root;
    }

    // 删除节点
    Node *remove(Node *root, int val)
    {
        if (!root)
            return root;
        if (val < root->val)
            root->left = remove(root->left, val);//node=remove(node,val)代表删除子树val结点
        else if (val > root->val)
            root->right = remove(root->right, val);
        else
        {
            // 如果没有左子树则用右子树为新的根节点，如果没有右子树则用左子树为新的根节点
            if (!root->left)
                return root->right;
            if (!root->right)
                return root->left;
            // 左右子树均存在，则找到右子树的最小结点，覆盖当前根结点，并在右子树中删除此最小结点
            Node *min = root->right;
            while (min->left)
                min = min->left;
            root->val = min->val;
            root->right = remove(root->right, min->val);
        }
        return root;
    }
    
    // 查找节点
    bool search(Node *root, int val)
    {
        if (!root)
            return false;
        if (val == root->val)
            return true;
        return val < root->val ? search(root->left, val) : search(root->right, val);
    }

    // 查找范围内所有节点（左闭右闭区间）
    vector<int> rangeSearch(Node *root, int l, int r)
    {
        vector<int> result;
        function<void(Node *)> search = [&](Node *node)
        {
            if (!node)
                return;
            //中序遍历
            if (node->val > l)
                search(node->left); // 左子树可能有符合条件的
            if (node->val >= l && node->val <= r)
                result.push_back(node->val);
            if (node->val < r)
                search(node->right); // 右子树可能有符合条件的
        };
        search(root);
        return result;
    }
    
    // 检查是否为有效的二叉搜索树：使用上下界递归验证（更高效）
    bool isValidBST(Node *root)
    {
        function<bool(Node *, long, long)> check = [&](Node *node, long min_val, long max_val)
        {
            if (!node)
                return true;
            if (node->val <= min_val || node->val >= max_val)
                return false;
            return check(node->left, min_val, node->val) &&
                   check(node->right, node->val, max_val);
        };
        return check(root, LONG_MIN, LONG_MAX);
    }
};
