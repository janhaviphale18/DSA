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

    Node* second = NULL;
    Node* previous = NULL;
    Node* current = NULL;
    Node* next = NULL;

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

    if(head != NULL && head->next != NULL)
    {
        slow = head;
        fast = head;

        while(fast->next != NULL && fast->next->next != NULL)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        second = slow->next;
        slow->next = NULL;

        previous = NULL;
        current = second;

        while(current != NULL)
        {
            next = current->next;
            current->next = previous;
            previous = current;
            current = next;
        }

        second = previous;

        current = head;

        while(second != NULL)
        {
            next = current->next;
            current->next = second;
            current = second;

            second = second->next;
            current->next = next;
            current = next;
        }
    }

    cout << "\nReordered Linked List: ";

    temp = head;

    while(temp != NULL)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }

    cout << endl;

    return 0;
}