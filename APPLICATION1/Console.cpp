#include "Console.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <chrono>
#include <thread>
#include "ShapeList.h"
#include "Console.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "SFMLGraphics.h"
using namespace std;

void Console::console_game() {
    system("cls");
    //PlaySound(TEXT("launch.wav"), NULL, SND_SYNC);
    

    // Seed the random number generator
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Create a ShapeList object
    ShapeList shapeList;
    Console console;console.setTopScore(0);
    console.AfficheC();
    /* console.afficheTimer();*/
    /*Load scores from file*/
    console.readScoresFromFile("consolescores.txt");

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
        std::cout << "Top Score: " << console.getTopScore() << std::endl;
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
        std::cout << "                                                                                                                                      ";
        // Check user's choice
        if (choice == 0) {
            // Update and save scores before exiting
            console.updateScores();
            shapeList.writeScoresToFile("scores.txt"); // Save scores to file
            break;
        }
        else if (choice == 1) {
            // Add the current shape to the beginning of the list
            shapeList.addToBeginning(currentShape);
            //PlaySound(TEXT("sound.wav"), NULL, SND_SYNC);

        }
        else if (choice == 2) {
            // Add the current shape to the end of the list
            shapeList.addToEnd(currentShape);
            //PlaySound(TEXT("sound.wav"), NULL, SND_SYNC);

        }
        else if (choice == 3) {
            int a;
            cout << "Enter the color you want to shift: ";
            cin >> a;

            shapeList.shiftcolor(a);


        }
        else if (choice == 4) {
            int a;
            cout << "Enter the form you want to shift: ";
            cin >> a;

            shapeList.shiftform(a);


        }
        else {
            //PlaySound(TEXT("chosefailed.wav"), NULL, SND_SYNC);
            std::cout << "Invalid choice. Please enter '1', '2', or '0'." << std::endl;
            continue; // Skip the rest of the loop if choice is invalid
        }

        // Display the updated list of shapes


        // Check for duplicates and remove them
        shapeList.removeNodesWithSameColorOrType(currentScore);

        console.affichelist(shapeList);

        if (currentScore > shapeList.getTopScore()) {
            console.setTopScore(currentScore);
        }

        // Update and display current score
        currentScore += console.getLastScore();

        nextShapetmp = nextShape;
        count = 1;

    }
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

std::string shapeToASCII(int type, int color) {
    // Define ASCII representations for different shapes and colors
    // Customize these as needed
    const std::string shapes[] = { "S", "C", "T", "R" };
    const std::string colors[] = { "\033[0;31m", "\033[0;34m", "\033[0;32m", "\033[0;33m" };

    // Get the ASCII representation based on shape type and color
    std::string shapeASCII = shapes[type];
    std::string colorASCII = colors[color];

    return colorASCII + shapeASCII  +  "\033[0m" ; // Reset text color to default after shape
}


void Console::afficheshapes(Shape currentShape, Shape nextShape) {
    // Display the shapes in the list
    gotoxy(22, 13);
    std::cout << " " << shapeToASCII(currentShape.type, currentShape.color) << std::endl;
    gotoxy(114, 13);
    std::cout << " " << shapeToASCII(nextShape.type, nextShape.color) << std::endl;

}

void afficheshape(Shape currentShape, int x) {
    // Display the shapes in the list
    gotoxy(x, 26);
    std::cout << "  " << shapeToASCII(currentShape.type, currentShape.color);


}
void Console::affichelist(ShapeList shapeList) {

    // Display the list of shapes
    int x = 15;
    for (int i = 0; i < 15; i++)
    {
        gotoxy(x, 26);
        std::cout << "             " ;
           x += 3;
    }
    Node* current = shapeList.getHead();
    x = 15;
    while (current) {
        afficheshape(current->data, x);
        current = current->next;
        x += 3;
    }
}

void Console::updateScores() {
    // Update the scores
    if (lastScore > topScore) {
        topScore = lastScore;
        writeScoresToFile("scores.txt"); // Write updated scores to file
    }
}

