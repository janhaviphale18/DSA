#include <iostream>
#include <queue>
using namespace std;

int main()
{
    queue<int> q;

    int n, x;
    bool found = false;

    cout << "Enter number of elements: ";
    cin >> n;

    cout << "Enter elements: ";

    for (int i = 0; i < n; i++)
    {
        cin >> x;
        q.push(x);
    }

    queue<int> temp = q;

    while (!temp.empty() && !found)
    {
        int current = temp.front();
        temp.pop();

        queue<int> check = temp;

        while (!check.empty())
        {
            if (check.front() == current)
            {
                cout << "First repeating element: " << current;
                found = true;
                break;
            }

            check.pop();
        }
    }

    if (!found)
    {
        cout << "No repeating element";
    }

    return 0;
}