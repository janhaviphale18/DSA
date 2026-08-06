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
    Node* newNode = NULL;

    int n, value, position;

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

    cout << "\nEnter the position: ";
    cin >> position;

    cout << "Enter the value to insert: ";
    cin >> value;

    if(position < 1 || position > n + 1)
    {
        cout << "Invalid Position." << endl;
    }
    else
    {
        newNode = new Node;
        newNode->data = value;

        if(position == 1)
        {
            newNode->next = head;
            head = newNode;
        }
        else
        {
            temp = head;

            for(int i = 1; i < position - 1; i++)
            {
                temp = temp->next;
            }

            newNode->next = temp->next;
            temp->next = newNode;
        }

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