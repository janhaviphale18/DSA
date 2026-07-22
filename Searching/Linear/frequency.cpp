#include <iostream>
using namespace std;

int main()
{
    int n, arr[100];
    bool visited[100] = {false};

    cout << "Enter the number of elements in the array: ";
    cin >> n;

    cout << "Enter the elements in the array: ";
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    cout << "\nElement\tFrequency\n";

    for (int i = 0; i < n; i++)
    {
        if (visited[i] == true)
        {
            continue;
        }

        int count = 1;

        for (int j = i + 1; j < n; j++)
        {
            if (arr[i] == arr[j])
            {
                count++;
                visited[j] = true;
            }
        }

        cout << arr[i] << "\t" << count << endl;
    }

    return 0;
}