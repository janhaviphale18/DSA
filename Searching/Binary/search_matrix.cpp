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

    cout << "Enter matrix elements: ";

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cin >> matrix[i][j];
        }
    }

    cout << "Enter element to search: ";
    cin >> key;

    int low = 0;
    int high = row * col - 1;
    int position = -1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        int r = mid / col;
        int c = mid % col;

        if (matrix[r][c] == key)
        {
            position = mid;
            break;
        }
        else if (matrix[r][c] < key)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    if (position != -1)
    {
        cout << "Element found at Row = "
             << position / col + 1
             << ", Column = "
             << position % col + 1;
    }
    else
    {
        cout << "Element not found.";
    }

    return 0;
}