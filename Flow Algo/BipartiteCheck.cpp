#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;

vector<vector<int>> adj;

bool isBipartite()
{
    int color[N];
    memset(color, -1, sizeof(color));

    queue<int> q;
    q.push(1);
    color[1] = 1;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int v : adj[u])
        {
            if (color[v] == -1)
            {
                color[v] = 1 - color[u];
                q.push(v);
            }
            else if ((color[v] == color[u]) or (v == u))
                return false;
        }
    }
    return true;
}
