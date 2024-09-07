//
// Created by Ishan Sharma on 6/9/2024.
//


#include "Player.h"

// Constructor definition
Player::Player() {

    // allocating the data members to the heap using the new kyword

    name = new std::string();
    currentScore = new int(0);
    totalScore = new int(0);

    // making a vector of 6 dices on the heap using new keyword
    for (int i = 0; i < 6; i++) {
        dice.push_back(new Die());
    }
}


// Destructor definition
Player::~Player() {

    // deleting the objects inside the heap using the pointer which was created above

    delete name;
    delete currentScore;
    delete totalScore;

    // deleting the dice values and setting them to null to avoid it being a dangling pointer

    for (int i = 0; i < dice.size(); i++) {
        delete dice[i];
        dice[i] = nullptr;
    }
    dice.clear();
}

// accessors/mutators or getters and setters definition

std::string Player::getName() {
    return (*name);
}

void Player::setName(std::string playerName) {
    (*name) = playerName;
}

int Player::getCurrentScore() {
    return (*currentScore);
}

int Player::getTotalScore() {
    return (*totalScore);
}

std::vector<Die*> Player::getDice() {
    return dice;
}


// Helper /utility member funcrtions definition

void Player::setDice(std::vector<Die*> newDice) {
    dice = newDice;
}

void Player::addCurrentScore(int score) {
    (*currentScore) += score;
}

void Player::updateTotalScore() {
    (*totalScore) += (*currentScore);
    resetCurrentScore();
}

void Player::resetCurrentScore() {
    (*currentScore) = 0;
}

void Player::resetDice() {
    for (int i = 0; i < dice.size(); i++) {
        dice[i]->setIsRollable(true);
    }
}