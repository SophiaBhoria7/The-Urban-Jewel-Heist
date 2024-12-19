//Programmer: Sophia Bhoria
//Date: Nov 24, 2024
//Purpose: Implements the `Police` class, managing movement, arrests, loot confiscation, and tracking.

#include "Police.h"
#include <random>
#include <iostream>
using namespace std;

// Constructor
Police::Police(int id, int x, int y)
    : id(id), xPos(x), yPos(y), confiscatedValue(0), arrests(0) {}

// Move function
void Police::move(City& city) {
    static default_random_engine generator(210);
    uniform_int_distribution<int> direction(0, 7);
    int dir = direction(generator);

    switch (dir) {
        case 0: --xPos; --yPos; break;  // NW
        case 1: --yPos; break;          // N
        case 2: ++xPos; --yPos; break;  // NE
        case 3: --xPos; break;          // W
        case 4: ++xPos; break;          // E
        case 5: --xPos; ++yPos; break;  // SW
        case 6: ++yPos; break;          // S
        case 7: ++xPos; ++yPos; break;  // SE
    }

    // Ensure police stay within grid bounds
    xPos = max(0, min(xPos, 16));
    yPos = max(0, min(yPos, 9));
}

// Arrest function implementation
void Police::arrest(Robber<Jewel>& robber, City& city) {
    if (robber.isActive() && robber.getX() == xPos && robber.getY() == yPos) {
        robber.deactivate();
        ++arrests;

        // Confiscate the loot from the robber and double its value
        for (auto& loot : robber.getLootBag()) {
            loot *= 2;  // Double the loot value when confiscated
            confiscatedValue += loot.getValue();
        }
        robber.getLootBag().clear();  // Clear the robber's loot bag

        city.removeEntity(xPos, yPos);
        city.placeEntity(xPos, yPos, 'P');  // Place police on the grid
        cout << "Police " << id << " arrested Robber " << robber.getID() << "!" << endl;
    }
}

// Getter for confiscated value
int Police::getConfiscatedValue() const {
    return confiscatedValue;
}

// Getter for number of arrests
int Police::getArrests() const {
    return arrests;
}
