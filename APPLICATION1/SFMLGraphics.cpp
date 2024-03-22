// sfml.cpp

#include "SFMLGraphics.h"
#include <iostream>
using namespace std;

SFMLGraphics::SFMLGraphics() : window(sf::VideoMode(800, 600), "SFML Shapes") {}

sf::Color SFMLGraphics::getColorFromIndex(int colorIndex) {
    switch (colorIndex) {
    case RED:
        return sf::Color::Red;
    case BLUE:
        return sf::Color::Blue;
    case GREEN:
        return sf::Color::Green;
    case YELLOW:
        return sf::Color::Yellow;
    default:
        return sf::Color::White; // Default color
    }
}

sf::Drawable* SFMLGraphics::createSFMLShape(const Shape& shape) {
    sf::Drawable* sfmlShape = nullptr;

    switch (shape.type) {
    case SQUARE:
        sfmlShape = new sf::RectangleShape(sf::Vector2f(50, 50));
        break;
    case CIRCLE:
        sfmlShape = new sf::CircleShape(25);
        break;
    case TRIANGLE:
        // Implement triangle shape creation
        break;
    case RECTANGLE:
        sfmlShape = new sf::RectangleShape(sf::Vector2f(80, 40));
        break;
    default:
        break;
    }

    if (sfmlShape != nullptr) {
        sf::Transformable* transformableShape = dynamic_cast<sf::Transformable*>(sfmlShape);
        if (transformableShape != nullptr) {
            transformableShape->setPosition(shape.position);
        }
        static_cast<sf::Shape*>(sfmlShape)->setFillColor(getColorFromIndex(shape.color));
    }

    return sfmlShape;
}


void SFMLGraphics::run() {
    // Seed the random number generator
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Create a ShapeList object
    ShapeList shapeList;
    // Set initial score variables
    int currentScore = 0;
    int topScore = 0;
    Shape currentShape = { std::rand() % 4, std::rand() % 4 };
    Shape nextShape = { std::rand() % 4, std::rand() % 4 };

    // Main loop
    while (window.isOpen()) {
        // Generate random current and next shapes
        

        // Clear the window
       /* window.clear();*/

        // Draw current and next shapes using SFML
        sf::Drawable* currentDrawable = createSFMLShape(currentShape);
        sf::Drawable* nextDrawable = createSFMLShape(nextShape);

        if (currentDrawable != nullptr && nextDrawable != nullptr) {
            // Set positions for the shapes
            sf::Vector2f currentPosition(100, 100); // Adjust position as needed
            sf::Vector2f nextPosition(300, 100); // Adjust position as needed

            // Cast to sf::Transformable to set positions
            sf::Transformable* currentTransformable = dynamic_cast<sf::Transformable*>(currentDrawable);
            sf::Transformable* nextTransformable = dynamic_cast<sf::Transformable*>(nextDrawable);

            if (currentTransformable && nextTransformable) {
                currentTransformable->setPosition(currentPosition);
                nextTransformable->setPosition(nextPosition);
            }

            // Draw current and next shapes
            window.draw(*currentDrawable);
            window.draw(*nextDrawable);

            // Clean up dynamically allocated memory
          
        }

        // Display the window
        window.display();

        // Handle user input
        bool shapeAdded = false;
        sf::Event event;
        cout << "h1";
        
        while (window.pollEvent(event)==sf::Event::KeyPressed) {
            
            cout << "h2";
            currentShape = nextShape;
            nextShape = { std::rand() % 4, std::rand() % 4 };
                std::cout << "h3";
            if (event.type == sf::Event::Closed) {
                std::cout << "h7";
                // Update and save scores before exiting
                shapeList.setTopScore(topScore);
                shapeList.writeScoresToFile("scores.txt"); // Save scores to file
                window.close();
            }
           
                if (event.key.code == sf::Keyboard::Escape) {
                    // Update and save scores before exiting
                    shapeList.setTopScore(topScore);
                    shapeList.writeScoresToFile("scores.txt"); // Save scores to file
                    window.close();
                }
                else if (event.key.code == sf::Keyboard::Right) {
                    // Add the next shape to the end of the list
                    shapeList.addToEnd(nextShape);
                    shapeAdded = true;
                }
                else if (event.key.code == sf::Keyboard::Left) {
                    // Add the next shape to the beginning of the list
                    shapeList.addToBeginning(nextShape);
                    shapeAdded = true;
                }
            
          
        }
        std::cout << "h4";

        // Check for duplicates and remove them
        shapeList.removeNodesWithSameColorOrType(currentScore);

        // Update top score if necessary
        if (currentScore > topScore) {
            topScore = currentScore;
        }

        // Update current score
        currentScore += shapeList.getLastScore();
    }
}




