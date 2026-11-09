#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <limits>
using namespace std;

struct Edge
{
    int source;
    int destination;
};

int readInteger(string message)
{
    int value;

    while (true)
    {
        cout << message;

        if (cin >> value)
        {
            return value;
        }

        cout << "Invalid input! Enter an integer.\n";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

bool validVertex(int vertex, int vertices)
{
    return vertex >= 0 && vertex < vertices;
}

// Checks whether an edge exists in the adjacency matrix
bool matrixSearch(const vector<vector<int>>& matrix, int source, int destination)
{
    return matrix[source][destination] == 1;
}

// Checks whether an edge exists in the adjacency list
bool listSearch(const vector<vector<int>>& adj, int source, int destination)
{
    return find(adj[source].begin(), adj[source].end(), destination)
           != adj[source].end();
}

// Checks whether an edge exists in the edge list
bool edgeListSearch(const vector<Edge>& edges, int source, int destination,
                    bool directed)
{
    for (const Edge& edge : edges)
    {
        if (edge.source == source && edge.destination == destination)
        {
            return true;
        }

        if (!directed &&
            edge.source == destination &&
            edge.destination == source)
        {
            return true;
        }
    }

    return false;
}

// Displays adjacency matrix
void displayMatrix(const vector<vector<int>>& matrix, int vertices)
{
    cout << "\nADJACENCY MATRIX\n\n";

    cout << "    ";

    for (int i = 0; i < vertices; i++)
    {
        cout << i << " ";
    }

    cout << "\n";

    for (int i = 0; i < vertices; i++)
    {
        cout << i << " | ";

        for (int j = 0; j < vertices; j++)
        {
            cout << matrix[i][j] << " ";
        }

        cout << "\n";
    }
}

// Displays adjacency list
void displayList(const vector<vector<int>>& adj, int vertices)
{
    cout << "\nADJACENCY LIST\n\n";

    for (int i = 0; i < vertices; i++)
    {
        cout << i << " -> ";

        for (int neighbour : adj[i])
        {
            cout << neighbour << " ";
        }

        if (adj[i].empty())
        {
            cout << "NULL";
        }

        cout << "\n";
    }
}

// Displays edge list
void displayEdgeList(const vector<Edge>& edges)
{
    cout << "\nEDGE LIST\n\n";

    if (edges.empty())
    {
        cout << "No edges present.\n";
        return;
    }

    for (const Edge& edge : edges)
    {
        cout << "(" << edge.source
             << ", " << edge.destination << ")\n";
    }
}

// Compares storage requirements
void compareStorage(int vertices, int edgeCount,
                    bool directed, const vector<vector<int>>& adj)
{
    long long matrixEntries = 1LL * vertices * vertices;

    long long adjacencyEntries = 0;

    for (const auto& neighbours : adj)
    {
        adjacencyEntries += neighbours.size();
    }

    long long listSlots = vertices + adjacencyEntries;

    cout << "\nSTORAGE COMPARISON\n\n";

    cout << "Adjacency Matrix:\n";
    cout << "  Matrix entries = " << matrixEntries << "\n";

    cout << "\nAdjacency List:\n";
    cout << "  Vertex list containers = " << vertices << "\n";
    cout << "  Neighbour entries = " << adjacencyEntries << "\n";
    cout << "  Conceptual slots = " << listSlots << "\n";

    cout << "\nEdge List:\n";
    cout << "  Edge records = " << edgeCount << "\n";
    cout << "  Endpoint integer fields = " << 2LL * edgeCount << "\n";

    cout << "\nSPACE COMPLEXITY\n\n";

    cout << "Adjacency Matrix: O(V^2)\n";
    cout << "Adjacency List:   O(V + E)\n";
    cout << "Edge List:        O(E) for edge records\n";

    cout << "\nNote: The adjacency list also maintains V vertex containers.\n";
    cout << "The edge list stores each edge only once.\n";

    if (directed)
    {
        cout << "For a directed graph, adjacency lists store each edge once.\n";
    }
    else
    {
        cout << "For an undirected graph, adjacency lists store each edge twice.\n";
    }
}

int main()
{
    int vertices, edges;
    int directedChoice;

    cout << "GRAPH REPRESENTATION COMPARISON\n";
    cout << "-------------------------------\n";

    vertices = readInteger("Enter number of vertices: ");

    while (vertices <= 0 || vertices > 1000)
    {
        cout << "Vertices must be between 1 and 1000.\n";
        vertices = readInteger("Enter number of vertices: ");
    }

    cout << "\nChoose graph type:\n";
    cout << "0. Undirected Graph\n";
    cout << "1. Directed Graph\n";

    directedChoice = readInteger("Enter your choice: ");

    while (directedChoice != 0 && directedChoice != 1)
    {
        cout << "Invalid choice! Enter 0 or 1.\n";
        directedChoice = readInteger("Enter your choice: ");
    }

    bool directed = (directedChoice == 1);

    int maximumEdges;

    if (directed)
    {
        maximumEdges = vertices * (vertices - 1);
    }
    else
    {
        maximumEdges = vertices * (vertices - 1) / 2;
    }

    edges = readInteger("\nEnter number of edges: ");

    while (edges < 0 || edges > maximumEdges)
    {
        cout << "Invalid edge count! Maximum possible edges = "
             << maximumEdges << "\n";

        edges = readInteger("Enter number of edges: ");
    }

    // Creating all three graph representations

    vector<vector<int>> matrix(
        vertices, vector<int>(vertices, 0)
    );

    vector<vector<int>> adj(vertices);

    vector<Edge> edgeList;

    set<pair<int, int>> insertedEdges;

    cout << "\nEnter the edges:\n";

    for (int i = 0; i < edges; i++)
    {
        int source, destination;

        cout << "\nEdge " << i + 1 << ":\n";

        source = readInteger("Enter source vertex: ");
        destination = readInteger("Enter destination vertex: ");

        while (!validVertex(source, vertices) ||
               !validVertex(destination, vertices) ||
               source == destination)
        {
            cout << "Invalid vertices or self-loop!\n";
            cout << "Enter valid and different vertex numbers.\n";

            source = readInteger("Enter source vertex: ");
            destination = readInteger("Enter destination vertex: ");
        }

        pair<int, int> key;

        if (directed)
        {
            key = {source, destination};
        }
        else
        {
            key = {min(source, destination),
                   max(source, destination)};
        }

        while (insertedEdges.count(key))
        {
            cout << "Duplicate edge! Enter a different edge.\n";

            source = readInteger("Enter source vertex: ");
            destination = readInteger("Enter destination vertex: ");

            while (!validVertex(source, vertices) ||
                   !validVertex(destination, vertices) ||
                   source == destination)
            {
                cout << "Invalid vertices or self-loop!\n";

                source = readInteger("Enter source vertex: ");
                destination = readInteger("Enter destination vertex: ");
            }

            if (directed)
            {
                key = {source, destination};
            }
            else
            {
                key = {min(source, destination),
                       max(source, destination)};
            }
        }

        insertedEdges.insert(key);

        // Adjacency Matrix
        matrix[source][destination] = 1;

        // Adjacency List
        adj[source].push_back(destination);

        // Edge List
        edgeList.push_back({source, destination});

        // Additional reverse edge for undirected graphs
        if (!directed)
        {
            matrix[destination][source] = 1;
            adj[destination].push_back(source);
        }
    }

    // Display all three representations

    displayMatrix(matrix, vertices);

    displayList(adj, vertices);

    displayEdgeList(edgeList);

    // Compare edge searching

    cout << "\nEDGE SEARCH COMPARISON\n\n";

    int source = readInteger("Enter source vertex to search: ");
    int destination = readInteger("Enter destination vertex to search: ");

    while (!validVertex(source, vertices) ||
           !validVertex(destination, vertices) ||
           source == destination)
    {
        cout << "Invalid vertices! Enter two different valid vertices.\n";

        source = readInteger("Enter source vertex to search: ");
        destination = readInteger("Enter destination vertex to search: ");
    }

    cout << "\nSearching edge (" << source
         << ", " << destination << "):\n";

    cout << "Adjacency Matrix: "
         << (matrixSearch(matrix, source, destination)
             ? "Edge found" : "Edge not found") << "\n";

    cout << "Adjacency List:   "
         << (listSearch(adj, source, destination)
             ? "Edge found" : "Edge not found") << "\n";

    cout << "Edge List:        "
         << (edgeListSearch(edgeList, source, destination, directed)
             ? "Edge found" : "Edge not found") << "\n";

    // Compare storage requirements

    compareStorage(vertices, edges, directed, adj);

    return 0;
}
