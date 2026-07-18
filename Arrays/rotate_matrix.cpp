#include <iostream>
using namespace std;

int main()
{
    int size;
    int matrix[100][100];
    int rotated[100][100];

    cout << "Enter matrix size: ";
    cin >> size;

    cout << "Enter matrix elements:\n";

    for (int row = 0; row < size; row++)
    {
        for (int column = 0; column < size; column++)
        {
            cin >> matrix[row][column];
        }
    }

    for (int row = 0; row < size; row++)
    {
        for (int column = 0; column < size; column++)
        {
            rotated[column][size - 1 - row] = matrix[row][column];
        }
    }

    cout << "Rotated Matrix:\n";

    for (int row = 0; row < size; row++)
    {
        for (int column = 0; column < size; column++)
        {
            cout << rotated[row][column] << " ";
        }
        cout << endl;
    }

    return 0;
}