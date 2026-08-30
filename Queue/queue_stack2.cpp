#include <iostream>
#include <stack>
using namespace std;

stack<int> s1;
stack<int> s2;

void enqueue(int value)
{
    s1.push(value);
}

void dequeue()
{
    if (s1.empty() && s2.empty())
    {
        cout << "Queue Underflow" << endl;
        return;
    }

    if (s2.empty())
    {
        while (!s1.empty())
        {
            s2.push(s1.top());
            s1.pop();
        }
    }

    cout << s2.top() << " deleted from queue" << endl;
    s2.pop();
}

void display()
{
    if (s1.empty() && s2.empty())
    {
        cout << "Queue is empty" << endl;
        return;
    }

    stack<int> temp1 = s2;

    while (!temp1.empty())
    {
        cout << temp1.top() << " ";
        temp1.pop();
    }

    stack<int> temp2 = s1;
    stack<int> reverse;

    while (!temp2.empty())
    {
        reverse.push(temp2.top());
        temp2.pop();
    }

    while (!reverse.empty())
    {
        cout << reverse.top() << " ";
        reverse.pop();
    }

    cout << endl;
}

int main()
{
    enqueue(10);
    enqueue(20);
    enqueue(30);

    dequeue();

    cout << "Queue: ";
    display();

    return 0;
}