#include <iostream>
using namespace std;

const int MAX_SIZE = 100000;

long long arr[MAX_SIZE];
long long tree[4 * MAX_SIZE];
long long lazy[4 * MAX_SIZE];

int n;

// Build the Segment Tree
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

// Apply pending updates to children
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

// Add X to every element in range [queryLeft, queryRight]
void update(int node, int left, int right,
            int queryLeft, int queryRight, long long x)
{
    // No overlap
    if (right < queryLeft || left > queryRight)
    {
        return;
    }

    // Complete overlap
    if (queryLeft <= left && right <= queryRight)
    {
        tree[node] += x * (right - left + 1);
        lazy[node] += x;
        return;
    }

    // Apply pending updates before accessing children
    push(node, left, right);

    int mid = left + (right - left) / 2;

    update(
        2 * node, left, mid,
        queryLeft, queryRight, x
    );

    update(
        2 * node + 1, mid + 1, right,
        queryLeft, queryRight, x
    );

    // Recalculate the parent sum
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

// Find sum in range [queryLeft, queryRight]
long long query(int node, int left, int right,
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

    // Apply pending updates before accessing children
    push(node, left, right);

    int mid = left + (right - left) / 2;

    long long leftSum = query(
        2 * node, left, mid,
        queryLeft, queryRight
    );

    long long rightSum = query(
        2 * node + 1, mid + 1, right,
        queryLeft, queryRight
    );

    return leftSum + rightSum;
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

    // Build the Segment Tree
    build(1, 0, n - 1);

    int q;

    cout << "Enter number of operations: ";
    cin >> q;

    while (q--)
    {
        int type;

        cout << "Enter operation type (1 = Update, 2 = Query): ";
        cin >> type;

        int L, R;

        cout << "Enter range L and R: ";
        cin >> L >> R;

        if (L < 0 || R >= n || L > R)
        {
            cout << "Invalid range!" << endl;
            continue;
        }

        if (type == 1)
        {
            long long x;

            cout << "Enter value to add: ";
            cin >> x;

            update(1, 0, n - 1, L, R, x);

            cout << "Range updated successfully." << endl;
        }
        else if (type == 2)
        {
            long long answer = query(
                1, 0, n - 1, L, R
            );

            cout << "Range sum = " << answer << endl;
        }
        else
        {
            cout << "Invalid operation type!" << endl;
        }
    }

    return 0;
}
