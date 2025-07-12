#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <stack>
#include <queue>
#include <functional>
#include <unordered_map>
using namespace std;
using Graph = vector<vector<int>>;             // 邻接表
using wGraph = vector<vector<pair<int, int>>>; // 带权图,(vertax,weight)
wGraph wg1 = {
    {{1, 1}, {2, 4}},         // 顶点0的邻接边：(1,1), (2,4)
    {{0, 1}, {2, 2}, {3, 5}}, // 顶点1
    {{0, 4}, {1, 2}, {3, 3}}, // 顶点2
    {{1, 5}, {2, 3}}          // 顶点3
};
wGraph wg2 = {
    {{1, 5}, {2, 8}, {3, 12}}, // 0
    {{0, 5}, {4, 7}, {5, 9}},  // 1
    {{0, 8}, {6, 6}, {7, 4}},  // 2
    {{0, 12}, {8, 11}},        // 3
    {{1, 7}, {9, 3}},          // 4
    {{1, 9}},                  // 5
    {{2, 6}},                  // 6
    {{2, 4}},                  // 7
    {{3, 11}},                 // 8
    {{4, 3}}                   // 9
};
wGraph wg100 = {
    {{1, 7}, {5, 12}, {8, 19}},               // 0
    {{0, 7}, {2, 15}, {9, 4}},                // 1
    {{1, 15}, {3, 8}, {10, 11}},              // 2
    {{2, 8}, {4, 6}, {11, 17}},               // 3
    {{3, 6}, {5, 13}, {12, 9}},               // 4
    {{0, 12}, {4, 13}, {6, 5}, {13, 20}},     // 5
    {{5, 5}, {7, 14}, {14, 10}},              // 6
    {{6, 14}, {8, 3}, {15, 18}},              // 7
    {{0, 19}, {7, 3}, {16, 2}},               // 8
    {{1, 4}, {10, 16}, {17, 7}},              // 9
    {{2, 11}, {9, 16}, {11, 1}, {18, 12}},    // 10
    {{3, 17}, {10, 1}, {19, 5}},              // 11
    {{4, 9}, {13, 11}, {20, 8}},              // 12
    {{5, 20}, {12, 11}, {14, 15}, {21, 19}},  // 13
    {{6, 10}, {13, 15}, {22, 6}},             // 14
    {{7, 18}, {16, 13}, {23, 14}},            // 15
    {{8, 2}, {15, 13}, {17, 10}, {24, 4}},    // 16
    {{9, 7}, {16, 10}, {18, 9}, {25, 16}},    // 17
    {{10, 12}, {17, 9}, {26, 3}},             // 18
    {{11, 5}, {20, 7}, {27, 18}},             // 19
    {{12, 8}, {19, 7}, {21, 6}, {28, 12}},    // 20
    {{13, 19}, {20, 6}, {22, 17}, {29, 5}},   // 21
    {{14, 6}, {21, 17}, {30, 11}},            // 22
    {{15, 14}, {24, 15}, {31, 8}},            // 23
    {{16, 4}, {23, 15}, {25, 2}, {32, 20}},   // 24
    {{17, 16}, {24, 2}, {26, 13}, {33, 9}},   // 25
    {{18, 3}, {25, 13}, {34, 14}},            // 26
    {{19, 18}, {28, 10}, {35, 7}},            // 27
    {{20, 12}, {27, 10}, {29, 4}, {36, 15}},  // 28
    {{21, 5}, {28, 4}, {30, 19}, {37, 16}},   // 29
    {{22, 11}, {29, 19}, {38, 1}},            // 30
    {{23, 8}, {32, 9}, {39, 12}},             // 31
    {{24, 20}, {31, 9}, {33, 3}, {40, 17}},   // 32
    {{25, 9}, {32, 3}, {34, 8}, {41, 6}},     // 33
    {{26, 14}, {33, 8}, {42, 10}},            // 34
    {{27, 7}, {36, 13}, {43, 5}},             // 35
    {{28, 15}, {35, 13}, {37, 2}, {44, 18}},  // 36
    {{29, 16}, {36, 2}, {38, 11}, {45, 14}},  // 37
    {{30, 1}, {37, 11}, {46, 7}},             // 38
    {{31, 12}, {40, 16}, {47, 9}},            // 39
    {{32, 17}, {39, 16}, {41, 20}, {48, 3}},  // 40
    {{33, 6}, {40, 20}, {42, 15}, {49, 8}},   // 41
    {{34, 10}, {41, 15}, {50, 12}},           // 42
    {{35, 5}, {44, 19}, {51, 4}},             // 43
    {{36, 18}, {43, 19}, {45, 1}, {52, 7}},   // 44
    {{37, 14}, {44, 1}, {46, 6}, {53, 13}},   // 45
    {{38, 7}, {45, 6}, {54, 16}},             // 46
    {{39, 9}, {48, 14}, {55, 10}},            // 47
    {{40, 3}, {47, 14}, {49, 11}, {56, 5}},   // 48
    {{41, 8}, {48, 11}, {50, 17}, {57, 18}},  // 49
    {{42, 12}, {49, 17}, {58, 2}},            // 50
    {{43, 4}, {52, 8}, {59, 15}},             // 51
    {{44, 7}, {51, 8}, {53, 20}, {60, 9}},    // 52
    {{45, 13}, {52, 20}, {54, 3}, {61, 12}},  // 53
    {{46, 16}, {53, 3}, {62, 6}},             // 54
    {{47, 10}, {56, 19}, {63, 7}},            // 55
    {{48, 5}, {55, 19}, {57, 14}, {64, 11}},  // 56
    {{49, 18}, {56, 14}, {58, 1}, {65, 17}},  // 57
    {{50, 2}, {57, 1}, {66, 10}},             // 58
    {{51, 15}, {60, 4}, {67, 13}},            // 59
    {{52, 9}, {59, 4}, {61, 16}, {68, 8}},    // 60
    {{53, 12}, {60, 16}, {62, 5}, {69, 19}},  // 61
    {{54, 6}, {61, 5}, {70, 18}},             // 62
    {{55, 7}, {64, 12}, {71, 3}},             // 63
    {{56, 11}, {63, 12}, {65, 7}, {72, 20}},  // 64
    {{57, 17}, {64, 7}, {66, 9}, {73, 6}},    // 65
    {{58, 10}, {65, 9}, {74, 15}},            // 66
    {{59, 13}, {68, 2}, {75, 11}},            // 67
    {{60, 8}, {67, 2}, {69, 10}, {76, 14}},   // 68
    {{61, 19}, {68, 10}, {70, 1}, {77, 16}},  // 69
    {{62, 18}, {69, 1}, {78, 7}},             // 70
    {{63, 3}, {72, 17}, {79, 5}},             // 71
    {{64, 20}, {71, 17}, {73, 8}, {80, 13}},  // 72
    {{65, 6}, {72, 8}, {74, 4}, {81, 19}},    // 73
    {{66, 15}, {73, 4}, {82, 12}},            // 74
    {{67, 11}, {76, 6}, {83, 9}},             // 75
    {{68, 14}, {75, 6}, {77, 20}, {84, 3}},   // 76
    {{69, 16}, {76, 20}, {78, 13}, {85, 10}}, // 77
    {{70, 7}, {77, 13}, {86, 2}},             // 78
    {{71, 5}, {80, 18}, {87, 14}},            // 79
    {{72, 13}, {79, 18}, {81, 1}, {88, 11}},  // 80
    {{73, 19}, {80, 1}, {82, 5}, {89, 17}},   // 81
    {{74, 12}, {81, 5}, {90, 8}},             // 82
    {{75, 9}, {84, 15}, {91, 7}},             // 83
    {{76, 3}, {83, 15}, {85, 12}, {92, 6}},   // 84
    {{77, 10}, {84, 12}, {86, 19}, {93, 4}},  // 85
    {{78, 2}, {85, 19}, {94, 16}},            // 86
    {{79, 14}, {88, 7}, {95, 13}},            // 87
    {{80, 11}, {87, 7}, {89, 3}, {96, 20}},   // 88
    {{81, 17}, {88, 3}, {90, 9}, {97, 5}},    // 89
    {{82, 8}, {89, 9}, {98, 14}},             // 90
    {{83, 7}, {92, 10}, {99, 18}},            // 91
    {{84, 6}, {91, 10}, {93, 1}, {99, 16}},   // 92
    {{85, 4}, {92, 1}, {94, 11}},             // 93
    {{86, 16}, {93, 11}, {95, 8}},            // 94
    {{87, 13}, {94, 8}, {96, 15}},            // 95
    {{88, 20}, {95, 15}, {97, 6}},            // 96
    {{89, 5}, {96, 6}, {98, 17}},             // 97
    {{90, 14}, {97, 17}, {99, 2}},            // 98
    {{91, 18}, {92, 16}, {98, 2}}             // 99
};
const static int INF = INT_MAX;

