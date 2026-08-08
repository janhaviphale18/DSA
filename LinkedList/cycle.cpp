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

    Node* slow = NULL;
    Node* fast = NULL;

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

    cout << "\nEnter the position to create cycle (0 for no cycle): ";
    cin >> position;

    if(position != 0)
    {
        Node* cycleNode = head;

        for(int i = 1; i < position; i++)
        {
            cycleNode = cycleNode->next;
        }

        temp->next = cycleNode;
    }

    slow = head;
    fast = head;

    bool cycle = false;

    while(fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;

        if(slow == fast)
        {
            cycle = true;
            break;
        }
    }

    if(cycle)
    {
        cout << "\nCycle is present in the Linked List." << endl;
    }
    else
    {
        cout << "\nCycle is not present in the Linked List." << endl;
    }

    return 0;
}