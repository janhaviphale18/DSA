#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#include <numeric>
using namespace std;

using Permutation = vector<int>;

class GraphAutomorphismGroup {
private:
    int vertices;
    vector<vector<int>> adj;
    vector<int> current;
    vector<bool> used;
    vector<Permutation> automorphisms;
    map<Permutation, int> groupIndex;

    void generateAutomorphisms(int vertex) {
        if (vertex == vertices) {
            automorphisms.push_back(current);
            return;
        }

        for (int candidate = 0; candidate < vertices; candidate++) {
            if (used[candidate]) {
                continue;
            }

            // Vertices with different degrees cannot correspond.
            int degree1 = 0;
            int degree2 = 0;

            for (int i = 0; i < vertices; i++) {
                degree1 += adj[vertex][i];
                degree2 += adj[candidate][i];
            }

            if (degree1 != degree2) {
                continue;
            }

            // Check adjacency with all already mapped vertices.
            bool valid = true;

            for (int previous = 0; previous < vertex; previous++) {
                int mappedPrevious = current[previous];

                if (adj[vertex][previous] !=
                    adj[candidate][mappedPrevious]) {
                    valid = false;
                    break;
                }
            }

            if (!valid) {
                continue;
            }

            current[vertex] = candidate;
            used[candidate] = true;

            generateAutomorphisms(vertex + 1);

            used[candidate] = false;
        }
    }

    Permutation compose(const Permutation& p,
                        const Permutation& q) {
        // p o q means apply q first, then p.
        Permutation result(vertices);

        for (int i = 0; i < vertices; i++) {
            result[i] = p[q[i]];
        }

        return result;
    }

    Permutation findInverse(const Permutation& p) {
        Permutation inverse(vertices);

        for (int i = 0; i < vertices; i++) {
            inverse[p[i]] = i;
        }

        return inverse;
    }

    void printPermutation(const Permutation& p) {
        cout << "[ ";

        for (int value : p) {
            cout << value << " ";
        }

        cout << "]";
    }

public:
    GraphAutomorphismGroup(int n) {
        vertices = n;
        adj.assign(n, vector<int>(n, 0));
        current.assign(n, -1);
        used.assign(n, false);
    }

    void addEdge(int u, int v) {
        adj[u][v] = 1;
        adj[v][u] = 1;
    }

    void findAllAutomorphisms() {
        automorphisms.clear();
        generateAutomorphisms(0);

        sort(automorphisms.begin(), automorphisms.end());

        for (int i = 0; i < (int)automorphisms.size(); i++) {
            groupIndex[automorphisms[i]] = i;
        }
    }

    void displayAutomorphisms() {
        cout << "\nAll automorphisms:\n";

        for (int i = 0; i < (int)automorphisms.size(); i++) {
            cout << "G" << i << " = ";
            printPermutation(automorphisms[i]);
            cout << "\n";
        }

        cout << "\nOrder of automorphism group: "
             << automorphisms.size() << "\n";
    }

    void identifyIdentity() {
        Permutation identity(vertices);
        iota(identity.begin(), identity.end(), 0);

        cout << "\nIdentity element:\n";

        auto it = groupIndex.find(identity);

        if (it == groupIndex.end()) {
            cout << "Identity not found. Something went wrong.\n";
            return;
        }

        cout << "G" << it->second << " = ";
        printPermutation(identity);
        cout << "\n";
    }

    void verifyClosure() {
        int total = (int)automorphisms.size();
        long long tested = 0;
        bool closure = true;

        cout << "\nChecking closure property...\n";

        // Exhaustively check smaller groups.
        if (total <= 1500) {
            for (const auto& p : automorphisms) {
                for (const auto& q : automorphisms) {
                    Permutation result = compose(p, q);
                    tested++;

                    if (groupIndex.find(result) == groupIndex.end()) {
                        closure = false;
                        break;
                    }
                }

                if (!closure) {
                    break;
                }
            }

            cout << "Pairs tested: " << tested << "\n";
        } else {
            // For very large groups, test a deterministic sample.
            int limit = min(total, 1000);

            for (int i = 0; i < limit && closure; i++) {
                for (int j = 0; j < limit; j++) {
                    Permutation result =
                        compose(automorphisms[i], automorphisms[j]);

                    tested++;

                    if (groupIndex.find(result) == groupIndex.end()) {
                        closure = false;
                        break;
                    }
                }
            }

            cout << "Sampled pairs tested: " << tested << "\n";
            cout << "Full closure is guaranteed mathematically "
                 << "for the complete automorphism set.\n";
        }

        if (closure) {
            cout << "Closure check passed.\n";
        } else {
            cout << "Closure check failed.\n";
        }
    }

