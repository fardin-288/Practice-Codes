#include <bits\stdc++.h>
using namespace std;

const int N = 1e3 + 10;
const int INF = 1e9 + 10;

class point
{
public:
    int x, y;
};

class pp
{
public:
    point a;
    point b;
    float dist = sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));

    pp();

    pp(point a, point b)
    {
        this->a = a;
        this->b = b;
    }
};

point res1;
point res2;
pp finalans;

bool compareX(point a, point b)
{
    if (a.x < b.x)
        return true;
    else
        return false;
}

bool compareY(point a, point b)
{
    if (a.y < b.y)
        return true;
    else
        return false;
}

float min(float x, float y)
{
    if (x < y)
        return x;
    else
        return y;
}

float dist(point a, point b)
{
    return (sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)));
}

float bruteForce(point p[], int n)
{
    float res = INF;

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            res = min(res, dist(p[i], p[j]));
        }
    }

    return res;
}

float stripClosest(point p[], int n, float d)
{
    float mini = d;

    sort(p, p + n, compareY);

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n && (p[j].y - p[i].y) < d; j++)
        {
            mini = min(mini, dist(p[i], p[j]));
        }
    }

    return mini;
}

float closestUtil(point p[], int n)
{

    if (n <= 3)
        return bruteForce(p, n);

    int mid = n / 2;
    point midPoint = p[mid];

    float dl = closestUtil(p, mid);
    float dr = closestUtil(p + mid, n - mid);

    float d = min(dl, dr);

    point strip[n];

    int j = 0;

    for (int i = 0; i < n; i++)
    {
        if (abs(p[i].x - midPoint.x) < d)
        {
            strip[j] = p[i];
            j++;
        }
    }

    return min(d, stripClosest(strip, j, d));
}

float closestPoint(point p[], int n)
{
    sort(p, p + n, compareX);
    return closestUtil(p, n);
}

int main(int argc, char const *argv[])
{
    point P[] = {{2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}};
    int n = sizeof(P) / sizeof(P[0]);

    cout << (float)closestPoint(P, n) << endl;

    return 0;
}
