#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// O(N^2)
// Expected O(N)

int partition(int arr[], int low, int high)
{
    int pivot_element = arr[high];
    int j = low;
    for (int i = low; i <= high - 1; i++)
    {
        if (arr[i] <= pivot_element)
        {
            swap(arr[j], arr[i]);
            j++;
        }
    }
    swap(arr[j], arr[high]);
    int pivot_pos = j;
    return pivot_pos;
}

int kthSmallestElement(int arr[], int low, int high, int k)
{
    if (low == high)
        return arr[low];

    int pivot_pos = partition(arr, low, high);
    int i = pivot_pos - low + 1;

    if (i == k)
        return arr[pivot_pos];
    else if (i > k)
        return kthSmallestElement(arr, low, pivot_pos - 1, k);
    else
        kthSmallestElement(arr, pivot_pos + 1, high, k);
}

int main()
{

    int arr[] = {10, 7, 2, 15, 4};
    int n = sizeof(arr) / sizeof(arr[0]);

    int k = 2;

    cout << kthSmallestElement(arr, 0, n - 1, k);

    return 0;
}
