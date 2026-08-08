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

    int n;
    bool duplicate;

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

    cout << "\nDuplicate Elements: ";

    current = head;

    while(current != NULL)
    {
        duplicate = false;
        check = head;

        while(check != current)
        {
            if(check->data == current->data)
            {
                duplicate = true;
                break;
            }

            check = check->next;
        }

        if(duplicate)
        {
            bool alreadyPrinted = false;
            check = head;

            while(check != current)
            {
                if(check->data == current->data)
                {
                    alreadyPrinted = true;
                    break;
                }

                check = check->next;
            }

            if(!alreadyPrinted)
            {
                cout << current->data << " ";
            }
        }

        current = current->next;
    }

    cout << endl;

    return 0;
}