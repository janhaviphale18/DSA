#include<iostream>
using namespace std;

#define MAX 100

char stack[MAX];
int top = -1;

void push(char value)
{
    top++;
    stack[top] = value;
}

char pop()
{
    char value = stack[top];
    top--;

    return value;
}

int main()
{
    string str;

    cout << "Enter string: ";
    cin >> str;

    for(int i = 0; str[i] != '\0'; i++)
    {
        push(str[i]);
    }

    for(int i = 0; str[i] != '\0'; i++)
    {
        if(str[i] != pop())
        {
            cout << "Not a Palindrome" << endl;
            return 0;
        }
    }

    cout << "Palindrome" << endl;

    return 0;
}