#include <iostream>
using namespace std;

int main()
{
    int rows;
    int triangle[100][100];

    cout << "Enter number of rows: ";
    cin >> rows;

    for (int row = 0; row < rows; row++)
    {
        for (int column = 0; column <= row; column++)
        {
            if (column == 0 || column == row)
            {
                triangle[row][column] = 1;
            }
            else
            {
                triangle[row][column] =
                    triangle[row - 1][column - 1] +
                    triangle[row - 1][column];
            }
        }
    }

    cout << "Pascal's Triangle:\n";

    for (int row = 0; row < rows; row++)
    {
        for (int column = 0; column <= row; column++)
        {
            cout << triangle[row][column] << " ";
        }

        cout << endl;
    }

    return 0;
}