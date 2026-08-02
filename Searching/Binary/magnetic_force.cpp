#include <iostream>
#include <algorithm>
using namespace std;

bool isPossible(int position[], int n, int balls, int distance)
{
    int ballCount = 1;
    int lastPosition = position[0];

    for (int i = 1; i < n; i++)
    {
        if (position[i] - lastPosition >= distance)
        {
            ballCount++;
            lastPosition = position[i];

            if (ballCount == balls)
            {
                return true;
            }
        }
    }

    return false;
}

int main()
{
    int n, balls;
    int position[100];

    cout << "Enter the number of positions: ";
    cin >> n;

    cout << "Enter the positions: ";
    for (int i = 0; i < n; i++)
    {
        cin >> position[i];
    }

    cout << "Enter the number of balls: ";
    cin >> balls;

    sort(position, position + n);

    int low = 1;
    int high = position[n - 1] - position[0];
    int answer = -1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (isPossible(position, n, balls, mid))
        {
            answer = mid;
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    cout << "Maximum Magnetic Force = " << answer;

    return 0;
}