#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

struct TrieNode
{
    TrieNode* children[26];
    TrieNode* failureLink;

    string prefix;
    vector<string> output;

    TrieNode()
    {
        for (int i = 0; i < 26; i++)
        {
            children[i] = nullptr;
        }

        failureLink = nullptr;
        prefix = "";
    }
};

class AhoCorasick
{
private:
    TrieNode* root;
    vector<TrieNode*> allNodes;

    int getIndex(char ch)
    {
        return ch - 'a';
    }

    bool isValid(const string& value)
    {
        if (value.empty())
        {
            return false;
        }

        for (char ch : value)
        {
            if (ch < 'a' || ch > 'z')
            {
                return false;
            }
        }

        return true;
    }

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
    AhoCorasick()
    {
        root = new TrieNode();
        root->failureLink = root;

        allNodes.push_back(root);
    }

    ~AhoCorasick()
    {
        deleteTrie(root);
    }

    // Insert a pattern into the Trie.
    bool insertPattern(const string& pattern)
    {
        if (!isValid(pattern))
        {
            return false;
        }

        TrieNode* current = root;

        for (char ch : pattern)
        {
            int index = getIndex(ch);

            if (current->children[index] == nullptr)
            {
                TrieNode* newNode = new TrieNode();

                newNode->prefix = current->prefix + ch;

                current->children[index] = newNode;

                allNodes.push_back(newNode);
            }

            current = current->children[index];
        }

        current->output.push_back(pattern);

        return true;
    }

    // Construct failure links using BFS.
    void buildFailureLinks()
    {
        queue<TrieNode*> q;

        // Root's direct children fail to the root.
        for (int i = 0; i < 26; i++)
        {
            TrieNode* child = root->children[i];

            if (child != nullptr)
            {
                child->failureLink = root;
                q.push(child);
            }
        }

        // Process nodes level by level.
        while (!q.empty())
        {
            TrieNode* current = q.front();
            q.pop();

            for (int i = 0; i < 26; i++)
            {
                TrieNode* child = current->children[i];

                if (child == nullptr)
                {
                    continue;
                }

                TrieNode* fallback = current->failureLink;

                // Follow failure links until a transition exists.
                while (fallback != root &&
                       fallback->children[i] == nullptr)
                {
                    fallback = fallback->failureLink;
                }

                // Assign the child's failure link.
                if (fallback->children[i] != nullptr)
                {
                    child->failureLink = fallback->children[i];
                }
                else
                {
                    child->failureLink = root;
                }

                // Copy patterns ending at the failure state.
                for (const string& pattern :
                     child->failureLink->output)
                {
                    child->output.push_back(pattern);
                }

                q.push(child);
            }
        }
    }

    // Display every node and its failure destination.
    void displayFailureLinks()
    {
        cout << "\nFailure Link Table:\n";

        cout << "Trie Prefix\tFailure Destination\n";

        for (TrieNode* node : allNodes)
        {
            if (node == root)
            {
                continue;
            }

            cout << node->prefix << "\t\t";

            if (node->failureLink == root)
            {
                cout << "ROOT";
            }
            else
            {
                cout << node->failureLink->prefix;
            }

            cout << "\n";
        }
    }

    // Search for all patterns, including overlapping matches.
    void searchText(const string& text)
    {
        for (char ch : text)
        {
            if (ch < 'a' || ch > 'z')
            {
                cout << "Invalid text. Use lowercase letters only.\n";
                return;
            }
        }

        TrieNode* current = root;
        bool foundAny = false;

        cout << "\nMatching Pattern Occurrences:\n";

        for (int i = 0; i < (int)text.length(); i++)
        {
            int index = getIndex(text[i]);

            // Follow failure links when no transition exists.
            while (current != root &&
                   current->children[index] == nullptr)
            {
                current = current->failureLink;
            }

            // Move to the matching child if available.
            if (current->children[index] != nullptr)
            {
                current = current->children[index];
            }

            // Report all patterns ending at this position.
            for (const string& pattern : current->output)
            {
                int startPosition =
                    i - (int)pattern.length() + 1;

                cout << "Pattern: " << pattern
                     << " | Start: " << startPosition
                     << " | End: " << i << "\n";

                foundAny = true;
            }
        }

        if (!foundAny)
        {
            cout << "No patterns found.\n";
        }
    }
};

int main()
{
    AhoCorasick matcher;

    int patternCount;

    cout << "Enter number of patterns: ";
    cin >> patternCount;

    if (!cin || patternCount <= 0)
    {
        cout << "Invalid number of patterns.\n";
        return 1;
    }

    for (int i = 0; i < patternCount; i++)
    {
        string pattern;

        cout << "Enter pattern " << i + 1 << ": ";
        cin >> pattern;

        if (!matcher.insertPattern(pattern))
        {
            cout << "Invalid pattern. Use lowercase letters only.\n";
            i--;
        }
    }

    matcher.buildFailureLinks();

    cout << "\nFailure links constructed successfully.\n";

    matcher.displayFailureLinks();

    string text;

    cout << "\nEnter text to search: ";
    cin >> text;

    matcher.searchText(text);

    return 0;
}
