#include<iostream>
using namespace std;

#define MAX 100

int stack[MAX];
int top = -1;

void push(int value)
{
    top++;
    stack[top] = value;
}

int pop()
{
    int value = stack[top];
    top--;

    return value;
}

int peek()
{
    return stack[top];
}

int main()
{
    int n;
    int arr[MAX];
    int result[MAX];

    cout << "Enter number of elements: ";
    cin >> n;

    cout << "Enter elements: ";

    for(int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    for(int i = n - 1; i >= 0; i--)
    {
        while(top != -1 && peek() <= arr[i])
        {
            pop();
        }

        if(top == -1)
        {
            result[i] = -1;
        }
        else
        {
            result[i] = peek();
        }

        push(arr[i]);
    }

    cout << "Next Greater Elements: ";

    for(int i = 0; i < n; i++)
    {
        cout << result[i] << " ";
    }

    cout << endl;

    return 0;
}