#include <iostream>
#include <vector>
#include <numeric>
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

        // Both vertices already belong to the same component.

        if (rootU == rootV)
        {
            return false;
        }

        // Attach the smaller component to the larger component.

        if (size[rootU] < size[rootV])
        {
            swap(rootU, rootV);
        }

        parent[rootV] = rootU;

        size[rootU] += size[rootV];

        components--;

        return true;
    }

    // Check whether two vertices are connected.

    bool connected(int u, int v)
    {
        return find(u) == find(v);
    }

    // Return the size of a component.

    int componentSize(int vertex)
    {
        int root = find(vertex);

        return size[root];
    }

    // Return the number of disjoint components.

    int countComponents()
    {
        return components;
    }

    // Display all components.

    void displayComponents(int n)
    {
        vector<vector<int>> groups(n);

        for (int i = 0; i < n; i++)
        {
            int root = find(i);

            groups[root].push_back(i);
        }

        cout << "\nDisjoint Components:\n";

        for (int i = 0; i < n; i++)
        {
            if (!groups[i].empty())
            {
                cout << "Representative " << i << " : ";

                for (int vertex : groups[i])
                {
                    cout << vertex << " ";
                }

                cout << "\n";
            }
        }
    }

    // Display the parent and size information.

    void displayDSU(int n)
    {
        cout << "\nDSU Information:\n";

        cout << "Vertex\tParent\tComponent Size\n";

        for (int i = 0; i < n; i++)
        {
            int root = find(i);

            cout << i << "\t"
                 << parent[i] << "\t"
                 << size[root] << "\n";
        }
    }
};

int main()
{
    int V;

    cout << "Enter the number of vertices: ";
    cin >> V;

    if (cin.fail() || V <= 0)
    {
        cout << "Invalid number of vertices.\n";
        return 0;
    }

    DSU dsu(V);

    int unionOperations;

    cout << "Enter the number of union operations: ";
    cin >> unionOperations;

    if (cin.fail() || unionOperations < 0)
    {
        cout << "Invalid number of union operations.\n";
        return 0;
    }

    cout << "\nEnter vertex pairs for union operations:\n";

    for (int i = 0; i < unionOperations; i++)
    {
        int u, v;

        cout << "Union " << i + 1 << " (u v): ";
        cin >> u >> v;

        if (cin.fail() || u < 0 || u >= V ||
            v < 0 || v >= V)
        {
            cout << "Invalid vertex number.\n";
            return 0;
        }

        if (dsu.unite(u, v))
        {
            cout << "Components containing "
                 << u << " and " << v
                 << " successfully merged.\n";
        }
        else
        {
            cout << "Vertices " << u << " and " << v
                 << " already belong to the same component.\n";
        }
    }

    int queries;

    cout << "\nEnter the number of connectivity queries: ";
    cin >> queries;

    if (cin.fail() || queries < 0)
    {
        cout << "Invalid number of queries.\n";
        return 0;
    }

    cout << "\nConnectivity Queries:\n";

    for (int i = 0; i < queries; i++)
    {
        int u, v;

        cout << "Query " << i + 1 << " (u v): ";
        cin >> u >> v;

        if (cin.fail() || u < 0 || u >= V ||
            v < 0 || v >= V)
        {
            cout << "Invalid vertex number.\n";
            return 0;
        }

        if (dsu.connected(u, v))
        {
            cout << u << " and " << v
                 << " are connected.\n";
        }
        else
        {
            cout << u << " and " << v
                 << " are not connected.\n";
        }
    }

    int vertex;

    cout << "\nEnter a vertex to find its component size: ";
    cin >> vertex;

    if (cin.fail() || vertex < 0 || vertex >= V)
    {
        cout << "Invalid vertex number.\n";
        return 0;
    }

    cout << "Component size of vertex "
         << vertex << " : "
         << dsu.componentSize(vertex) << "\n";

    cout << "\nTotal Number of Components: "
         << dsu.countComponents() << "\n";

    dsu.displayComponents(V);

    dsu.displayDSU(V);

    cout << "\n================================\n";

    return 0;
}