//
// Created by Ishan Sharma on 6/9/2024.
//


#include "MainMenu.h"
#include "Application.h"

void runMenu() {
    do {
        int userChoice;
        std::cout << " --- Programming Fundamental Concepts ---" << std::endl;
        std::cout << "1. End The Program" << std::endl;
        std::cout << "2. Display Game Rules" << std::endl;
        std::cout << "3. Play FARKLE" << std::endl;
        std::cout << "4. Display Inflection Report" << std::endl;
        std::cout << std::endl;
        std::cout << "Which option would you like to choose (1 to 4): ";
        std::cin >> userChoice;

        if (userChoice == 1)
        {
            std::cout << "Thanks for using our program." << std::endl;
            break;

        }

        else if (userChoice == 2)
        {
            displayRules();

        }

        else if (userChoice == 3)
        {
            Application farkle;
            farkle.startGame();
        }

        else if (userChoice == 4)
        {
            std::cout << "Here is the report" << std::endl;
            displayReport();
        }

        else
        {
            std::cout << "Invalid Option" << std::endl;
        }
    }
    while (true);
}

void displayRules(){

    std::fstream fileReader; // creating an instance of the fstream which will read the rules
    std::string fileContent;

    fileReader.open("gameRulesAsgn2.txt");

    if(fileReader.is_open() == true)
    {
        while(fileReader.eof() == false) // reading till the file ends
        {
            std::getline(fileReader, fileContent); // using getline to read lines instead of words
            fileContent.erase(fileContent.size()-1);
            /*
             * After the running the code in debugger mode, as the file was only reading the last line from the file, it was found that
             * there was a carriage return character at the end of each line '/r', so the code line above removes the last character which
             * is the '/r' carriage return character and displays the text on the screen.
             *  source: https://stackoverflow.com/questions/2528995/remove-r-from-a-string-in-c
             *
             */
            std::cout << fileContent << std::endl;
        }
        fileReader.close(); // closing the file
    }
    else
    {
        std::cout << "YO! Can not find the file you are looking for!" << std::endl;
    }


}


void displayReport(){

    std::fstream fileReader; // creating an instance of the fstream which will read the rules
    std::string fileContent;

    fileReader.open("reportA2.txt");

    if(fileReader.is_open() == true)
    {
        while(fileReader.eof() == false) // reading till the file ends
        {
            std::getline(fileReader, fileContent); // using getline to read lines instead of words
            fileContent.erase(fileContent.size()-1);
            /*
             * After the running the code in debugger mode, as the file was only reading the last line from the file, it was found that
             * there was a carriage return character at the end of each line '/r', so the code line above removes the last character which
             * is the '/r' carriage return character and displays the text on the screen.
             *  source: https://stackoverflow.com/questions/2528995/remove-r-from-a-string-in-c
             *
             */
            std::cout << fileContent << std::endl;
        }
        fileReader.close(); // closing the file
    }
    else
    {
        std::cout << "YO! Can not find the file you are looking for!" << std::endl;
    }


}
