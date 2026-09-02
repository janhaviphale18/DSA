#include <iostream>
#include <queue>
using namespace std;

int main()
{
    queue<int> q1, q2;

    int n, m, x;
    bool equal = true;

    cout << "Enter number of elements in Queue 1: ";
    cin >> n;

    cout << "Enter elements of Queue 1: ";
    for (int i = 0; i < n; i++)
    {
        cin >> x;
        q1.push(x);
    }

    cout << "Enter number of elements in Queue 2: ";
    cin >> m;

    cout << "Enter elements of Queue 2: ";
    for (int i = 0; i < m; i++)
    {
        cin >> x;
        q2.push(x);
    }

    if (n != m)
    {
        equal = false;
    }
    else
    {
        while (!q1.empty())
        {
            if (q1.front() != q2.front())
            {
                equal = false;
                break;
            }

            q1.pop();
            q2.pop();
        }
    }

    if (equal)
    {
        cout << "Queues are equal";
    }
    else
    {
        cout << "Queues are not equal";
    }

    return 0;
}