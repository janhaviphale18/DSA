#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <map>
#include <set>
#include <queue>
using namespace std;

using Permutation = vector<int>;

class QuotientGroup {
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

    vector<vector<int>> cosets;
    vector<int> elementToCoset;
    vector<int> representatives;

    vector<vector<int>> quotientTable;

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

    void backtrack(int vertex) {
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

            backtrack(vertex + 1);

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

    bool isNormalSubgroup() const {
        for (const auto& g : automorphisms) {
            Permutation inverseG = inverse(g);

            for (const auto& h : subgroup) {
                Permutation conjugate =
                    compose(compose(g, h), inverseG);

                if (subgroupIndex.find(conjugate) ==
                    subgroupIndex.end()) {
                    return false;
                }
            }
        }

        return true;
    }

public:
    QuotientGroup(int vertices) {
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

        backtrack(0);

        sort(automorphisms.begin(), automorphisms.end());

        for (int i = 0; i < (int)automorphisms.size(); i++) {
            groupIndex[automorphisms[i]] = i;
        }
    }

    int groupSize() const {
        return (int)automorphisms.size();
    }

    void displayAutomorphisms() const {
        cout << "\nFULL AUTOMORPHISM GROUP\n";
        cout << "Group order: " << groupSize() << "\n";

        for (int i = 0; i < groupSize(); i++) {
            cout << "G" << i << " = ";
            printPermutation(automorphisms[i]);

            if (automorphisms[i] == identity) {
                cout << " (Identity)";
            }

            cout << "\n";
        }
    }

    bool generateSubgroup(const vector<int>& generatorIDs) {
        subgroup.clear();
        subgroupIndex.clear();

        vector<Permutation> generators;
        set<int> uniqueIDs;

        for (int id : generatorIDs) {
            if (id < 0 || id >= groupSize()) {
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

        int originalCount = (int)generators.size();

        for (int i = 0; i < originalCount; i++) {
            Permutation inv = inverse(generators[i]);

            if (find(generators.begin(), generators.end(), inv)
                == generators.end()) {
                generators.push_back(inv);
            }
        }

        queue<Permutation> q;

        subgroup.push_back(identity);
        subgroupIndex[identity] = 0;
        q.push(identity);

        while (!q.empty()) {
            Permutation current = q.front();
            q.pop();

            for (const auto& generator : generators) {
                Permutation result = compose(current, generator);

                if (groupIndex.find(result) == groupIndex.end()) {
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
        cout << "Subgroup order: " << subgroup.size() << "\n";

        for (int i = 0; i < (int)subgroup.size(); i++) {
            cout << "H" << i << " = ";
            printPermutation(subgroup[i]);

            if (subgroup[i] == identity) {
                cout << " (Identity)";
            }

            cout << "\n";
        }
    }

    bool constructCosets() {
        if (!isNormalSubgroup()) {
            cout << "\nCannot construct a quotient group.\n";
            cout << "The selected subgroup is not normal.\n";
            return false;
        }

        cosets.clear();
        representatives.clear();

        elementToCoset.assign(groupSize(), -1);

        // Construct distinct left cosets gH.
        for (int g = 0; g < groupSize(); g++) {
            if (elementToCoset[g] != -1) {
                continue;
            }

            vector<int> currentCoset;

            for (const auto& h : subgroup) {
                Permutation product =
                    compose(automorphisms[g], h);

                int elementID = groupIndex.at(product);

                currentCoset.push_back(elementID);
            }

            sort(currentCoset.begin(), currentCoset.end());
            currentCoset.erase(
                unique(currentCoset.begin(), currentCoset.end()),
                currentCoset.end()
            );

            int cosetID = (int)cosets.size();

            representatives.push_back(g);
            cosets.push_back(currentCoset);

            for (int elementID : currentCoset) {
                if (elementToCoset[elementID] != -1 &&
                    elementToCoset[elementID] != cosetID) {
                    cout << "Coset partition error.\n";
                    return false;
                }

                elementToCoset[elementID] = cosetID;
            }
        }

        // Verify that every group element belongs to one coset.
        for (int id : elementToCoset) {
            if (id == -1) {
                cout << "Some group elements are not covered.\n";
                return false;
            }
        }

        return true;
    }

    void displayCosets() const {
        cout << "\nDISTINCT LEFT COSETS\n";

        for (int i = 0; i < (int)cosets.size(); i++) {
            cout << "Q" << i << " = { ";

            for (int elementID : cosets[i]) {
                cout << "G" << elementID << " ";
            }

            cout << "}\n";
        }

        cout << "Number of distinct cosets: "
             << cosets.size() << "\n";
    }

    void constructQuotientTable() {
        int count = (int)cosets.size();

        quotientTable.assign(count, vector<int>(count, -1));

        for (int i = 0; i < count; i++) {
            for (int j = 0; j < count; j++) {
                int representativeA = representatives[i];
                int representativeB = representatives[j];

                Permutation product =
                    compose(automorphisms[representativeA],
                            automorphisms[representativeB]);

                int groupElementID = groupIndex.at(product);

                quotientTable[i][j] =
                    elementToCoset[groupElementID];
            }
        }
    }

    void displayQuotientTable() const {
        int count = (int)cosets.size();

        cout << "\nQUOTIENT GROUP MULTIPLICATION TABLE\n\n";

        cout << "    ";

        for (int j = 0; j < count; j++) {
            cout << "Q" << j << " ";
        }

        cout << "\n";

        for (int i = 0; i < count; i++) {
            cout << "Q" << i << "  ";

            for (int j = 0; j < count; j++) {
                cout << "Q" << quotientTable[i][j] << "  ";
            }

            cout << "\n";
        }
    }

    void analyzeQuotientGroup() const {
        int count = (int)cosets.size();

        cout << "\nQUOTIENT GROUP ANALYSIS\n";

        cout << "Full group order: " << groupSize() << "\n";
        cout << "Subgroup order: " << subgroup.size() << "\n";
        cout << "Quotient group order: " << count << "\n";

        cout << "Lagrange verification: "
             << groupSize() << " = "
             << subgroup.size() << " x "
             << count << "\n";

        // The coset containing the identity is the quotient identity.
        int identityCoset = elementToCoset[
            groupIndex.at(identity)
        ];

        cout << "Quotient identity: Q"
             << identityCoset << "\n";

        bool inversesValid = true;

        cout << "\nQUOTIENT INVERSES\n";

        for (int i = 0; i < count; i++) {
            bool found = false;

            for (int j = 0; j < count; j++) {
                if (quotientTable[i][j] == identityCoset &&
                    quotientTable[j][i] == identityCoset) {

                    cout << "Inverse of Q" << i
                         << " is Q" << j << "\n";

                    found = true;
                    break;
                }
            }

            if (!found) {
                inversesValid = false;
                cout << "Inverse missing for Q" << i << "\n";
            }
        }

        bool closureValid = true;

        for (int i = 0; i < count; i++) {
            for (int j = 0; j < count; j++) {
                if (quotientTable[i][j] < 0 ||
                    quotientTable[i][j] >= count) {
                    closureValid = false;
                }
            }
        }

        cout << "\nQuotient closure: "
             << (closureValid ? "Passed" : "Failed") << "\n";

        cout << "Quotient inverse property: "
             << (inversesValid ? "Passed" : "Failed") << "\n";

        if (closureValid && inversesValid) {
            cout << "Quotient group operations verified.\n";
        }
    }
};

int main() {
    int n, m;

    cout << "QUOTIENT GROUP OF GRAPH AUTOMORPHISMS\n";

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

    QuotientGroup graph(n);

    cout << "Enter edges (u v), using vertices 0 to "
         << n - 1 << ":\n";

    for (int i = 0; i < m; i++) {
        int u, v;

        if (!(cin >> u >> v)) {
            cout << "Invalid input.\n";
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

    cout << "\nEnter number of subgroup generators: ";

    if (!(cin >> count) ||
        count < 0 ||
        count > graph.groupSize() - 1) {
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

    if (!graph.generateSubgroup(generatorIDs)) {
        cout << "Invalid generator selection.\n";
        return 1;
    }

    graph.displaySubgroup();

    if (!graph.constructCosets()) {
        return 1;
    }

    graph.displayCosets();

    graph.constructQuotientTable();
    graph.displayQuotientTable();
    graph.analyzeQuotientGroup();

    cout << "\nQuotient group construction completed.\n";

    return 0;
}
