#include <iostream>
#include <algorithm>
using namespace std;

const int MAX_SIZE = 100000;

long long arr[MAX_SIZE];
long long tree[4 * MAX_SIZE];

int n;

// Build a Maximum Segment Tree
void build(int node, int left, int right)
{
    if (left == right)
    {
        tree[node] = arr[left];
        return;
    }

    int mid = left + (right - left) / 2;

    build(2 * node, left, mid);
    build(2 * node + 1, mid + 1, right);

    tree[node] = max(tree[2 * node], tree[2 * node + 1]);
}

// Find the first element greater than or equal to X
int firstAtLeast(int node, int left, int right,
                 int queryLeft, int queryRight, long long x)
{
    // No overlap with the query range
    if (right < queryLeft || left > queryRight)
    {
        return -1;
    }

    // No element in this segment can be >= X
    if (tree[node] < x)
    {
        return -1;
    }

    // Found a qualifying element
    if (left == right)
    {
        return left;
    }

    int mid = left + (right - left) / 2;

    // Search the left child first
    int leftResult = firstAtLeast(
        2 * node, left, mid,
        queryLeft, queryRight, x
    );

    if (leftResult != -1)
    {
        return leftResult;
    }

    // If not found on the left, search the right child
    return firstAtLeast(
        2 * node + 1, mid + 1, right,
        queryLeft, queryRight, x
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
    }

    build(1, 0, n - 1);

    int q;

    cout << "Enter number of queries: ";
    cin >> q;

    while (q--)
    {
        int L, R;
        long long X;

        cout << "Enter L, R and X: ";
        cin >> L >> R >> X;

        if (L < 0 || R >= n || L > R)
        {
            cout << "Invalid query range!" << endl;
            continue;
        }

        int index = firstAtLeast(1, 0, n - 1, L, R, X);

        if (index == -1)
        {
            cout << "No element greater than or equal to "
                 << X << " found in the given range." << endl;
        }
        else
        {
            cout << "First element greater than or equal to "
                 << X << " = " << arr[index] << endl;

            cout << "Index = " << index << endl;
        }
    }

    return 0;
}
