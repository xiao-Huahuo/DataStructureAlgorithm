#include <iostream>
#include <stack>
#include <cmath>
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>
#include <unordered_map>
using namespace std;
// 二叉树
class BTree
{
public:
    struct Node
    {
        char data;
        Node *lchild;
        Node *rchild;

        Node(char inival = '\0') : data(inival), lchild(NULL), rchild(NULL) {}
    };

    // __1__ 创建二叉树:"A(B(D(,G)),C(E,F))",使用栈代替递归
    Node *create(string str)
    {
        Node *root = NULL;
        Node *curr = NULL;
        stack<Node *> stk;
        enum STATUS
        {
            LEFT,
            RIGHT
        };
        STATUS choice = LEFT; // 决定左子树还是右子树，LEFT表示左子树，RIGHT表示右子树
        for (char ch : str)
        {
            if (ch == '(')
            {
                stk.push(curr); // 存入空的node，如果有数值则后续修改
                choice = LEFT;   // 注意转向左子树
            }
            else if (ch == ')')
                stk.pop(); // 弹出栈顶
            else if (ch == ',')
                choice = RIGHT; // 转向右子树
            else
            {
                // 数值
                curr = new Node(ch);
                if (!root)
                    root = curr; // 没有主根结点的情况，直接赋值为主根节点
                else
                {
                    // 注意 栈顶结点 才是当前的根节点
                    if (choice == LEFT)
                        stk.top()->lchild = curr;
                    else
                        stk.top()->rchild = curr;
                }
            }
        }
        return root;
    }

    // 销毁二叉树
    void clearBTree(Node *&root)
    {
        if (!root)
            return;
        clearBTree(root->lchild);
        clearBTree(root->rchild);
        delete root;
        root = NULL;
    }

    // __2__ 邻接表式输入二叉树的构造
    class createBTree_Vertax
    {
    public:
        unordered_map<char, pair<char, char>> adj; // 邻接表
        void inputBTree()
        {
            int n;
            cin >> n;
            for (int i = 0; i < n; i++)
            {
                char parent, left, right;
                cin >> parent >> left >> right;
                adj.insert({parent, {left, right}});
            }
        }
        Node*buildBTree(char curr){
            if (curr == '#' || adj.count(curr)!=0)
                return NULL;//如果是空结点，或者表中已经存在，则不处理
            Node *root = new Node(curr);
            root->lchild = buildBTree(adj.at(curr).first);//递归构造左子树
            root->rchild = buildBTree(adj.at(curr).second);//递归构造右子树
            return root;
        }
    };
    
    // 输出二叉树
    void print(Node *root)
    {
        if (!root)
            return;
        cout << root->data;
        if (root->lchild || root->rchild)
        {
            // 子树存在，递归输出
            cout << '(';

            print(root->lchild);
            if (root->rchild)
                cout << ',';
            print(root->rchild);

            cout << ')';
        }
    }
    // 先序遍历
    void preOrder(Node *root)
    {
        if (root)
        {
            cout << root->data << ' ';
            preOrder(root->lchild);
            preOrder(root->rchild);
        }
    }
    // 中序遍历
    void inOrder(Node *root)
    {
        if (root)
        {
            inOrder(root->lchild);
            cout << root->data << ' ';
            inOrder(root->rchild);
        }
    }
    // 后序遍历
    void postOrder(Node *root)
    {
        if (root)
        {
            postOrder(root->lchild);
            postOrder(root->rchild);
            cout << root->data << ' ';
        }
    }
    // 层次遍历
    void nodes(Node *root)
    {
        if (!root)
            return;
        queue<Node *> que;
        que.push(root);
        while (!que.empty())
        {
            Node *front = que.front(); // 弹出队首
            que.pop();
            cout << front->data << " ";
            // 顺序存入子结点
            if (front->lchild)
                que.push(front->lchild);
            if (front->rchild)
                que.push(front->rchild);
        }
    }

