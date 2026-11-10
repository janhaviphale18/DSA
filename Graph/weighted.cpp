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
    int weight;
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

int findEdge(const vector<Edge>& edges, int source,
             int destination, bool directed)
{
    for (int i = 0; i < (int)edges.size(); i++)
    {
        if (edges[i].source == source &&
            edges[i].destination == destination)
        {
            return i;
        }

        if (!directed &&
            edges[i].source == destination &&
            edges[i].destination == source)
        {
            return i;
        }
    }

    return -1;
}

void displayMatrix(const vector<vector<int>>& matrix,
                   const vector<vector<bool>>& exists,
                   int vertices)
{
    cout << "\nWEIGHTED ADJACENCY MATRIX\n\n";

    cout << "     ";

    for (int i = 0; i < vertices; i++)
    {
        cout << i << "     ";
    }

    cout << "\n";

    for (int i = 0; i < vertices; i++)
    {
        cout << i << " | ";

        for (int j = 0; j < vertices; j++)
        {
            if (exists[i][j])
            {
                cout << matrix[i][j] << "     ";
            }
            else
            {
                cout << "-     ";
            }
        }

        cout << "\n";
    }
}

void displayList(const vector<vector<pair<int, int>>>& adj,
                 int vertices)
{
    cout << "\nWEIGHTED ADJACENCY LIST\n\n";

    for (int i = 0; i < vertices; i++)
    {
        cout << i << " -> ";

        if (adj[i].empty())
        {
            cout << "NULL";
        }

        for (const auto& neighbour : adj[i])
        {
            cout << "(" << neighbour.first
                 << ", weight " << neighbour.second << ") ";
        }

        cout << "\n";
    }
}

void displayEdgeList(const vector<Edge>& edges)
{
    cout << "\nWEIGHTED EDGE LIST\n\n";

    if (edges.empty())
    {
        cout << "No edges present.\n";
        return;
    }

    for (const Edge& edge : edges)
    {
        cout << "(" << edge.source << ", "
             << edge.destination << ", "
             << edge.weight << ")\n";
    }
}

int main()
{
    int vertices, edgeCount;
    int directedChoice;

    cout << "WEIGHTED GRAPH REPRESENTATION\n";
    cout << "-----------------------------\n";

    vertices = readInteger("Enter number of vertices: ");

    while (vertices <= 0 || vertices > 1000)
    {
        cout << "Enter vertices between 1 and 1000.\n";
        vertices = readInteger("Enter number of vertices: ");
    }

    cout << "\nChoose graph type:\n";
    cout << "0. Undirected weighted graph\n";
    cout << "1. Directed weighted graph\n";

    directedChoice = readInteger("Enter choice: ");

    while (directedChoice != 0 && directedChoice != 1)
    {
        cout << "Invalid choice!\n";
        directedChoice = readInteger("Enter choice: ");
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

    edgeCount = readInteger("\nEnter number of edges: ");

    while (edgeCount < 0 || edgeCount > maximumEdges)
    {
        cout << "Invalid edge count! Maximum = "
             << maximumEdges << "\n";

        edgeCount = readInteger("Enter number of edges: ");
    }

    vector<vector<int>> matrix(
        vertices, vector<int>(vertices, 0)
    );

    vector<vector<bool>> exists(
        vertices, vector<bool>(vertices, false)
    );

    vector<vector<pair<int, int>>> adj(vertices);

    vector<Edge> edges;

    set<pair<int, int>> insertedEdges;

    cout << "\nEnter edge details:\n";

    for (int i = 0; i < edgeCount; i++)
    {
        int source, destination, weight;

        cout << "\nEdge " << i + 1 << ":\n";

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
            cout << "Duplicate edge! Enter another edge.\n";

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

        weight = readInteger("Enter edge weight: ");

        // Weighted adjacency matrix
        matrix[source][destination] = weight;
        exists[source][destination] = true;

        // Weighted adjacency list
        adj[source].push_back({destination, weight});

        // Weighted edge list
        edges.push_back({source, destination, weight});

        // Reverse connection for undirected graph
        if (!directed)
        {
            matrix[destination][source] = weight;
            exists[destination][source] = true;

            adj[destination].push_back({source, weight});
        }
    }

    // Display all representations

    displayMatrix(matrix, exists, vertices);

    displayList(adj, vertices);

    displayEdgeList(edges);

    // Search for an edge

    cout << "\nEDGE SEARCH\n";

    int source = readInteger("Enter source vertex: ");
    int destination = readInteger("Enter destination vertex: ");

    while (!validVertex(source, vertices) ||
           !validVertex(destination, vertices) ||
           source == destination)
    {
        cout << "Invalid vertices!\n";

        source = readInteger("Enter source vertex: ");
        destination = readInteger("Enter destination vertex: ");
    }

    int index = findEdge(edges, source, destination, directed);

    if (index == -1)
    {
        cout << "Edge does not exist.\n";
    }
    else
    {
        cout << "Edge exists.\n";
        cout << "Weight = " << edges[index].weight << "\n";
    }

    // Calculate total edge weight

    long long totalWeight = 0;

    for (const Edge& edge : edges)
    {
        totalWeight += edge.weight;
    }

    cout << "\nTotal weight of all edges = "
         << totalWeight << "\n";

    cout << "\nGraph representation completed successfully.\n";

    return 0;
}
