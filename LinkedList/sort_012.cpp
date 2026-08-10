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

    Node* zeroHead = NULL;
    Node* zeroTail = NULL;

    Node* oneHead = NULL;
    Node* oneTail = NULL;

    Node* twoHead = NULL;
    Node* twoTail = NULL;

    int n;

    cout << "Enter the number of nodes: ";
    cin >> n;

    for(int i = 1; i <= n; i++)
    {
        newNode = new Node;

        cout << "Enter data for node " << i << " (0, 1 or 2): ";
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

    temp = head;

    while(temp != NULL)
    {
        if(temp->data == 0)
        {
            if(zeroHead == NULL)
            {
                zeroHead = temp;
                zeroTail = temp;
            }
            else
            {
                zeroTail->next = temp;
                zeroTail = temp;
            }
        }
        else if(temp->data == 1)
        {
            if(oneHead == NULL)
            {
                oneHead = temp;
                oneTail = temp;
            }
            else
            {
                oneTail->next = temp;
                oneTail = temp;
            }
        }
        else
        {
            if(twoHead == NULL)
            {
                twoHead = temp;
                twoTail = temp;
            }
            else
            {
                twoTail->next = temp;
                twoTail = temp;
            }
        }

        temp = temp->next;
    }

    if(zeroHead != NULL)
    {
        head = zeroHead;

        if(oneHead != NULL)
        {
            zeroTail->next = oneHead;
        }
        else
        {
            zeroTail->next = twoHead;
        }
    }
    else if(oneHead != NULL)
    {
        head = oneHead;
    }
    else
    {
        head = twoHead;
    }

    if(oneHead != NULL)
    {
        if(twoHead != NULL)
        {
            oneTail->next = twoHead;
        }
        else
        {
            oneTail->next = NULL;
        }
    }

    if(twoTail != NULL)
    {
        twoTail->next = NULL;
    }

    cout << "\nSorted Linked List: ";

    temp = head;

    while(temp != NULL)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }

    cout << endl;

    return 0;
}