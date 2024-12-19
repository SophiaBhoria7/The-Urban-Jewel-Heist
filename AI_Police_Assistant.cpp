//Programmer: Sophia Bhoria
//Date: Nov 24, 2024
//Purpose: Implements the `AI_Police_Assistant` class, enabling drones to move randomly and scan for robbers.

#include "AI_Police_Assistant.h"
#include <random>
using namespace std;

// Constructor
AI_Police_Assistant::AI_Police_Assistant(int id, int x, int y)
    : id(id), xPos(x), yPos(y) {}

// Move function
void AI_Police_Assistant::move(City& city) {
    static default_random_engine generator(210);
    uniform_int_distribution<int> direction(0, 7);
    int dir = direction(generator);

    // Adjust xPos, yPos based on direction
    if (dir == 0) { --xPos; --yPos; } // NW
    else if (dir == 1) { --yPos; }    // N
    else if (dir == 2) { ++xPos; --yPos; } // NE
    else if (dir == 3) { --xPos; }    // W
    else if (dir == 4) { ++xPos; }    // E
    else if (dir == 5) { --xPos; ++yPos; } // SW
    else if (dir == 6) { ++yPos; }    // S
    else if (dir == 7) { ++xPos; ++yPos; } // SE

    // Ensure the drone stays within grid bounds
    xPos = max(0, min(xPos, 16));
    yPos = max(0, min(yPos, 9));
}

// Scan function
void AI_Police_Assistant::scan(const City& city) const {
    cout << "AI Drone " << id << " is scanning for robbers..." << endl;
    // Logic for scanning and reporting positions of robbers
}
