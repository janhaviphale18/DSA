#include <iostream>
#include <string>
using namespace std;

// Structure representing a Trie node
struct TrieNode
{
    TrieNode* children[26];
    bool isEndOfWord;

    // Constructor
    TrieNode()
    {
        isEndOfWord = false;

        for (int i = 0; i < 26; i++)
        {
            children[i] = nullptr;
        }
    }
};

// Class representing Trie
class Trie
{
private:
    TrieNode* root;

    // Recursively release memory
    void clear(TrieNode* node)
    {
        if (node == nullptr)
        {
            return;
        }

        for (int i = 0; i < 26; i++)
        {
            clear(node->children[i]);
        }

        delete node;
    }

public:
    // Constructor
    Trie()
    {
        root = new TrieNode();
    }

    // Insert a word into Trie
    void insert(string word)
    {
        if (word.empty())
        {
            cout << "Empty word cannot be inserted.\n";
            return;
        }

        TrieNode* current = root;

        for (char character : word)
        {
            if (character < 'a' || character > 'z')
            {
                cout << "Invalid word! Use lowercase letters only.\n";
                return;
            }

            int index = character - 'a';

            if (current->children[index] == nullptr)
            {
                current->children[index] = new TrieNode();
            }

            current = current->children[index];
        }

        if (current->isEndOfWord)
        {
            cout << "Word already exists.\n";
        }
        else
        {
            current->isEndOfWord = true;
            cout << "Word inserted successfully.\n";
        }
    }

    // Search for a prefix
    bool startsWith(string prefix)
    {
        if (prefix.empty())
        {
            return false;
        }

        TrieNode* current = root;

        for (char character : prefix)
        {
            if (character < 'a' || character > 'z')
            {
                return false;
            }

            int index = character - 'a';

            // Check whether the required child exists
            if (current->children[index] == nullptr)
            {
                return false;
            }

            // Move to the next node
            current = current->children[index];
        }

        // All prefix characters exist
        return true;
    }

    // Destructor
    ~Trie()
    {
        clear(root);
    }
};

// Main function
int main()
{
    Trie trie;

    int numberOfWords;

    cout << "Enter number of words to insert: ";
    cin >> numberOfWords;

    if (cin.fail() || numberOfWords < 0)
    {
        cout << "Invalid number of words.\n";
        return 0;
    }

    // Insert words
    for (int i = 0; i < numberOfWords; i++)
    {
        string word;

        cout << "Enter word " << i + 1 << ": ";
        cin >> word;

        trie.insert(word);
    }

    // Accept prefix queries
    int numberOfPrefixes;

    cout << "\nEnter number of prefixes to search: ";
    cin >> numberOfPrefixes;

    if (cin.fail() || numberOfPrefixes < 0)
    {
        cout << "Invalid number of prefixes.\n";
        return 0;
    }

    // Perform prefix searching
    for (int i = 0; i < numberOfPrefixes; i++)
    {
        string prefix;

        cout << "Enter prefix " << i + 1 << ": ";
        cin >> prefix;

        if (trie.startsWith(prefix))
        {
            cout << prefix << " : Prefix found.\n";
        }
        else
        {
            cout << prefix << " : Prefix not found.\n";
        }
    }

    return 0;
}
