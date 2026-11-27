#include <iostream>
#include <algorithm>
using namespace std;

const int MAX_SIZE = 100000;

long long arr[MAX_SIZE];
long long tree[4 * MAX_SIZE];

int n;

// Build Maximum Segment Tree
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

    tree[node] = max(tree[2 * node],
                     tree[2 * node + 1]);
}

// Find First Element Greater Than X
int firstGreater(int node, int left, int right,
                 int queryLeft, int queryRight,
                 long long x)
{
    // Condition 1: No Overlap
    if (right < queryLeft || left > queryRight)
    {
        return -1;
    }

    // Condition 2: Maximum is not greater than X
    if (tree[node] <= x)
    {
        return -1;
    }

    // Condition 3: Leaf node found
    if (left == right)
    {
        return left;
    }

    int mid = left + (right - left) / 2;

    // Search left child first
    int leftResult = firstGreater(2 * node, left, mid,
                                  queryLeft, queryRight, x);

    if (leftResult != -1)
    {
        return leftResult;
    }

    // Search right child if left child has no answer
    return firstGreater(2 * node + 1, mid + 1, right,
                        queryLeft, queryRight, x);
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

    cout << "\nMaximum Segment Tree constructed successfully.\n";

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
        long long x;

        cout << "\nEnter L, R and X: ";
        cin >> L >> R >> x;

        if (L < 0 || R >= n || L > R)
        {
            cout << "Invalid query range.\n";
            continue;
        }

        int answer = firstGreater(1, 0, n - 1,
                                  L, R, x);

        if (answer == -1)
        {
            cout << "No element greater than "
                 << x << " found in the given range.\n";
        }
        else
        {
            cout << "First element greater than "
                 << x << " = " << arr[answer] << endl;

            cout << "Index = " << answer << endl;
        }
    }

    return 0;
}
