#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std; //not recommended
class House {
public:
    std::vector<std::string> layout;
    vector<vector<int>> house_matrix;
    std::pair<int, int> docking_station;
    int max_battery_steps ;
    int max_mission_steps;
    int width;
    int length;
    // Default constructor initializing all fields
    House()
    : docking_station(-1, -1), max_battery_steps(0), max_mission_steps(0), width(0), length(0) {}
    //constructs House from the given file
    explicit House(const std::string &file_path)
        : docking_station(-1, -1), max_battery_steps(0), max_mission_steps(0), width(0), length(0) {
        readFromFile(file_path);
        parseConfig();
        initializeMatrix();
        //findDockingStation();
    }


/*
    static House fromFile(const std::string &file_path) {
        House house; // create an instance of House
        std::ifstream file(file_path);  // Attempt to open the file at the given file_path
        if (!file.is_open()) {
            // print error message :check if the file was opened successfully, if not print error message and return.
            std::cerr << "Failed to open file: " << file_path << std::endl;
            return house ;
        }
        std::string line;
        // Read the file line by line
        while (std::getline(file, line)) {
            house.layout.push_back(line); // Add each line to the house layout
        }


        // Parse configuration for the max battrey steps and for the max mission steps
        std::istringstream iss(house.layout.back()); // from the last line
        house.layout.pop_back();
        //iss >> house.max_battery_steps >> house.max_mission_steps;
        if (!(iss >> house.max_battery_steps >> house.max_mission_steps)) {
            throw std::runtime_error("Failed to parse configuration from file: " + file_path);
        }
        file.close();
        // Find docking station
        bool found_d=false;
        for (int i = 0; i < house.layout.size(); ++i)
        {
            for (int j = 0; j < house.layout[i].size(); ++j) {
                if (house.layout[i][j] == 'D') {
                    house.docking_station = {i, j};
                    house.house_matrix[i][j]=20;
                   // house.layout[i][j] = ' ';// maybe we can use 11 or 0 intead if we want to build int matrix
                    found_d=true;
                }
                if (house.layout[i][j] == '#') {
                    house.house_matrix[i][j]=-1;
                }
                else {
                    house.house_matrix[i][j]=(house.layout[i][j] >= '1' && house.layout[i][j] <= '9') ? house.layout[i][j] - '0' : 0;
                }
            }
        }
        if (!found_d) {
            throw std::runtime_error("Doking sattion D not found in file:"+file_path);
        }
        return house;
    }
    */

    void readFromFile(const std::string &file_path) {
        ifstream file(file_path);
        if (!file.is_open()) {
            throw runtime_error("Failed to open file: " + file_path);
        }
        string line;
        while (getline(file, line)) {
            layout.push_back(line);
        }
        file.close();
    }
    // Parse configuration for the max battrey steps and for the max mission steps
    void parseConfig() { // convert string>>int!!!!!!!!
        istringstream iss(layout.back());
        layout.pop_back();
        if (!(iss >> max_battery_steps >> max_mission_steps)) { // from the last line
            throw runtime_error("Failed to parse configuration from file");
        }
    }
    void initializeMatrix() {
        length = layout.size();
        width = layout[0].size();
        house_matrix.resize(length, vector<int>(width, 0));

        for (int i = 0; i < length; ++i) {
            for (int j = 0; j < width; ++j) {
                char cell = layout[i][j];
                if (cell == '#') {
                    house_matrix[i][j] = -1;
                } else if (cell >= '1' && cell <= '9') {
                    house_matrix[i][j] = cell - '0';
                } else if (cell == 'D') {
                    docking_station = {i, j};
                    house_matrix[i][j] = 20;
                } else {
                    house_matrix[i][j] = 0;
                }
            }
        }
    }
    void findDockingStation() {
        bool found = false;
        for (int i = 0; i < length; ++i) {
            for (int j = 0; j < width; ++j) {
                if (layout[i][j] == 'D') {
                    docking_station = {i, j};
                    layout[i][j] = ' ';
                    found = true;
                    break;
                }
            }
            if (found) break;
        }
        if (!found) {
            throw runtime_error("Docking station 'D' not found in file");
        }
    }

};