// 输出无权图（Graph）
void print(const Graph &graph)
{
    for (int u = 0; u < graph.size(); ++u)
    {
        std::cout << u << " ";
        for (int v : graph[u])
        {
            std::cout << v << "->";
        }
        std::cout << "^\n";
    }
}

// 输出带权图（wGraph）
void print(const wGraph &graph)
{
    for (int u = 0; u < graph.size(); ++u)
    {
        std::cout << u << " ";
        for (const auto &edge : graph[u])
        {
            int v = edge.first;
            int weight = edge.second;
            std::cout << v << "[" << weight << "]" << "->";
        }
        std::cout << "^\n";
    }
}

// 基本遍历与搜索
class travelAndSearchSolution
{
public:
    const static int MAXV = 1000;
    bool vis[MAXV] = {0}; // 全局访问数组，一般使用哈希表键值对存储，此处可以使用数组
    // 深度优先遍历
    void dft(const Graph &graph, int val)
    {
        vis[val] = true;
        cout << val << " ";
        for (int neib : graph[val]) // 对邻接未访问过的结点进行递归遍历
        {
            if (!vis[neib])
                dft(graph, neib);
        }
    }

    // 广度优先遍历
    void bft(const Graph &graph, int start)
    {
        vector<bool> vis(graph.size(), false);
        queue<int> queue;

        vis[start] = true;
        queue.push(start);

        while (!queue.empty())
        {
            int curr = queue.front();
            queue.pop();

            for (int neib : graph[curr]) // 邻接未访问过的结点入队
            {
                if (!vis[neib])
                {
                    cout << neib << " ";
                    vis[neib] = true;
                    queue.push(neib);
                }
            }
        }
    }
    // 深度优先搜索路径是否存在
    bool existPathDFS(const Graph &graph, int start, int end)
    {
        if (start == end)
            return true;

        vis[start] = true;
        for (int neib : graph[start]) // 探索邻接结点
        {
            if (!vis[neib] && existPathDFS(graph, neib, end))
                return true;
        }
        return false;
    }

