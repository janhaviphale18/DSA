#include <iostream>
#include <vector>
#include <limits>
using namespace std;

// Read and validate integer input
bool readInteger(string message, int &value)
{
    while (true)
    {
        cout << message;
        cin >> value;

        if (!cin.fail())
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

// Display adjacency matrix
void displayMatrix(const vector<vector<int>> &matrix)
{
    int vertices = matrix.size();

    cout << "\nAdjacency Matrix:\n\n";

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

// Display adjacent vertices
void displayAdjacent(const vector<vector<int>> &matrix, int vertex)
{
    int vertices = matrix.size();
    bool found = false;

    cout << "\nVertices adjacent to " << vertex << ": ";

    for (int i = 0; i < vertices; i++)
    {
        if (matrix[vertex][i] == 1)
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

// Calculate and display degrees
void displayDegrees(const vector<vector<int>> &matrix,
                    bool directed)
{
    int vertices = matrix.size();

    cout << "\nDegree Information:\n";

    if (!directed)
    {
        for (int i = 0; i < vertices; i++)
        {
            int degree = 0;

            for (int j = 0; j < vertices; j++)
            {
                degree += matrix[i][j];
            }

            cout << "Degree of vertex " << i
                 << " = " << degree << "\n";
        }
    }
    else
    {
        for (int i = 0; i < vertices; i++)
        {
            int indegree = 0;
            int outdegree = 0;

            for (int j = 0; j < vertices; j++)
            {
                outdegree += matrix[i][j];
                indegree += matrix[j][i];
            }

            cout << "Vertex " << i
                 << " | Indegree: " << indegree
                 << " | Outdegree: " << outdegree
                 << "\n";
        }
    }
}

int main()
{
    int vertices, edges, graphType;

    cout << "ADJACENCY MATRIX REPRESENTATION\n";

    // Select graph type
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

    // Accept number of vertices
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

    // Initialize adjacency matrix
    vector<vector<int>> matrix(
        vertices, vector<int>(vertices, 0)
    );

    // Accept graph edges
    cout << "\nEnter edges (source destination):\n";

    for (int i = 0; i < edges; i++)
    {
        while (true)
        {
            int u, v;

            if (!readInteger("Enter source vertex: ", u))
            {
                return 1;
            }

            if (!readInteger("Enter destination vertex: ", v))
            {
                return 1;
            }

            if (!validVertex(u, vertices) ||
                !validVertex(v, vertices))
            {
                cout << "Invalid vertex! Enter values between 0 and "
                     << vertices - 1 << ".\n";
                continue;
            }

            if (u == v)
            {
                cout << "Self-loops are not allowed!\n";
                continue;
            }

            if (matrix[u][v] == 1)
            {
                cout << "Duplicate edge! Enter another edge.\n";
                continue;
            }

            // Insert edge
            matrix[u][v] = 1;

            if (!directed)
            {
                matrix[v][u] = 1;
            }

            break;
        }
    }

    // Display initial matrix
    cout << "\n========== ORIGINAL GRAPH ==========\n";

    displayMatrix(matrix);

    // Check whether an edge exists
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
        return 1;
    }

    if (matrix[source][destination] == 1)
    {
        cout << "Edge exists between "
             << source << " and " << destination << ".\n";
    }
    else
    {
        cout << "Edge does not exist between "
             << source << " and " << destination << ".\n";
    }

    // Insert a new edge
    int newSource, newDestination;

    cout << "\n========== INSERT EDGE ==========\n";

    if (!readInteger("Enter source vertex: ", newSource) ||
        !readInteger("Enter destination vertex: ", newDestination))
    {
        return 1;
    }

    if (!validVertex(newSource, vertices) ||
        !validVertex(newDestination, vertices))
    {
        cout << "Invalid vertices! Edge not inserted.\n";
    }
    else if (newSource == newDestination)
    {
        cout << "Self-loops are not allowed!\n";
    }
    else if (matrix[newSource][newDestination] == 1)
    {
        cout << "Edge already exists!\n";
    }
    else
    {
        matrix[newSource][newDestination] = 1;

        if (!directed)
        {
            matrix[newDestination][newSource] = 1;
        }

        cout << "Edge inserted successfully.\n";
    }

    // Delete an existing edge
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
        cout << "Invalid vertices! Edge not deleted.\n";
    }
    else if (matrix[deleteSource][deleteDestination] == 0)
    {
        cout << "Edge does not exist!\n";
    }
    else
    {
        matrix[deleteSource][deleteDestination] = 0;

        if (!directed)
        {
            matrix[deleteDestination][deleteSource] = 0;
        }

        cout << "Edge deleted successfully.\n";
    }

    // Display updated matrix
    cout << "\n========== UPDATED GRAPH ==========\n";

    displayMatrix(matrix);

    // Display adjacent vertices
    int selectedVertex;

    cout << "\n========== ADJACENT VERTICES ==========\n";

    if (!readInteger("Enter vertex: ", selectedVertex))
    {
        return 1;
    }

    if (!validVertex(selectedVertex, vertices))
    {
        cout << "Invalid vertex!\n";
        return 1;
    }

    displayAdjacent(matrix, selectedVertex);

    // Display degree information
    displayDegrees(matrix, directed);

    return 0;
}