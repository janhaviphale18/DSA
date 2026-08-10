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

    Node* fast = NULL;
    Node* slow = NULL;
    Node* previous = NULL;

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

    cout << "\nEnter the position from the end to delete: ";
    cin >> position;

    if(position < 1 || position > n)
    {
        cout << "\nInvalid position." << endl;
    }
    else
    {
        fast = head;
        slow = head;

        for(int i = 1; i <= position; i++)
        {
            fast = fast->next;
        }

        if(fast == NULL)
        {
            temp = head;
            head = head->next;
            delete temp;
        }
        else
        {
            while(fast != NULL)
            {
                fast = fast->next;
                slow = slow->next;
            }

            previous = slow;

            temp = slow->next;
            previous->next = slow->next->next;

            delete temp;
        }

        cout << "\nLinked List after deletion: ";

        temp = head;

        while(temp != NULL)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }

        cout << endl;
    }

    return 0;
}