#include <iostream>
#include <algorithm>
using namespace std;

const int MAX_SIZE = 100000;

long long arr[MAX_SIZE];
long long values[MAX_SIZE];

int frequency[MAX_SIZE];
int tree[4 * MAX_SIZE];

int n;
int uniqueCount;

// Find the compressed index of a value using binary search
int findIndex(long long x)
{
    int left = 0;
    int right = uniqueCount - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (values[mid] == x)
        {
            return mid;
        }
        else if (values[mid] < x)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    return -1;
}

// Build the Frequency Segment Tree
void build(int node, int left, int right)
{
    if (left == right)
    {
        tree[node] = frequency[left];
        return;
    }

    int mid = left + (right - left) / 2;

    build(2 * node, left, mid);
    build(2 * node + 1, mid + 1, right);

    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

// Find the Kth smallest element
int kthSmallest(int node, int left, int right, int k)
{
    // Reached the leaf representing the answer
    if (left == right)
    {
        return left;
    }

    int mid = left + (right - left) / 2;

    // Frequency of elements in the left subtree
    int leftCount = tree[2 * node];

    if (k <= leftCount)
    {
        // Answer lies in the left subtree
        return kthSmallest(
            2 * node, left, mid, k
        );
    }
    else
    {
        // Skip left subtree and search the right subtree
        return kthSmallest(
            2 * node + 1, mid + 1, right,
            k - leftCount
        );
    }
}

int main()
{
    cout << "Enter number of elements: ";
    cin >> n;

    if (n <= 0 || n > MAX_SIZE)
    {
        cout << "Invalid array size!" << endl;
        return 0;
    }

    cout << "Enter array elements: ";

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];

        values[i] = arr[i];
    }

    // Sort values for coordinate compression
    sort(values, values + n);

    // Remove duplicate values
    uniqueCount = 0;

    for (int i = 0; i < n; i++)
    {
        if (i == 0 || values[i] != values[i - 1])
        {
            values[uniqueCount] = values[i];
            uniqueCount++;
        }
    }

    // Initialize frequencies
    for (int i = 0; i < uniqueCount; i++)
    {
        frequency[i] = 0;
    }

    // Calculate frequency of every distinct value
    for (int i = 0; i < n; i++)
    {
        int index = findIndex(arr[i]);

        frequency[index]++;
    }

    // Build the Frequency Segment Tree
    build(1, 0, uniqueCount - 1);

    int q;

    cout << "Enter number of queries: ";
    cin >> q;

    while (q--)
    {
        int k;

        cout << "Enter K: ";
        cin >> k;

        if (k < 1 || k > n)
        {
            cout << "Invalid K! Enter a value between 1 and "
                 << n << "." << endl;
            continue;
        }

        int index = kthSmallest(
            1, 0, uniqueCount - 1, k
        );

        cout << k << "th smallest element = "
             << values[index] << endl;
    }

    return 0;
}
