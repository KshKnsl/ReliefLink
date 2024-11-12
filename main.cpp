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

using namespace std;

// Infrastructure and Resource Structures
struct Equipment {
    int id;
    string name;
    string type;
    bool isAvailable;
    string currentLocation;
    int condition; // 1-10 scale
};

struct Hospital {
    int id;
    string name;
    string location;
    int totalBeds;
    int availableBeds;
    bool hasEmergencyUnit;
    vector<string> specializations;
};

struct City {
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

struct Location {
    double latitude;
    double longitude;
    string address;
    string city;
    string state;
};

struct Disaster {
    int id;
    string type;
    Location location;
    int severity;
    string status;
    string date;
    int affectedPopulation;
    vector<int> assignedTeams;
    vector<string> requiredResources;
};

struct RescueTeam {
    int id;
    string name;
    Location currentLocation;
    bool isAvailable;
    string specialization;
    int memberCount;
    vector<int> equippedWith;
};

struct Shelter {
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

// Class for managing file operations
class FileManager {
private:
    string citiesFile = "cities.txt";
    string disastersFile = "disasters.txt";
    string teamsFile = "teams.txt";
    string sheltersFile = "shelters.txt";
    string usersFile = "users.txt";

public:
    void createDummyData() {
        createDummyCities();
        createDummyEquipment();
        createDummyHospitals();
    }

private:
    void createDummyCities() {
        ofstream file("cities.txt");
        vector<pair<string, string>> cities = {
            {"New York", "NY"}, {"Los Angeles", "CA"}, {"Chicago", "IL"},
            {"Houston", "TX"}, {"Phoenix", "AZ"}, {"Philadelphia", "PA"},
            {"San Antonio", "TX"}, {"San Diego", "CA"}, {"Dallas", "TX"},
            {"San Jose", "CA"}
        };

        for (const auto& city : cities) {
            file << city.first << "|" << city.second << "|"
                 << (30.0 + (rand() % 20)) << "|"  // Random latitude
                 << (-120.0 + (rand() % 50)) << "|"  // Random longitude
                 << (100000 + (rand() % 900000)) << "|"  // Random population
                 << (2 + (rand() % 5)) << "|"  // Fire stations
                 << (2 + (rand() % 5)) << "|"  // Police stations
                 << (5 + (rand() % 20)) << "\n";  // Emergency vehicles
        }
        file.close();
    }

    void createDummyEquipment() {
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
            {"Mobile Command Center", "command"}
        };

        int id = 1;
        for (const auto& eq : equipment) {
            file << id++ << "|" << eq.first << "|" << eq.second << "|"
                 << "1|"  // isAvailable
                 << "Central Station|"  // currentLocation
                 << (7 + (rand() % 4)) << "\n";  // condition (7-10)
        }
        file.close();
    }

    void createDummyHospitals() {
        ofstream file("hospitals.txt");
        vector<string> hospitalNames = {
            "General Hospital", "Memorial Hospital", "Community Medical Center",
            "University Hospital", "Regional Medical Center", "Emergency Care Center",
            "St. Mary's Hospital", "City Medical Center", "County Hospital",
            "Medical Center"
        };

        vector<string> specializations = {
            "Emergency", "Trauma", "Burns", "Cardiac", "Pediatric",
            "Orthopedic", "Neurological", "Respiratory", "General Surgery"
        };

        int id = 1;
        for (const auto& name : hospitalNames) {
            file << id++ << "|" << name << "|"
                 << "City Location|"
                 << (100 + (rand() % 400)) << "|"  // totalBeds
                 << (20 + (rand() % 100)) << "|"  // availableBeds
                 << "1|";  // hasEmergencyUnit

            // Add 2-4 random specializations
            int specCount = 2 + (rand() % 3);
            for (int i = 0; i < specCount; i++) {
                if (i > 0) file << ",";
                file << specializations[rand() % specializations.size()];
            }
            file << "\n";
        }
        file.close();
    }
};

// Class for the Disaster Management System
class DisasterManagementSystem {
private:
    map<int, Disaster> disasters;
    map<int, RescueTeam> rescueTeams;
    map<int, Shelter> shelters;
    map<string, City> cities;
    map<int, Equipment> equipment;
    priority_queue<pair<int, int>> alertQueue;
    