    // 广度优先搜索路径是否存在
    bool existPathBFS(const Graph &graph, int start, int end)
    {
        if (start == end)
            return true;

        vector<bool> vis(graph.size(), false);
        queue<int> queue;

        vis[start] = true;
        queue.push(start);

        while (!queue.empty())
        {
            int curr = queue.front();
            queue.pop();

            for (int neib : graph[curr])
            {
                if (neib == end)
                    return true;
                if (!vis[neib])
                {
                    vis[neib] = true;
                    queue.push(neib);
                }
            }
        }
        return false;
    }
    // 深度优先搜索求最短路径
    void findPathDFS(const Graph &graph, int start, int end)
    {
        if (start == end)
        {
            cout << start;
            return;
        }
        vector<int> shortestPath, currPath;
        vector<bool> vis(graph.size(), false);
        int minDist = INT_MAX;

        function<void(int)> dfs = [&](int curr)
        {
            currPath.push_back(curr);
            vis[curr] = true;

            if (curr == end)
            {
                if (currPath.size() < minDist)
                {
                    minDist = currPath.size();
                    shortestPath = currPath;
                }
                // 关键的两步，防止其他路径无法到达，要将end结点回溯掉
                currPath.pop_back();
                vis[curr] = false;
                return;
            }

            for (int neib : graph[curr])
            {
                if (!vis[neib])
                {
                    if (currPath.size() >= minDist)
                        break; // 剪枝
                    dfs(neib); // 递归探索
                }
            }
            // 回溯
            currPath.pop_back();
            vis[curr] = false;
        };

        dfs(start);

        for (int step : shortestPath)
        {
            cout << step << ' ';
        }
    }
    // 广度优先搜索求最短路径
    void findPathBFS(const Graph &graph, int start, int end)
    {
        if (start == end)
        {
            cout << start;
            return;
        }
        unordered_map<int, int> prev;
        vector<bool> vis(graph.size(), false);
        vis[start] = true;
        queue<int> q;
        q.push(start);
        while (!q.empty())
        {
            int front = q.front();
            q.pop();
            if (front == end)
            {
                // 重建路径
                vector<int> path;
                int curr = end;
                while (curr != start)
                {
                    path.push_back(curr);
                    curr = prev[curr];
                }
                path.push_back(start);
                reverse(path.begin(), path.end());
                // 输出路径
                for (int step : path)
                {
                    cout << step << ' ';
                }
                return;
            }
            // 向各个方向搜索
            for (int neib : graph[front])
            {
                if (!vis[neib])
                {
                    q.push(neib);
                    vis[neib] = true;
                    prev[neib] = front;
                }
            }
        }
    }
};

