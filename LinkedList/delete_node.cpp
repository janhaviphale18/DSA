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
    Node* deleteNode = NULL;

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

    cout << "\nEnter the position of node to delete: ";
    cin >> position;

    if(position < 1 || position >= n)
    {
        cout << "\nNode cannot be deleted using this method." << endl;
    }
    else
    {
        deleteNode = head;

        for(int i = 1; i < position; i++)
        {
            deleteNode = deleteNode->next;
        }

        deleteNode->data = deleteNode->next->data;

        temp = deleteNode->next;

        deleteNode->next = deleteNode->next->next;

        delete temp;

        cout << "\nLinked List after deletion: ";

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