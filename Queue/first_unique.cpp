#include <iostream>
#include <queue>
using namespace std;

int main()
{
    queue<int> q;

    int n, x;
    int freq[1000] = {0};

    cout << "Enter number of elements: ";
    cin >> n;

    cout << "Enter stream elements: ";

    for (int i = 0; i < n; i++)
    {
        cin >> x;

        freq[x]++;
        q.push(x);

        while (!q.empty() && freq[q.front()] > 1)
        {
            q.pop();
        }

        if (q.empty())
        {
            cout << -1 << " ";
        }
        else
        {
            cout << q.front() << " ";
        }
    }

    return 0;
}