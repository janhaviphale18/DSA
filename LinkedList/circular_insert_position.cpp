#include<iostream>
using namespace std;

struct Node
{
    int data;
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
            tail->next = head;
        }
        else
        {
            newNode->next = head;
            tail->next = newNode;
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
        newNode->next = head;
        head = newNode;
        tail->next = head;
    }
    else
    {
        Node* temp = head;

        for(int i = 1; i < position - 1; i++)
        {
            temp = temp->next;
        }

        newNode->next = temp->next;
        temp->next = newNode;

        if(newNode->next == head)
        {
            tail = newNode;
        }
    }

    cout << "\nCircular Linked List: ";

    Node* temp = head;

    do
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
    while(temp != head);

    cout << endl;

    return 0;
}