    int currentDisasterId;
    int currentTeamId;
    int currentShelterId;
    int currentEquipmentId;
    
    bool isLoggedIn;
    string currentUser;
    map<string, string> users;

    // File handling methods
    void loadAllData() {
        loadUsers();
        loadCities();
        loadEquipment();
        // loadDisasters();
        // loadTeams();
        // loadShelters();
    }

    void saveAllData() {
        saveUsers();
        saveCities();
        saveEquipment();
        // saveDisasters();
        // saveTeams();
        // saveShelters();
    }

    void loadCities() {
        ifstream file("cities.txt");
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string token;
            vector<string> tokens;
            while (getline(ss, token, '|')) {
                tokens.push_back(token);
            }
            if (tokens.size() >= 8) {
                City city;
                city.name = tokens[0];
                city.state = tokens[1];
                city.latitude = stod(tokens[2]);
                city.longitude = stod(tokens[3]);
                city.population = stoi(tokens[4]);
                city.fireStations = stoi(tokens[5]);
                city.policeStations = stoi(tokens[6]);
                city.emergencyVehicles = stoi(tokens[7]);
                cities[city.name] = city;
            }
        }
        file.close();
    }

    void saveCities() {
        ofstream file("cities.txt");
        for (const auto& pair : cities) {
            const City& city = pair.second;
            file << city.name << "|"
                 << city.state << "|"
                 << city.latitude << "|"
                 << city.longitude << "|"
                 << city.population << "|"
                 << city.fireStations << "|"
                 << city.policeStations << "|"
                 << city.emergencyVehicles << "\n";
        }
        file.close();
    }

    void loadEquipment() {
        ifstream file("equipment.txt");
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string token;
            vector<string> tokens;
            while (getline(ss, token, '|')) {
                tokens.push_back(token);
            }
            if (tokens.size() >= 6) {
                Equipment eq;
                eq.id = stoi(tokens[0]);
                eq.name = tokens[1];
                eq.type = tokens[2];
                eq.isAvailable = (tokens[3] == "1");
                eq.currentLocation = tokens[4];
                eq.condition = stoi(tokens[5]);
                equipment[eq.id] = eq;
                currentEquipmentId = max(currentEquipmentId, eq.id + 1);
            }
        }
        file.close();
    }

    void saveEquipment() {
        ofstream file("equipment.txt");
        for (const auto& pair : equipment) {
            const Equipment& eq = pair.second;
            file << eq.id << "|"
                 << eq.name << "|"
                 << eq.type << "|"
                 << (eq.isAvailable ? "1" : "0") << "|"
                 << eq.currentLocation << "|"
                 << eq.condition << "\n";
        }
        file.close();
    }

    void loadUsers() {
        ifstream file("users.txt");
        string username, password;
        while (file >> username >> password) {
            users[username] = password;
        }
        file.close();

        if (users.empty()) {
            users["admin"] = "admin123";
            saveUsers();
        }
    }

    void saveUsers() {
        ofstream file("users.txt");
        for (const auto& user : users) {
            file << user.first << " " << user.second << "\n";
        }
        file.close();
    }

    string getHiddenInput() {
        string input;
        char ch;
        while ((ch = _getch()) != 13) {
            if (ch == 8) {
                if (!input.empty()) {
                    input.pop_back();
                    cout << "\b \b";
                }
            }
            else {
                input += ch;
                cout << "*";
            }
        }
        cout << endl;
        return input;
    }

    void displayCityInfo(const string& cityName) {
        if (cities.find(cityName) == cities.end()) {
            cout << "\nCity not found!\n";
            return;
        }

        const City& city = cities[cityName];
        cout << "\nCity Information:";
        cout << "\n----------------";
        cout << "\nName: " << city.name;
        cout << "\nState: " << city.state;
        cout << "\nPopulation: " << city.population;
        cout << "\nEmergency Infrastructure:";
        cout << "\n- Fire Stations: " << city.fireStations;
        cout << "\n- Police Stations: " << city.policeStations;
        cout << "\n- Emergency Vehicles: " << city.emergencyVehicles;
        cout << "\nLocation: " << city.latitude << ", " << city.longitude;
        cout << "\n----------------\n";
    }

    void displayEquipmentInfo() {
        cout << "\nAvailable Equipment:";
        cout << "\n-------------------";
        for (const auto& pair : equipment) {
            const Equipment& eq = pair.second;
            cout << "\nID: " << eq.id;
            cout << "\nName: " << eq.name;
            cout << "\nType: " << eq.type;
            cout << "\nStatus: " << (eq.isAvailable ? "Available" : "In Use");
            cout << "\nLocation: " << eq.currentLocation;
            cout << "\nCondition: " << eq.condition << "/10";
            cout << "\n-------------------";
        }
    }

