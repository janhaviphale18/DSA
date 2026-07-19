#include <iostream>
using namespace std;

int main()
{
    int size;
    int numbers[100];
    int dp[100];

    cout << "Enter number of elements: ";
    cin >> size;

    cout << "Enter array elements: ";

    for (int index = 0; index < size; index++)
    {
        cin >> numbers[index];
        dp[index] = numbers[index];
    }

    for (int current = 1; current < size; current++)
    {
        for (int previous = 0; previous < current; previous++)
        {
            if (numbers[current] > numbers[previous] &&
                dp[current] < dp[previous] + numbers[current])
            {
                dp[current] = dp[previous] + numbers[current];
            }
        }
    }

    int maximumSum = dp[0];

    for (int index = 1; index < size; index++)
    {
        if (dp[index] > maximumSum)
        {
            maximumSum = dp[index];
        }
    }


    cout << "Maximum Sum Increasing Subsequence = "
         << maximumSum << endl;

    return 0;
}