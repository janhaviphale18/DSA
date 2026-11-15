#include <iostream>
#include <vector>
using namespace std;

int n;
long long target;
long long maxSolutions;

vector<int> arr;
vector<int> currentSubset;
vector<vector<int>> solutions;

long long recursiveCalls = 0;
bool limitReached = false;

void findSubsets(int index, long long currentSum) {

    recursiveCalls++;

    // Stop exploring if the solution limit has been reached
    if ((long long)solutions.size() >= maxSolutions) {
        limitReached = true;
        return;
    }

    // All elements have been considered
    if (index == n) {

        if (currentSum == target) {
            solutions.push_back(currentSubset);
        }

        return;
    }

    // Choice 1: Include the current element
    currentSubset.push_back(arr[index]);

    findSubsets(
        index + 1,
        currentSum + arr[index]
    );

    // Undo the inclusion
    currentSubset.pop_back();

    // Stop if the display limit was reached
    if (limitReached) {
        return;
    }

    // Choice 2: Exclude the current element
    findSubsets(index + 1, currentSum);
}

void displaySolutions() {

    cout << "\n========== VALID SUBSETS ==========\n";

    for (int i = 0; i < (int)solutions.size(); i++) {

        cout << "\nSubset " << i + 1 << ": { ";

        if (solutions[i].empty()) {
            cout << "EMPTY";
        } else {

            for (int j = 0; j < (int)solutions[i].size(); j++) {

                cout << solutions[i][j];

                if (j != (int)solutions[i].size() - 1) {
                    cout << ", ";
                }
            }
        }

        cout << " }";

        long long sum = 0;

        for (int value : solutions[i]) {
            sum += value;
        }

        cout << "  Sum = " << sum << endl;
    }

    cout << "\nTotal subsets found: " << solutions.size() << endl;

    if (limitReached) {
        cout << "Search stopped after reaching the solution limit."
             << endl;
        cout << "Additional valid subsets, if any, were not explored."
             << endl;
    }
}

int main() {

    cout << "===== SUBSET SUM USING BACKTRACKING =====\n";

    cout << "\nEnter number of elements: ";
    cin >> n;

    if (n < 0) {
        cout << "\nNumber of elements cannot be negative.\n";
        return 0;
    }

    if (n > 25) {
        cout << "\nInput is too large for this exhaustive backtracking program.\n";
        cout << "Please enter at most 25 elements.\n";
        return 0;
    }

    arr.resize(n);

    cout << "\nEnter " << n << " elements:\n";

    for (int i = 0; i < n; i++) {

        cin >> arr[i];
    }

    cout << "\nEnter target sum: ";
    cin >> target;

    cout << "\nEnter maximum number of solutions to display: ";
    cin >> maxSolutions;

    if (maxSolutions <= 0) {
        cout << "\nSolution limit must be positive.\n";
        return 0;
    }

    // Start recursive backtracking
    findSubsets(0, 0);

    if (solutions.empty()) {

        cout << "\nNo subset produces the target sum.\n";

        cout << "Total recursive calls: "
             << recursiveCalls << endl;

        return 0;
    }

    displaySolutions();

    cout << "\nTotal recursive calls: "
         << recursiveCalls << endl;

    return 0;
}
