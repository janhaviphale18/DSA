#include <iostream>
#include <queue>
using namespace std;

int findMinimum(queue<int> q)
{
    int minimum = q.front();

    while (!q.empty())
    {
        if (q.front() < minimum)
        {
            minimum = q.front();
        }

        q.pop();
    }

    return minimum;
}

void display(queue<int> q)
{
    cout << "Queue: ";

    while (!q.empty())
    {
        cout << q.front() << " ";
        q.pop();
    }

    cout << endl;
}

int main()
{
    queue<int> q;

    q.push(10);
    q.push(25);
    q.push(15);
    q.push(5);
    q.push(30);

    display(q);

    cout << "Minimum element: "
         << findMinimum(q) << endl;

    return 0;
}