//
// Created by Ishan Sharma on 6/9/2024.
//



#include "Application.h"



Application::Application() {  // constructor definition
    targetScore = 5000;
    gameWon = false;
    currentWinnerIndex = -1;
}


Application::~Application() { // destructor definition


    // loopinf through all the pointers to delte the objects from the memory (heap) to be specific and set pointers to nullptr to avoid danglingptr
    for (int i = 0; i < players.size(); i++)
    {
        delete players[i];
        players[i] = nullptr;
    }
}

void Application::startGame() {
    bool playAgain = true;

    while (playAgain)
    {
        players.clear();
        gameWon = false;
        currentWinnerIndex = -1;

        int numPlayers;
        std::cout << "\n***********************************************************************\n";
        std::cout << "                     FARKLE:: A dice game for 1-4 players\n";
        std::cout << "***********************************************************************\n";

        do {

            // asking for the number of players from the user

            std::cout << "How many players? (1-4): ";
            std::cin >> numPlayers;


            if (numPlayers > 4)  // if more than 4 players are entered
            {
                std::cout << "YO! Just becuase it has extra functionalities does not mean that it can hold more than 4 people, try 4 or less." << std::endl;
            }


            else if (numPlayers < 1)
            {
                std::cout << "YO! How can players negative, atleast have a single player." << std::endl;
            }
        }
        while (numPlayers < 1 || numPlayers > 4);

        for (int i = 0; i < numPlayers; i++)
        {
            // creating objects of players in the heap and adding them in the vector

            std::string playerName;

            std::cout << "Enter player's name: ";
            std::cin >> playerName;

            Player* newPlayer = new Player();

            newPlayer->setName(playerName);


            players.push_back(newPlayer);
        }


        int currentPlayerIndex = 0;
        bool gameRunning = true;

        while (gameRunning)
        {

            playTurn(currentPlayerIndex);
            currentPlayerIndex = (currentPlayerIndex + 1) % players.size();

            // checking if some player is winning or not --> The logic is simple:
            // if the flag (gamWon) is true and the position of the player is of the winner then that player is the winner
            // then when the winner is declared, we call the declare winnerfunctions and then the standins of the leaders

            if (gameWon && currentPlayerIndex == currentWinnerIndex)
            {
                declareWinner();
                gameRunning = false;
            }

            // checking if the playerVector is empty so that we can terminate the game.
            if (players.empty())
            {
                std::cout << "No players left. Game over.\n";
                gameRunning = false;
            }
        }

        displayFinalStandings();

        char response;
        do {

            // this is a simple q/a type script which will ask the user after the game finishes or when both players quit to play game again
            // well but if the players will quit the game this shouldn't make sense but anyways just to be sure that the user did not click exit by mistake

            std::cout << "Would you like to play again? (y/n): ";
            std::cin >> response;

            if (response == 'y')
            {
                playAgain = true;
            }

            else if (response == 'n')
            {
                playAgain = false;
            }

            else
            {
                std::cout << "Invalid argument. Please enter 'y' for yes or 'n' for no.\n";
            }
        }
        while (response != 'y' && response != 'n');
    }
}


// THe function which runs the farkle game and performs the necessary options, for ver11, this is still a bit buggy on the scoring side

