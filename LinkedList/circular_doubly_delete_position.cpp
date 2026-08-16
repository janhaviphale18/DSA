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

            head->prev = tail;
            tail->next = head;

            delete temp;
        }
    }
    else
    {
        Node* temp = head;

        for(int i = 1; i < position; i++)
        {
            temp = temp->next;

            if(temp == head)
            {
                cout << "Invalid position." << endl;
                return 0;
            }
        }

        if(temp == tail)
        {
            tail = tail->prev;
        }

        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;

        delete temp;
    }

    cout << "\nForward: ";

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

    cout << "\nBackward: ";

    if(tail != NULL)
    {
        Node* temp = tail;

        do
        {
            cout << temp->data << " ";
            temp = temp->prev;
        }
        while(temp != tail);
    }

    cout << endl;

    return 0;
}