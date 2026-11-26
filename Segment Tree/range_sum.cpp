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

// Function to calculate range sum
long long query(int node, int left, int right,
                int queryLeft, int queryRight)
{
    // Case 1: No overlap
    if (right < queryLeft || left > queryRight)
    {
        return 0;
    }

    // Case 2: Complete overlap
    if (queryLeft <= left && right <= queryRight)
    {
        return tree[node];
    }

    // Case 3: Partial overlap
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

    // Construct the Segment Tree
    build(1, 0, n - 1);

    cout << "\nSegment Tree Successfully Built!" << endl;

    cout << "Total Sum: " << tree[1] << endl;

    int q;

    cout << "\nEnter the number of queries: ";
    cin >> q;

    if (cin.fail() || q < 0)
    {
        cout << "Invalid number of queries." << endl;
        return 1;
    }

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

        cout << "Sum of range ["
             << queryLeft << ", "
             << queryRight << "] = "
             << result << endl;
    }

    return 0;
}
