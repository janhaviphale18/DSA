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

// Display adjacency list
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

// Find connected components using BFS
vector<vector<int>> findComponentsBFS(
    const vector<vector<int>>& adj, int vertices)
{
    vector<bool> visited(vertices, false);

    vector<vector<int>> components;

    for (int i = 0; i < vertices; i++)
    {
        if (!visited[i])
        {
            vector<int> component;

            queue<int> q;

            visited[i] = true;
            q.push(i);

            while (!q.empty())
            {
                int current = q.front();
                q.pop();

                component.push_back(current);

                for (int neighbour : adj[current])
                {
                    if (!visited[neighbour])
                    {
                        visited[neighbour] = true;
                        q.push(neighbour);
                    }
                }
            }

            components.push_back(component);
        }
    }

    return components;
}

// Recursive DFS helper
void DFS(const vector<vector<int>>& adj,
         int current,
         vector<bool>& visited,
         vector<int>& component)
{
    visited[current] = true;

    component.push_back(current);

    for (int neighbour : adj[current])
    {
        if (!visited[neighbour])
        {
            DFS(adj, neighbour, visited, component);
        }
    }
}

// Find connected components using DFS
vector<vector<int>> findComponentsDFS(
    const vector<vector<int>>& adj, int vertices)
{
    vector<bool> visited(vertices, false);

    vector<vector<int>> components;

    for (int i = 0; i < vertices; i++)
    {
        if (!visited[i])
        {
            vector<int> component;

            DFS(adj, i, visited, component);

            components.push_back(component);
        }
    }

    return components;
}

// Sort vertices within components and components themselves
void normalizeComponents(vector<vector<int>>& components)
{
    for (auto& component : components)
    {
        sort(component.begin(), component.end());
    }

    sort(components.begin(), components.end());
}

// Display components
void displayComponents(
    const vector<vector<int>>& components, string method)
{
    cout << "\n" << method << " CONNECTED COMPONENTS\n\n";

    for (int i = 0; i < (int)components.size(); i++)
    {
        cout << "Component " << i + 1 << ": ";

        for (int vertex : components[i])
        {
            cout << vertex << " ";
        }

        cout << "\n";

        cout << "Component size: "
             << components[i].size() << "\n\n";
    }

    cout << "Total components found using "
         << method << " = " << components.size() << "\n";
}

// Analyze component sizes
void analyzeComponents(
    const vector<vector<int>>& components)
{
    int largest = -1;
    int smallest = numeric_limits<int>::max();

    cout << "\nCOMPONENT SIZE ANALYSIS\n\n";

    for (int i = 0; i < (int)components.size(); i++)
    {
        int size = components[i].size();

        largest = max(largest, size);
        smallest = min(smallest, size);

        cout << "Component " << i + 1
             << " size = " << size << "\n";
    }

    cout << "\nLargest component size = " << largest << "\n";
    cout << "Smallest component size = " << smallest << "\n";

    if (components.size() == 1)
    {
        cout << "The graph is connected.\n";
    }
    else
    {
        cout << "The graph is disconnected.\n";
    }
}

int main()
{
    int vertices, edges;

    cout << "CONNECTED COMPONENTS USING BFS AND DFS\n";
    cout << "---------------------------------------\n";

    vertices = readInteger("Enter number of vertices: ");

    while (vertices <= 0 || vertices > 1000)
    {
        cout << "Enter vertices between 1 and 1000.\n";

        vertices = readInteger("Enter number of vertices: ");
    }

    int maximumEdges = vertices * (vertices - 1) / 2;

    edges = readInteger("Enter number of edges: ");

    while (edges < 0 || edges > maximumEdges)
    {
        cout << "Invalid edge count! Maximum possible edges = "
             << maximumEdges << "\n";

        edges = readInteger("Enter number of edges: ");
    }

    vector<vector<int>> adj(vertices);

    set<pair<int, int>> insertedEdges;

    cout << "\nEnter undirected graph edges:\n";

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

        pair<int, int> key = {
            min(source, destination),
            max(source, destination)
        };

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

            key = {
                min(source, destination),
                max(source, destination)
            };
        }

        insertedEdges.insert(key);

        adj[source].push_back(destination);
        adj[destination].push_back(source);
    }

    // Display graph
    displayGraph(adj, vertices);

    // Find components using BFS
    vector<vector<int>> bfsComponents =
        findComponentsBFS(adj, vertices);

    // Find components using DFS
    vector<vector<int>> dfsComponents =
        findComponentsDFS(adj, vertices);

    // Display BFS results
    displayComponents(bfsComponents, "BFS");

    // Display DFS results
    displayComponents(dfsComponents, "DFS");

    // Normalize both results before comparison
    normalizeComponents(bfsComponents);
    normalizeComponents(dfsComponents);

    cout << "\nBFS AND DFS COMPARISON\n\n";

    if (bfsComponents == dfsComponents)
    {
        cout << "Both algorithms identified the same "
             << "connected components.\n";
    }
    else
    {
        cout << "Component partitions do not match.\n";
    }

    // Analyze components
    analyzeComponents(bfsComponents);

    return 0;
}
