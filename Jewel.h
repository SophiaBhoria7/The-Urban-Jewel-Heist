//Programmer: Sophia Bhoria
//Date: Nov 24, 2024
//Purpose: Defines a `Jewel` class to represent and manage properties of a jewel, including its value, position, and operations for modification and display.

#ifndef JEWEL_H
#define JEWEL_H

#include <iostream>
using namespace std;

class Jewel {
private:
    int value; // Value of the jewel
    int xPos;  // X-coordinate
    int yPos;  // Y-coordinate

public:
    Jewel(int value, int xPos, int yPos); // Constructor
    int getValue() const; // Get the jewel's value
    int getX() const;     // Get the x-coordinate
    int getY() const;     // Get the y-coordinate
    Jewel& operator*=(int factor); // Modify value (non-const)
    void display() const; // Display jewel information
};

#endif // JEWEL_H
