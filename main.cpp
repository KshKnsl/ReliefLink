#include <bits/stdc++.h>
#include <unistd.h>

using namespace std;

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
void changeColor()
{
    cout << "\033[2J\033[1;1H";
    const string colors[] = {"01", "02", "03", "04", "05", "06", "07", "08", "09", "0A", "0B", "0C", "0D", "0E", "0F", "10", "12", "13", "14", "15", "16", "17", "18", "19", "1A", "1B", "1C", "1D", "1E", "1F", "20", "21", "23", "24", "25", "26", "27", "28", "29", "2A", "2B", "2C", "2D", "2E", "2F", "30", "31", "32", "34", "35", "36", "37", "38", "39", "3A", "3B", "3C", "3D", "3E", "3F", "40", "41", "42", "43", "45", "46", "47", "48", "49", "4A", "4B", "4C", "4D", "4E", "4F", "50", "51", "52", "53", "54", "56", "57", "58", "59", "5A", "5B", "5C", "5D", "5E", "5F", "60", "61", "62", "63", "64", "65", "67", "68", "69", "6A", "6B", "6C", "6D", "6E", "6F", "70", "71", "72", "73", "74", "75", "76", "78", "79", "7A", "7B", "7C", "7D", "7E", "7F", "80", "81", "82", "83", "84", "85", "86", "87", "89", "8A", "8B", "8C", "8D", "8E", "8F"};
    srand((int)time(0));
    int randomIndex = rand() % (sizeof(colors) / sizeof(colors[0]));
    system(("color " + colors[randomIndex]).c_str());
}
void animatePrint(const string &filename)
{
    changeColor();
    ifstream file(filename);
    string line;
    vector<string> lines;
    while (getline(file, line))
        lines.push_back(line);
    size_t maxLength = 0;
    for (const auto &l : lines)
        maxLength = max(maxLength, l.length());
    for (size_t i = 0; i < maxLength; ++i)
    {
        cout << "\033[2J\033[1;1H";
        for (size_t j = 0; j < lines.size(); ++j)
        {
            if (i < lines[j].length())
                cout << lines[j].substr(0, i + 1);
            else
                cout << lines[j].substr(0, lines[j].length());
            cout << endl;
        }
        cout << endl;
        nanosleep((const struct timespec[]){{0, 25000000L}}, nullptr);
    }
    sleep(1);
    file.close();
}

struct Equipment
{
    int id;
    string name;
    string type;
    bool isAvailable;
    string currentLocation;
    int condition;
};

struct Hospital
{
    int id;
    string name;
    string location;
    int totalBeds;
    int availableBeds;
    bool hasEmergencyUnit;
    vector<string> specializations;
};

struct City
{
    string name;
    string state;
    double latitude;
    double longitude;
    int population;
    vector<Hospital> hospitals;
    vector<Equipment> equipment;
    int fireStations;
    int policeStations;
    int emergencyVehicles;
};

class Location
{
private:
    double latitude;
    double longitude;
    string address;
    string city;
    string state;

public:
    // Default Constructor
    Location() : latitude(0.0), longitude(0.0), address(""), city(""), state("") {}

    // Parameterized Constructor
    Location(double latitude, double longitude, const string &address, const string &city, const string &state)
        : latitude(latitude), longitude(longitude), address(address), city(city), state(state) {}

    // Copy Constructor
    Location(const Location &other)
        : latitude(other.latitude), longitude(other.longitude), address(other.address), city(other.city), state(other.state) {}

    // Overloaded Assignment Operator
    Location &operator=(const Location &other)
    {
        if (this != &other)
        {
            latitude = other.latitude;
            longitude = other.longitude;
            address = other.address;
            city = other.city;
            state = other.state;
        }
        return *this;
    }
    friend class Disaster;
    template <typename T>
    friend class BPlusTree;
    friend class DisasterManagementSystem;
    friend ostream &operator<<(ostream &os, const Location &loc);
};
ostream &operator<<(ostream &os, const Location &loc)
{
    os << loc.address << ", " << loc.city << ", " << loc.state << " (" << loc.latitude << ", " << loc.longitude << ")";
    return os;
}

class Disaster
{
private:
    int id;
    string type;
    Location location;
    int severity;
    string status;
    string date;
    int affectedPopulation;
    vector<int> assignedTeams;
    vector<string> requiredResources;

public:
    // Constructor for convenience
    Disaster() {}
    Disaster(int id, const string &type, const Location &location, int severity,
             const string &status, const string &date, int affectedPopulation,
             const vector<int> &assignedTeams, const vector<string> &requiredResources)
        : id(id), type(type), location(location), severity(severity),
          status(status), date(date), affectedPopulation(affectedPopulation),
          assignedTeams(assignedTeams), requiredResources(requiredResources) {}

