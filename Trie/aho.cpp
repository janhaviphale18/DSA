#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

struct TrieNode
{
    TrieNode* children[26];
    TrieNode* failureLink;
    vector<string> output;

    TrieNode()
    {
        for (int i = 0; i < 26; i++)
        {
            children[i] = nullptr;
        }

        failureLink = nullptr;
    }
};

class AhoCorasick
{
private:
    TrieNode* root;

    int getIndex(char ch)
    {
        return ch - 'a';
    }

    bool isValidWord(const string& word)
    {
        if (word.empty())
        {
            return false;
        }

        for (char ch : word)
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
    }

    ~AhoCorasick()
    {
        deleteTrie(root);
    }

    // Insert a pattern into the Trie.
    bool insertPattern(const string& pattern)
    {
        if (!isValidWord(pattern))
        {
            return false;
        }

        TrieNode* current = root;

        for (char ch : pattern)
        {
            int index = getIndex(ch);

            if (current->children[index] == nullptr)
            {
                current->children[index] = new TrieNode();
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

        for (int i = 0; i < 26; i++)
        {
            TrieNode* child = root->children[i];

            if (child != nullptr)
            {
                child->failureLink = root;
                q.push(child);
            }
        }

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

                while (fallback != root &&
                       fallback->children[i] == nullptr)
                {
                    fallback = fallback->failureLink;
                }

                if (fallback->children[i] != nullptr)
                {
                    child->failureLink = fallback->children[i];
                }
                else
                {
                    child->failureLink = root;
                }

                // Inherit patterns from the failure state.
                for (const string& pattern :
                     child->failureLink->output)
                {
                    child->output.push_back(pattern);
                }

                q.push(child);
            }
        }
    }

    // Search for all patterns in the given text.
    void searchText(const string& text)
    {
        TrieNode* current = root;
        bool foundAny = false;

        for (char ch : text)
        {
            if (ch < 'a' || ch > 'z')
            {
                cout << "\nInvalid text character: " << ch << "\n";
                return;
            }
        }

        cout << "\nPattern matching results:\n";

        for (int i = 0; i < (int)text.length(); i++)
        {
            int index = getIndex(text[i]);

            while (current != root &&
                   current->children[index] == nullptr)
            {
                current = current->failureLink;
            }

            if (current->children[index] != nullptr)
            {
                current = current->children[index];
            }

            for (const string& pattern : current->output)
            {
                int startPosition =
                    i - (int)pattern.length() + 1;

                cout << "Pattern: " << pattern
                     << " | Start index: " << startPosition
                     << " | End index: " << i << "\n";

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

    vector<string> patterns;

    for (int i = 0; i < patternCount; i++)
    {
        string pattern;

        cout << "Enter pattern " << i + 1 << ": ";
        cin >> pattern;

        if (!matcher.insertPattern(pattern))
        {
            cout << "Invalid pattern. Use lowercase letters only.\n";
            i--;
            continue;
        }

        patterns.push_back(pattern);
    }

    matcher.buildFailureLinks();

    cout << "\nFailure links constructed successfully.\n";

    string text;

    cout << "\nEnter text to search: ";
    cin >> text;

    matcher.searchText(text);

    return 0;
}
