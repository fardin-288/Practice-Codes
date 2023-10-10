#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 10;
const int INF = 1e9 + 10;

int merge(int arr[], int left, int right, int mid)
{
    int temp[N];

    int i = left;
    int j = mid;
    int k = left;

    int inv = 0;

    while (i < mid and j <= right)
    {
        if (arr[i] <= arr[j])
        {
            temp[k] = arr[i];
            k++;
            i++;
        }
        else
        {
            temp[k] = arr[j];
            k++;
            j++;
            inv += mid - i;
        }
    }

    while (i < mid)
    {
        temp[k] = arr[i];
        k++;
        i++;
    }

    while (j <= right)
    {
        temp[k] = arr[j];
        k++;
        j++;
    }

    for (int i = left; i <= right; i++)
    {
        arr[i] = temp[i];
    }

    return inv;
}

int mergseSort(int arr[], int left, int right)
{
    int inversion = 0;

    if (left < right)
    {
        int mid = (left + right) / 2;

        inversion += mergseSort(arr, left, mid);
        inversion += mergseSort(arr, mid + 1, right);

        inversion += merge(arr, left, right, mid + 1);
    }

    return inversion;
}

int main(int argc, char const *argv[])
{
    int arr[] = {1, 20, 6, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    cout << "inversions " << mergseSort(arr, 0, n - 1) << endl;

    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    return 0;
}