    // Comparison operator for ordering (based on id as an example)
    bool operator<(const Disaster &other) const
    {
        return id < other.id;
    }

    bool operator==(const Disaster &other) const
    {
        return id == other.id;
    }
    template <typename T>
    friend class BPlusTree;
    friend class DisasterManagementSystem;
    template <typename T>
    friend class HashTable;
    friend ostream &operator<<(ostream &os, const Disaster *D);
};
ostream &operator<<(ostream &os, const Disaster *D)
{
    os << "ID: " << D->id << endl;
    os << "Type: " << D->type << endl;
    os << "Status: " << D->status << endl;
    os << "Severity: " << D->severity << endl;
    os << "Date Of Disaster: " << D->date << endl;
    os << "Affected Population: " << D->affectedPopulation << endl;
    os << "Location: " << D->location << endl;
    os << "Assigned Rescue Teams: ";
    for (auto k : D->assignedTeams)
    {
        os << k << " ";
    }
    return os;
}
struct RescueTeam
{
    int id;
    string name;
    Location currentLocation;
    bool isAvailable;
    string specialization;
    int memberCount;
    vector<int> equippedWith;
};

struct Shelter
{
    int id;
    string name;
    Location location;
    int capacity;
    int currentOccupancy;
    bool hasFirstAid;
    bool hasFood;
    bool hasPower;
    vector<string> facilities;
};

template <typename T>
class HashTable
{
    vector<T *> V;
    int size;
    int total;

public:
    HashTable(int s)
    {
        V.resize(s, NULL);
        size = s;
        total = 0;
    }
    int Hash(int k, int i = 0)
    {
        return (k + i) % size;
    }
    float Load()
    {
        return (1.0 * total) / size;
    }
    void Insert(T *D)
    {
        int pos = Hash(D->id);
        int i = 1;
        while (V[pos] != NULL)
        {
            pos = Hash(D->id, i);
            i++;
        }
        V[pos] = D;
        total++;
        if (Load() > 0.7)
        {
            IncreaseSize(size * 2);
        }
    }
    void IncreaseSize(int newSize)
    {
        vector<T *> oldTable = V;
        size = newSize;
        V.clear();
        V.resize(size, nullptr);
        total = 0;
        for (T *d : oldTable)
        {
            if (d != nullptr)
            {
                Insert(d);
            }
        }
    }

    Disaster *Search(int k)
    {
        int pos = Hash(k);
        int i = 1;
        while (V[pos] != NULL)
        {
            if (V[pos]->id == k)
                break;
            pos = Hash(k, i);
            i++;
        }
        return V[pos];
    }

    void Delete(int k)
    {
        int pos = Hash(k);
        int i = 1;
        while (V[pos] != NULL)
        {
            if (V[pos]->id == k)
            {
                V[pos] = NULL;
                total--;
                return;
            }
            pos = Hash(k, i);
            i++;
        }
    }
};

template <typename T>
class BPlusTree
{
public:
    class Node
    {
    private:
        bool isLeaf;
        vector<T *> keys;
        vector<Node *> children;
        Node *next;

    public:
        // Constructor
        Node(bool leaf = false) : isLeaf(leaf), next(nullptr) {}
        friend class BPlusTree<T>;
    };

    Node *root;
    int t;
    void splitChild(Node *parent, int index, Node *child)
    {
        Node *newChild = new Node(child->isLeaf);
        parent->children.insert(parent->children.begin() + index + 1, newChild);
        parent->keys.insert(parent->keys.begin() + index, child->keys[t - 1]);

        newChild->keys.assign(child->keys.begin() + t, child->keys.end());
        child->keys.resize(t - 1);

        if (!child->isLeaf)
        {
            newChild->children.assign(child->children.begin() + t, child->children.end());
            child->children.resize(t);
        }

        if (child->isLeaf)
        {
            newChild->next = child->next;
            child->next = newChild;
        }
    }

    // Implementation of insertNonFull function
    void insertNonFull(Node *node, T *key)
    {
        if (node->isLeaf)
        {
            node->keys.insert(upper_bound(node->keys.begin(), node->keys.end(), key, [](const T *a, const T *b)
                                          { return a->id < b->id; }),
                              key);
        }
        else
        {
            int i = node->keys.size() - 1;
            while (i >= 0 && key->id < node->keys[i]->id)
            {
                i--;
            }
            i++;
            if ((int)node->children[i]->keys.size() == 2 * t - 1)
            {
                splitChild(node, i, node->children[i]);
                if (key->id > node->keys[i]->id)
                {
                    i++;
                }
            }
            insertNonFull(node->children[i], key);
        }
    }

