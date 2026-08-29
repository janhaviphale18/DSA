#include <iostream>
#include <queue>
#include <stack>
using namespace std;

bool isPalindrome(queue<int> q)
{
    stack<int> s;
    queue<int> temp = q;

    while (!q.empty())
    {
        s.push(q.front());
        q.pop();
    }

    while (!temp.empty())
    {
        if (temp.front() != s.top())
        {
            return false;
        }

        temp.pop();
        s.pop();
    }

    return true;
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
    q.push(2);
    q.push(1);

    display(q);

    if (isPalindrome(q))
    {
        cout << "Queue is a palindrome" << endl;
    }
    else
    {
        cout << "Queue is not a palindrome" << endl;
    }

    return 0;
}