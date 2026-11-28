#include <iostream>
using namespace std;

const int MAX_SIZE = 100000;

long long arr[MAX_SIZE];
long long tree[4 * MAX_SIZE];

int n;

// Build a Sum Segment Tree
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

    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

// Find the first prefix whose sum is at least X
int firstPrefix(int node, int left, int right, long long x)
{
    // Reached the answer
    if (left == right)
    {
        return left;
    }

    int mid = left + (right - left) / 2;

    // Sum of the left subtree
    long long leftSum = tree[2 * node];

    if (leftSum >= x)
    {
        // Answer lies in the left subtree
        return firstPrefix(
            2 * node, left, mid, x
        );
    }
    else
    {
        // Skip left subtree and search right subtree
        return firstPrefix(
            2 * node + 1, mid + 1, right,
            x - leftSum
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

    cout << "Enter non-negative array elements: ";

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];

        if (arr[i] < 0)
        {
            cout << "Negative elements are not supported!"
                 << endl;
            return 0;
        }
    }

    // Build the Sum Segment Tree
    build(1, 0, n - 1);

    int q;

    cout << "Enter number of queries: ";
    cin >> q;

    while (q--)
    {
        long long x;

        cout << "Enter target X: ";
        cin >> x;

        if (x <= 0)
        {
            cout << "First qualifying prefix index = 0"
                 << endl;
            continue;
        }

        if (tree[1] < x)
        {
            cout << "No prefix has sum at least "
                 << x << "." << endl;
            continue;
        }

        int index = firstPrefix(1, 0, n - 1, x);

        cout << "First prefix with sum at least "
             << x << " is at index " << index << endl;

        cout << "Prefix sum = ";

        long long prefixSum = 0;

        for (int i = 0; i <= index; i++)
        {
            prefixSum += arr[i];
        }

        cout << prefixSum << endl;
    }

    return 0;
}
