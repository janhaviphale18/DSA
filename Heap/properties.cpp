
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int arr[] = {40, 20, 60, 10, 30, 50, 70};

    int n = 7;

    int leaf = 0;
    int internal = 0;

    cout << "Complete Binary Tree Properties\n\n";

    cout << "Tree Elements: ";

    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    cout << "\n\n";

    // Count leaf and internal nodes
    for (int i = 0; i < n; i++)
    {
        int left = 2 * i + 1;

        if (left < n)
        {
            internal++;
        }
        else
        {
            leaf++;
        }
    }

    // Calculate height
    int height = log2(n);

    cout << "Total Nodes: " << n << endl;

    cout << "Leaf Nodes: " << leaf << endl;

    cout << "Internal Nodes: " << internal << endl;

    cout << "Height of Tree: " << height << endl;

    cout << "\nComplete Binary Tree Property:\n";

    cout << "All levels except possibly the last are full.\n";
    cout << "The last level is filled from left to right.\n";

    return 0;
}
