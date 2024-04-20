#include "SFMLGraphics.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

enum MenuResult { consoleGame, graphicGame, Exit};

void SFMLGraphics::displayScore(sf::Text& text, sf::RectangleShape& background, sf::Font& font, int currentScore,int topScore) {
    // Create a rectangle shape to act as the background
    background.setSize(sf::Vector2f(200, 100)); // Increased height to accommodate two lines of text
    background.setFillColor(sf::Color(100, 100, 200)); // Gray color for the background
    background.setPosition(10, 10); // Position at the top left corner

    // Set up the text object
    text.setFont(font); // Set the font
    // Concatenate strings to display score and top score
    text.setString("Score: " + std::to_string(currentScore) + "\nTop Score: " + std::to_string(topScore));
    text.setCharacterSize(20); // Set the character size
    text.setFillColor(sf::Color::White); // Set the fill color

    // Center the text inside the rectangle
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    text.setPosition(background.getPosition().x + background.getSize().x / 2.0f,
        background.getPosition().y + background.getSize().y / 2.0f);
}

void SFMLGraphics::displayTime(sf::Text& text, sf::RectangleShape& background, sf::Font& font, int time) {
	// Create a rectangle shape to act as the background
	background.setSize(sf::Vector2f(200, 100)); // Increased height to accommodate two lines of text
	background.setFillColor(sf::Color(100, 100, 200)); // Gray color for the background
	background.setPosition(790, 10); // Position at the top left corner

	// Set up the text object
	text.setFont(font); // Set the font
	// Concatenate strings to display score and top score
	text.setString("Time left: " + std::to_string(time));
	text.setCharacterSize(20); // Set the character size
	text.setFillColor(sf::Color::White); // Set the fill color

	// Center the text inside the rectangle
	sf::FloatRect textBounds = text.getLocalBounds();
	text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
	text.setPosition(background.getPosition().x + background.getSize().x / 2.0f,
		background.getPosition().y + background.getSize().y / 2.0f);
}

void SFMLGraphics::displayArrows(sf::RenderWindow& window) {
    // Create the arrow shape
    sf::ConvexShape rightArrow;
    sf::ConvexShape leftArrow;
    rightArrow.setPointCount(3); // Set the number of points for the arrow
    leftArrow.setPointCount(3);

    // Define the points of the left arrow shape
    rightArrow.setPoint(0, sf::Vector2f(0, 0));
    rightArrow.setPoint(1, sf::Vector2f(0, 50));
    rightArrow.setPoint(2, sf::Vector2f(50, 25));

    // Define the points of the right arrow shape
    leftArrow.setPoint(0, sf::Vector2f(50, 0));
    leftArrow.setPoint(1, sf::Vector2f(0, 25));
    leftArrow.setPoint(2, sf::Vector2f(50, 50));

    // Set the position and color of the left arrow
    rightArrow.setPosition(950, 330);
    rightArrow.setFillColor(sf::Color::White);

    // Set the position and color of the left arrow
    leftArrow.setPosition(0, 330);
    leftArrow.setFillColor(sf::Color::White);

    // Draw the arrow shape to the window
    window.draw(rightArrow);
    window.draw(leftArrow);
}

void SFMLGraphics::displayCurrentShape(sf::Text& text, sf::RectangleShape& background, sf::Font& font) {
    // Create a rectangle shape to act as the background
    background.setSize(sf::Vector2f(200, 100)); // Increased height to accommodate two lines of text
    background.setFillColor(sf::Color(100, 100, 200)); // Gray color for the background
    background.setPosition(10, 170); // Position at the top left corner

    // Set up the text object
    text.setFont(font); // Set the font
    // Concatenate strings to display score and top score
    text.setString("Current Shape: " );
    text.setCharacterSize(20); // Set the character size
    text.setFillColor(sf::Color::White); // Set the fill color

    // Center the text inside the rectangle
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    text.setPosition(background.getPosition().x + background.getSize().x / 2.0f,
        background.getPosition().y + background.getSize().y / 2.0f);
}

