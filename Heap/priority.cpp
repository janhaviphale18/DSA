
#include <iostream>
#include <queue>
using namespace std;

int main()
{
    priority_queue<int> maxPQ;
    priority_queue<int, vector<int>, greater<int>> minPQ;

    int n, value;

    cout << "Enter number of elements (1-100): ";
    cin >> n;

    if (cin.fail() || n < 1 || n > 100)
    {
        cout << "Invalid number of elements!" << endl;
        return 0;
    }

    cout << "Enter " << n << " elements:" << endl;

    for (int i = 0; i < n; i++)
    {
        cin >> value;

        if (cin.fail())
        {
            cout << "Invalid input!" << endl;
            return 0;
        }

        maxPQ.push(value);
        minPQ.push(value);
    }

    // Display Max Priority Queue information
    cout << "\n--- Max Priority Queue ---" << endl;

    cout << "Highest Priority Element: " << maxPQ.top() << endl;

    cout << "Number of Elements: " << maxPQ.size() << endl;

    cout << "Elements in Priority Order: ";

    while (!maxPQ.empty())
    {
        cout << maxPQ.top() << " ";
        maxPQ.pop();
    }

    cout << endl;

    // Display Min Priority Queue information
    cout << "\n--- Min Priority Queue ---" << endl;

    cout << "Highest Priority Element: " << minPQ.top() << endl;

    cout << "Number of Elements: " << minPQ.size() << endl;

    cout << "Elements in Priority Order: ";

    while (!minPQ.empty())
    {
        cout << minPQ.top() << " ";
        minPQ.pop();
    }

    cout << endl;

    return 0;
}
