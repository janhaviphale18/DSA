#include <iostream>
#include <queue>
using namespace std;

void firstNonRepeating(string str)
{
    int frequency[256] = {0};
    queue<char> q;

    for (int i = 0; i < str.length(); i++)
    {
        char ch = str[i];

        frequency[ch]++;
        q.push(ch);

        while (!q.empty() && frequency[q.front()] > 1)
        {
            q.pop();
        }

        cout << "After " << ch << ": ";

        if (q.empty())
        {
            cout << -1 << endl;
        }
        else
        {
            cout << q.front() << endl;
        }
    }
}

int main()
{
    string str = "aabc";

    firstNonRepeating(str);

    return 0;
}