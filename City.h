//Programmer: Sophia Bhoria
//Date: Nov 24, 2024
//Purpose: Defines the `City` class to manage a 17x10 grid, place entities, and display the city state.

#ifndef CITY_H
#define CITY_H

#include <iostream>
#include <vector>
#include <random>
using namespace std;

class City {
private:
    static const int WIDTH = 17; // Width of the grid
    static const int HEIGHT = 10; // Height of the grid
    char grid[WIDTH][HEIGHT]; // 2D grid representing the city
    int jewelCount; // Current number of jewels in the city

public:
    City(); // Default constructor
    void initializeGrid(int jewelCount = 70); // Initialize grid with jewels
    void displayGrid() const; // Display the current state of the grid
    bool isCellEmpty(int x, int y) const; // Check if a cell is empty
    void placeEntity(int x, int y, char entity); // Place an entity on the grid
    char getEntityAt(int x, int y) const; // Get the entity at a specific position
    void removeEntity(int x, int y); // Remove an entity from the grid
};

#endif
