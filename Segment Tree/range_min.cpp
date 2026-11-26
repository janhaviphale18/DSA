#include <iostream>
#include <climits>
using namespace std;

const int MAX_SIZE = 100000;

long long arr[MAX_SIZE];
long long tree[4 * MAX_SIZE];

int n;

// Function to build the Minimum Segment Tree
void build(int node, int left, int right)
{
    // Base case: leaf node
    if (left == right)
    {
        tree[node] = arr[left];
        return;
    }

    int mid = left + (right - left) / 2;

    // Build left and right subtrees
    build(2 * node, left, mid);
    build(2 * node + 1, mid + 1, right);

    // Store minimum of both children
    tree[node] = min(tree[2 * node],
                     tree[2 * node + 1]);
}

// Function to find minimum in a given range
long long query(int node, int left, int right,
                int queryLeft, int queryRight)
{
    // Case 1: No overlap
    if (right < queryLeft || left > queryRight)
    {
        return LLONG_MAX;
    }

    // Case 2: Complete overlap
    if (queryLeft <= left && right <= queryRight)
    {
        return tree[node];
    }

    // Case 3: Partial overlap
    int mid = left + (right - left) / 2;

    long long leftMin = query(
        2 * node,
        left,
        mid,
        queryLeft,
        queryRight
    );

    long long rightMin = query(
        2 * node + 1,
        mid + 1,
        right,
        queryLeft,
        queryRight
    );

    // Return minimum of both results
    return min(leftMin, rightMin);
}

// Function to display the Segment Tree
void displayTree(int node, int left, int right)
{
    cout << "Node: " << node
         << " | Interval: [" << left << ", "
         << right << "]"
         << " | Minimum: " << tree[node] << endl;

    if (left == right)
    {
        return;
    }

    int mid = left + (right - left) / 2;

    displayTree(2 * node, left, mid);
    displayTree(2 * node + 1, mid + 1, right);
}

int main()
{
    cout << "Enter the number of elements: ";
    cin >> n;

    if (cin.fail() || n <= 0 || n > MAX_SIZE)
    {
        cout << "Invalid array size." << endl;
        return 1;
    }

    cout << "Enter " << n << " elements:" << endl;

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];

        if (cin.fail())
        {
            cout << "Invalid array element." << endl;
            return 1;
        }
    }

    // Construct the Minimum Segment Tree
    build(1, 0, n - 1);

    cout << "\nMinimum Segment Tree Successfully Built!" << endl;

    cout << "Minimum of Entire Array: " << tree[1] << endl;

    // Display the complete tree
    cout << "\nSegment Tree Structure" << endl;
    cout << "============================" << endl;

    displayTree(1, 0, n - 1);

    int q;

    cout << "\nEnter the number of queries: ";
    cin >> q;

    if (cin.fail() || q < 0)
    {
        cout << "Invalid number of queries." << endl;
        return 1;
    }

    // Process range minimum queries
    for (int i = 1; i <= q; i++)
    {
        int queryLeft, queryRight;

        cout << "\nEnter range for Query " << i << ": ";
        cin >> queryLeft >> queryRight;

        if (cin.fail() ||
            queryLeft < 0 ||
            queryRight >= n ||
            queryLeft > queryRight)
        {
            cout << "Invalid query range." << endl;
            return 1;
        }

        long long result = query(
            1,
            0,
            n - 1,
            queryLeft,
            queryRight
        );

        cout << "Minimum in range ["
             << queryLeft << ", "
             << queryRight << "] = "
             << result << endl;
    }

    return 0;
}