void Application::playTurn(int playerIndex) {

    Player* player = players[playerIndex];  // Get the current player
    std::vector<Die*> playerDice = player->getDice();  // Get player's dice
    bool turnOver = false;

    std::cout << "\n**************************************************************************************\n";
    std::cout << "It’s your turn, " << player->getName() << "!\n";

    while (!turnOver) {
        // Display current scores and dice info
        std::cout << "**************************************************************************************\n";
        for (int i = 0; i < players.size(); i++)
        {
            std::cout << players[i]->getName() << "   Total: " << players[i]->getTotalScore()
                      << "   Current: " << players[i]->getCurrentScore()
                      << "   Dice left: " << calculateDiceLeft(players[i]->getDice()) << std::endl;
        }
        std::cout << "**************************************************************************************\n";
        std::cout << "Would you like to [q]uit, [r]oll, or [s]core ?: ";

        char choice;
        std::cin >> choice;

        if (choice == 'q')
        {
            /*
             * what this part does is, it gets the user details if the user chooses to quit, and as we learned in class to follow best practice,
             * we will first go to the first index of the vector and then go to the player's location in the vector to clear the encapsuled player.
             */

            std::cout << "It has been an honour playing with you, " << player->getName() << ". Goodbye as you choose to [q]uit" << std::endl;
            players.erase(players.begin() + playerIndex);
            turnOver = true;
        }

        else if (choice == 'r')
        {
            // here what we do is we roll the diec
            playerDice = rollDice(playerDice);
            showDice(playerDice);

            if (checkForFarkle(playerDice))
            {
                /*
                * this is the part where we check if the player has farkled and we perfom functionalities such as resertting
                * the dice and resetting the current score
                */

                std::cout << "Well there, " << /*(*player).getName()*/ player->getName() << " you have farkled, a bit sad innit?" << std::endl;
                player->resetCurrentScore();
                player->resetDice();
                turnOver = true;
            }

            else
            {
                /*
                 * if the player decides not to quit, then carry on with the regular flow such as selecting the dice, and scoring process.
                 */

                playerDice = selectDice(playerDice);
                int pointsEarnedThisRoll = calculateScore(playerDice);  // Calculate points only for this roll

                player->resetCurrentScore();  // Ensure current score starts from 0 every roll
                player->addCurrentScore(pointsEarnedThisRoll);  // Add points for this roll only to the current score

                /*
                std::cout << "\nPoints earned this roll: " << pointsEarnedThisRoll << "\n";

                                /// these are meant just for debugging purpose /// because there was an initial bug where the scoring was messed up
                                thanks to the C-Lion De-Bugger this was fixed

                std::cout << "Total current score: " << player->getCurrentScore() << "\n";  // Show updated score
                 8?  */
            }

        }

        else if (choice == 's')
        {

            // this is the part where the current score gets added to total score

            player->updateTotalScore();

            player->resetCurrentScore();

            player->resetDice();

            //std::cout << player->getName() << " WHY IS YOUR SCORE NOT ADDING TO THE TOTAL SCORE BRAH."; ---> this was also for debugging

            turnOver = true; // make the turn to a finish or en end whatever

        }

        else
        {
            // if something other than p q or s has been entered

            std::cout << "Invalid argument" << std::endl;
        }
    }

    // Check if player has won the game
    if (player->getTotalScore() >= targetScore && !gameWon)
    {

        gameWon = true;
        currentWinnerIndex = playerIndex;

    }
}


/*
 * Although this could have been done in the playTurn function,
 * i think that creating a seperate function for this would look more neat than a big playTurn funcion
 */

void Application::declareWinner() {

    int highestScore = 0;
    Player* winner = nullptr;

    for (int i = 0; i < players.size(); i++)
    {
        // looping throug all the player objects and checking for the highest score
        Player* player = players[i];

        // pointing to the highest scorer
        if (player->getTotalScore() > highestScore)
        {
            highestScore = player->getTotalScore();
            winner = player;
        }
    }

    // displaying the winningg messge here

    std::cout << "\n**************************************************************************************\n";
    std::cout << "Congratulations " << winner->getName() << "! You are the winner with " << winner->getTotalScore() << " points!\n";
    std::cout << "\n**************************************************************************************\n";
}





void Application::displayFinalStandings() {


    /*
     * For this part, i used sort which comes in the algorithm library, i used two resources in order to make this part here they are:
     *
     * https://stackoverflow.com/questions/1380463/how-do-i-sort-a-vector-of-custom-objects
     * https://www.geeksforgeeks.org/sort-algorithms-the-c-standard-template-library-stl/
     */





    sort(players.begin(), players.end(), [](Player* a, Player* b)
         {
             return a->getTotalScore() > b->getTotalScore();
         }
    );

    std::cout << "\n************************************************************\n";
    std::cout << "\t The final standings are as follows:\n\n";

    if (!players.empty())
    {
        std::cout << "And The Winner isssssss:  " << players[0]->getName() << " - " << players[0]->getTotalScore() << " points   (imaginary drumroll)" << std::endl;
    }

    for (int i = 1; i < players.size(); i++) {
        std::cout << "Player: " << players[i]->getName() << " - " << players[i]->getTotalScore() << " points" << std::endl;
    }

    std::cout << "************************************************************\n";
}

std::vector<Die*> Application::rollDice(std::vector<Die*> playerDice) {

    // this function just checks if the dice is unlocked and if it is then rolles it, by rilling it means that put random no between 1 and 6

    for (int i = 0; i < playerDice.size(); i++)
    {

        if (playerDice[i]->getIsRollable())
        {
            playerDice[i]->roll();
        }
    }
    return playerDice;
}

