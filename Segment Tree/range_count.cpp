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

// Find the first index where values[index] >= x
int lowerBound(long long x)
{
    int left = 0;
    int right = uniqueCount;

    while (left < right)
    {
        int mid = left + (right - left) / 2;

        if (values[mid] < x)
        {
            left = mid + 1;
        }
        else
        {
            right = mid;
        }
    }

    return left;
}

// Find the first index where values[index] > x
int upperBound(long long x)
{
    int left = 0;
    int right = uniqueCount;

    while (left < right)
    {
        int mid = left + (right - left) / 2;

        if (values[mid] <= x)
        {
            left = mid + 1;
        }
        else
        {
            right = mid;
        }
    }

    return left;
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

// Calculate frequency sum in a compressed index range
int rangeSum(int node, int left, int right,
             int queryLeft, int queryRight)
{
    // No overlap
    if (right < queryLeft || left > queryRight)
    {
        return 0;
    }

    // Complete overlap
    if (queryLeft <= left && right <= queryRight)
    {
        return tree[node];
    }

    int mid = left + (right - left) / 2;

    int leftSum = rangeSum(
        2 * node, left, mid,
        queryLeft, queryRight
    );

    int rightSum = rangeSum(
        2 * node + 1, mid + 1, right,
        queryLeft, queryRight
    );

    return leftSum + rightSum;
}

// Count elements whose values lie in [L, R]
int countInRange(long long L, long long R)
{
    if (L > R)
    {
        return 0;
    }

    // First compressed position with value >= L
    int leftIndex = lowerBound(L);

    // First compressed position with value > R
    int rightIndex = upperBound(R) - 1;

    // No compressed values exist in this interval
    if (leftIndex > rightIndex)
    {
        return 0;
    }

    return rangeSum(
        1, 0, uniqueCount - 1,
        leftIndex, rightIndex
    );
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

    // Calculate frequency of each distinct value
    for (int i = 0; i < n; i++)
    {
        int index = lowerBound(arr[i]);
        frequency[index]++;
    }

    // Build the Frequency Segment Tree
    build(1, 0, uniqueCount - 1);

    int q;

    cout << "Enter number of queries: ";
    cin >> q;

    while (q--)
    {
        long long L, R;

        cout << "Enter range L and R: ";
        cin >> L >> R;

        if (L > R)
        {
            cout << "Invalid value range!" << endl;
            continue;
        }

        int answer = countInRange(L, R);

        cout << "Number of elements in range ["
             << L << ", " << R << "] = "
             << answer << endl;
    }

    return 0;
}
