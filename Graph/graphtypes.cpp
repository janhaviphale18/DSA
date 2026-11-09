#include <iostream>
#include <vector>
#include <set>
#include <limits>
#include <algorithm>
using namespace std;

struct Edge
{
    int source;
    int destination;
    int weight;
};

int main()
{
    int vertices, edges;
    int graphDirection, graphWeight;

    // Select graph direction
    cout << "GRAPH CLASSIFICATION PROGRAM\n";

    cout << "\nSelect graph type:\n";
    cout << "1. Undirected Graph\n";
    cout << "2. Directed Graph\n";

    cout << "Enter your choice: ";
    cin >> graphDirection;

    if (cin.fail() || (graphDirection != 1 && graphDirection != 2))
    {
        cout << "Invalid graph type!\n";
        return 1;
    }

    // Select weighted or unweighted graph
    cout << "\nSelect edge type:\n";
    cout << "1. Unweighted Graph\n";
    cout << "2. Weighted Graph\n";

    cout << "Enter your choice: ";
    cin >> graphWeight;

    if (cin.fail() || (graphWeight != 1 && graphWeight != 2))
    {
        cout << "Invalid edge type!\n";
        return 1;
    }

    // Accept number of vertices
    cout << "\nEnter number of vertices: ";
    cin >> vertices;

    if (cin.fail() || vertices <= 0 || vertices > 1000)
    {
        cout << "Invalid number of vertices!\n";
        return 1;
    }

    // Calculate maximum edges
    long long maxEdges;

    if (graphDirection == 1)
    {
        maxEdges = 1LL * vertices * (vertices - 1) / 2;
    }
    else
    {
        maxEdges = 1LL * vertices * (vertices - 1);
    }

    // Accept number of edges
    cout << "Enter number of edges: ";
    cin >> edges;

    if (cin.fail() || edges < 0 || edges > maxEdges)
    {
        cout << "Invalid number of edges!\n";
        return 1;
    }

    vector<Edge> graph;
    set<pair<int, int>> uniqueEdges;

    // Accept graph edges
    for (int i = 0; i < edges; i++)
    {
        while (true)
        {
            int u, v, weight = 0;

            cout << "\nEnter source and destination of edge "
                 << i + 1 << ": ";

            cin >> u >> v;

            if (cin.fail())
            {
                cout << "Invalid input! Enter integer vertices.\n";

                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                continue;
            }

            // Validate vertices
            if (u < 0 || u >= vertices || v < 0 || v >= vertices)
            {
                cout << "Invalid vertex numbers!\n";
                continue;
            }

            // Prevent self-loops
            if (u == v)
            {
                cout << "Self-loops are not allowed!\n";
                continue;
            }

            // Check duplicate edges
            pair<int, int> edge;

            if (graphDirection == 1)
            {
                edge = {min(u, v), max(u, v)};
            }
            else
            {
                edge = {u, v};
            }

            if (uniqueEdges.find(edge) != uniqueEdges.end())
            {
                cout << "Duplicate edge! Try again.\n";
                continue;
            }

            // Accept weight if graph is weighted
            if (graphWeight == 2)
            {
                cout << "Enter edge weight: ";
                cin >> weight;

                if (cin.fail())
                {
                    cout << "Invalid weight!\n";

                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    continue;
                }
            }

            // Store valid edge
            uniqueEdges.insert(edge);

            graph.push_back({u, v, weight});

            break;
        }
    }

    // Display graph classification
    cout << "\n========== GRAPH INFORMATION ==========\n";

    cout << "Graph Direction: ";

    if (graphDirection == 1)
    {
        cout << "Undirected Graph\n";
    }
    else
    {
        cout << "Directed Graph\n";
    }

    cout << "Edge Type: ";

    if (graphWeight == 1)
    {
        cout << "Unweighted Graph\n";
    }
    else
    {
        cout << "Weighted Graph\n";
    }

    cout << "Number of Vertices: " << vertices << endl;
    cout << "Number of Edges: " << graph.size() << endl;

    // Display edges
    cout << "\n========== GRAPH EDGES ==========\n";

    if (graph.empty())
    {
        cout << "No edges present.\n";
    }
    else
    {
        for (const Edge &edge : graph)
        {
            if (graphWeight == 2)
            {
                cout << edge.source << " --("
                     << edge.weight << ")--> "
                     << edge.destination << endl;
            }
            else
            {
                if (graphDirection == 1)
                {
                    cout << edge.source << " <----> "
                         << edge.destination << endl;
                }
                else
                {
                    cout << edge.source << " ----> "
                         << edge.destination << endl;
                }
            }
        }
    }

    cout << "\nGraph classification completed successfully.\n";

    return 0;
}