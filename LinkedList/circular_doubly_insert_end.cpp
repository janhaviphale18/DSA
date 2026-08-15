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

    int value;

    cout << "Enter the element to insert at end: ";
    cin >> value;

    Node* newNode = new Node;

    newNode->data = value;
    newNode->prev = tail;
    newNode->next = head;

    tail->next = newNode;
    head->prev = newNode;

    tail = newNode;

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