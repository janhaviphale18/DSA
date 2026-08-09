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

    if(k <= 0)
    {
        cout << "\nInvalid value of k." << endl;
    }
    else
    {
        Node* current = head;
        Node* previous = NULL;
        Node* next = NULL;

        Node* groupStart = NULL;
        Node* groupEnd = NULL;
        Node* newHead = NULL;
        Node* lastEnd = NULL;

        while(current != NULL)
        {
            groupStart = current;
            previous = NULL;

            for(int i = 0; i < k && current != NULL; i++)
            {
                next = current->next;
                current->next = previous;
                previous = current;
                current = next;
            }

            groupEnd = groupStart;

            if(newHead == NULL)
            {
                newHead = previous;
            }
            else
            {
                lastEnd->next = previous;
            }

            lastEnd = groupEnd;
        }

        head = newHead;

        cout << "\nLinked List after reversing in groups of "
             << k << ": ";

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