#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 10;
const int N = 110;

vector<vector<pair<int, int>>> graph(N);
bool visited[N];
int parent[N];

bool bfs(int s, int t)
{
    memset(visited, false, sizeof(visited));
    queue<int> q;
    q.push(s);
    visited[s] = true;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (auto edge : graph[u])
        {
            int v = edge.first;
            int w = edge.second;

            if (!visited[v] && w > 0)
            {
                parent[v] = u;
                visited[v] = true;
                q.push(v);
            }
        }
    }

    return visited[t];
}

int fordFulkerson_EdmondKarp(int s, int t)
{
    int max_flow = 0;
    while (bfs(s, t))
    {
        int path_flow = INF;

        for (int v = t; v != s; v = parent[v])
        {
            int u = parent[v];

            for (auto &edge : graph[u])
            {
                if (edge.first == v)
                {
                    path_flow = min(path_flow, edge.second);
                    break;
                }
            }
        }

        for (int v = t; v != s; v = parent[v])
        {
            int u = parent[v];

            for (auto &edge : graph[u])
            {
                if (edge.first == v)
                {
                    edge.second -= path_flow;
                    break;
                }
            }

            for (auto &edge : graph[v])
            {
                if (edge.first == u)
                {
                    edge.second += path_flow;
                    break;
                }
            }
        }

        max_flow += path_flow;
    }

    return max_flow;
}

void addEdge(int u, int v, int w)
{
    graph[u].push_back({v, w});
    // graph[v].push_back({u, 0});
}

int main(int argc, char const *argv[])
{

    addEdge(0, 1, 10);
    addEdge(0, 3, 5);
    addEdge(1, 2, 10);
    addEdge(3, 2, 5);

    // addEdge(0, 1, 10);
    // addEdge(0, 2, 5);
    // addEdge(1, 2, 15);
    // addEdge(1, 3, 10);
    // addEdge(2, 4, 10);
    // addEdge(3, 4, 5);
    // addEdge(3, 5, 10);
    // addEdge(4, 5, 10);
    // addEdge(4, 6, 5);
    // addEdge(5, 7, 15);
    // addEdge(6, 7, 10);
    cout << fordFulkerson_EdmondKarp(0, 3) << endl;

    return 0;
}