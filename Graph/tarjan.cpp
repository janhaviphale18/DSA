#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <set>
using namespace std;

class TarjanSCC
{
    int V;
    int timer;

    vector<int> disc;
    vector<int> low;

    vector<bool> onStack;

    stack<int> st;

    vector<vector<int>> components;

    // Recursive DFS
    void dfs(int u, vector<vector<int>>& adj)
    {
        // Assign discovery and low-link values
        disc[u] = low[u] = timer++;

        // Push vertex into stack
        st.push(u);
        onStack[u] = true;

        // Explore all neighbours
        for (int v : adj[u])
        {
            if (disc[v] == -1)
            {
                // Visit unvisited neighbour
                dfs(v, adj);

                low[u] = min(low[u], low[v]);
            }
            else if (onStack[v])
            {
                // Back edge to a vertex still on stack
                low[u] = min(low[u], disc[v]);
            }
        }

        // Check whether u is the root of an SCC
        if (low[u] == disc[u])
        {
            vector<int> component;

            while (true)
            {
                int vertex = st.top();
                st.pop();

                onStack[vertex] = false;

                component.push_back(vertex);

                if (vertex == u)
                    break;
            }

            sort(component.begin(), component.end());

            components.push_back(component);
        }
    }

public:

    TarjanSCC(int n)
    {
        V = n;
        timer = 0;

        disc.assign(V, -1);
        low.assign(V, -1);

        onStack.assign(V, false);
    }

    // Find all SCCs
    vector<vector<int>> findSCCs(
        vector<vector<int>>& adj)
    {
        for (int i = 0; i < V; i++)
        {
            if (disc[i] == -1)
            {
                dfs(i, adj);
            }
        }

        return components;
    }

    // Display discovery and low-link values
    void displayValues()
    {
        cout << "\nDiscovery and Low-Link Values:\n";

        cout << "Vertex\tDisc\tLow\n";

        for (int i = 0; i < V; i++)
        {
            cout << i << "\t"
                 << disc[i] << "\t"
                 << low[i] << "\n";
        }
    }
};

// Display SCCs
void displayComponents(
    const vector<vector<int>>& components)
{
    for (int i = 0; i < components.size(); i++)
    {
        cout << "SCC " << i + 1 << ": ";

        for (int vertex : components[i])
        {
            cout << vertex << " ";
        }

        cout << "\n";
    }
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

        if (u == v)
        {
            cout << "Self-loops are not allowed. Enter again.\n";
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

    // Display directed graph
    cout << "\nDirected Adjacency List:\n";

    for (int i = 0; i < V; i++)
    {
        cout << i << " -> ";

        for (int neighbour : adj[i])
        {
            cout << neighbour << " ";
        }

        cout << "\n";
    }

    // Run Tarjan's algorithm
    TarjanSCC tarjan(V);

    vector<vector<int>> components = tarjan.findSCCs(adj);

    // Display discovery and low-link values
    tarjan.displayValues();

    // Display SCCs
    cout << "\nStrongly Connected Components:\n";

    displayComponents(components);

    cout << "\nTotal SCCs: "
         << components.size() << "\n";

    // Check strong connectivity
    cout << "\nConnectivity Result:\n";

    if (components.size() == 1)
    {
        cout << "The graph is strongly connected.\n";
    }
    else
    {
        cout << "The graph is NOT strongly connected.\n";
    }

    // Display SCC sizes
    cout << "\nSize of Each SCC:\n";

    for (int i = 0; i < components.size(); i++)
    {
        cout << "SCC " << i + 1 << ": "
             << components[i].size()
             << " vertices\n";
    }

    return 0;
}
