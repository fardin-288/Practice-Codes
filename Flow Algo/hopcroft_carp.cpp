#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 10;
const int N = 6;

bool graph[][6] = {{0, 1, 1, 0, 0, 0},
                   {1, 0, 0, 1, 0, 0},
                   {0, 0, 1, 0, 0, 0},
                   {0, 0, 1, 1, 0, 0},
                   {0, 0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0, 1}};
int match[N];
bool visited[N];

bool dfs(int s)
{
    for (int i = 0; i < N; i++)
    {
        if (graph[s][i] && !visited[i])
        {
            visited[i] = true;
            if (match[i] == -1 || dfs(match[i]))
            {
                match[i] = s;
                return true;
            }
        }
    }
    return false;
}

int hopcroft_carp(void)
{

    memset(match, -1, sizeof(match));
    int max_flow = 0;

    for (int i = 0; i < N; i++)
    {
        memset(visited, false, sizeof(visited));

        if (dfs(i))
        {
            max_flow++;
        }
    }

    return max_flow;
}

int main(int argc, char const *argv[])
{

    cout << hopcroft_carp() << endl;

    return 0;
}
