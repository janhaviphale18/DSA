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

    int n, item, position = 1;
    bool found = false;

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

    cout << "\nEnter the element to search: ";
    cin >> item;

    temp = head;

    while(temp != NULL)
    {
        if(temp->data == item)
        {
            found = true;
            break;
        }

        temp = temp->next;
        position++;
    }

    if(found)
    {
        cout << "Element found at position " << position << endl;
    }
    else
    {
        cout << "Element not found." << endl;
    }

    return 0;
}