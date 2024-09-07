//
// Created by Ishan Sharma on 6/9/2024.
//



#include "Die.h"

// member function definition


// Constructor definition

Die::Die() {
    value = new int(0);           // storing the value of the dice in the heap using the new
    isRollable = new bool(true);  // same for the boolean for locking the dice
}

// Destructor definition
Die::~Die() {

    // deleteing the heap obecjt so that we dont have memory leak
    delete value;
    delete isRollable;

    // setting the nullptr to avoid danglingpointer
    value = nullptr;
    isRollable = nullptr;

}


// accessors/mutators or getters/setters definition

void Die::roll() {
    if (*isRollable)
    {
        (*value) = rand() % 6 + 1;
    }
}

int Die::getValue() {

    return (*value);

}


void Die::setIsRollable(bool rollable) {

    (*isRollable) = rollable;
}

bool Die::getIsRollable() {

    return (*isRollable);
}


// in these member functions, we use '*' which is known as the de-references operator which returns the value stored at a pointer
// this was taught in class