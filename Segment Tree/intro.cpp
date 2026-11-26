#include <iostream>
using namespace std;

const int MAX_SIZE = 100000;

int arr[MAX_SIZE];
int tree[4 * MAX_SIZE];

int n;

// Recursively build the Segment Tree
void build(int node, int left, int right)
{
    // Base case: leaf node
    if (left == right)
    {
        tree[node] = arr[left];
        return;
    }

    // Find the midpoint
    int mid = left + (right - left) / 2;

    // Build the left subtree
    build(2 * node, left, mid);

    // Build the right subtree
    build(2 * node + 1, mid + 1, right);

    // Calculate the sum of the current interval
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

// Display all valid Segment Tree nodes
void display(int node, int left, int right)
{
    cout << "Node Index: " << node << endl;

    cout << "Interval: [" << left << ", "
         << right << "]" << endl;

    cout << "Sum: " << tree[node] << endl;

    if (left == right)
    {
        cout << "Left Child: None" << endl;
        cout << "Right Child: None" << endl;
    }
    else
    {
        cout << "Left Child Index: " << 2 * node << endl;
        cout << "Right Child Index: " << 2 * node + 1 << endl;
    }

    cout << "--------------------------" << endl;

    if (left == right)
    {
        return;
    }

    int mid = left + (right - left) / 2;

    display(2 * node, left, mid);
    display(2 * node + 1, mid + 1, right);
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

    cout << "\nSegment Tree Root Sum: "
         << tree[1] << endl;

    cout << "\nSegment Tree Structure" << endl;
    cout << "==========================" << endl;

    display(1, 0, n - 1);

    return 0;
}
