#include <iostream>
#include <queue>
using namespace std;

int main()
{
    queue<int> q;
    queue<int> temp;
    queue<int> visited;

    int n, x;
    bool already;

    cout << "Enter number of elements: ";
    cin >> n;

    cout << "Enter elements: ";

    for (int i = 0; i < n; i++)
    {
        cin >> x;
        q.push(x);
    }

    temp = q;

    cout << "Frequency of elements:" << endl;

    while (!temp.empty())
    {
        x = temp.front();
        temp.pop();

        already = false;

        queue<int> check = visited;

        while (!check.empty())
        {
            if (check.front() == x)
            {
                already = true;
                break;
            }

            check.pop();
        }

        if (already)
        {
            continue;
        }

        int count = 0;

        queue<int> search = q;

        while (!search.empty())
        {
            if (search.front() == x)
            {
                count++;
            }

            search.pop();
        }

        cout << x << " -> " << count << endl;

        visited.push(x);
    }

    return 0;
}