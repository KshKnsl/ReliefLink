#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iomanip>
#include <ctime>
#include <algorithm>
#include <thread>
#include <stack>
#include <list>
#include <set>
#include <unordered_map>
#include <climits>
#include <cmath>
#include <unistd.h>
#include <stdexcept>

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

class Team {
private:
    int id;
    string skillset;
    string location;
    string status;
public:
    Team(){};
    Team(int id,string skillset,string location, string status){
        this->id=id;
        this->skillset=skillset;
        this->location=location;
        this->status=status;
    }
    friend class RescueTeamManager;
    template <typename T>
    friend class HashTable;
    friend ostream &operator<<(ostream &os, const Team *D);
};
ostream &operator<<(ostream &os, const Team *T)
{
    os << "Team ID: " << T->id<<endl;
    os<< "Skillset: " << T->skillset<<endl;
    os<< "Location: " << T->location<<endl;
    os<< "Status: " << T->status << endl;
    return os;
}



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

    T* Search(int k)
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
    void Display(){
        for(auto k:V){
            cout<<k<<endl;
        }
    }
    void HashToFile(fstream &file){
        for(auto k:V){
            file.write(reinterpret_cast<char *>(k),sizeof(Team));
        }
    }
};

template <typename T>
class BPlusTree
{
private:
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
    void remove(Node *node, int key) {
        if (node->isLeaf) {
            auto it = std::find_if(node->keys.begin(), node->keys.end(),
                                   [key](const T *obj) { return obj->id == key; });
            if (it != node->keys.end()) {
                node->keys.erase(it);
            }
        } 
        else {
            int idx = std::lower_bound(node->keys.begin(), node->keys.end(), key,
                                       [](const T *a, int b) { return a->id < b; }) -
                      node->keys.begin();

            if (idx < node->keys.size() && node->keys[idx]->id == key) {
                if (node->children[idx]->keys.size() >= t) {
                    Node *predNode = node->children[idx];
                    while (!predNode->isLeaf) {
                        predNode = predNode->children.back();
                    }
                    T *pred = predNode->keys.back();
                    node->keys[idx] = pred;
                    remove(node->children[idx], pred->id);
                } 
                else if (node->children[idx + 1]->keys.size() >= t) {
                    Node *succNode = node->children[idx + 1];
                    while (!succNode->isLeaf) {
                        succNode = succNode->children.front();
                    }
                    T *succ = succNode->keys.front();
                    node->keys[idx] = succ;
                    remove(node->children[idx + 1], succ->id);
                } 
                else {
                    merge(node, idx);
                    remove(node->children[idx], key);
                }
            } 
            else {
                if (node->children[idx]->keys.size() < t) {
                    if (idx > 0 && node->children[idx - 1]->keys.size() >= t) {
                        borrowFromPrev(node, idx);
                    } 
                    else if (idx < node->children.size() - 1 && node->children[idx + 1]->keys.size() >= t) {
                        borrowFromNext(node, idx);
                    } 
                    else {
                        if (idx < node->children.size() - 1) {
                            merge(node, idx);
                        } else {
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

    void AddToFile(Node *node, int level, fstream &file)
    {
        if (node != nullptr)
        {
            for (auto key : node->keys)
            {
                file.write(reinterpret_cast<char *>(key), sizeof(Disaster));
            }
            for (Node *child : node->children)
            {
                AddToFile(child, level + 1, file);
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
    void AddToFile()
    {
        fstream file;
        file.open("Disasters.txt", ios::out | ios::binary);
        AddToFile(root, 0, file);
        file.close();
        cout << 2 << endl;
    }
};

// Graph class to represent locations and routes
class Graph
{
private:
    map<string, vector<pair<string, int>>> adjList; // Adjacency list: location -> [(neighbor, weight)]

public:
    // Add a new location (node) to the graph
    void addNode(const string &location)
    {
        if (adjList.find(location) == adjList.end())
        {
            adjList[location] = {};
            cout << "Added location: " + location << endl;
        }
        else
        {
            cout << "Location already exists: " + location << endl;
        }
    }

    // Add a route (edge) between two locations with a distance (weight)
    void addEdge(const string &from, const string &to, int distance)
    {
        adjList[from].push_back({to, distance});
        adjList[to].push_back({from, distance}); // Assuming undirected graph
        cout << "Added edge from " + from + " to " + to + " with distance " + to_string(distance) << endl;
    }

    // Dijkstra's algorithm to find shortest path between two locations
    vector<string> dijkstra(const string &start, const string &end)
    {
        unordered_map<string, int> distances;
        unordered_map<string, string> previous;
        set<pair<int, string>> pq; // Min-heap: (distance, location)

        // Initialize distances to infinity
        for (const auto &node : adjList)
        {
            distances[node.first] = numeric_limits<int>::max();
        }
        distances[start] = 0;
        pq.insert({0, start});

        while (!pq.empty())
        {
            auto currentPair = *pq.begin();
            int currentDist = currentPair.first;
            string current = currentPair.second;
            pq.erase(pq.begin());

            if (current == end)
                break;

            for (const auto &neighbor : adjList[current])
            {
                string next = neighbor.first;
                int weight = neighbor.second;

                if (distances[current] + weight < distances[next])
                {
                    pq.erase({distances[next], next});
                    distances[next] = distances[current] + weight;
                    previous[next] = current;
                    pq.insert({distances[next], next});
                }
            }
        }

        // Reconstruct the shortest path
        vector<string> path;
        for (string at = end; !at.empty(); at = previous[at])
        {
            path.push_back(at);
        }
        reverse(path.begin(), path.end());
        return (path.size() > 1) ? path : vector<string>{};
    }

    // Print graph for debugging
    void printGraph()
    {
        cout << "Graph structure:" << endl;
        for (const auto &node : adjList)
        {
            string output = node.first + " -> ";
            for (const auto &neighbor : node.second)
            {
                output += "(" + neighbor.first + ", " + to_string(neighbor.second) + ") ";
            }
            cout << output << endl;
        }
    }
};

// RoutingSystem class to interact with Graph for path calculations
class RoutingSystem
{
private:
    Graph graph;

public:
    void addLocation(const string &location)
    {
        graph.addNode(location);
    }

    void addRoute(const string &from, const string &to, int distance)
    {
        graph.addEdge(from, to, distance);
    }

    vector<string> calculateOptimalPath(const string &start, const string &end)
    {
        return graph.dijkstra(start, end);
    }

    void updateGraph()
    {
        cout << "Graph updated successfully!" << endl;
    }

    void printGraph()
    {
        graph.printGraph();
    }
};

// RescueTeam class to manage rescue teams
class RescueTeam
{
private:
    string teamID;
    string location;
    int capacity;
    bool availabilityStatus;
    vector<string> skills;
    RoutingSystem *routingSystem; // Pointer to the RoutingSystem object

    struct Disaster
    {
        string disaster_ID;
        int severity;
    };

    // HashMap for location mapping to disasters
    unordered_map<string, Disaster> locationToDisaster;

public:
    RescueTeam(const string &id, const string &loc, int cap, bool status, const vector<string> &skillset, RoutingSystem *rs)
        : teamID(id), location(loc), capacity(cap), availabilityStatus(status), skills(skillset), routingSystem(rs) {}

    // Check for active disaster at a location
    void checkActiveDisaster(const string &loc)
    {
        if (locationToDisaster.find(loc) != locationToDisaster.end())
        {
            cout << "Active disaster at " + loc + ": Disaster ID = " + locationToDisaster[loc].disaster_ID +
                        ", Severity = " + to_string(locationToDisaster[loc].severity)
                 << endl;
        }
        else
        {
            cout << "No active disaster at " + loc << endl;
        }
    }

    // Update location using RoutingSystem's shortest path method
    void updateLocation(const string &targetLocation)
    {
        if (availabilityStatus)
        {
            vector<string> path = routingSystem->calculateOptimalPath(location, targetLocation);
            if (!path.empty())
            {
                cout << "Updating location. Shortest path: ";
                for (size_t i = 0; i < path.size(); ++i)
                {
                    cout << path[i];
                    if (i < path.size() - 1)
                        cout << " -> ";
                }
                cout << endl;
                location = targetLocation; // Update the team's location
            }
            else
            {
                cout << "No valid path to the target location." << endl;
            }
        }
        else
        {
            cout << "Rescue team is not available for relocation." << endl;
        }
    }

    // Check availability based on skills and status
    bool checkAvailability(const vector<string> &requiredSkills)
    {
        if (!availabilityStatus)
        {
            cout << "Rescue team is unavailable." << endl;
            return false;
        }
        for (const string &skill : requiredSkills)
        {
            if (find(skills.begin(), skills.end(), skill) == skills.end())
            {
                cout << "Rescue team lacks required skill: " + skill << endl;
                return false;
            }
        }
        cout << "Rescue team is available and has the required skills." << endl;
        return true;
    }
};

class Alert
{
public:
    int AlertID;
    int DisasterID;
    int Severity;
    string Message;
    string Time;

public:
    Alert(int alertID, int disasterID, int severity, const string &message, const string &time)
        : AlertID(alertID), DisasterID(disasterID), Severity(severity), Message(message), Time(time) {}

    int getAlertID() const { return AlertID; }
    int getDisasterID() const { return DisasterID; }
    int getSeverity() const { return Severity; }
    string getMessage() const { return Message; }
    string getTime() const { return Time; }

    void setSeverity(int severity) { Severity = severity; }
    void setMessage(const string &message) { Message = message; }
    void setTime(const string &time) { Time = time; }

    friend ostream &operator<<(ostream &os, const Alert &alert)
    {
        os << "AlertID: " << alert.AlertID
           << ", DisasterID: " << alert.DisasterID
           << ", Severity: " << alert.Severity
           << ", Message: " << alert.Message
           << ", Time: " << alert.Time;
        return os;
    }

    bool operator<(const Alert &other) const
    {
        return Severity < other.Severity;
    }
};
class AlertManager
{
private:
    priority_queue<Alert> alertQueue;

public:
    void sendAlert(int alertID, int disasterID, int severity, const string &message, const string &time)
    {

        Alert newAlert(alertID, disasterID, severity, message, time);
        alertQueue.push(newAlert);
        cout << "Alert sent successfully for DisasterID " << disasterID << "!" << endl;
    }


    void updateAlert(int disasterID, int severity, const string &message, const string &time)
    {
        vector<Alert> temp;
        bool found = false;

        while (!alertQueue.empty())
        {
            Alert current = alertQueue.top();
            alertQueue.pop();

            if (current.getDisasterID() == disasterID)
            {
                current.setSeverity(severity);
                current.setMessage(message);
                current.setTime(time);
                found = true;
            }

            temp.push_back(current);
        }

        for (const Alert &alert : temp)
        {
            alertQueue.push(alert);
        }

        if (found)
            cout << "Alert updated successfully for DisasterID " << disasterID << "!" << endl;
        else
            cout << "No alert found for DisasterID " << disasterID << endl;
    }

    void displayAlerts() const
    {
        priority_queue<Alert> tempQueue = alertQueue;
        while (!tempQueue.empty())
        {
            cout << tempQueue.top() << endl;
            tempQueue.pop();
        }
    }
    friend class RescueTeamManager;
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
    void insertCsvtoTrie(Trie *trie, const string &filename)
    {
        int i=0;
        ifstream file(filename);
        string allData,line;
        while (i<180 && getline(file, line))
        {
            allData += line;
        }
        trie->insertBulk(allData);
        file.close();
    }
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

struct Shelter {
    string name;
    int capacity;
    int available_space;
    double latitude;
    double longitude;

    Shelter(string n, int cap, int avail, double lat, double lon)
        : name(n), capacity(cap), available_space(avail), latitude(lat), longitude(lon) {}
};

struct KDNode {
    Shelter shelter;
    KDNode* left;
    KDNode* right;

    KDNode(Shelter s) : shelter(s), left(nullptr), right(nullptr) {}
};

class KDTree {
private:
    KDNode* root;
    const string filename = "shelter.txt";

    KDNode* insertRec(KDNode* node, Shelter shelter, unsigned depth) {
        if (!node)
            return new KDNode(shelter);

        unsigned cd = depth % 2;
        if ((cd == 0 && shelter.latitude < node->shelter.latitude) || (cd == 1 && shelter.longitude < node->shelter.longitude))
            node->left = insertRec(node->left, shelter, depth + 1);
        else
            node->right = insertRec(node->right, shelter, depth + 1);

        return node;
    }

    double distance(double lat1, double lon1, double lat2, double lon2) {
        return sqrt(pow(lat1 - lat2, 2) + pow(lon1 - lon2, 2));
    }

    void searchNearestRec(KDNode* node, double lat, double lon, unsigned depth, KDNode*& best, double& bestDist) {
        if (!node)
            return;

        double d = distance(lat, lon, node->shelter.latitude, node->shelter.longitude);
        if (d < bestDist) {
            bestDist = d;
            best = node;
        }

        unsigned cd = depth % 2;
        KDNode* nextBranch = (cd == 0 && lat < node->shelter.latitude) || (cd == 1 && lon < node->shelter.longitude)
            ? node->left
            : node->right;
        KDNode* otherBranch = (nextBranch == node->left) ? node->right : node->left;

        searchNearestRec(nextBranch, lat, lon, depth + 1, best, bestDist);

        if ((cd == 0 && fabs(lat - node->shelter.latitude) < bestDist) ||
            (cd == 1 && fabs(lon - node->shelter.longitude) < bestDist)) {
            searchNearestRec(otherBranch, lat, lon, depth + 1, best, bestDist);
        }
    }

    KDNode* searchRec(KDNode* node, const string& name) {
        if (!node)
            return nullptr;

        if (node->shelter.name == name)
            return node;

        KDNode* leftResult = searchRec(node->left, name);
        if (leftResult)
            return leftResult;

        return searchRec(node->right, name);
    }
     KDNode* findMin(KDNode* node, unsigned d, unsigned depth) {
        if (!node) return nullptr;

        unsigned cd = depth % 2;
        if (cd == d) {
            if (!node->left) return node;
            return findMin(node->left, d, depth + 1);
        }

        KDNode* leftMin = findMin(node->left, d, depth + 1);
        KDNode* rightMin = findMin(node->right, d, depth + 1);

        KDNode* minNode = node;
        if (leftMin && leftMin->shelter.latitude < minNode->shelter.latitude) minNode = leftMin;
        if (rightMin && rightMin->shelter.latitude < minNode->shelter.latitude) minNode = rightMin;

        return minNode;
    }

    KDNode* deleteRec(KDNode* node, const string& name, unsigned depth) {
        if (!node) return nullptr;

        if (node->shelter.name == name) {
            if (!node->right) return node->left;
            if (!node->left) return node->right;

            KDNode* minNode = findMin(node->right, depth % 2, depth + 1);
            node->shelter = minNode->shelter;
            node->right = deleteRec(node->right, minNode->shelter.name, depth + 1);
        } else {
            unsigned cd = depth % 2;
            if ((cd == 0 && name < node->shelter.name) || (cd == 1 && name < node->shelter.name))
                node->left = deleteRec(node->left, name, depth + 1);
            else
                node->right = deleteRec(node->right, name, depth + 1);
        }
        return node;
    }
    void displaySheltersRec(KDNode* node) {
        if (!node)
            return;

        cout << "Shelter Name: " << node->shelter.name
             << ", Capacity: " << node->shelter.capacity
             << ", Available Space: " << node->shelter.available_space
             << ", Location: (" << node->shelter.latitude << ", " << node->shelter.longitude << ")" << endl;

        displaySheltersRec(node->left);
        displaySheltersRec(node->right);
    }
    void saveToFileRec(KDNode* node, ofstream& outfile) {
        if (!node) return;

        outfile << node->shelter.name << ","
                << node->shelter.capacity << ","
                << node->shelter.available_space << ","
                << node->shelter.latitude << ","
                << node->shelter.longitude << endl;

        saveToFileRec(node->left, outfile);
        saveToFileRec(node->right, outfile);
    }

    void loadFromFileRec(ifstream& infile) {
        string line;
        while (getline(infile, line)) {
            stringstream ss(line);
            string name;
            int capacity, available_space;
            double latitude, longitude;

            getline(ss, name, ',');
            ss >> capacity;
            ss.ignore(1);
            ss >> available_space;
            ss.ignore(1);
            ss >> latitude;
            ss.ignore(1);
            ss >> longitude;

            Shelter shelter(name, capacity, available_space, latitude, longitude);
            addShelter(shelter);
        }
    }
public:
    KDTree() : root(nullptr) {
        loadData();
    }

    ~KDTree() {
        saveData();
    }

    void loadData() {
        ifstream infile(filename);
        if (!infile.is_open()) throw runtime_error("Could not open file for loading.");
        loadFromFileRec(infile);
        infile.close();
        
    }

    void saveData() {
       ofstream outfile(filename);
        if (!outfile.is_open()) throw runtime_error("Could not open file for saving.");
        saveToFileRec(root, outfile);
        outfile.close();
    }
  Shelter searchShelterByName(const string &name)
    {
        KDNode *node = searchRec(root, name);
        if (!node)
            throw runtime_error("Shelter not found.");
        return node->shelter;
    }
    
    void addShelter(Shelter shelter) {
        root = insertRec(root, shelter, 0);
    }

    void updateShelter(const string& name, int newCapacity, int newAvailableSpace) {
        KDNode* node = searchRec(root, name);
        if (!node)
            throw runtime_error("Shelter not found.");
        node->shelter.capacity = newCapacity;
        node->shelter.available_space = newAvailableSpace;
        saveData();
    }

    void deleteShelter(const string& name) {
        root = deleteRec(root, name, 0);
        saveData();
    }

    Shelter searchNearestShelter(double lat, double lon) {
        KDNode* best = nullptr;
        double bestDist = numeric_limits<double>::max();
        searchNearestRec(root, lat, lon, 0, best, bestDist);
        if (best)
            return best->shelter;
        throw runtime_error("No shelter found.");
    }

    int getAvailableSpace(const string& name) {
        KDNode* node = searchRec(root, name);
        if (!node)
            throw runtime_error("Shelter not found.");
        return node->shelter.available_space;
    }

    pair<double, double> getLocation(const string& name) {
        KDNode* node = searchRec(root, name);
        if (!node)
            throw runtime_error("Shelter not found.");
        return {node->shelter.latitude, node->shelter.longitude};
    }

    void displayShelters() {
        displaySheltersRec(root);
    }
};
void getAvailableSpaceForShelter(KDTree &tree) {
    string name;
    cout << "Enter the shelter name: ";
    cin >> name;
    int availableSpace = tree.getAvailableSpace(name);
    cout << "Available space for " << name << ": " << availableSpace << endl;
}


void getLocationForShelter(KDTree &tree) {
    string name;
    cout << "Enter the shelter name: ";
    cin >> name;
    auto location = tree.getLocation(name);
    cout << "Location of " << name << ": (" << location.first << ", " << location.second << ")" << endl;
}

void searchNearestShelter(KDTree &tree) {
    double latitude, longitude;
    cout << "Enter latitude: ";
    cin >> latitude;
    cout << "Enter longitude: ";
    cin >> longitude;

    Shelter nearest = tree.searchNearestShelter(latitude, longitude);
    cout << "Nearest shelter: " << nearest.name << endl;
}

void searchShelterByNameFunction(KDTree &tree)
{
    string shelterName;
    cout << "Enter the Shelter Name you want to search for: ";
    getline(cin, shelterName);

    try
    {
        Shelter foundShelter = tree.searchShelterByName(shelterName);
        cout << "Shelter Name: " << foundShelter.name
             << ", Capacity: " << foundShelter.capacity
             << ", Available Space: " << foundShelter.available_space
             << ", Location: (" << foundShelter.latitude << ", " << foundShelter.longitude << ")" << endl;
    }
    catch (const runtime_error &e)
    {
        cout << e.what() << endl;
    }
}

void insertShelter(KDTree& tree) {
    string name;
    int capacity, available_space;
    double latitude, longitude;
cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter Shelter Name: ";
    getline(cin, name);
    cout << "Enter Capacity: ";
    cin >> capacity;
    cout << "Enter Available Space: ";
    cin >> available_space;
    cout << "Enter Latitude: ";
    cin >> latitude;
    cout << "Enter Longitude: ";
    cin >> longitude;
    cin.ignore();  // Ignore newline character after cin

    Shelter shelter(name, capacity, available_space, latitude, longitude);
    tree.addShelter(shelter);
    cout << "Shelter added successfully.\n";
}

void updateShelter(KDTree& tree) {
    string name;
    int newCapacity, newAvailableSpace;

    cout << "Enter Shelter Name to update: ";
    getline(cin, name);
    cout << "Enter New Capacity: ";
    cin >> newCapacity;
    cout << "Enter New Available Space: ";
    cin >> newAvailableSpace;
    cin.ignore();

    try {
        tree.updateShelter(name, newCapacity, newAvailableSpace);
        cout << "Shelter updated successfully.\n";
    }
    catch (const runtime_error& e) {
        cout << e.what() << endl;
    }
}

void deleteShelter(KDTree& tree) {
    string name;

    cout << "Enter Shelter Name to delete: ";
    getline(cin, name);

    try {
        tree.deleteShelter(name);
        cout << "Shelter deleted successfully.\n";
    }
    catch (const runtime_error& e) {
        cout << e.what() << endl;
    }
}

void displayShelters(KDTree& tree) {
    cout << "\nList of Shelters:\n";
    tree.displayShelters();
}


class RescueTeamManager {
private:
    HashTable<Team> *team;
    AlertManager*alert;
//  Helper function to append a single team's data to the file
    void saveTeamToFile(){
        fstream file;
        file.open("RescueTeam.txt",ios::out | ios::binary);
        if (!file) {
            cout << "Error opening file for writing.\n";
            return;
        }

        team->HashToFile(file);
        file.close();
    }

public:
    RescueTeamManager(){
        team=new HashTable<Team>(20);
        alert=new AlertManager;
    }
    // Function to add a new rescue team
    void addRescueTeam(int teamID, const string& skillset, const string& location) {
        Team *T=team->Search(teamID);
            if (T != NULL) {
                cout << "Team with ID " << teamID << " already exists. Cannot add duplicate team.\n";
                return;
            }

        // Add the team to the vector
        Team *newTeam = new Team(teamID, skillset, location, "Active");
        team->Insert(newTeam);
        cout << "Rescue team added successfully.\n";
    }

    void addRescueTeam(Team *R) {
        // Add the team to the vector
        team->Insert(R);
        cout << "Rescue team added successfully.\n";
    }

    // Function to display all rescue teams
    void displayTeams() const {
        cout << "\nRescue Teams:\n";
        team->Display();
    }

    // Function to delete a rescue team
    void deleteRescueTeam(int teamID) {
        Team * T=team->Search(teamID);
            if (T!=NULL) {
                if (T->status == "Removed") {
                    cout << "Team with ID " << teamID << " is already removed.\n";
                    return;
                }
                T->status = "Removed";
                cout << "Rescue team with ID " << teamID << " has been removed.\n";
                return;
            }
        cout << "No team found with ID " << teamID << ".\n";
    }

    // Function to update a rescue team's details
    void updateRescueTeam(int teamID, const string& newSkillset, const string& newLocation) {
        Team * T=team->Search(teamID);
            if (T!=NULL) {
                if (T->status == "Removed") {
                    cout << "Team with ID " << teamID << " is already removed.\n";
                    return;
                }
                T->skillset = newSkillset;
                T->location = newLocation;
                cout << "Rescue team with ID " << teamID << " has been updated.\n";
                return;
            }
        cout << "No team found with ID " << teamID << ".\n";
    }
    void DisplayAlert(){
        alert->displayAlerts();
            }
    friend class DisasterManagementSystem;
};



class DisasterManagementSystem
{
private:
    BPlusTree<Disaster> *disasters;
    RescueTeamManager * Rescue;
    map<string, City> cities;
    map<int, Equipment> equipment;
    priority_queue<pair<int, int>> alertQueue; // Disaster severity queue
    RoutingSystem routingSystem;
    Trie trie;

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
        cout << "3. Request Help (Citizen)" << endl;
        cout << "4. Exit" << endl;
    }
    void showAdminMenu()
    {
        KDTree tree;
        animatePrint("adminMenu.txt");
        while(true){
        cout << "\nAdmin Menu:" << endl;
        cout << "1. Display Requests" << endl;
        cout << "2. Add Disaster" << endl;
        cout << "3. Update Disaster" << endl;
        cout << "4. Delete Disaster" << endl;
        cout << "5. Display Disaster" << endl;
        cout << "6. Add Rescue Team" << endl;
        cout << "7. Update Rescue Team" << endl;
        cout << "8. Delete Rescue Team" << endl;
        cout << "9. Add Relief Camp" << endl;
        cout << "10. Update Relief Camp" << endl;
        cout << "11. Delete Relief Camp" << endl;
        cout << "12. Search Relief Camp" << endl;
        cout << "13. Display All Relief Camps" << endl;
        cout << "14. Logout" << endl;
        int adminChoice;
        cin >> adminChoice;
        switch (adminChoice)
        {
        case 1:
        displayRequests();
        break;
        case 2:
            addDisaster();
            break;
        case 3:
            updateDisaster();
            break;
        case 4:
            // disasters->remove(1);
            break;
        case 5:
            disasters->printTree();
            break;
        case 6:
            addRescueTeam();
            break;
        case 7:
            updateRescueTeam();
            break;
        case 8:
            deleteRescueTeam();
            break;
        case 9:
            insertShelter(tree);
            break;
        case 10:
            updateShelter(tree);
            break;
        case 11:
            deleteShelter(tree);
            break;
        case 12:
            searchShelterByNameFunction(tree);
            break;
        case 13:
            displayShelters(tree);
            break;
        case 14:
            isLoggedIn = 0;
            break;
        default:
            cout << RED << "Invalid choice, please try again." << RESET << endl;
        }
        if(isLoggedIn==0){
            break;
        }
        }
    }
    void addRescueTeam(){
        int id;
        string skillset,location;
        cout<<"Enter the Rescue Team ID: ";
        cin>>id;
        cout<<"Enter the Rescue Team skillset: ";
        cin>>skillset;
        cout<<"Location under Rescue Team: ";
        cin>>location;
        Rescue->addRescueTeam(id,skillset,location);
    }
    void updateRescueTeam(){
        int id;
        string skillset,location;
        cout<<"Enter the Rescue Team ID: ";
        cin>>id;
        cout<<"Enter the Rescue Team New Skillset: ";
        cin>>skillset;
        cout<<"New Location under Rescue Team: ";
        cin>>location;
        Rescue->updateRescueTeam(id,skillset,location);
    }
    void deleteRescueTeam(){
        int id;
        string skillset,location;
        cout<<"Enter the Rescue Team ID to be deleted: ";
        cin>>id;
        Rescue->deleteRescueTeam(id);
    }
    void displayRequests()
    {
        // read the file request.txt completely
        ifstream file;
        cout<<"Requests:"<<endl;
        file.open("request.txt");
        string line;
        while (getline(file, line))
        {
            cout << line << endl;
        }
    }
    void showRescueTeamMenu()
    {
        animatePrint("rescueMenu.txt");
        cout << "\nRescue Team Menu:" << endl;
        cout << "1. View Active Disasters" << endl;
        cout << "2. Priority wise Alert Calls" << endl;
        cout << "3. Logout" << endl;
        int rescueTeamChoice;

        cin >> rescueTeamChoice;
        switch (rescueTeamChoice)
        {
        case 1:
            viewActiveDisasters();
            break;
        case 2:
            respondToAlertCalls();
            break;
        case 3:
            isLoggedIn = 0;
            break;
        default:
            cout << RED << "Invalid choice, please try again." << RESET << endl;
        }
    }
    void showCitizenMenu()
    {
        animatePrint("Help.txt");
        cout << "\nCitizen Help Menu:" << endl;
        cout << "1. Request Help" << endl;
        cout << "2. Exit" << endl;
        int citizenChoice;
        cin >> citizenChoice;
        switch (citizenChoice)
        {
        case 1:
            requestHelp();
            break;
        case 2:
            break;
        default:
            cout << RED << "Invalid choice, please try again." << RESET << endl;
        }
    }
    void addDisaster()
    {
        string type, status, date, address, city, state;
        double lat, lon;
        int severity, affected_population;

        cout << "Enter Disaster Type: ";
        cin >> type;
        cout << "Enter Status: ";
                cin.ignore();
        cin >> status;
        cout << "Enter Date (YYYY-MM-DD): ";
                cin.ignore();
        cin >> date;
        cout << "Enter Location (latitude longitude): ";
        cin >> lat >> lon;
        cout << "Enter Address: ";
        cin.ignore();
        getline(cin, address);
        cout << "Enter City: ";
        cin.ignore();
        getline(cin, city);
        cout << "Enter State: ";
                cin.ignore();
        getline(cin, state);
        cout << "Enter Severity (1-5): ";
        cin >> severity;
        cout << "Enter Affected Population: ";
        cin >> affected_population;

        Location loc(lat, lon, address, city, state);
        Disaster *d = new Disaster(currentDisasterId++, type, loc, severity, status, date, affected_population, {}, {});
        disasters->insert(d);
        cout << GREEN << "Disaster added successfully!" << RESET << endl;
    }
    void updateDisaster()
    {
        int id;
        cout << "Enter Disaster ID: ";
        cin >> id;
        Disaster *d = disasters->search(id);
        if (d == nullptr)
        {
            cout << RED << "Disaster not found." << RESET << endl;
            return;
        }
        cout << "Enter new Status: ";
        cin >> d->status;
        cout << "Enter new Severity: ";
        cin >> d->severity;
        cout << GREEN << "Disaster updated successfully!" << RESET << endl;
    }
    void viewActiveDisasters()
    {
        cout << "\nActive Disasters:" << endl;
        disasters->printTree();
    }
    void respondToAlertCalls()
    {
        if (alertQueue.empty())
        {
            cout << "No active alerts." << endl;
            return;
        }
        pair<int, int> alert = alertQueue.top();
        alertQueue.pop();
        cout << "Responding to alert call for Disaster ID: " << alert.second << endl;
    }
    void requestHelp()
    {
        trie.insertCsvtoTrie(&trie, "noida_city_graph.csv");
        string location;
        cout << "Enter your location: ";
        getline(cin,location);
        getline(cin,location);
        vector<string> suggestions = trie.autocomplete(location);
        if (suggestions.empty())
        {
            cout << "No suggestions found for your location." << endl;
            return;
        }
        cout << "Did you mean:" << endl;
        int sugg=1;
        for (const string &suggestion : suggestions)
        {
            cout << sugg++ <<"."<< suggestion << endl;
        }
        cout << "Enter the correct location no: ";
        int op;
        cin >> op;
        location = suggestions[op-1];
        cout<< "Enter Disaster Type: ";
        string type;
        cin >> type;
        cout << "Enter Disaster Severity: ";
        int severity;
        cin >> severity;
        cout << "Enter Contact Number: ";
        string contact;
        cin >> contact;
        ofstream file;
        file.open("request.txt", ios::app);
        file << "Location: " << location << ", Disaster Type: " << type << ", Severity: " << severity << ", Contact No."<< contact<<endl;
        file.close();
cout << "Help requested successfully!" << endl;
        cout<< "Will reach you out soon!!"<<endl;
        vector<string> path = routingSystem.calculateOptimalPath(location, "Relief Camp");
        if (!path.empty())
        {
            cout << "Help is on the way! Shortest path: ";
            for (size_t i = 0; i < path.size(); ++i)
            {
                cout << path[i];
                if (i < path.size() - 1)
                    cout << " -> ";
            }
            cout << endl;
        }
        // showMenu();
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
        if (Rescue->team->Search(teamId)==NULL)
        {
            cout << RED << "Invalid team ID." << RESET << endl;
            return;
        }

        find->assignedTeams.push_back(teamId);
        cout << GREEN << "Team assigned successfully!" << RESET << endl;
    }

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
    }

public:
    DisasterManagementSystem() : currentDisasterId(0), currentTeamId(1), currentShelterId(1), currentEquipmentId(1), isLoggedIn(false)
    {
        Rescue=new RescueTeamManager;
        disasters = new BPlusTree<Disaster>(5);
        loadUsers();
        loadRescueUsers();
    }
    void run()
    {
        fstream file;
        file.open("Disasters.txt",ios::in | ios::binary);
        Disaster *D=new Disaster;
        while(file.read(reinterpret_cast<char *>(D),sizeof(Disaster))){
            // cout<<&*D;
            disasters->insert(D);
            currentDisasterId=max(currentDisasterId,D->id);
        }
        currentDisasterId++;
        file.close();
        file.open("RescueTeam.txt",ios::in | ios::binary);
        Team *R=new Team;
        while(file.read(reinterpret_cast<char *>(R),sizeof(Team))){
            Rescue->addRescueTeam(R);
        }
        file.close();
        while (true)
        {
            if (isLoggedIn == 0)
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
                        showAdminMenu();
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
                        showRescueTeamMenu();
                    }
                    else
                    {
                        cout << RED << "Invalid credentials. Try again." << RESET << endl;
                    }
                }
                else if (choice == 3)
                {
                    showCitizenMenu();
                }
                else if (choice == 4)
                {
                    break;
                }
                else
                {
                    cout << RED << "Invalid choice, please try again." << RESET << endl;
                }
            }
        }
        disasters->AddToFile();
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
    // animatePrint("Logo.txt");
    // animatePrint("Welcome.txt");
    KDTree tree; 
    DisasterManagementSystem dms;
    dms.run();
    animatePrint("Thanks.txt");
    return 0;
}