    // Implementation of remove function
    void remove(Node *node, int key)
    {
        // If node is a leaf
        if (node->isLeaf)
        {
            auto it = find(node->keys.begin(), node->keys.end(), key);
            if (it != node->keys.end())
            {
                node->keys.erase(it);
            }
        }
        else
        {
            int idx = lower_bound(node->keys.begin(), node->keys.end(), key) - node->keys.begin();
            if (idx < node->keys.size() && node->keys[idx] == key)
            {
                if (node->children[idx]->keys.size() >= t)
                {
                    Node *predNode = node->children[idx];
                    while (!predNode->isLeaf)
                    {
                        predNode = predNode->children.back();
                    }
                    T pred = predNode->keys.back();
                    node->keys[idx] = pred;
                    remove(node->children[idx], pred);
                }
                else if (node->children[idx + 1]->keys.size() >= t)
                {
                    Node *succNode = node->children[idx + 1];
                    while (!succNode->isLeaf)
                    {
                        succNode = succNode->children.front();
                    }
                    T succ = succNode->keys.front();
                    node->keys[idx] = succ;
                    remove(node->children[idx + 1], succ);
                }
                else
                {
                    merge(node, idx);
                    remove(node->children[idx], key);
                }
            }
            else
            {
                if (node->children[idx]->keys.size() < t)
                {
                    if (idx > 0 && node->children[idx - 1]->keys.size() >= t)
                    {
                        borrowFromPrev(node, idx);
                    }
                    else if (idx < node->children.size() - 1 && node->children[idx + 1]->keys.size() >= t)
                    {
                        borrowFromNext(node, idx);
                    }
                    else
                    {
                        if (idx < node->children.size() - 1)
                        {
                            merge(node, idx);
                        }
                        else
                        {
                            merge(node, idx - 1);
                        }
                    }
                }
                remove(node->children[idx], key);
            }
        }
    }

    // Implementation of borrowFromPrev function
    void borrowFromPrev(Node *node, int index)
    {
        Node *child = node->children[index];
        Node *sibling = node->children[index - 1];

        child->keys.insert(child->keys.begin(), node->keys[index - 1]);
        node->keys[index - 1] = sibling->keys.back();
        sibling->keys.pop_back();

        if (!child->isLeaf)
        {
            child->children.insert(child->children.begin(), sibling->children.back());
            sibling->children.pop_back();
        }
    }

    // Implementation of borrowFromNext function
    void borrowFromNext(Node *node, int index)
    {
        Node *child = node->children[index];
        Node *sibling = node->children[index + 1];

        child->keys.push_back(node->keys[index]);
        node->keys[index] = sibling->keys.front();
        sibling->keys.erase(sibling->keys.begin());

        if (!child->isLeaf)
        {
            child->children.push_back(sibling->children.front());
            sibling->children.erase(sibling->children.begin());
        }
    }

    // Implementation of merge function
    void merge(Node *node, int index)
    {
        Node *child = node->children[index];
        Node *sibling = node->children[index + 1];

        child->keys.push_back(node->keys[index]);
        child->keys.insert(child->keys.end(), sibling->keys.begin(), sibling->keys.end());
        if (!child->isLeaf)
        {
            child->children.insert(child->children.end(), sibling->children.begin(), sibling->children.end());
        }

        node->keys.erase(node->keys.begin() + index);
        node->children.erase(node->children.begin() + index + 1);

        delete sibling;
    }

    // Implementation of printTree function
    void printTree(Node *node, int level)
    {
        if (node != nullptr)
        {
            for (const T *key : node->keys)
            {
                cout << &*key << " ";
            }
            for (Node *child : node->children)
            {
                printTree(child, level + 1);
            }
        }
    }
    void AddDisasterToHash(HashTable<T> *H, Node *node, int level)
    {
        if (node != nullptr)
        {
            for (const T *key : node->keys)
            {
                if (key->status == "Active")
                {
                    H->Insert(key);
                }
            }
            for (Node *child : node->children)
            {
                AddDisasterToHash(H, child, level + 1);
            }
        }
    }

public:
    BPlusTree(int degree) : root(nullptr), t(degree) {}
    // Implementation of printTree wrapper function
    void printTree()
    {
        printTree(root, 0);
    }

    // Implementation of search function
    T *search(int key)
    {
        Node *current = root;
        while (current != nullptr)
        {
            int i = 0;
            while (i < current->keys.size() && key > current->keys[i]->id)
            {
                i++;
            }
            if (i < current->keys.size() && key == current->keys[i]->id)
            {
                return current->keys[i];
            }
            if (current->isLeaf)
            {
                return NULL;
            }
            current = current->children[i];
        }
        return NULL;
    }

