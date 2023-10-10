#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 10;
const int INF = 1e9 + 10;
int dp[N][N];
int dp2[N][N];
int bracket[N][N];

int MCM(int arr[], int i, int j)
{
    if (i == j)
    {
        return 0;
    }
    if (dp[i][j] != -1)
    {
        return dp[i][j];
    }
    dp[i][j] = INF;

    for (int k = i; k < j; k++)
    {
        dp[i][j] = min(dp[i][j], MCM(arr, i, k) + MCM(arr, k + 1, j) + arr[i - 1] * arr[k] * arr[j]);
    }

    return dp[i][j];
}

int MCM2(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        dp2[i][i] = 0;
    }

    for (int L = 1; L <= n - 2; L++)
    {
        for (int i = 1; i <= n - 2; i++)
        {
            dp2[i][i + L] = min(dp2[i][i + L - 1] + arr[i - 1] * arr[i + L - 1] * arr[i + L],
                                dp2[i + 1][i + L] + arr[i - 1] * arr[i] * arr[i + L]);

            if (dp2[i][i + L - 1] + arr[i - 1] * arr[i + L - 1] * arr[i + L] > dp2[i + 1][i + L] + arr[i - 1] * arr[i] * arr[i + L])
            {
                bracket[i][i + L] = i;
            }
            else
            {
                bracket[i][i + L] = i + L - 1;
            }
        }
    }

    return dp2[1][n - 1];

    // O(n^2)
}

int MCM_B_U(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        dp[i][i] = 0;

    for (int L = 2; L < n; L++)
    {
        for (int i = 1; i < n - L + 1; i++)
        {
            int j = i + L - 1;
            dp[i][j] = INF;

            for (int k = i; k <= j - 1; k++)
            {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + arr[i - 1] * arr[k] * arr[j]);
            }
        }
    }

    return dp[1][n - 1];
}

char c = 'A';

void print(int arr[], int i, int j)
{
    if (i == j)
    {
        // cout << c;
        cout << arr[c - 'A'] << "*" << arr[c + 1 - 'A'] << " ";
        c++;
        return;
    }

    cout << "(";

    print(arr, i, bracket[i][j]);

    print(arr, bracket[i][j] + 1, j);

    cout << ")";
}

int main(int argc, char const *argv[])
{
    int arr[] = {40, 20, 30, 10, 30};
    int n = sizeof(arr) / sizeof(arr[0]);
    // memset(dp, -1, sizeof dp);

    cout << MCM2(arr, n) << endl;
    cout << MCM_B_U(arr, n) << endl;

    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //     {
    //         cout << bracket[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    // print(arr, 1, n - 1);

    return 0;
}
