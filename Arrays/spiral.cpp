#include <iostream>
using namespace std;

int main()
{
    int rows, columns;
    int matrix[100][100];

    cout << "Enter number of rows: ";
    cin >> rows;

    cout << "Enter number of columns: ";
    cin >> columns;

    cout << "Enter matrix elements:\n";

    for (int row = 0; row < rows; row++)
    {
        for (int column = 0; column < columns; column++)
        {
            cin >> matrix[row][column];
        }
    }

    int top = 0;
    int bottom = rows - 1;
    int left = 0;
    int right = columns - 1;

    cout << "Spiral Traversal: ";

    while (top <= bottom && left <= right)
    {
        for (int column = left; column <= right; column++)
        {
            cout << matrix[top][column] << " ";
        }
        top++;

        for (int row = top; row <= bottom; row++)
        {
            cout << matrix[row][right] << " ";
        }
        right--;

        if (top <= bottom)
        {
            for (int column = right; column >= left; column--)
            {
                cout << matrix[bottom][column] << " ";
            }
            bottom--;
        }

        if (left <= right)
        {
            for (int row = bottom; row >= top; row--)
            {
                cout << matrix[row][left] << " ";
            }
            left++;
        }
    }

    cout << endl;

    return 0;
}