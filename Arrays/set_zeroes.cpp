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

    bool zeroRow[100] = {false};
    bool zeroColumn[100] = {false};

    for (int row = 0; row < rows; row++)
    {
        for (int column = 0; column < columns; column++)
        {
            if (matrix[row][column] == 0)
            {
                zeroRow[row] = true;
                zeroColumn[column] = true;
            }
        }
    }

    for (int row = 0; row < rows; row++)
    {
        for (int column = 0; column < columns; column++)
        {
            if (zeroRow[row] || zeroColumn[column])
            {
                matrix[row][column] = 0;
            }
        }
    }

    cout << "Updated Matrix:\n";

    for (int row = 0; row < rows; row++)
    {
        for (int column = 0; column < columns; column++)
        {
            cout << matrix[row][column] << " ";
        }
        cout << endl;
    }

    return 0;
}