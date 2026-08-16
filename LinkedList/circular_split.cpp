#include<iostream>
using namespace std;

struct Node
{
    int data;
    Node* next;
};

void display(Node* head)
{
    if(head == NULL)
    {
        return;
    }

    Node* temp = head;

    do
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
    while(temp != head);
}

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

    if(head == NULL || head->next == head)
    {
        cout << "\nCannot split the list." << endl;
        return 0;
    }

    Node* slow = head;
    Node* fast = head;

    while(fast->next != head && fast->next->next != head)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    Node* head1 = head;
    Node* head2 = slow->next;

    Node* tail1 = slow;

    if(fast->next == head)
    {
        fast->next = head2;
    }
    else
    {
        fast->next->next = head2;
    }

    tail1->next = head1;

    cout << "\nFirst Circular List: ";
    display(head1);

    cout << "\nSecond Circular List: ";
    display(head2);

    cout << endl;

    return 0;
}