public:
    DisasterManagementSystem() {
        currentDisasterId = 1;
        currentTeamId = 1;
        currentShelterId = 1;
        currentEquipmentId = 1;
        isLoggedIn = false;
        
        FileManager fileManager;
        fileManager.createDummyData();
        loadAllData();
    }

    ~DisasterManagementSystem() {
        saveAllData();
    }

    bool login() {
        string username, password;
        cout << "\nLogin System\n";
        cout << "Username: ";
        cin >> username;
        cout << "Password: ";
        password = getHiddenInput();

        if (users.find(username) != users.end() && users[username] == password) {
            isLoggedIn = true;
            currentUser = username;
            cout << "\nLogin successful!\n";
            return true;
        }
        cout << "\nInvalid username or password!\n";
        return false;
    }

    void searchCity() {
        string cityName;
        cout << "\nEnter city name: ";
        cin.ignore();
        getline(cin, cityName);
        displayCityInfo(cityName);
    }

    void addDisaster() {
        Disaster disaster;
        disaster.id = currentDisasterId++;
        
        cout << "\nEnter disaster details:";
        cout << "\nType (flood/earthquake/fire/hurricane): ";
        cin >> disaster.type;
        cout << "Location (latitude longitude): ";
        cin >> disaster.location.latitude >> disaster.location.longitude;
        cout << "City: ";
        cin.ignore();
        getline(cin, disaster.location.city);
        cout << "Severity (1-10): ";
        cin >> disaster.severity;
        cout << "Affected Population: ";
        cin >> disaster.affectedPopulation;
        
        // Get current date
        time_t now = time(0);
        disaster.date = ctime(&now);
        disaster.status = "Active";
        
        disasters[disaster.id] = disaster;
        alertQueue.push({disaster.severity, disaster.id});
        
        cout << "\nDisaster added successfully! ID: " << disaster.id << endl;
    }

    void viewDisasters() {
        if (disasters.empty()) {
            cout << "\nNo disasters recorded.\n";
            return;
        }
        
        cout << "\nCurrent Disasters:\n";
        cout << setw(5) << "ID" << setw(15) << "Type" << setw(20) << "City"
             << setw(10) << "Severity" << setw(15) << "Status" << "\n";
        cout << string(65, '-') << "\n";
        
        for (const auto& pair : disasters) {
            const Disaster& d = pair.second;
            cout << setw(5) << d.id << setw(15) << d.type 
                 << setw(20) << d.location.city << setw(10) << d.severity
                 << setw(15) << d.status << "\n";
        }
    }

    void viewEquipment() {
        displayEquipmentInfo();
    }

    void run() {
        while (true) {
            if (!isLoggedIn) {
                cout << "\n1. Login\n2. Exit\nChoice: ";
                int choice;
                cin >> choice;
                if (choice == 1) {
                    if (login()) {
                        cout << "\nLogged in as " << currentUser << endl;
                    }
                }
                else {
                    break;
                }
            }
            else {
                cout << "\n1. Search City\n2. Add Disaster\n3. View Disasters\n"
                     << "4. View Equipment\n5. Logout\nChoice: ";
                int choice;
                cin >> choice;
                switch (choice) {
                    case 1: searchCity(); break;
                    case 2: addDisaster(); break;
                    case 3: viewDisasters(); break;
                    case 4: viewEquipment(); break;
                    case 5: isLoggedIn = false; break;
                    default: cout << "\nInvalid choice!\n";
                }
            }
        }
    }
};

int main() {
    DisasterManagementSystem dms;
    dms.run();
    return 0;
}