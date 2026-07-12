#include <iostream>
using namespace std;

int main()
{
    int size;
    int packets[100];
    int students;

    cout << "Enter number of chocolate packets: ";
    cin >> size;

    cout << "Enter sorted chocolate packets: ";

    for (int index = 0; index < size; index++)
    {
        cin >> packets[index];
    }

    cout << "Enter number of students: ";
    cin >> students;

    if (students > size || students == 0)
    {
        cout << "Invalid number of students." << endl;
        return 0;
    }

    int minimumDifference = packets[students - 1] - packets[0];

    for (int index = 1; index <= size - students; index++)
    {
        int difference = packets[index + students - 1] - packets[index];

        if (difference < minimumDifference)
        {
            minimumDifference = difference;
        }
    }

    cout << "Minimum Difference: "
         << minimumDifference << endl;

    return 0;
}