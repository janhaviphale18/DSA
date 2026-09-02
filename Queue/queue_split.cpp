#include <iostream>
#include <queue>
using namespace std;

int main()
{
    queue<int> q;
    queue<int> q1, q2;

    int n, x;

    cout << "Enter number of elements: ";
    cin >> n;

    cout << "Enter elements: ";

    for (int i = 0; i < n; i++)
    {
        cin >> x;
        q.push(x);
    }

    int first = (n + 1) / 2;

    for (int i = 0; i < first; i++)
    {
        q1.push(q.front());
        q.pop();
    }

    while (!q.empty())
    {
        q2.push(q.front());
        q.pop();
    }

    cout << "Queue 1: ";

    while (!q1.empty())
    {
        cout << q1.front() << " ";
        q1.pop();
    }

    cout << "\nQueue 2: ";

    while (!q2.empty())
    {
        cout << q2.front() << " ";
        q2.pop();
    }

    return 0;
}