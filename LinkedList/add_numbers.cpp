#include<iostream>
using namespace std;

struct Node
{
    int data;
    Node* next;
};

int main()
{
    Node* head1 = NULL;
    Node* head2 = NULL;

    Node* temp = NULL;
    Node* newNode = NULL;

    Node* current1 = NULL;
    Node* current2 = NULL;

    Node* resultHead = NULL;
    Node* resultTail = NULL;

    int n1, n2;

    cout << "Enter the number of nodes in List 1: ";
    cin >> n1;

    for(int i = 1; i <= n1; i++)
    {
        newNode = new Node;

        cout << "Enter digit " << i << " for List 1: ";
        cin >> newNode->data;

        newNode->next = NULL;

        if(head1 == NULL)
        {
            head1 = newNode;
            temp = newNode;
        }
        else
        {
            temp->next = newNode;
            temp = newNode;
        }
    }

    cout << "\nEnter the number of nodes in List 2: ";
    cin >> n2;

    for(int i = 1; i <= n2; i++)
    {
        newNode = new Node;

        cout << "Enter digit " << i << " for List 2: ";
        cin >> newNode->data;

        newNode->next = NULL;

        if(head2 == NULL)
        {
            head2 = newNode;
            temp = newNode;
        }
        else
        {
            temp->next = newNode;
            temp = newNode;
        }
    }

    current1 = head1;
    current2 = head2;

    int carry = 0;

    while(current1 != NULL || current2 != NULL || carry != 0)
    {
        int sum = carry;

        if(current1 != NULL)
        {
            sum = sum + current1->data;
            current1 = current1->next;
        }

        if(current2 != NULL)
        {
            sum = sum + current2->data;
            current2 = current2->next;
        }

        int digit = sum % 10;
        carry = sum / 10;

        newNode = new Node;
        newNode->data = digit;
        newNode->next = NULL;

        if(resultHead == NULL)
        {
            resultHead = newNode;
            resultTail = newNode;
        }
        else
        {
            resultTail->next = newNode;
            resultTail = newNode;
        }
    }

    cout << "\nSum Linked List: ";

    temp = resultHead;

    while(temp != NULL)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }

    cout << endl;

    return 0;
}