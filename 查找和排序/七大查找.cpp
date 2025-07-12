#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <list>
using namespace std;

// 1. 顺序查找
int sequentialSearch(const vector<int> &arr, int target)
{
    for (int i = 0; i < arr.size(); ++i)
    {
        if (arr[i] == target)
            return i;
    }
    return -1;
}

// 2. 二分查找
int binarySearch(const vector<int> &vec, int target)
{
    int l = 0, r = vec.size() - 1;
    while (l <= r)
    {
        int mid = (r + l) / 2;
        if (vec[mid] == target)
            return mid;
        if (vec[mid] < target)
            l = mid + 1;
        else
            r = mid + 1;
    }
    return -1;
}

// 3. 插值查找
int interpolationSearch(const vector<int> &arr, int target)
{
    int low = 0, high = arr.size() - 1;
    while (low <= high && target >= arr[low] && target <= arr[high])
    {
        int pos = low + ((target - arr[low]) * (high - low)) / (arr[high] - arr[low]);
        if (arr[pos] == target)
            return pos;
        if (arr[pos] < target)
            low = pos + 1;
        else
            high = pos - 1;
    }
    return -1;
}
// 4. 斐波那契查找
int fibonacciSearch(const vector<int> &arr, int target)
{
    int fibMMm2 = 0, fibMMm1 = 1, fibM = fibMMm2 + fibMMm1;
    while (fibM < arr.size())
    {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }
    int offset = -1;
    while (fibM > 1)
    {
        int i = min(offset + fibMMm2, (int)arr.size() - 1);
        if (arr[i] < target)
        {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        }
        else if (arr[i] > target)
        {
            fibM = fibMMm2;
            fibMMm1 -= fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        }
        else
            return i;
    }
    if (fibMMm1 && arr[offset + 1] == target)
        return offset + 1;
    return -1;
}

// 5. 哈希查找（链地址法）
class HashTable
{
    vector<list<int>> table;
    int size;

public:
    HashTable(int size) : size(size), table(size) {}

    int hash(int key) { return key % size; }

    void insert(int key)
    {
        table[hash(key)].push_back(key);
    }

    bool search(int key)
    {
        for (int num : table[hash(key)])
        {
            if (num == key)
                return true;
        }
        return false;
    }
};

// 6. 二叉搜索树查找
class BSTNode
{
public:
    int val;
    BSTNode *left, *right;
    BSTNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

BSTNode *searchBST(BSTNode *root, int target)
{
    if (!root || root->val == target)
        return root;
    return target < root->val ? searchBST(root->left, target)
                              : searchBST(root->right, target);
}

// 7. 图查找（DFS/BFS）
class Graph
{
    int V;
    vector<vector<int>> adj;

public:
    Graph(int V) : V(V), adj(V) {}
    void addEdge(int u, int v) { adj[u].push_back(v); }

    // DFS
    bool DFS(int start, int target)
    {
        vector<bool> visited(V, false);
        return DFSUtil(start, target, visited);
    }

    bool DFSUtil(int u, int target, vector<bool> &visited)
    {
        visited[u] = true;
        if (u == target)
            return true;
        for (int v : adj[u])
        {
            if (!visited[v] && DFSUtil(v, target, visited))
                return true;
        }
        return false;
    }

    // BFS
    bool BFS(int start, int target)
    {
        vector<bool> visited(V, false);
        queue<int> q;
        q.push(start);
        visited[start] = true;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            if (u == target)
                return true;
            for (int v : adj[u])
            {
                if (!visited[v])
                {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
        return false;
    }
};

// 测试查找算法
int main()
{
    vector<int> arr = {2, 3, 4, 10, 40};
    cout << binarySearch(arr, 10) << endl; // 输出3

    HashTable ht(7);
    ht.insert(15);
    ht.insert(22);
    cout << boolalpha << ht.search(22) << endl; // 输出true

    return 0;
}