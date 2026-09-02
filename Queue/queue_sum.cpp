#include <iostream>
#include <queue>
using namespace std;

int findSum(queue<int> q)
{
    int sum = 0;

    while (!q.empty())
    {
        sum = sum + q.front();
        q.pop();
    }

    return sum;
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

    cout << "Sum of elements: "
         << findSum(q) << endl;

    return 0;
}