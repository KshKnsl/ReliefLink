#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <conio.h>
#include <iomanip>
#include <ctime>
#include <algorithm>
#include <thread>
#include <stack>
#include <list>
#include <set>
#include <unordered_map>
#include <climits>

using namespace std;

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"

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


class Location {
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
    Location(double latitude, double longitude, const string& address, const string& city, const string& state)
        : latitude(latitude), longitude(longitude), address(address), city(city), state(state) {}

    // Copy Constructor
    Location(const Location& other)
        : latitude(other.latitude), longitude(other.longitude), address(other.address), city(other.city), state(other.state) {}
    
    // Overloaded Assignment Operator
    Location& operator=(const Location& other) {
        if (this != &other) {
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
};

class Disaster {
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
    Disaster(int id, const string& type, const Location& location, int severity,
             const string& status, const string& date, int affectedPopulation,
             const vector<int>& assignedTeams, const vector<string>& requiredResources)
        : id(id), type(type), location(location), severity(severity),
          status(status), date(date), affectedPopulation(affectedPopulation),
          assignedTeams(assignedTeams), requiredResources(requiredResources) {}

    // Comparison operator for ordering (based on id as an example)
    bool operator<(const Disaster& other) const {
        return id < other.id;
    }

    bool operator==(const Disaster& other) const {
        return id == other.id;
    }
    template <typename T>
    friend class BPlusTree;
};

ostream &operator<<(ostream &os, Location &loc)
{
    os << loc.address << ", " << loc.city << ", " << loc.state << " (" << loc.latitude << ", " << loc.longitude << ")";
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

struct Graph
{
    map<string, vector<pair<string, double>>> adjList;

    void addEdge(string &src, string &dest, double weight)
    {
        adjList[src].push_back(make_pair(dest, weight));
        adjList[dest].push_back(make_pair(src, weight));
    }

    void dijkstra(string &start)
    {
        map<string, double> dist;
        for (auto &node : adjList)
        {
            dist[node.first] = INT_MAX;
        }
        dist[start] = 0;

        priority_queue<pair<double, string>, vector<pair<double, string>>, greater<pair<double, string>>> pq;
        pq.push(make_pair(0, start));

        while (!pq.empty())
        {
            string u = pq.top().second;
            pq.pop();

            for (auto &neighbor : adjList[u])
            {
                string v = neighbor.first;
                double weight = neighbor.second;

                if (dist[u] + weight < dist[v])
                {
                    dist[v] = dist[u] + weight;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }

        cout << CYAN << "Shortest paths from " << start << ":" << RESET << endl;
        for (auto &d : dist)
        {
            cout << d.first << ": " << d.second << endl;
        }
    }

    void displayGraph()
    {
        for (auto &node : adjList)
        {
            cout << node.first << ": ";
            for (auto &neighbor : node.second)
            {
                cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
            }
            cout << endl;
        }
    }
};

class FileManager
{
private:
    string citiesFile = "cities.txt";
    string disastersFile = "disasters.txt";
    string teamsFile = "teams.txt";
    string sheltersFile = "shelters.txt";
    string usersFile = "users.txt";

public:
    void createDummyData()
    {
        createDummyCities();
        createDummyEquipment();
        createDummyHospitals();
        createDummyTeams();
        createDummyShelters();
    }

private:
    void createDummyCities()
    {
        ofstream file("cities.txt");
        vector<pair<string, string>> cities = {
            {"New York", "NY"}, {"Los Angeles", "CA"}, {"Chicago", "IL"}, {"Houston", "TX"}, {"Phoenix", "AZ"}, {"Philadelphia", "PA"}, {"San Antonio", "TX"}, {"San Diego", "CA"}, {"Dallas", "TX"}, {"San Jose", "CA"}};

        for (auto &city : cities)
        {
            file << city.first << "|" << city.second << "|"
                 << (30.0 + (rand() % 20)) << "|"
                 << (-120.0 + (rand() % 50)) << "|"
                 << (100000 + (rand() % 900000)) << "|"
                 << (2 + (rand() % 5)) << "|"
                 << (2 + (rand() % 5)) << "|"
                 << (5 + (rand() % 20)) << "\n";
        }
        file.close();
    }

    void createDummyEquipment()
    {
        ofstream file("equipment.txt");
        vector<pair<string, string>> equipment = {
            {"Fire Truck", "firefighting"},
            {"Ambulance", "medical"},
            {"Rescue Helicopter", "aerial"},
            {"Water Pump", "firefighting"},
            {"Generator", "power"},
            {"Bulldozer", "construction"},
            {"Medical Supply Kit", "medical"},
            {"Search Drone", "surveillance"},
            {"Emergency Boat", "water_rescue"},
            {"Mobile Command Center", "command"}};

        int id = 1;
        for (auto &eq : equipment)
        {
            file << id++ << "|" << eq.first << "|" << eq.second << "|"
                 << "1|"
                 << "Central Station|"
                 << (7 + (rand() % 4)) << "\n";
        }
        file.close();
    }

    void createDummyHospitals()
    {
        ofstream file("hospitals.txt");
        vector<string> hospitalNames = {
            "General Hospital", "Memorial Hospital", "Community Medical Center",
            "University Hospital", "Regional Medical Center", "Emergency Care Center",
            "St. Mary's Hospital", "City Medical Center", "County Hospital",
            "Medical Center"};

        vector<string> specializations = {
            "Emergency", "Trauma", "Burns", "Cardiac", "Pediatric",
            "Orthopedic", "Neurological", "Respiratory", "General Surgery"};

        int id = 1;
        for (auto &name : hospitalNames)
        {
            file << id++ << "|" << name << "|"
                 << "City Location|"
                 << (100 + (rand() % 400)) << "|"
                 << (20 + (rand() % 100)) << "|"
                 << "1|";

            int specCount = 2 + (rand() % 3);
            for (int i = 0; i < specCount; i++)
            {
                if (i > 0)
                    file << ",";
                file << specializations[rand() % specializations.size()];
            }
            file << "\n";
        }
        file.close();
    }

    void createDummyTeams()
    {
        ofstream file("teams.txt");
        vector<string> teamNames = {
            "Rescue Squad A", "Medical Unit B", "Fire Brigade C",
            "Search Team D", "Water Rescue E", "Helicopter Support F"};

        vector<string> specializations = {
            "Firefighting", "Medical", "Aerial Support", "Water Rescue",
            "Construction", "Surveillance"};

        int id = 1;
        for (auto &name : teamNames)
        {
            file << id++ << "|" << name << "|"
                 << "Random Location|"
                 << "1|"
                 << specializations[rand() % specializations.size()] << "|"
                 << (3 + (rand() % 8)) << "\n";
        }
        file.close();
    }

    void createDummyShelters()
    {
        ofstream file("shelters.txt");
        vector<string> shelterNames = {
            "Community Center", "High School Gym", "City Park Shelter",
            "Convention Center", "Stadium", "Local Church"};

        int id = 1;
        for (auto &name : shelterNames)
        {
            file << id++ << "|" << name << "|"
                 << "Random Address|"
                 << (50 + (rand() % 150)) << "|"
                 << (10 + (rand() % 50)) << "|"
                 << "1|" << "1|" << "1|\n";
        }
        file.close();
    }
};


template <typename T> class BPlusTree{
public:
    class Node {
    private:
        bool isLeaf;
        vector<T> keys;
        vector<Node*> children;
        Node* next;

    public:
        // Constructor
        Node(bool leaf = false) : isLeaf(leaf), next(nullptr) {}
        friend class BPlusTree<T>;
    };
    
    Node* root;
    int t;
    void splitChild(Node* parent, int index, Node* child);
    void insertNonFull(Node* node, T key);
    void remove(Node* node, T key);
    void borrowFromPrev(Node* node, int index);
    void borrowFromNext(Node* node, int index);
    void merge(Node* node, int index);
    void printTree(Node* node, int level);
    
public:
    BPlusTree(int degree): root(nullptr), t(degree){}
    
    void insert(T key);
    bool search(T key);
    void remove(T key);
    void printTree();
};

template <typename T>
void BPlusTree<T>::splitChild(Node* parent, int index,Node* child){
    Node* newChild = new Node(child->isLeaf);
    parent->children.insert(parent->children.begin() + index + 1, newChild);
    parent->keys.insert(parent->keys.begin() + index,child->keys[t - 1]);
    
    newChild->keys.assign(child->keys.begin() + t,child->keys.end());
    child->keys.resize(t - 1);
    
    if (!child->isLeaf) {
        newChild->children.assign(child->children.begin()+ t,child->children.end());
        child->children.resize(t);
    }
    
    if (child->isLeaf) {
        newChild->next = child->next;
        child->next = newChild;
    }
}

// Implementation of insertNonFull function
template <typename T>
void BPlusTree<T>::insertNonFull(Node* node, T key)
{
    if (node->isLeaf) {
        node->keys.insert(upper_bound(node->keys.begin(),node->keys.end(),key),key);
    }
    else {
        int i = node->keys.size() - 1;
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        i++;
        if (node->children[i]->keys.size() == 2 * t - 1) {
            splitChild(node, i, node->children[i]);
            if (key > node->keys[i]) {
                i++;
            }
        }
        insertNonFull(node->children[i], key);
    }
}

// Implementation of remove function
template <typename T>
void BPlusTree<T>::remove(Node* node, T key)
{
    // If node is a leaf
    if (node->isLeaf) {
        auto it = find(node->keys.begin(), node->keys.end(),key);
        if (it != node->keys.end()) {
            node->keys.erase(it);
        }
    }
    else {
        int idx = lower_bound(node->keys.begin(),node->keys.end(), key)- node->keys.begin();
        if (idx < node->keys.size()
            && node->keys[idx] == key) {
            if (node->children[idx]->keys.size() >= t) {
                Node* predNode = node->children[idx];
                while (!predNode->isLeaf) {
                    predNode = predNode->children.back();
                }
                T pred = predNode->keys.back();
                node->keys[idx] = pred;
                remove(node->children[idx], pred);
            }
            else if (node->children[idx + 1]->keys.size()>= t) {
                Node* succNode = node->children[idx + 1];
                while (!succNode->isLeaf) {
                    succNode = succNode->children.front();
                }
                T succ = succNode->keys.front();
                node->keys[idx] = succ;
                remove(node->children[idx + 1], succ);
            }
            else {
                merge(node, idx);
                remove(node->children[idx], key);
            }
        }
        else {
            if (node->children[idx]->keys.size() < t) {
                if (idx > 0&& node->children[idx - 1]->keys.size()>= t) {
                    borrowFromPrev(node, idx);
                }
                else if (idx < node->children.size() - 1&& node->children[idx + 1]->keys.size()>= t) {
                    borrowFromNext(node, idx);
                }
                else {
                    if (idx < node->children.size() - 1) {
                        merge(node, idx);
                    }
                    else {
                        merge(node, idx - 1);
                    }
                }
            }
            remove(node->children[idx], key);
        }
    }
}

// Implementation of borrowFromPrev function
template <typename T>
void BPlusTree<T>::borrowFromPrev(Node* node, int index)
{
    Node* child = node->children[index];
    Node* sibling = node->children[index - 1];
    
    child->keys.insert(child->keys.begin(),node->keys[index - 1]);
    node->keys[index - 1] = sibling->keys.back();
    sibling->keys.pop_back();
    
    if (!child->isLeaf) {
        child->children.insert(child->children.begin(),sibling->children.back());
        sibling->children.pop_back();
    }
}

// Implementation of borrowFromNext function
template <typename T>
void BPlusTree<T>::borrowFromNext(Node* node, int index)
{
    Node* child = node->children[index];
    Node* sibling = node->children[index + 1];
    
    child->keys.push_back(node->keys[index]);
    node->keys[index] = sibling->keys.front();
    sibling->keys.erase(sibling->keys.begin());
    
    if (!child->isLeaf) {
        child->children.push_back(sibling->children.front());
        sibling->children.erase(sibling->children.begin());
    }
}

// Implementation of merge function
template <typename T>
void BPlusTree<T>::merge(Node* node, int index)
{
    Node* child = node->children[index];
    Node* sibling = node->children[index + 1];
    
    child->keys.push_back(node->keys[index]);
    child->keys.insert(child->keys.end(),sibling->keys.begin(),sibling->keys.end());
    if (!child->isLeaf) {
        child->children.insert(child->children.end(),sibling->children.begin(),sibling->children.end());
    }
    
    node->keys.erase(node->keys.begin() + index);
    node->children.erase(node->children.begin() + index+ 1);
    
    delete sibling;
}

// Implementation of printTree function
template <typename T>
void BPlusTree<T>::printTree(Node* node, int level)
{
    if (node != nullptr) {
        for (const T& key : node->keys) {
            cout << key << " ";
        }
        for (Node* child : node->children) {
            printTree(child, level + 1);
        }
    }
}

// Implementation of printTree wrapper function
template <typename T> void BPlusTree<T>::printTree()
{
    printTree(root, 0);
}

// Implementation of search function
template <typename T> bool BPlusTree<T>::search(T key)
{
    Node* current = root;
    while (current != nullptr) {
        int i = 0;
        while (i < current->keys.size()&& key > current->keys[i]) {
            i++;
        }
        if (i < current->keys.size()&& key == current->keys[i]) {
            return true;
        }
        if (current->isLeaf) {
            return false;
        }
        current = current->children[i];
    }
    return false;
}

// Implementation of insert function
template <typename T> void BPlusTree<T>::insert(T key)
{
    if (root == nullptr) {
        root = new Node(true);
        root->keys.push_back(key);
    }
    else {
        if (root->keys.size() == 2 * t - 1) {
            Node* newRoot = new Node();
            newRoot->children.push_back(root);
            splitChild(newRoot, 0, root);
            root = newRoot;
        }
        insertNonFull(root, key);
    }
}

// Implementation of remove function
template <typename T> void BPlusTree<T>::remove(T key)
{
    if (root == nullptr) {
        return;
    }
    remove(root, key);
    if (root->keys.empty() && !root->isLeaf) {
        Node* tmp = root;
        root = root->children[0];
        delete tmp;
    }
}

class DisasterManagementSystem
{
private:
    map<int, Disaster> disasters;
    map<int, RescueTeam> rescueTeams;
    map<int, Shelter> shelters;
    map<string, City> cities;
    map<int, Equipment> equipment;
    priority_queue<pair<int, int>> alertQueue; // Disaster severity queue

    int currentDisasterId;
    int currentTeamId;
    int currentShelterId;
    int currentEquipmentId;

    bool isLoggedIn;
    string currentUser;
    map<string, string> users;

    void loadAllData()
    {
        loadUsers();
        loadCities();
        loadEquipment();
    }

    void saveAllData()
    {
        saveUsers();
        saveCities();
        saveEquipment();
    }

    void loadUsers()
    {
        ifstream file("users.txt");
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string username, password;
            getline(ss, username, '|');
            getline(ss, password);
            users[username] = password;
        }
        file.close();
    }

    void saveUsers()
    {
        ofstream file("users.txt");
        for (auto &user : users)
        {
            file << user.first << "|" << user.second << "\n";
        }
        file.close();
    }

    void loadCities()
    {
        ifstream file("cities.txt");
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            City city;
            string temp;

            getline(ss, city.name, '|');
            getline(ss, city.state, '|');
            getline(ss, temp, '|');
            city.latitude = stod(temp);
            getline(ss, temp, '|');
            city.longitude = stod(temp);
            getline(ss, temp, '|');
            city.population = stoi(temp);
            getline(ss, temp, '|');
            city.fireStations = stoi(temp);
            getline(ss, temp, '|');
            city.policeStations = stoi(temp);
            getline(ss, temp, '|');
            city.emergencyVehicles = stoi(temp);

            cities[city.name] = city;
        }
        file.close();
    }

    void saveCities()
    {
        ofstream file("cities.txt");
        for (auto &city : cities)
        {
            auto &c = city.second;
            file << c.name << "|" << c.state << "|"
                 << fixed << setprecision(6) << c.latitude << "|"
                 << fixed << setprecision(6) << c.longitude << "|"
                 << c.population << "|"
                 << c.fireStations << "|"
                 << c.policeStations << "|"
                 << c.emergencyVehicles << "\n";
        }
        file.close();
    }

    void loadEquipment()
    {
        ifstream file("equipment.txt");
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            Equipment eq;
            string temp;

            getline(ss, temp, '|');
            eq.id = stoi(temp);
            getline(ss, eq.name, '|');
            getline(ss, eq.type, '|');
            getline(ss, temp, '|');
            eq.isAvailable = (temp == "1");
            getline(ss, eq.currentLocation, '|');
            getline(ss, temp, '|');
            eq.condition = stoi(temp);

            equipment[eq.id] = eq;
        }
        file.close();
    }

    void saveEquipment()
    {
        ofstream file("equipment.txt");
        for (auto &eq : equipment)
        {
            file << eq.second.id << "|" << eq.second.name << "|" << eq.second.type << "|"
                 << (eq.second.isAvailable ? 1 : 0) << "|"
                 << eq.second.currentLocation << "|" << eq.second.condition << "\n";
        }
        file.close();
    }

    void showMenu()
    {
        cout << "\nWelcome to Disaster Management System!" << endl;
        cout << "1. Login as Admin" << endl;
        cout << "2. Report Disaster" << endl;
        cout << "3. Request Help (Citizen)" << endl;
        cout << "4. Exit" << endl;
    }

    void adminMenu()
    {
        while (true)
        {
            cout << "\nAdmin Menu:" << endl;
            cout << "1. Report Disaster" << endl;
            cout << "2. View All Disasters" << endl;
            cout << "3. View and Assign Teams to Disasters" << endl;
            cout << "4. View and Assign Equipment to Teams" << endl;
            cout << "5. View Hospitals and Shelters" << endl;
            cout << "6. Logout" << endl;
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
                assignEquipment();
            }
            else if (choice == 5)
            {
                viewHospitalsAndShelters();
            }
            else if (choice == 6)
            {
                isLoggedIn = false;
                cout << GREEN << "Logged out successfully!" << RESET << endl;
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

        cout << "Enter disaster type: ";
        cin >> disasterType;
        cout << "Enter status (e.g., ongoing, resolved): ";
        cin >> status;
        cout << "Enter date (YYYY-MM-DD): ";
        cin >> date;
        cout << "Enter latitude and longitude of disaster: ";
        cin >> latitude >> longitude;
        cout << "Enter severity (1 to 5): ";
        cin >> severity;
        cout << "Enter affected population: ";
        cin >> affectedPopulation;

        Location loc = {latitude, longitude, "", "", ""};
        Disaster disaster = {currentDisasterId++, disasterType, loc, severity, status, date, affectedPopulation, {}, {}};
        disasters[disaster.id] = disaster;
        cout << GREEN << "Disaster reported successfully!" << RESET << endl;
    }

    void viewAllDisasters()
    {
        if (disasters.empty())
        {
            cout << RED << "No disasters reported yet." << RESET << endl;
            return;
        }

        cout << "Disasters Reported:" << endl;
        for (auto &disaster : disasters)
        {
            cout << "ID: " << disaster.second.id << ", Type: " << disaster.second.type
                 << ", Status: " << disaster.second.status << ", Severity: " << disaster.second.severity
                 << ", Affected Population: " << disaster.second.affectedPopulation << endl;
        }
    }

    void assignTeams()
    {
        if (disasters.empty())
        {
            cout << RED << "No disasters to assign teams to." << RESET << endl;
            return;
        }

        int disasterId;
        cout << "Enter disaster ID to assign teams: ";
        cin >> disasterId;

        if (disasters.find(disasterId) == disasters.end())
        {
            cout << RED << "Invalid disaster ID." << RESET << endl;
            return;
        }

        int teamId;
        cout << "Enter team ID to assign: ";
        cin >> teamId;

        if (rescueTeams.find(teamId) == rescueTeams.end())
        {
            cout << RED << "Invalid team ID." << RESET << endl;
            return;
        }

        disasters[disasterId].assignedTeams.push_back(teamId);
        cout << GREEN << "Team assigned successfully!" << RESET << endl;
    }

    void assignEquipment()
    {
        if (disasters.empty())
        {
            cout << RED << "No disasters to assign equipment to." << RESET << endl;
            return;
        }

        int disasterId;
        cout << "Enter disaster ID to assign equipment: ";
        cin >> disasterId;

        if (disasters.find(disasterId) == disasters.end())
        {
            cout << RED << "Invalid disaster ID." << RESET << endl;
            return;
        }

        int equipmentId;
        cout << "Enter equipment ID to assign: ";
        cin >> equipmentId;

        if (equipment.find(equipmentId) == equipment.end())
        {
            cout << RED << "Invalid equipment ID." << RESET << endl;
            return;
        }

        disasters[disasterId].requiredResources.push_back(equipment[equipmentId].name);
        cout << GREEN << "Equipment assigned successfully!" << RESET << endl;
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

        cout << "\nShelters:" << endl;
        for (auto &shelter : shelters)
        {
            cout << "ID: " << shelter.second.id << ", Name: " << shelter.second.name
                 << ", Location: " << shelter.second.location << ", Current Occupancy: " << shelter.second.currentOccupancy << endl;
        }
    }

    void citizenRequest()
    {
        int disasterId;
        cout << "Enter disaster ID to request help: ";
        cin >> disasterId;

        if (disasters.find(disasterId) == disasters.end())
        {
            cout << RED << "Invalid disaster ID." << RESET << endl;
            return;
        }

        cout << GREEN << "Request submitted successfully! Help is on the way!" << RESET << endl;
    }

public:
    DisasterManagementSystem() : currentDisasterId(1), currentTeamId(1), currentShelterId(1), currentEquipmentId(1), isLoggedIn(false)
    {
        loadAllData();
    }

    ~DisasterManagementSystem()
    {
        saveAllData();
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
                    isLoggedIn = true;
                    currentUser = username;
                    cout << GREEN << "Login successful!" << RESET << endl;
                    adminMenu();
                }
                else
                {
                    cout << RED << "Invalid credentials. Try again." << RESET << endl;
                }
            }
            else if (choice == 2)
            {
                // Report Disaster (for admin)
                if (!isLoggedIn)
                {
                    cout << RED << "You must be logged in as an admin to report a disaster." << RESET << endl;
                    continue;
                }
                reportDisaster();
            }
            else if (choice == 3)
            {
                // Citizen Request (no login required)
                citizenRequest();
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
        while ((end = data.find(',', start)) != string::npos)
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


int main()
{
    Trie trie;
    trie.insertBulk("New York,Los Angeles,Chicago,Houston,Phoenix,Philadelphia,San Antonio,San Diego,Dallas,San Jose");
    cout << "Search 'Chicago': " << (trie.search("Chicago") ? "Found" : "Not Found") << endl;
    cout << "Search 'Miami': " << (trie.search("Miami") ? "Found" : "Not Found") << endl;
    cout << "Starts with 'San': " << (trie.startsWith("San") ? "Yes" : "No") << endl;
    cout << "Starts with 'Bos': " << (trie.startsWith("Bos") ? "Yes" : "No") << endl;
    cout << "Autocomplete 'San':" << endl;
    vector<string> results = trie.autocomplete("San");
    for (string &result : results)
    {
        cout << "  " << result << endl;
    }

    DisasterManagementSystem dms;
    dms.run();
    return 0;
}





