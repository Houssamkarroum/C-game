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

void console_game() {
    PlaySound(TEXT("launch.wav"), NULL, SND_SYNC);

    // Seed the random number generator
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Create a ShapeList object
    ShapeList shapeList;
    Console console;
    console.AfficheC();
    /* console.afficheTimer();*/
    /*Load scores from file*/
    shapeList.readScoresFromFile("scores.txt");

    // Variables to track scores
    int currentScore = 0;

    Shape nextShapetmp;
    Shape currentShape;
    Shape nextShape;
    int count = 0;

    currentShape = { std::rand() % 4, std::rand() % 4 };

    
    int choice;
    // Main loop
    while (true) {
        console.gotoxy(3, 3);
        std::cout << "Current Score: " << currentScore << std::endl;
        console.gotoxy(3, 4);
        std::cout << "Top Score: " << shapeList.getTopScore() << std::endl;
        // Generate random current and next shapes
        nextShape = { std::rand() % 4, std::rand() % 4 };

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
        else if (choice == 3) {
            Node* samecoleur = shapeList.getHead();
            Node* sameform = shapeList.getHead();
            
 
            int x = 1;
            while (samecoleur->nextcouleur != nullptr) { 
               
                    x+= 1;
                    samecoleur = samecoleur->nextcouleur;
        
                
            }
            int y = 1;
            while (sameform->nextforme != nullptr) {

                y += 1;
                sameform = sameform->nextforme;


            }
            system("cls");
            cout << "x = " << x; cout << "  y  = " << y;



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

    console_game();

    return 0;
}