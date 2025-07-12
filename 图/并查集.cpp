#include <vector>
#include <iostream>
using namespace std;

class DSU
{

private:
    vector<int> parent; // 父节点数组
    vector<int> rank;   // 秩（用于按秩合并优化）

public:
    // 构造函数，初始化大小为n
    DSU(int n)
    {
        parent.resize(n);
        rank.resize(n, 1); // 初始秩为1
        for (int i = 0; i < n; ++i)
            parent[i] = i; // 初始时每个元素的父节点是自己
    }

    // 查找根节点（带路径压缩）(递归版)
    // int find(int x)
    // {
    //     if (parent[x] != x)
    //         parent[x] = find(parent[x]); // 路径压缩
    //     return parent[x];
    // }

    // "查"
    // 查找根节点（带路径压缩）(迭代版)
    int find(int u)
    {
        while (parent[u] != u)
        {
            parent[u] = parent[parent[u]]; // 路径压缩
            u = parent[u];
        }
        return u;
    }

    // "并"
    // 合并两个集合（按秩合并）
    void unionSets(int x, int y)
    {
        int rx = find(x);
        int ry = find(y);
        if (rx == ry)
            return; // 已经在同一集合

        // 按秩合并：小树合并到大树下
        if (rank[rx] < rank[ry])
            parent[rx] = ry;
        else if (rank[rx] > rank[ry])
            parent[ry] = rx;
        else
        {
            parent[ry] = rx;
            rank[rx]++; // 秩相同时，合并后秩+1
        }
    }

    // 检查两个元素是否属于同一集合
    bool isConnected(int x, int y)
    {
        return find(x) == find(y);
    }

    // 查找小团体数量
    int getNumber()
    {
        int count = 0;
        for (int i = 0; i < parent.size(); i++)
            if (parent[i] == i)
                count++;
        return count;
    }

    // 获取某个集合的大小
    int getSize(int x)
    {
        int root = find(x);
        return rank[root]; // 注意：这里rank已被用作集合大小
    }
};

// ====================== 朋友圈问题 ======================
// 给定一些双人关系，求有多少个相互独立的朋友圈
int friendCircles(int n, const vector<pair<int, int>> &relations)
{
    DSU dsu(n);
    for (auto &rel : relations)
    {
        dsu.unionSets(rel.first, rel.second);
    }
    return dsu.getNumber(); // 直接返回当前集合数量
}

// ====================== 岛屿问题 ======================
// 一个二维棋盘里面,1是陆地0是海，求有多少个独立岛屿
int numIslands(const vector<vector<int>> &grid)
{
    int rows = grid.size(), cols = grid[0].size();
    int water = 0; // 海洋区域计数

    DSU dsu(rows * cols);

    // 方向数组
    vector<pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            if (grid[i][j] == 0)
            {
                water++; // 遇到海洋，不在并查集里面合并，自己占一个小团体
                continue;
            }
            for (auto &dir : directions) // 朝四个方向探索
            {
                int x = i + dir.first, y = j + dir.second;
                if (x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] == 1)
                    dsu.unionSets(i * cols + j, x * cols + y); // 二维坐标转一维ID, 陆地区域连起来
            }
        }
    }
    return dsu.getNumber() - water; // 总数减去海洋区域
}

//
int main()
{
    // ===== 朋友圈问题测试 =====
    vector<pair<int, int>> relations = {{0, 1}, {1, 2}, {3, 4}};
    std::cout << "friendCircle Number: " << friendCircles(5, relations) << std::endl; // 输出2

    // ===== 岛屿问题测试 =====
    vector<vector<int>> grid = {
        {1, 1, 0, 0},
        {1, 0, 1, 0},
        {0, 0, 0, 1},
        {1, 1, 1, 1}};
    cout << "Island Number: " << numIslands(grid) << endl; // 输出3

    return 0;
}
