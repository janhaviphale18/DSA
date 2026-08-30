#include <iostream>
#include <queue>
using namespace std;

int findMaximum(queue<int> q)
{
    int maximum = q.front();

    while (!q.empty())
    {
        if (q.front() > maximum)
        {
            maximum = q.front();
        }

        q.pop();
    }

    return maximum;
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
    q.push(40);
    q.push(30);

    display(q);

    cout << "Maximum element: "
         << findMaximum(q) << endl;

    return 0;
}