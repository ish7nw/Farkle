//
// Created by Ishan Sharma on 6/9/2024.
//

// Header File For The Player Class

#ifndef PLAYER_H   // Inclusion Guards
#define PLAYER_H

#include "Die.h"
#include "Includes.h"



class Player {
private: // access specifier / modifier

     // data members

    std::string* name;       // pointer to the name of the player
    int* currentScore;     // pointer to the current score
    int* totalScore;        // pointer to the total score
    std::vector<Die*> dice;  // vector of dice pointers (object pointer to be specific)

public:

    // member functions

    Player();   // Constructor
    ~Player();  // Destructor


    // accessors/mutators or setters/getters declaration

    std::string getName();
    void setName(std::string playerName);

    int getCurrentScore();
    int getTotalScore();

    std::vector<Die*> getDice();
    void setDice(std::vector<Die*> newDice);

    // utility / helper member functions

    void addCurrentScore(int score);
    void updateTotalScore();
    void resetCurrentScore();
    void resetDice();
};

#endif // PLAYER_H