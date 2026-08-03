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

    int maxOnes = 0;
    int rowIndex = -1;

    for (int i = 0; i < row; i++)
    {
        int index = firstOne(matrix[i], col);

        if (index != -1)
        {
            int ones = col - index;

            if (ones > maxOnes)
            {
                maxOnes = ones;
                rowIndex = i;
            }
        }
    }

    if (rowIndex != -1)
    {
        cout << "Row with Maximum 1's = " << rowIndex + 1;
    }
    else
    {
        cout << "No 1's present in the matrix.";
    }

    return 0;
}