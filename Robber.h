//Programmer: Sophia Bhoria
//Date: Nov 24, 2024
//Purpose: Template-based `Robber` class models robbers, loot, moves, and interactions in a city.

#ifndef ROBBER_H
#define ROBBER_H

#include <vector>
#include <iostream>
#include "Jewel.h"
#include "City.h"
using namespace std;

template <typename LootType>
class Robber {
private:
    static int totalLootValue;  // Collective worth of loot across all robbers
    static int robberCount;      // Total number of robbers created
    int id;                      // Unique ID
    int xPos, yPos;              // Current position
    bool active;                 // Robber's active status
    bool spawned;                // Has the robber spawned another robber
    vector<LootType> lootBag;    // Bag of loot
    bool isGreedy;               // Robber type: greedy or ordinary
    int consecutiveMoves;        // For greedy robbers' multiple moves

public:
    Robber(int x, int y, bool greedy = false);
    void move(City& city);
    void pickUpLoot(LootType loot, int value);
    void dropLoot(City& city);
    bool isBagFull() const;
    static int getTotalLootValue();  // Static method
    int getID() const { return id; }
    bool isActive() const { return active; }
    void deactivate();
    bool trySpawnNewRobber(City& city);
    void redistributeLoot(Robber<LootType>& otherRobber);
    int getX() const { return xPos; }
    int getY() const { return yPos; }

    // Non-const version of getLootBag to modify the loot bag
    vector<LootType>& getLootBag() { return lootBag; }

    // Const version of getLootBag to access it without modifying
    const vector<LootType>& getLootBag() const { return lootBag; }  // Const version
};

// Initialize static variables
template <typename LootType>
int Robber<LootType>::totalLootValue = 0;

template <typename LootType>
int Robber<LootType>::robberCount = 0;

// Constructor implementation
template <typename LootType>
Robber<LootType>::Robber(int x, int y, bool greedy)
    : xPos(x), yPos(y), active(true), spawned(false), isGreedy(greedy), consecutiveMoves(0) {
    id = ++robberCount;
}

// Move function implementation
template <typename LootType>
void Robber<LootType>::move(City& city) {
    if (!active) return;

    static default_random_engine generator(210);
    uniform_int_distribution<int> direction(0, 7);
    int dir = direction(generator);

    switch (dir) {
        case 0: --xPos; --yPos; break;  // Northwest
        case 1: --yPos; break;          // North
        case 2: ++xPos; --yPos; break;  // Northeast
        case 3: --xPos; break;          // West
        case 4: ++xPos; break;          // East
        case 5: --xPos; ++yPos; break;  // Southwest
        case 6: ++yPos; break;          // South
        case 7: ++xPos; ++yPos; break;  // Southeast
    }

    xPos = max(0, min(xPos, 16));
    yPos = max(0, min(yPos, 9));

    if (city.getEntityAt(xPos, yPos) == 'J') {
        int value = (xPos + yPos) * (xPos + yPos);  // Calculate jewel value
        LootType newJewel(value, xPos, yPos);
        pickUpLoot(newJewel, value);
        city.removeEntity(xPos, yPos);
    }
}

// Pick up loot function
template <typename LootType>
void Robber<LootType>::pickUpLoot(LootType loot, int value) {
    if (lootBag.size() < 20) {
        lootBag.push_back(loot);
        totalLootValue += value;
    }
}

// Static method to get total loot value
template <typename LootType>
int Robber<LootType>::getTotalLootValue() {
    return totalLootValue;
}

// Deactivate robber
template <typename LootType>
void Robber<LootType>::deactivate() {
    active = false;
}

// Check if loot bag is full
template <typename LootType>
bool Robber<LootType>::isBagFull() const {
    return lootBag.size() >= 20;
}

// Try to spawn a new robber if loot value is greater than 1000
template <typename LootType>
bool Robber<LootType>::trySpawnNewRobber(City& city) {
    if (totalLootValue > 1000 && !spawned) {
        spawned = true;
        // Spawn a new robber at a random position
        default_random_engine generator(210);
        uniform_int_distribution<int> xDist(0, 16);
        uniform_int_distribution<int> yDist(0, 9);
        int newX = xDist(generator), newY = yDist(generator);
        Robber<LootType> newRobber(newX, newY);
        return true;
    }
    return false;
}

// Redistribute loot between two robbers
template <typename LootType>
void Robber<LootType>::redistributeLoot(Robber<LootType>& otherRobber) {
    int otherLootValue = 0;
    for (auto& loot : otherRobber.lootBag) {
        otherLootValue += loot.getValue();
    }

    int share = otherLootValue / 2;
    otherRobber.dropLoot();  // Drop loot
    this->pickUpLoot(otherRobber.lootBag.back(), share);
}

#endif // ROBBER_H
