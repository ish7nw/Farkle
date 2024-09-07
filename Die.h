//
// Created by Ishan Sharma on 6/9/2024.
//

// Header file for Dice Class

#ifndef DIE_H  //Inclusion Guards
#define DIE_H

#include "Includes.h"

class Die {

    // access specifier
private:

    // data members

    int* value;         // Pointer to store the die value
    bool* isRollable;   // Pointer to store the boolean of if the dcie is or not rollable

public:

    // member functions

    Die();   // Constructor non parametrised
    ~Die();  // Destructor

    // accessors and mutators or getters and setters
    void roll();               // Function to roll the die
    int getValue();            // Function to get the value of the die
    void setIsRollable(bool);  // Function to set rollable status
    bool getIsRollable();      // Function to get rollable status
};

#endif // DIE_H