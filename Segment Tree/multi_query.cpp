#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

const int MAX_SIZE = 100000;

// Structure for storing multiple operations
struct Node
{
    long long sum;
    long long minimum;
    long long maximum;
    long long gcd;
    long long xorValue;
};

long long arr[MAX_SIZE];
Node tree[4 * MAX_SIZE];

int n;

// Find GCD using Euclidean Algorithm
long long findGCD(long long a, long long b)
{
    while (b != 0)
    {
        long long temp = b;
        b = a % b;
        a = temp;
    }

    return (a < 0) ? -a : a;
}

// Create an identity node for no overlap
Node emptyNode()
{
    Node result;

    result.sum = 0;
    result.minimum = LLONG_MAX;
    result.maximum = LLONG_MIN;
    result.gcd = 0;
    result.xorValue = 0;

    return result;
}

// Merge two nodes
Node merge(Node leftNode, Node rightNode)
{
    Node result;

    result.sum = leftNode.sum + rightNode.sum;

    result.minimum = min(leftNode.minimum,
                         rightNode.minimum);

    result.maximum = max(leftNode.maximum,
                         rightNode.maximum);

    result.gcd = findGCD(leftNode.gcd,
                         rightNode.gcd);

    result.xorValue = leftNode.xorValue ^
                      rightNode.xorValue;

    return result;
}

// Build Segment Tree
void build(int node, int left, int right)
{
    if (left == right)
    {
        tree[node].sum = arr[left];
        tree[node].minimum = arr[left];
        tree[node].maximum = arr[left];
        tree[node].gcd = arr[left];
        tree[node].xorValue = arr[left];

        return;
    }

    int mid = left + (right - left) / 2;

    build(2 * node, left, mid);
    build(2 * node + 1, mid + 1, right);

    tree[node] = merge(tree[2 * node],
                       tree[2 * node + 1]);
}

// Combined Range Query
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

// Display Query Results
void displayResult(Node result, int L, int R)
{
    cout << "\nResults for range ["
         << L << ", " << R << "]\n";

    cout << "Sum     = " << result.sum << endl;
    cout << "Minimum = " << result.minimum << endl;
    cout << "Maximum = " << result.maximum << endl;
    cout << "GCD     = " << result.gcd << endl;
    cout << "XOR     = " << result.xorValue << endl;
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

    cout << "Enter non-negative array elements:\n";

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];

        if (arr[i] < 0)
        {
            cout << "Please enter non-negative elements.\n";
            return 0;
        }
    }

    build(1, 0, n - 1);

    cout << "\nCombined Segment Tree constructed successfully.\n";

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
