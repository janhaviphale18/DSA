#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <string>
using namespace std;

// Structure to represent an edge
struct Edge
{
    int source;
    int destination;
    int weight;
};

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

// Find an edge
int findEdge(const vector<Edge> &edges,
             int u, int v, bool directed)
{
    for (int i = 0; i < static_cast<int>(edges.size()); i++)
    {
        if (directed)
        {
            if (edges[i].source == u &&
                edges[i].destination == v)
            {
                return i;
            }
        }
        else
        {
            if ((edges[i].source == u &&
                 edges[i].destination == v) ||
                (edges[i].source == v &&
                 edges[i].destination == u))
            {
                return i;
            }
        }
    }

    return -1;
}

// Insert a new edge
bool insertEdge(vector<Edge> &edges, int u, int v,
                int weight, int vertices, bool directed)
{
    if (!validVertex(u, vertices) ||
        !validVertex(v, vertices) || u == v)
    {
        return false;
    }

    if (findEdge(edges, u, v, directed) != -1)
    {
        return false;
    }

    edges.push_back({u, v, weight});

    return true;
}

// Delete an edge
bool deleteEdge(vector<Edge> &edges,
                int u, int v, bool directed)
{
    int position = findEdge(edges, u, v, directed);

    if (position == -1)
    {
        return false;
    }

    edges.erase(edges.begin() + position);

    return true;
}

// Display all edges
void displayEdges(const vector<Edge> &edges, bool weighted)
{
    cout << "\nEdge List:\n";

    if (edges.empty())
    {
        cout << "No edges present.\n";
        return;
    }

    cout << "Edge\tSource\tDestination";

    if (weighted)
    {
        cout << "\tWeight";
    }

    cout << "\n";

    for (int i = 0; i < static_cast<int>(edges.size()); i++)
    {
        cout << i + 1 << "\t"
             << edges[i].source << "\t"
             << edges[i].destination;

        if (weighted)
        {
            cout << "\t\t" << edges[i].weight;
        }

        cout << "\n";
    }
}

// Display edges connected to a selected vertex
void displayIncidentEdges(const vector<Edge> &edges,
                          int vertex, bool weighted)
{
    bool found = false;

    cout << "\nEdges connected to vertex "
         << vertex << ":\n";

    for (const Edge &edge : edges)
    {
        if (edge.source == vertex ||
            edge.destination == vertex)
        {
            cout << edge.source << " -> "
                 << edge.destination;

            if (weighted)
            {
                cout << " (Weight: " << edge.weight << ")";
            }

            cout << "\n";
            found = true;
        }
    }

    if (!found)
    {
        cout << "No connected edges.\n";
    }
}

// Calculate degree information
void displayDegrees(const vector<Edge> &edges,
                    int vertices, bool directed)
{
    vector<int> degree(vertices, 0);
    vector<int> indegree(vertices, 0);
    vector<int> outdegree(vertices, 0);

    for (const Edge &edge : edges)
    {
        if (directed)
        {
            outdegree[edge.source]++;
            indegree[edge.destination]++;
        }
        else
        {
            degree[edge.source]++;
            degree[edge.destination]++;
        }
    }

    cout << "\nDegree Information:\n";

    for (int i = 0; i < vertices; i++)
    {
        if (directed)
        {
            cout << "Vertex " << i
                 << " | Indegree: " << indegree[i]
                 << " | Outdegree: " << outdegree[i] << "\n";
        }
        else
        {
            cout << "Vertex " << i
                 << " | Degree: " << degree[i] << "\n";
        }
    }

    // Identify isolated vertices
    cout << "\nIsolated Vertices: ";

    bool isolatedFound = false;

    for (int i = 0; i < vertices; i++)
    {
        bool isolated;

        if (directed)
        {
            isolated = (indegree[i] == 0 &&
                        outdegree[i] == 0);
        }
        else
        {
            isolated = (degree[i] == 0);
        }

        if (isolated)
        {
            cout << i << " ";
            isolatedFound = true;
        }
    }

    if (!isolatedFound)
    {
        cout << "None";
    }

    cout << "\n";
}

