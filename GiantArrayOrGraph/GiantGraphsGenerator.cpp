#include <vector>
#include <random>
#include <algorithm>
#include <unordered_set>
#include <iostream>
#include <fstream>

using Graph = std::vector<std::vector<int>>;                  // 邻接表
using wGraph = std::vector<std::vector<std::pair<int, int>>>; // 带权图,(vertex,weight)

// 生成一个具有n个顶点和m条边的随机带权无向图
wGraph generateRandomWeightedGraph(int n, int m, int minWeight = 1, int maxWeight = 20)
{
    if (m > n * (n - 1) / 2)
    {
        throw std::invalid_argument("Too many edges for the given number of vertices");
    }

    wGraph graph(n);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> vertexDis(0, n - 1);
    std::uniform_int_distribution<> weightDis(minWeight, maxWeight);

    // 使用集合来避免重复边
    std::unordered_set<int> edges;
    auto edgeHash = [n](int u, int v)
    {
        return u * n + v; // 简单的哈希函数
    };

    int edgesAdded = 0;
    while (edgesAdded < m)
    {
        int u = vertexDis(gen);
        int v = vertexDis(gen);

        // 确保u != v (无自环)且边不存在
        if (u == v)
            continue;
        if (u > v)
            std::swap(u, v); // 确保u < v，避免重复存储

        int hash = edgeHash(u, v);
        if (edges.count(hash))
            continue;

        // 生成随机权重
        int weight = weightDis(gen);

        // 添加边（双向）
        graph[u].emplace_back(v, weight);
        graph[v].emplace_back(u, weight);
        edges.insert(hash);
        edgesAdded++;
    }

    return graph;
}

// 从带权图生成无权图
Graph convertToUnweightedGraph(const wGraph &wg)
{
    Graph g(wg.size());
    for (size_t i = 0; i < wg.size(); ++i)
    {
        for (const auto &edge : wg[i])
        {
            g[i].push_back(edge.first);
        }
    }
    return g;
}

// 将带权图保存到文本文件
void saveGraphsToFile(const wGraph &wg, const Graph &g, const std::string &filename,
                      const std::string &wgVarName, const std::string &gVarName)
{
    std::ofstream outFile(filename);
    if (!outFile)
    {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }

    // 写入头文件和类型定义
    outFile << "#include <vector>\n";
    outFile << "using Graph = std::vector<std::vector<int>>;// 邻接表\n";
    outFile << "using wGraph = std::vector<std::vector<std::pair<int, int>>>; // 带权图,(vertex,weight)\n\n";

    // 写入带权图
    outFile << "wGraph " << wgVarName << " = {\n";
    for (size_t i = 0; i < wg.size(); ++i)
    {
        outFile << "    {";
        for (size_t j = 0; j < wg[i].size(); ++j)
        {
            outFile << "{" << wg[i][j].first << ", " << wg[i][j].second << "}";
            if (j != wg[i].size() - 1)
            {
                outFile << ", ";
            }
        }
        outFile << "}";
        if (i != wg.size() - 1)
        {
            outFile << ",";
        }
        outFile << "               // " << i << "\n";
    }
    outFile << "};\n\n";

    // 写入无权图
    outFile << "Graph " << gVarName << " = {\n";
    for (size_t i = 0; i < g.size(); ++i)
    {
        outFile << "    {";
        for (size_t j = 0; j < g[i].size(); ++j)
        {
            outFile << g[i][j];
            if (j != g[i].size() - 1)
            {
                outFile << ", ";
            }
        }
        outFile << "}";
        if (i != g.size() - 1)
        {
            outFile << ",";
        }
        outFile << "//" << i << "\n";
    }
    outFile << "};\n";

    outFile.close();
    std::cout << "Graph data saved to " << filename << std::endl;
}

int main()
{
    // 生成一个有100个顶点和1000条边的随机带权图
    const int vertexCount = 100;
    const int edgeCount = 1000;
    const int minWeight = 1;
    const int maxWeight = 20;

    wGraph wg = generateRandomWeightedGraph(vertexCount, edgeCount, minWeight, maxWeight);
    Graph g = convertToUnweightedGraph(wg);

    // 验证边数
    int actualEdges = 0;
    for (const auto &neighbors : wg)
    {
        actualEdges += neighbors.size();
    }
    actualEdges /= 2; // 因为是无向图

    // 打印一些信息
    std::cout << "Generated graphs with " << vertexCount << " vertices and "
              << actualEdges << " edges." << std::endl;

    // 将图保存到文件
    saveGraphsToFile(wg, g, "Giant_Graphs.h", "SuperWeightGraph", "SuperGraph");

    return 0;
}