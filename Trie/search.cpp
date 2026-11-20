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

    // Recursive function to free memory
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

    // Insert a word
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

    // Search for an exact word
    bool search(string word)
    {
        if (word.empty())
        {
            return false;
        }

        TrieNode* current = root;

        for (char character : word)
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

        // Check whether the complete word exists
        return current->isEndOfWord;
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

    // Accept search queries
    int numberOfSearches;

    cout << "\nEnter number of words to search: ";
    cin >> numberOfSearches;

    if (cin.fail() || numberOfSearches < 0)
    {
        cout << "Invalid number of searches.\n";
        return 0;
    }

    // Perform exact searching
    for (int i = 0; i < numberOfSearches; i++)
    {
        string searchWord;

        cout << "Enter search word " << i + 1 << ": ";
        cin >> searchWord;

        if (trie.search(searchWord))
        {
            cout << searchWord << " : Word found.\n";
        }
        else
        {
            cout << searchWord << " : Word not found.\n";
        }
    }

    return 0;
}
