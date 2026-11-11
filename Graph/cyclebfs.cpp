#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
using namespace std;

// Reconstruct the cycle using BFS parent information
vector<int> buildCycle(
    int u,
    int v,
    const vector<int>& parent,
    int V)
{
    vector<int> pathU;
    vector<int> pathV;
    vector<int> position(V, -1);

    // Store the path from u to the BFS root
    int current = u;

    while (current != -1)
    {
        position[current] = pathU.size();
        pathU.push_back(current);
        current = parent[current];
    }

    // Store the path from v to the BFS root
    current = v;

    while (current != -1)
    {
        pathV.push_back(current);
        current = parent[current];
    }

    // Find the lowest common ancestor
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

    // Build path from LCA to u
    int lcaPosition = position[lca];

    for (int i = lcaPosition; i >= 0; i--)
        cycle.push_back(pathU[i]);

    // Add the edge from u to v
    cycle.push_back(v);

    // Build path from v back to LCA
    int vPosition = 0;

    while (pathV[vPosition] != lca)
    {
        vPosition++;
        if (pathV[vPosition] == -1)
            break;
    }

    for (int i = 1; i <= vPosition; i++)
        cycle.push_back(pathV[i]);

    return cycle;
}

// Detect a cycle using BFS
bool detectCycleBFS(
    vector<vector<int>>& adj,
    int V)
{
    vector<bool> visited(V, false);
    vector<int> parent(V, -1);

    // Check every disconnected component
    for (int start = 0; start < V; start++)
    {
        if (visited[start])
            continue;

        queue<int> q;

        visited[start] = true;
        q.push(start);

        while (!q.empty())
        {
            int current = q.front();
            q.pop();

            for (int neighbour : adj[current])
            {
                if (!visited[neighbour])
                {
                    visited[neighbour] = true;
                    parent[neighbour] = current;
                    q.push(neighbour);
                }
                else if (neighbour != parent[current])
                {
                    cout << "\nCycle detected!\n";

                    vector<int> cycle = buildCycle(
                        current,
                        neighbour,
                        parent,
                        V
                    );

                    cout << "Cycle: ";

                    for (int i = 0; i < cycle.size(); i++)
                    {
                        cout << cycle[i];

                        if (i != cycle.size() - 1)
                            cout << " -> ";
                    }

                    cout << "\nCycle length: "
                         << cycle.size() - 1 << " edges\n";

                    return true;
                }
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

        // Normalize undirected edge
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

    cout << "\nCycle Detection Using BFS:\n";

    bool hasCycle = detectCycleBFS(adj, V);

    if (!hasCycle)
        cout << "No cycle exists in the graph.\n";

    return 0;
}
