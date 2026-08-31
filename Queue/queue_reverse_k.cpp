#include <iostream>
#include <queue>
#include <stack>
using namespace std;

void reverseFirstK(queue<int>& q, int k)
{
    if (q.empty() || k <= 0 || k > q.size())
    {
        cout << "Invalid K" << endl;
        return;
    }

    stack<int> s;

    // Move first K elements to stack
    for (int i = 0; i < k; i++)
    {
        s.push(q.front());
        q.pop();
    }

    // Insert them back in reversed order
    while (!s.empty())
    {
        q.push(s.top());
        s.pop();
    }

    // Move remaining elements to the rear
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

    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    q.push(5);

    int k = 3;

    cout << "Original ";
    display(q);

    reverseFirstK(q, k);

    cout << "After reversing first " << k << " elements: ";
    display(q);

    return 0;
}