    // Implementation of insert function
    void insert(T *key)
    {
        if (root == nullptr)
        {
            root = new Node(true);
            root->keys.push_back(key);
        }
        else
        {
            if ((int)root->keys.size() == 2 * t - 1)
            {
                Node *newRoot = new Node();
                newRoot->children.push_back(root);
                splitChild(newRoot, 0, root);
                root = newRoot;
            }
            insertNonFull(root, key);
        }
    }

    // Implementation of remove function
    void remove(int key)
    {
        if (root == nullptr)
        {
            return;
        }
        remove(root, key);
        if (root->keys.empty() && !root->isLeaf)
        {
            Node *tmp = root;
            root = root->children[0];
            delete tmp;
        }
    }

    void AddActiveDisaster(HashTable<T> *H)
    {
        AddDisasterToHash(H, root, 0);
    }
};

// class Graph {
// private:
//     unordered_map<string, vector<pair<string, int>>> adj; // Node -> [(Neighbor, Weight)]
// public:
//     void addNode(const string& node) {
//         if (adj.find(node) == adj.end()) adj[node] = {};
//     }

//     void addEdge(const string& from, const string& to, int weight) {
//         adj[from].push_back({to, weight});
//         adj[to].push_back({from, weight}); // For undirected graph
//     }

//     // Shortest Path: Basic Dijkstra
//     vector<string> dijkstra(const string& start, const string& end) {
//         unordered_map<string, int> dist;
//         unordered_map<string, string> parent;
//         for (auto& [node, _] : adj) dist[node] = numeric_limits<int>::max();
//         dist[start] = 0;

//         priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> pq;
//         pq.push({0, start});

//         while (!pq.empty()) {
//             auto [d, current] = pq.top();
//             pq.pop();
//             if (current == end) break;

//             for (auto& [neighbor, weight] : adj[current]) {
//                 if (dist[current] + weight < dist[neighbor]) {
//                     dist[neighbor] = dist[current] + weight;
//                     pq.push({dist[neighbor], neighbor});
//                     parent[neighbor] = current;
//                 }
//             }
//         }

//         vector<string> path;
//         for (string at = end; at != start; at = parent[at]) {
//             path.push_back(at);
//             if (parent.find(at) == parent.end()) return {}; // No path found
//         }
//         path.push_back(start);
//         reverse(path.begin(), path.end());
//         return path;
//     }

//     // Optimal Path: Considering route easibility
//     vector<string> optimalPath(const string& start, const string& end, int maxWeight) {
//         unordered_map<string, int> dist;
//         unordered_map<string, string> parent;
//         for (auto& [node, _] : adj) dist[node] = numeric_limits<int>::max();
//         dist[start] = 0;

//         priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> pq;
//         pq.push({0, start});

//         while (!pq.empty()) {
//             auto [d, current] = pq.top();
//             pq.pop();
//             if (current == end) break;

//             for (auto& [neighbor, weight] : adj[current]) {
//                 if (weight > maxWeight) continue; // Skip edges that don't satisfy easibility
//                 if (dist[current] + weight < dist[neighbor]) {
//                     dist[neighbor] = dist[current] + weight;
//                     pq.push({dist[neighbor], neighbor});
//                     parent[neighbor] = current;
//                 }
//             }
//         }

//         vector<string> path;
//         for (string at = end; at != start; at = parent[at]) {
//             path.push_back(at);
//             if (parent.find(at) == parent.end()) return {}; // No path found
//         }
//         path.push_back(start);
//         reverse(path.begin(), path.end());
//         return path;
//     }
// };

// class RoutingSystem {
// private:
//     Graph graph;
// public:
//     void updateGraph(const string& from, const string& to, int weight) {
//         graph.addNode(from);
//         graph.addNode(to);
//         graph.addEdge(from, to, weight);
//     }

//     void shortestPath(const string& start, const string& end) {
//         vector<string> path = graph.dijkstra(start, end);
//         if (path.empty()) {
//             cout << "No path found between " << start << " and " << end << endl;
//         } else {
//             cout << "Shortest path from " << start << " to " << end << ": ";
//             for (const string& node : path) cout << node << " ";
//             cout << endl;
//         }
//     }

//     void calculateOptimalPath(const string& start, const string& end, int maxWeight) {
//         vector<string> path = graph.optimalPath(start, end, maxWeight);
//         if (path.empty()) {
//             cout << "No optimal path found between " << start << " and " << end << " under max weight " << maxWeight << endl;
//         } else {
//             cout << "Optimal path (max weight " << maxWeight << ") from " << start << " to " << end << ": ";
//             for (const string& node : path) cout << node << " ";
//             cout << endl;
//         }
//     }
// };

class DisasterManagementSystem
{
private:
    BPlusTree<Disaster> *disasters;
    map<int, RescueTeam> rescueTeams;
    map<int, Shelter> shelters;
    map<string, City> cities;
    map<int, Equipment> equipment;
    priority_queue<pair<int, int>> alertQueue; // Disaster severity queue

