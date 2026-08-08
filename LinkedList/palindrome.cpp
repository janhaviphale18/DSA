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

    int n;
    bool palindrome = true;

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

    int size = 0;

    temp = head;

    while(temp != NULL)
    {
        size++;
        temp = temp->next;
    }

    int* arr = new int[size];

    temp = head;

    int i = 0;

    while(temp != NULL)
    {
        arr[i] = temp->data;
        i++;
        temp = temp->next;
    }

    int start = 0;
    int end = size - 1;

    while(start < end)
    {
        if(arr[start] != arr[end])
        {
            palindrome = false;
            break;
        }

        start++;
        end--;
    }

    if(palindrome)
    {
        cout << "\nLinked List is a Palindrome." << endl;
    }
    else
    {
        cout << "\nLinked List is not a Palindrome." << endl;
    }

    delete[] arr;

    return 0;
}