void SFMLGraphics::displayNextShape(sf::Text& text, sf::RectangleShape& background, sf::Font& font) {
    // Create a rectangle shape to act as the background
    background.setSize(sf::Vector2f(200, 100)); // Increased height to accommodate two lines of text
    background.setFillColor(sf::Color(100, 100, 200)); // Gray color for the background
    background.setPosition(650, 170); // Position at the top left corner

    // Set up the text object
    text.setFont(font); // Set the font
    // Concatenate strings to display score and top score
    text.setString("Next Shape: ");
    text.setCharacterSize(20); // Set the character size
    text.setFillColor(sf::Color::White); // Set the fill color

    // Center the text inside the rectangle
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    text.setPosition(background.getPosition().x + background.getSize().x / 2.0f,
        background.getPosition().y + background.getSize().y / 2.0f);
}

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
        sfmlShape = new sf::ConvexShape();
        static_cast<sf::ConvexShape*>(sfmlShape)->setPointCount(3);
        static_cast<sf::ConvexShape*>(sfmlShape)->setPoint(0, sf::Vector2f(25, 0));
        static_cast<sf::ConvexShape*>(sfmlShape)->setPoint(1, sf::Vector2f(0, 50));
        static_cast<sf::ConvexShape*>(sfmlShape)->setPoint(2, sf::Vector2f(50, 50));
        break;
    case RECTANGLE:
        sfmlShape = new sf::ConvexShape();
        static_cast<sf::ConvexShape*>(sfmlShape)->setPointCount(4);
        static_cast<sf::ConvexShape*>(sfmlShape)->setPoint(0, sf::Vector2f(25, 0));
        static_cast<sf::ConvexShape*>(sfmlShape)->setPoint(1, sf::Vector2f(0, 25));
        static_cast<sf::ConvexShape*>(sfmlShape)->setPoint(2, sf::Vector2f(25, 50));
        static_cast<sf::ConvexShape*>(sfmlShape)->setPoint(3, sf::Vector2f(50, 25));
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

void SFMLGraphics::displayShapeList(sf::RenderWindow& window) {
    sf::Vector2f position(10, 450); // Starting position to draw shapes
    const float shapeSpacing = 10.0f; // Spacing between shapes

    // Iterate over the shape list
    Node* current = shapeList.getHead();
    while (current != nullptr) {
        // Create SFML shape corresponding to the current shape node
        sf::Drawable* sfmlShape = createSFMLShape(current->data);
        if (sfmlShape != nullptr) {
            // Set position for the shape
            sf::Transformable* transformableShape = dynamic_cast<sf::Transformable*>(sfmlShape);
            if (transformableShape != nullptr) {
                transformableShape->setPosition(position);
            }

            // Draw the shape to the window
            window.draw(*sfmlShape);

            // Clean up dynamically allocated memory
            delete sfmlShape;

            // Update position for the next shape
            position.x += 50 + shapeSpacing; // Adjust spacing as needed
            if (position.x + 100 > window.getSize().x) {
				position.x = 10;
				position.y += 100 + shapeSpacing; // Adjust spacing as needed
			}
        }

        // Move to the next shape node
        current = current->next;
    }
}

