
#include <iostream>
using namespace std;

int main()
{
    int arr[] = {40, 20, 60, 10, 30, 50, 70};

    int n = 7;

    cout << "Array Representation of Binary Tree:\n";

    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    cout << "\n\nNode Relationships:\n";

    for (int i = 0; i < n; i++)
    {
        cout << "\nNode: " << arr[i];

        // Find parent
        if (i == 0)
        {
            cout << "\nParent: None";
        }
        else
        {
            int parent = (i - 1) / 2;
            cout << "\nParent: " << arr[parent];
        }

        // Find left child
        int left = 2 * i + 1;

        if (left < n)
        {
            cout << "\nLeft Child: " << arr[left];
        }
        else
        {
            cout << "\nLeft Child: None";
        }

        // Find right child
        int right = 2 * i + 2;

        if (right < n)
        {
            cout << "\nRight Child: " << arr[right];
        }
        else
        {
            cout << "\nRight Child: None";
        }

        cout << "\n";
    }

    return 0;
}
