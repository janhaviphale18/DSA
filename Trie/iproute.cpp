#include <iostream>
#include <string>
#include <cstdint>
#include <limits>
using namespace std;

struct TrieNode
{
    TrieNode* children[2];
    bool hasRoute;
    string nextHop;
    int prefixLength;

    TrieNode()
    {
        children[0] = nullptr;
        children[1] = nullptr;
        hasRoute = false;
        nextHop = "";
        prefixLength = -1;
    }
};

struct RouteResult
{
    bool found;
    string nextHop;
    int prefixLength;
    uint32_t networkAddress;
};

class IPRoutingTrie
{
private:
    TrieNode* root;

    // Parse and validate an IPv4 address.
    bool parseIPv4(const string& ip, uint32_t& result)
    {
        uint32_t value = 0;
        int octetCount = 0;
        int currentOctet = 0;
        int digits = 0;

        for (size_t i = 0; i <= ip.length(); i++)
        {
            if (i == ip.length() || ip[i] == '.')
            {
                if (digits == 0 || currentOctet > 255)
                {
                    return false;
                }

                value = (value << 8) | currentOctet;
                octetCount++;

                if (octetCount > 4)
                {
                    return false;
                }

                currentOctet = 0;
                digits = 0;
            }
            else
            {
                if (ip[i] < '0' || ip[i] > '9')
                {
                    return false;
                }

                currentOctet =
                    currentOctet * 10 + (ip[i] - '0');

                if (currentOctet > 255)
                {
                    return false;
                }

                digits++;
            }
        }

        if (octetCount != 4)
        {
            return false;
        }

        result = value;
        return true;
    }

    // Convert a 32-bit IPv4 integer into dotted notation.
    string formatIPv4(uint32_t ip)
    {
        return to_string((ip >> 24) & 255) + "." +
               to_string((ip >> 16) & 255) + "." +
               to_string((ip >> 8) & 255) + "." +
               to_string(ip & 255);
    }

    // Parse CIDR notation such as 192.168.1.0/24.
    bool parseCIDR(
        const string& cidr,
        uint32_t& network,
        int& prefixLength)
    {
        size_t slashPosition = cidr.find('/');

        if (slashPosition == string::npos ||
            cidr.find('/', slashPosition + 1) != string::npos)
        {
            return false;
        }

        string ipPart = cidr.substr(0, slashPosition);
        string prefixPart = cidr.substr(slashPosition + 1);

        if (prefixPart.empty())
        {
            return false;
        }

        int prefix = 0;

        for (char ch : prefixPart)
        {
            if (ch < '0' || ch > '9')
            {
                return false;
            }

            prefix = prefix * 10 + (ch - '0');

            if (prefix > 32)
            {
                return false;
            }
        }

        uint32_t address;

        if (!parseIPv4(ipPart, address))
        {
            return false;
        }

        uint32_t mask;

        if (prefix == 0)
        {
            mask = 0;
        }
        else
        {
            mask = 0xFFFFFFFFu << (32 - prefix);
        }

        network = address & mask;
        prefixLength = prefix;

        return true;
    }

    // Insert a route into the binary Trie.
    void insertRoute(
        uint32_t network,
        int prefixLength,
        const string& nextHop)
    {
        TrieNode* current = root;

        for (int i = 31; i >= 32 - prefixLength; i--)
        {
            int bit = (network >> i) & 1;

            if (current->children[bit] == nullptr)
            {
                current->children[bit] = new TrieNode();
            }

            current = current->children[bit];
        }

        current->hasRoute = true;
        current->nextHop = nextHop;
        current->prefixLength = prefixLength;
    }

    // Search for the longest matching route.
    RouteResult longestPrefixMatch(uint32_t destination)
    {
        TrieNode* current = root;

        RouteResult bestMatch = {
            false, "", -1, 0
        };

        if (current->hasRoute)
        {
            bestMatch = {
                true,
                current->nextHop,
                current->prefixLength,
                0
            };
        }

        uint32_t matchedNetwork = 0;

        for (int i = 31; i >= 0; i--)
        {
            int bit = (destination >> i) & 1;

            if (current->children[bit] == nullptr)
            {
                break;
            }

            current = current->children[bit];

            if (current->hasRoute)
            {
                int prefix = current->prefixLength;

                uint32_t mask;

                if (prefix == 0)
                {
                    mask = 0;
                }
                else
                {
                    mask = 0xFFFFFFFFu << (32 - prefix);
                }

                matchedNetwork = destination & mask;

                bestMatch = {
                    true,
                    current->nextHop,
                    prefix,
                    matchedNetwork
                };
            }
        }

        return bestMatch;
    }

    // Release all dynamically allocated Trie nodes.
    void deleteTrie(TrieNode* node)
    {
        if (node == nullptr)
        {
            return;
        }

        deleteTrie(node->children[0]);
        deleteTrie(node->children[1]);

        delete node;
    }

public:
    IPRoutingTrie()
    {
        root = new TrieNode();
    }

    ~IPRoutingTrie()
    {
        deleteTrie(root);
    }

    // Validate and insert a route supplied by the user.
    bool addRoute(const string& cidr, const string& nextHop)
    {
        uint32_t network;
        int prefixLength;

        if (!parseCIDR(cidr, network, prefixLength))
        {
            return false;
        }

        insertRoute(network, prefixLength, nextHop);
        return true;
    }

    // Validate a destination and return its best matching route.
    bool lookup(const string& destination, RouteResult& result)
    {
        uint32_t address;

        if (!parseIPv4(destination, address))
        {
            return false;
        }

        result = longestPrefixMatch(address);
        return true;
    }

    // Display the selected route.
    void displayResult(
        const string& destination,
        const RouteResult& result)
    {
        cout << "\nDestination IP: " << destination << "\n";

        if (!result.found)
        {
            cout << "No matching route found.\n";
            return;
        }

        cout << "Longest matching prefix: "
             << formatIPv4(result.networkAddress)
             << "/" << result.prefixLength << "\n";

        cout << "Next hop: " << result.nextHop << "\n";
    }
};

int main()
{
    IPRoutingTrie router;

    int routeCount;

    cout << "Enter number of routes: ";
    cin >> routeCount;

    if (!cin || routeCount < 0)
    {
        cout << "Invalid route count.\n";
        return 1;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < routeCount; i++)
    {
        string cidr;
        string nextHop;

        cout << "\nEnter route " << i + 1
             << " (CIDR format): ";
        getline(cin, cidr);

        cout << "Enter next hop: ";
        getline(cin, nextHop);

        if (nextHop.empty())
        {
            cout << "Next hop cannot be empty. Try again.\n";
            i--;
            continue;
        }

        if (!router.addRoute(cidr, nextHop))
        {
            cout << "Invalid route. Please enter it again.\n";
            i--;
            continue;
        }

        cout << "Route added successfully.\n";
    }

    int destinationCount;

    cout << "\nEnter number of destination IPs to check: ";
    cin >> destinationCount;

    if (!cin || destinationCount < 0)
    {
        cout << "Invalid destination count.\n";
        return 1;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < destinationCount; i++)
    {
        string destination;

        cout << "\nEnter destination IP: ";
        getline(cin, destination);

        RouteResult result;

        if (!router.lookup(destination, result))
        {
            cout << "Invalid IPv4 address. Try again.\n";
            i--;
            continue;
        }

        router.displayResult(destination, result);
    }

    return 0;
}
