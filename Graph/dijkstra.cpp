#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
#include <limits>
using namespace std;

using ll = long long;

const ll INF = numeric_limits<ll>::max() / 4;

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

    cout << "Enter the number of weighted edges: ";
    cin >> E;

    if (cin.fail() || E < 0 || E > maxEdges)
    {
        cout << "Invalid number of edges.\n";
        return 0;
    }

    vector<vector<pair<int, ll>>> adj(V);

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

        if (weight < 0 || weight >= INF)
        {
            cout << "Invalid weight. "
                 << "Dijkstra requires non-negative weights.\n";
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

        adj[u].push_back({v, weight});

        if (!directed)
        {
            adj[v].push_back({u, weight});
        }
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

    vector<ll> distance(V, INF);
    vector<int> parent(V, -1);

    priority_queue<
        pair<ll, int>,
        vector<pair<ll, int>>,
        greater<pair<ll, int>>
    > pq;

    distance[source] = 0;

    pq.push({0, source});

    cout << "\nDijkstra's Algorithm Execution:\n";

    while (!pq.empty())
    {
        ll currentDistance = pq.top().first;
        int u = pq.top().second;

        pq.pop();

        // Ignore outdated priority queue entries.
        if (currentDistance != distance[u])
        {
            continue;
        }

        cout << "Processing vertex " << u
             << " with distance " << currentDistance << "\n";

        for (auto edge : adj[u])
        {
            int v = edge.first;
            ll weight = edge.second;

            if (weight > INF - currentDistance)
            {
                continue;
            }

            ll newDistance = currentDistance + weight;

            if (newDistance < distance[v])
            {
                distance[v] = newDistance;
                parent[v] = u;

                pq.push({newDistance, v});

                cout << "Updated distance of vertex "
                     << v << " to " << newDistance << "\n";
            }
        }
    }

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
