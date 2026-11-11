#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
using namespace std;

// Find connected components using BFS
vector<vector<int>> findComponentsBFS(
    vector<vector<int>>& adj,
    int V)
{
    vector<bool> visited(V, false);
    vector<vector<int>> components;

    for (int start = 0; start < V; start++)
    {
        if (visited[start])
            continue;

        vector<int> component;
        queue<int> q;

        visited[start] = true;
        q.push(start);

        while (!q.empty())
        {
            int current = q.front();
            q.pop();

            component.push_back(current);

            for (int neighbour : adj[current])
            {
                if (!visited[neighbour])
                {
                    visited[neighbour] = true;
                    q.push(neighbour);
                }
            }
        }

        sort(component.begin(), component.end());
        components.push_back(component);
    }

    return components;
}

// Recursive DFS
void dfs(
    int current,
    vector<vector<int>>& adj,
    vector<bool>& visited,
    vector<int>& component)
{
    visited[current] = true;
    component.push_back(current);

    for (int neighbour : adj[current])
    {
        if (!visited[neighbour])
        {
            dfs(neighbour, adj, visited, component);
        }
    }
}

// Find connected components using DFS
vector<vector<int>> findComponentsDFS(
    vector<vector<int>>& adj,
    int V)
{
    vector<bool> visited(V, false);
    vector<vector<int>> components;

    for (int i = 0; i < V; i++)
    {
        if (!visited[i])
        {
            vector<int> component;

            dfs(i, adj, visited, component);

            sort(component.begin(), component.end());
            components.push_back(component);
        }
    }

    return components;
}

// Display connected components
void displayComponents(
    const vector<vector<int>>& components)
{
    for (int i = 0; i < components.size(); i++)
    {
        cout << "Component " << i + 1 << ": ";

        for (int vertex : components[i])
            cout << vertex << " ";

        cout << "\n";
    }
}

// Compare BFS and DFS component partitions
bool compareComponents(
    vector<vector<int>> bfs,
    vector<vector<int>> dfs)
{
    if (bfs.size() != dfs.size())
        return false;

    sort(bfs.begin(), bfs.end());
    sort(dfs.begin(), dfs.end());

    return bfs == dfs;
}

int main()
{
    int V, E;

    cout << "Enter number of vertices: ";
    cin >> V;

    if (V <= 0)
    {
        cout << "Invalid number of vertices.\n";
        return 0;
    }

    long long maxEdges = 1LL * V * (V - 1) / 2;

    cout << "Enter number of edges: ";
    cin >> E;

    if (E < 0 || E > maxEdges)
    {
        cout << "Invalid number of edges.\n";
        return 0;
    }

    vector<vector<int>> adj(V);
    set<pair<int, int>> edges;

    cout << "Enter edges (u v):\n";

    for (int i = 0; i < E; i++)
    {
        int u, v;
        cin >> u >> v;

        if (u < 0 || u >= V || v < 0 || v >= V)
        {
            cout << "Invalid vertex. Enter again.\n";
            i--;
            continue;
        }

        if (u == v)
        {
            cout << "Self-loops are not allowed. Enter again.\n";
            i--;
            continue;
        }

        pair<int, int> edge = {min(u, v), max(u, v)};

        if (edges.find(edge) != edges.end())
        {
            cout << "Duplicate edge. Enter again.\n";
            i--;
            continue;
        }

        edges.insert(edge);

        adj[u].push_back(v);
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

    // BFS connectivity check
    vector<vector<int>> bfsComponents =
        findComponentsBFS(adj, V);

    // DFS connectivity check
    vector<vector<int>> dfsComponents =
        findComponentsDFS(adj, V);

    cout << "\nBFS Connected Components:\n";
    displayComponents(bfsComponents);

    cout << "\nDFS Connected Components:\n";
    displayComponents(dfsComponents);

    cout << "\nConnectivity Results:\n";

    if (bfsComponents.size() == 1)
        cout << "BFS: Graph is connected.\n";
    else
        cout << "BFS: Graph is disconnected.\n";

    if (dfsComponents.size() == 1)
        cout << "DFS: Graph is connected.\n";
    else
        cout << "DFS: Graph is disconnected.\n";

    cout << "\nComparison:\n";

    if (compareComponents(bfsComponents, dfsComponents))
        cout << "BFS and DFS identified the same components.\n";
    else
        cout << "BFS and DFS results differ.\n";

    // Display isolated vertices
    cout << "\nIsolated Vertices:\n";

    bool found = false;

    for (int i = 0; i < V; i++)
    {
        if (adj[i].empty())
        {
            cout << i << " ";
            found = true;
        }
    }

    if (!found)
        cout << "None";

    cout << "\n";

    return 0;
}
