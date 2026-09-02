#include <iostream>
#include <queue>
using namespace std;

int main()
{
    queue<int> q;

    int n, k;

    cout << "Enter number of people: ";
    cin >> n;

    cout << "Enter value of k: ";
    cin >> k;

    for (int i = 1; i <= n; i++)
    {
        q.push(i);
    }

    while (q.size() > 1)
    {
        for (int i = 1; i < k; i++)
        {
            q.push(q.front());
            q.pop();
        }

        cout << "Eliminated: " << q.front() << endl;
        q.pop();
    }

    cout << "Survivor: " << q.front();

    return 0;
}