// 判断无向图是否连通
bool isConnected(const Graph &graph)
{
    vector<bool> vis(graph.size(), false);

    function<void(int)> dfs = [&](int val)
    {
        vis[val] = true;
        for (int neib : graph[val])
        {
            if (!vis[neib])
            {
                dfs(neib);
            }
        }
    };

    dfs(0); // 从顶点0开始DFS

    // 检查所有顶点是否都被访问过
    return all_of(vis.begin(), vis.end(), [&](bool v)
                  { return v; }); // 注意这里必须是连续的数字或者字符，字符需要从连续分布的起点开始
}

// 无向图求顶点v的度
int Degree1(const Graph &graph, int v)
{
    return graph[v].size();
}

// 有向图求顶点v的出度和入度
vector<int> Degree2(const Graph &graph, int v)
{
    vector<int> degree(2, 0); // degree[0]=出度, degree[1]=入度

    // 计算出度（直接统计邻接表大小）
    degree[0] = graph[v].size();

    // 计算入度（遍历所有顶点）
    for (int u = 0; u < graph.size(); ++u)
    {
        // 从所有的顶点检查邻接结点，如果邻居是v则计算一个入度
        for (int neib : graph[u])
        {
            if (neib == v)
            {
                ++degree[1];
                break; // 每个顶点只需找到一个v即可
            }
        }
    }

    return degree;
}

// 图论七大算法
class GraphAlgorithms
{
public:
    const static int INF = 100000;
    using Edge = pair<int, int>; //(vertax,weight)
    using Graph = vector<vector<int>>;
    using wGraph = vector<vector<Edge>>;
    // 拓扑排序Kahn算法
    vector<int> topologicalSort(const Graph &g)
    {
        int V = g.size();
        vector<int> inDegrees(V, 0); // 入度数组
        queue<int> q;                // 存储入度为0的顶点
        vector<int> result;          // 结果
        // 1. 计算所有顶点的入度
        for (int i = 0; i < V; i++)
        {
            for (int j : g[i])
                inDegrees[j]++;
        }
        // 2. 初始化队列(入度为0的顶点入队)
        for (int i = 0; i < V; i++)
        {
            if (!inDegrees[i])
                q.push(i);
        }
        // 3. 筛除入度为0的顶点，更新并入队新的入度0顶点
        while (!q.empty())
        {
            int frt = q.front();
            q.pop();
            result.push_back(frt);
            for (int neib : g[frt])
            {
                if (--inDegrees[neib] == 0)
                    q.push(neib);
            }
        }
        if (result.size() != V)
            return {}; // 存在环，无法生成拓扑序列
        return result;
    }

    // 优先队列按权重排序结构体
    struct EdgeComparison
    {
        bool operator()(const Edge &e1, const Edge &e2) { return e1.second > e2.second; } // 小顶堆->大于
    };

    // 最小生成树(MST)算法