int main()
{
    int vertices, edges;
    int graphType, edgeType;

    cout << "EDGE LIST REPRESENTATION\n";

    // Select graph direction
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

    // Select weighted or unweighted graph
    cout << "\nSelect edge type:\n";
    cout << "1. Unweighted Graph\n";
    cout << "2. Weighted Graph\n";

    if (!readInteger("Enter your choice: ", edgeType))
    {
        return 1;
    }

    if (edgeType != 1 && edgeType != 2)
    {
        cout << "Invalid edge type!\n";
        return 1;
    }

    bool weighted = (edgeType == 2);

    // Accept vertices
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

    // Store edges
    vector<Edge> graphEdges;

    cout << "\nEnter graph edges:\n";

    for (int i = 0; i < edges; i++)
    {
        while (true)
        {
            int u, v, weight = 0;

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

            if (findEdge(graphEdges, u, v, directed) != -1)
            {
                cout << "Duplicate edge! Try again.\n";
                continue;
            }

            if (weighted)
            {
                if (!readInteger("Enter edge weight: ", weight))
                {
                    return 1;
                }
            }

            graphEdges.push_back({u, v, weight});

            break;
        }
    }

    // Display original graph
    cout << "\n========== ORIGINAL GRAPH ==========\n";

    displayEdges(graphEdges, weighted);

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
    else
    {
        int position = findEdge(
            graphEdges, source, destination, directed
        );

        if (position != -1)
        {
            cout << "Edge exists.\n";

            if (weighted)
            {
                cout << "Edge weight: "
                     << graphEdges[position].weight << "\n";
            }
        }
        else
        {
            cout << "Edge does not exist.\n";
        }
    }

    // Insert a new edge
    int newSource, newDestination;
    int newWeight = 0;

    cout << "\n========== INSERT EDGE ==========\n";

    if (!readInteger("Enter source vertex: ", newSource) ||
        !readInteger("Enter destination vertex: ", newDestination))
    {
        return 1;
    }

    bool validNewVertices =
        validVertex(newSource, vertices) &&
        validVertex(newDestination, vertices);

    if (!validNewVertices || newSource == newDestination)
    {
        cout << "Invalid vertices or self-loop!\n";
    }
    else
    {
        if (weighted)
        {
            if (!readInteger("Enter edge weight: ", newWeight))
            {
                return 1;
            }
        }

        if (insertEdge(graphEdges, newSource, newDestination,
                       newWeight, vertices, directed))
        {
            cout << "Edge inserted successfully.\n";
        }
        else
        {
            cout << "Edge already exists!\n";
        }
    }

    // Delete an edge
    int deleteSource, deleteDestination;

    cout << "\n========== DELETE EDGE ==========\n";

    if (!readInteger("Enter source vertex: ", deleteSource) ||
        !readInteger("Enter destination vertex: ", deleteDestination))
    {
        return 1;
    }

    if (!validVertex(deleteSource, vertices) ||
        !validVertex(deleteDestination, vertices))
    {
        cout << "Invalid vertex selection!\n";
    }
    else if (deleteEdge(graphEdges, deleteSource,
                        deleteDestination, directed))
    {
        cout << "Edge deleted successfully.\n";
    }
    else
    {
        cout << "Edge does not exist!\n";
    }

    // Display updated edge list
    cout << "\n========== UPDATED GRAPH ==========\n";

    displayEdges(graphEdges, weighted);

    // Display incident edges
    int selectedVertex;

    cout << "\n========== CONNECTED EDGES ==========\n";

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
        displayIncidentEdges(
            graphEdges, selectedVertex, weighted
        );
    }

    // Display degrees
    displayDegrees(graphEdges, vertices, directed);

    return 0;
}