#include <iostream>
using namespace std;

const int MAX_SIZE = 100000;

long long arr[MAX_SIZE];

long long tree[4 * MAX_SIZE];
long long lazy[4 * MAX_SIZE];

bool pending[4 * MAX_SIZE];

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

// Apply assignment to a complete segment
void applyAssignment(int node, int left, int right,
                     long long value)
{
    tree[node] = value * (right - left + 1);

    lazy[node] = value;
    pending[node] = true;
}

// Push pending assignment to children
void push(int node, int left, int right)
{
    if (!pending[node] || left == right)
    {
        return;
    }

    int mid = left + (right - left) / 2;

    long long value = lazy[node];

    // Assign value to left child
    applyAssignment(2 * node, left, mid, value);

    // Assign value to right child
    applyAssignment(2 * node + 1, mid + 1, right, value);

    // Clear parent's pending assignment
    pending[node] = false;
}

// Assign a value to a given range
void rangeAssign(int node, int left, int right,
                 int queryLeft, int queryRight,
                 long long value)
{
    // No overlap
    if (right < queryLeft || left > queryRight)
    {
        return;
    }

    // Complete overlap
    if (queryLeft <= left && right <= queryRight)
    {
        applyAssignment(node, left, right, value);
        return;
    }

    // Partial overlap
    push(node, left, right);

    int mid = left + (right - left) / 2;

    rangeAssign(2 * node, left, mid,
                queryLeft, queryRight, value);

    rangeAssign(2 * node + 1, mid + 1, right,
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

// Collect the final array values
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

    int operations;

    cout << "Enter the number of operations: ";
    cin >> operations;

    if (operations < 0)
    {
        cout << "Invalid number of operations." << endl;
        return 0;
    }

    cout << "\nOperation types:\n";
    cout << "1. Range Assignment\n";
    cout << "2. Range Sum Query\n";
    cout << "3. Display Final Array\n";

    for (int i = 0; i < operations; i++)
    {
        int type;

        cout << "\nEnter operation type: ";
        cin >> type;

        if (type == 1)
        {
            int left, right;
            long long value;

            cout << "Enter left and right indices: ";
            cin >> left >> right;

            cout << "Enter assignment value: ";
            cin >> value;

            if (left < 0 || right >= n || left > right)
            {
                cout << "Invalid range. Assignment skipped." << endl;
                continue;
            }

            rangeAssign(1, 0, n - 1,
                        left, right, value);

            cout << "Range assignment completed." << endl;
        }
        else if (type == 2)
        {
            int left, right;

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
        else if (type == 3)
        {
            collect(1, 0, n - 1);

            cout << "Current array: ";

            for (int j = 0; j < n; j++)
            {
                cout << arr[j] << " ";
            }

            cout << endl;
        }
        else
        {
            cout << "Invalid operation type." << endl;
        }
    }

    return 0;
}
