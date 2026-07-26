#include <iostream>
#include <climits>
using namespace std;

int main()
{
    int n1, n2;

    cout << "Enter the size of first sorted array: ";
    cin >> n1;

    int arr1[100];

    cout << "Enter the elements of first array: ";
    for (int i = 0; i < n1; i++)
    {
        cin >> arr1[i];
    }

    cout << "Enter the size of second sorted array: ";
    cin >> n2;

    int arr2[100];

    cout << "Enter the elements of second array: ";
    for (int i = 0; i < n2; i++)
    {
        cin >> arr2[i];
    }

    if (n1 > n2)
    {
        cout << "Please enter the smaller array first.";
        return 0;
    }

    int low = 0;
    int high = n1;

    while (low <= high)
    {
        int cut1 = (low + high) / 2;
        int cut2 = (n1 + n2 + 1) / 2 - cut1;

        int left1;
        int left2;
        int right1;
        int right2;

        if (cut1 == 0)
            left1 = INT_MIN;
        else
            left1 = arr1[cut1 - 1];

        if (cut2 == 0)
            left2 = INT_MIN;
        else
            left2 = arr2[cut2 - 1];

        if (cut1 == n1)
            right1 = INT_MAX;
        else
            right1 = arr1[cut1];

        if (cut2 == n2)
            right2 = INT_MAX;
        else
            right2 = arr2[cut2];

        if (left1 <= right2 && left2 <= right1)
        {
            if ((n1 + n2) % 2 == 0)
            {
                double median = (max(left1, left2) + min(right1, right2)) / 2.0;
                cout << "Median = " << median;
            }
            else
            {
                cout << "Median = " << max(left1, left2);
            }
            return 0;
        }
        else if (left1 > right2)
        {
            high = cut1 - 1;
        }
        else
        {
            low = cut1 + 1;
        }
    }

    return 0;
}