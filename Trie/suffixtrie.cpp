#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct TrieNode
{
    TrieNode* children[26];
    vector<int> suffixPositions;

    TrieNode()
    {
        for (int i = 0; i < 26; i++)
        {
            children[i] = nullptr;
        }
    }
};

class SuffixTrie
{
private:
    TrieNode* root;
    string originalString;

    int getIndex(char ch)
    {
        return ch - 'a';
    }

    string normalize(const string& text)
    {
        string result = text;

        for (char& ch : result)
        {
            if (ch >= 'A' && ch <= 'Z')
            {
                ch = ch - 'A' + 'a';
            }
        }

        return result;
    }

    bool isValid(const string& text)
    {
        if (text.empty())
        {
            return false;
        }

        for (char ch : text)
        {
            if (ch < 'a' || ch > 'z')
            {
                return false;
            }
        }

        return true;
    }

    // Insert one suffix into the Trie.
    void insertSuffix(int startPosition)
    {
        TrieNode* current = root;

        for (int i = startPosition;
             i < (int)originalString.length(); i++)
        {
            int index = getIndex(originalString[i]);

            if (current->children[index] == nullptr)
            {
                current->children[index] = new TrieNode();
            }

            current = current->children[index];
        }

        current->suffixPositions.push_back(startPosition);
    }

    // Collect all suffix starting positions below a node.
    void collectPositions(
        TrieNode* node,
        vector<int>& positions)
    {
        if (node == nullptr)
        {
            return;
        }

        for (int position : node->suffixPositions)
        {
            positions.push_back(position);
        }

        for (int i = 0; i < 26; i++)
        {
            collectPositions(node->children[i], positions);
        }
    }

    // Delete all Trie nodes.
    void deleteTrie(TrieNode* node)
    {
        if (node == nullptr)
        {
            return;
        }

        for (int i = 0; i < 26; i++)
        {
            deleteTrie(node->children[i]);
        }

        delete node;
    }

public:
    SuffixTrie()
    {
        root = new TrieNode();
    }

    ~SuffixTrie()
    {
        deleteTrie(root);
    }

    // Build a Suffix Trie from the input string.
    bool build(const string& input)
    {
        string text = normalize(input);

        if (!isValid(text))
        {
            return false;
        }

        originalString = text;

        for (int i = 0; i < (int)originalString.length(); i++)
        {
            insertSuffix(i);
        }

        return true;
    }

    // Find the Trie node representing a substring.
    TrieNode* findSubstringNode(const string& pattern)
    {
        if (pattern.empty())
        {
            return nullptr;
        }

        TrieNode* current = root;

        for (char ch : pattern)
        {
            int index = getIndex(ch);

            if (current->children[index] == nullptr)
            {
                return nullptr;
            }

            current = current->children[index];
        }

        return current;
    }

    // Check whether a substring exists.
    bool searchSubstring(const string& inputPattern)
    {
        string pattern = normalize(inputPattern);

        if (!isValid(pattern))
        {
            return false;
        }

        return findSubstringNode(pattern) != nullptr;
    }

    // Find every occurrence of a substring.
    vector<int> findOccurrences(const string& inputPattern)
    {
        vector<int> positions;

        string pattern = normalize(inputPattern);

        if (!isValid(pattern))
        {
            return positions;
        }

        TrieNode* node = findSubstringNode(pattern);

        if (node == nullptr)
        {
            return positions;
        }

        collectPositions(node, positions);

        sort(positions.begin(), positions.end());

        return positions;
    }

    // Display all suffixes.
    void displaySuffixes()
    {
        cout << "\nAll suffixes:\n";

        for (int i = 0; i < (int)originalString.length(); i++)
        {
            cout << i << " : "
                 << originalString.substr(i) << "\n";
        }
    }

    // Display substring search results.
    void displaySearchResult(const string& pattern)
    {
        vector<int> positions = findOccurrences(pattern);

        cout << "\nSubstring: " << pattern << "\n";

        if (positions.empty())
        {
            cout << "Substring not found.\n";
            return;
        }

        cout << "Substring found.\n";

        cout << "Starting positions: ";

        for (int position : positions)
        {
            cout << position << " ";
        }

        cout << "\nTotal occurrences: "
             << positions.size() << "\n";
    }
};

int main()
{
    SuffixTrie trie;

    string text;

    cout << "Enter original string: ";
    cin >> text;

    if (!trie.build(text))
    {
        cout << "Invalid string. Use English letters only.\n";
        return 1;
    }

    cout << "\nSuffix Trie constructed successfully.\n";

    trie.displaySuffixes();

    int queryCount;

    cout << "\nEnter number of substring searches: ";
    cin >> queryCount;

    if (!cin || queryCount < 0)
    {
        cout << "Invalid query count.\n";
        return 1;
    }

    for (int i = 0; i < queryCount; i++)
    {
        string pattern;

        cout << "\nEnter substring " << i + 1 << ": ";
        cin >> pattern;

        trie.displaySearchResult(pattern);
    }

    return 0;
}