int Console::getLastScore() const {
    return lastScore;
}

int Console::getTopScore() const {
    return topScore;
}

void Console::readScoresFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        if (std::getline(file, line)) {
            lastScore = std::stoi(line); // Read last score from the first line
        }
        if (std::getline(file, line)) {
            topScore = std::stoi(line); // Read top score from the second line
        }
        file.close();
    }
    else {
        std::cout << "Unable to open file: " << filename << std::endl;
    }
}
// Implémentation de la fonction setTopScore
void Console::setTopScore(int score) {
    topScore = score;
}

// Implémentation de la fonction writeScoresToFile
void Console::writeScoresToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << lastScore << "\n"; // Write last score on the first line
        file << topScore << "\n";  // Write top score on the second line
        file.close();
    }
    else {
        std::cout << "Unable to open file: " << filename << std::endl;
    }
}


void Console::createScoresFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Failed to create scores file: " << filename << std::endl;
    }
    else {
        file.close();
        std::cout << "Scores file created successfully: " << filename << std::endl;
    }
} // Method to return the score

void Console::exitYN(void) {
	
}

void Console::pauseALL(void) {
	std::cout << "Press any key to continue...";
	std::cin.get();
	std::cin.get();
}




void Console::gameOverScreen() {
	std::cout << "Game Over!" << std::endl;
}



void Console::setColor(int color) {
	
}

void Console::gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Console::youWinScreen() {
    int x = 25, y = 9;
    gotoxy(x, y++);
    std::cout << "'##:::'##::'#######::'##::::'##::::'##:::::'##:'####:'##::: ##:'####:";
    gotoxy(x, y++);
    std::cout << ". ##:'##::'##.... ##: ##:::: ##:::: ##:'##: ##:. ##:: ###:: ##: ####:";
    gotoxy(x, y++);
    std::cout << ":. ####::: ##:::: ##: ##:::: ##:::: ##: ##: ##:: ##:: ####: ##: ####:";
    gotoxy(x, y++);
    std::cout << "::: ##:::: ##:::: ##: ##:::: ##:::: ##: ##: ##:: ##:: ## ## ##:: ##::";
    gotoxy(x, y++);
    std::cout << "::: ##:::: ##:::: ##: ##:::: ##:::: ##: ##: ##:: ##:: ##. ####::..:::";
    gotoxy(x, y++);
    std::cout << "::: ##:::: ##:::: ##: ##:::: ##:::: ##: ##: ##:: ##:: ##:. ###:'####:";
    gotoxy(x, y++);
    std::cout << "::: ##::::. #######::. #######:::::. ###. ###::'####: ##::. ##: ####:";
    gotoxy(x, y++);
    std::cout << ":::..::::::.......::::.......:::::::...::...:::....::..::::..::....::";
    gotoxy(x, y++);
    gotoxy(x, y++);gotoxy(x, y++);
    system("pause"); // Pause the console so the message can be read
     // Clear the console
}


// Affiche le timer

void Console::afficheTimer(){ 
    int minutes = 1; // Définir le nombre de minutes
    int seconds = 0; // Définir le nombre de secondes

    while (minutes >= 0 && seconds >= 0) {
        // Afficher le timer
        gotoxy(102,4); // Move the cursor to the top-right corner of the console (117, 3)
        std::cout << "Timer: " << (minutes < 10 ? "0" : "") << minutes << ":" << (seconds < 10 ? "0" : "") << seconds << std::endl;

        // Attendre 1 seconde
        std::this_thread::sleep_for(std::chrono::seconds(1));

        // Mettre à jour les minutes et les secondes
        if (seconds == 0) {
            if (minutes > 0) {
                --minutes;
                seconds = 59;
            }
            else {
                break; // Arrêter le compte à rebours si le temps est écoulé
            }
        }
        else {
            --seconds;
        }
    }
   
    //PlaySound(TEXT("timeup.wav"), NULL, SND_SYNC);
    system("cls");
    gotoxy(55, 55);
    std::cout << "Time's up!" << std::endl;
    gotoxy(55, 60);
    gameOverScreen();
    exit(0);
}


