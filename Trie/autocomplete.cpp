#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

struct TrieNode {
    TrieNode* children[27];
    map<string, int> sentences;

    TrieNode() {
        for (int i = 0; i < 27; i++) {
            children[i] = nullptr;
        }
    }
};

class AutocompleteSystem {
private:
    TrieNode* root;
    string currentInput;

    int getIndex(char ch) {
        if (ch == ' ') {
            return 26;
        }

        return ch - 'a';
    }

    void insertSentence(const string& sentence, int frequency) {
        TrieNode* current = root;

        for (int i = 0; i < sentence.length(); i++) {
            int index = getIndex(sentence[i]);

            if (current->children[index] == nullptr) {
                current->children[index] = new TrieNode();
            }

            current = current->children[index];

            current->sentences[sentence] += frequency;
        }
    }

    TrieNode* findPrefixNode(const string& prefix) {
        TrieNode* current = root;

        for (int i = 0; i < prefix.length(); i++) {
            int index = getIndex(prefix[i]);

            if (current->children[index] == nullptr) {
                return nullptr;
            }

            current = current->children[index];
        }

        return current;
    }

    vector<string> getSuggestions(const string& prefix) {
        TrieNode* node = findPrefixNode(prefix);

        if (node == nullptr) {
            return {};
        }

        vector<pair<string, int>> candidates;

        for (const auto& entry : node->sentences) {
            candidates.push_back(entry);
        }

        sort(candidates.begin(), candidates.end(),
            [](const pair<string, int>& a,
               const pair<string, int>& b) {

                if (a.second != b.second) {
                    return a.second > b.second;
                }

                return a.first < b.first;
            }
        );

        vector<string> suggestions;

        int limit = min(3, (int)candidates.size());

        for (int i = 0; i < limit; i++) {
            suggestions.push_back(candidates[i].first);
        }

        return suggestions;
    }

    void deleteTrie(TrieNode* node) {
        if (node == nullptr) {
            return;
        }

        for (int i = 0; i < 27; i++) {
            deleteTrie(node->children[i]);
        }

        delete node;
    }

public:
    AutocompleteSystem(
        vector<string>& sentences,
        vector<int>& times
    ) {
        root = new TrieNode();
        currentInput = "";

        for (int i = 0; i < sentences.size(); i++) {
            insertSentence(sentences[i], times[i]);
        }
    }

    vector<string> input(char ch) {
        if (ch == '#') {
            insertSentence(currentInput, 1);

            currentInput = "";

            return {};
        }

        if (ch != ' ' && (ch < 'a' || ch > 'z')) {
            return {};
        }

        currentInput += ch;

        return getSuggestions(currentInput);
    }

    ~AutocompleteSystem() {
        deleteTrie(root);
    }
};

int main() {
    int numberOfSentences;

    cout << "Enter number of initial sentences: ";
    cin >> numberOfSentences;

    if (numberOfSentences < 0) {
        cout << "Invalid number of sentences." << endl;
        return 0;
    }

    vector<string> sentences;
    vector<int> times;

    cout << "\nEnter sentences and their frequencies:\n";

    for (int i = 0; i < numberOfSentences; i++) {
        string sentence;
        int frequency;

        cin >> ws;
        getline(cin, sentence);

        cin >> frequency;

        bool valid = !sentence.empty() && frequency > 0;

        for (int j = 0; j < sentence.length(); j++) {
            char ch = sentence[j];

            if (ch != ' ' && (ch < 'a' || ch > 'z')) {
                valid = false;
                break;
            }
        }

        if (!valid) {
            cout << "Invalid sentence or frequency. Try again.\n";
            i--;
            continue;
        }

        sentences.push_back(sentence);
        times.push_back(frequency);
    }

    AutocompleteSystem system(sentences, times);

    cout << "\nAutocomplete system started.\n";
    cout << "Enter characters one by one.\n";
    cout << "Enter # to finish a sentence.\n";
    cout << "Enter ! to exit.\n";

    char ch;

    while (true) {
        cout << "\nEnter character: ";
        cin >> ch;

        if (ch == '!') {
            break;
        }

        vector<string> suggestions = system.input(ch);

        cout << "\nSuggestions:\n";

        if (suggestions.empty()) {
            cout << "No suggestions found.\n";
        } else {
            for (int i = 0; i < suggestions.size(); i++) {
                cout << i + 1 << ". "
                     << suggestions[i] << endl;
            }
        }
    }

    cout << "\nAutocomplete system closed." << endl;

    return 0;
}
