#include <iostream>
#include <queue>
using namespace std;

int main()
{
    queue<int> q;
    queue<int> result;

    int n, x;
    bool duplicate;

    cout << "Enter number of elements: ";
    cin >> n;

    cout << "Enter elements: ";

    for (int i = 0; i < n; i++)
    {
        cin >> x;
        q.push(x);
    }

    while (!q.empty())
    {
        x = q.front();
        q.pop();

        duplicate = false;

        queue<int> temp = result;

        while (!temp.empty())
        {
            if (temp.front() == x)
            {
                duplicate = true;
                break;
            }

            temp.pop();
        }

        if (!duplicate)
        {
            result.push(x);
        }
    }

    cout << "Queue after removing duplicates: ";

    while (!result.empty())
    {
        cout << result.front() << " ";
        result.pop();
    }

    return 0;
}