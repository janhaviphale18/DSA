#include <iostream>
#include <queue>
using namespace std;

void generate(int n)
{
    queue<int> q;

    for (int i = 1; i <= n; i++)
    {
        q.push(i);
    }

    cout << "Queue: ";

    while (!q.empty())
    {
        cout << q.front() << " ";
        q.pop();
    }

    cout << endl;
}

int main()
{
    int n = 5;

    generate(n);

    return 0;
}