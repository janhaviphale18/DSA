#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
using namespace std;

class DSU
{
    vector<int> parent;
    vector<int> size;

public:

    DSU(int n)
    {
        parent.resize(n);
        size.resize(n, 1);

        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    // Find representative using path compression
    int find(int x)
    {
        if (parent[x] != x)
            parent[x] = find(parent[x]);

        return parent[x];
    }

    // Combine two sets using union by size
    bool unite(int u, int v)
    {
        int rootU = find(u);
        int rootV = find(v);

        if (rootU == rootV)
            return false;

        if (size[rootU] < size[rootV])
            swap(rootU, rootV);

        parent[rootV] = rootU;
        size[rootU] += size[rootV];

        return true;
    }
};

// Find a path in the forest of successful DSU unions
vector<int> findPath(
    vector<vector<int>>& forest,
    int source,
    int destination)
{
    int V = forest.size();

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

        for (int neighbour : forest[current])
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

    DSU dsu(V);

    // Stores only edges that successfully joined two sets.
    // These edges form a forest without cycles.
    vector<vector<int>> forest(V);

    set<pair<int, int>> edges;

    int cycleU = -1;
    int cycleV = -1;

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

        // Check whether both vertices already belong to one set
        if (!dsu.unite(u, v))
        {
            if (cycleU == -1)
            {
                cycleU = u;
                cycleV = v;
            }
        }
        else
        {
            // Successful union: add edge to the forest
            forest[u].push_back(v);
            forest[v].push_back(u);
        }
    }

    cout << "\nDSU Cycle Detection:\n";

    if (cycleU == -1)
    {
        cout << "No cycle exists in the graph.\n";
    }
    else
    {
        cout << "Cycle detected!\n";

        cout << "Cycle-forming edge: "
             << cycleU << " - " << cycleV << "\n";

        // Find the existing path between the endpoints
        vector<int> cycle = findPath(
            forest,
            cycleU,
            cycleV
        );

        // The new edge closes the cycle
        cycle.push_back(cycleU);

        cout << "Cycle: ";

        for (int i = 0; i < cycle.size(); i++)
        {
            cout << cycle[i];

            if (i != cycle.size() - 1)
                cout << " -> ";
        }

        cout << "\nCycle length: "
             << cycle.size() - 1 << " edges\n";
    }

    return 0;
}
