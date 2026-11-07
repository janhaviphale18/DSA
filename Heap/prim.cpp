#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;

void prim(int vertices,
          vector<pair<int, long long>> adj[])
{
    // Min Heap: {weight, vertex, parent}
    priority_queue<
        tuple<long long, int, int>,
        vector<tuple<long long, int, int>>,
        greater<tuple<long long, int, int>>
    > minHeap;

    bool visited[1001] = {false};

    vector<tuple<int, int, long long>> mst;

    long long totalCost = 0;

    int visitedCount = 0;

    // Start from vertex 1.
    minHeap.push({0, 1, -1});

    while (!minHeap.empty())
    {
        long long weight;
        int u, parent;

        tie(weight, u, parent) = minHeap.top();
        minHeap.pop();

        // Ignore vertices already included in MST.
        if (visited[u])
            continue;

        visited[u] = true;
        visitedCount++;

        // Add the selected edge to MST.
        if (parent != -1)
        {
            mst.push_back({parent, u, weight});
            totalCost += weight;
        }

        // Explore adjacent vertices.
        for (auto edge : adj[u])
        {
            int v = edge.first;
            long long edgeWeight = edge.second;

            if (!visited[v])
            {
                minHeap.push({edgeWeight, v, u});
            }
        }
    }

    cout << "\n========== PRIM'S ALGORITHM ==========\n";

    if (visitedCount != vertices)
    {
        cout << "The graph is disconnected." << endl;
        cout << "A Minimum Spanning Tree does not exist." << endl;

        cout << "\nEdges selected in the reachable component:\n";

        for (auto edge : mst)
        {
            int u, v;
            long long weight;

            tie(u, v, weight) = edge;

            cout << u << " - " << v
                 << " : " << weight << endl;
        }

        return;
    }

    cout << "\nEdges included in Minimum Spanning Tree:\n";

    for (auto edge : mst)
    {
        int u, v;
        long long weight;

        tie(u, v, weight) = edge;

        cout << u << " - " << v
             << " : " << weight << endl;
    }

    cout << "\nTotal edges in MST: " << mst.size() << endl;
    cout << "Minimum Spanning Tree Cost: " << totalCost << endl;
}

int main()
{
    int vertices, edges;

    cout << "Enter number of vertices: ";
    cin >> vertices;

    if (vertices < 1 || vertices > 1000)
    {
        cout << "Invalid number of vertices!" << endl;
        return 0;
    }

    cout << "Enter number of edges: ";
    cin >> edges;

    if (edges < 0 || edges > 10000)
    {
        cout << "Invalid number of edges!" << endl;
        return 0;
    }

    vector<pair<int, long long>> adj[1001];

    cout << "\nEnter edges in the format: source destination weight\n";

    for (int i = 0; i < edges; i++)
    {
        int u, v;
        long long weight;

        cout << "Edge " << i + 1 << ": ";
        cin >> u >> v >> weight;

        if (u < 1 || u > vertices ||
            v < 1 || v > vertices ||
            weight < -1000000000000LL ||
            weight > 1000000000000LL)
        {
            cout << "Invalid edge details!" << endl;
            return 0;
        }

        // Undirected graph.
        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight});
    }

    prim(vertices, adj);

    return 0;
}