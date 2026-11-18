#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <map>
#include <set>
#include <queue>
using namespace std;

using Permutation = vector<int>;

class SubgroupEnumeration {
private:
    int n;

    vector<vector<int>> adj;
    vector<int> degree;

    vector<int> mapping;
    vector<bool> used;

    vector<Permutation> automorphisms;
    map<Permutation, int> groupIndex;

    vector<Permutation> subgroup;
    map<Permutation, int> subgroupIndex;

    Permutation identity;

    Permutation compose(const Permutation& p,
                        const Permutation& q) const {
        // p o q: apply q first, then p.
        Permutation result(n);

        for (int i = 0; i < n; i++) {
            result[i] = p[q[i]];
        }

        return result;
    }

    Permutation inverse(const Permutation& p) const {
        Permutation result(n);

        for (int i = 0; i < n; i++) {
            result[p[i]] = i;
        }

        return result;
    }

    bool compatible(int vertex, int candidate) const {
        if (degree[vertex] != degree[candidate]) {
            return false;
        }

        for (int previous = 0; previous < vertex; previous++) {
            if (adj[vertex][previous] !=
                adj[candidate][mapping[previous]]) {
                return false;
            }
        }

        return true;
    }

    void generateAutomorphisms(int vertex) {
        if (vertex == n) {
            automorphisms.push_back(mapping);
            return;
        }

        for (int candidate = 0; candidate < n; candidate++) {
            if (used[candidate]) {
                continue;
            }

            if (!compatible(vertex, candidate)) {
                continue;
            }

            mapping[vertex] = candidate;
            used[candidate] = true;

            generateAutomorphisms(vertex + 1);

            used[candidate] = false;
            mapping[vertex] = -1;
        }
    }

    void printPermutation(const Permutation& p) const {
        cout << "[";

        for (int i = 0; i < n; i++) {
            if (i > 0) {
                cout << " ";
            }

            cout << p[i];
        }

        cout << "]";
    }

public:
    SubgroupEnumeration(int vertices) {
        n = vertices;

        adj.assign(n, vector<int>(n, 0));
        degree.assign(n, 0);

        mapping.assign(n, -1);
        used.assign(n, false);

        identity.resize(n);
        iota(identity.begin(), identity.end(), 0);
    }

    bool addEdge(int u, int v) {
        if (u < 0 || u >= n || v < 0 || v >= n) {
            return false;
        }

        if (u == v || adj[u][v] == 1) {
            return false;
        }

        adj[u][v] = 1;
        adj[v][u] = 1;

        degree[u]++;
        degree[v]++;

        return true;
    }

    void findAutomorphisms() {
        automorphisms.clear();
        groupIndex.clear();

        generateAutomorphisms(0);

        sort(automorphisms.begin(), automorphisms.end());

        for (int i = 0; i < (int)automorphisms.size(); i++) {
            groupIndex[automorphisms[i]] = i;
        }
    }

    void displayAutomorphisms() const {
        cout << "\nFULL AUTOMORPHISM GROUP\n";

        cout << "Group order: "
             << automorphisms.size() << "\n";

        for (int i = 0; i < (int)automorphisms.size(); i++) {
            cout << "G" << i << " = ";
            printPermutation(automorphisms[i]);

            if (automorphisms[i] == identity) {
                cout << " (Identity)";
            }

            cout << "\n";
        }
    }

    int getGroupSize() const {
        return (int)automorphisms.size();
    }

    bool enumerateSubgroup(const vector<int>& generatorIDs) {
        subgroup.clear();
        subgroupIndex.clear();

        vector<Permutation> generators;

        set<int> uniqueIDs;

        // Validate and collect selected generators.
        for (int id : generatorIDs) {
            if (id < 0 || id >= getGroupSize()) {
                return false;
            }

            if (!uniqueIDs.insert(id).second) {
                continue;
            }

            if (automorphisms[id] == identity) {
                return false;
            }

            generators.push_back(automorphisms[id]);
        }

        // Include inverses of all generators.
        int originalCount = (int)generators.size();

        for (int i = 0; i < originalCount; i++) {
            Permutation inv = inverse(generators[i]);

            if (inv != identity &&
                find(generators.begin(), generators.end(), inv)
                    == generators.end()) {
                generators.push_back(inv);
            }
        }

        // Begin enumeration from the identity.
        queue<Permutation> q;

        subgroup.push_back(identity);
        subgroupIndex[identity] = 0;

        q.push(identity);

        // Repeatedly compose discovered elements
        // with the generators and their inverses.
        while (!q.empty()) {
            Permutation current = q.front();
            q.pop();

            for (const auto& generator : generators) {
                Permutation result = compose(current, generator);

                if (groupIndex.find(result) == groupIndex.end()) {
                    cout << "Internal error: composition "
                         << "is not an automorphism.\n";
                    return false;
                }

                if (subgroupIndex.find(result) ==
                    subgroupIndex.end()) {

                    int index = (int)subgroup.size();

                    subgroup.push_back(result);
                    subgroupIndex[result] = index;

                    q.push(result);
                }
            }
        }

        return true;
    }

