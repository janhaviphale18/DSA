#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

// Reconstruct the cycle using DFS parent information
vector<int> buildCycle(
    int u,
    int v,
    const vector<int>& parent,
    int V)
{
    vector<int> pathU;
    vector<int> pathV;
    vector<int> position(V, -1);

    int current = u;

    // Store ancestors of u
    while (current != -1)
    {
        position[current] = pathU.size();
        pathU.push_back(current);
        current = parent[current];
    }

    current = v;

    // Store ancestors of v
    while (current != -1)
    {
        pathV.push_back(current);
        current = parent[current];
    }

    // Find lowest common ancestor
    int lca = -1;

    for (int vertex : pathV)
    {
        if (position[vertex] != -1)
        {
            lca = vertex;
            break;
        }
    }

    vector<int> cycle;

    // Path from LCA to u
    for (int i = position[lca]; i >= 0; i--)
    {
        cycle.push_back(pathU[i]);
    }

    // Add the cycle-forming edge
    cycle.push_back(v);

    // Path from v back to LCA
    int i = 1;

    while (pathV[i] != lca)
    {
        cycle.push_back(pathV[i]);
        i++;
    }

    cycle.push_back(lca);

    return cycle;
}

// Recursive DFS cycle detection
bool dfsCycleUtil(
    int current,
    int parentVertex,
    vector<vector<int>>& adj,
    vector<bool>& visited,
    vector<int>& parent,
    vector<int>& cycle)
{
    visited[current] = true;

    for (int neighbour : adj[current])
    {
        if (!visited[neighbour])
        {
            parent[neighbour] = current;

            if (dfsCycleUtil(
                neighbour,
                current,
                adj,
                visited,
                parent,
                cycle))
            {
                return true;
            }
        }
        else if (neighbour != parentVertex)
        {
            cycle = buildCycle(
                current,
                neighbour,
                parent,
                adj.size()
            );

            return true;
        }
    }

    return false;
}

// Check all disconnected components
bool detectCycleDFS(vector<vector<int>>& adj, int V)
{
    vector<bool> visited(V, false);
    vector<int> parent(V, -1);
    vector<int> cycle;

    for (int i = 0; i < V; i++)
    {
        if (!visited[i])
        {
            if (dfsCycleUtil(
                i,
                -1,
                adj,
                visited,
                parent,
                cycle))
            {
                cout << "\nCycle detected!\n";
                cout << "Cycle: ";

                for (int j = 0; j < cycle.size(); j++)
                {
                    cout << cycle[j];

                    if (j != cycle.size() - 1)
                        cout << " -> ";
                }

                cout << "\nCycle length: "
                     << cycle.size() - 1 << " edges\n";

                return true;
            }
        }
    }

    return false;
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

    cout << "\nCycle Detection Using DFS:\n";

    bool hasCycle = detectCycleDFS(adj, V);

    if (!hasCycle)
        cout << "No cycle exists in the graph.\n";

    return 0;
}
