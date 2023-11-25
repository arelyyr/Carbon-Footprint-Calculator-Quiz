#include <iostream>
#include <string>
#include <limits>
#include "quiz.h" // quiz functions
#include "calculator.h" // calculator functions

// main
int main()
{
    std::string choice;
    bool quitCondition = false;

    std::cout << "\nWelcome! This program is designed to educate you more in terms of Climate Change. The program is made up of two parts. One part being the Climate Change Quiz! This quiz is designed to see what you know, and teach you what you don't know. The other part is our Emissions Calculator! The Calculator is designed to ask a series of questions that'll help determine your CO2 levels, and give you some tips on how to lower that usage!\n";
  
    while (!quitCondition) {
        std::cout << "\nMenu:\n";
        std::cout << "1. Quiz\n";
        std::cout << "2. Calculator\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";
        getline(std::cin, choice);

        // Convert user input to lowercase
        for (auto& c : choice) {
            c = tolower(c);
        }

        // Run corresponding action for user input
        if (choice == "1" || choice == "quiz") {
            // Execute quiz function
            std::cout << "Quiz selected\n\n";
            quizGame();
        }
        else if (choice == "2" || choice == "calculator") {
            // Execute calculator function
            std::cout << "Calculator selected\n\n";
            calculator();
        }
        else if (choice == "3" || choice == "quit" || choice == "exit" || choice == "q") {
            // Exit program
            std::cout << "Exiting program...\n";
            quitCondition = true;
        }
        else {
            // Invalid input
            std::cout << "Invalid choice\n\n";
        }
        
        if (!quitCondition)
        {
          // Clear input buffer
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return 0;
}