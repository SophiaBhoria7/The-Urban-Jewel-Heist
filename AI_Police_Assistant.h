//Programmers: Sophia Bhoria
//Date: Nov 24, 2024
//Purpose: Declares the `AI_Police_Assistant` class for an autonomous drone that scans for robbers.

#ifndef AI_POLICE_ASSISTANT_H
#define AI_POLICE_ASSISTANT_H

#include <iostream>
#include "City.h"
using namespace std;

class AI_Police_Assistant {
private:
    int id;          // Unique ID for the assistant
    int xPos, yPos;  // Current position on the grid

public:
    AI_Police_Assistant(int id, int x, int y); // Constructor
    void move(City& city);                     // Move the assistant
    void scan(const City& city) const;         // Scan for robbers
};

#endif 