    // Prim算法
    class Prim
    { // 适合稠密图
    public:
        vector<int> parent, lowCost;
        vector<bool> vis;
        priority_queue<Edge, vector<Edge>, EdgeComparison> pq; // 优先队列,从 O( V^2 ) ​优化到 ​O(E log V)
        vector<pair<Edge, int>> result;
        int start;
        Prim(const wGraph &wg, int start = 0) : start(start)
        {
            int V = wg.size();
            parent.assign(V, -1);
            lowCost.assign(V, INF);
            vis.assign(V, false);
            pq.push({start, 0});
            lowCost[start] = 0;
            while (!pq.empty())
            {
                auto top = pq.top();
                pq.pop();
                int curr = top.first, currw = top.second;
                if (vis[curr])
                    continue;
                vis[curr] = true;
                if (parent[curr] != -1)
                    result.push_back({{parent[curr], curr}, currw});
                for (auto edge : wg[curr])
                { // 更新邻接顶点的最小权重
                    int neib = edge.first, w = edge.second;
                    if (!vis[neib] && w < lowCost[neib])
                    {
                        lowCost[neib] = w;
                        parent[neib] = curr;
                        pq.push({neib, w});
                    }
                }
            }
        }
    };

    // Kruskal算法
    class Kruskal
    { // 适合稀疏图
    public:
        struct KEdge
        {
            int from, to, w;
            KEdge(int f, int t, int w) : from(f), to(t), w(w) {}
            bool operator<(const KEdge &other)
            {
                return this->w < other.w; // 按权重排序
            }
        };
        vector<int> parent, rank;
        vector<KEdge> mstEdges, edges;
        // 并查集查找
        int find(int u)
        {
            while (u != parent[u])
            { // 路径压缩
                parent[u] = parent[parent[u]];
                u = parent[u];
            }
            return u;
        }
        Kruskal(const wGraph &wg)
        {
            int V = wg.size();
            parent.assign(V, -1);
            rank.assign(V, 0);
            for (int u = 0; u < V; u++)
                parent[u] = u; // 初始化父节点
            for (int u = 0; u < V; u++)
            {
                for (auto edge : wg[u])
                {
                    int v = edge.first, w = edge.second;
                    if (u < v)
                        edges.emplace_back(u, v, w);
                }
            }
            sort(edges.begin(), edges.end()); // 按权重排序
            for (auto edge : edges)
            { // 并查集按秩合并
                int ru = find(edge.from), rv = find(edge.to);
                if (ru == rv)
                    continue;
                mstEdges.push_back(edge);
                if (rank[ru] < rank[rv])
                    parent[ru] = rv;
                else
                {
                    parent[rv] = ru;
                    if (rank[ru] == rank[rv])
                        rank[ru]++;
                }
                if (mstEdges.size() == V - 1)
                    break;
            }
        }
    };

    // 最短路径算法
    // Dijkstra算法和Floyd算法都可以处理有向图和无向图，但是在下面的算法中处理的是针对于有向图的邻接表形式，不可以直接放入无向图。
    // 解决方法：
    // 1.如果是一个无向图邻接矩阵，则每次读取一条边u->v的时候，同时也将v->u存储入邻接表，如此可以获得一个双向图邻接表（即无向图的有向图形式）；
    // 2.如果是一个无向图邻接表，则先将邻接表转换为邻接矩阵，然后用1的方法还原为双向图邻接表。