    int currentDisasterId;
    int currentTeamId;
    int currentShelterId;
    int currentEquipmentId;

    int isLoggedIn; // 0: Not logged in, 1: Admin, 2: Rescue Team
    string currentUser;
    map<string, string> users;
    map<string, string> RescueUsers;

    void loadUsers()
    {
        ifstream file("users.txt");
        string username, password;
        while (getline(file, username))
        {
            getline(file, password);
            users[username] = password;
        }
        file.close();
    }
    void loadRescueUsers()
    {
        ifstream file("rescueUsers.txt");
        string username, password;
        while (getline(file, username))
        {
            getline(file, password);
            RescueUsers[username] = password;
        }
        file.close();
    }
    void showMenu()
    {
        cout << "\nWelcome to Relief Link! How can we help you?" << endl;
        cout << "1. Login as Admin" << endl;
        cout << "2. Login as Rescue Team" << endl;
        cout << "3. Report Disaster" << endl;
        cout << "4. Request Help (Citizen)" << endl;
        cout << "5. Exit" << endl;
    }
    void adminMenu()
    {
        changeColor();
        while (true)
        {
            cout << "\nAdmin Menu:" << endl;
            cout << "1. Report Disaster" << endl;
            cout << "2. View All Disasters" << endl;
            cout << "3. View and Assign Teams to Disasters" << endl;
            cout << "4. View and Assign Equipment to Teams" << endl;
            cout << "5. View Hospitals and Shelters" << endl;
            cout << "6. Logout OR Exit" << endl;
            int choice;
            cin >> choice;

            if (choice == 1)
            {
                reportDisaster();
            }
            else if (choice == 2)
            {
                viewAllDisasters();
            }
            else if (choice == 3)
            {
                assignTeams();
            }
            else if (choice == 4)
            {
                
            }
            else if (choice == 5)
            {
                viewHospitalsAndShelters();
            }
            else if (choice == 6)
            {
                isLoggedIn = 0;
                currentUser = "";
                cout << GREEN << "Logged out successfully!" << RESET << endl;
                sleep(2);
                changeColor();
                break;
            }
            else
            {
                cout << RED << "Invalid choice, please try again." << RESET << endl;
            }
        }
    }

    void reportDisaster()
    {
        string disasterType, status, date;
        double latitude, longitude;
        int severity, affectedPopulation;
        string address, city, state;

        cout << "Enter disaster type: ";
        cin >> disasterType;
        cout << "Enter status (e.g., ongoing, resolved): ";
        cin >> status;
        cout << "Enter date (YYYY-MM-DD): ";
        cin >> date;
        cout << "Enter latitude and longitude of disaster: ";
        cin >> latitude >> longitude;
        cout << "Enter Address: ";
        cin >> address;
        cout << "Enter City: ";
        cin >> city;
        cout << "Enter State: ";
        cin >> state;
        cout << "Enter severity (1 to 5): ";
        cin >> severity;
        cout << "Enter affected population: ";
        cin >> affectedPopulation;

        Location loc(latitude, longitude, address, city, state);
        Disaster *D = new Disaster(currentDisasterId++, disasterType, loc, severity, status, date, affectedPopulation, {}, {});
        disasters->insert(D);
        cout << GREEN << "Disaster reported successfully!" << RESET << endl;
    }

    void viewAllDisasters()
    {
        cout << "Disasters Reported:" << endl;
        disasters->printTree();
    }

    void UpdateStatus()
    {
        if (disasters == NULL)
        {
            cout << RED << "No disasters to assign teams to." << RESET << endl;
            return;
        }

        int disasterId;
        cout << "Enter Disaster ID to Update Severity: ";
        cin >> disasterId;
        Disaster *find = disasters->search(disasterId);
        if (find == NULL)
        {
            cout << RED << "Invalid disaster ID." << RESET << endl;
            return;
        }

        string status;
        cout << "Enter Updated Status: ";
        cin >> status;
        find->status = status;
        cout << GREEN << "Status Updated Successfully!" << RESET << endl;
    }

    void UpdateSeverity()
    {
        if (disasters == NULL)
        {
            cout << RED << "No disasters to assign teams to." << RESET << endl;
            return;
        }
        int disasterId;
        cout << "Enter Disaster ID to Update Severity: ";
        cin >> disasterId;
        Disaster *find = disasters->search(disasterId);
        if (find == NULL)
        {
            cout << RED << "Invalid disaster ID." << RESET << endl;
            return;
        }

        int severity;
        cout << "Enter Updated Severity: ";
        cin >> severity;
        find->severity = severity;
        cout << GREEN << "Status Updated Successfully!" << RESET << endl;
    }

