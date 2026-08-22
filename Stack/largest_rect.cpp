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
    int height[MAX];

    cout << "Enter number of bars: ";
    cin >> n;

    cout << "Enter heights: ";

    for(int i = 0; i < n; i++)
    {
        cin >> height[i];
    }

    int maxArea = 0;

    for(int i = 0; i <= n; i++)
    {
        int currentHeight;

        if(i == n)
        {
            currentHeight = 0;
        }
        else
        {
            currentHeight = height[i];
        }

        while(top != -1 && height[peek()] > currentHeight)
        {
            int h = height[pop()];

            int width;

            if(top == -1)
            {
                width = i;
            }
            else
            {
                width = i - peek() - 1;
            }

            int area = h * width;

            if(area > maxArea)
            {
                maxArea = area;
            }
        }

        push(i);
    }

    cout << "Largest Rectangle Area: " << maxArea << endl;

    return 0;
}