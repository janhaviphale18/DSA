#include <iostream>
using namespace std;

struct Node
{
    int data;
    int priority;
    Node* next;
};

Node* front = NULL;

void insert(int value, int priority)
{
    Node* newNode = new Node();

    newNode->data = value;
    newNode->priority = priority;
    newNode->next = NULL;

    if (front == NULL || priority > front->priority)
    {
        newNode->next = front;
        front = newNode;
    }
    else
    {
        Node* temp = front;

        while (temp->next != NULL &&
               temp->next->priority >= priority)
        {
            temp = temp->next;
        }

        newNode->next = temp->next;
        temp->next = newNode;
    }

    cout << value << " inserted with priority "
         << priority << endl;
}

void deleteHighest()
{
    if (front == NULL)
    {
        cout << "Priority Queue Underflow" << endl;
        return;
    }

    Node* temp = front;

    cout << front->data
         << " deleted from priority queue" << endl;

    front = front->next;

    delete temp;
}

void display()
{
    if (front == NULL)
    {
        cout << "Priority Queue is empty" << endl;
        return;
    }

    Node* temp = front;

    cout << "Priority Queue: ";

    while (temp != NULL)
    {
        cout << temp->data
             << "(" << temp->priority << ") ";

        temp = temp->next;
    }

    cout << endl;
}

int main()
{
    insert(10, 2);
    insert(20, 1);
    insert(30, 3);

    deleteHighest();

    display();

    return 0;
}