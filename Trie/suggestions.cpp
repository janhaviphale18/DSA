#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct TrieNode {
    TrieNode* children[26];
    vector<string> suggestions;

    TrieNode() {
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
    }
};

class SearchSuggestionSystem {
private:
    TrieNode* root;

    void deleteTrie(TrieNode* node) {
        if (node == nullptr) {
            return;
        }

        for (int i = 0; i < 26; i++) {
            deleteTrie(node->children[i]);
        }

        delete node;
    }

public:
    SearchSuggestionSystem() {
        root = new TrieNode();
    }

    void insertProduct(const string& product) {
        TrieNode* current = root;

        for (int i = 0; i < product.length(); i++) {
            int index = product[i] - 'a';

            if (current->children[index] == nullptr) {
                current->children[index] = new TrieNode();
            }

            current = current->children[index];

            if (current->suggestions.size() < 3) {
                current->suggestions.push_back(product);
            }
        }
    }

    void buildTrie(vector<string>& products) {
        sort(products.begin(), products.end());

        for (int i = 0; i < products.size(); i++) {
            insertProduct(products[i]);
        }
    }

    vector<vector<string>> searchSuggestions(
        const string& searchWord
    ) {
        vector<vector<string>> result;

        TrieNode* current = root;
        bool prefixExists = true;

        for (int i = 0; i < searchWord.length(); i++) {
            vector<string> suggestions;

            int index = searchWord[i] - 'a';

            if (prefixExists &&
                current->children[index] != nullptr) {

                current = current->children[index];

                suggestions = current->suggestions;

            } else {
                prefixExists = false;
            }

            result.push_back(suggestions);
        }

        return result;
    }

    ~SearchSuggestionSystem() {
        deleteTrie(root);
    }
};

int main() {
    SearchSuggestionSystem system;

    int numberOfProducts;

    cout << "Enter number of products: ";
    cin >> numberOfProducts;

    if (numberOfProducts < 0) {
        cout << "Invalid number of products." << endl;
        return 0;
    }

    vector<string> products;

    cout << "\nEnter product names (lowercase only):\n";

    for (int i = 0; i < numberOfProducts; i++) {
        string product;
        cin >> product;

        bool valid = !product.empty();

        for (int j = 0; j < product.length(); j++) {
            if (product[j] < 'a' || product[j] > 'z') {
                valid = false;
                break;
            }
        }

        if (!valid) {
            cout << "Invalid product. Use lowercase letters only.\n";
            i--;
            continue;
        }

        products.push_back(product);
    }

    string searchWord;

    cout << "\nEnter search word: ";
    cin >> searchWord;

    bool valid = !searchWord.empty();

    for (int i = 0; i < searchWord.length(); i++) {
        if (searchWord[i] < 'a' || searchWord[i] > 'z') {
            valid = false;
            break;
        }
    }

    if (!valid) {
        cout << "Invalid search word." << endl;
        return 0;
    }

    system.buildTrie(products);

    vector<vector<string>> result =
        system.searchSuggestions(searchWord);

    cout << "\nSearch suggestions:\n";

    for (int i = 0; i < result.size(); i++) {
        cout << "\nPrefix: "
             << searchWord.substr(0, i + 1) << endl;

        if (result[i].empty()) {
            cout << "No suggestions found.\n";
        } else {
            for (int j = 0; j < result[i].size(); j++) {
                cout << result[i][j] << endl;
            }
        }
    }

    return 0;
}
