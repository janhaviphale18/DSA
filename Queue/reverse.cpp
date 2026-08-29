#include <iostream>
#include <stack>
#include <queue>
using namespace std;

queue<int> q;

void enqueue(int value)
{
    q.push(value);
    cout << value << " inserted into queue" << endl;
}

void reverseQueue()
{
    stack<int> s;

    while (!q.empty())
    {
        s.push(q.front());
        q.pop();
    }

    while (!s.empty())
    {
        q.push(s.top());
        s.pop();
    }

    cout << "Queue reversed" << endl;
}

void display()
{
    if (q.empty())
    {
        cout << "Queue is empty" << endl;
        return;
    }

    queue<int> temp = q;

    cout << "Queue: ";

    while (!temp.empty())
    {
        cout << temp.front() << " ";
        temp.pop();
    }

    cout << endl;
}

int main()
{
    enqueue(10);
    enqueue(20);
    enqueue(30);
    enqueue(40);

    reverseQueue();

    display();

    return 0;
}