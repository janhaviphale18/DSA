#include <iostream>
using namespace std;

const int MAX_SIZE = 100000;

long long arr[MAX_SIZE];
long long tree[4 * MAX_SIZE];
long long lazy[4 * MAX_SIZE];

int n;

// Build the segment tree
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

// Push pending updates to children
void push(int node, int left, int right)
{
    if (lazy[node] == 0 || left == right)
    {
        return;
    }

    int mid = left + (right - left) / 2;

    long long pending = lazy[node];

    // Update left child
    tree[2 * node] += pending * (mid - left + 1);
    lazy[2 * node] += pending;

    // Update right child
    tree[2 * node + 1] += pending * (right - mid);
    lazy[2 * node + 1] += pending;

    // Clear the parent's pending update
    lazy[node] = 0;
}

// Add value to a given range
void rangeAdd(int node, int left, int right,
              int queryLeft, int queryRight, long long value)
{
    // No overlap
    if (right < queryLeft || left > queryRight)
    {
        return;
    }

    // Complete overlap
    if (queryLeft <= left && right <= queryRight)
    {
        tree[node] += value * (right - left + 1);
        lazy[node] += value;
        return;
    }

    // Partial overlap
    push(node, left, right);

    int mid = left + (right - left) / 2;

    rangeAdd(2 * node, left, mid,
             queryLeft, queryRight, value);

    rangeAdd(2 * node + 1, mid + 1, right,
             queryLeft, queryRight, value);

    // Recalculate parent
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

// Collect final values from leaf nodes
void collect(int node, int left, int right)
{
    if (left == right)
    {
        arr[left] = tree[node];
        return;
    }

    push(node, left, right);

    int mid = left + (right - left) / 2;

    collect(2 * node, left, mid);
    collect(2 * node + 1, mid + 1, right);
}

int main()
{
    cout << "Enter the number of elements: ";
    cin >> n;

    if (n <= 0 || n > MAX_SIZE)
    {
        cout << "Invalid array size." << endl;
        return 0;
    }

    cout << "Enter array elements: ";

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    // Build segment tree
    build(1, 0, n - 1);

    int updates;

    cout << "Enter the number of range updates: ";
    cin >> updates;

    if (updates < 0)
    {
        cout << "Invalid number of updates." << endl;
        return 0;
    }

    for (int i = 0; i < updates; i++)
    {
        int left, right;
        long long value;

        cout << "\nUpdate " << i + 1 << endl;

        cout << "Enter left and right indices: ";
        cin >> left >> right;

        cout << "Enter value to add: ";
        cin >> value;

        if (left < 0 || right >= n || left > right)
        {
            cout << "Invalid range. Update skipped." << endl;
            continue;
        }

        rangeAdd(1, 0, n - 1, left, right, value);

        cout << "Range update completed." << endl;
    }

    // Convert tree values into the final array
    collect(1, 0, n - 1);

    cout << "\nFinal updated array: ";

    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    cout << endl;

    return 0;
}