    // 先序序列
    string getPreSeq(Node *root)
    {
        string preseq;
        // 使用functional和lambda表达式，更高级和简便
        function<void(Node *)> pretravel = [&](Node *node) -> void
        {
            if (!node)
                return;
            preseq.push_back(node->data);
            pretravel(node->lchild);
            pretravel(node->rchild);
        };
        pretravel(root);
        return preseq;
    }
    // 中序序列
    string getInSeq(Node *root)
    {
        string inseq;
        // 使用functional和lambda表达式，更高级和简便
        function<void(Node *)> intravel = [&](Node *node) -> void
        {
            if (!node)
                return;
            intravel(node->lchild);
            inseq.push_back(node->data);
            intravel(node->rchild);
        };
        intravel(root);
        return inseq;
    }
    // 后序序列
    string getPostSeq(Node *root)
    {
        string postseq;
        // 使用functional和lambda表达式，更高级和简便
        function<void(Node *)> posttravel = [&](Node *node) -> void
        {
            if (!node)
                return;
            posttravel(node->lchild);
            posttravel(node->rchild);
            postseq.push_back(node->data);
        };
        posttravel(root);
        return postseq;
    }

    // 二叉树的构造

    // __3__ 先序序列构造(带'#')
    Node *constructPre(const string &nodes)
    {
        function<Node *(const string &, int &)> pre = [&](const string &nodes, int &index) -> Node *
        {
            if (index >= nodes.size() || nodes[index] == '#')
            {
                index++;
                return NULL;
            }
            Node *root = new Node(nodes[index++]);
            root->lchild = pre(nodes, index);
            root->rchild = pre(nodes, index);
            return root;
        };
        int index = 0; // 初始化索引
        return pre(nodes, index);
    }
    // __4__ 层序序列构造(带'#')(完全二叉树构造)
    Node *constructLevel(const string &nodes)
    {
        if (nodes.empty() )
            return NULL;

        Node *root = new Node(nodes[0]);
        queue<Node *> q; // 使用队列进行广搜
        q.push(root);

        int i = 1;
        while (!q.empty() && i < nodes.size())
        {
            Node *curr = q.front();
            q.pop();

            // 处理左孩子
            if (i < nodes.size() && nodes[i] != '#')
            {
                curr->lchild = new Node(nodes[i]);
                q.push(curr->lchild);
            }
            i++;

            // 处理右孩子
            if (i < nodes.size() && nodes[i] != '#')
            {
                curr->rchild = new Node(nodes[i]);
                q.push(curr->rchild);
            }
            i++;
        }
        return root;
    }

    // 先序序列+中序序列构造
    Node *constructPreIn(const string &pres, int i, const string &ins, int j, int n)
    {
        // i:根结点在pres的索引(初始值填0)，j:起始结点在ins的索引(初始值填0)，n:构造的树的结点数量,初始值填pres.size()
        if (n <= 0)
            return NULL;
        // 在ins中分割[j,j+n)为左子树[j,p-1]、根节点p、右子树[p+1,j+n-1]
        int p = j;
        while (ins[p] != pres[i])
            p++;
        Node *root = new Node(ins[p]);
        root->lchild = constructPreIn(pres, i + 1, ins, j, p - j);
        root->rchild = constructPreIn(pres, i + p - j + 1, ins, p + 1, n - p + j - 1);
        return root;
    }
    // 后序序列+中序序列构造
    Node *constructPostIn(const string &posts, int i, const string &ins, int j, int n)
    {
        // i:起始结点在posts的索引(初始值填0)，j:起始结点在ins的索引(初始值填0)，n:构造的树的结点数量,初始值填posts.size()
        if (n <= 0)
            return NULL;
        // 在ins中分割[j,j+n)为左子树[j,p-1]、根节点p、右子树[p+1,j+n-1]
        int p = j;
        while (ins[p] != posts[i + n - 1]) // 后序中root是最后一个结点
            p++;
        Node *root = new Node(ins[p]);
        root->lchild = constructPostIn(posts, i, ins, j, p - j);
        root->rchild = constructPostIn(posts, i + p - j, ins, p + 1, n - p + j - 1);
        return root;
    }

