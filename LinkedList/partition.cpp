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

    Node* lessHead = NULL;
    Node* lessTail = NULL;

    Node* greaterHead = NULL;
    Node* greaterTail = NULL;

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

    cout << "\nEnter the value of x: ";
    cin >> x;

    temp = head;

    while(temp != NULL)
    {
        if(temp->data < x)
        {
            if(lessHead == NULL)
            {
                lessHead = temp;
                lessTail = temp;
            }
            else
            {
                lessTail->next = temp;
                lessTail = temp;
            }
        }
        else
        {
            if(greaterHead == NULL)
            {
                greaterHead = temp;
                greaterTail = temp;
            }
            else
            {
                greaterTail->next = temp;
                greaterTail = temp;
            }
        }

        temp = temp->next;
    }

    if(lessHead == NULL)
    {
        head = greaterHead;
    }
    else
    {
        head = lessHead;
        lessTail->next = greaterHead;
    }

    if(greaterTail != NULL)
    {
        greaterTail->next = NULL;
    }

    cout << "\nPartitioned Linked List: ";

    temp = head;

    while(temp != NULL)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }

    cout << endl;

    return 0;
}