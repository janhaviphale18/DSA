#include <iostream>
#include <queue>
using namespace std;

void generateBinary(int n)
{
    queue<string> q;

    q.push("1");

    cout << "Binary numbers: ";

    for (int i = 1; i <= n; i++)
    {
        string current = q.front();
        q.pop();

        cout << current << " ";

        q.push(current + "0");
        q.push(current + "1");
    }

    cout << endl;
}

int main()
{
    int n = 5;

    generateBinary(n);

    return 0;
}