    void UpdateLocation(int Did, Location L)
    {
        if (disasters == NULL)
        {
            cout << RED << "No disasters to assign teams to." << RESET << endl;
            return;
        }
        int disasterId;
        cout << "Enter Disaster ID to Update Severity: ";
        cin >> disasterId;
        Disaster *find = disasters->search(disasterId);
        if (find == NULL)
        {
            cout << RED << "Invalid disaster ID." << RESET << endl;
            return;
        }
        double latitude, longitude;
        string address, city, state;
        cout << "Enter latitude and longitude of disaster: ";
        cin >> latitude >> longitude;
        cout << "Enter Address: ";
        cin >> address;
        cout << "Enter City: ";
        cin >> city;
        cout << "Enter State: ";
        cin >> state;
        Location loc(latitude, longitude, address, city, state);
        find->location = loc;
        cout << GREEN << "Status Updated Successfully!" << RESET << endl;
    }

    void assignTeams()
    {
        if (disasters == NULL)
        {
            cout << RED << "No disasters to assign teams to." << RESET << endl;
            return;
        }

        int disasterId;
        cout << "Enter disaster ID to assign teams: ";
        cin >> disasterId;
        Disaster *find = disasters->search(disasterId);
        if (find == NULL)
        {
            cout << RED << "Invalid disaster ID." << RESET << endl;
            return;
        }

        int teamId;
        cout << "Enter team ID to assign: ";
        cin >> teamId;
        // Will change according to rescue team
        if (rescueTeams.find(teamId) == rescueTeams.end())
        {
            cout << RED << "Invalid team ID." << RESET << endl;
            return;
        }

        find->assignedTeams.push_back(teamId);
        cout << GREEN << "Team assigned successfully!" << RESET << endl;
    }

    //    void assignEquipment()
    //    {
    //        if (disasters.empty())
    //        {
    //            cout << RED << "No disasters to assign equipment to." << RESET << endl;
    //            return;
    //        }
    //
    //        int disasterId;
    //        cout << "Enter disaster ID to assign equipment: ";
    //        cin >> disasterId;
    //
    //        if (disasters.find(disasterId) == disasters.end())
    //        {
    //            cout << RED << "Invalid disaster ID." << RESET << endl;
    //            return;
    //        }
    //
    //        int equipmentId;
    //        cout << "Enter equipment ID to assign: ";
    //        cin >> equipmentId;
    //
    //        if (equipment.find(equipmentId) == equipment.end())
    //        {
    //            cout << RED << "Invalid equipment ID." << RESET << endl;
    //            return;
    //        }
    //
    //        disasters[disasterId].requiredResources.push_back(equipment[equipmentId].name);
    //        cout << GREEN << "Equipment assigned successfully!" << RESET << endl;
    //    }

    void viewHospitalsAndShelters()
    {
        cout << "\nHospitals and Shelters Overview:" << endl;
        cout << "Hospitals:" << endl;
        for (auto &city : cities)
        {
            for (auto &hospital : city.second.hospitals)
            {
                cout << "ID: " << hospital.id << ", Name: " << hospital.name
                     << ", Location: " << hospital.location << ", Available Beds: " << hospital.availableBeds << endl;
            }
        }

        cout << "\nShelters:" << endl;
        for (auto &shelter : shelters)
        {
            cout << "ID: " << shelter.second.id << ", Name: " << shelter.second.name
                 << ", Location: " << shelter.second.location << ", Current Occupancy: " << shelter.second.currentOccupancy << endl;
        }
    }

    //    void citizenRequest()
    //    {
    //        int disasterId;
    //        cout << "Enter disaster ID to request help: ";
    //        cin >> disasterId;
    //
    //        if (disasters.find(disasterId) == disasters.end())
    //        {
    //            cout << RED << "Invalid disaster ID." << RESET << endl;
    //            return;
    //        }
    //
    //        cout << GREEN << "Request submitted successfully! Help is on the way!" << RESET << endl;
    //    }

public:
    DisasterManagementSystem() : currentDisasterId(1), currentTeamId(1), currentShelterId(1), currentEquipmentId(1), isLoggedIn(false)
    {
        disasters = new BPlusTree<Disaster>(5);
        loadUsers();
        loadRescueUsers();
    }
    void run()
    {
        while (true)
        {
            showMenu();
            int choice;
            cin >> choice;

            if (choice == 1)
            {
                // Admin login
                string username, password;
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;

                if (users.find(username) != users.end() && users[username] == password)
                {
                    isLoggedIn = 1;
                    currentUser = username;
                    cout << GREEN << "Login successful!" << RESET << endl;
                    sleep(2);
                    adminMenu();
                }
                else
                {
                    cout << RED << "Invalid credentials. Try again." << RESET << endl;
                }
            }
            else if (choice == 2)
            {
                // Rescue Team login
                string username, password;
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;

                if (RescueUsers.find(username) != RescueUsers.end() && RescueUsers[username] == password)
                {
                    isLoggedIn = 2;
                    currentUser = username;
                    cout << GREEN << "Login successful!" << RESET << endl;
                    sleep(2);
                }
                else
                {
                    cout << RED << "Invalid credentials. Try again." << RESET << endl;
                }
            }
            else if (choice == 3)
            {
                // Report Disaster (for admin)
                if (!isLoggedIn)
                {
                    cout << RED << "You must be logged in as an admin to report a disaster." << RESET << endl;
                    continue;
                }
                reportDisaster();
            }
            else if (choice == 4)
            {
                // Citizen Request (no login required)
                //                citizenRequest();
            }
            else if (choice == 5)
            {
                return;
            }
            else
            {
                cout << RED << "Invalid choice, please try again." << RESET << endl;
            }
        }
    }
};

