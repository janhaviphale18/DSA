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
    Node* check = NULL;
    Node* prev = NULL;

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

    current = head;

    while(current != NULL)
    {
        prev = current;
        check = current->next;

        while(check != NULL)
        {
            if(check->data == current->data)
            {
                prev->next = check->next;
                delete check;
                check = prev->next;
            }
            else
            {
                prev = check;
                check = check->next;
            }
        }

        current = current->next;
    }

    cout << "\nLinked List after removing duplicates: ";

    temp = head;

    while(temp != NULL)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }

    cout << endl;

    return 0;
}