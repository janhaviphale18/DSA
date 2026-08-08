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

    Node* common = NULL;
    Node* current1 = NULL;
    Node* current2 = NULL;

    int n1, n2, commonPosition;

    cout << "Enter the number of nodes in List 1: ";
    cin >> n1;

    for(int i = 1; i <= n1; i++)
    {
        newNode = new Node;

        cout << "Enter data for List 1 node " << i << ": ";
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

        cout << "Enter data for List 2 node " << i << ": ";
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

    cout << "\nEnter the position in List 1 where intersection starts: ";
    cin >> commonPosition;

    if(commonPosition >= 1 && commonPosition <= n1)
    {
        common = head1;

        for(int i = 1; i < commonPosition; i++)
        {
            common = common->next;
        }

        temp = head2;

        while(temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = common;
    }

    current1 = head1;

    while(current1 != NULL)
    {
        current2 = head2;

        while(current2 != NULL)
        {
            if(current1 == current2)
            {
                cout << "\nIntersection Point = "
                     << current1->data << endl;

                return 0;
            }

            current2 = current2->next;
        }

        current1 = current1->next;
    }

    cout << "\nNo Intersection." << endl;

    return 0;
}