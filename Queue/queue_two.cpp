#include <iostream>
#include <queue>
using namespace std;

class MyQueue
{
    queue<int> q;

public:

    void enqueue(int x)
    {
        q.push(x);
    }

    void dequeue()
    {
        if (q.empty())
        {
            cout << "Queue is empty" << endl;
            return;
        }

        cout << "Deleted: " << q.front() << endl;
        q.pop();
    }

    void frontElement()
    {
        if (q.empty())
        {
            cout << "Queue is empty" << endl;
            return;
        }

        cout << "Front: " << q.front() << endl;
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
    MyQueue q;

    int choice, x;

    do
    {
        cout << "\n1. Enqueue";
        cout << "\n2. Dequeue";
        cout << "\n3. Front";
        cout << "\n4. Display";
        cout << "\n5. Exit";

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
                q.frontElement();
                break;

            case 4:
                q.display();
                break;

            case 5:
                cout << "Exiting...";
                break;

            default:
                cout << "Invalid choice";
        }

    } while (choice != 5);

    return 0;
}