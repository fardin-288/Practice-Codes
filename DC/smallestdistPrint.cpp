#include <bits/stdc++.h>
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
    float dist;

    pp()
    {
        dist = 0.0;
    }

    pp(point a, point b)
    {
        this->a = a;
        this->b = b;
        dist = sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    }
};

pp min(pp a, pp b)
{
    if (a.dist < b.dist)
        return a;
    else
        return b;
}

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

float dist(point a, point b)
{
    return (sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)));
}

pp closestPoint(point p[], int n);
pp stripClosest(point p[], int n, float d);
pp closestUtil(point p[], int n);

pp bruteForce(point p[], int n)
{
    float res = INF;
    pp resp;

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (dist(p[i], p[j]) < res)
            {
                resp = pp(p[i], p[j]);
                res = dist(p[i], p[j]);
            }
        }
    }

    return resp;
}

pp closestUtil(point p[], int n)
{
    sort(p, p + n, compareX);

    if (n <= 3)
    {
        return bruteForce(p, n);
    }

    int mid = n / 2;
    point midPoint = p[mid];

    pp dl = closestUtil(p, mid);
    pp dr = closestUtil(p + mid, n - mid);

    pp d = min(dl, dr);

    point strip[n];
    int j = 0;

    for (int i = 0; i < n; i++)
    {
        if (abs(p[i].x - midPoint.x) < d.dist)
        {
            strip[j] = p[i];
            j++;
        }
    }

    return min(d, stripClosest(strip, j, d.dist));
};

pp closestPoint(point p[], int n)
{
    sort(p, p + n, compareX);
    return closestUtil(p, n);
}

pp stripClosest(point p[], int n, float d)
{
    pp mini = pp();
    mini.dist = INF;

    sort(p, p + n, compareY);

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n && (p[j].y - p[i].y) < d; j++)
        {
            if (dist(p[i], p[j]) < d)

                mini = min(mini, pp(p[i], p[j]));
        }
    }

    return mini;
}

int main(int argc, char const *argv[])
{
    point P[] = {{2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}};
    int n = sizeof(P) / sizeof(P[0]);

    pp closest = closestPoint(P, n);
    cout << "Closest pair of points: (" << closest.a.x << ", " << closest.a.y << ") and (" << closest.b.x << ", " << closest.b.y << ")" << endl;

    return 0;
}
