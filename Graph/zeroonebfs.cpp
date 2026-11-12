#include <iostream>
#include <vector>
#include <deque>
#include <set>
#include <algorithm>
#include <limits>
using namespace std;

using ll = long long;

const ll INF = numeric_limits<ll>::max() / 4;

struct Edge
{
    int destination;
    int weight;
};

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

    vector<vector<Edge>> adj(V);

    set<pair<int, int>> existingEdges;

    cout << "\nEnter edges (source destination weight):\n";

    for (int i = 0; i < E; i++)
    {
        int u, v, weight;

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

        if (weight != 0 && weight != 1)
        {
            cout << "Invalid weight. Only 0 and 1 are allowed.\n";
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
            for (const Edge &e : adj[i])
            {
                cout << "(" << e.destination
                     << ", weight = " << e.weight << ") ";
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

    // Deque stores {distance, vertex}.

    deque<pair<ll, int>> dq;

    distance[source] = 0;
    dq.push_front({0, source});

    cout << "\n0-1 BFS Execution:\n";

    while (!dq.empty())
    {
        ll currentDistance = dq.front().first;
        int u = dq.front().second;

        dq.pop_front();

        // Ignore outdated deque entries.

        if (currentDistance != distance[u])
        {
            continue;
        }

        cout << "Processing vertex " << u
             << " with distance " << currentDistance << "\n";

        for (const Edge &e : adj[u])
        {
            int v = e.destination;
            int weight = e.weight;

            ll newDistance = currentDistance + weight;

            if (newDistance < distance[v])
            {
                distance[v] = newDistance;
                parent[v] = u;

                cout << "Updated distance of vertex "
                     << v << " to " << newDistance << "\n";

                if (weight == 0)
                {
                    dq.push_front({newDistance, v});

                    cout << "Vertex " << v
                         << " inserted at front of deque.\n";
                }
                else
                {
                    dq.push_back({newDistance, v});

                    cout << "Vertex " << v
                         << " inserted at back of deque.\n";
                }
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
