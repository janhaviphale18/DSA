#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <set>
using namespace std;

using ll = long long;

const ll INF = numeric_limits<ll>::max() / 4;

struct Edge
{
    int source;
    int destination;
    ll weight;
};

class DSU
{
private:
    vector<int> parent;
    vector<int> size;

public:
    DSU(int n)
    {
        parent.resize(n);
        size.resize(n, 1);

        iota(parent.begin(), parent.end(), 0);
    }

    // Find the representative with path compression.

    int find(int vertex)
    {
        if (parent[vertex] != vertex)
        {
            parent[vertex] = find(parent[vertex]);
        }

        return parent[vertex];
    }

    // Merge two components using union by size.

    bool unite(int u, int v)
    {
        int rootU = find(u);
        int rootV = find(v);

        // Same component means adding the edge creates a cycle.

        if (rootU == rootV)
        {
            return false;
        }

        // Attach the smaller component to the larger one.

        if (size[rootU] < size[rootV])
        {
            swap(rootU, rootV);
        }

        parent[rootV] = rootU;
        size[rootU] += size[rootV];

        return true;
    }

    int countComponents(int n)
    {
        int components = 0;

        for (int i = 0; i < n; i++)
        {
            if (find(i) == i)
            {
                components++;
            }
        }

        return components;
    }
};

// Sort edges by increasing weight.

bool compareEdges(const Edge &a, const Edge &b)
{
    if (a.weight != b.weight)
    {
        return a.weight < b.weight;
    }

    if (a.source != b.source)
    {
        return a.source < b.source;
    }

    return a.destination < b.destination;
}

int main()
{
    int V, E;

    cout << "Enter the number of vertices: ";
    cin >> V;

    if (cin.fail() || V <= 0)
    {
        cout << "Invalid number of vertices.\n";
        return 0;
    }

    long long maxEdges = 1LL * V * (V - 1) / 2;

    cout << "Enter the number of edges: ";
    cin >> E;

    if (cin.fail() || E < 0 || E > maxEdges)
    {
        cout << "Invalid number of edges.\n";
        return 0;
    }

    vector<Edge> edges;
    set<pair<int, int>> existingEdges;

    // Keep the total weight safely within long long range.

    ll maxWeight = INF / V;

    cout << "\nEnter undirected edges (u v weight):\n";

    for (int i = 0; i < E; i++)
    {
        int u, v;
        ll weight;

        cout << "Edge " << i + 1 << ": ";
        cin >> u >> v >> weight;

        if (cin.fail() || u < 0 || u >= V ||
            v < 0 || v >= V)
        {
            cout << "Invalid vertex number.\n";
            return 0;
        }

        if (u == v)
        {
            cout << "Self-loops are not allowed.\n";
            return 0;
        }

        if (weight <= -maxWeight || weight >= maxWeight)
        {
            cout << "Invalid edge weight.\n";
            return 0;
        }

        pair<int, int> edge = {min(u, v), max(u, v)};

        if (existingEdges.count(edge))
        {
            cout << "Duplicate edge is not allowed.\n";
            return 0;
        }

        existingEdges.insert(edge);

        edges.push_back({u, v, weight});
    }

    cout << "\nOriginal Edge List:\n";

    for (const Edge &e : edges)
    {
        cout << e.source << " - " << e.destination
             << " | Weight: " << e.weight << "\n";
    }

    // Sort all edges in ascending order.

    sort(edges.begin(), edges.end(), compareEdges);

    cout << "\nEdges Sorted by Weight:\n";

    for (const Edge &e : edges)
    {
        cout << e.source << " - " << e.destination
             << " | Weight: " << e.weight << "\n";
    }

    DSU dsu(V);

    vector<Edge> mstEdges;

    ll totalWeight = 0;

    cout << "\n================================\n";
    cout << "Kruskal's Algorithm Execution\n";
    cout << "================================\n";

    for (const Edge &e : edges)
    {
        cout << "\nConsidering edge "
             << e.source << " - " << e.destination
             << " | Weight: " << e.weight << "\n";

        if (dsu.unite(e.source, e.destination))
        {
            mstEdges.push_back(e);
            totalWeight += e.weight;

            cout << "Selected: Edge added to spanning forest.\n";
        }
        else
        {
            cout << "Rejected: Edge would create a cycle.\n";
        }

        if ((int)mstEdges.size() == V - 1)
        {
            break;
        }
    }

    int components = dsu.countComponents(V);

    cout << "\n================================\n";

    if (components == 1)
    {
        cout << "Minimum Spanning Tree (MST)\n";
    }
    else
    {
        cout << "Minimum Spanning Forest (MSF)\n";
    }

    cout << "================================\n";

    cout << "Selected Edges:\n";

    if (mstEdges.empty())
    {
        cout << "No edges selected.\n";
    }
    else
    {
        for (const Edge &e : mstEdges)
        {
            cout << e.source << " - " << e.destination
                 << " (Weight: " << e.weight << ")\n";
        }
    }

    cout << "\nNumber of Components: "
         << components << "\n";

    cout << "Number of Selected Edges: "
         << mstEdges.size() << "\n";

    cout << "Minimum Total Weight: "
         << totalWeight << "\n";

    if (components == 1)
    {
        cout << "All vertices are connected.\n";
    }
    else
    {
        cout << "The graph is disconnected. "
             << "A single MST does not exist.\n";
    }

    cout << "================================\n";

    return 0;
}
