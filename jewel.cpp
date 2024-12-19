//Programmer: Sophia Bhoria
//Date: Nov 24, 2024
//Purpose: Defines a `Jewel` class with value, position, and methods.

#include "Jewel.h"

// Constructor
Jewel::Jewel(int value, int xPos, int yPos)
    : value(value), xPos(xPos), yPos(yPos) {}

// Get the jewel's value
int Jewel::getValue() const {
    return value;
}

// Get the x-coordinate
int Jewel::getX() const {
    return xPos;
}

// Get the y-coordinate
int Jewel::getY() const {
    return yPos;
}

// Modify the jewel's value
Jewel& Jewel::operator*=(int factor) {
    value *= factor;
    return *this;  // Return the modified object
}

// Display jewel information
void Jewel::display() const {
    cout << "Jewel at (" << xPos << ", " << yPos << ") with value: $" << value << endl;
}
