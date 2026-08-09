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

    Node* current = NULL;
    Node* tail = NULL;
    Node* newTail = NULL;

    int n, k;

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

    cout << "\nEnter the value of k: ";
    cin >> k;

    if(head == NULL || head->next == NULL || k == 0)
    {
        cout << "\nRotated Linked List: ";

        temp = head;

        while(temp != NULL)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }

        cout << endl;
    }
    else
    {
        int length = 0;

        current = head;

        while(current != NULL)
        {
            length++;
            current = current->next;
        }

        k = k % length;

        if(k == 0)
        {
            cout << "\nRotated Linked List: ";

            temp = head;

            while(temp != NULL)
            {
                cout << temp->data << " ";
                temp = temp->next;
            }

            cout << endl;
        }
        else
        {
            tail = head;

            while(tail->next != NULL)
            {
                tail = tail->next;
            }

            newTail = head;

            for(int i = 1; i < length - k; i++)
            {
                newTail = newTail->next;
            }

            head = newTail->next;
            newTail->next = NULL;
            tail->next = head;

            cout << "\nRotated Linked List: ";

            temp = head;

            while(temp != NULL)
            {
                cout << temp->data << " ";
                temp = temp->next;
            }

            cout << endl;
        }
    }

    return 0;
}