#include <iostream>
using namespace std;

int power(int base, int exponent)
{
    int result = 1;

    for (int i = 1; i <= exponent; i++)
    {
        result = result * base;
    }

    return result;
}

int main()
{
    int number, root;

    cout << "Enter the number: ";
    cin >> number;

    cout << "Enter the value of N: ";
    cin >> root;

    int low = 1;
    int high = number;
    int answer = -1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        int value = power(mid, root);

        if (value == number)
        {
            answer = mid;
            break;
        }
        else if (value < number)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    if (answer != -1)
    {
        cout << "Nth Root = " << answer;
    }
    else
    {
        cout << "Exact Nth Root does not exist.";
    }

    return 0;
}