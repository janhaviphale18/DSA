#include <iostream>
#include <vector>
#include <set>
#include <limits>
#include <algorithm>
using namespace std;

// Perform DFS traversal
void DFS(int vertex, const vector<vector<int>> &adj,
         vector<bool> &visited)
{
    visited[vertex] = true;

    for (int neighbour : adj[vertex])
    {
        if (!visited[neighbour])
        {
            DFS(neighbour, adj, visited);
        }
    }
}

// Count connected components
int countComponents(int vertices,
                    const vector<vector<int>> &adj)
{
    vector<bool> visited(vertices, false);
    int components = 0;

    for (int i = 0; i < vertices; i++)
    {
        if (!visited[i])
        {
            DFS(i, adj, visited);
            components++;
        }
    }

    return components;
}

// Check whether a cycle exists
bool detectCycle(int vertex, int parent,
                 const vector<vector<int>> &adj,
                 vector<bool> &visited)
{
    visited[vertex] = true;

    for (int neighbour : adj[vertex])
    {
        if (!visited[neighbour])
        {
            if (detectCycle(neighbour, vertex, adj, visited))
            {
                return true;
            }
        }
        else if (neighbour != parent)
        {
            return true;
        }
    }

    return false;
}

// Check cycle in disconnected graph
bool hasCycle(int vertices, const vector<vector<int>> &adj)
{
    vector<bool> visited(vertices, false);

    for (int i = 0; i < vertices; i++)
    {
        if (!visited[i])
        {
            if (detectCycle(i, -1, adj, visited))
            {
                return true;
            }
        }
    }

    return false;
}

// Check path between two vertices
bool pathExists(int source, int destination,
                const vector<vector<int>> &adj)
{
    vector<bool> visited(adj.size(), false);

    DFS(source, adj, visited);

    return visited[destination];
}

int main()
{
    int vertices, edges;

    cout << "GRAPH PROPERTIES PROGRAM\n";

    // Accept number of vertices
    cout << "\nEnter number of vertices: ";
    cin >> vertices;

    if (cin.fail() || vertices <= 0 || vertices > 1000)
    {
        cout << "Invalid number of vertices!\n";
        return 1;
    }

    // Maximum edges in a simple undirected graph
    long long maxEdges = 1LL * vertices * (vertices - 1) / 2;

    // Accept number of edges
    cout << "Enter number of edges: ";
    cin >> edges;

    if (cin.fail() || edges < 0 || edges > maxEdges)
    {
        cout << "Invalid number of edges!\n";
        return 1;
    }

    // Adjacency list
    vector<vector<int>> adj(vertices);

    // Degree array
    vector<int> degree(vertices, 0);

    // Prevent duplicate edges
    set<pair<int, int>> uniqueEdges;

    // Accept edges
    cout << "\nEnter edges (vertex1 vertex2):\n";

    for (int i = 0; i < edges; i++)
    {
        while (true)
        {
            int u, v;

            cout << "Edge " << i + 1 << ": ";
            cin >> u >> v;

            if (cin.fail())
            {
                cout << "Invalid input!\n";

                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                continue;
            }

            if (u < 0 || u >= vertices ||
                v < 0 || v >= vertices)
            {
                cout << "Invalid vertex numbers!\n";
                continue;
            }

            if (u == v)
            {
                cout << "Self-loops are not allowed!\n";
                continue;
            }

            pair<int, int> edge = {min(u, v), max(u, v)};

            if (uniqueEdges.find(edge) != uniqueEdges.end())
            {
                cout << "Duplicate edge! Try again.\n";
                continue;
            }

            uniqueEdges.insert(edge);

            // Add undirected connection
            adj[u].push_back(v);
            adj[v].push_back(u);

            degree[u]++;
            degree[v]++;

            break;
        }
    }

    // Display graph properties
    cout << "\n========== GRAPH PROPERTIES ==========\n";

    cout << "Total Vertices: " << vertices << endl;
    cout << "Total Edges: " << edges << endl;

    // Connected components
    int components = countComponents(vertices, adj);

    cout << "\nConnected Components: " << components << endl;

    if (components == 1)
    {
        cout << "Graph Status: Connected\n";
    }
    else
    {
        cout << "Graph Status: Disconnected\n";
    }

    // Check complete graph
    bool complete = (edges == maxEdges);

    cout << "\nComplete Graph: ";

    if (complete)
    {
        cout << "Yes\n";
    }
    else
    {
        cout << "No\n";
    }

    // Check regular graph
    bool regular = true;

    for (int i = 1; i < vertices; i++)
    {
        if (degree[i] != degree[0])
        {
            regular = false;
            break;
        }
    }

    cout << "Regular Graph: ";

    if (regular)
    {
        cout << "Yes (" << degree[0] << "-regular)\n";
    }
    else
    {
        cout << "No\n";
    }

    // Check cycle
    bool cycle = hasCycle(vertices, adj);

    cout << "Contains Cycle: ";

    if (cycle)
    {
        cout << "Yes\n";
    }
    else
    {
        cout << "No\n";
    }

    // Identify isolated vertices
    cout << "Isolated Vertices: ";

    bool isolated = false;

    for (int i = 0; i < vertices; i++)
    {
        if (degree[i] == 0)
        {
            cout << i << " ";
            isolated = true;
        }
    }

    if (!isolated)
    {
        cout << "None";
    }

    cout << endl;

    // Check path between two vertices
    int source, destination;

    cout << "\nEnter source vertex for path checking: ";
    cin >> source;

    cout << "Enter destination vertex: ";
    cin >> destination;

    if (cin.fail() ||
        source < 0 || source >= vertices ||
        destination < 0 || destination >= vertices)
    {
        cout << "Invalid vertex selection!\n";
        return 1;
    }

    if (pathExists(source, destination, adj))
    {
        cout << "A path exists between "
             << source << " and " << destination << ".\n";
    }
    else
    {
        cout << "No path exists between "
             << source << " and " << destination << ".\n";
    }

    return 0;
}