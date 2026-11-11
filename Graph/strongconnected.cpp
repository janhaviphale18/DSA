#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <set>
using namespace std;

// First DFS: store vertices by finishing time
void dfsFirst(
    int current,
    vector<vector<int>>& adj,
    vector<bool>& visited,
    stack<int>& finishStack)
{
    visited[current] = true;

    for (int neighbour : adj[current])
    {
        if (!visited[neighbour])
        {
            dfsFirst(neighbour, adj, visited, finishStack);
        }
    }

    // Store vertex after exploring all neighbours
    finishStack.push(current);
}

// Second DFS: collect one SCC in transpose graph
void dfsSecond(
    int current,
    vector<vector<int>>& transpose,
    vector<bool>& visited,
    vector<int>& component)
{
    visited[current] = true;
    component.push_back(current);

    for (int neighbour : transpose[current])
    {
        if (!visited[neighbour])
        {
            dfsSecond(neighbour, transpose, visited, component);
        }
    }
}

// Kosaraju's algorithm
vector<vector<int>> findSCCs(
    vector<vector<int>>& adj,
    int V)
{
    vector<bool> visited(V, false);
    stack<int> finishStack;

    // Step 1: First DFS on original graph
    for (int i = 0; i < V; i++)
    {
        if (!visited[i])
        {
            dfsFirst(i, adj, visited, finishStack);
        }
    }

    // Step 2: Create transpose graph
    vector<vector<int>> transpose(V);

    for (int u = 0; u < V; u++)
    {
        for (int v : adj[u])
        {
            transpose[v].push_back(u);
        }
    }

    // Reset visited array
    fill(visited.begin(), visited.end(), false);

    vector<vector<int>> components;

    // Step 3: Second DFS in finishing order
    while (!finishStack.empty())
    {
        int current = finishStack.top();
        finishStack.pop();

        if (!visited[current])
        {
            vector<int> component;

            dfsSecond(
                current,
                transpose,
                visited,
                component
            );

            sort(component.begin(), component.end());

            components.push_back(component);
        }
    }

    return components;
}

// Display SCCs
void displaySCCs(const vector<vector<int>>& components)
{
    for (int i = 0; i < components.size(); i++)
    {
        cout << "SCC " << i + 1 << ": ";

        for (int vertex : components[i])
        {
            cout << vertex << " ";
        }

        cout << "\n";
    }
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

    vector<vector<int>> adj(V);

    set<pair<int, int>> edges;

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

        if (edges.find({u, v}) != edges.end())
        {
            cout << "Duplicate directed edge. Enter again.\n";
            i--;
            continue;
        }

        edges.insert({u, v});

        adj[u].push_back(v);
    }

    // Display original graph
    cout << "\nOriginal Directed Graph:\n";

    for (int i = 0; i < V; i++)
    {
        cout << i << " -> ";

        for (int neighbour : adj[i])
        {
            cout << neighbour << " ";
        }

        cout << "\n";
    }

    // Find SCCs
    vector<vector<int>> components = findSCCs(adj, V);

    cout << "\nStrongly Connected Components:\n";

    displaySCCs(components);

    cout << "\nTotal Strongly Connected Components: "
         << components.size() << "\n";

    cout << "\nConnectivity Result:\n";

    if (components.size() == 1)
    {
        cout << "The graph is strongly connected.\n";
    }
    else
    {
        cout << "The graph is NOT strongly connected.\n";
    }

    // Display SCC sizes
    cout << "\nSize of Each SCC:\n";

    for (int i = 0; i < components.size(); i++)
    {
        cout << "SCC " << i + 1 << ": "
             << components[i].size() << " vertices\n";
    }

    return 0;
}
