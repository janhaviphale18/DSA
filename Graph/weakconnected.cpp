#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
using namespace std;

// Find weakly connected components using BFS
vector<vector<int>> findComponentsBFS(
    vector<vector<int>>& weakAdj,
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

            for (int neighbour : weakAdj[current])
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
    vector<vector<int>>& weakAdj,
    vector<bool>& visited,
    vector<int>& component)
{
    visited[current] = true;
    component.push_back(current);

    for (int neighbour : weakAdj[current])
    {
        if (!visited[neighbour])
        {
            dfs(neighbour, weakAdj, visited, component);
        }
    }
}

// Find weakly connected components using DFS
vector<vector<int>> findComponentsDFS(
    vector<vector<int>>& weakAdj,
    int V)
{
    vector<bool> visited(V, false);
    vector<vector<int>> components;

    for (int i = 0; i < V; i++)
    {
        if (!visited[i])
        {
            vector<int> component;

            dfs(i, weakAdj, visited, component);

            sort(component.begin(), component.end());
            components.push_back(component);
        }
    }

    return components;
}

// Display components
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

    long long maxEdges = 1LL * V * (V - 1);

    cout << "Enter number of directed edges: ";
    cin >> E;

    if (E < 0 || E > maxEdges)
    {
        cout << "Invalid number of edges.\n";
        return 0;
    }

    // Original directed adjacency list
    vector<vector<int>> directedAdj(V);

    // Adjacency list for weak connectivity
    vector<vector<int>> weakAdj(V);

    // Detect duplicate directed edges
    set<pair<int, int>> directedEdges;

    // Avoid duplicate connections in weak adjacency list
    set<pair<int, int>> weakEdges;

    cout << "Enter directed edges (u v):\n";

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

        if (directedEdges.find({u, v}) != directedEdges.end())
        {
            cout << "Duplicate directed edge. Enter again.\n";
            i--;
            continue;
        }

        directedEdges.insert({u, v});

        // Store original directed edge
        directedAdj[u].push_back(v);

        // Normalize the edge for weak connectivity
        pair<int, int> edge = {min(u, v), max(u, v)};

        if (weakEdges.insert(edge).second)
        {
            weakAdj[u].push_back(v);
            weakAdj[v].push_back(u);
        }
    }

    // Display original directed graph
    cout << "\nDirected Adjacency List:\n";

    for (int i = 0; i < V; i++)
    {
        cout << i << " -> ";

        for (int neighbour : directedAdj[i])
            cout << neighbour << " ";

        cout << "\n";
    }

    // Display weak adjacency list
    cout << "\nAdjacency List Ignoring Directions:\n";

    for (int i = 0; i < V; i++)
    {
        cout << i << " -> ";

        for (int neighbour : weakAdj[i])
            cout << neighbour << " ";

        cout << "\n";
    }

    // Find components using BFS
    vector<vector<int>> bfsComponents =
        findComponentsBFS(weakAdj, V);

    // Find components using DFS
    vector<vector<int>> dfsComponents =
        findComponentsDFS(weakAdj, V);

    cout << "\nWeakly Connected Components Using BFS:\n";
    displayComponents(bfsComponents);

    cout << "\nWeakly Connected Components Using DFS:\n";
    displayComponents(dfsComponents);

    cout << "\nConnectivity Result:\n";

    if (bfsComponents.size() == 1)
        cout << "The directed graph is weakly connected.\n";
    else
        cout << "The directed graph is weakly disconnected.\n";

    cout << "\nComparison:\n";

    if (compareComponents(bfsComponents, dfsComponents))
        cout << "BFS and DFS identified the same components.\n";
    else
        cout << "BFS and DFS results differ.\n";

    // Find isolated vertices in the weak graph
    cout << "\nIsolated Vertices:\n";

    bool found = false;

    for (int i = 0; i < V; i++)
    {
        if (weakAdj[i].empty())
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
