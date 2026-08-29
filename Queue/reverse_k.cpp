#include <iostream>
#include <queue>
#include <stack>
using namespace std;

void reverseFirstK(queue<int>& q, int k)
{
    if (k <= 0 || k > q.size())
    {
        cout << "Invalid value of K" << endl;
        return;
    }

    stack<int> s;

    // Move first K elements into stack
    for (int i = 0; i < k; i++)
    {
        s.push(q.front());
        q.pop();
    }

    // Put them back in reversed order
    while (!s.empty())
    {
        q.push(s.top());
        s.pop();
    }

    // Move remaining elements to the back
    int remaining = q.size() - k;

    for (int i = 0; i < remaining; i++)
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

    q.push(10);
    q.push(20);
    q.push(30);
    q.push(40);
    q.push(50);

    int k = 3;

    cout << "Original ";
    display(q);

    reverseFirstK(q, k);

    cout << "Queue after reversing first "
         << k << " elements: ";
    display(q);

    return 0;
}