#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// BFS to find the shortest path
vector<int> bfsPath(vector<vector<int>>& adj, int source, int destination)
{
    int V = adj.size();

    vector<bool> visited(V, false);
    vector<int> parent(V, -1);

    queue<int> q;

    visited[source] = true;
    q.push(source);

    while (!q.empty())
    {
        int current = q.front();
        q.pop();

        if (current == destination)
            break;

        for (int neighbour : adj[current])
        {
            if (!visited[neighbour])
            {
                visited[neighbour] = true;
                parent[neighbour] = current;
                q.push(neighbour);
            }
        }
    }

    vector<int> path;

    if (!visited[destination])
        return path;

    int current = destination;

    while (current != -1)
    {
        path.push_back(current);
        current = parent[current];
    }

    reverse(path.begin(), path.end());

    return path;
}

// DFS to find a path
bool dfsPathUtil(
    vector<vector<int>>& adj,
    int current,
    int destination,
    vector<bool>& visited,
    vector<int>& path)
{
    visited[current] = true;
    path.push_back(current);

    if (current == destination)
        return true;

    for (int neighbour : adj[current])
    {
        if (!visited[neighbour])
        {
            if (dfsPathUtil(adj, neighbour, destination, visited, path))
                return true;
        }
    }

    // Backtrack if this route does not reach destination
    path.pop_back();

    return false;
}

vector<int> dfsPath(vector<vector<int>>& adj, int source, int destination)
{
    int V = adj.size();

    vector<bool> visited(V, false);
    vector<int> path;

    dfsPathUtil(adj, source, destination, visited, path);

    return path;
}

// Display path
void displayPath(const vector<int>& path)
{
    if (path.empty())
    {
        cout << "No path exists.\n";
        return;
    }

    for (int i = 0; i < path.size(); i++)
    {
        cout << path[i];

        if (i != path.size() - 1)
            cout << " -> ";
    }

    cout << "\n";
}

int main()
{
    int V, E, choice;

    cout << "Enter number of vertices: ";
    cin >> V;

    if (V <= 0)
    {
        cout << "Invalid number of vertices.\n";
        return 0;
    }

    cout << "Enter 1 for Undirected Graph\n";
    cout << "Enter 2 for Directed Graph\n";
    cout << "Enter graph type: ";
    cin >> choice;

    if (choice != 1 && choice != 2)
    {
        cout << "Invalid graph type.\n";
        return 0;
    }

    cout << "Enter number of edges: ";
    cin >> E;

    if (E < 0 || (choice == 1 && E > V * (V - 1) / 2) ||
        (choice == 2 && E > V * (V - 1)))
    {
        cout << "Invalid number of edges.\n";
        return 0;
    }

    vector<vector<int>> adj(V);

    cout << "Enter edges (u v):\n";

    for (int i = 0; i < E; i++)
    {
        int u, v;

        cin >> u >> v;

        if (u < 0 || u >= V || v < 0 || v >= V)
        {
            cout << "Invalid vertex. Enter this edge again.\n";
            i--;
            continue;
        }

        if (u == v)
        {
            cout << "Self-loops are not allowed. Enter again.\n";
            i--;
            continue;
        }

        bool duplicate = false;

        for (int neighbour : adj[u])
        {
            if (neighbour == v)
            {
                duplicate = true;
                break;
            }
        }

        if (duplicate)
        {
            cout << "Duplicate edge. Enter again.\n";
            i--;
            continue;
        }

        adj[u].push_back(v);

        if (choice == 1)
            adj[v].push_back(u);
    }

    cout << "\nAdjacency List:\n";

    for (int i = 0; i < V; i++)
    {
        cout << i << " -> ";

        for (int neighbour : adj[i])
            cout << neighbour << " ";

        cout << "\n";
    }

    int source, destination;

    cout << "\nEnter source vertex: ";
    cin >> source;

    cout << "Enter destination vertex: ";
    cin >> destination;

    if (source < 0 || source >= V ||
        destination < 0 || destination >= V)
    {
        cout << "Invalid source or destination.\n";
        return 0;
    }

    // BFS
    vector<int> bfsResult = bfsPath(adj, source, destination);

    cout << "\nBFS Result:\n";

    if (bfsResult.empty())
    {
        cout << "No path exists between "
             << source << " and " << destination << ".\n";
    }
    else
    {
        cout << "Path exists: ";
        displayPath(bfsResult);

        cout << "Shortest path length: "
             << bfsResult.size() - 1 << " edges\n";
    }

    // DFS
    vector<int> dfsResult = dfsPath(adj, source, destination);

    cout << "\nDFS Result:\n";

    if (dfsResult.empty())
    {
        cout << "No path exists between "
             << source << " and " << destination << ".\n";
    }
    else
    {
        cout << "Path exists: ";
        displayPath(dfsResult);

        cout << "Path length: "
             << dfsResult.size() - 1 << " edges\n";
    }

    return 0;
}