    // Dijkstra算法
    class Dijkstra
    { // 不可以有负权或负权环
    public:
        vector<int> parent, dist;
        vector<bool> vis;
        priority_queue<Edge, vector<Edge>, EdgeComparison> pq; // 优先队列优化.O((V+E)logV)
        int start;
        Dijkstra(const wGraph &wg, int start = 0, int end = 0) : start(start)
        {
            int V = wg.size();
            parent.assign(V, -1);
            dist.assign(V, INF);
            vis.assign(V, false);
            pq.push({start, 0});
            dist[start] = 0;
            while (!pq.empty())
            {
                auto top = pq.top();
                pq.pop();
                int u = top.first;
                if (vis[u])
                    continue;
                vis[u] = true;
                for (auto edge : wg[u])
                { // 更新所有邻接顶点的权重
                    int v = edge.first, w = edge.second;
                    if (!vis[v] && dist[u] + w < dist[v])
                    {
                        dist[v] = dist[u] + w;
                        parent[v] = u;
                        pq.push({v, dist[v]});
                    }
                }
            }
        }
        // 重建路径
        vector<int> rebuildPath(int end)
        {
            vector<int> path;
            if (dist[end] == INF)
                return path;
            int curr = end;
            while (curr != start)
            {
                path.push_back(curr);
                curr = parent[curr];
            }
            path.push_back(start);
            reverse(path.begin(), path.end());
            return path;
        }
        // 路径总长度
        int pathLength(int end)
        {
            return dist[end] == INF ? -1 : dist[end];
        }
    };

    // Floyd-Warshall算法
    class FloydWarshall
    { // 可以有负权，但是不能有负权环，但是可检测出负权环
    public:
        vector<vector<int>> parent, dist;
        bool hasNegativeCircle;
        FloydWarshall(const wGraph &wg, int start = 0, int end = 0) : hasNegativeCircle(false)
        {
            int V = wg.size();
            parent.assign(V, vector<int>(V, -1));
            dist.assign(V, vector<int>(V, INF));
            for (int i = 0; i < V; i++)
            {
                dist[i][i] = 0;
                for (auto edge : wg[i])
                {
                    int j = edge.first, w = edge.second;
                    dist[i][j] = w;
                    parent[i][j] = i;
                }
            }
            // 三重循环,O(N^3)
            for (int k = 0; k < V; k++)
            {
                for (int i = 0; i < V; i++)
                {
                    for (int j = 0; j < V; j++)
                    {
                        if (dist[i][k] < INF && dist[k][j] < INF && dist[i][j] > dist[i][k] + dist[k][j])
                        {
                            dist[i][j] = dist[i][k] + dist[k][j];
                            parent[i][j] = parent[k][j];
                        }
                    }
                }
            }
            // 可以检测负权环
            for (int i = 0; i < V; i++)
            {
                if (dist[i][i] < 0)
                {
                    hasNegativeCircle = true;
                    break;
                }
            }
        }
        // 重建路径
        vector<int> rebuildPath(int start, int end)
        {
            vector<int> path;
            if (dist[start][end] == INF)
                return path;
            int curr = end;
            while (curr != start)
            {
                path.push_back(curr);
                curr = parent[start][curr];
            }
            path.push_back(start);
            reverse(path.begin(), path.end());
            return path;
        }
        // 路径总长度
        int pathLength(int start, int end)
        {
            return dist[start][end] == INF ? -1 : dist[start][end];
        }
    };

    // Bellman-Ford算法
    class BellmanFord
    {
    public:
        vector<int> dist, parent;
        bool hasNegativeCycle = false;

        BellmanFord(const wGraph &graph, int start)
        {
            int V = graph.size();
            dist.assign(V, INF);
            parent.assign(V, -1);
            dist[start] = 0;
            hasNegativeCycle = false;

            // 松弛操作：进行V-1轮迭代
            for (int i = 0; i < V - 1; ++i)
            {
                for (int u = 0; u < V; ++u)
                {
                    if (dist[u] == INF)
                        continue; // 跳过未访问的节点
                    for (const Edge &edge : graph[u])
                    {
                        int v = edge.first, w = edge.second;
                        if (dist[u] + w < dist[v])
                        {
                            dist[v] = dist[u] + w;
                            parent[v] = u;
                        }
                    }
                }
            }

            // 第V轮检查负权环
            for (int u = 0; u < V; ++u)
            {
                for (const Edge &edge : graph[u])
                {
                    int v = edge.first, w = edge.second;
                    if (dist[u] != INF && dist[u] + w < dist[v])
                    {
                        hasNegativeCycle = true;
                        return;
                    }
                }
            }
        }
        // 重建路径
        vector<int> rebuildPath(int end)
        {
            vector<int> path;
            if (dist[end] == INF)
                return path;
            for (int at = end; at != -1; at = parent[at])
            {
                path.push_back(at);
            }
            reverse(path.begin(), path.end());
            return path;
        }
    };

