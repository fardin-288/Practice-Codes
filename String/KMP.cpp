#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
int lps[N];

void genLPS(string arr)
{
    int i = 1;
    int j = 0;

    lps[0] = 0;

    while (i < arr.length())
    {
        if (arr[i] == arr[j])
        {
            lps[i] = j + 1;
            j++;
            i++;
        }
        else if (j > 0)
        {
            j = lps[j - 1];
        }
        else
        {
            lps[i] = 0;
            i++;
        }
    }
}

int KMP(string given, string pattern)
{
    genLPS(pattern);
    int i = 0;
    int j = 0;
    int res = 0;

    while (i < given.length())
    {
        if (given[i] == pattern[j])
        {
            i++;
            j++;
        }
        else if (j > 0)
        {
            j = lps[j - 1];
        }
        else
        {
            i++;
        }

        if (j == pattern.length())
        {
            res++;
            // cout << "Pattern found at index: " << i - j << endl;
            for (int z = 0; z < given.length(); z++)
            {
                if (z >= i - j and z < i - j + pattern.length())
                {
                    char a = given[z] - 'a' + 'A';
                    cout << a;
                }
                else
                {
                    cout << given[z];
                }
            }
            cout << endl;
            j = 0;
        }
    }

    if (res == 0)
    {
        cout << "Pattern not found" << endl;
    }
    return res;
}

int main(int argc, char const *argv[])
{
    string given = "abababdcabababd";
    string pattern = "ababd";

    KMP(given, pattern);

    return 0;
}
