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

    if(head == NULL)
    {
        cout << "List is empty." << endl;
        return 0;
    }

    Node* current = head;
    Node* temp;

    do
    {
        temp = current->next;
        current->next = current->prev;
        current->prev = temp;
        current = temp;
    }
    while(current != head);

    temp = head;
    head = tail;
    tail = temp;

    cout << "\nReversed Forward: ";

    current = head;

    do
    {
        cout << current->data << " ";
        current = current->next;
    }
    while(current != head);

    cout << "\nReversed Backward: ";

    current = tail;

    do
    {
        cout << current->data << " ";
        current = current->prev;
    }
    while(current != tail);

    cout << endl;

    return 0;
}