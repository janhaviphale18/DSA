#include <iostream>
using namespace std;

int main()
{
    int row, col;
    int matrix[100][100];
    int key;
    int positionRow = -1;
    int positionCol = -1;

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

    int i = 0;
    int j = col - 1;

    while (i < row && j >= 0)
    {
        if (matrix[i][j] == key)
        {
            positionRow = i + 1;
            positionCol = j + 1;
            break;
        }
        else if (matrix[i][j] > key)
        {
            j--;
        }
        else
        {
            i++;
        }
    }

    if (positionRow != -1)
    {
        cout << "Element found at Row = "
             << positionRow
             << ", Column = "
             << positionCol;
    }
    else
    {
        cout << "Element not found.";
    }

    return 0;
}