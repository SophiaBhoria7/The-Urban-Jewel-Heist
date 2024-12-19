//Programmer: Sophia Bhoria
//Date: Nov 24, 2024
//Purpose: Runs a 30-turn simulation of robbers vs. police, with optional drones, in a city grid.

#include <iostream>
#include <fstream>
#include "City.h"
#include "Jewel.h"
#include "Robber.h"
#include "Police.h"
#include "AI_Police_Assistant.h"
using namespace std;

void runSimulation(bool withDrones) {
    // Initialize the city and entities
    City city;
    city.initializeGrid();
    city.displayGrid();

    // Initialize police officers
    vector<Police> policeOfficers = {
        Police(1, 0, 0),
        Police(2, 5, 5),
        Police(3, 10, 10)
    };

    // Initialize robbers
    vector<Robber<Jewel>> robbers = {
        Robber<Jewel>(3, 3, false),
        Robber<Jewel>(8, 8, false),
        Robber<Jewel>(4, 4, true),
        Robber<Jewel>(9, 9, true)
    };

    // Initialize drones if needed
    vector<AI_Police_Assistant> drones;
    if (withDrones) {
        drones = {
            AI_Police_Assistant(1, 2, 2),
            AI_Police_Assistant(2, 6, 6),
            AI_Police_Assistant(3, 14, 8)
        };
    }

    // Create an output file stream to write to the file
    ofstream outFile;
    if (withDrones) {
        outFile.open("simulation_with_drones.txt");
    } else {
        outFile.open("simulation_without_drones.txt");
    }

    // Write simulation details to the file
    outFile << "Simulation (With Drones: " << (withDrones ? "Yes" : "No") << ")\n";
    int turn = 0;
    const int maxTurns = 30;

    // Simulation Loop (Max 30 Turns or Early Termination)
    while (turn < maxTurns) {
        outFile << "\nTurn " << turn + 1 << ":" << endl;

        // Move robbers
        for (auto& robber : robbers) {
            if (robber.isActive()) {
                robber.move(city);
            }
        }

        // Move police and attempt arrests
        for (auto& officer : policeOfficers) {
            officer.move(city);
            for (auto& robber : robbers) {
                officer.arrest(robber, city);  // Check each robber
            }
        }

        // Move drones (optional scanning logic)
        if (withDrones) {
            for (auto& drone : drones) {
                drone.move(city);
                drone.scan(city);  // Optional drone scanning logic
            }
        }

        // Display grid after each turn
        city.displayGrid();

        // Check for winning conditions
        int totalLootValue = Robber<Jewel>::getTotalLootValue();
        if (totalLootValue >= 5000) {
            outFile << "\nRobbers win! Total loot value exceeds $5000." << endl;
            break;
        }

        // Check if all robbers are arrested
        bool allArrested = true;
        for (const auto& robber : robbers) {
            if (robber.isActive()) {
                allArrested = false;
                break;
            }
        }
        if (allArrested) {
            outFile << "\nPolice win! All robbers have been arrested." << endl;
            break;
        }

        ++turn;
    }

    // Simulation Summary
    outFile << "\nSummary of the chase:" << endl;
    if (turn == maxTurns) {
        outFile << "The robbers win the chase because the maximum number of turns (" << maxTurns << ") has been reached." << endl;
    }

    // Police Summary
    for (const auto& officer : policeOfficers) {
        outFile << "Police " << officer.getID() << ":\n\tConfiscated loot value: $" 
                << officer.getConfiscatedValue() << "\n\tRobbers caught: " 
                << officer.getArrests() << endl;
    }

    // Robber Summary
    for (const auto& robber : robbers) {
        outFile << "\nRobber " << robber.getID() << ":\n\tJewels picked up: " 
                << robber.getLootBag().size() << "\n\tTotal jewel worth: $" 
                << robber.getTotalLootValue() << endl;
    }

    outFile.close();
}

int main() {
    // Run simulation with drones and save to a file
    runSimulation(true);  // With drones

    // Run simulation without drones and save to a file
    runSimulation(false);  // Without drones

    cout << "Simulation completed and saved to files." << endl;
    return 0;
}
