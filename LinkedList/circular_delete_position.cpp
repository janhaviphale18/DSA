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

    int position;

    cout << "Enter the position to delete: ";
    cin >> position;

    if(head == NULL)
    {
        cout << "List is empty." << endl;
        return 0;
    }

    if(position == 1)
    {
        if(head == tail)
        {
            delete head;
            head = NULL;
            tail = NULL;
        }
        else
        {
            Node* temp = head;

            head = head->next;
            tail->next = head;

            delete temp;
        }
    }
    else
    {
        Node* temp = head;

        for(int i = 1; i < position - 1; i++)
        {
            temp = temp->next;
        }

        Node* deleteNode = temp->next;

        if(deleteNode == head)
        {
            cout << "Invalid position." << endl;
            return 0;
        }

        temp->next = deleteNode->next;

        if(deleteNode == tail)
        {
            tail = temp;
        }

        delete deleteNode;
    }

    cout << "\nCircular Linked List: ";

    if(head != NULL)
    {
        Node* temp = head;

        do
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        while(temp != head);
    }

    cout << endl;

    return 0;
}