#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;

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

    long long maxEdges = 1LL * V * V;

    cout << "Enter the number of directed edges: ";
    cin >> E;

    if (cin.fail() || E < 0 || E > maxEdges)
    {
        cout << "Invalid number of edges.\n";
        return 0;
    }

    vector<vector<int>> adj(V);
    vector<int> indegree(V, 0);

    set<pair<int, int>> existingEdges;

    cout << "\nEnter directed edges (source destination):\n";

    for (int i = 0; i < E; i++)
    {
        int u, v;

        cout << "Edge " << i + 1 << ": ";
        cin >> u >> v;

        if (cin.fail() || u < 0 || u >= V || v < 0 || v >= V)
        {
            cout << "Invalid vertex. Enter vertices between 0 and "
                 << V - 1 << ".\n";
            return 0;
        }

        if (existingEdges.count({u, v}))
        {
            cout << "Duplicate directed edge is not allowed.\n";
            return 0;
        }

        existingEdges.insert({u, v});

        adj[u].push_back(v);
        indegree[v]++;
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

    cout << "\nInitial Indegree of Vertices:\n";

    for (int i = 0; i < V; i++)
    {
        cout << "Vertex " << i << " : "
             << indegree[i] << "\n";
    }

    queue<int> q;

    for (int i = 0; i < V; i++)
    {
        if (indegree[i] == 0)
        {
            q.push(i);
        }
    }

    vector<int> topoOrder;

    cout << "\nProcessing vertices using BFS:\n";

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        topoOrder.push_back(u);

        cout << "Processed vertex: " << u << "\n";

        for (int v : adj[u])
        {
            indegree[v]--;

            cout << "Indegree of vertex " << v
                 << " decreased to " << indegree[v] << "\n";

            if (indegree[v] == 0)
            {
                q.push(v);

                cout << "Vertex " << v
                     << " added to queue.\n";
            }
        }
    }

    cout << "\n================================\n";

    if ((int)topoOrder.size() == V)
    {
        cout << "Graph is a DAG.\n";

        cout << "Topological Ordering: ";

        for (int v : topoOrder)
        {
            cout << v << " ";
        }

        cout << "\n";
    }
    else
    {
        cout << "Graph contains a cycle.\n";

        cout << "Topological sorting is not possible.\n";

        cout << "\nUnprocessed vertices:\n";

        for (int i = 0; i < V; i++)
        {
            if (indegree[i] > 0)
            {
                cout << i << " ";
            }
        }

        cout << "\n";

        cout << "These vertices may belong to a cycle "
             << "or depend on vertices in a cycle.\n";
    }

    cout << "================================\n";

    return 0;
}
