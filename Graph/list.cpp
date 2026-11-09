#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <string>
using namespace std;

// Read and validate integer input
bool readInteger(const string &message, int &value)
{
    while (true)
    {
        cout << message;

        if (cin >> value)
        {
            return true;
        }

        if (cin.eof())
        {
            return false;
        }

        cout << "Invalid input! Enter an integer.\n";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Validate vertex number
bool validVertex(int vertex, int vertices)
{
    return vertex >= 0 && vertex < vertices;
}

// Check whether an edge exists
bool edgeExists(const vector<vector<int>> &adj, int u, int v)
{
    return find(adj[u].begin(), adj[u].end(), v)
           != adj[u].end();
}

// Insert an edge
bool insertEdge(vector<vector<int>> &adj,
                int u, int v, bool directed)
{
    int vertices = static_cast<int>(adj.size());

    if (!validVertex(u, vertices) ||
        !validVertex(v, vertices) || u == v)
    {
        return false;
    }

    if (edgeExists(adj, u, v))
    {
        return false;
    }

    adj[u].push_back(v);

    if (!directed)
    {
        adj[v].push_back(u);
    }

    return true;
}

// Delete an edge
bool deleteEdge(vector<vector<int>> &adj,
                int u, int v, bool directed)
{
    int vertices = static_cast<int>(adj.size());

    if (!validVertex(u, vertices) ||
        !validVertex(v, vertices))
    {
        return false;
    }

    if (!edgeExists(adj, u, v))
    {
        return false;
    }

    // Remove destination from source's list
    auto &sourceList = adj[u];

    sourceList.erase(
        remove(sourceList.begin(), sourceList.end(), v),
        sourceList.end()
    );

    // Remove reverse connection for undirected graph
    if (!directed)
    {
        auto &destinationList = adj[v];

        destinationList.erase(
            remove(destinationList.begin(),
                   destinationList.end(), u),
            destinationList.end()
        );
    }

    return true;
}

// Display adjacency list
void displayList(const vector<vector<int>> &adj)
{
    cout << "\nAdjacency List:\n";

    for (int i = 0; i < static_cast<int>(adj.size()); i++)
    {
        cout << "Vertex " << i << " -> ";

        if (adj[i].empty())
        {
            cout << "NULL";
        }
        else
        {
            for (int neighbour : adj[i])
            {
                cout << neighbour << " -> ";
            }

            cout << "NULL";
        }

        cout << "\n";
    }
}

// Display adjacent vertices
void displayAdjacent(const vector<vector<int>> &adj,
                     int vertex)
{
    cout << "\nAdjacent vertices of " << vertex << ": ";

    if (adj[vertex].empty())
    {
        cout << "None";
    }
    else
    {
        for (int neighbour : adj[vertex])
        {
            cout << neighbour << " ";
        }
    }

    cout << "\n";
}

// Display degree information
void displayDegrees(const vector<vector<int>> &adj,
                    bool directed)
{
    int vertices = static_cast<int>(adj.size());

    cout << "\nDegree Information:\n";

    if (!directed)
    {
        for (int i = 0; i < vertices; i++)
        {
            cout << "Degree of vertex " << i
                 << " = " << adj[i].size() << "\n";
        }
    }
    else
    {
        vector<int> indegree(vertices, 0);

        // Calculate indegree of every vertex
        for (int i = 0; i < vertices; i++)
        {
            for (int neighbour : adj[i])
            {
                indegree[neighbour]++;
            }
        }

        for (int i = 0; i < vertices; i++)
        {
            cout << "Vertex " << i
                 << " | Indegree: " << indegree[i]
                 << " | Outdegree: " << adj[i].size()
                 << "\n";
        }
    }
}

int main()
{
    int vertices, edges, graphType;

    cout << "ADJACENCY LIST REPRESENTATION\n";

    cout << "\nSelect graph type:\n";
    cout << "1. Undirected Graph\n";
    cout << "2. Directed Graph\n";

    if (!readInteger("Enter your choice: ", graphType))
    {
        return 1;
    }

    if (graphType != 1 && graphType != 2)
    {
        cout << "Invalid graph type!\n";
        return 1;
    }

    bool directed = (graphType == 2);

    // Accept number of vertices
    if (!readInteger("\nEnter number of vertices: ", vertices))
    {
        return 1;
    }

    if (vertices <= 0 || vertices > 1000)
    {
        cout << "Invalid number of vertices!\n";
        return 1;
    }

    // Calculate maximum possible edges
    long long maxEdges;

    if (directed)
    {
        maxEdges = 1LL * vertices * (vertices - 1);
    }
    else
    {
        maxEdges = 1LL * vertices * (vertices - 1) / 2;
    }

    // Accept number of edges
    if (!readInteger("Enter number of edges: ", edges))
    {
        return 1;
    }

    if (edges < 0 || edges > maxEdges)
    {
        cout << "Invalid number of edges!\n";
        return 1;
    }

    // Initialize adjacency list
    vector<vector<int>> adj(vertices);

    cout << "\nEnter graph edges:\n";

    // Accept initial edges
    for (int i = 0; i < edges; i++)
    {
        while (true)
        {
            int u, v;

            cout << "\nEdge " << i + 1 << ":\n";

            if (!readInteger("Enter source vertex: ", u) ||
                !readInteger("Enter destination vertex: ", v))
            {
                return 1;
            }

            if (!validVertex(u, vertices) ||
                !validVertex(v, vertices))
            {
                cout << "Invalid vertex numbers!\n";
                continue;
            }

            if (u == v)
            {
                cout << "Self-loops are not allowed!\n";
                continue;
            }

            if (edgeExists(adj, u, v))
            {
                cout << "Duplicate edge! Try again.\n";
                continue;
            }

            insertEdge(adj, u, v, directed);
            break;
        }
    }

    // Display original graph
    cout << "\n========== ORIGINAL GRAPH ==========\n";

    displayList(adj);

    // Search for an edge
    int source, destination;

    cout << "\n========== EDGE SEARCH ==========\n";

    if (!readInteger("Enter source vertex: ", source) ||
        !readInteger("Enter destination vertex: ", destination))
    {
        return 1;
    }

    if (!validVertex(source, vertices) ||
        !validVertex(destination, vertices))
    {
        cout << "Invalid vertex selection!\n";
    }
    else if (edgeExists(adj, source, destination))
    {
        cout << "Edge exists between "
             << source << " and " << destination << ".\n";
    }
    else
    {
        cout << "Edge does not exist between "
             << source << " and " << destination << ".\n";
    }

    // Insert a new edge
    int newSource, newDestination;

    cout << "\n========== INSERT EDGE ==========\n";

    if (!readInteger("Enter source vertex: ", newSource) ||
        !readInteger("Enter destination vertex: ", newDestination))
    {
        return 1;
    }

    if (insertEdge(adj, newSource, newDestination, directed))
    {
        cout << "Edge inserted successfully.\n";
    }
    else
    {
        cout << "Edge insertion failed! Invalid, duplicate "
             << "or self-loop edge.\n";
    }

    // Delete an existing edge
    int deleteSource, deleteDestination;

    cout << "\n========== DELETE EDGE ==========\n";

    if (!readInteger("Enter source vertex: ", deleteSource) ||
        !readInteger("Enter destination vertex: ", deleteDestination))
    {
        return 1;
    }

    if (deleteEdge(adj, deleteSource, deleteDestination, directed))
    {
        cout << "Edge deleted successfully.\n";
    }
    else
    {
        cout << "Edge deletion failed! Invalid or missing edge.\n";
    }

    // Display updated graph
    cout << "\n========== UPDATED GRAPH ==========\n";

    displayList(adj);

    // Display adjacent vertices
    int selectedVertex;

    cout << "\n========== ADJACENT VERTICES ==========\n";

    if (!readInteger("Enter vertex: ", selectedVertex))
    {
        return 1;
    }

    if (!validVertex(selectedVertex, vertices))
    {
        cout << "Invalid vertex!\n";
    }
    else
    {
        displayAdjacent(adj, selectedVertex);
    }

    // Display degree information
    displayDegrees(adj, directed);

    return 0;
}