    // 深度优先搜索DFS/广度优先搜索BFS,以迷宫路径问题为例
    class MazePathSolution
    {
    public: // vector<vector<int>> maze = {
        //     {0, 0, 0, 0, 0, 0, 1, 1, 0},
        //     {0, 1, 0, 0, 1, 1, 0, 1, 1},
        //     {0, 1, 0, 0, 0, 0, 1, 1, 1},
        //     {0, 0, 0, 1, 1, 1, 1, 0, 0},
        //     {1, 0, 0, 1, 0, 0, 1, 1, 1},
        //     {0, 0, 0, 0, 0, 0, 0, 0, 0},
        //     {1, 1, 0, 1, 0, 1, 1, 0, 0}};
        // cord begin = {0, 0}, end = {6, 8};
        typedef pair<int, int> cord;
        // 计算曼哈顿距离
        int manhattanDistance(cord a, cord b)
        {
            return abs(a.first - b.first) + abs(a.second - b.second);
        }
        // 深度优先搜索(递归)--迷宫路径存在性问题（加入曼哈顿距离剪枝）
        vector<cord> findPath_DFS(const vector<vector<int>> &maze, cord begin, cord end)
        {
            vector<cord> directions = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}; // 四个移动方向
            int row = maze.size(), col = maze[0].size();
            vector<vector<bool>> vis(row, vector<bool>(col, false)); // 探索历史
            vector<cord> path;                                       // 当前路径
            int minPathLength = INT_MAX;                             // 记录当前找到的最小路径长度
            vector<cord> shortestPath;                               // 记录最短路径
            // DFS回溯函数
            function<void(cord)> dfs = [&](cord curr)
            {
                vis[curr.first][curr.second] = true;
                path.push_back(curr);
                if (curr == end)
                {
                    if (path.size() < minPathLength)
                    {
                        minPathLength = path.size();
                        shortestPath = path;
                    }
                    // 将终点回溯，以免影响其他回溯
                    path.pop_back();
                    vis[curr.first][curr.second] = false;
                    return;
                }
                for (cord direct : directions)
                {
                    int X = curr.first + direct.first, Y = curr.second + direct.second;
                    if (X >= 0 && X < row && Y >= 0 && Y < col)
                    {
                        if (maze[X][Y] == 0 && !vis[X][Y])
                        {
                            // 计算当前路径的代价（已走步数 + 曼哈顿距离）
                            int currCost = path.size() + manhattanDistance({X, Y}, end);
                            // 如果当前路径的代价超过最小路径长度，剪枝
                            if (currCost >= minPathLength)
                                break;
                            dfs({X, Y});
                        }
                    }
                }
                // 回溯
                path.pop_back();
                vis[curr.first][curr.second] = false;
            };
            dfs(begin);
            // 返回最短路径
            return shortestPath;
        }
        // 深度优先搜索(栈)
        vector<cord> findPath_DFS_Stack(const vector<vector<int>> &maze, cord begin, cord end)
        {
            vector<cord> directions = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}; // 四个移动方向
            int row = maze.size(), col = maze[0].size();
            vector<vector<bool>> vis(row, vector<bool>(col, false)); // 探索历史
            vis[begin.first][begin.second] = true;                   // 标记起点为已访问
            stack<cord> stack;
            stack.push(begin);           // 起点压栈
            vector<cord> path = {begin}; // 当前路径
            int minPathLength = INT_MAX; // 记录当前找到的最小路径长度
            vector<cord> shortestPath;   // 记录最短路径
            while (!stack.empty())
            {
                cord curr = stack.top(); // 取栈顶为当前坐标
                // 注意不要一开始就弹出栈顶，而是最后回溯的时候才弹出栈顶

                if (curr == end)
                {
                    // 找到终点，更新最小路径长度和最短路径
                    if (path.size() < minPathLength)
                    {
                        minPathLength = path.size();
                        shortestPath = path; // 更新最短路径
                    }
                }

                bool found_next = false;
                for (cord direct : directions)
                {
                    int X = curr.first + direct.first, Y = curr.second + direct.second;
                    if (X >= 0 && X < row && Y >= 0 && Y < col)
                    {
                        if (maze[X][Y] == 0 && !vis[X][Y])
                        {
                            // 计算当前路径的代价（已走步数 + 曼哈顿距离）
                            int currCost = path.size() + manhattanDistance({X, Y}, end);
                            // 如果当前路径的代价超过最小路径长度，剪枝
                            if (currCost >= minPathLength)
                                continue;
                            stack.push(make_pair(X, Y));
                            path.push_back(make_pair(X, Y)); // 将新点加入路径
                            vis[X][Y] = true;
                            found_next = true;
                            break; //!!!!!!!!!!!别忘了这个break!!!!!!!!!!!!!
                        }
                    }
                }

                if (!found_next)
                {
                    // 没有可移动的方向，回溯
                    stack.pop();
                    path.pop_back(); // 从路径中移除当前点
                }
            }

