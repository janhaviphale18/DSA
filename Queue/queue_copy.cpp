#include <iostream>
#include <queue>
using namespace std;

int main()
{
    queue<int> q1, q2;

    int n, x;

    cout << "Enter number of elements: ";
    cin >> n;

    cout << "Enter elements: ";

    for (int i = 0; i < n; i++)
    {
        cin >> x;
        q1.push(x);
    }

    queue<int> temp = q1;

    while (!temp.empty())
    {
        q2.push(temp.front());
        temp.pop();
    }

    cout << "Original Queue: ";

    temp = q1;

    while (!temp.empty())
    {
        cout << temp.front() << " ";
        temp.pop();
    }

    cout << "\nCopied Queue: ";

    while (!q2.empty())
    {
        cout << q2.front() << " ";
        q2.pop();
    }

    return 0;
}