// Function to display Tetris ASCII art line by line
void displayTetris() {
    // Tetris ASCII art
    std::string tetrisArt[] = {
        "___________________________________________.___  ____________________",
        "\\__    ___/\\_   _____/\\__    ___/\\______   \\   |/   _____/\\_   _____/",
        "  |    |    |    __)_   |    |    |       _/   |\\_____  \\  |    __)_",
        "  |    |    |        \\  |    |    |    |   \\   |/        \\ |        \\",
        "  |____|   /_______  /  |____|    |____|_  /___/_______  //_______  /",
        "                   \\/                    \\/            \\/         \\/"
    };

    // Display Tetris ASCII art line by line using gotoxy function
    int x = 24; // x-coordinate
    int y = 3; // y-coordinate
    for (const auto& line : tetrisArt) {
        gotoxy(x, y++);
        std::cout << line << std::endl;
    }
    gotoxy(100, 100);
}

 void Console::AfficheC() {

    char niveau[][121] = {
        "########################################################################################################################",
        "#===================|                                                                             |====================#",
        "#                   |                                                                             |                    #",
        "#                   |                                                                             |                    #",
        "#                   |                                                                             |                    #",
        "#                   |                                                                             |                    #",
        "#===================|                                                                             |====================#",
        "#                                                                                                                      #",
        "#                                                                                                                      #",
        "#                                                                                                                      #",
        "#                                                                                                                      #",
        "#                                                                                                                      #",
        "#                                                                                                                      #",
        "# YOUR CURRENT SHAPE :                                                                          YOUR NEXT SHAPE :      #",
        "#                                                                                                                      #",
        "#                                                                                                                      #",
        "#                                                                                                                      #",
        "#                                                                                                                      #",
        "#                                                                                                                      #",
        "#                                                                                                                      #",
        "#                                                                                                                      #",
        "#                                                                                                                      #",
        "#                                                                                                                      #",
        "#                                                                                                                      #",
        "#                                                                                                                      #",
        "#                                                                                                                      #",
        "#                                                                                                                      #",
        "#                                                                                                                      #",
        "#                                                                                                                      #",
        "#                                                                                                                      #",
        "#                                                                                                                      #",
        "#                                                                                                                      #",
        "########################################################################################################################"
    };

    int x = 0, y = 0;
    for (int i = 0; i < 33; i++) {
        gotoxy(x, y++);
        std::cout << niveau[i] << std::endl;
    }
    displayTetris();

}

//void Console::welcomeAnimation() {
//
//    
//    
//    // Display loading message
//    gotoxy(70, 12);
//    std::cout << "\n\n\n\t\tChargement Du Jeu, Veuillez Patienter:\n\n\t\t\t" << std::endl;
//
//    // Display completion message
//    gotoxy(70, 6);
//    std::cout << "\n\t\t\tLe Chargement est COMPLET !" << std::endl;
//
//    // Display continue prompt
//    gotoxy(70, 11);
//    std::cout << "\n\n\n\t\t>Appuyez sur {ENTRER} pour continuer<" << std::endl;
//
//    // Display welcome message
//    std::string welcomeMessage = "\n\n\n\n\t\t Welcome to Tetrise!";
//    int welcomeX = 30, welcomeY = 20;
//    for (char c : welcomeMessage) {
//        gotoxy(welcomeX++, welcomeY);
//        std::cout << c;
//        Sleep(50);
//    }
//
//    // Wait for user input
//    std::cout << "\n\n\n\t Press a key to continue";
//    _getch();
//    system("cls");
//
//    Console c;
//    c.AfficheC();
//    displayTetris();
//    
//
//}


// End of Console.cpp
   