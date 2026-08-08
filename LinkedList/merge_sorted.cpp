#include<iostream>
using namespace std;

struct Node
{
    int data;
    Node* next;
};

int main()
{
    Node* head1 = NULL;
    Node* head2 = NULL;

    Node* temp = NULL;
    Node* newNode = NULL;

    Node* current1 = NULL;
    Node* current2 = NULL;

    Node* head = NULL;
    Node* tail = NULL;

    int n1, n2;

    cout << "Enter the number of nodes in List 1: ";
    cin >> n1;

    for(int i = 1; i <= n1; i++)
    {
        newNode = new Node;

        cout << "Enter data for List 1 node " << i << ": ";
        cin >> newNode->data;

        newNode->next = NULL;

        if(head1 == NULL)
        {
            head1 = newNode;
            temp = newNode;
        }
        else
        {
            temp->next = newNode;
            temp = newNode;
        }
    }

    cout << "\nEnter the number of nodes in List 2: ";
    cin >> n2;

    for(int i = 1; i <= n2; i++)
    {
        newNode = new Node;

        cout << "Enter data for List 2 node " << i << ": ";
        cin >> newNode->data;

        newNode->next = NULL;

        if(head2 == NULL)
        {
            head2 = newNode;
            temp = newNode;
        }
        else
        {
            temp->next = newNode;
            temp = newNode;
        }
    }

    current1 = head1;
    current2 = head2;

    while(current1 != NULL && current2 != NULL)
    {
        if(current1->data <= current2->data)
        {
            newNode = new Node;
            newNode->data = current1->data;
            newNode->next = NULL;

            current1 = current1->next;
        }
        else
        {
            newNode = new Node;
            newNode->data = current2->data;
            newNode->next = NULL;

            current2 = current2->next;
        }

        if(head == NULL)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
    }

    while(current1 != NULL)
    {
        newNode = new Node;
        newNode->data = current1->data;
        newNode->next = NULL;

        if(head == NULL)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }

        current1 = current1->next;
    }

    while(current2 != NULL)
    {
        newNode = new Node;
        newNode->data = current2->data;
        newNode->next = NULL;

        if(head == NULL)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }

        current2 = current2->next;
    }

    cout << "\nMerged Linked List: ";

    temp = head;

    while(temp != NULL)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }

    cout << endl;

    return 0;
}