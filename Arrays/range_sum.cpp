#include <iostream>
using namespace std;

int main()
{
    int size;
    int numbers[100];
    int prefix[100];
    int queries;
    int left;
    int right;
    int sum;

    cout << "Enter number of elements: ";
    cin >> size;

    cout << "Enter array elements: ";

    for (int index = 0; index < size; index++)
    {
        cin >> numbers[index];
    }

    prefix[0] = numbers[0];

    for (int index = 1; index < size; index++)
    {
        prefix[index] = prefix[index - 1] + numbers[index];
    }

    cout << "Enter number of queries: ";
    cin >> queries;

    while (queries > 0)
    {
        cout << "Enter starting position: ";
        cin >> left;

        cout << "Enter ending position: ";
        cin >> right;

        left--;
        right--;

        if (left == 0)
        {
            sum = prefix[right];
        }
        else
        {
            sum = prefix[right] - prefix[left - 1];
        }

        cout << "Range Sum: " << sum << endl;

        queries--;
    }

    return 0;
}