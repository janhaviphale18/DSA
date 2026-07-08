#include <iostream>
using namespace std;

int main()
{
    int size;
    int numbers[100];
    int maximumProduct;
    int firstElement;
    int secondElement;

    cout << "Enter number of elements: ";
    cin >> size;

    if (size < 2)
    {
        cout << "At least two elements are required." << endl;
        return 0;
    }

    cout << "Enter array elements: ";

    for (int index = 0; index < size; index++)
    {
        cin >> numbers[index];
    }

    maximumProduct = numbers[0] * numbers[1];
    firstElement = numbers[0];
    secondElement = numbers[1];

    for (int first = 0; first < size - 1; first++)
    {
        for (int second = first + 1; second < size; second++)
        {
            int product = numbers[first] * numbers[second];

            if (product > maximumProduct)
            {
                maximumProduct = product;
                firstElement = numbers[first];
                secondElement = numbers[second];
            }
        }
    }

    cout << "Pair: " << firstElement << " " << secondElement << endl;
    cout << "Maximum product: " << maximumProduct << endl;

    return 0;
}