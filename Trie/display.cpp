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

    // Validate lowercase English words
    bool isValid(string word)
    {
        if (word.empty())
        {
            return false;
        }

        for (char character : word)
        {
            if (character < 'a' || character > 'z')
            {
                return false;
            }
        }

        return true;
    }

    // Recursive function to display words
    void displayHelper(
        TrieNode* node,
        string& currentWord,
        int& totalWords
    )
    {
        if (node == nullptr)
        {
            return;
        }

        // Print if a complete word ends here
        if (node->isEndOfWord)
        {
            cout << currentWord << endl;
            totalWords++;
        }

        // Explore all existing children
        for (int i = 0; i < 26; i++)
        {
            if (node->children[i] != nullptr)
            {
                char character = 'a' + i;

                // Add current character
                currentWord.push_back(character);

                // Explore the child node
                displayHelper(
                    node->children[i],
                    currentWord,
                    totalWords
                );

                // Backtrack
                currentWord.pop_back();
            }
        }
    }

    // Recursively release allocated memory
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
        if (!isValid(word))
        {
            cout << "Invalid word! Use lowercase letters only.\n";
            return;
        }

        TrieNode* current = root;

        for (char character : word)
        {
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

    // Display all stored words
    void display()
    {
        if (isEmpty())
        {
            cout << "\nTrie is empty.\n";
            return;
        }

        string currentWord = "";
        int totalWords = 0;

        cout << "\nWords stored in Trie:\n";

        displayHelper(root, currentWord, totalWords);

        cout << "\nTotal number of words: "
             << totalWords << endl;
    }

    // Check whether Trie is empty
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

    // Display all words
    trie.display();

    return 0;
}
