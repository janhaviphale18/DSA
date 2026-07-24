#include <iostream>
using namespace std;

int main()
{
    int number;
    int answer = -1;

    cout << "Enter a positive number: ";
    cin >> number;

    int low = 0;
    int high = number;
    int mid;

    while (low <= high)
    {
        mid = low + (high - low) / 2;

        if ((long long)mid * mid == number)
        {
            answer = mid;
            break;
        }
        else if ((long long)mid * mid < number)
        {
            answer = mid;
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    cout << "Integer Square Root = " << answer;

    return 0;
}