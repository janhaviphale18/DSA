#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

struct TrieNode
{
    TrieNode* children[26];
    TrieNode* failureLink;
    vector<int> output;

    TrieNode()
    {
        for (int i = 0; i < 26; i++)
        {
            children[i] = nullptr;
        }

        failureLink = nullptr;
    }
};

struct PatternInfo
{
    string pattern;
    int frequency;

    PatternInfo()
    {
        frequency = 0;
    }
};

struct Match
{
    string pattern;
    int start;
    int end;
};

class MultiPatternMatcher
{
private:
    TrieNode* root;
    vector<PatternInfo> patterns;
    vector<Match> matches;

    int getIndex(char ch)
    {
        return ch - 'a';
    }

    string normalize(const string& text)
    {
        string result = text;

        for (char& ch : result)
        {
            ch = (char)tolower((unsigned char)ch);
        }

        return result;
    }

    bool isValidPattern(const string& pattern)
    {
        if (pattern.empty())
        {
            return false;
        }

        for (char ch : pattern)
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
    MultiPatternMatcher()
    {
        root = new TrieNode();
        root->failureLink = root;
    }

    ~MultiPatternMatcher()
    {
        deleteTrie(root);
    }

    // Insert a pattern into the Trie.
    bool insertPattern(const string& inputPattern)
    {
        string pattern = normalize(inputPattern);

        if (!isValidPattern(pattern))
        {
            return false;
        }

        int patternID = -1;

        // Avoid storing duplicate patterns separately.
        for (int i = 0; i < (int)patterns.size(); i++)
        {
            if (patterns[i].pattern == pattern)
            {
                return true;
            }
        }

        PatternInfo info;
        info.pattern = pattern;

        patterns.push_back(info);
        patternID = (int)patterns.size() - 1;

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

        current->output.push_back(patternID);

        return true;
    }

    // Build failure links using BFS.
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

                // Inherit pattern IDs from the failure state.
                for (int id : child->failureLink->output)
                {
                    child->output.push_back(id);
                }

                q.push(child);
            }
        }
    }

    // Search the document and record all matches.
    void searchDocument(const string& document)
    {
        string text = normalize(document);

        TrieNode* current = root;

        matches.clear();

        for (PatternInfo& info : patterns)
        {
            info.frequency = 0;
        }

        for (int i = 0; i < (int)text.length(); i++)
        {
            char ch = text[i];

            // Treat spaces and punctuation as separators.
            if (ch < 'a' || ch > 'z')
            {
                current = root;
                continue;
            }

            int index = getIndex(ch);

            while (current != root &&
                   current->children[index] == nullptr)
            {
                current = current->failureLink;
            }

            if (current->children[index] != nullptr)
            {
                current = current->children[index];
            }

            for (int id : current->output)
            {
                int startPosition =
                    i - (int)patterns[id].pattern.length() + 1;

                int endPosition = i;

                patterns[id].frequency++;

                Match match;
                match.pattern = patterns[id].pattern;
                match.start = startPosition;
                match.end = endPosition;

                matches.push_back(match);
            }
        }
    }

    // Display all individual matches.
    void displayMatches()
    {
        cout << "\n========== MATCH DETAILS ==========\n";

        if (matches.empty())
        {
            cout << "No matching patterns found.\n";
            return;
        }

        for (const Match& match : matches)
        {
            cout << "Pattern: " << match.pattern
                 << " | Start: " << match.start
                 << " | End: " << match.end << "\n";
        }
    }

    // Display the frequency of each pattern.
    void displayFrequencyReport()
    {
        cout << "\n========== FREQUENCY REPORT ==========\n";

        int maximumFrequency = 0;
        int totalOccurrences = 0;

        for (const PatternInfo& info : patterns)
        {
            cout << info.pattern
                 << " : " << info.frequency << "\n";

            maximumFrequency =
                max(maximumFrequency, info.frequency);

            totalOccurrences += info.frequency;
        }

        cout << "\nTotal pattern occurrences: "
             << totalOccurrences << "\n";

        if (maximumFrequency == 0)
        {
            cout << "No patterns were found.\n";
            return;
        }

        cout << "\nMost frequent pattern(s):\n";

        for (const PatternInfo& info : patterns)
        {
            if (info.frequency == maximumFrequency)
            {
                cout << info.pattern
                     << " (" << info.frequency
                     << " occurrences)\n";
            }
        }
    }
};

int main()
{
    MultiPatternMatcher matcher;

    int patternCount;

    cout << "Enter number of patterns: ";
    cin >> patternCount;

    if (!cin || patternCount <= 0)
    {
        cout << "Invalid pattern count.\n";
        return 1;
    }

    for (int i = 0; i < patternCount; i++)
    {
        string pattern;

        cout << "Enter pattern " << i + 1 << ": ";
        cin >> pattern;

        if (!matcher.insertPattern(pattern))
        {
            cout << "Invalid pattern. Use English letters only.\n";
            i--;
            continue;
        }
    }

    matcher.buildFailureLinks();

    cout << "\nAho-Corasick automaton constructed successfully.\n";

    cin.ignore(10000, '\n');

    string document;

    cout << "\nEnter document text:\n";
    getline(cin, document);

    matcher.searchDocument(document);

    matcher.displayMatches();

    matcher.displayFrequencyReport();

    return 0;
}
