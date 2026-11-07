#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>
using namespace std;

const long long INF = numeric_limits<long long>::max() / 4;

void dijkstra(int vertices,
              vector<pair<int, long long>> adj[],
              int source)
{
    vector<long long> distance(vertices + 1, INF);
    vector<int> parent(vertices + 1, -1);

    // Min Heap: {distance, vertex}
    priority_queue<
        pair<long long, int>,
        vector<pair<long long, int>>,
        greater<pair<long long, int>>
    > minHeap;

    distance[source] = 0;

    minHeap.push({0, source});

    while (!minHeap.empty())
    {
        long long currentDistance = minHeap.top().first;
        int u = minHeap.top().second;

        minHeap.pop();

        // Ignore outdated heap entries.
        if (currentDistance != distance[u])
            continue;

        // Visit all adjacent vertices.
        for (auto edge : adj[u])
        {
            int v = edge.first;
            long long weight = edge.second;

            // Check whether a shorter path exists.
            if (currentDistance + weight < distance[v])
            {
                distance[v] = currentDistance + weight;

                parent[v] = u;

                minHeap.push({distance[v], v});
            }
        }
    }

    cout << "\n========== SHORTEST PATH RESULTS ==========\n";

    for (int i = 1; i <= vertices; i++)
    {
        cout << "\nVertex " << i << ":\n";

        if (distance[i] == INF)
        {
            cout << "Shortest distance: Unreachable" << endl;
            cout << "Path: Not available" << endl;
            continue;
        }

        cout << "Shortest distance: " << distance[i] << endl;

        // Reconstruct the shortest path.
        vector<int> path;

        int current = i;

        while (current != -1)
        {
            path.push_back(current);
            current = parent[current];
        }

        reverse(path.begin(), path.end());

        cout << "Shortest path: ";

        for (int j = 0; j < (int)path.size(); j++)
        {
            cout << path[j];

            if (j != (int)path.size() - 1)
                cout << " -> ";
        }

        cout << endl;
    }
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
            weight < 0 || weight > INF)
        {
            cout << "Invalid edge details!" << endl;
            return 0;
        }

        // Undirected graph.
        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight});
    }

    int source;

    cout << "\nEnter source vertex: ";
    cin >> source;

    if (source < 1 || source > vertices)
    {
        cout << "Invalid source vertex!" << endl;
        return 0;
    }

    dijkstra(vertices, adj, source);

    return 0;
}