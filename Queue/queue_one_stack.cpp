#include <iostream>
#include <stack>
using namespace std;

class Queue
{
    stack<int> s;

public:

    void enqueue(int x)
    {
        s.push(x);
    }

    int dequeue()
    {
        if (s.empty())
        {
            cout << "Queue is empty" << endl;
            return -1;
        }

        int x = s.top();
        s.pop();

        if (s.empty())
        {
            return x;
        }

        int front = dequeue();

        s.push(x);

        return front;
    }

    void display()
    {
        if (s.empty())
        {
            cout << "Queue is empty" << endl;
            return;
        }

        stack<int> temp = s;

        cout << "Queue: ";

        while (!temp.empty())
        {
            cout << temp.top() << " ";
            temp.pop();
        }

        cout << endl;
    }
};

int main()
{
    Queue q;

    int choice, x;

    do
    {
        cout << "\n1. Enqueue";
        cout << "\n2. Dequeue";
        cout << "\n3. Display";
        cout << "\n4. Exit";

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
                x = q.dequeue();

                if (x != -1)
                {
                    cout << "Deleted: " << x << endl;
                }
                break;

            case 3:
                q.display();
                break;

            case 4:
                cout << "Exiting...";
                break;

            default:
                cout << "Invalid choice";
        }

    } while (choice != 4);

    return 0;
}