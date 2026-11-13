#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <limits>
using namespace std;

using ll = long long;

const ll INF = numeric_limits<ll>::max() / 4;

struct Edge
{
    int source;
    int destination;
    ll price;
};

int main()
{
    int V, E;

    cout << "Enter the number of cities: ";
    cin >> V;

    if (cin.fail() || V <= 0)
    {
        cout << "Invalid number of cities.\n";
        return 0;
    }

    long long maxEdges = 1LL * V * (V - 1);

    cout << "Enter the number of flights: ";
    cin >> E;

    if (cin.fail() || E < 0 || E > maxEdges)
    {
        cout << "Invalid number of flights.\n";
        return 0;
    }

    vector<Edge> flights;
    vector<vector<Edge>> adj(V);

    set<pair<int, int>> existingEdges;

    cout << "\nEnter flights (source destination price):\n";

    for (int i = 0; i < E; i++)
    {
        int u, v;
        ll price;

        cout << "Flight " << i + 1 << ": ";
        cin >> u >> v >> price;

        if (cin.fail() || u < 0 || u >= V ||
            v < 0 || v >= V)
        {
            cout << "Invalid city number.\n";
            return 0;
        }

        if (u == v)
        {
            cout << "Flights from a city to itself are not allowed.\n";
            return 0;
        }

        if (price < 0 || price >= INF)
        {
            cout << "Invalid flight price.\n";
            return 0;
        }

        pair<int, int> edge = {u, v};

        if (existingEdges.count(edge))
        {
            cout << "Duplicate flight is not allowed.\n";
            return 0;
        }

        existingEdges.insert(edge);

        flights.push_back({u, v, price});
        adj[u].push_back({u, v, price});
    }

    cout << "\nFlight Adjacency List:\n";

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
                     << ", price = " << e.price << ") ";
            }
        }

        cout << "\n";
    }

    int source, destination, K;

    cout << "\nEnter source city: ";
    cin >> source;

    if (cin.fail() || source < 0 || source >= V)
    {
        cout << "Invalid source city.\n";
        return 0;
    }

    cout << "Enter destination city: ";
    cin >> destination;

    if (cin.fail() || destination < 0 || destination >= V)
    {
        cout << "Invalid destination city.\n";
        return 0;
    }

    cout << "Enter maximum number of stops (K): ";
    cin >> K;

    if (cin.fail() || K < 0)
    {
        cout << "Invalid number of stops.\n";
        return 0;
    }

    // A route with K stops can contain at most K + 1 flights.
    // With non-negative prices, an optimal simple path needs
    // at most V - 1 flights.

    ll maxFlights = min(1LL * K + 1, 1LL * V - 1);

    // dp[r][v] stores the minimum cost to reach vertex v
    // using at most r flights.

    vector<vector<ll>> dp(
        maxFlights + 1,
        vector<ll>(V, INF)
    );

    // parent[r][v] stores the previous vertex
    // when the best route uses an additional flight in round r.

    vector<vector<int>> parent(
        maxFlights + 1,
        vector<int>(V, -1)
    );

    // usedEdge[r][v] indicates whether round r
    // improved the cost by adding an actual flight.

    vector<vector<bool>> usedEdge(
        maxFlights + 1,
        vector<bool>(V, false)
    );

    dp[0][source] = 0;

    cout << "\n================================\n";
    cout << "Bounded Bellman-Ford Execution\n";
    cout << "================================\n";

    for (int r = 1; r <= maxFlights; r++)
    {
        // Carry forward the previous round's distances.

        dp[r] = dp[r - 1];

        cout << "\nRound " << r
             << " (At most " << r << " flights):\n";

        bool updated = false;

        for (const Edge &e : flights)
        {
            int u = e.source;
            int v = e.destination;
            ll price = e.price;

            if (dp[r - 1][u] == INF)
            {
                continue;
            }

            if (price > INF - dp[r - 1][u])
            {
                continue;
            }

            ll newCost = dp[r - 1][u] + price;

            if (newCost < dp[r][v])
            {
                dp[r][v] = newCost;
                parent[r][v] = u;
                usedEdge[r][v] = true;

                updated = true;

                cout << "Updated city " << v
                     << " through city " << u
                     << " with cost " << newCost << "\n";
            }
        }

        if (!updated)
        {
            cout << "No further improvement in this round.\n";
        }
    }

    cout << "\n================================\n";

    cout << "Minimum Costs from Source "
         << source << ":\n";

    for (int i = 0; i < V; i++)
    {
        cout << "City " << i << " : ";

        if (dp[maxFlights][i] == INF)
        {
            cout << "Unreachable\n";
        }
        else
        {
            cout << dp[maxFlights][i] << "\n";
        }
    }

    cout << "\n================================\n";

    if (dp[maxFlights][destination] == INF)
    {
        cout << "No valid route exists from city "
             << source << " to city "
             << destination << " within "
             << K << " stops.\n";
    }
    else
    {
        vector<int> path;

        int current = destination;

        // Reconstruct the path by moving backwards
        // through the DP rounds.

        for (int r = maxFlights; r >= 1; r--)
        {
            if (usedEdge[r][current])
            {
                path.push_back(current);
                current = parent[r][current];
            }
        }

        path.push_back(current);

        reverse(path.begin(), path.end());

        int flightsUsed = (int)path.size() - 1;

        int stopsUsed = max(0, flightsUsed - 1);

        cout << "Cheapest Flight Route: ";

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
             << dp[maxFlights][destination] << "\n";

        cout << "Flights Used: " << flightsUsed << "\n";

        cout << "Intermediate Stops Used: "
             << stopsUsed << "\n";
    }

    cout << "================================\n";

    return 0;
}
