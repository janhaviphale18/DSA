#include <iostream>
#include <algorithm>
using namespace std;

bool isPossible(int stalls[], int n, int cows, int distance)
{
    int cowCount = 1;
    int lastPosition = stalls[0];

    for (int i = 1; i < n; i++)
    {
        if (stalls[i] - lastPosition >= distance)
        {
            cowCount++;
            lastPosition = stalls[i];

            if (cowCount == cows)
            {
                return true;
            }
        }
    }

    return false;
}

int main()
{
    int n, cows;
    int stalls[100];

    cout << "Enter the number of stalls: ";
    cin >> n;

    cout << "Enter the stall positions: ";
    for (int i = 0; i < n; i++)
    {
        cin >> stalls[i];
    }

    cout << "Enter the number of cows: ";
    cin >> cows;

    sort(stalls, stalls + n);

    int low = 1;
    int high = stalls[n - 1] - stalls[0];
    int answer = -1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (isPossible(stalls, n, cows, mid))
        {
            answer = mid;
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    cout << "Largest Minimum Distance = " << answer;

    return 0;
}