class Alert
{
private:
    int AlertID;
    int DisasterID;
    int Severity;
    string Message;
    string Time;

public:
    Alert(int alertID, int disasterID, int severity, string message, string time)
    {
        AlertID = alertID;
        DisasterID = disasterID;
        Severity = severity;
        Message = message;
        Time = time;
    }

    int getSeverity() const { return Severity; }
    string getMessage() const { return Message; }
    string getTime() const { return Time; }
    int getAlertID() const { return AlertID; }

    friend ostream &operator<<(ostream &os, const Alert &alert)
    {
        os << "AlertID: " << alert.AlertID
           << ", DisasterID: " << alert.DisasterID
           << ", Severity: " << alert.Severity
           << ", Message: " << alert.Message
           << ", Time: " << alert.Time;
        return os;
    }
};

class MaxHeap
{
private:
    vector<Alert> heap;

    int parent(int index) { return (index - 1) / 2; }
    int leftChild(int index) { return 2 * index + 1; }
    int rightChild(int index) { return 2 * index + 2; }

    void heapifyUp(int index)
    {
        while (index != 0 && heap[parent(index)].getSeverity() < heap[index].getSeverity())
        {
            swap(heap[index], heap[parent(index)]);
            index = parent(index);
        }
    }

    void heapifyDown(int index)
    {
        int largest = index;
        int left = leftChild(index);
        int right = rightChild(index);

        if (left < heap.size() && heap[left].getSeverity() > heap[largest].getSeverity())
            largest = left;

        if (right < heap.size() && heap[right].getSeverity() > heap[largest].getSeverity())
            largest = right;

        if (largest != index)
        {
            swap(heap[index], heap[largest]);
            heapifyDown(largest);
        }
    }

public:
    void insert(const Alert &alert)
    {
        heap.push_back(alert);
        heapifyUp((int)heap.size() - 1);
    }

    Alert extractMax()
    {
        if (heap.empty())
            throw runtime_error("Heap is empty!");

        Alert maxAlert = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
        return maxAlert;
    }

    Alert getMax() const
    {
        if (heap.empty())
            throw runtime_error("Heap is empty!");
        return heap[0];
    }

    bool isEmpty() const
    {
        return heap.empty();
    }

    void displayHeap() const
    {
        for (const Alert &alert : heap)
        {
            cout << alert << endl;
        }
    }
};

class TrieNode
{
public:
    unordered_map<char, TrieNode *> children;
    bool isEndOfWord;
    int id;
    TrieNode() : isEndOfWord(false) {}
};
class Trie
{
private:
    TrieNode *root;
    void dfsHelper(TrieNode *node, string prefix, vector<string> &results)
    {
        if (node->isEndOfWord)
            results.push_back(prefix);

        for (auto &pair : node->children)
        {
            prefix.push_back(pair.first);
            dfsHelper(pair.second, prefix, results);
            prefix.pop_back();
        }
    }

public:
    Trie() : root(new TrieNode()) {}
    void insert(string word)
    {
        TrieNode *current = root;
        for (char c : word)
        {
            if (current->children.find(c) == current->children.end())
                current->children[c] = new TrieNode();
            current = current->children[c];
        }
        current->isEndOfWord = true;
    }
    bool search(string word)
    {
        TrieNode *node = findNode(word);
        return node != NULL && node->isEndOfWord;
    }
    bool startsWith(string prefix)
    {
        return findNode(prefix) != NULL;
    }
    vector<string> autocomplete(string prefix)
    {
        vector<string> results;
        TrieNode *node = findNode(prefix);
        if (node)
        {
            string current = prefix;
            dfsHelper(node, current, results);
        }
        return results;
    }

