#include <iostream>
#include <queue>
using namespace std;

int main()
{
    queue<int> q1, q2, q3;

    int n, m, x;

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

    while (!q1.empty() && !q2.empty())
    {
        q3.push(q1.front());
        q1.pop();

        q3.push(q2.front());
        q2.pop();
    }

    while (!q1.empty())
    {
        q3.push(q1.front());
        q1.pop();
    }

    while (!q2.empty())
    {
        q3.push(q2.front());
        q2.pop();
    }

    cout << "Merged Queue: ";

    while (!q3.empty())
    {
        cout << q3.front() << " ";
        q3.pop();
    }

    return 0;
}