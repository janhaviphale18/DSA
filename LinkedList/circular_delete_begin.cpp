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

    if(head == NULL)
    {
        cout << "List is empty." << endl;
        return 0;
    }

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