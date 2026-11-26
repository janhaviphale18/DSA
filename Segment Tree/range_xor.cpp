#include <iostream>
using namespace std;

const int MAX_SIZE = 100000;

long long arr[MAX_SIZE];
long long tree[4 * MAX_SIZE];

int n;

// Build Segment Tree
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

    tree[node] = tree[2 * node] ^ tree[2 * node + 1];
}

// Range XOR Query
long long query(int node, int left, int right,
                int queryLeft, int queryRight)
{
    // Case 1: No Overlap
    if (right < queryLeft || left > queryRight)
    {
        return 0;
    }

    // Case 2: Complete Overlap
    if (queryLeft <= left && right <= queryRight)
    {
        return tree[node];
    }

    // Case 3: Partial Overlap
    int mid = left + (right - left) / 2;

    long long leftXOR = query(2 * node, left, mid,
                             queryLeft, queryRight);

    long long rightXOR = query(2 * node + 1, mid + 1, right,
                               queryLeft, queryRight);

    return leftXOR ^ rightXOR;
}

// Display Segment Tree
void displayTree(int totalNodes)
{
    cout << "\nSegment Tree Array:\n";

    for (int i = 1; i < totalNodes; i++)
    {
        cout << "Tree[" << i << "] = "
             << tree[i] << endl;
    }
}

int main()
{
    cout << "Enter number of elements: ";
    cin >> n;

    if (n <= 0 || n > MAX_SIZE)
    {
        cout << "Invalid array size.\n";
        return 0;
    }

    cout << "Enter array elements:\n";

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    build(1, 0, n - 1);

    cout << "\nSegment Tree constructed successfully.\n";

    displayTree(4 * n);

    int q;

    cout << "\nEnter number of queries: ";
    cin >> q;

    if (q < 0)
    {
        cout << "Invalid number of queries.\n";
        return 0;
    }

    for (int i = 0; i < q; i++)
    {
        int L, R;

        cout << "\nEnter query range (L R): ";
        cin >> L >> R;

        if (L < 0 || R >= n || L > R)
        {
            cout << "Invalid query range.\n";
            continue;
        }

        long long answer = query(1, 0, n - 1, L, R);

        cout << "XOR in range [" << L << ", " << R
             << "] = " << answer << endl;
    }

    return 0;
}
