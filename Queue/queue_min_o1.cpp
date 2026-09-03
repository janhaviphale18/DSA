#include <iostream>
#include <queue>
#include <deque>
using namespace std;

class QueueMin
{
    queue<int> q;
    deque<int> dq;

public:

    void enqueue(int x)
    {
        q.push(x);

        while (!dq.empty() && dq.back() > x)
        {
            dq.pop_back();
        }

        dq.push_back(x);
    }

    void dequeue()
    {
        if (q.empty())
        {
            cout << "Queue is empty" << endl;
            return;
        }

        int x = q.front();
        q.pop();

        if (dq.front() == x)
        {
            dq.pop_front();
        }

        cout << "Deleted: " << x << endl;
    }

    void front()
    {
        if (q.empty())
        {
            cout << "Queue is empty" << endl;
            return;
        }

        cout << "Front: " << q.front() << endl;
    }

    void minimum()
    {
        if (q.empty())
        {
            cout << "Queue is empty" << endl;
            return;
        }

        cout << "Minimum: " << dq.front() << endl;
    }

    void display()
    {
        if (q.empty())
        {
            cout << "Queue is empty" << endl;
            return;
        }

        queue<int> temp = q;

        cout << "Queue: ";

        while (!temp.empty())
        {
            cout << temp.front() << " ";
            temp.pop();
        }

        cout << endl;
    }
};

int main()
{
    QueueMin q;

    int choice, x;

    do
    {
        cout << "\n1. Enqueue";
        cout << "\n2. Dequeue";
        cout << "\n3. Front";
        cout << "\n4. Minimum";
        cout << "\n5. Display";
        cout << "\n6. Exit";

        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                cout << "Enter element: ";
                cin >> x;
                q.enqueue(x);
                break;

            case 2:
                q.dequeue();
                break;

            case 3:
                q.front();
                break;

            case 4:
                q.minimum();
                break;

            case 5:
                q.display();
                break;

            case 6:
                cout << "Exiting...";
                break;

            default:
                cout << "Invalid choice";
        }

    } while (choice != 6);

    return 0;
}