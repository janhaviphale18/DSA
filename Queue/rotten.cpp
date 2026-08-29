#include <iostream>
#include <queue>
using namespace std;

int orangesRotting(int grid[][3], int rows, int cols)
{
    queue<pair<int, int>> q;

    int fresh = 0;
    int time = 0;

    // Store all rotten oranges
    // and count fresh oranges
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (grid[i][j] == 2)
            {
                q.push({i, j});
            }
            else if (grid[i][j] == 1)
            {
                fresh++;
            }
        }
    }

    int directions[4][2] =
    {
        {-1, 0},
        {1, 0},
        {0, -1},
        {0, 1}
    };

    while (!q.empty() && fresh > 0)
    {
        int size = q.size();

        for (int i = 0; i < size; i++)
        {
            int row = q.front().first;
            int col = q.front().second;

            q.pop();

            for (int j = 0; j < 4; j++)
            {
                int newRow = row + directions[j][0];
                int newCol = col + directions[j][1];

                if (newRow >= 0 && newRow < rows &&
                    newCol >= 0 && newCol < cols &&
                    grid[newRow][newCol] == 1)
                {
                    grid[newRow][newCol] = 2;
                    fresh--;

                    q.push({newRow, newCol});
                }
            }
        }

        time++;
    }

    if (fresh > 0)
    {
        return -1;
    }

    return time;
}

int main()
{
    int grid[3][3] =
    {
        {2, 1, 1},
        {1, 1, 0},
        {0, 1, 1}
    };

    int result = orangesRotting(grid, 3, 3);

    cout << "Minimum time: " << result << endl;

    return 0;
}