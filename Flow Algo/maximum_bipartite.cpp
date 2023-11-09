#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 10;
const int N = 4;
const int J = 3;

int graph[N + J + 2][N + J + 2];
// int graph[N + J + 2][N + J + 2] = {
//     {0, 2, 2, 2, 2, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 1, 1, 0, 0},
//     {0, 0, 0, 0, 0, 0, 1, 0, 0},
//     {0, 0, 0, 0, 0, 0, 1, 1, 0},
//     {0, 0, 0, 0, 0, 0, 0, 1, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 2},
//     {0, 0, 0, 0, 0, 0, 0, 0, 2},
//     {0, 0, 0, 0, 0, 0, 0, 0, 1},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0}};

bool visited[N + J + 2];
int match[N + J + 2];

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

        for (int v = 0; v < N + J + 2; v++)
        {
            if (!visited[v] && graph[u][v] > 0)
            {
                visited[v] = true;
                match[v] = u;
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

        for (int v = t; v != s; v = match[v])
        {
            int u = match[v];
            path_flow = min(path_flow, graph[u][v]);
        }

        for (int v = t; v != s; v = match[v])
        {
            int u = match[v];
            graph[u][v] -= path_flow;
            graph[v][u] += path_flow;
        }

        max_flow += path_flow;
    }

    return max_flow;
}

int main(int argc, char const *argv[])
{
    // N = 4, J = 3
    // random 6*6 list of if person likes job
    bool person_interest[N][J] = {{1, 1, 0},
                                  {0, 1, 0},
                                  {0, 1, 1},
                                  {0, 0, 1}};

    // list of how many jobs each person can do
    int job_ability[N] = {INF, INF, INF, INF};
    // int job_ability[N] = {2, 2, 2, 2};

    // vacancies for each job
    int job_vacancy[J] = {2, 2, 1};

    // filling preference matrix
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < J; j++)
        {
            if (person_interest[i][j])
            {
                graph[i + 1][j + N + 1] = 1;
            }
        }
    }

    // filling person capability
    for (int i = 0; i < N; i++)
    {
        graph[0][i + 1] = job_ability[i];
    }

    // fill job vacancy
    for (int i = 0; i < J; i++)
    {
        graph[i + N + 1][J + N + 1] = job_vacancy[i];
    }

    // for (int i = 0; i < N + J + 2; i++)
    // {
    //     for (int j = 0; j < N + J + 2; j++)
    //     {
    //         cout << graph[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    cout << fordFulkerson_EdmondKarp(0, N + J + 1) << endl;

    // for (int i = N + 1; i < N + J + 1; i++)
    // {
    //     cout << match[i] << " ";
    // }

    return 0;
}
