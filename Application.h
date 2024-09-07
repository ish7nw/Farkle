//
// Created by Ishan Sharma on 6/9/2024.
//

// HEader file for Application Class

#ifndef APPLICATION_H  // inclusion guards
#define APPLICATION_H

#include "Player.h"
#include "Includes.h"

class Application {


private: // access specifier / modifiers

    // data members or attributes

    std::vector<Player*> players;  // player vector

    int targetScore;  // this is the maximum score that we want the player to reach to win which was written in the brief as 5000
    bool gameWon;   //this boolean holds the truth value of  if a user has won the game or not
    int currentWinnerIndex;   // index sounded more formal but it is the position of the player with the highest score in the player vecotr

public:

    // member functions/ methods

    Application();  // constrcutor declaration
    ~Application();  // destructor declaration

    // helper/utility member functions declaration
    void startGame();

    void playTurn(int playerIndex);

    void declareWinner();

    void displayFinalStandings();

    std::vector<Die*> rollDice(std::vector<Die*> playerDice);

    std::vector<Die*> selectDice(std::vector<Die*> playerDice);

    void showDice(std::vector<Die*> playerDice);

    bool checkForFarkle(std::vector<Die*> playerDice);

    int calculateScore(std::vector<Die*> playerDice);

    int calculateDiceLeft(std::vector<Die*> playerDice);
};

#endif // APPLICATION_H