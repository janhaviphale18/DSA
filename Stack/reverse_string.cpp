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
    string reversed = "";

    cout << "Enter string: ";
    cin >> str;

    for(int i = 0; str[i] != '\0'; i++)
    {
        push(str[i]);
    }

    while(top != -1)
    {
        reversed += pop();
    }

    cout << "Original String: " << str << endl;
    cout << "Reversed String: " << reversed << endl;

    return 0;
}