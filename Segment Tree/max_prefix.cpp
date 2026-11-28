#include <iostream>
#include <algorithm>
using namespace std;

const int MAX_SIZE = 100000;

long long arr[MAX_SIZE];

int n;

// Each Segment Tree node stores two values
struct Node
{
    long long sum;
    long long maxPrefix;
};

Node tree[4 * MAX_SIZE];

// Merge two child nodes
Node mergeNodes(Node leftNode, Node rightNode)
{
    Node result;

    result.sum = leftNode.sum + rightNode.sum;

    result.maxPrefix = max(
        leftNode.maxPrefix,
        leftNode.sum + rightNode.maxPrefix
    );

    return result;
}

// Build the Segment Tree
void build(int node, int left, int right)
{
    if (left == right)
    {
        tree[node].sum = arr[left];
        tree[node].maxPrefix = arr[left];

        return;
    }

    int mid = left + (right - left) / 2;

    build(2 * node, left, mid);
    build(2 * node + 1, mid + 1, right);

    tree[node] = mergeNodes(
        tree[2 * node],
        tree[2 * node + 1]
    );
}

// Query maximum prefix sum in [queryLeft, queryRight]
Node query(int node, int left, int right,
           int queryLeft, int queryRight)
{
    // No overlap
    if (right < queryLeft || left > queryRight)
    {
        Node emptyNode;

        emptyNode.sum = 0;
        emptyNode.maxPrefix = -1e18;

        return emptyNode;
    }

    // Complete overlap
    if (queryLeft <= left && right <= queryRight)
    {
        return tree[node];
    }

    int mid = left + (right - left) / 2;

    Node leftResult = query(
        2 * node, left, mid,
        queryLeft, queryRight
    );

    Node rightResult = query(
        2 * node + 1, mid + 1, right,
        queryLeft, queryRight
    );

    // Preserve left-to-right order
    return mergeNodes(leftResult, rightResult);
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

    cout << "Enter number of queries: ";
    cin >> q;

    while (q--)
    {
        int L, R;

        cout << "Enter range L and R: ";
        cin >> L >> R;

        if (L < 0 || R >= n || L > R)
        {
            cout << "Invalid query range!" << endl;
            continue;
        }

        Node answer = query(
            1, 0, n - 1, L, R
        );

        cout << "Maximum prefix sum in range ["
             << L << ", " << R << "] = "
             << answer.maxPrefix << endl;

        cout << "Total sum of range = "
             << answer.sum << endl;
    }

    return 0;
}
