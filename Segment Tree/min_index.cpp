#include <iostream>
#include <climits>
using namespace std;

const int MAX_SIZE = 100000;

// Structure to store minimum value and its index
struct Node
{
    long long value;
    int index;
};

long long arr[MAX_SIZE];
Node tree[4 * MAX_SIZE];

int n;

// Create identity node for no overlap
Node emptyNode()
{
    Node result;

    result.value = LLONG_MAX;
    result.index = INT_MAX;

    return result;
}

// Merge two nodes
Node merge(Node leftNode, Node rightNode)
{
    if (leftNode.value < rightNode.value)
    {
        return leftNode;
    }

    if (rightNode.value < leftNode.value)
    {
        return rightNode;
    }

    // If values are equal, choose leftmost index
    if (leftNode.index < rightNode.index)
    {
        return leftNode;
    }

    return rightNode;
}

// Build Segment Tree
void build(int node, int left, int right)
{
    if (left == right)
    {
        tree[node].value = arr[left];
        tree[node].index = left;

        return;
    }

    int mid = left + (right - left) / 2;

    build(2 * node, left, mid);
    build(2 * node + 1, mid + 1, right);

    tree[node] = merge(tree[2 * node],
                       tree[2 * node + 1]);
}

// Range Minimum Query with Index
Node query(int node, int left, int right,
           int queryLeft, int queryRight)
{
    // Case 1: No Overlap
    if (right < queryLeft || left > queryRight)
    {
        return emptyNode();
    }

    // Case 2: Complete Overlap
    if (queryLeft <= left && right <= queryRight)
    {
        return tree[node];
    }

    // Case 3: Partial Overlap
    int mid = left + (right - left) / 2;

    Node leftResult = query(2 * node, left, mid,
                            queryLeft, queryRight);

    Node rightResult = query(2 * node + 1, mid + 1, right,
                             queryLeft, queryRight);

    return merge(leftResult, rightResult);
}

// Display query result
void displayResult(Node result, int L, int R)
{
    cout << "\nResults for range ["
         << L << ", " << R << "]\n";

    cout << "Minimum value = " << result.value << endl;
    cout << "Index         = " << result.index << endl;
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

        Node result = query(1, 0, n - 1, L, R);

        displayResult(result, L, R);
    }

    return 0;
}