    void displaySubgroup() const {
        cout << "\nGENERATED SUBGROUP\n";

        cout << "Subgroup order: "
             << subgroup.size() << "\n";

        for (int i = 0; i < (int)subgroup.size(); i++) {
            cout << "H" << i << " = ";
            printPermutation(subgroup[i]);

            if (subgroup[i] == identity) {
                cout << " (Identity)";
            }

            cout << "\n";
        }
    }

    void analyzeSubgroup() const {
        cout << "\nSUBGROUP ANALYSIS\n";

        int fullOrder = getGroupSize();
        int subgroupOrder = (int)subgroup.size();

        cout << "Full group order: " << fullOrder << "\n";
        cout << "Subgroup order: " << subgroupOrder << "\n";

        if (subgroupOrder == fullOrder) {
            cout << "Generated subgroup equals the full "
                 << "automorphism group.\n";
        } else {
            cout << "Generated subgroup is a proper subgroup.\n";
        }

        if (fullOrder % subgroupOrder == 0) {
            cout << "Lagrange's theorem verified.\n";

            cout << "Index of subgroup [G:H] = "
                 << fullOrder / subgroupOrder << "\n";
        } else {
            cout << "Lagrange's theorem verification failed.\n";
        }
    }

    void verifySubgroupProperties() const {
        cout << "\nVERIFYING SUBGROUP PROPERTIES\n";

        bool identityPresent =
            subgroupIndex.find(identity) != subgroupIndex.end();

        cout << "Identity present: "
             << (identityPresent ? "Yes" : "No") << "\n";

        bool inversesValid = true;

        for (const auto& element : subgroup) {
            Permutation inv = inverse(element);

            if (subgroupIndex.find(inv) == subgroupIndex.end()) {
                inversesValid = false;
                break;
            }
        }

        cout << "Inverse property: "
             << (inversesValid ? "Passed" : "Failed") << "\n";

        bool closureValid = true;

        for (const auto& p : subgroup) {
            for (const auto& q : subgroup) {
                Permutation result = compose(p, q);

                if (subgroupIndex.find(result) ==
                    subgroupIndex.end()) {
                    closureValid = false;
                    break;
                }
            }

            if (!closureValid) {
                break;
            }
        }

        cout << "Closure property: "
             << (closureValid ? "Passed" : "Failed") << "\n";

        if (identityPresent && inversesValid && closureValid) {
            cout << "All subgroup checks passed.\n";
        }
    }

    void displayLeftCosets() const {
        cout << "\nLEFT COSETS OF THE SUBGROUP\n";

        set<Permutation> assigned;
        int cosetNumber = 0;

        for (const auto& g : automorphisms) {
            if (assigned.find(g) != assigned.end()) {
                continue;
            }

            vector<Permutation> coset;

            for (const auto& h : subgroup) {
                // Left coset: gH = {g o h : h belongs to H}.
                Permutation result = compose(g, h);

                coset.push_back(result);
                assigned.insert(result);
            }

            cout << "Coset C" << cosetNumber++ << ": ";

            for (const auto& element : coset) {
                cout << "G" << groupIndex.at(element) << " ";
            }

            cout << "\n";
        }

        cout << "Total distinct left cosets: "
             << cosetNumber << "\n";
    }
};

int main() {
    int n, m;

    cout << "GRAPH AUTOMORPHISM SUBGROUP ENUMERATION\n";

    cout << "Enter number of vertices (1 to 6): ";

    if (!(cin >> n) || n < 1 || n > 6) {
        cout << "Invalid number of vertices.\n";
        return 1;
    }

    cout << "Enter number of edges: ";

    if (!(cin >> m) || m < 0 || m > n * (n - 1) / 2) {
        cout << "Invalid number of edges.\n";
        return 1;
    }

    SubgroupEnumeration graph(n);

    cout << "Enter edges (u v), using vertices 0 to "
         << n - 1 << ":\n";

    for (int i = 0; i < m; i++) {
        int u, v;

        if (!(cin >> u >> v)) {
            cout << "Invalid edge input.\n";
            return 1;
        }

        if (!graph.addEdge(u, v)) {
            cout << "Invalid or duplicate edge.\n";
            return 1;
        }
    }

    graph.findAutomorphisms();
    graph.displayAutomorphisms();

    int count;

    cout << "\nEnter number of generators: ";

    if (!(cin >> count) ||
        count < 0 ||
        count > graph.getGroupSize() - 1) {
        cout << "Invalid generator count.\n";
        return 1;
    }

    vector<int> generatorIDs(count);

    cout << "Enter generator IDs (without G):\n";

    for (int i = 0; i < count; i++) {
        if (!(cin >> generatorIDs[i])) {
            cout << "Invalid generator input.\n";
            return 1;
        }
    }

    if (!graph.enumerateSubgroup(generatorIDs)) {
        cout << "Invalid generator selection or enumeration error.\n";
        return 1;
    }

    graph.displaySubgroup();
    graph.analyzeSubgroup();
    graph.verifySubgroupProperties();
    graph.displayLeftCosets();

    cout << "\nSubgroup enumeration completed.\n";

    return 0;
}
