#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <set>
using namespace std;

// DFS for topological sorting and cycle detection
bool dfsTopo(
    int current,
    vector<vector<int>>& adj,
    vector<int>& state,
    vector<int>& activePath,
    stack<int>& topoStack,
    vector<int>& cycle)
{
    // Mark vertex as currently being explored
    state[current] = 1;
    activePath.push_back(current);

    for (int neighbour : adj[current])
    {
        // Case 1: Neighbour is unvisited
        if (state[neighbour] == 0)
        {
            if (!dfsTopo(
                neighbour,
                adj,
                state,
                activePath,
                topoStack,
                cycle))
            {
                return false;
            }
        }

        // Case 2: Neighbour is currently being explored
        else if (state[neighbour] == 1)
        {
            // Reconstruct the cycle
            auto it = find(
                activePath.begin(),
                activePath.end(),
                neighbour
            );

            for (; it != activePath.end(); it++)
                cycle.push_back(*it);

            cycle.push_back(neighbour);

            return false;
        }
    }

    // Mark vertex as completely processed
    state[current] = 2;

    activePath.pop_back();

    // Push after processing all neighbours
    topoStack.push(current);

    return true;
}

// Perform topological sorting
bool topologicalSort(
    vector<vector<int>>& adj,
    int V,
    vector<int>& ordering,
    vector<int>& cycle)
{
    vector<int> state(V, 0);

    vector<int> activePath;

    stack<int> topoStack;

    // Handle disconnected components
    for (int i = 0; i < V; i++)
    {
        if (state[i] == 0)
        {
            if (!dfsTopo(
                i,
                adj,
                state,
                activePath,
                topoStack,
                cycle))
            {
                return false;
            }
        }
    }

    // Extract topological ordering
    while (!topoStack.empty())
    {
        ordering.push_back(topoStack.top());
        topoStack.pop();
    }

    return true;
}

// Display a sequence of vertices
void displaySequence(const vector<int>& sequence)
{
    for (int i = 0; i < sequence.size(); i++)
    {
        cout << sequence[i];

        if (i != sequence.size() - 1)
            cout << " -> ";
    }

    cout << "\n";
}

int main()
{
    int V, E;

    cout << "Enter number of vertices: ";
    cin >> V;

    if (V <= 0)
    {
        cout << "Invalid number of vertices.\n";
        return 0;
    }

    long long maxEdges = 1LL * V * (V - 1);

    cout << "Enter number of directed edges: ";
    cin >> E;

    if (E < 0 || E > maxEdges)
    {
        cout << "Invalid number of edges.\n";
        return 0;
    }

    vector<vector<int>> adj(V);

    set<pair<int, int>> edges;

    cout << "Enter directed edges (u v):\n";

    for (int i = 0; i < E; i++)
    {
        int u, v;

        cin >> u >> v;

        if (u < 0 || u >= V || v < 0 || v >= V)
        {
            cout << "Invalid vertex. Enter again.\n";
            i--;
            continue;
        }

        if (edges.find({u, v}) != edges.end())
        {
            cout << "Duplicate directed edge. Enter again.\n";
            i--;
            continue;
        }

        edges.insert({u, v});

        adj[u].push_back(v);
    }

    // Display graph
    cout << "\nDirected Adjacency List:\n";

    for (int i = 0; i < V; i++)
    {
        cout << i << " -> ";

        for (int neighbour : adj[i])
            cout << neighbour << " ";

        cout << "\n";
    }

    vector<int> ordering;
    vector<int> cycle;

    cout << "\nTopological Sorting Using DFS:\n";

    bool result = topologicalSort(
        adj,
        V,
        ordering,
        cycle
    );

    if (!result)
    {
        cout << "Topological ordering is not possible.\n";

        cout << "Cycle detected: ";
        displaySequence(cycle);
    }
    else
    {
        cout << "Topological Ordering:\n";
        displaySequence(ordering);

        cout << "\nTotal vertices: "
             << ordering.size() << "\n";

        cout << "Graph is a DAG.\n";
    }

    return 0;
}
