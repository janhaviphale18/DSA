#include <iostream>
#include <vector>
#include <stack>
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

// Performs iterative DFS using stack
void DFSIterative(const vector<vector<int>>& adj,
                  int start, int vertices)
{
    vector<bool> visited(vertices, false);
    vector<int> parent(vertices, -1);
    vector<int> depth(vertices, -1);

    stack<int> st;

    vector<int> traversal;

    // Push starting vertex
    st.push(start);

    // Mark starting vertex
    visited[start] = true;
    depth[start] = 0;

    cout << "\nITERATIVE DFS EXECUTION\n\n";

    while (!st.empty())
    {
        // Get top element
        int current = st.top();

        // Remove top element
        st.pop();

        // Store traversal order
        traversal.push_back(current);

        cout << "Visiting vertex: " << current
             << " | Depth: " << depth[current] << "\n";

        // Explore neighbours in reverse order
        for (int i = (int)adj[current].size() - 1; i >= 0; i--)
        {
            int neighbour = adj[current][i];

            if (!visited[neighbour])
            {
                visited[neighbour] = true;

                parent[neighbour] = current;

                depth[neighbour] = depth[current] + 1;

                st.push(neighbour);
            }
        }
    }

    // Display traversal
    cout << "\nFINAL DFS TRAVERSAL\n";

    for (int vertex : traversal)
    {
        cout << vertex << " ";
    }

    cout << "\n";

    // Display vertex information
    cout << "\nVERTEX INFORMATION\n\n";

    cout << "Vertex\tDepth\tParent\tStatus\n";

    for (int i = 0; i < vertices; i++)
    {
        cout << i << "\t";

        if (visited[i])
        {
            cout << depth[i] << "\t";

            if (parent[i] == -1)
            {
                cout << "None\t";
            }
            else
            {
                cout << parent[i] << "\t";
            }

            cout << "Visited";
        }
        else
        {
            cout << "-\t-\tUnreachable";
        }

        cout << "\n";
    }
}

int main()
{
    int vertices, edges;
    int directedChoice;

    cout << "ITERATIVE DFS USING STACK\n";
    cout << "-------------------------\n";

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

    int start = readInteger("\nEnter starting vertex for DFS: ");

    while (!validVertex(start, vertices))
    {
        cout << "Invalid starting vertex!\n";

        start = readInteger("Enter starting vertex for DFS: ");
    }

    DFSIterative(adj, start, vertices);

    return 0;
}
