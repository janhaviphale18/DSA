
#include <iostream>
#include <climits>
using namespace std;

int main()
{
    int n, m;
    int a[100], b[100];

    cout << "Enter size of first array: ";
    cin >> n;

    cout << "Enter first sorted array: ";
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    cout << "Enter size of second array: ";
    cin >> m;

    cout << "Enter second sorted array: ";
    for (int i = 0; i < m; i++)
    {
        cin >> b[i];
    }

    if (n > m)
    {
        cout << "Make the first array smaller.";
        return 0;
    }

    int low = 0;
    int high = n;

    while (low <= high)
    {
        int cut1 = low + (high - low) / 2;
        int cut2 = (n + m + 1) / 2 - cut1;

        int left1 = (cut1 == 0) ? INT_MIN : a[cut1 - 1];
        int right1 = (cut1 == n) ? INT_MAX : a[cut1];

        int left2 = (cut2 == 0) ? INT_MIN : b[cut2 - 1];
        int right2 = (cut2 == m) ? INT_MAX : b[cut2];

        if (left1 <= right2 && left2 <= right1)
        {
            int leftMax = (left1 > left2) ? left1 : left2;

            if ((n + m) % 2 == 1)
            {
                cout << "Median = " << leftMax;
            }
            else
            {
                int rightMin = (right1 < right2)
                               ? right1 : right2;

                double median =
                    ((double)leftMax + rightMin) / 2.0;

                cout << "Median = " << median;
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

    cout << "Invalid input.";
    return 0;
}
