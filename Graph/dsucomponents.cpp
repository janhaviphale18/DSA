#include <iostream>
#include <vector>
#include <numeric>
#include <set>
#include <algorithm>
using namespace std;

class DSU
{
private:
    vector<int> parent;
    vector<int> size;
    int components;

public:
    // Initialize every vertex as a separate component.

    DSU(int n)
    {
        parent.resize(n);
        size.resize(n, 1);

        iota(parent.begin(), parent.end(), 0);

        components = n;
    }

    // Find representative using path compression.

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

        if (rootU == rootV)
        {
            return false;
        }

        if (size[rootU] < size[rootV])
        {
            swap(rootU, rootV);
        }

        parent[rootV] = rootU;
        size[rootU] += size[rootV];

        components--;

        return true;
    }

    // Return the total number of components.

    int countComponents()
    {
        return components;
    }

    // Return the size of a component.

    int componentSize(int vertex)
    {
        return size[find(vertex)];
    }

    // Display all connected components.

    void displayComponents(int n)
    {
        vector<vector<int>> groups(n);

        for (int i = 0; i < n; i++)
        {
            int root = find(i);
            groups[root].push_back(i);
        }

        cout << "\nConnected Components:\n";

        int componentNumber = 1;

        for (int i = 0; i < n; i++)
        {
            if (!groups[i].empty())
            {
                cout << "Component " << componentNumber++ << " : ";

                for (int vertex : groups[i])
                {
                    cout << vertex << " ";
                }

                cout << "\n";
            }
        }
    }
};

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

    DSU dsu(V);

    vector<int> degree(V, 0);

    set<pair<int, int>> existingEdges;

    cout << "\nEnter undirected edges (u v):\n";

    for (int i = 0; i < E; i++)
    {
        int u, v;

        cout << "Edge " << i + 1 << ": ";
        cin >> u >> v;

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

        // Normalize the edge to identify duplicates.

        pair<int, int> edge = {min(u, v), max(u, v)};

        if (existingEdges.count(edge))
        {
            cout << "Duplicate edge is not allowed.\n";
            return 0;
        }

        existingEdges.insert(edge);

        degree[u]++;
        degree[v]++;

        cout << "Processing edge " << u << " - " << v << "\n";

        if (dsu.unite(u, v))
        {
            cout << "Components successfully merged.\n";
        }
        else
        {
            cout << "Vertices already belong to the same component.\n";
        }
    }

    cout << "\n================================\n";

    cout << "Total Connected Components: "
         << dsu.countComponents() << "\n";

    cout << "================================\n";

    dsu.displayComponents(V);

    cout << "\nComponent Sizes:\n";

    for (int i = 0; i < V; i++)
    {
        if (dsu.find(i) == i)
        {
            cout << "Component represented by " << i
                 << " : " << dsu.componentSize(i)
                 << " vertices\n";
        }
    }

    cout << "\nIsolated Vertices:\n";

    bool isolatedFound = false;

    for (int i = 0; i < V; i++)
    {
        if (degree[i] == 0)
        {
            cout << i << " ";
            isolatedFound = true;
        }
    }

    if (!isolatedFound)
    {
        cout << "None";
    }

    cout << "\n";

    cout << "\n================================\n";

    return 0;
}