            // 返回最短路径
            return shortestPath;
        }

        // 广度优先搜索--迷宫最短路径问题
        vector<cord> findPath_BFS(const vector<vector<int>> &maze, cord begin, cord end)
        {
            vector<cord> directions = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
            int row = maze.size(), col = maze[0].size();
            vector<vector<bool>> vis(row, vector<bool>(col, false));
            std::queue<cord> queue;
            queue.push(begin);
            vis[begin.first][begin.second] = true;
            map<cord, cord> prev; // 记录每个节点的前驱节点，以便于重建路径
            while (!queue.empty())
            {
                cord curr = queue.front();
                queue.pop(); // 广义优先搜索是一开头就直接排出队首
                if (curr == end)
                {
                    // 重建路径并返回
                    vector<cord> path;
                    cord temp = curr;
                    while (temp != begin)
                    {
                        path.push_back(temp);
                        temp = prev[temp];
                    }
                    path.push_back(begin);
                    reverse(path.begin(), path.end());
                    return path;
                }
                // 探索各个方向
                for (cord direct : directions)
                {
                    int X = curr.first + direct.first, Y = curr.second + direct.second;
                    if (X >= 0 && X < row && Y >= 0 && Y < col)
                    {
                        if (maze[X][Y] == 0 && !vis[X][Y])
                        {
                            vis[X][Y] = true;
                            prev[{X, Y}] = curr;
                            queue.push({X, Y});
                            //!!!!!!!!!!!这里不能有break!!!!!!!!!!!!!
                        }
                    }
                }
            }
            // 如果队列为空且没有找到终点，则返回空的路径
            return vector<cord>();
        }
        void test()
        {
            vector<vector<int>> maze = {
                {0, 0, 0, 0, 0, 0, 1, 1, 0},
                {0, 1, 0, 0, 1, 1, 0, 1, 1},
                {0, 1, 0, 0, 0, 0, 1, 1, 1},
                {0, 0, 0, 1, 1, 1, 1, 0, 0},
                {1, 0, 0, 1, 0, 0, 1, 1, 1},
                {0, 0, 0, 0, 0, 0, 0, 0, 0},
                {1, 1, 0, 1, 0, 1, 1, 0, 0}};
            cord begin = {0, 0}, end = {6, 8};
            vector<cord> resultd = findPath_DFS(maze, begin, end);
            if (resultd.empty())
            {
                cout << "Empty";
            }
            else
                for (cord cd : resultd)
                {
                    cout << "(" << cd.first << ',' << cd.second << ')' << ' ';
                }
            cout << '\n';
            vector<cord> resultb = findPath_BFS(maze, begin, end);
            if (resultb.empty())
            {
                cout << "Empty";
            }
            else
                for (cord cd : resultb)
                {
                    cout << "(" << cd.first << ',' << cd.second << ')' << ' ';
                }
        }
    };
};

int main()
{
    Graph graph = {
        {1, 2},    // 顶点 0 的邻接顶点是 1 和 2
        {0, 2},    // 顶点 1 的邻接顶点是 0 和 2
        {0, 1, 3}, // 顶点 2 的邻接顶点是 0、1 和 3
        {2}        // 顶点 3 的邻接顶点是 2
    };
    print(graph);
}
