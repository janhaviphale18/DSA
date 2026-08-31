#include <iostream>
#include <queue>
using namespace std;

void separate(queue<int> q)
{
    queue<int> even;
    queue<int> odd;

    while (!q.empty())
    {
        int value = q.front();
        q.pop();

        if (value % 2 == 0)
        {
            even.push(value);
        }
        else
        {
            odd.push(value);
        }
    }

    cout << "Even Queue: ";

    while (!even.empty())
    {
        cout << even.front() << " ";
        even.pop();
    }

    cout << endl;

    cout << "Odd Queue: ";

    while (!odd.empty())
    {
        cout << odd.front() << " ";
        odd.pop();
    }

    cout << endl;
}

int main()
{
    queue<int> q;

    q.push(10);
    q.push(15);
    q.push(20);
    q.push(25);
    q.push(30);
    q.push(35);

    separate(q);

    return 0;
}