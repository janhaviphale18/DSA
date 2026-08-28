#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node* next;
};

Node* front = NULL;
Node* rear = NULL;

void enqueue(int value)
{
    Node* newNode = new Node();

    newNode->data = value;
    newNode->next = NULL;

    if (rear == NULL)
    {
        front = rear = newNode;
    }
    else
    {
        rear->next = newNode;
        rear = newNode;
    }

    cout << value << " inserted into queue" << endl;
}

void displayFront()
{
    if (front == NULL)
    {
        cout << "Queue is empty" << endl;
        return;
    }

    cout << "Front element: " << front->data << endl;
}

void displayRear()
{
    if (rear == NULL)
    {
        cout << "Queue is empty" << endl;
        return;
    }

    cout << "Rear element: " << rear->data << endl;
}

int main()
{
    enqueue(10);
    enqueue(20);
    enqueue(30);

    displayFront();
    displayRear();

    return 0;
}