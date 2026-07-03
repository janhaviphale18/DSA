#include <iostream>
using namespace std;

int main()
{
    int size;
    int numbers[100];
    int isPalindrome = 1;

    cout << "Enter number of elements: ";
    cin >> size;

    cout << "Enter array elements: ";
    for (int index = 0; index < size; index++)
    {
        cin >> numbers[index];
    }

    for (int index = 0; index < size / 2; index++)
    {
        if (numbers[index] != numbers[size - index - 1])
        {
            isPalindrome = 0;
            break;
        }
    }

    if (isPalindrome == 1)
    {
        cout << "Palindrome array" << endl;
    }
    else
    {
        cout << "Not a palindrome array" << endl;
    }

    return 0;
}