#include<iostream>
using namespace std;

struct Node
{
    int data;
    Node* next;
};

int main()
{
    Node* head = NULL;
    Node* temp = NULL;
    Node* prev = NULL;
    Node* newNode = NULL;

    int n, position;

    cout << "Enter the number of nodes: ";
    cin >> n;

    for(int i = 1; i <= n; i++)
    {
        newNode = new Node;

        cout << "Enter data for node " << i << ": ";
        cin >> newNode->data;

        newNode->next = NULL;

        if(head == NULL)
        {
            head = newNode;
            temp = newNode;
        }
        else
        {
            temp->next = newNode;
            temp = newNode;
        }
    }

    cout << "\nEnter the position to delete: ";
    cin >> position;

    if(position < 1 || position > n)
    {
        cout << "Invalid Position." << endl;
    }
    else if(position == 1)
    {
        temp = head;
        head = head->next;
        delete temp;

        cout << "\nUpdated Linked List: ";

        temp = head;

        while(temp != NULL)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }

        cout << endl;
    }
    else
    {
        temp = head;

        for(int i = 1; i < position; i++)
        {
            prev = temp;
            temp = temp->next;
        }

        prev->next = temp->next;

        delete temp;

        cout << "\nUpdated Linked List: ";

        temp = head;

        while(temp != NULL)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }

        cout << endl;
    }

    return 0;
}