#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int n;
long long maxSolutions;

vector<vector<long long>> cost;

vector<bool> visited;

vector<int> currentPath;
vector<int> bestPath;

vector<vector<int>> bestTours;

long long currentCost = 0;
long long minimumCost = LLONG_MAX;

long long recursiveCalls = 0;
long long optimalTourCount = 0;

bool storageLimitReached = false;

// Display a tour
void displayTour(const vector<int>& tour) {

    for (int i = 0; i < (int)tour.size(); i++) {

        cout << tour[i];

        if (i != (int)tour.size() - 1) {
            cout << " -> ";
        }
    }
}

// Store a newly discovered optimal tour
void storeTour() {

    optimalTourCount++;

    if ((long long)bestTours.size() < maxSolutions) {

        bestTours.push_back(currentPath);

    } else {

        storageLimitReached = true;
    }
}

// Recursive TSP backtracking
void solveTSP(int currentCity, int visitedCount) {

    recursiveCalls++;

    // All cities have been visited
    if (visitedCount == n) {

        // Check whether a return route to the starting city exists
        if (cost[currentCity][0] == -1) {
            return;
        }

        long long totalCost =
            currentCost + cost[currentCity][0];

        // Add the return to the starting city
        currentPath.push_back(0);

        // A better tour has been found
        if (totalCost < minimumCost) {

            minimumCost = totalCost;

            bestPath = currentPath;

            bestTours.clear();

            optimalTourCount = 0;
            storageLimitReached = false;

            storeTour();
        }

        // Another tour with the same minimum cost
        else if (totalCost == minimumCost) {

            if (bestPath.empty()) {
                bestPath = currentPath;
            }

            storeTour();
        }

        currentPath.pop_back();

        return;
    }

    // Explore every unvisited city
    for (int nextCity = 1; nextCity < n; nextCity++) {

        // Skip already visited cities
        if (visited[nextCity]) {
            continue;
        }

        // Skip unavailable routes
        if (cost[currentCity][nextCity] == -1) {
            continue;
        }

        long long nextCost =
            currentCost + cost[currentCity][nextCity];

        // Prune branches that are already more expensive
        if (nextCost > minimumCost) {
            continue;
        }

        // Visit the next city
        visited[nextCity] = true;

        currentPath.push_back(nextCity);

        currentCost = nextCost;

        // Recursive exploration
        solveTSP(nextCity, visitedCount + 1);

        // Backtracking
        currentCost -= cost[currentCity == nextCity
                            ? currentPath[currentPath.size() - 2]
                            : currentCity][nextCity];

        currentPath.pop_back();

        visited[nextCity] = false;
    }
}

// A simpler recursive implementation with explicit previous city
void searchTSP(int currentCity, int visitedCount) {

    recursiveCalls++;

    // All cities have been visited
    if (visitedCount == n) {

        if (cost[currentCity][0] == -1) {
            return;
        }

        long long totalCost =
            currentCost + cost[currentCity][0];

        currentPath.push_back(0);

        if (totalCost < minimumCost) {

            minimumCost = totalCost;

            bestPath = currentPath;

            bestTours.clear();

            optimalTourCount = 0;
            storageLimitReached = false;

            storeTour();
        }

        else if (totalCost == minimumCost) {

            if (bestPath.empty()) {
                bestPath = currentPath;
            }

            storeTour();
        }

        currentPath.pop_back();

        return;
    }

    // Try every unvisited city
    for (int nextCity = 1; nextCity < n; nextCity++) {

        if (visited[nextCity]) {
            continue;
        }

        if (cost[currentCity][nextCity] == -1) {
            continue;
        }

        long long edgeCost = cost[currentCity][nextCity];

        long long nextCost = currentCost + edgeCost;

        // Branch pruning
        if (nextCost > minimumCost) {
            continue;
        }

        // Make the choice
        visited[nextCity] = true;
        currentPath.push_back(nextCity);

        currentCost = nextCost;

        // Explore the next city
        searchTSP(nextCity, visitedCount + 1);

        // Restore the previous cost
        currentCost -= edgeCost;

        // Backtrack
        currentPath.pop_back();
        visited[nextCity] = false;
    }
}

// Solve the TSP
void solve() {

    visited.assign(n, false);

    currentPath.clear();
    bestPath.clear();
    bestTours.clear();

    currentCost = 0;
    minimumCost = LLONG_MAX;

    recursiveCalls = 0;
    optimalTourCount = 0;
    storageLimitReached = false;

    // Start from city 0
    visited[0] = true;
    currentPath.push_back(0);

    // A single city requires no travelling
    if (n == 1) {

        currentPath.push_back(0);

        minimumCost = 0;
        bestPath = currentPath;

        storeTour();

        return;
    }

    searchTSP(0, 1);
}

// Display all optimal tours
void displayResults() {

    cout << "\n========== TSP RESULTS ==========\n";

    cout << "\nMinimum travelling cost: "
         << minimumCost << endl;

    cout << "\nOne optimal tour:\n";

    displayTour(bestPath);

    cout << "\n\nAll stored optimal tours:\n";

    for (int i = 0; i < (int)bestTours.size(); i++) {

        cout << "\nTour " << i + 1 << ": ";

        displayTour(bestTours[i]);

        cout << endl;
    }

    cout << "\nTotal optimal tours found: "
         << optimalTourCount << endl;

    if (storageLimitReached) {

        cout << "\nStorage limit reached.\n";

        cout << "Additional optimal tours were found "
             << "but not stored.\n";
    }
}

// Display the cost matrix
void displayMatrix() {

    cout << "\n========== COST MATRIX ==========\n";

    for (int i = 0; i < n; i++) {

        for (int j = 0; j < n; j++) {

            if (cost[i][j] == -1) {
                cout << "X ";
            } else {
                cout << cost[i][j] << " ";
            }
        }

        cout << endl;
    }
}

int main() {

    cout << "===== TRAVELING SALESMAN PROBLEM =====\n";

    cout << "\nEnter number of cities: ";
    cin >> n;

    if (n <= 0) {

        cout << "\nNumber of cities must be positive.\n";
        return 0;
    }

    if (n > 12) {

        cout << "\nToo many cities for this basic backtracking implementation.\n";

        cout << "Please enter at most 12 cities.\n";

        return 0;
    }

    cost.resize(n, vector<long long>(n));

    cout << "\nEnter the cost matrix:\n";

    cout << "-1 = No direct route\n";
    cout << "0 = Same city\n";
    cout << "Positive value = Travelling cost\n\n";

    for (int i = 0; i < n; i++) {

        for (int j = 0; j < n; j++) {

            cin >> cost[i][j];

            if (cost[i][j] < -1 ||
                cost[i][j] > 1000000000000LL) {

                cout << "\nInvalid travelling cost.\n";
                return 0;
            }

            if (i == j && cost[i][j] != 0) {

                cout << "\nDiagonal elements must be zero.\n";
                return 0;
            }
        }
    }

    cout << "\nEnter maximum optimal tours to store: ";
    cin >> maxSolutions;

    if (maxSolutions <= 0) {

        cout << "\nStorage limit must be positive.\n";
        return 0;
    }

    displayMatrix();

    cout << "\nStarting journey from City 0...\n";

    solve();

    if (bestPath.empty()) {

        cout << "\nNo Hamiltonian cycle exists.\n";

        cout << "It is not possible to visit every city "
             << "and return to City 0.\n";

    } else {

        displayResults();
    }

    cout << "\nTotal recursive calls: "
         << recursiveCalls << endl;

    return 0;
}
