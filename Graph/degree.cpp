#include <iostream>
#include <vector>
#include <set>
#include <limits>
#include <algorithm>
using namespace std;

int main()
{
    int vertices, edges, graphType;

    cout << "GRAPH DEGREE CALCULATION PROGRAM\n";

    // Select graph type
    cout << "\nSelect graph type:\n";
    cout << "1. Undirected Graph\n";
    cout << "2. Directed Graph\n";
    cout << "Enter your choice: ";
    cin >> graphType;

    if (cin.fail() || (graphType != 1 && graphType != 2))
    {
        cout << "Invalid graph type!\n";
        return 1;
    }

    // Accept vertices
    cout << "\nEnter number of vertices: ";
    cin >> vertices;

    if (cin.fail() || vertices <= 0 || vertices > 1000)
    {
        cout << "Invalid number of vertices!\n";
        return 1;
    }

    // Calculate maximum possible edges
    long long maxEdges;

    if (graphType == 1)
    {
        maxEdges = 1LL * vertices * (vertices - 1) / 2;
    }
    else
    {
        maxEdges = 1LL * vertices * (vertices - 1);
    }

    // Accept edges
    cout << "Enter number of edges: ";
    cin >> edges;

    if (cin.fail() || edges < 0 || edges > maxEdges)
    {
        cout << "Invalid number of edges!\n";
        return 1;
    }

    // Initialize degree arrays
    vector<int> degree(vertices, 0);
    vector<int> indegree(vertices, 0);
    vector<int> outdegree(vertices, 0);

    // Store edges to prevent duplicates
    set<pair<int, int>> uniqueEdges;

    cout << "\nEnter edges (source destination):\n";

    for (int i = 0; i < edges; i++)
    {
        while (true)
        {
            int u, v;

            cout << "Edge " << i + 1 << ": ";
            cin >> u >> v;

            if (cin.fail())
            {
                cout << "Invalid input! Enter integers.\n";

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

            // Normalize undirected edges
            pair<int, int> edge;

            if (graphType == 1)
            {
                edge = {min(u, v), max(u, v)};
            }
            else
            {
                edge = {u, v};
            }

            // Check duplicate edges
            if (uniqueEdges.find(edge) != uniqueEdges.end())
            {
                cout << "Duplicate edge! Try again.\n";
                continue;
            }

            uniqueEdges.insert(edge);

            // Calculate degrees
            if (graphType == 1)
            {
                degree[u]++;
                degree[v]++;
            }
            else
            {
                outdegree[u]++;
                indegree[v]++;
            }

            break;
        }
    }

    // Display results
    cout << "\n========== GRAPH RESULTS ==========\n";

    if (graphType == 1)
    {
        cout << "\nUNDIRECTED GRAPH\n";

        cout << "\nVertex\tDegree\n";

        for (int i = 0; i < vertices; i++)
        {
            cout << i << "\t" << degree[i] << endl;
        }

        cout << "\nIsolated Vertices: ";

        bool found = false;

        for (int i = 0; i < vertices; i++)
        {
            if (degree[i] == 0)
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

        // Verify degree sum
        int totalDegree = 0;

        for (int value : degree)
        {
            totalDegree += value;
        }

        cout << "\nSum of Degrees: " << totalDegree << endl;
        cout << "Twice the Number of Edges: " << 2LL * edges << endl;
    }
    else
    {
        cout << "\nDIRECTED GRAPH\n";

        cout << "\nVertex\tIndegree\tOutdegree\n";

        for (int i = 0; i < vertices; i++)
        {
            cout << i << "\t"
                 << indegree[i] << "\t\t"
                 << outdegree[i] << endl;
        }

        cout << "\nSource Vertices: ";

        bool sourceFound = false;

        for (int i = 0; i < vertices; i++)
        {
            if (indegree[i] == 0 && outdegree[i] > 0)
            {
                cout << i << " ";
                sourceFound = true;
            }
        }

        if (!sourceFound)
        {
            cout << "None";
        }

        cout << "\nSink Vertices: ";

        bool sinkFound = false;

        for (int i = 0; i < vertices; i++)
        {
            if (outdegree[i] == 0 && indegree[i] > 0)
            {
                cout << i << " ";
                sinkFound = true;
            }
        }

        if (!sinkFound)
        {
            cout << "None";
        }

        cout << "\nIsolated Vertices: ";

        bool isolatedFound = false;

        for (int i = 0; i < vertices; i++)
        {
            if (indegree[i] == 0 && outdegree[i] == 0)
            {
                cout << i << " ";
                isolatedFound = true;
            }
        }

        if (!isolatedFound)
        {
            cout << "None";
        }

        // Verify indegree and outdegree sums
        int totalIndegree = 0;
        int totalOutdegree = 0;

        for (int i = 0; i < vertices; i++)
        {
            totalIndegree += indegree[i];
            totalOutdegree += outdegree[i];
        }

        cout << "\n\nSum of Indegrees: " << totalIndegree << endl;
        cout << "Sum of Outdegrees: " << totalOutdegree << endl;
        cout << "Total Edges: " << edges << endl;
    }

    return 0;
}