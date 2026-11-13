#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
#include <limits>
using namespace std;

using ll = long long;

const ll INF = numeric_limits<ll>::max() / 4;

struct Edge
{
    int destination;
    ll weight;
};

struct Node
{
    ll weight;
    int vertex;
};

struct Compare
{
    bool operator()(const Node &a, const Node &b) const
    {
        if (a.weight != b.weight)
        {
            return a.weight > b.weight;
        }

        return a.vertex > b.vertex;
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

    vector<vector<Edge>> adj(V);

    set<pair<int, int>> existingEdges;

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

        if (weight <= -INF || weight >= INF)
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

        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight});
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

    int start;

    cout << "\nEnter starting vertex: ";
    cin >> start;

    if (cin.fail() || start < 0 || start >= V)
    {
        cout << "Invalid starting vertex.\n";
        return 0;
    }

    vector<ll> key(V, INF);
    vector<int> parent(V, -1);
    vector<bool> inMST(V, false);

    priority_queue<Node, vector<Node>, Compare> pq;

    vector<pair<int, int>> mstEdges;

    ll totalWeight = 0;
    int components = 0;

    // Start with the user-selected vertex.
    // Additional roots handle disconnected components.

    for (int pass = 0; pass < V; pass++)
    {
        int root;

        if (pass == 0)
        {
            root = start;
        }
        else
        {
            root = pass - 1;

            if (root >= start)
            {
                root++;
            }
        }

        if (inMST[root])
        {
            continue;
        }

        components++;

        key[root] = 0;
        pq.push({0, root});

        cout << "\nStarting component " << components
             << " from vertex " << root << "\n";

        while (!pq.empty())
        {
            Node current = pq.top();
            pq.pop();

            int u = current.vertex;
            ll currentWeight = current.weight;

            // Ignore outdated entries.

            if (inMST[u] || currentWeight != key[u])
            {
                continue;
            }

            inMST[u] = true;

            cout << "Included vertex " << u
                 << " in the spanning forest.\n";

            // Add the selected edge to the MST.

            if (parent[u] != -1)
            {
                mstEdges.push_back({parent[u], u});
                totalWeight += key[u];

                cout << "Selected edge: "
                     << parent[u] << " - " << u
                     << " | Weight: " << key[u] << "\n";
            }

            // Examine all adjacent vertices.

            for (const Edge &e : adj[u])
            {
                int v = e.destination;
                ll weight = e.weight;

                if (!inMST[v] && weight < key[v])
                {
                    key[v] = weight;
                    parent[v] = u;

                    pq.push({key[v], v});

                    cout << "Updated vertex " << v
                         << " | Minimum connecting edge weight: "
                         << weight << "\n";
                }
            }
        }
    }

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
        for (const auto &edge : mstEdges)
        {
            int u = edge.first;
            int v = edge.second;

            cout << u << " - " << v
                 << " (Weight: " << key[v] << ")\n";
        }
    }

    cout << "\nNumber of Components: " << components << "\n";

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
