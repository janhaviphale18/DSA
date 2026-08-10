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

    int n;

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

    Node* current = head;
    Node* previous = NULL;
    Node* first = NULL;
    Node* second = NULL;

    while(current != NULL && current->next != NULL)
    {
        first = current;
        second = current->next;

        first->next = second->next;
        second->next = first;

        if(previous == NULL)
        {
            head = second;
        }
        else
        {
            previous->next = second;
        }

        previous = first;
        current = first->next;
    }

    cout << "\nLinked List after swapping pairs: ";

    temp = head;

    while(temp != NULL)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }

    cout << endl;

    return 0;
}