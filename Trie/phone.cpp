#include <iostream>
#include <string>
using namespace std;

struct TrieNode {
    TrieNode* children[26];
    bool isEndOfWord;

    TrieNode() {
        isEndOfWord = false;

        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
    }
};

class PhoneDirectory {
private:
    TrieNode* root;

    void displayContacts(TrieNode* node, string& currentContact) {
        if (node == nullptr) {
            return;
        }

        if (node->isEndOfWord) {
            cout << currentContact << endl;
        }

        for (int i = 0; i < 26; i++) {
            if (node->children[i] != nullptr) {
                currentContact += char('a' + i);

                displayContacts(
                    node->children[i],
                    currentContact
                );

                currentContact.pop_back();
            }
        }
    }

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
    PhoneDirectory() {
        root = new TrieNode();
    }

    void insertContact(const string& contact) {
        TrieNode* current = root;

        for (int i = 0; i < contact.length(); i++) {
            int index = contact[i] - 'a';

            if (current->children[index] == nullptr) {
                current->children[index] = new TrieNode();
            }

            current = current->children[index];
        }

        current->isEndOfWord = true;
    }

    void searchContacts(const string& prefix) {
        TrieNode* current = root;

        for (int i = 0; i < prefix.length(); i++) {
            int index = prefix[i] - 'a';

            if (current->children[index] == nullptr) {
                cout << "No contacts found for prefix: "
                     << prefix << endl;
                return;
            }

            current = current->children[index];
        }

        string currentContact = prefix;

        cout << "\nContacts matching '" << prefix << "':\n";

        int previousCount = 0;

        displayContacts(current, currentContact);

        if (!current->isEndOfWord) {
            bool hasContact = false;

            for (int i = 0; i < 26; i++) {
                if (current->children[i] != nullptr) {
                    hasContact = true;
                    break;
                }
            }

            if (!hasContact) {
                cout << "No contacts found.\n";
            }
        }
    }

    ~PhoneDirectory() {
        deleteTrie(root);
    }
};

int main() {
    PhoneDirectory directory;

    int numberOfContacts;

    cout << "Enter number of contacts: ";
    cin >> numberOfContacts;

    if (numberOfContacts < 0) {
        cout << "Invalid number of contacts." << endl;
        return 0;
    }

    cout << "\nEnter contact names (lowercase only):\n";

    for (int i = 0; i < numberOfContacts; i++) {
        string contact;
        cin >> contact;

        bool valid = true;

        for (int j = 0; j < contact.length(); j++) {
            if (contact[j] < 'a' || contact[j] > 'z') {
                valid = false;
                break;
            }
        }

        if (contact.empty() || !valid) {
            cout << "Invalid contact. Use lowercase letters only.\n";
            i--;
            continue;
        }

        directory.insertContact(contact);
    }

    int numberOfSearches;

    cout << "\nEnter number of prefix searches: ";
    cin >> numberOfSearches;

    if (numberOfSearches < 0) {
        cout << "Invalid number of searches." << endl;
        return 0;
    }

    for (int i = 0; i < numberOfSearches; i++) {
        string prefix;

        cout << "\nEnter prefix to search: ";
        cin >> prefix;

        bool valid = true;

        for (int j = 0; j < prefix.length(); j++) {
            if (prefix[j] < 'a' || prefix[j] > 'z') {
                valid = false;
                break;
            }
        }

        if (prefix.empty() || !valid) {
            cout << "Invalid prefix. Use lowercase letters only.\n";
            i--;
            continue;
        }

        directory.searchContacts(prefix);
    }

    return 0;
}
