#include <iostream>
#include <cstdlib> // for rand() function
#include <ctime>   // for time() function
#include "ShapeList.h"

// Function to convert shape type and color to ASCII art
std::string shapeToASCII(int type, int color) {
    // Define ASCII representations for different shapes and colors
    // Customize these as needed
    const std::string shapes[] = { "■", "●", "▲", "□" };
    const std::string colors[] = { "\033[0;31m", "\033[0;34m", "\033[0;32m", "\033[0;33m" };

    // Get the ASCII representation based on shape type and color
    std::string shapeASCII = shapes[type];
    std::string colorASCII = colors[color];

    return colorASCII + shapeASCII + "\033[0m"; // Reset text color to default after shape
}

int main() {
    // Seed the random number generator
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Create a ShapeList object
    ShapeList shapeList;

    // Load scores from file
    shapeList.readScoresFromFile("scores.txt");

    // Variables to track scores
    int currentScore = 0;
   
    

    // Main loop
    while (true) {
        // Generate random current and next shapes
        Shape currentShape = { std::rand() % 4, std::rand() % 4 };
        Shape nextShape = { std::rand() % 4, std::rand() % 4 };

        // Display current and next shapes using ASCII art
        std::cout << "Current Shape: " << shapeToASCII(currentShape.type, currentShape.color) << std::endl;
        std::cout << "Next Shape: " << shapeToASCII(nextShape.type, nextShape.color) << std::endl;

        // Ask user to choose where to add the shape
        std::cout << "Enter '1' to add the current shape to the beginning, '2' to add to the end, or '0' to exit: ";
        int choice;
        std::cin >> choice;

        // Check user's choice
        if (choice == 0) {
            // Update and save scores before exiting
            shapeList.updateScores();
            shapeList.writeScoresToFile("scores.txt"); // Save scores to file

            break;
        }
        else if (choice == 1) {
            // Add the current shape to the beginning of the list
            shapeList.addToBeginning(currentShape);

           
        }
        else if (choice == 2) {
            // Add the current shape to the end of the list
            shapeList.addToEnd(currentShape);
            
        }
        else {
            std::cout << "Invalid choice. Please enter '1', '2', or '0'." << std::endl;
            continue; // Skip the rest of the loop if choice is invalid
        }
        // Display the updated list of shapes
        shapeList.displayList();
        // Check for duplicates and remove them
        shapeList.checkPatterns(currentScore);
        if (currentScore > shapeList.getTopScore()) {
            shapeList.setTopScore(currentScore);
            }

        // Update and display current score
        currentScore += shapeList.getLastScore();
        std::cout << "Current Score: " << currentScore << std::endl;
    }

    // Display highest score
    std::cout << "Highest Score: " << shapeList.getTopScore() << std::endl;

    return 0;
}


