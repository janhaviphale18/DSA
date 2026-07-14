#include <iostream>
using namespace std;

int main()
{
    int n;
    int numbers[100];
    bool found;

    cout << "Enter value of N: ";
    cin >> n;

    cout << "Enter " << n - 1 << " elements: ";

    for (int index = 0; index < n - 1; index++)
    {
        cin >> numbers[index];
    }

    for (int value = 1; value <= n; value++)
    {
        found = false;

        for (int index = 0; index < n - 1; index++)
        {
            if (numbers[index] == value)
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            cout << "Missing Number: " << value << endl;
            break;
        }
    }

    return 0;
}