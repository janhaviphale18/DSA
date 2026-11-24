
#include <iostream>
#include <vector>
#include <cstdint>
#include <limits>
using namespace std;

struct TrieNode
{
    int children[2];
    int count;

    TrieNode()
    {
        children[0] = 0;
        children[1] = 0;
        count = 0;
    }
};

struct QueryResult
{
    uint32_t selectedNumber;
    uint32_t maximumXOR;
};

class PersistentBinaryTrie
{
private:
    vector<TrieNode> nodes;
    vector<int> roots;

    // Create a new node by copying an existing node.
    int cloneNode(int previousNode)
    {
        nodes.push_back(nodes[previousNode]);

        return (int)nodes.size() - 1;
    }

    // Insert a number using path copying.
    int insert(
        int previousNode,
        uint32_t number,
        int bit)
    {
        int currentNode = cloneNode(previousNode);

        nodes[currentNode].count++;

        if (bit < 0)
        {
            return currentNode;
        }

        int currentBit = (number >> bit) & 1;

        int previousChild =
            nodes[previousNode].children[currentBit];

        int newChild = insert(
            previousChild,
            number,
            bit - 1
        );

        nodes[currentNode].children[currentBit] = newChild;

        return currentNode;
    }

public:
    PersistentBinaryTrie()
    {
        // Node zero represents an empty/null node.
        nodes.push_back(TrieNode());

        // Version zero represents an empty Trie.
        roots.push_back(0);
    }

    // Build a new Trie version after inserting a number.
    void addNumber(uint32_t number)
    {
        int newRoot = insert(
            roots.back(),
            number,
            31
        );

        roots.push_back(newRoot);
    }

    // Count elements in a branch within a given range.
    int getRangeCount(
        int rightNode,
        int leftNode,
        int bit)
    {
        if (rightNode == 0 && leftNode == 0)
        {
            return 0;
        }

        return nodes[rightNode].count -
               nodes[leftNode].count;
    }

    // Find maximum XOR within an inclusive range.
    QueryResult maximumXOR(
        uint32_t number,
        int left,
        int right)
    {
        int rightNode = roots[right + 1];
        int leftNode = roots[left];

        uint32_t selectedNumber = 0;
        uint32_t result = 0;

        for (int bit = 31; bit >= 0; bit--)
        {
            int currentBit = (number >> bit) & 1;

            // Prefer the opposite bit to maximize XOR.
            int preferredBit = 1 - currentBit;

            int preferredRight =
                nodes[rightNode].children[preferredBit];

            int preferredLeft =
                nodes[leftNode].children[preferredBit];

            int preferredCount =
                getRangeCount(
                    preferredRight,
                    preferredLeft,
                    bit
                );

            int chosenBit;

            if (preferredCount > 0)
            {
                chosenBit = preferredBit;
                result |= (1u << bit);
            }
            else
            {
                chosenBit = currentBit;
            }

            // Reconstruct the selected array element.
            if (chosenBit == 1)
            {
                selectedNumber |= (1u << bit);
            }

            rightNode =
                nodes[rightNode].children[chosenBit];

            leftNode =
                nodes[leftNode].children[chosenBit];
        }

        return {selectedNumber, result};
    }

    // Display the number of persistent versions.
    int versionCount()
    {
        return (int)roots.size() - 1;
    }
};

// Read and validate a 32-bit unsigned integer.
bool readUnsigned32(const string& message, uint32_t& value)
{
    long long input;

    cout << message;
    cin >> input;

    if (!cin || input < 0 ||
        input > numeric_limits<uint32_t>::max())
    {
        return false;
    }

    value = (uint32_t)input;

    return true;
}

int main()
{
    PersistentBinaryTrie trie;

    int n;

    cout << "Enter number of array elements: ";
    cin >> n;

    if (!cin || n <= 0)
    {
        cout << "Invalid array size.\n";
        return 1;
    }

    vector<uint32_t> arr(n);

    cout << "\nEnter array elements:\n";

    for (int i = 0; i < n; i++)
    {
        if (!readUnsigned32(
                "Element " + to_string(i) + ": ",
                arr[i]))
        {
            cout << "Invalid element. Enter a value "
                 << "between 0 and 4294967295.\n";
            return 1;
        }

        trie.addNumber(arr[i]);
    }

    cout << "\nPersistent Binary Trie constructed successfully.\n";

    cout << "Total Trie versions: "
         << trie.versionCount() << "\n";

    int queryCount;

    cout << "\nEnter number of queries: ";
    cin >> queryCount;

    if (!cin || queryCount < 0)
    {
        cout << "Invalid query count.\n";
        return 1;
    }

    for (int i = 0; i < queryCount; i++)
    {
        cout << "\n========== QUERY "
             << i + 1 << " ==========\n";

        uint32_t x;

        if (!readUnsigned32("Enter XOR value x: ", x))
        {
            cout << "Invalid XOR value.\n";
            return 1;
        }

        int left, right;

        cout << "Enter left index (L): ";
        cin >> left;

        cout << "Enter right index (R): ";
        cin >> right;

        if (!cin || left < 0 || right >= n ||
            left > right)
        {
            cout << "Invalid range. Use 0 <= L <= R < "
                 << n << ".\n";
            i--;
            continue;
        }

        QueryResult result =
            trie.maximumXOR(x, left, right);

        cout << "\nRange: [" << left
             << ", " << right << "]\n";

        cout << "Selected array element: "
             << result.selectedNumber << "\n";

        cout << "Maximum XOR value: "
             << result.maximumXOR << "\n";
    }

    return 0;
}
