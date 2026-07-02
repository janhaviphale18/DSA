#include <iostream>
using namespace std;

int main()
{
    int size;
    int numbers[100];
    int sum = 0;
    float average;

    cout << "Enter number of elements: ";
    cin >> size;

    cout << "Enter array elements: ";
    for (int index = 0; index < size; index++)
    {
        cin >> numbers[index];
    }

    for (int index = 0; index < size; index++)
    {
        sum = sum + numbers[index];
    }

    average = (float)sum / size;

    cout << "Average: " << average << endl;

    return 0;
}