    void insertBulk(string data)
    {
        int start = 0, end = 0;
        while ((end = (int)data.find(',', start)) != string::npos)
        {
            insert(data.substr(start, end - start));
            start = end + 1;
        }
        if (start < data.length())
        {
            insert(data.substr(start));
        }
    }

private:
    TrieNode *findNode(string prefix)
    {
        TrieNode *current = root;
        for (char c : prefix)
        {
            if (current->children.find(c) == current->children.end())
            {
                return NULL;
            }
            current = current->children[c];
        }
        return current;
    }
};

struct Point
{
    double x;
    double y;
    string shelter_name;

    Point(double _x, double _y, string _shelter_name)
        : x(_x), y(_y), shelter_name(_shelter_name) {}
};

struct KDNode
{
    Point point;
    KDNode *left;
    KDNode *right;

    KDNode(Point p) : point(p), left(nullptr), right(nullptr) {}
};

class KDTree
{
private:
    KDNode *root;

    KDNode *insertRec(KDNode *node, Point point, unsigned depth)
    {
        if (!node)
            return new KDNode(point);

        unsigned cd = depth % 2;

        if (cd == 0)
        {
            if (point.x < node->point.x)
                node->left = insertRec(node->left, point, depth + 1);
            else
                node->right = insertRec(node->right, point, depth + 1);
        }
        else
        {
            if (point.y < node->point.y)
                node->left = insertRec(node->left, point, depth + 1);
            else
                node->right = insertRec(node->right, point, depth + 1);
        }

        return node;
    }

    void nearestNeighbor(KDNode *node, Point target, unsigned depth, KDNode *&best, double &bestDist)
    {
        if (!node)
            return;

        double dist = distance(node->point, target);

        if (dist < bestDist)
        {
            best = node;
            bestDist = dist;
        }

        unsigned cd = depth % 2;
        KDNode *primary = (cd == 0 ? (target.x < node->point.x ? node->left : node->right)
                                   : (target.y < node->point.y ? node->left : node->right));
        KDNode *secondary = (primary == node->left ? node->right : node->left);

        nearestNeighbor(primary, target, depth + 1, best, bestDist);

        double splitDist = (cd == 0 ? fabs(target.x - node->point.x) : fabs(target.y - node->point.y));
        if (splitDist < bestDist)
        {
            nearestNeighbor(secondary, target, depth + 1, best, bestDist);
        }
    }

    double distance(Point a, Point b)
    {
        return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    }

public:
    KDTree() : root(nullptr) {}

    void insert(Point point)
    {
        root = insertRec(root, point, 0);
    }

    string findNearest(Point target)
    {
        KDNode *best = nullptr;
        double bestDist = numeric_limits<double>::max();

        nearestNeighbor(root, target, 0, best, bestDist);

        if (best)
            return best->point.shelter_name;
        return "No shelters found";
    }
};

int main()
{
    //     Trie trie;
    //     trie.insertBulk("New York,Los Angeles,Chicago,Houston,Phoenix,Philadelphia,San Antonio,San Diego,Dallas,San Jose");
    //     cout << "Search 'Chicago': " << (trie.search("Chicago") ? "Found" : "Not Found") << endl;
    //     cout << "Search 'Miami': " << (trie.search("Miami") ? "Found" : "Not Found") << endl;
    //     cout << "Starts with 'San': " << (trie.startsWith("San") ? "Yes" : "No") << endl;
    //     cout << "Starts with 'Bos': " << (trie.startsWith("Bos") ? "Yes" : "No") << endl;
    //     cout << "Autocomplete 'San':" << endl;
    //     vector<string> results = trie.autocomplete("San");
    //     for (string &result : results)
    //     {
    //         cout << "  " << result << endl;
    //     }

    // MaxHeap alertHeap;

    // alertHeap.insert(Alert(1, 101, 5, "chicago", "2024-11-16 10:00"));
    // alertHeap.insert(Alert(2, 102, 8, "Miami", "2024-11-16 10:30"));
    // alertHeap.insert(Alert(3, 103, 4, "Boston", "2024-11-16 11:00"));
    // alertHeap.insert(Alert(4, 104, 10, "San diego", "2024-11-16 12:00"));

    // cout << "Alerts in Max-Heap:" << endl;
    // alertHeap.displayHeap();
    // cout << endl;

    // cout << "Processing Alerts by Priority:" << endl;
    // while (!alertHeap.isEmpty())
    // {
    //     Alert alert = alertHeap.extractMax();
    //     cout << "Processing: " << alert << endl;
    // }
    animatePrint("Logo.txt");
    animatePrint("Welcome.txt");
    DisasterManagementSystem dms;
    dms.run();
    animatePrint("Thanks.txt");
    return 0;
}
