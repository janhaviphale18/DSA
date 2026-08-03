#include <iostream>
using namespace std;

int main()
{
    int row, col;
    int matrix[100][100];

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

    int low = 0;
    int high = col - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        int maxRow = 0;

        for (int i = 1; i < row; i++)
        {
            if (matrix[i][mid] > matrix[maxRow][mid])
            {
                maxRow = i;
            }
        }

        int left = -1;
        int right = -1;

        if (mid > 0)
        {
            left = matrix[maxRow][mid - 1];
        }

        if (mid < col - 1)
        {
            right = matrix[maxRow][mid + 1];
        }

        if (matrix[maxRow][mid] >= left && matrix[maxRow][mid] >= right)
        {
            cout << "Peak Element = " << matrix[maxRow][mid] << endl;
            cout << "Position = Row " << maxRow + 1
                 << ", Column " << mid + 1;
            return 0;
        }
        else if (left > matrix[maxRow][mid])
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    return 0;
}