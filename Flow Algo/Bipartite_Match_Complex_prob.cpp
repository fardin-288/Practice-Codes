#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 10;
const int N = 110;
const int P = 4;
const int J = 4;
const int V = P + J + 2;

// int graph[N][N];
// int rgraph[N][N];
int parent[V];
bool vis[V];

bool bfs(int s, int t, int graph[][V])
{
    memset(vis, false, sizeof(vis));

    queue<int> q;
    q.push(s);

    parent[s] = -1;
    vis[s] = true;

    while (q.empty() == false)
    {
        int u = q.front();
        q.pop();

        for (int v = 0; v < V; v++)
        {
            if (graph[u][v] > 0 and vis[v] == false)
            {
                vis[v] = true;
                q.push(v);
                parent[v] = u;
            }
        }
    }

    return vis[t];
}

int Edmond_Karp(int s, int t, int graph[][V])
{
    int rgraph[V][V];
    int max_flow = 0;

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            rgraph[i][j] = graph[i][j];
        }
    }

    int prev_parent[V];

    while (bfs(s, t, rgraph))
    {
        int path_flow = INF;

        for (int v = t; v != s; v = parent[v])
        {
            int u = parent[v];
            prev_parent[v] = parent[v];
            path_flow = min(path_flow, graph[u][v]);
        }

        for (int v = t; v != s; v = parent[v])
        {
            int u = parent[v];
            rgraph[u][v] -= path_flow;
            rgraph[v][u] += path_flow;
        }

        max_flow += path_flow;
    }

    memcpy(parent, prev_parent, sizeof(parent));

    cout << "Flow : " << max_flow << endl;

    // for (int i = 0; i < V; i++)
    // {
    //     for (int j = 0; j < V; j++)
    //     {
    //         if (graph[i][j] > 0 and rgraph[i][j] < graph[i][j])
    //         {
    //             cout << i << "-->" << j << " : " << graph[i][j] - rgraph[i][j] << endl;
    //         }
    //     }
    // }

    for (int i = 1; i <= P; i++)
    {
        cout << "Person " << i << " got number of jobs : " << graph[0][i] - rgraph[0][i] << endl;
    }

    for (int i = 1; i <= J; i++)
    {
        cout << "Job " << i << " got filled by applicant : " << graph[P + i][P + J + 1] - rgraph[P + i][P + J + 1] << endl;
    }

    for (int i = 0; i < P; i++)
    {
        for (int j = 0; j < J; j++)
        {
            if (graph[i + 1][j + P + 1] > 0 and graph[i + 1][j + P + 1] > rgraph[i + 1][j + P + 1])
            {
                cout << "person :" << i + 1 << " has got job :" << j + 1 << endl;
            }
        }
    }

    return max_flow;
}

void maximim_bipartite(int preference[][J])
{
    int graph[P + J + 2][P + J + 2];

    for (int i = 0; i < P + J + 2; i++)
    {
        for (int j = 0; j < P + J + 2; j++)
        {
            graph[i][j] = 0;
        }
    }

    int personJobCapacity[P] = {2, 2, 2, 2};

    for (int i = 1; i <= P; i++)
    {
        graph[0][i] = personJobCapacity[i - 1];
    }

    // if capacity only once
    // for (int i = 1; i <= P; i++)
    // {
    //     graph[0][i] = 1;
    // }

    int jobOpening[J] = {1, 1, 2, 2};
    for (int i = P + 1; i < P + J + 1; i++)
    {
        graph[i][P + J + 1] = jobOpening[i - P - 1];
    }

    // if job opening obly once
    //  for (int i = P + 1; i < P + J + 1; i++)
    //  {
    //      graph[i][P + J + 1] = 1;
    //  }

    for (int i = 0; i < P; i++)
    {
        for (int j = 0; j < J; j++)
        {
            graph[i + 1][P + 1 + j] = preference[i][j];
        }
    }

    int max_job = Edmond_Karp(0, V - 1, graph);

    cout << "Total Jobs : " << max_job << endl;

    // for (int i = P + 1; i < P + J + 1; i++)
    // {
    //     cout << "Person: " << parent[i] << " get job :" << i - P << endl;
    // }
}

int main(int argc, char const *argv[])
{
    int graph[P][J] = {{1, 1, 0, 0},
                       {1, 0, 1, 0},
                       {0, 0, 1, 1},
                       {0, 1, 0, 0}};

    maximim_bipartite(graph);

    return 0;
}
