#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include<functional>
using namespace std;
// 哈夫曼树-数组实现
class HuffmanTree
{ // 哈夫曼树的性质：总结点数 = 2 × 叶子数 - 1 → 叶子数 = (总结点数 + 1) / 2
public:
    // 哈夫曼树结点
    struct Node
    {
        char data;     // 字符数据
        double w; // 权重
        int parent;    // 父结点
        int lchild;    // 左孩子结点
        int rchild;    // 右孩子结点

        Node(char d = '\0', double w = 0.0)
            : data(d), w(w), parent(-1), lchild(-1), rchild(-1) {}
    };

    std::vector<Node> nodes; // 存储所有哈夫曼树结点

    // 构造哈夫曼树
    void buildHTree(const string &leaves, const std::vector<double> &ws)
    {
        if (leaves.size() != ws.size() || leaves.empty())
            return;
        int lSize = leaves.size(); // 叶子结点数
        int total = 2 * lSize - 1; // 总结点数 = 2 × 叶子数 - 1
        nodes.resize(total);

        // 初始化叶子结点
        for (int i = 0; i < lSize; ++i)
            nodes[i] = Node(leaves[i], ws[i]);

        // 构建哈夫曼树
        for (int i = lSize; i < total; ++i)
        {
            int left = 0, right = 0;           // 最小和第二小结点的索引
            double w1 = INT_MAX, w2 = INT_MAX; // 最小和第二小权重

            // 每次从左边的所有结点中，找出权重最小的两个未处理结点，构建出新结点
            for (int j = 0; j < i; ++j)
            {
                if (nodes[j].parent != -1)
                    continue; // parent=-1代表森林中可用的树根
                if (nodes[j].w < w1)
                {
                    // 更新最小和第二小
                    w2 = w1;
                    w1 = nodes[j].w;
                    right = left;
                    left = j;
                }
                else if (nodes[j].w < w2)
                {
                    // 只更新第二小
                    w2 = nodes[j].w;
                    right = j;
                }
            }

            // 创建新结点
            nodes[i].w = nodes[left].w + nodes[right].w; // 权为左子树和右子树之和
            nodes[i].lchild = left;
            nodes[i].rchild = right;
            nodes[left].parent = nodes[right].parent = i; // 不要忘记设置parent
        }
    }

    // 计算带权路径长度(WPL)
    double calculateWPL()
    {
        // WPL:即计算所有叶子结点的权乘以叶子的层数的和(层数以root为0)
        if (nodes.empty())
            return 0.0;
        double wpl = 0.0;
        const int leafNum = (nodes.size() + 1) / 2; // 叶子结点数

        for (int i = 0; i < leafNum; ++i)
        {
            int depth = 0;
            int current = i;

            // 向上遍历到根结点
            while (nodes[current].parent != -1)
            {
                current = nodes[current].parent;
                depth++;
            }

            wpl += nodes[i].w * depth; // 使用w字段计算
        }

        return wpl;
    }

    // 哈夫曼编码结构
    struct Code
    {
        std::string bits; // 编码位串
        int start;        // 有效编码的起始位置(如bits="  101"start=2前面有两个空格)
        Code(int size = 0)
        {
            start = size;             // start初始在尾后
            bits = string(size, ' '); // 预留空间，而不是频繁扩展字符串，可以有效提高效率
        }
    };

    // 生成哈夫曼编码
    std::vector<Code> generateCodes()
    {
        std::vector<Code> codes;
        int lSize = (nodes.size() + 1) / 2;

        for (int i = 0; i < lSize; ++i)
        {
            Code cd(lSize);

            int curr = i;
            int parent = nodes[curr].parent;

            // 从叶子回溯到根生成编码
            while (parent != -1)
            {
                cd.bits[--cd.start] = (nodes[parent].lchild == curr) ? '0' : '1'; // 判断当前结点是父结点的左孩子还是右孩子
                curr = parent;
                parent = nodes[parent].parent;
            }

            codes.push_back(cd);
        }
        return codes;
    }
};

// 哈夫曼树-结点实现
class HuffmanTree2
{
public:
    struct Node
    {
        char data;
        double w;
        Node *left;
        Node *right;

        Node(char d, double w) : data(d), w(w), left(NULL), right(NULL) {}
    }; 
    // 比较器：最小堆
    struct Comparison
    {
        bool operator()(Node *a, Node *b)
        {
            return a->w > b->w;
        }
    };
    //哈夫曼树树根
    Node *root;

    HuffmanTree2() : root(NULL) {}

    // 构建哈夫曼树
    void build(const string &chars, const vector<double> &ws)
    {
        priority_queue<Node *, vector<Node *>, Comparison> pq;//最小堆,森林

        // 初始化叶子结点
        for (int i = 0; i < chars.size(); ++i)
            pq.push(new Node(chars[i], ws[i]));

        // 构造哈夫曼树
        while (pq.size() > 1)
        {
            Node *left = pq.top();
            pq.pop();
            Node *right = pq.top();
            pq.pop();
            Node *parent = new Node('\0', left->w + right->w);
            parent->left = left;
            parent->right = right;
            pq.push(parent);
        }

        // 树根
        if (!pq.empty())
            root = pq.top();
    }

    // 生成哈夫曼编码
    unordered_map<char, string> getCodes()
    {
        unordered_map<char, string> result;
        function<void(Node *, string)> generateCodes = [&](Node *node, string code)
        {
            if (!node)
                return;

            // 到达叶子结点
            if (!node->left && !node->right)
            {
                result[node->data] = code;
                return;
            }

            generateCodes(node->left, code + "0");
            generateCodes(node->right, code + "1");
        };
        generateCodes(root, "");
        return result;
    }

    // WPL 计算（带权路径长度）
    int calculateWPL(Node *node, int depth = 0)
    {
        if (!node)
            return 0;
        if (!node->left && !node->right)
            return node->w * depth;
        return calculateWPL(node->left, depth + 1) + calculateWPL(node->right, depth + 1);
    }
};