#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int row, col;

    cout << "Enter the number of rows: ";
    cin >> row;

    cout << "Enter the number of columns: ";
    cin >> col;

    int matrix[100][100];

    cout << "Enter the row-wise sorted matrix:\n";

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cin >> matrix[i][j];
        }
    }

    int low = matrix[0][0];
    int high = matrix[0][col - 1];

    for (int i = 1; i < row; i++)
    {
        low = min(low, matrix[i][0]);
        high = max(high, matrix[i][col - 1]);
    }

    int required = (row * col) / 2;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        int count = 0;

        for (int i = 0; i < row; i++)
        {
            count += upper_bound(matrix[i], matrix[i] + col, mid) - matrix[i];
        }

        if (count <= required)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    cout << "Median = " << low;

    return 0;
}