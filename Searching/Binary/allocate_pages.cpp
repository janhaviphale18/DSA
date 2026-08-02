#include <iostream>
using namespace std;

bool isPossible(int arr[], int n, int students, int maxPages)
{
    int studentCount = 1;
    int pageSum = 0;

    for (int i = 0; i < n; i++)
    {
        if (arr[i] > maxPages)
        {
            return false;
        }

        if (pageSum + arr[i] <= maxPages)
        {
            pageSum += arr[i];
        }
        else
        {
            studentCount++;
            pageSum = arr[i];

            if (studentCount > students)
            {
                return false;
            }
        }
    }

    return true;
}

int main()
{
    int n;
    int students;
    int arr[100];

    cout << "Enter the number of books: ";
    cin >> n;

    cout << "Enter the pages in each book: ";
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    cout << "Enter the number of students: ";
    cin >> students;

    if (students > n)
    {
        cout << "Allocation is not possible.";
        return 0;
    }

    int sum = 0;

    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }

    int low = 0;
    int high = sum;
    int answer = -1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (isPossible(arr, n, students, mid))
        {
            answer = mid;
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    cout << "Minimum Possible Maximum Pages = " << answer;

    return 0;
}