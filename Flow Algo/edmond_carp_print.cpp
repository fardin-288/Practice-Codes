#include <bits/stdc++.h>
using namespace std;

const int V = 6;
bool visited[V];
int parent[V];

bool bfs(int rGraph[V][V], int s, int t)
{
    memset(visited, false, sizeof(visited));

    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int v = 0; v < V; v++)
        {
            if (visited[v] == false && rGraph[u][v] > 0)
            {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    return visited[t];
}

void printMaxFlowAndEdges(int graph[V][V], int s, int t)
{
    int u, v;
    int rGraph[V][V];

    for (u = 0; u < V; u++)
        for (v = 0; v < V; v++)
            rGraph[u][v] = graph[u][v];

    int max_flow = 0;

    while (bfs(rGraph, s, t))
    {
        int path_flow = INT_MAX;
        for (v = t; v != s; v = parent[v])
        {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }

        for (v = t; v != s; v = parent[v])
        {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        max_flow += path_flow;
    }

    cout << "Maximum Flow: " << max_flow << endl;

    cout << "Edges in the Maximum Flow:" << endl;
    for (u = 0; u < V; u++)
    {
        for (v = 0; v < V; v++)
        {
            if (graph[u][v] > 0 && rGraph[u][v] < graph[u][v])
            {
                cout << "Edge (" << u << " -> " << v << "), Flow = " << graph[u][v] - rGraph[u][v] << endl;
            }
        }
    }
}

int main()
{
    int graph[V][V] = {{0, 16, 13, 0, 0, 0},
                       {0, 0, 10, 12, 0, 0},
                       {0, 4, 0, 0, 14, 0},
                       {0, 0, 9, 0, 0, 20},
                       {0, 0, 0, 7, 0, 4},
                       {0, 0, 0, 0, 0, 0}};

    int source = 0;
    int sink = 5;

    printMaxFlowAndEdges(graph, source, sink);

    return 0;
}
