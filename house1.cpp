//
// Created by Mariam on 6/25/2024.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

class House {
public:
    std::vector<std::string> layout;
    std::pair<int, int> docking_station;
    int max_battery_steps;
    int max_mission_steps;

    static House fromFile(const std::string &file_path) {
        House house;
        std::ifstream file(file_path);
        std::string line;

        while (std::getline(file, line)) {
            house.layout.push_back(line);
        }

        // Parse configuration
        std::istringstream iss(house.layout.back());
        house.layout.pop_back();
        iss >> house.max_battery_steps >> house.max_mission_steps;

        // Find docking station
        for (int i = 0; i < house.layout.size(); ++i) {
            for (int j = 0; j < house.layout[i].size(); ++j) {
                if (house.layout[i][j] == 'D') {
                    house.docking_station = {i, j};
                    house.layout[i][j] = ' ';
                }
            }
        }

        return house;
    }
};

