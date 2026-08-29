#include <iostream>
#include <stack>
using namespace std;

stack<int> s1;
stack<int> s2;

void enqueue(int value)
{
    s1.push(value);

    cout << value << " inserted into queue" << endl;
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

    stack<int> temp = s2;

    while (!temp.empty())
    {
        cout << temp.top() << " ";
        temp.pop();
    }

    stack<int> reverseS1 = s1;

    stack<int> temp2;

    while (!reverseS1.empty())
    {
        temp2.push(reverseS1.top());
        reverseS1.pop();
    }

    while (!temp2.empty())
    {
        cout << temp2.top() << " ";
        temp2.pop();
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