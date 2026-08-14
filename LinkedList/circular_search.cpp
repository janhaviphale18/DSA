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

    int value;

    cout << "Enter the element to search: ";
    cin >> value;

    if(head == NULL)
    {
        cout << "List is empty." << endl;
        return 0;
    }

    Node* temp = head;
    int position = 1;
    bool found = false;

    do
    {
        if(temp->data == value)
        {
            cout << "Element found at position " << position << endl;
            found = true;
            break;
        }

        temp = temp->next;
        position++;
    }
    while(temp != head);

    if(!found)
    {
        cout << "Element not found." << endl;
    }

    return 0;
}