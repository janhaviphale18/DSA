#include <iostream>
#include <algorithm>
using namespace std;

const int MAX_SIZE = 100000;

long long arr[MAX_SIZE];

int n;

// Each node stores four properties
struct Node
{
    long long sum;
    long long maxPrefix;
    long long maxSuffix;
    long long maxSubarray;
};

Node tree[4 * MAX_SIZE];

// Merge two child nodes
Node mergeNodes(Node leftNode, Node rightNode)
{
    Node result;

    // Total sum
    result.sum = leftNode.sum + rightNode.sum;

    // Maximum prefix sum
    result.maxPrefix = max(
        leftNode.maxPrefix,
        leftNode.sum + rightNode.maxPrefix
    );

    // Maximum suffix sum
    result.maxSuffix = max(
        rightNode.maxSuffix,
        rightNode.sum + leftNode.maxSuffix
    );

    // Maximum subarray sum
    result.maxSubarray = max(
        leftNode.maxSuffix + rightNode.maxPrefix,
        max(
            leftNode.maxSubarray,
            rightNode.maxSubarray
        )
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
        tree[node].maxSuffix = arr[left];
        tree[node].maxSubarray = arr[left];

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

// Return an identity node for no overlap
Node identityNode()
{
    Node result;

    result.sum = 0;
    result.maxPrefix = -1e18;
    result.maxSuffix = -1e18;
    result.maxSubarray = -1e18;

    return result;
}

// Query maximum subarray information in [queryLeft, queryRight]
Node query(int node, int left, int right,
           int queryLeft, int queryRight)
{
    // No overlap
    if (right < queryLeft || left > queryRight)
    {
        return identityNode();
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

    // Merge in left-to-right order
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

        cout << "Maximum subarray sum in range ["
             << L << ", " << R << "] = "
             << answer.maxSubarray << endl;

        cout << "Total sum = "
             << answer.sum << endl;

        cout << "Maximum prefix sum = "
             << answer.maxPrefix << endl;

        cout << "Maximum suffix sum = "
             << answer.maxSuffix << endl;
    }

    return 0;
}
