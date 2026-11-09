#include <iostream>
#include <vector>
#include <set>
#include <limits>
using namespace std;

int main()
{
    int vertices, edges;

    // Accept number of vertices
    cout << "Enter the number of vertices: ";
    cin >> vertices;

    // Validate number of vertices
    if (cin.fail() || vertices <= 0 || vertices > 1000)
    {
        cout << "Invalid number of vertices!" << endl;
        return 1;
    }

    // Calculate maximum possible edges in a simple undirected graph
    long long maxEdges = 1LL * vertices * (vertices - 1) / 2;

    // Accept number of edges
    cout << "Enter the number of edges: ";
    cin >> edges;

    // Validate number of edges
    if (cin.fail() || edges < 0 || edges > maxEdges)
    {
        cout << "Invalid number of edges!" << endl;
        return 1;
    }

    // Store all edges
    vector<pair<int, int>> graphEdges;

    // Store degree of every vertex
    vector<int> degree(vertices, 0);

    // Prevent duplicate edges
    set<pair<int, int>> uniqueEdges;

    cout << "\nEnter the edges (vertex1 vertex2):\n";

    for (int i = 0; i < edges; i++)
    {
        int u, v;

        while (true)
        {
            cout << "Edge " << i + 1 << ": ";
            cin >> u >> v;

            // Handle invalid input
            if (cin.fail())
            {
                cout << "Invalid input! Enter two integers.\n";

                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                continue;
            }

            // Validate vertex numbers
            if (u < 0 || u >= vertices || v < 0 || v >= vertices)
            {
                cout << "Invalid vertex! Enter vertices between 0 and "
                     << vertices - 1 << ".\n";

                continue;
            }

            // Prevent self-loops
            if (u == v)
            {
                cout << "Self-loops are not allowed. Try again.\n";
                continue;
            }

            // Normalize edge to detect duplicates
            pair<int, int> edge = {min(u, v), max(u, v)};

            if (uniqueEdges.find(edge) != uniqueEdges.end())
            {
                cout << "Duplicate edge! Enter a different edge.\n";
                continue;
            }

            // Store valid edge
            uniqueEdges.insert(edge);
            graphEdges.push_back(edge);

            // Update degree of both vertices
            degree[u]++;
            degree[v]++;

            break;
        }
    }

    // Display vertices
    cout << "\nVertices in the Graph:\n";

    for (int i = 0; i < vertices; i++)
    {
        cout << i << " ";
    }

    // Display edges
    cout << "\n\nEdges in the Graph:\n";

    if (graphEdges.empty())
    {
        cout << "No edges present.\n";
    }
    else
    {
        for (auto edge : graphEdges)
        {
            cout << "(" << edge.first << ", "
                 << edge.second << ")\n";
        }
    }

    // Display graph information
    cout << "\nGraph Information:\n";

    cout << "Total Vertices: " << vertices << endl;
    cout << "Total Edges: " << graphEdges.size() << endl;

    // Display degree of every vertex
    cout << "\nDegree of Each Vertex:\n";

    for (int i = 0; i < vertices; i++)
    {
        cout << "Vertex " << i << " : "
             << degree[i] << endl;
    }

    // Identify isolated vertices
    cout << "\nIsolated Vertices:\n";

    bool isolatedFound = false;

    for (int i = 0; i < vertices; i++)
    {
        if (degree[i] == 0)
        {
            cout << i << " ";
            isolatedFound = true;
        }
    }

    if (!isolatedFound)
    {
        cout << "None";
    }

    cout << endl;

    return 0;
}