void SFMLGraphics::display() {
    // Create window
    sf::RenderWindow window(sf::VideoMode(1000, 600), "Tetris");

    // Seed the random number generator
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Set initial score variables
    int currentScore = 0;
    int topScore = 0;
    Shape currentShape = { std::rand() % 4, std::rand() % 4 };
    Shape nextShape = { std::rand() % 4, std::rand() % 4 };

    // Load the font from a file
    sf::Font font;
    if (!font.loadFromFile("C:/Users/LEGEND/Desktop/c++/APPLICATION1/fonts/test.ttf")) {
        // Error loading font
        std::cerr << "Failed to load font" << std::endl;
        return;
    }

    // Create a rectangle shape and text object to display the score and the time left
    sf::RectangleShape score_background;
    sf::RectangleShape time_background;
    sf::RectangleShape currentShapebackground;
    sf::RectangleShape nextShapebackground;

    sf::Text score_text;
    sf::Text time_text;
    sf::Text currentShape_text;
    sf::Text nextShape_text;

    displayScore(score_text, score_background, font, currentScore, topScore);
    displayTime(time_text, time_background, font, 0);
    displayCurrentShape(currentShape_text, currentShapebackground, font);
    displayNextShape(nextShape_text, nextShapebackground, font);

    // Create drawable objects for current and next shapes
    sf::Drawable* currentDrawable = createSFMLShape(currentShape);
    sf::Drawable* nextDrawable = createSFMLShape(nextShape);

    // Main loop
    while (window.isOpen()) {
        // Clear the window
        window.clear();

        // Draw the background rectangle
        window.draw(score_background);
        window.draw(time_background);
        window.draw(currentShapebackground);
        window.draw(nextShapebackground);

        // Draw the text
        window.draw(score_text);
        window.draw(time_text);
        window.draw(currentShape_text);
        window.draw(nextShape_text);

        // Draw the arrows
        displayArrows(window);

        // Handle user input
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                // Close the window if the close button is clicked
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    // Close the window if Escape key is pressed
                    window.close();
                }
                else if (event.key.code == sf::Keyboard::Right) {
                    // Add the next shape to the end of the list
                    shapeList.addToEnd(currentShape);
                    // Update current shape
                    currentShape = nextShape;
                    // Generate new random shape for next iteration
                    nextShape = { std::rand() % 4, std::rand() % 4 };
                    // Update drawable objects for current and next shapes
                    delete currentDrawable;
                    delete nextDrawable;
                    currentDrawable = createSFMLShape(currentShape);
                    nextDrawable = createSFMLShape(nextShape);
                }
                else if (event.key.code == sf::Keyboard::Left) {
                    // Add the next shape to the beginning of the list
                    shapeList.addToBeginning(currentShape);
                    // Update current shape
                    currentShape = nextShape;
                    // Generate new random shape for next iteration
                    nextShape = { std::rand() % 4, std::rand() % 4 };
                    // Update drawable objects for current and next shapes
                    delete currentDrawable;
                    delete nextDrawable;
                    currentDrawable = createSFMLShape(currentShape);
                    nextDrawable = createSFMLShape(nextShape);
                }
            }
        }

        // Display the list of shapes
        displayShapeList(window);

        // Draw current and next shapes using SFML
        if (currentDrawable != nullptr && nextDrawable != nullptr) {
            // Set positions for the shapes
            sf::Vector2f currentPosition(250, 200); // Adjust position as needed
            sf::Vector2f nextPosition(900, 200); // Adjust position as needed

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
        }

        // Update and display scores
        currentScore += shapeList.getLastScore();
        // Your code for displaying the score here

        // Check for duplicates and remove them
        shapeList.removeNodesWithSameColorOrType(currentScore);

        // Update top score if necessary
        if (currentScore > topScore) {
            topScore = currentScore;
        }

        // Display the window
        window.display();
    }

    // Clean up dynamically allocated memory
    delete currentDrawable;
    delete nextDrawable;
}

MenuResult showMenu(sf::RenderWindow& window) {
    // Load font
    sf::Font font;
    if (!font.loadFromFile("C:/Users/LEGEND/Desktop/c++/APPLICATION1/fonts/test.ttf")) {
        std::cerr << "Failed to load font." << std::endl;
        return Exit;
    }

    // Play menu item
    sf::Text consoleText;
    consoleText.setFont(font);
    consoleText.setString("Play With The Console");
    consoleText.setCharacterSize(24);
    consoleText.setFillColor(sf::Color::White);
    consoleText.setPosition(100, 100);

    sf::Text graghicsText;
    graghicsText.setFont(font);
    graghicsText.setString("Play With The Graphics");
    graghicsText.setCharacterSize(24);
    graghicsText.setFillColor(sf::Color::White);
    graghicsText.setPosition(100, 150);

    // Exit menu item
    sf::Text exitText;
    exitText.setFont(font);
    exitText.setString("Exit");
    exitText.setCharacterSize(24);
    exitText.setFillColor(sf::Color::White);
    exitText.setPosition(100, 200);

    // Render loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return Exit;
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (consoleText.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                        window.close();
                        return consoleGame;
                    }
                    else if (exitText.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                        window.close();
                        return Exit;
                    }
                    else if (graghicsText.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                        window.close();
                        return graphicGame;
                    }
                }
            }
        }

        // Clear the window
        window.clear();

        // Draw menu items
        window.draw(consoleText);
        window.draw(graghicsText);
        window.draw(exitText);

        // Display
        window.display();
    }
    return Exit;
}

void SFMLGraphics::menu() {
    // Create window
    sf::RenderWindow window(sf::VideoMode(600, 300), "Menu");

    // Show menu
    MenuResult result = showMenu(window);

    // Process menu result
    switch (result) {
    case consoleGame:
        console.console_game();
        break;
    case graphicGame:
        display();
        break;
    case Exit:
        exit(0);
        break;
    }
}