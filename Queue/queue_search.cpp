#include <iostream>
#include <queue>
using namespace std;

int main()
{
    queue<int> q;

    int n, x, search;
    bool found = false;
    int position = 1;

    cout << "Enter number of elements: ";
    cin >> n;

    cout << "Enter elements: ";

    for (int i = 0; i < n; i++)
    {
        cin >> x;
        q.push(x);
    }

    cout << "Enter element to search: ";
    cin >> search;

    queue<int> temp = q;

    while (!temp.empty())
    {
        if (temp.front() == search)
        {
            cout << "Element found at position " << position;
            found = true;
            break;
        }

        temp.pop();
        position++;
    }

    if (!found)
    {
        cout << "Element not found";
    }

    return 0;
}