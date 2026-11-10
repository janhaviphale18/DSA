#include <iostream>
#include <vector>
#include <queue>
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

// Displays adjacency list
void displayGraph(const vector<vector<int>>& adj, int vertices)
{
    cout << "\nADJACENCY LIST\n\n";

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

// Performs BFS for one component
void BFSComponent(const vector<vector<int>>& adj,
                  vector<bool>& visited,
                  int start,
                  vector<int>& component,
                  vector<int>& completeTraversal)
{
    queue<int> q;

    visited[start] = true;
    q.push(start);

    cout << "Component BFS: ";

    while (!q.empty())
    {
        int current = q.front();
        q.pop();

        cout << current << " ";

        component.push_back(current);
        completeTraversal.push_back(current);

        for (int neighbour : adj[current])
        {
            if (!visited[neighbour])
            {
                visited[neighbour] = true;
                q.push(neighbour);
            }
        }
    }

    cout << "\n";
}

// Performs BFS across every component
void BFSDisconnected(const vector<vector<int>>& adj,
                     int vertices)
{
    vector<bool> visited(vertices, false);

    vector<int> completeTraversal;

    int componentCount = 0;

    cout << "\nBFS OF ALL COMPONENTS\n\n";

    for (int i = 0; i < vertices; i++)
    {
        if (!visited[i])
        {
            componentCount++;

            vector<int> component;

            cout << "Component " << componentCount << ":\n";

            BFSComponent(adj, visited, i,
                         component, completeTraversal);

            cout << "Number of vertices in this component: "
                 << component.size() << "\n\n";
        }
    }

    cout << "COMPLETE BFS TRAVERSAL\n";

    for (int vertex : completeTraversal)
    {
        cout << vertex << " ";
    }

    cout << "\n";

    cout << "\nTotal number of components: "
         << componentCount << "\n";

    cout << "\nTotal vertices visited: "
         << completeTraversal.size() << "\n";
}

int main()
{
    int vertices, edges;
    int directedChoice;

    cout << "BFS FOR DISCONNECTED GRAPHS\n";
    cout << "---------------------------\n";

    vertices = readInteger("Enter number of vertices: ");

    while (vertices <= 0 || vertices > 1000)
    {
        cout << "Enter vertices between 1 and 1000.\n";

        vertices = readInteger("Enter number of vertices: ");
    }

    cout << "\nChoose graph type:\n";
    cout << "0. Undirected Graph\n";
    cout << "1. Directed Graph\n";

    directedChoice = readInteger("Enter choice: ");

    while (directedChoice != 0 && directedChoice != 1)
    {
        cout << "Invalid choice! Enter 0 or 1.\n";

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

    edges = readInteger("\nEnter number of edges: ");

    while (edges < 0 || edges > maximumEdges)
    {
        cout << "Invalid edge count! Maximum possible edges = "
             << maximumEdges << "\n";

        edges = readInteger("Enter number of edges: ");
    }

    vector<vector<int>> adj(vertices);

    set<pair<int, int>> insertedEdges;

    cout << "\nEnter graph edges:\n";

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

        adj[source].push_back(destination);

        if (!directed)
        {
            adj[destination].push_back(source);
        }
    }

    displayGraph(adj, vertices);

    // BFS across all components
    BFSDisconnected(adj, vertices);

    return 0;
}
