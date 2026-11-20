#include <iostream>
#include <string>
using namespace std;

// Structure representing one Trie node
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

// Class representing the Trie
class Trie
{
private:
    TrieNode* root;

    // Recursive function to display the Trie
    void displayHelper(TrieNode* node, string currentWord)
    {
        if (node == nullptr)
        {
            return;
        }

        if (node->isEndOfWord)
        {
            cout << currentWord << endl;
        }

        for (int i = 0; i < 26; i++)
        {
            if (node->children[i] != nullptr)
            {
                char character = 'a' + i;

                displayHelper(
                    node->children[i],
                    currentWord + character
                );
            }
        }
    }

public:
    // Constructor creates the root node
    Trie()
    {
        root = new TrieNode();
    }

    // Insert a word into Trie
    void insert(string word)
    {
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

        current->isEndOfWord = true;

        cout << "Word inserted successfully.\n";
    }

    // Display all complete words
    void display()
    {
        cout << "\nWords stored in Trie:\n";

        displayHelper(root, "");

    }
    
    // Check whether the Trie is empty
    bool isEmpty()
    {
        for (int i = 0; i < 26; i++)
        {
            if (root->children[i] != nullptr)
            {
                return false;
            }
        }

        return true;
    }

    // Destructor to release allocated memory
    ~Trie()
    {
        clear(root);
    }

    // Recursively delete all nodes
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
};

// Main function
int main()
{
    Trie trie;

    int numberOfWords;

    cout << "Enter number of words to insert: ";
    cin >> numberOfWords;

    if (numberOfWords < 0)
    {
        cout << "Invalid number of words.\n";
        return 0;
    }

    for (int i = 0; i < numberOfWords; i++)
    {
        string word;

        cout << "Enter word " << i + 1 << ": ";
        cin >> word;

        trie.insert(word);
    }

    if (trie.isEmpty())
    {
        cout << "\nTrie is empty.\n";
    }
    else
    {
        trie.display();
    }

    return 0;
}
