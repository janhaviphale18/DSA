#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

struct Edge
{
    int source;
    int destination;
};

class DSU
{
private:
    vector<int> parent;
    vector<int> size;
    int components;

public:
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

        // Same representative means a cycle is formed.

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

        components--;

        return true;
    }

    int countComponents()
    {
        return components;
    }

    // Display the final connected components.

    void displayComponents(int n)
    {
        vector<vector<int>> groups(n);

        for (int i = 0; i < n; i++)
        {
            int root = find(i);
            groups[root].push_back(i);
        }

        cout << "\nConnected Components:\n";

        for (int i = 0; i < n; i++)
        {
            if (!groups[i].empty())
            {
                cout << "Component " << i << " : ";

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

    cout << "Enter the number of edges: ";
    cin >> E;

    if (cin.fail() || E < 0)
    {
        cout << "Invalid number of edges.\n";
        return 0;
    }

    vector<Edge> edges;

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

        edges.push_back({u, v});
    }

    DSU dsu(V);

    vector<Edge> cycleEdges;

    cout << "\n================================\n";
    cout << "DSU Cycle Detection Execution\n";
    cout << "================================\n";

    for (const Edge &e : edges)
    {
        int u = e.source;
        int v = e.destination;

        cout << "\nProcessing edge "
             << u << " - " << v << "\n";

        int rootU = dsu.find(u);
        int rootV = dsu.find(v);

        cout << "Representative of " << u
             << " : " << rootU << "\n";

        cout << "Representative of " << v
             << " : " << rootV << "\n";

        if (rootU == rootV)
        {
            cout << "Cycle detected! Edge "
                 << u << " - " << v
                 << " connects vertices already in the same component.\n";

            cycleEdges.push_back(e);
        }
        else
        {
            dsu.unite(u, v);

            cout << "No cycle. Components successfully merged.\n";
        }
    }

    cout << "\n================================\n";

    if (cycleEdges.empty())
    {
        cout << "Result: Graph does not contain a cycle.\n";
    }
    else
    {
        cout << "Result: Graph contains a cycle.\n";

        cout << "\nCycle-forming edges:\n";

        for (const Edge &e : cycleEdges)
        {
            cout << e.source << " - "
                 << e.destination << "\n";
        }
    }

    cout << "\nNumber of Connected Components: "
         << dsu.countComponents() << "\n";

    dsu.displayComponents(V);

    cout << "\n================================\n";

    return 0;
}
