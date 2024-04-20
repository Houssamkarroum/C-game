#include <iostream>
#include <cstdlib> // for rand() function
#include <ctime>   // for time() function
#include "ShapeList.h"
#include <conio.h>
#include "Console.h"
#include <Windows.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "SFMLGraphics.h"
using namespace std;


        if (count == 1) {
            currentShape = nextShapetmp;
        }

        // Display current and next shapes using ASCII art
        console.afficheshapes(currentShape, nextShape);

        // Ask user to choose where to add the shape
        console.gotoxy(7, 50);
        std::cout << "Enter '1' to add the current shape to the beginning, '2' to add to the end, or '0' to exit: ";
        std::cin >> choice;
        console.gotoxy(6, 50);
        std::cout << "                                                                                                                     ";
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
            PlaySound(TEXT("sound.wav"), NULL, SND_SYNC);
            
        }
        else if (choice == 2) {
            // Add the current shape to the end of the list
            shapeList.addToEnd(currentShape);
            PlaySound(TEXT("sound.wav"), NULL, SND_SYNC);
            
        }
        else if (choice == 3) {int a ;
            cout << "Enter the color you want to shift: ";
            cin >> a;

        }else {
            PlaySound(TEXT("chosefailed.wav"), NULL, SND_SYNC);
            std::cout << "Invalid choice. Please enter '1', '2', or '0'." << std::endl;
            continue; // Skip the rest of the loop if choice is invalid
        }

        // Display the updated list of shapes


        // Check for duplicates and remove them
        shapeList.removeNodesWithSameColorOrType(currentScore);

        console.affichelist(shapeList);

        if (currentScore > shapeList.getTopScore()) {
            shapeList.setTopScore(currentScore);
        }

        // Update and display current score
        currentScore += shapeList.getLastScore();

        nextShapetmp = nextShape;
        count = 1;

    }
}







int main() {
    SFMLGraphics app;
    app.menu();


    SFMLGraphics app;
    app.menu();
    return 0;
}