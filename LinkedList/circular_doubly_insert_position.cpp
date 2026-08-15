#include<iostream>
using namespace std;

struct Node
{
    int data;
    Node* prev;
    Node* next;
};

int main()
{
    int n;

    cout << "Enter the number of nodes: ";
    cin >> n;

    Node* head = NULL;
    Node* tail = NULL;

    cout << "Enter the elements: ";

    for(int i = 0; i < n; i++)
    {
        int value;
        cin >> value;

        Node* newNode = new Node;

        newNode->data = value;

        if(head == NULL)
        {
            head = newNode;
            tail = newNode;

            head->next = head;
            head->prev = head;
        }
        else
        {
            newNode->prev = tail;
            newNode->next = head;

            tail->next = newNode;
            head->prev = newNode;

            tail = newNode;
        }
    }

    int value, position;

    cout << "Enter the element to insert: ";
    cin >> value;

    cout << "Enter the position: ";
    cin >> position;

    Node* newNode = new Node;
    newNode->data = value;

    if(position == 1)
    {
        newNode->prev = tail;
        newNode->next = head;

        head->prev = newNode;
        tail->next = newNode;

        head = newNode;
    }
    else
    {
        Node* temp = head;

        for(int i = 1; i < position - 1; i++)
        {
            temp = temp->next;
        }

        newNode->next = temp->next;
        newNode->prev = temp;

        temp->next->prev = newNode;
        temp->next = newNode;

        if(newNode->next == head)
        {
            tail = newNode;
        }
    }

    cout << "\nForward: ";

    Node* temp = head;

    do
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
    while(temp != head);

    cout << "\nBackward: ";

    temp = tail;

    do
    {
        cout << temp->data << " ";
        temp = temp->prev;
    }
    while(temp != tail);

    cout << endl;

    return 0;
}