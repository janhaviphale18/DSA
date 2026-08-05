#include <iostream>
using namespace std;

int firstOne(int arr[], int col)
{
    int low = 0;
    int high = col - 1;
    int answer = -1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (arr[mid] == 1)
        {
            answer = mid;
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    return answer;
}

int main()
{
    int row, col;
    int matrix[100][100];

    cout << "Enter number of rows: ";
    cin >> row;

    cout << "Enter number of columns: ";
    cin >> col;

    cout << "Enter binary matrix:\n";

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cin >> matrix[i][j];
        }
    }

    for (int i = 0; i < row; i++)
    {
        int index = firstOne(matrix[i], col);

        if (index != -1)
        {
            cout << "First row containing 1 = " << i + 1;
            cout << "\nFirst 1 is at Column = " << index + 1;
            return 0;
        }
    }

    cout << "No 1 found in the matrix.";

    return 0;
}