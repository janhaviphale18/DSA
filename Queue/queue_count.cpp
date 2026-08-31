#include <iostream>
#include <queue>
using namespace std;

int countElements(queue<int> q)
{
    int count = 0;

    while (!q.empty())
    {
        count++;
        q.pop();
    }

    return count;
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

    display(q);

    cout << "Number of elements: "
         << countElements(q) << endl;

    return 0;
}