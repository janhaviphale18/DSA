#include <iostream>
#include <queue>
using namespace std;

void interleave(queue<int>& q)
{
    if (q.size() % 2 != 0)
    {
        cout << "Queue must contain even number of elements" << endl;
        return;
    }

    int half = q.size() / 2;

    queue<int> firstHalf;

    for (int i = 0; i < half; i++)
    {
        firstHalf.push(q.front());
        q.pop();
    }

    while (!firstHalf.empty())
    {
        q.push(firstHalf.front());
        firstHalf.pop();

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
    q.push(6);

    cout << "Original ";
    display(q);

    interleave(q);

    cout << "Interleaved ";
    display(q);

    return 0;
}