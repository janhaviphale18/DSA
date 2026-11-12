#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
using namespace std;

int main()
{
    int V, E;
    char choice;

    cout << "Enter the number of vertices: ";
    cin >> V;

    if (cin.fail() || V <= 0)
    {
        cout << "Invalid number of vertices.\n";
        return 0;
    }

    cout << "Enter graph type (D for Directed, U for Undirected): ";
    cin >> choice;

    if (choice != 'D' && choice != 'd' &&
        choice != 'U' && choice != 'u')
    {
        cout << "Invalid graph type.\n";
        return 0;
    }

    bool directed = (choice == 'D' || choice == 'd');

    long long maxEdges;

    if (directed)
    {
        maxEdges = 1LL * V * (V - 1);
    }
    else
    {
        maxEdges = 1LL * V * (V - 1) / 2;
    }

    cout << "Enter the number of edges: ";
    cin >> E;

    if (cin.fail() || E < 0 || E > maxEdges)
    {
        cout << "Invalid number of edges.\n";
        return 0;
    }

    vector<vector<int>> adj(V);
    set<pair<int, int>> existingEdges;

    cout << "\nEnter edges (source destination):\n";

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

        pair<int, int> edge = {u, v};

        if (!directed && u > v)
        {
            edge = {v, u};
        }

        if (existingEdges.count(edge))
        {
            cout << "Duplicate edge is not allowed.\n";
            return 0;
        }

        existingEdges.insert(edge);

        adj[u].push_back(v);

        if (!directed)
        {
            adj[v].push_back(u);
        }
    }

    cout << "\nAdjacency List:\n";

    for (int i = 0; i < V; i++)
    {
        cout << i << " -> ";

        if (adj[i].empty())
        {
            cout << "NULL";
        }
        else
        {
            for (int v : adj[i])
            {
                cout << v << " ";
            }
        }

        cout << "\n";
    }

    int source, destination;

    cout << "\nEnter source vertex: ";
    cin >> source;

    if (cin.fail() || source < 0 || source >= V)
    {
        cout << "Invalid source vertex.\n";
        return 0;
    }

    cout << "Enter destination vertex: ";
    cin >> destination;

    if (cin.fail() || destination < 0 || destination >= V)
    {
        cout << "Invalid destination vertex.\n";
        return 0;
    }

    vector<int> distance(V, -1);
    vector<int> parent(V, -1);

    queue<int> q;

    distance[source] = 0;
    q.push(source);

    cout << "\nBFS Traversal:\n";

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        cout << u << " ";

        for (int v : adj[u])
        {
            if (distance[v] == -1)
            {
                distance[v] = distance[u] + 1;
                parent[v] = u;

                q.push(v);
            }
        }
    }

    cout << "\n";

    cout << "\nShortest Distance from Source "
         << source << ":\n";

    for (int i = 0; i < V; i++)
    {
        cout << "Vertex " << i << " : ";

        if (distance[i] == -1)
        {
            cout << "Unreachable\n";
        }
        else
        {
            cout << distance[i] << "\n";
        }
    }

    cout << "\n================================\n";

    if (distance[destination] == -1)
    {
        cout << "No path exists between "
             << source << " and " << destination << ".\n";
    }
    else
    {
        vector<int> path;

        int current = destination;

        while (current != -1)
        {
            path.push_back(current);
            current = parent[current];
        }

        reverse(path.begin(), path.end());

        cout << "Shortest Path: ";

        for (int i = 0; i < (int)path.size(); i++)
        {
            cout << path[i];

            if (i != (int)path.size() - 1)
            {
                cout << " -> ";
            }
        }

        cout << "\n";

        cout << "Shortest Distance: "
             << distance[destination] << " edges\n";
    }

    cout << "================================\n";

    return 0;
}
