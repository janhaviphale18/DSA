#include<iostream>
using namespace std;

struct Node
{
    int data;
    Node* prev;
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

            head->next = head;
            head->prev = head;
        }
        else
        {
            newNode->prev = tail;
            newNode->next = head;

            tail->next = newNode;
            head->prev = newNode;

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
    Node* tail2 = tail;

    tail1->next = head1;
    head1->prev = tail1;

    tail2->next = head2;
    head2->prev = tail2;

    cout << "\nFirst Circular Doubly List: ";
    display(head1);

    cout << "\nSecond Circular Doubly List: ";
    display(head2);

    cout << endl;

    return 0;
}