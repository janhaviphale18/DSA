#include <iostream>
using namespace std;

bool isPossible(int arr[], int n, int hours, int speed)
{
    int totalHours = 0;

    for (int i = 0; i < n; i++)
    {
        totalHours += (arr[i] + speed - 1) / speed;

        if (totalHours > hours)
        {
            return false;
        }
    }

    return true;
}

int main()
{
    int n, hours;
    int arr[100];

    cout << "Enter the number of banana piles: ";
    cin >> n;

    cout << "Enter bananas in each pile: ";
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    cout << "Enter total hours: ";
    cin >> hours;

    int maximum = arr[0];

    for (int i = 1; i < n; i++)
    {
        if (arr[i] > maximum)
        {
            maximum = arr[i];
        }
    }

    int low = 1;
    int high = maximum;
    int answer = maximum;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (isPossible(arr, n, hours, mid))
        {
            answer = mid;
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    cout << "Minimum Eating Speed = " << answer;

    return 0;
}