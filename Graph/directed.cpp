#include <iostream>
#include <vector>
#include <set>
#include <limits>
#include <algorithm>
using namespace std;

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

bool edgeExists(const vector<vector<int>>& adj,
                int source, int destination)
{
    return find(adj[source].begin(),
                adj[source].end(),
                destination) != adj[source].end();
}

void addEdge(vector<vector<int>>& adj,
             int source, int destination)
{
    adj[source].push_back(destination);
}

bool deleteEdge(vector<vector<int>>& adj,
                int source, int destination)
{
    auto& neighbours = adj[source];

    auto it = find(neighbours.begin(),
                   neighbours.end(),
                   destination);

    if (it == neighbours.end())
    {
        return false;
    }

    neighbours.erase(it);

    return true;
}

void displayGraph(const vector<vector<int>>& adj, int vertices)
{
    cout << "\nDIRECTED GRAPH - ADJACENCY LIST\n\n";

    for (int i = 0; i < vertices; i++)
    {
        cout << i << " -> ";

        if (adj[i].empty())
        {
            cout << "NULL";
        }

        for (int neighbour : adj[i])
        {
            cout << neighbour << " ";
        }

        cout << "\n";
    }
}

void calculateDegrees(const vector<vector<int>>& adj,
                      int vertices)
{
    vector<int> indegree(vertices, 0);
    vector<int> outdegree(vertices, 0);

    for (int i = 0; i < vertices; i++)
    {
        outdegree[i] = adj[i].size();

        for (int neighbour : adj[i])
        {
            indegree[neighbour]++;
        }
    }

    cout << "\nVERTEX DEGREE INFORMATION\n\n";

    for (int i = 0; i < vertices; i++)
    {
        cout << "Vertex " << i
             << " | Indegree = " << indegree[i]
             << " | Outdegree = " << outdegree[i] << "\n";
    }

    cout << "\nSOURCE VERTICES (Indegree = 0)\n";

    bool found = false;

    for (int i = 0; i < vertices; i++)
    {
        if (indegree[i] == 0)
        {
            cout << i << " ";
            found = true;
        }
    }

    if (!found)
    {
        cout << "None";
    }

    cout << "\n\nSINK VERTICES (Outdegree = 0)\n";

    found = false;

    for (int i = 0; i < vertices; i++)
    {
        if (outdegree[i] == 0)
        {
            cout << i << " ";
            found = true;
        }
    }

    if (!found)
    {
        cout << "None";
    }

    cout << "\n\nISOLATED VERTICES (Indegree = 0 and Outdegree = 0)\n";

    found = false;

    for (int i = 0; i < vertices; i++)
    {
        if (indegree[i] == 0 && outdegree[i] == 0)
        {
            cout << i << " ";
            found = true;
        }
    }

    if (!found)
    {
        cout << "None";
    }

    cout << "\n";
}

void displayIncomingEdges(const vector<vector<int>>& adj,
                          int vertices, int target)
{
    cout << "\nINCOMING EDGES OF VERTEX " << target << "\n";

    bool found = false;

    for (int i = 0; i < vertices; i++)
    {
        for (int neighbour : adj[i])
        {
            if (neighbour == target)
            {
                cout << i << " -> " << target << "\n";
                found = true;
            }
        }
    }

    if (!found)
    {
        cout << "No incoming edges.\n";
    }
}

void displayOutgoingEdges(const vector<vector<int>>& adj,
                          int source)
{
    cout << "\nOUTGOING EDGES OF VERTEX " << source << "\n";

    if (adj[source].empty())
    {
        cout << "No outgoing edges.\n";
        return;
    }

    for (int neighbour : adj[source])
    {
        cout << source << " -> " << neighbour << "\n";
    }
}

void dfs(const vector<vector<int>>& adj,
         vector<bool>& visited, int vertex)
{
    visited[vertex] = true;

    for (int neighbour : adj[vertex])
    {
        if (!visited[neighbour])
        {
            dfs(adj, visited, neighbour);
        }
    }
}

bool isReachable(const vector<vector<int>>& adj,
                 int source, int destination, int vertices)
{
    vector<bool> visited(vertices, false);

    dfs(adj, visited, source);

    return visited[destination];
}

