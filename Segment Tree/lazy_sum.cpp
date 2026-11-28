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

    // Clear parent's pending update
    lazy[node] = 0;
}

// Add a value to a given range
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

// Find sum of a given range
long long rangeSum(int node, int left, int right,
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

    // Partial overlap
    push(node, left, right);

    int mid = left + (right - left) / 2;

    long long leftSum = rangeSum(
        2 * node, left, mid, queryLeft, queryRight
    );

    long long rightSum = rangeSum(
        2 * node + 1, mid + 1, right,
        queryLeft, queryRight
    );

    return leftSum + rightSum;
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

    // Build the tree
    build(1, 0, n - 1);

    int operations;

    cout << "Enter the number of operations: ";
    cin >> operations;

    if (operations < 0)
    {
        cout << "Invalid number of operations." << endl;
        return 0;
    }

    cout << "\nOperation types:\n";
    cout << "1. Range Addition\n";
    cout << "2. Range Sum Query\n";

    for (int i = 0; i < operations; i++)
    {
        int type;

        cout << "\nEnter operation type: ";
        cin >> type;

        int left, right;

        if (type == 1)
        {
            long long value;

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

            cout << "Range addition completed." << endl;
        }
        else if (type == 2)
        {
            cout << "Enter left and right indices: ";
            cin >> left >> right;

            if (left < 0 || right >= n || left > right)
            {
                cout << "Invalid range. Query skipped." << endl;
                continue;
            }

            long long result = rangeSum(
                1, 0, n - 1, left, right
            );

            cout << "Range sum: " << result << endl;
        }
        else
        {
            cout << "Invalid operation type." << endl;
        }
    }

    return 0;
}
