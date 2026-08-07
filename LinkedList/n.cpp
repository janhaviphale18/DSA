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

    cout << "\nEnter the position: ";
    cin >> position;

    if(position < 1 || position > n)
    {
        cout << "Invalid Position." << endl;
    }
    else
    {
        temp = head;

        for(int i = 1; i < position; i++)
        {
            temp = temp->next;
        }

        cout << "\nNode at Position " << position << " = " << temp->data << endl;
    }

    return 0;
}