int main()
{
    int vertices, edges;

    cout << "DIRECTED GRAPH IMPLEMENTATION\n";
    cout << "-----------------------------\n";

    vertices = readInteger("Enter number of vertices: ");

    while (vertices <= 0 || vertices > 1000)
    {
        cout << "Enter vertices between 1 and 1000.\n";
        vertices = readInteger("Enter number of vertices: ");
    }

    int maximumEdges = vertices * (vertices - 1);

    edges = readInteger("Enter number of directed edges: ");

    while (edges < 0 || edges > maximumEdges)
    {
        cout << "Invalid edge count! Maximum possible edges = "
             << maximumEdges << "\n";

        edges = readInteger("Enter number of directed edges: ");
    }

    vector<vector<int>> adj(vertices);

    set<pair<int, int>> insertedEdges;

    cout << "\nEnter directed edges:\n";

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

            source = readInteger("Enter source vertex: ");
            destination = readInteger("Enter destination vertex: ");
        }

        while (insertedEdges.count({source, destination}))
        {
            cout << "Duplicate directed edge!\n";

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
        }

        insertedEdges.insert({source, destination});

        addEdge(adj, source, destination);
    }

    // Display initial graph

    displayGraph(adj, vertices);

    // Display degree information

    calculateDegrees(adj, vertices);

    // Display incoming and outgoing edges

    int vertex = readInteger("\nEnter vertex to inspect: ");

    while (!validVertex(vertex, vertices))
    {
        cout << "Invalid vertex!\n";
        vertex = readInteger("Enter vertex to inspect: ");
    }

    displayIncomingEdges(adj, vertices, vertex);

    displayOutgoingEdges(adj, vertex);

    // Search for a directed edge

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

    if (edgeExists(adj, source, destination))
    {
        cout << "Directed edge " << source << " -> "
             << destination << " exists.\n";
    }
    else
    {
        cout << "Directed edge does not exist.\n";
    }

    // Reachability check

    cout << "\nREACHABILITY CHECK\n";

    source = readInteger("Enter starting vertex: ");
    destination = readInteger("Enter destination vertex: ");

    while (!validVertex(source, vertices) ||
           !validVertex(destination, vertices))
    {
        cout << "Invalid vertex!\n";

        source = readInteger("Enter starting vertex: ");
        destination = readInteger("Enter destination vertex: ");
    }

    if (isReachable(adj, source, destination, vertices))
    {
        cout << "Vertex " << destination
             << " is reachable from vertex " << source << ".\n";
    }
    else
    {
        cout << "Vertex " << destination
             << " is NOT reachable from vertex " << source << ".\n";
    }

    // Insert a new directed edge

    cout << "\nEDGE INSERTION\n";

    source = readInteger("Enter source vertex: ");
    destination = readInteger("Enter destination vertex: ");

    while (!validVertex(source, vertices) ||
           !validVertex(destination, vertices) ||
           source == destination)
    {
        cout << "Invalid vertices!\n";

        source = readInteger("Enter source vertex: ");
        destination = readInteger("Enter destination vertex: ");
    }

    if (edgeExists(adj, source, destination))
    {
        cout << "Edge already exists. Insertion skipped.\n";
    }
    else
    {
        addEdge(adj, source, destination);
        insertedEdges.insert({source, destination});

        cout << "Directed edge inserted successfully.\n";
    }

    // Delete a directed edge

    cout << "\nEDGE DELETION\n";

    source = readInteger("Enter source vertex: ");
    destination = readInteger("Enter destination vertex: ");

    while (!validVertex(source, vertices) ||
           !validVertex(destination, vertices) ||
           source == destination)
    {
        cout << "Invalid vertices!\n";

        source = readInteger("Enter source vertex: ");
        destination = readInteger("Enter destination vertex: ");
    }

    if (deleteEdge(adj, source, destination))
    {
        insertedEdges.erase({source, destination});
        cout << "Directed edge deleted successfully.\n";
    }
    else
    {
        cout << "Edge does not exist. Nothing deleted.\n";
    }

    // Final graph

    cout << "\nFINAL GRAPH\n";

    displayGraph(adj, vertices);

    calculateDegrees(adj, vertices);

    return 0;
}
