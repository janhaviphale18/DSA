#include <iostream>
#include <vector>
#include <set>
#include <iomanip>
#include <limits>
using namespace std;

using ll = long long;

const ll INF = numeric_limits<ll>::max() / 4;

// Safely add two distances without overflow.

ll safeAdd(ll a, ll b)
{
    if (b > 0 && a > INF - b)
    {
        return INF - 1;
    }

    if (b < 0 && a < -INF - b)
    {
        return -INF + 1;
    }

    return a + b;
}

// Display the all-pairs shortest distance matrix.

void displayMatrix(
    const vector<vector<ll>> &dist,
    const vector<vector<bool>> &affected,
    int V)
{
    cout << "\nAll-Pairs Shortest Distance Matrix:\n\n";

    cout << setw(8) << " ";

    for (int j = 0; j < V; j++)
    {
        cout << setw(10) << j;
    }

    cout << "\n";

    for (int i = 0; i < V; i++)
    {
        cout << setw(8) << i;

        for (int j = 0; j < V; j++)
        {
            if (affected[i][j])
            {
                cout << setw(10) << "-INF";
            }
            else if (dist[i][j] == INF)
            {
                cout << setw(10) << "INF";
            }
            else
            {
                cout << setw(10) << dist[i][j];
            }
        }

        cout << "\n";
    }
}

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

    vector<vector<ll>> dist(V, vector<ll>(V, INF));

    vector<vector<int>> nextVertex(
        V, vector<int>(V, -1)
    );

    set<pair<int, int>> existingEdges;

    // Every vertex has distance zero from itself.

    for (int i = 0; i < V; i++)
    {
        dist[i][i] = 0;
        nextVertex[i][i] = i;
    }

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

        dist[u][v] = weight;
        nextVertex[u][v] = v;

        if (!directed)
        {
            dist[v][u] = weight;
            nextVertex[v][u] = u;
        }
    }

    cout << "\nInitial Distance Matrix:\n";

    vector<vector<bool>> noAffected(
        V, vector<bool>(V, false)
    );

    displayMatrix(dist, noAffected, V);

    cout << "\nFloyd-Warshall Algorithm Execution:\n";

    // Consider each vertex as an intermediate vertex.

    for (int k = 0; k < V; k++)
    {
        cout << "\nConsidering vertex " << k
             << " as intermediate vertex.\n";

        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                if (dist[i][k] == INF ||
                    dist[k][j] == INF)
                {
                    continue;
                }

                ll newDistance = safeAdd(
                    dist[i][k], dist[k][j]
                );

                if (newDistance < dist[i][j])
                {
                    dist[i][j] = newDistance;

                    nextVertex[i][j] = nextVertex[i][k];
                }
            }
        }
    }

    // Check which vertices can reach each other
    // through a negative-weight cycle.

    vector<vector<bool>> reachable(V, vector<bool>(V, false));

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            reachable[i][j] = (dist[i][j] != INF);
        }
    }

    vector<vector<bool>> affected(
        V, vector<bool>(V, false)
    );

    bool negativeCycle = false;

    for (int k = 0; k < V; k++)
    {
        if (dist[k][k] < 0)
        {
            negativeCycle = true;

            for (int i = 0; i < V; i++)
            {
                for (int j = 0; j < V; j++)
                {
                    if (reachable[i][k] &&
                        reachable[k][j])
                    {
                        affected[i][j] = true;
                    }
                }
            }
        }
    }

    cout << "\n================================\n";

    if (negativeCycle)
    {
        cout << "Negative-weight cycle detected.\n";
    }
    else
    {
        cout << "No negative-weight cycle detected.\n";
    }

    displayMatrix(dist, affected, V);

    cout << "\n================================\n";

    int source, destination;

    cout << "Enter source vertex: ";
    cin >> source;

    if (cin.fail() || source < 0 || source >= V)
    {
        cout << "Invalid source vertex.\n";
        return 0;
    }

    cout << "Enter destination vertex: ";
    cin >> destination;

    if (cin.fail() || destination < 0 ||
        destination >= V)
    {
        cout << "Invalid destination vertex.\n";
        return 0;
    }

    cout << "\nShortest Path Result:\n";

    if (affected[source][destination])
    {
        cout << "Shortest path is not well-defined.\n";

        cout << "A reachable negative-weight cycle "
             << "affects this vertex pair.\n";
    }
    else if (dist[source][destination] == INF)
    {
        cout << "No path exists between "
             << source << " and " << destination << ".\n";
    }
    else
    {
        cout << "Shortest Path: ";

        int current = source;
        int steps = 0;

        cout << current;

        while (current != destination)
        {
            current = nextVertex[current][destination];

            if (current == -1 || ++steps > V)
            {
                cout << "\nPath reconstruction failed.\n";
                return 0;
            }

            cout << " -> " << current;
        }

        cout << "\n";

        cout << "Minimum Total Cost: "
             << dist[source][destination] << "\n";
    }

    cout << "================================\n";

    return 0;
}
