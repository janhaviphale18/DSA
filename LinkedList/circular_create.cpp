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
        newNode->next = NULL;

        if(head == NULL)
        {
            head = newNode;
            tail = newNode;
            tail->next = head;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
            tail->next = head;
        }
    }

    cout << "\nCircular Linked List: ";

    Node* temp = head;

    if(head != NULL)
    {
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