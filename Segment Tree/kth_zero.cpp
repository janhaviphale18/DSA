#include <iostream>
using namespace std;

const int MAX_SIZE = 100000;

int arr[MAX_SIZE];
int tree[4 * MAX_SIZE];

int n;

// Build a Segment Tree storing zero frequencies
void build(int node, int left, int right)
{
    if (left == right)
    {
        if (arr[left] == 0)
        {
            tree[node] = 1;
        }
        else
        {
            tree[node] = 0;
        }

        return;
    }

    int mid = left + (right - left) / 2;

    build(2 * node, left, mid);
    build(2 * node + 1, mid + 1, right);

    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

// Find the position of the Kth zero
int kthZero(int node, int left, int right, int k)
{
    // Reached the leaf representing the answer
    if (left == right)
    {
        return left;
    }

    int mid = left + (right - left) / 2;

    // Number of zeros in the left subtree
    int leftCount = tree[2 * node];

    if (k <= leftCount)
    {
        // Kth zero lies in the left subtree
        return kthZero(
            2 * node, left, mid, k
        );
    }
    else
    {
        // Skip left subtree and search right subtree
        return kthZero(
            2 * node + 1, mid + 1, right,
            k - leftCount
        );
    }
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

    // Build the zero-frequency Segment Tree
    build(1, 0, n - 1);

    int q;

    cout << "Enter number of queries: ";
    cin >> q;

    while (q--)
    {
        int k;

        cout << "Enter K: ";
        cin >> k;

        // Validate K
        if (k < 1 || k > tree[1])
        {
            cout << "Invalid K! Total zeros = "
                 << tree[1] << endl;
            continue;
        }

        int index = kthZero(1, 0, n - 1, k);

        cout << "Position of " << k
             << "th zero = " << index << endl;
    }

    return 0;
}
