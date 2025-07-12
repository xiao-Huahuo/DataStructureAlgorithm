#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <algorithm>
using namespace std;
using Graph = vector<vector<int>>;
using Edge = pair<int, int>;
using wGraph = vector<vector<Edge>>;
const static int INF = 1000000;
struct Comparison
{
    bool operator()(const Edge &e1, const Edge &e2) { return e1.second > e2.second; }
};
class Prim
{
public:
    Prim(const wGraph &wg, int start)
    {
        int V = wg.size();
        vector<int> parent(V, -1);
        vector<int> lowCost(V, INF);
        vector<bool> vis(V, false);
        priority_queue<Edge, vector<Edge>, Comparison> pq;
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
            for (auto edge : wg[curr])
            {
                int neib = edge.first, w = edge.second;
                if (!vis[neib] && w < lowCost[neib])
                {
                    lowCost[neib] = w;
                    parent[neib] = curr;
                    pq.emplace(neib, w);
                }
            }
        }
    }
};
class Kruskal
{
public:
    struct KEdge
    {
        int from, to, w;
        KEdge(int f, int t, int w) : from(f), to(t), w(w) {}
        bool operator<(const KEdge &other) { return this->w < other.w; }
    };
    vector<int> parent, rank;
    vector<KEdge> edges, results;
    int find(int u)
    {
        while (u != parent[u])
        {
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
        for (int i = 0; i < V; i++)
            parent[i] = i;
        for (int i = 0; i < V; i++)
        {
            for (auto edge : wg[i])
            {
                int j = edge.first, w = edge.second;
                if (i < j)
                    edges.emplace_back(i, j, w);
            }
        }
        sort(edges.begin(), edges.end());
        for (auto edge : edges)
        {
            int u = find(edge.from), v = find(edge.to);
            if (u == v)
                continue;
            results.push_back(edge);
            int ru = rank[u], rv = rank[v];
            if (ru < rv)
                parent[u] = v;
            else
            {
                parent[v] = u;
                rank[u]++;
            }
            if (results.size() == V - 1)
                break;
        }
    }
};

class Dijkstra
{
public:
    vector<int> parent, dist;
    int start;
    Dijkstra(const wGraph &wg, int start) : start(start)
    {
        int V = wg.size();
        parent.assign(V, -1);
        dist.assign(V, INF);
        vector<bool> vis(V, false);
        priority_queue<Edge, vector<Edge>, Comparison> pq;
        pq.push({start, 0});
        dist[start] = 0;
        while (!pq.empty())
        {
            auto top = pq.top();
            pq.pop();
            int u = top.first, minDist = top.second;
            if (vis[u])
                continue;
            vis[u] = true;
            for (auto edge : wg[u])
            {
                int v = edge.first, w = edge.second;
                if (!vis[v] && dist[u] + w < dist[v])
                {
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                    pq.emplace(v, dist[v]);
                }
            }
        }
    }
};

class FloydWarshall
{
public:
    vector<vector<int>> parent, dist;
    int start, end;
    bool hasNegCycle;
    FloydWarshall(const wGraph &wg, int start, int end) : start(start), end(end)
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
        for (int i = 0; i < V; i++)
        {
            if (dist[i][i] < 0)
            {
                hasNegCycle = true;
                break;
            }
        }
    }
};

vector<int> topologicalSort(const Graph &g)
{
    int V = g.size();
    vector<int> result, inDegrees(V, 0);
    queue<int> zeros;
    for (int i = 0; i < V; i++)
    {
        for (int j : g[i])
        {
            inDegrees[j]++;
        }
    }
    for (int i = 0; i < V; i++)
    {
        if (!inDegrees[i])
            zeros.push(i);
    }
    while (!zeros.empty())
    {
        int curr = zeros.front();
        result.push_back(curr);
        zeros.pop();
        for (int neighbor : g[curr])
        {
            if (--inDegrees[neighbor] == 0)
                zeros.push(neighbor);
        }
    }
    return result;
}
#include <functional>
void dfs(const Graph &g, int start)
{
    printf("DFS");
}