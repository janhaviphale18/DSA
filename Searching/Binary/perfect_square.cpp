#include <iostream>
using namespace std;

int main()
{
    int n;

    cout << "Enter a number: ";
    cin >> n;

    int low = 0;
    int high = n;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        long long square = 1LL * mid * mid;

        if (square == n)
        {
            cout << n << " is a Perfect Square.";
            return 0;
        }
        else if (square < n)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    cout << n << " is Not a Perfect Square.";

    return 0;
}