    void verifyInverses() {
        cout << "\nChecking inverse property...\n";

        Permutation identity(vertices);
        iota(identity.begin(), identity.end(), 0);

        bool allValid = true;

        for (int i = 0; i < (int)automorphisms.size(); i++) {
            Permutation inverse = findInverse(automorphisms[i]);

            auto it = groupIndex.find(inverse);

            if (it == groupIndex.end()) {
                allValid = false;
                cout << "Inverse missing for G" << i << "\n";
                continue;
            }

            Permutation left = compose(automorphisms[i], inverse);
            Permutation right = compose(inverse, automorphisms[i]);

            if (left != identity || right != identity) {
                allValid = false;
                cout << "Inverse verification failed for G" << i << "\n";
            } else {
                cout << "G" << i << " inverse is G" << it->second
                     << " : ";
                printPermutation(inverse);
                cout << "\n";
            }
        }

        if (allValid) {
            cout << "Inverse property passed for every element.\n";
        }
    }

    void verifyAssociativity() {
        cout << "\nChecking associativity property...\n";

        int total = (int)automorphisms.size();
        long long tested = 0;
        bool valid = true;

        if (total <= 30) {
            // Exhaustively test every possible triple.
            for (const auto& p : automorphisms) {
                for (const auto& q : automorphisms) {
                    for (const auto& r : automorphisms) {
                        Permutation left = compose(compose(p, q), r);
                        Permutation right = compose(p, compose(q, r));

                        tested++;

                        if (left != right) {
                            valid = false;
                            break;
                        }
                    }

                    if (!valid) break;
                }

                if (!valid) break;
            }

            cout << "Triples tested: " << tested << "\n";
        } else {
            // Test selected triples for larger groups.
            int limit = min(total, 20);

            for (int i = 0; i < limit; i++) {
                for (int j = 0; j < limit; j++) {
                    for (int k = 0; k < limit; k++) {
                        Permutation left =
                            compose(compose(automorphisms[i],
                                            automorphisms[j]),
                                    automorphisms[k]);

                        Permutation right =
                            compose(automorphisms[i],
                                    compose(automorphisms[j],
                                            automorphisms[k]));

                        tested++;

                        if (left != right) {
                            valid = false;
                            break;
                        }
                    }

                    if (!valid) break;
                }

                if (!valid) break;
            }

            cout << "Sampled triples tested: " << tested << "\n";
            cout << "Associativity is guaranteed by function "
                 << "composition.\n";
        }

        if (valid) {
            cout << "Associativity check passed.\n";
        } else {
            cout << "Associativity check failed.\n";
        }
    }

    void displayCompositionTable() {
        int total = (int)automorphisms.size();

        if (total > 12) {
            cout << "\nComposition table skipped because the group "
                 << "has more than 12 elements.\n";
            return;
        }

        cout << "\nComposition table (row o column):\n\n";

        cout << "    ";
        for (int j = 0; j < total; j++) {
            cout << "G" << j << " ";
        }
        cout << "\n";

        for (int i = 0; i < total; i++) {
            cout << "G" << i << "  ";

            for (int j = 0; j < total; j++) {
                Permutation result =
                    compose(automorphisms[i], automorphisms[j]);

                cout << "G" << groupIndex[result] << "  ";
            }

            cout << "\n";
        }
    }
};

int main() {
    int n, m;

    cout << "GRAPH AUTOMORPHISM GROUP OPERATIONS\n";

    cout << "Enter number of vertices (1 to 8): ";
    cin >> n;

    if (cin.fail() || n < 1 || n > 8) {
        cout << "Invalid number of vertices.\n";
        return 1;
    }

    cout << "Enter number of edges: ";
    cin >> m;

    if (cin.fail() || m < 0 || m > n * (n - 1) / 2) {
        cout << "Invalid number of edges.\n";
        return 1;
    }

    GraphAutomorphismGroup graph(n);

    vector<vector<bool>> entered(n, vector<bool>(n, false));

    cout << "Enter edges (u v), using vertices 0 to "
         << n - 1 << ":\n";

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        if (cin.fail() || u < 0 || u >= n ||
            v < 0 || v >= n || u == v) {
            cout << "Invalid edge. Enter a valid edge again.\n";
            return 1;
        }

        if (entered[u][v]) {
            cout << "Duplicate edge detected.\n";
            return 1;
        }

        entered[u][v] = true;
        entered[v][u] = true;

        graph.addEdge(u, v);
    }

    graph.findAllAutomorphisms();

    graph.displayAutomorphisms();
    graph.identifyIdentity();
    graph.verifyClosure();
    graph.verifyInverses();
    graph.verifyAssociativity();
    graph.displayCompositionTable();

    cout << "\nAll group operation checks completed.\n";

    return 0;
}
