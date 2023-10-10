#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

ll power(ll x, ll y, ll m)
{
    ll res = 1;
    x %= m;

    while (y > 0)
    {

        if (y & 1)
        {
            res = (res * x) % m;
        }

        x = (x * x) % m;
        y = y / 2;
    }

    return res;
}

ll turn(string a, ll m)
{
    int res = 0;

    for (int i = 0; i < a.length(); i++)
    {
        res = (res * 10 + a[i] - '0') % m;
    }
    return res;
}

ll powerDC(ll x, ll y, ll m)
{
    if (y == 0)
        return 1;

    ll result;

    if (y % 2 == 1)
    {
        result = x % m;
        result = x * powerDC(x, y - 1, m);
    }
    else
    {
        result = powerDC(x, y / 2, m);
        result = ((result % m) * (result % m)) % m;
    }

    return result;
}

int main()
{
    int x = 13;
    // int y = 90;
    int m = 17;
    string b = "100000000000000000000000000";
    ll y = turn(b, m);
    cout << power(x, y, m) << endl;
    ;
    cout << powerDC(x, y, m) << endl;
    return 0;
    return 0;
}
