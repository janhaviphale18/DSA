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

    // Recursive function to display stored words
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

    // Recursively free allocated memory
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
    // Create root node
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

        // Traverse each character
        for (char character : word)
        {
            // Validate lowercase English alphabet
            if (character < 'a' || character > 'z')
            {
                cout << "Invalid word! Use lowercase letters only.\n";
                return;
            }

            int index = character - 'a';

            // Create node if it does not exist
            if (current->children[index] == nullptr)
            {
                current->children[index] = new TrieNode();
            }

            // Move to the next node
            current = current->children[index];
        }

        // Mark the last node as end of word
        if (current->isEndOfWord)
        {
            cout << "Word already exists in Trie.\n";
        }
        else
        {
            current->isEndOfWord = true;
            cout << "Word inserted successfully.\n";
        }
    }

    // Display all stored words
    void display()
    {
        cout << "\nWords stored in Trie:\n";

        displayHelper(root, "");
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

    for (int i = 0; i < numberOfWords; i++)
    {
        string word;

        cout << "Enter word " << i + 1 << ": ";
        cin >> word;

        trie.insert(word);
    }

    trie.display();

    return 0;
}
