#include <iostream>
using namespace std;

int main()
{
    int n, target;

    cout << "Enter the maximum number: ";
    cin >> n;

    cout << "Enter the hidden number: ";
    cin >> target;

    int low = 1;
    int high = n;
    int guess;

    while (low <= high)
    {
        guess = low + (high - low) / 2;

        if (guess == target)
        {
            cout << "Hidden Number Found = " << guess;
            break;
        }
        else if (guess < target)
        {
            low = guess + 1;
        }
        else
        {
            high = guess - 1;
        }
    }

    return 0;
}