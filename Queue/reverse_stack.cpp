#include <iostream>
#include <queue>
#include <stack>
using namespace std;

void reverseQueue(queue<int>& q)
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
}

void display(queue<int> q)
{
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
    q.push(20);
    q.push(30);
    q.push(40);

    cout << "Original Queue: ";
    display(q);

    reverseQueue(q);

    cout << "Reversed Queue: ";
    display(q);

    return 0;
}