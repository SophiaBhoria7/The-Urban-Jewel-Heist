//Programmer: Sophia Bhoria
//Date: Nov 24, 2024
//Purpose: Implements methods for grid initialization, entity placement, and grid display in the `City` class.

#include "City.h"

// Constructor initializes the grid with empty cells
City::City() : jewelCount(0) {
    for (int i = 0; i < WIDTH; ++i)
        for (int j = 0; j < HEIGHT; ++j)
            grid[i][j] = '.'; // Empty cell
}

// Randomly scatter jewels and initialize grid
void City::initializeGrid(int jewelCount) {
    this->jewelCount = jewelCount;
    default_random_engine generator(210); // Seed for consistent randomness
    uniform_int_distribution<int> xDist(0, WIDTH - 1);
    uniform_int_distribution<int> yDist(0, HEIGHT - 1);

    int scatteredJewels = 0;
    while (scatteredJewels < jewelCount) {
        int x = xDist(generator), y = yDist(generator);
        if (grid[x][y] == '.') {
            grid[x][y] = 'J'; // Place a jewel
            ++scatteredJewels;
        }
    }
}

// Display the current state of the grid
void City::displayGrid() const {
    for (int j = 0; j < HEIGHT; ++j) {
        for (int i = 0; i < WIDTH; ++i)
            cout << grid[i][j] << ' ';
        cout << endl;
    }
}

// Check if a cell is empty
bool City::isCellEmpty(int x, int y) const {
    return grid[x][y] == '.';
}

// Place an entity on the grid
void City::placeEntity(int x, int y, char entity) {
    grid[x][y] = entity;
}

// Get the entity at a specific position
char City::getEntityAt(int x, int y) const {
    return grid[x][y];
}

// Remove an entity from the grid
void City::removeEntity(int x, int y) {
    grid[x][y] = '.';
}
