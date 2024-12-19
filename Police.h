//Programmers: Sophia Bhoria
//Date: Nov 24, 2024
//Purpose: Declares the `Police` class for managing police movement, arrests, and confiscated loot tracking.

#ifndef POLICE_H
#define POLICE_H

#include <iostream>
#include "Robber.h"  // Include Robber.h to use the Robber template
#include "City.h"    // Access the city grid
using namespace std;

class Police {
private:
    int id;                  // Unique police ID
    int xPos, yPos;          // Current position
    int confiscatedValue;    // Total confiscated loot value
    int arrests;             // Total robbers arrested

public:
    Police(int id, int x, int y);      // Constructor
    void move(City& city);             // Move the police
    void arrest(Robber<Jewel>& robber, City& city);  // Arrest a single robber
    int getConfiscatedValue() const;   // Getter for confiscated value
    int getArrests() const;            // Getter for number of arrests
    int getID() const { return id; }   // Getter for police ID
};

#endif // POLICE_H
