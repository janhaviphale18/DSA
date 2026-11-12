#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <limits>
using namespace std;

using ll = long long;

const ll INF = numeric_limits<ll>::max() / 4;

struct Edge
{
    int source;
    int destination;
    ll weight;
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

    long long maxEdges = 1LL * V * (V - 1);

    cout << "Enter the number of directed weighted edges: ";
    cin >> E;

    if (cin.fail() || E < 0 || E > maxEdges)
    {
        cout << "Invalid number of edges.\n";
        return 0;
    }

    vector<vector<pair<int, ll>>> adj(V);
    vector<int> indegree(V, 0);

    vector<Edge> edges;

    set<pair<int, int>> existingEdges;

    cout << "\nEnter edges (source destination weight):\n";

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

        if (weight <= -INF || weight >= INF)
        {
            cout << "Weight is outside the supported range.\n";
            return 0;
        }

        if (existingEdges.count({u, v}))
        {
            cout << "Duplicate directed edge is not allowed.\n";
            return 0;
        }

        existingEdges.insert({u, v});

        adj[u].push_back({v, weight});

        edges.push_back({u, v, weight});

        indegree[v]++;
    }

    cout << "\nWeighted Adjacency List:\n";

    for (int i = 0; i < V; i++)
    {
        cout << i << " -> ";

        if (adj[i].empty())
        {
            cout << "NULL";
        }
        else
        {
            for (auto edge : adj[i])
            {
                cout << "(" << edge.first
                     << ", weight = " << edge.second << ") ";
            }
        }

        cout << "\n";
    }

    // Step 1: Generate topological ordering using Kahn's Algorithm.

    queue<int> q;

    for (int i = 0; i < V; i++)
    {
        if (indegree[i] == 0)
        {
            q.push(i);
        }
    }

    vector<int> topoOrder;

    cout << "\nGenerating Topological Ordering:\n";

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        topoOrder.push_back(u);

        for (auto edge : adj[u])
        {
            int v = edge.first;

            indegree[v]--;

            if (indegree[v] == 0)
            {
                q.push(v);
            }
        }
    }

    // A topological ordering must contain every vertex.

    if ((int)topoOrder.size() != V)
    {
        cout << "\nGraph contains a directed cycle.\n";
        cout << "Shortest path in a DAG is not applicable.\n";

        cout << "Unprocessed vertices: ";

        for (int i = 0; i < V; i++)
        {
            if (indegree[i] > 0)
            {
                cout << i << " ";
            }
        }

        cout << "\n";

        return 0;
    }

    cout << "\nTopological Ordering: ";

    for (int v : topoOrder)
    {
        cout << v << " ";
    }

    cout << "\n";

    // Step 2: Read source and destination.

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

    // Step 3: Initialize distances and parents.

    vector<ll> distance(V, INF);
    vector<int> parent(V, -1);

    distance[source] = 0;

    // Step 4: Relax edges in topological order.

    cout << "\nShortest Path Calculation:\n";

    for (int u : topoOrder)
    {
        if (distance[u] == INF)
        {
            continue;
        }

        cout << "Processing vertex " << u
             << " with distance " << distance[u] << "\n";

        for (auto edge : adj[u])
        {
            int v = edge.first;
            ll weight = edge.second;

            // Protect addition from overflow.

            if (weight > 0 && distance[u] > INF - weight)
            {
                continue;
            }

            if (weight < 0 && distance[u] < -INF - weight)
            {
                continue;
            }

            ll newDistance = distance[u] + weight;

            if (newDistance < distance[v])
            {
                distance[v] = newDistance;
                parent[v] = u;

                cout << "Updated distance of vertex "
                     << v << " to " << newDistance << "\n";
            }
        }
    }

    // Step 5: Display all shortest distances.

    cout << "\n================================\n";

    cout << "Shortest Distances from Source "
         << source << ":\n";

    for (int i = 0; i < V; i++)
    {
        cout << "Vertex " << i << " : ";

        if (distance[i] == INF)
        {
            cout << "Unreachable\n";
        }
        else
        {
            cout << distance[i] << "\n";
        }
    }

    // Step 6: Reconstruct the destination path.

    cout << "\n================================\n";

    if (distance[destination] == INF)
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

        cout << "Minimum Total Cost: "
             << distance[destination] << "\n";
    }

    cout << "================================\n";

    return 0;
}
