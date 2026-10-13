
#include <iostream>
using namespace std;

int main()
{
    int n, arr[100], target;

    cout << "Enter number of elements: ";
    cin >> n;

    cout << "Enter positive array elements: ";
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    cout << "Enter target sum: ";
    cin >> target;

    int left = 0;
    int sum = 0;
    int minLength = n + 1;

    for (int right = 0; right < n; right++)
    {
        sum += arr[right];

        while (sum >= target)
        {
            int length = right - left + 1;

            if (length < minLength)
            {
                minLength = length;
            }

            sum -= arr[left];
            left++;
        }
    }

    if (minLength == n + 1)
    {
        cout << "No valid subarray found.";
    }
    else
    {
        cout << "Minimum Subarray Length = " << minLength;
    }

    return 0;
}
