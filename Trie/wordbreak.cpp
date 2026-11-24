#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct TrieNode
{
    TrieNode* children[26];
    bool isEndOfWord;

    TrieNode()
    {
        for (int i = 0; i < 26; i++)
        {
            children[i] = nullptr;
        }

        isEndOfWord = false;
    }
};

class WordBreakTrie
{
private:
    TrieNode* root;

    // Convert uppercase letters into lowercase.
    string normalize(const string& word)
    {
        string result = word;

        for (char& ch : result)
        {
            if (ch >= 'A' && ch <= 'Z')
            {
                ch = ch - 'A' + 'a';
            }
        }

        return result;
    }

    // Validate lowercase English alphabet characters.
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

    // Delete all dynamically allocated Trie nodes.
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
    WordBreakTrie()
    {
        root = new TrieNode();
    }

    ~WordBreakTrie()
    {
        deleteTrie(root);
    }

    // Insert a dictionary word.
    bool insertWord(const string& inputWord)
    {
        string word = normalize(inputWord);

        if (!isValidWord(word))
        {
            return false;
        }

        TrieNode* current = root;

        for (char ch : word)
        {
            int index = ch - 'a';

            if (current->children[index] == nullptr)
            {
                current->children[index] = new TrieNode();
            }

            current = current->children[index];
        }

        current->isEndOfWord = true;

        return true;
    }

    // Check whether the string can be segmented.
    bool wordBreak(
        const string& input,
        vector<string>& segmentation)
    {
        string text = normalize(input);

        if (!isValidWord(text))
        {
            return false;
        }

        int n = (int)text.length();

        vector<bool> dp(n + 1, false);

        // Store the previous boundary for reconstruction.
        vector<int> previous(n + 1, -1);

        // Store the last word used to reach each position.
        vector<string> lastWord(n + 1);

        dp[0] = true;

        // Try every reachable starting position.
        for (int i = 0; i < n; i++)
        {
            if (!dp[i])
            {
                continue;
            }

            TrieNode* current = root;

            // Search for dictionary words starting at i.
            for (int j = i; j < n; j++)
            {
                int index = text[j] - 'a';

                if (current->children[index] == nullptr)
                {
                    break;
                }

                current = current->children[index];

                // A complete dictionary word is found.
                if (current->isEndOfWord)
                {
                    dp[j + 1] = true;

                    previous[j + 1] = i;

                    lastWord[j + 1] =
                        text.substr(i, j - i + 1);
                }
            }
        }

        if (!dp[n])
        {
            return false;
        }

        // Reconstruct one valid segmentation.
        segmentation.clear();

        int position = n;

        while (position > 0)
        {
            segmentation.push_back(lastWord[position]);

            position = previous[position];
        }

        reverse(segmentation.begin(), segmentation.end());

        return true;
    }
};

int main()
{
    WordBreakTrie dictionary;

    int wordCount;

    cout << "Enter number of dictionary words: ";
    cin >> wordCount;

    if (!cin || wordCount <= 0)
    {
        cout << "Invalid dictionary size.\n";
        return 1;
    }

    for (int i = 0; i < wordCount; i++)
    {
        string word;

        cout << "Enter dictionary word " << i + 1 << ": ";
        cin >> word;

        if (!dictionary.insertWord(word))
        {
            cout << "Invalid word. Use English letters only.\n";
            i--;
            continue;
        }
    }

    string input;

    cout << "\nEnter string to check: ";
    cin >> input;

    vector<string> segmentation;

    if (input.empty())
    {
        cout << "Empty string cannot be processed.\n";
        return 0;
    }

    bool result = dictionary.wordBreak(input, segmentation);

    if (result)
    {
        cout << "\nWord segmentation is possible.\n";

        cout << "One valid segmentation: ";

        for (int i = 0; i < (int)segmentation.size(); i++)
        {
            cout << segmentation[i];

            if (i != (int)segmentation.size() - 1)
            {
                cout << " | ";
            }
        }

        cout << "\n";
    }
    else
    {
        cout << "\nWord segmentation is not possible.\n";
    }

    return 0;
}
