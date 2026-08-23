#include<iostream>
using namespace std;

#define MAX 100

int numStack[MAX];
char opStack[MAX];

int numTop = -1;
int opTop = -1;

void pushNum(int value)
{
    numTop++;
    numStack[numTop] = value;
}

int popNum()
{
    int value = numStack[numTop];
    numTop--;

    return value;
}

void pushOp(char value)
{
    opTop++;
    opStack[opTop] = value;
}

char popOp()
{
    char value = opStack[opTop];
    opTop--;

    return value;
}

char peekOp()
{
    return opStack[opTop];
}

int precedence(char op)
{
    if(op == '^')
        return 3;

    if(op == '*' || op == '/')
        return 2;

    if(op == '+' || op == '-')
        return 1;

    return 0;
}

int calculate(int first, int second, char op)
{
    if(op == '+')
        return first + second;

    if(op == '-')
        return first - second;

    if(op == '*')
        return first * second;

    if(op == '/')
        return first / second;

    return 0;
}

void solve()
{
    int second = popNum();
    int first = popNum();
    char op = popOp();

    int result = calculate(first, second, op);

    pushNum(result);
}

int main()
{
    string expression;

    cout << "Enter infix expression: ";
    cin >> expression;

    for(int i = 0; expression[i] != '\0'; i++)
    {
        char ch = expression[i];

        if(ch >= '0' && ch <= '9')
        {
            int number = 0;

            while(expression[i] >= '0' && expression[i] <= '9')
            {
                number = number * 10 + (expression[i] - '0');
                i++;
            }

            i--;

            pushNum(number);
        }

        else if(ch == '(')
        {
            pushOp(ch);
        }

        else if(ch == ')')
        {
            while(opTop != -1 && peekOp() != '(')
            {
                solve();
            }

            popOp();
        }

        else
        {
            while(opTop != -1 &&
                  peekOp() != '(' &&
                  precedence(peekOp()) >= precedence(ch))
            {
                solve();
            }

            pushOp(ch);
        }
    }

    while(opTop != -1)
    {
        solve();
    }

    cout << "Result: " << popNum() << endl;

    return 0;
}