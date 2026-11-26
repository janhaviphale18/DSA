#include <iostream>
using namespace std;

const int MAX_SIZE = 100000;

long long arr[MAX_SIZE];
long long tree[4 * MAX_SIZE];

int n;

// Function to build the Segment Tree
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

// Function to update one array element
void update(int node, int left, int right,
            int index, long long newValue)
{
    // Base case: target leaf node found
    if (left == right)
    {
        tree[node] = newValue;
        return;
    }

    int mid = left + (right - left) / 2;

    // Find the subtree containing the target index
    if (index <= mid)
    {
        update(2 * node, left, mid, index, newValue);
    }
    else
    {
        update(2 * node + 1, mid + 1, right, index, newValue);
    }

    // Recalculate the current node
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

// Function to calculate range sum
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

    // Partial overlap
    int mid = left + (right - left) / 2;

    long long leftSum = query(
        2 * node,
        left,
        mid,
        queryLeft,
        queryRight
    );

    long long rightSum = query(
        2 * node + 1,
        mid + 1,
        right,
        queryLeft,
        queryRight
    );

    return leftSum + rightSum;
}

// Function to display the original array
void displayArray()
{
    cout << "Current Array: ";

    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    cout << endl;
}

// Function to display the Segment Tree
void displayTree(int node, int left, int right)
{
    cout << "Node: " << node
         << " | Interval: [" << left << ", " << right << "]"
         << " | Sum: " << tree[node] << endl;

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

    // Build the initial Segment Tree
    build(1, 0, n - 1);

    cout << "\nInitial Segment Tree Built!" << endl;

    displayArray();

    cout << "Initial Total Sum: " << tree[1] << endl;

    int q;

    cout << "\nEnter the number of updates: ";
    cin >> q;

    if (cin.fail() || q < 0)
    {
        cout << "Invalid number of updates." << endl;
        return 1;
    }

    // Process all updates
    for (int i = 1; i <= q; i++)
    {
        int index;
        long long newValue;

        cout << "\nEnter index and new value for Update "
             << i << ": ";

        cin >> index >> newValue;

        if (cin.fail() || index < 0 || index >= n)
        {
            cout << "Invalid update index or value." << endl;
            return 1;
        }

        // Update the original array
        arr[index] = newValue;

        // Update the Segment Tree
        update(1, 0, n - 1, index, newValue);

        cout << "\nUpdate " << i << " Successful!" << endl;

        displayArray();

        cout << "Updated Total Sum: " << tree[1] << endl;
    }

    // Display final tree structure
    cout << "\nFinal Segment Tree Structure" << endl;
    cout << "============================" << endl;

    displayTree(1, 0, n - 1);

    // Allow range-sum queries after all updates
    int queryCount;

    cout << "\nEnter the number of range queries: ";
    cin >> queryCount;

    if (cin.fail() || queryCount < 0)
    {
        cout << "Invalid number of queries." << endl;
        return 1;
    }

    for (int i = 1; i <= queryCount; i++)
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

        cout << "Range Sum [" << queryLeft
             << ", " << queryRight
             << "] = " << result << endl;
    }

    return 0;
}
