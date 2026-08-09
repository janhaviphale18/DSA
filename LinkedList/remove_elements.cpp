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
    Node* current = NULL;
    Node* previous = NULL;

    int n, x;

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

    cout << "\nEnter the value to remove: ";
    cin >> x;

    while(head != NULL && head->data == x)
    {
        temp = head;
        head = head->next;
        delete temp;
    }

    current = head;
    previous = NULL;

    while(current != NULL)
    {
        if(current->data == x)
        {
            previous->next = current->next;
            temp = current;
            current = current->next;
            delete temp;
        }
        else
        {
            previous = current;
            current = current->next;
        }
    }

    cout << "\nLinked List after removing elements: ";

    temp = head;

    while(temp != NULL)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }

    cout << endl;

    return 0;
}