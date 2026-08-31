#include <iostream>
#include <queue>
using namespace std;

void rotate(queue<int>& q, int k)
{
    if (q.empty())
    {
        cout << "Queue is empty" << endl;
        return;
    }

    k = k % q.size();

    for (int i = 0; i < k; i++)
    {
        q.push(q.front());
        q.pop();
    }
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

    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    q.push(5);

    int k = 2;

    cout << "Original ";
    display(q);

    rotate(q, k);

    cout << "Rotated ";
    display(q);

    return 0;
}