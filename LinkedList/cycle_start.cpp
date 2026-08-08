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
    Node* start = NULL;
    Node* cycleNode = NULL;

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
        cycleNode = head;

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
        start = head;

        while(start != slow)
        {
            start = start->next;
            slow = slow->next;
        }

        cout << "\nCycle starts at node with value: "
             << start->data << endl;
    }
    else
    {
        cout << "\nCycle is not present." << endl;
    }

    return 0;
}