std::vector<Die*> Application::selectDice(std::vector<Die*> playerDice) {

    // this is the part where the player chooses the dice from the ones diplayed

    std::string selectedDice;

    std::cout << "Select dice numbers without spaces, dice numbers are on the left and they have been mentioned . Press enter to continue : ";
    std::cin >> selectedDice;

    std::vector<Die*> tempDice = playerDice;

    for (int i = 0; i < selectedDice.length(); i++)
    {
        int dieIndex = selectedDice[i] - '1';   /*
                                                 *  This part was used from an articles which shows how to use ascii arithmetic
                                                 *  https://thelinuxcode.com/use-ascii-cpp/
                                                 */

        if (dieIndex >= 0 && dieIndex < 6)
        {
            tempDice[dieIndex]->setIsRollable(false);
        }

        else
        {
            std::cout << "Man, really, select a valid die!! \n";
        }
    }

    return tempDice;
}


// this function checks wether the user has fakrled or not

bool Application::checkForFarkle(std::vector<Die*> playerDice) {


    int diceCount[7] = {0}; // we use 7 here as we want to include 6 as well if we use 6 then we only have 0,1,2,3,4,5 --> so it leads to confusion

    for (int i = 0; i < playerDice.size(); i++)
    {
        if (playerDice[i]->getIsRollable())
        {
            diceCount[playerDice[i]->getValue()]++;
        }
    }

    if (diceCount[1] > 0 || diceCount[5] > 0)
    {
        return false;
    }

    for (int i = 1; i <= 6; i++)
    {
        if (diceCount[i] >= 3)
        {
            return false;
        }
    }

    return true;
}


//this is the function to calculate the score from the dices

int Application::calculateScore(std::vector<Die*> playerDice) {

    int scoreForThisRoll = 0;  // This will hold the score for the current roll, again, ---> this is only for debugging purposes
    int diceValueCount[7] = {0};  // To count occurrences of each die value (1 to 6)

    // Count the dices that were locked in this roll
    for (int i = 0; i < playerDice.size(); i++)
    {
        if (!playerDice[i]->getIsRollable())
        {
            diceValueCount[playerDice[i]->getValue()]++;
        }
    }


    bool flag = true;
    for (int i = 1; i <= 6; i++)
    {
        if (diceValueCount[i] != 1)
        {
            flag = false;
            break;
        }
    }

    if (flag)
    {
        return 1500;  // 1-6 = 1500 pts
    }


    int pairs = 0;
    for (int i = 1; i <= 6; i++)
    {
        if (diceValueCount[i] == 2)
        {
            pairs++;
        }
    }
    if (pairs == 3)
    {
        return 1500;  // three pairs = 1500 pts
    }

    for (int i = 1; i <= 6; i++)
    {
        if (diceValueCount[i] == 6)
        {
            return 3000;  // six are same = 3000 pts
        }

        else if (diceValueCount[i] == 5)
        {
            scoreForThisRoll += 2000;  // five are same = 2000pts
            diceValueCount[i] -= 5;
        }

        else if (diceValueCount[i] == 4)
        {
            scoreForThisRoll += 1000;  // four are same = 1000 pts
            diceValueCount[i] -= 4;
        }

        else if (diceValueCount[i] == 3)
        {
            if (i == 1)
            {
                scoreForThisRoll += 1000;  // three 1 = 1000
            }

            else
            {
                scoreForThisRoll += i * 100;  // three of any other number = 100 x number
            }
            diceValueCount[i] -= 3;
        }
    }

    // score 1 = 100pts
    scoreForThisRoll += diceValueCount[1] * 100;

    // score 5 = 50 pts
    scoreForThisRoll += diceValueCount[5] * 50;

    return scoreForThisRoll;  // Return the calculated score for this roll or throw whatver we can call this
}


int Application::calculateDiceLeft(std::vector<Die*> playerDice) {

    int diceLeft = 0;
    for (int i = 0; i < playerDice.size(); i++)
    {
        if (playerDice[i]->getIsRollable()) diceLeft++;
    }           // this one is straight forward, it just loops through the dice vector and finds the ones who are unlocked using the bool and loop
    return diceLeft;
}


void Application::showDice(std::vector<Die*> playerDice) {

    // this goes through each dice and checks if locked or unlocked, if it is locked then we print x

    for (int i = 0; i < playerDice.size(); i++)
    {
        std::cout << "Dice " << (i + 1) << ": ";

        if (!playerDice[i]->getIsRollable())
        {
            std::cout << "x";  // Show 'x' for locked dice
        }

        else
        {
            std::cout << playerDice[i]->getValue();  // Show the dice value
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}