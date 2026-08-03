#include <iostream>
using namespace std;

int main()
{
    int row, col;
    int matrix[100][100];
    int key;

    cout << "Enter number of rows: ";
    cin >> row;

    cout << "Enter number of columns: ";
    cin >> col;

    cout << "Enter matrix elements:\n";

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cin >> matrix[i][j];
        }
    }

    cout << "Enter element to search: ";
    cin >> key;

    int foundRow = -1;

    for (int i = 0; i < row; i++)
    {
        if (key >= matrix[i][0] && key <= matrix[i][col - 1])
        {
            foundRow = i;
            break;
        }
    }

    if (foundRow == -1)
    {
        cout << "Element not found.";
        return 0;
    }

    int low = 0;
    int high = col - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (matrix[foundRow][mid] == key)
        {
            cout << "Element found at Row = "
                 << foundRow + 1
                 << ", Column = "
                 << mid + 1;
            return 0;
        }
        else if (matrix[foundRow][mid] < key)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    cout << "Element not found.";

    return 0;
}