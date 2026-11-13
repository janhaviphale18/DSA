#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>
using namespace std;

const int INF = numeric_limits<int>::max();

struct Node
{
    int f;
    int g;
    int id;
};

struct Compare
{
    bool operator()(const Node &a, const Node &b) const
    {
        if (a.f != b.f)
        {
            return a.f > b.f;
        }

        if (a.g != b.g)
        {
            return a.g > b.g;
        }

        return a.id > b.id;
    }
};

int heuristic(int x, int y, int destX, int destY)
{
    return abs(x - destX) + abs(y - destY);
}

int main()
{
    int rows, cols;

    cout << "Enter number of rows: ";
    cin >> rows;

    if (cin.fail() || rows <= 0 || rows > 1000)
    {
        cout << "Invalid number of rows.\n";
        return 0;
    }

    cout << "Enter number of columns: ";
    cin >> cols;

    if (cin.fail() || cols <= 0 || cols > 1000 ||
        1LL * rows * cols > 1000000)
    {
        cout << "Invalid number of columns or grid size.\n";
        return 0;
    }

    vector<vector<int>> grid(rows, vector<int>(cols));

    cout << "\nEnter the grid (0 = Free, 1 = Blocked):\n";

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cin >> grid[i][j];

            if (cin.fail() ||
                (grid[i][j] != 0 && grid[i][j] != 1))
            {
                cout << "Invalid grid value. Enter only 0 or 1.\n";
                return 0;
            }
        }
    }

    int startX, startY;
    int destX, destY;

    cout << "\nEnter starting cell coordinates (row column): ";
    cin >> startX >> startY;

    if (cin.fail() || startX < 0 || startX >= rows ||
        startY < 0 || startY >= cols)
    {
        cout << "Invalid starting coordinates.\n";
        return 0;
    }

    cout << "Enter destination cell coordinates (row column): ";
    cin >> destX >> destY;

    if (cin.fail() || destX < 0 || destX >= rows ||
        destY < 0 || destY >= cols)
    {
        cout << "Invalid destination coordinates.\n";
        return 0;
    }

    if (grid[startX][startY] == 1 ||
        grid[destX][destY] == 1)
    {
        cout << "Starting and destination cells must be free.\n";
        return 0;
    }

    int totalCells = rows * cols;

    auto getId = [&](int x, int y)
    {
        return x * cols + y;
    };

    auto getRow = [&](int id)
    {
        return id / cols;
    };

    auto getCol = [&](int id)
    {
        return id % cols;
    };

    int source = getId(startX, startY);
    int destination = getId(destX, destY);

    vector<int> distance(totalCells, INF);
    vector<int> parent(totalCells, -1);

    priority_queue<Node, vector<Node>, Compare> pq;

    distance[source] = 0;

    int initialH = heuristic(
        startX, startY, destX, destY
    );

    pq.push({initialH, 0, source});

    // Four possible movement directions.

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    bool found = false;

    cout << "\n================================\n";
    cout << "A* Search Execution\n";
    cout << "================================\n";

    while (!pq.empty())
    {
        Node current = pq.top();
        pq.pop();

        int u = current.id;
        int x = getRow(u);
        int y = getCol(u);

        // Ignore outdated priority queue entries.

        if (current.g != distance[u])
        {
            continue;
        }

        cout << "Processing cell (" << x << ", " << y << ")"
             << " | g = " << current.g
             << " | h = "
             << heuristic(x, y, destX, destY)
             << " | f = " << current.f << "\n";

        if (u == destination)
        {
            found = true;
            break;
        }

        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];

            // Check grid boundaries.

            if (nx < 0 || nx >= rows ||
                ny < 0 || ny >= cols)
            {
                continue;
            }

            // Ignore blocked cells.

            if (grid[nx][ny] == 1)
            {
                continue;
            }

            int v = getId(nx, ny);

            int newG = distance[u] + 1;

            if (newG < distance[v])
            {
                distance[v] = newG;
                parent[v] = u;

                int h = heuristic(
                    nx, ny, destX, destY
                );

                int newF = newG + h;

                pq.push({newF, newG, v});

                cout << "Updated cell (" << nx << ", " << ny
                     << ") | g = " << newG
                     << " | h = " << h
                     << " | f = " << newF << "\n";
            }
        }
    }

    cout << "\n================================\n";

    if (!found)
    {
        cout << "No path exists between the starting "
             << "cell and destination.\n";

        return 0;
    }

    // Reconstruct the shortest path.

    vector<int> path;

    int current = destination;

    while (current != -1)
    {
        path.push_back(current);

        if (current == source)
        {
            break;
        }

        current = parent[current];
    }

    if (path.back() != source)
    {
        cout << "Path reconstruction failed.\n";
        return 0;
    }

    reverse(path.begin(), path.end());

    // Mark the path in the grid.

    vector<vector<char>> display(
        rows, vector<char>(cols, '.')
    );

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (grid[i][j] == 1)
            {
                display[i][j] = '#';
            }
        }
    }

    for (int id : path)
    {
        int x = getRow(id);
        int y = getCol(id);

        display[x][y] = '*';
    }

    display[startX][startY] = 'S';
    display[destX][destY] = 'D';

    cout << "Shortest Path:\n";

    for (int id : path)
    {
        cout << "(" << getRow(id)
             << ", " << getCol(id) << ")";

        if (id != destination)
        {
            cout << " -> ";
        }
    }

    cout << "\n\nPath Visualization:\n";

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << display[i][j] << " ";
        }

        cout << "\n";
    }

    cout << "\nMinimum Path Cost: "
         << distance[destination] << "\n";

    cout << "Number of Moves: "
         << path.size() - 1 << "\n";

    cout << "================================\n";

    return 0;
}