    // 查找结点
    Node *search(Node *root, char find_val)
    {
        if (!root)
            return NULL;
        if (root->data == find_val)
            return root;
        Node *l_find = search(root->lchild, find_val);           // 递归寻找左子树
        return l_find ? l_find : search(root->rchild, find_val); // 左子树找不到则递归寻找右子树
    }
    // 判断是不是完全二叉树
    bool isComplete(Node *root)
    {
        // 完全二叉树：1.除最后一层外，所有层必须完全填满   2.最后一层的结点必须尽可能靠左排列，且不能有空缺
        if (!root)
            return true;
        bool hasMetEmpty = false; // 是否已经遇到了空结点
        queue<Node *> queue;
        queue.push(root);
        // 广度优先搜索
        while (!queue.empty())
        {
            Node *front = queue.front();
            queue.pop();
            if (!front)
            {
                hasMetEmpty = true;
                continue;
            }
            // 非空结点,则判断：如果已经遇到过空结点并且此结点非空，则不是完全二叉树
            if (hasMetEmpty)
                return false;
            // 存入队头的两个子结点，无论是不是空结点
            queue.push(front->lchild);
            queue.push(front->rchild);
        }
        return true;
    }
    // 求高度
    int height(Node *root)
    {
        if (!root)
            return 0;
        int l_height = 0, r_height = 0;
        l_height = height(root->lchild);
        r_height = height(root->rchild);
        return max(l_height, r_height) + 1;
    }
    // 寻找节点的层次
    int level(Node *root, char val, int currHeight)
    {
        if (!root)
            return 0;
        if (root->data == val)
            return currHeight;
        int l_height = level(root->lchild, val, currHeight + 1); // 更深一层
        return l_height ? l_height : level(root->lchild, val, currHeight + 1);
    }
    // 第k层结点个数
    int count(Node *root, int currHeight, int k)
    {
        if (!root)
            return 0;
        int total = 0; // 总结点个数
        if (currHeight == k)
            return 1;
        total += count(root->lchild, currHeight + 1, k);
        total += count(root->rchild, currHeight + 1, k);
        return total;
    }
    // 寻找val结点的所有祖先节点
    vector<Node *> findAncestor(Node *root, char val)
    {
        vector<Node *> result;
        // 利用function+lambda表达式更方便于递归调用
        function<bool(Node *)> backtrack = [&](Node *root) -> bool
        {
            if (!root)
                return false;

            // 找到目标节点，触发回溯
            if (root->data == val)
                return true;

            // 在左右子树中搜索
            if (backtrack(root->lchild) || backtrack(root->rchild))
            {
                result.push_back(root); // 当前节点是祖先
                return true;
            }

            return false;
        };
        backtrack(root);
        reverse(result.begin(), result.end());
        return result; // 祖先顺序为父节点→根节点
    }
    // LeetCode863:二叉树中距离为k的结点
    class DistanceKSolution
    {
    public:
        // 从target出发，沿着两子树方向或父结点方向扩散，返回距离为k的结点

        // 带父结点的二叉树结点
        struct Node
        {
            int data;
            Node *lchild, *rchild, *parent;
            Node(int d = 0) : data(d), lchild(NULL), rchild(NULL), parent(NULL) {}
        };
        // 使用广度优先搜索，保证得到结果的顺序
        vector<int> distanceK(Node *root, Node *target, int k)
        {
            vector<int> result;
            if (!root || !target)
                return result;

            queue<pair<Node *, Node *>> q; // {curr,from}
            q.push({target, NULL});
            int dist = 0; // 距离起点的距离

            while (!q.empty())
            {
                if (dist == k)
                {
                    while (!q.empty())
                    {
                        result.push_back(q.front().first->data);
                        q.pop();
                    }
                    break;
                }

                int level_size = q.size();
                for (int i = 0; i < level_size; ++i)
                {
                    Node *curr, *from;
                    curr = q.front().first;
                    from = q.front().second;
                    q.pop();

                    if (curr->lchild && curr->lchild != from)
                        q.push({curr->lchild, curr});
                    if (curr->rchild && curr->rchild != from)
                        q.push({curr->rchild, curr});
                    if (curr->parent && curr->parent != from)
                        q.push({curr->parent, curr});
                }
                dist++;
            }

            return result;
        }
    };
};
