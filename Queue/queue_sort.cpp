#include <iostream>
#include <queue>
using namespace std;

void sortQueue(queue<int>& q)
{
    queue<int> sorted;

    while (!q.empty())
    {
        int current = q.front();
        q.pop();

        int size = sorted.size();

        while (size > 0 && sorted.back() > current)
        {
            q.push(sorted.back());
            sorted.pop();
            size--;
        }

        sorted.push(current);

        while (!q.empty() && q.back() == current)
        {
            break;
        }
    }

    q = sorted;
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

    q.push(4);
    q.push(2);
    q.push(1);
    q.push(3);

    cout << "Original ";
    display(q);

    sortQueue(q);

    cout << "Sorted ";
    display(q);

    return 0;
}