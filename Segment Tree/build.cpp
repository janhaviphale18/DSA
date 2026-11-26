#include <iostream>
using namespace std;

const int MAX_SIZE = 100000;

long long arr[MAX_SIZE];
long long tree[4 * MAX_SIZE];

int n;

// Function to build the Segment Tree
void build(int node, int left, int right)
{
    // Base case: interval contains one element
    if (left == right)
    {
        tree[node] = arr[left];
        return;
    }

    // Calculate the midpoint
    int mid = left + (right - left) / 2;

    // Recursively build the left subtree
    build(2 * node, left, mid);

    // Recursively build the right subtree
    build(2 * node + 1, mid + 1, right);

    // Merge the results of both children
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

// Function to display the constructed tree
void display(int node, int left, int right)
{
    cout << "Node: " << node << endl;
    cout << "Interval: [" << left << ", " << right << "]" << endl;
    cout << "Sum: " << tree[node] << endl;

    if (left == right)
    {
        cout << "Leaf Node" << endl;
    }
    else
    {
        cout << "Left Child: " << 2 * node << endl;
        cout << "Right Child: " << 2 * node + 1 << endl;
    }

    cout << "-----------------------------" << endl;

    // Stop at leaf nodes
    if (left == right)
    {
        return;
    }

    int mid = left + (right - left) / 2;

    // Display left and right subtrees
    display(2 * node, left, mid);
    display(2 * node + 1, mid + 1, right);
}

int main()
{
    cout << "Enter the number of elements: ";
    cin >> n;

    // Validate array size
    if (cin.fail() || n <= 0 || n > MAX_SIZE)
    {
        cout << "Invalid array size." << endl;
        return 1;
    }

    cout << "Enter " << n << " elements:" << endl;

    // Accept array elements
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];

        if (cin.fail())
        {
            cout << "Invalid array element." << endl;
            return 1;
        }
    }

    // Build the Segment Tree
    build(1, 0, n - 1);

    cout << "\nSegment Tree Successfully Built!" << endl;

    cout << "Total Sum of Array: " << tree[1] << endl;

    cout << "\nComplete Segment Tree Structure" << endl;
    cout << "=============================" << endl;

    // Display the complete tree
    display(1, 0, n - 1);

    return 0;
}
