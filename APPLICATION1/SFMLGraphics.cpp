#include "SFMLGraphics.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

enum MenuResult { consoleGame, graphicGame, Exit };

void SFMLGraphics::displayScore(sf::Text& text, sf::Font& font, int currentScore, int topScore) {
    // Set up the text object
    text.setFont(font); // Set the font
    // Concatenate strings to display score and top score
    text.setString("Score: " + std::to_string(currentScore) + "\nTop Score: " + std::to_string(topScore));
    text.setCharacterSize(20); // Set the character size
    text.setFillColor(sf::Color::White); // Set the fill color
    // Set default position
    sf::Vector2f defaultPosition(80, 70); // Example position, change as needed
    // Set the position of the text
    text.setPosition(defaultPosition);
}

void SFMLGraphics::displayTime(sf::Text& text, sf::Font& font, int time) {
	// Set up the text object
	text.setFont(font); // Set the font
	// Concatenate strings to display score and top score
	text.setString("Time left: " + std::to_string(time));
	text.setCharacterSize(20); // Set the character size
	text.setFillColor(sf::Color::White); // Set the fill color
    // Set default position
    sf::Vector2f defaultPosition(750, 70); // Example position, change as needed
    // Set the position of the text
    text.setPosition(defaultPosition);
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

void SFMLGraphics::displayCurrentShape(sf::Text& text, sf::Font& font) {
    // Set up the text object
    text.setFont(font); // Set the font
    // Concatenate strings to display score and top score
    text.setString("Current Shape: ");
    text.setCharacterSize(20); // Set the character size
    text.setFillColor(sf::Color::White); // Set the fill color
    // Set default position
    sf::Vector2f defaultPosition(50, 210); // Example position, change as needed
    // Set the position of the text
    text.setPosition(defaultPosition);
}

void SFMLGraphics::displayNextShape(sf::Text& text, sf::Font& font) {
    // Set up the text object
    text.setFont(font); // Set the font
    // Concatenate strings to display score and top score
    text.setString("Next Shape: ");
    text.setCharacterSize(20); // Set the character size
    text.setFillColor(sf::Color::White); // Set the fill color
    // Set default position
    sf::Vector2f defaultPosition(740, 210); // Example position, change as needed
    // Set the position of the text
    text.setPosition(defaultPosition);
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
    sf::Vector2f position(50, 450); // Starting position to draw shapes
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

void SFMLGraphics::gameOver(sf::Text& gameOverText, sf::Font& font, sf::RenderWindow& window) {
    gameOverText.setFont(font);
    gameOverText.setString("Game Over!");
    gameOverText.setCharacterSize(48);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(360, 250);
	window.draw(gameOverText);
    window.display();
	sf::sleep(sf::seconds(2));
    exit(0);
}

void SFMLGraphics::gamePaused(sf::Text& gamePausedText, sf::Font& font, sf::RenderWindow& window) {
	gamePausedText.setFont(font);
	gamePausedText.setString("Game Paused!");
	gamePausedText.setCharacterSize(40);
	gamePausedText.setFillColor(sf::Color::White);
	gamePausedText.setPosition(360, 250);
	window.draw(gamePausedText);
}

void SFMLGraphics::display() {
    // Create window
    sf::RenderWindow window(sf::VideoMode(1300, 600), "Tetris");

    // Load the background image
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("D:/ENSET/S2/Projet/bg1.png")) {
        std::cerr << "Failed to load background image." << std::endl;
        return;
    }

    // Load the rules image
    sf::Texture rulesTexture;
    if (!rulesTexture.loadFromFile("D:/ENSET/S2/Projet/rules.png")) {
        std::cerr << "Failed to load background image." << std::endl;
        return;
    }

    // Create a sprite for the background and set its texture
    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.scale(sf::Vector2f(0.735, 0.8));

    // Create a sprite for the rules and set its texture
    sf::Sprite rulesSprite;
    rulesSprite.setTexture(rulesTexture);
    rulesSprite.setPosition(sf::Vector2f(1003, 80));
    rulesSprite.scale(sf::Vector2f(0.5, 0.6));

    // Seed the random number generator
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    Shape currentShape = { std::rand() % 4, std::rand() % 4 };
    Shape nextShape = { std::rand() % 4, std::rand() % 4 };

    // Load the font from a file
    sf::Font font;
    if (!font.loadFromFile("C:/Users/LEGEND/Desktop/c++/APPLICATION1/test.ttf")) {
        // Error loading font
        std::cerr << "Failed to load font" << std::endl;
        return;
    }

    // Define time limit and clock
    int timeLimit = 100; // Time limit in seconds
    sf::Clock clock;
    sf::Time totalElapsedTime;
    sf::Time pauseStartTime;

    // Define paused state
    bool paused = false;

    // Define text objects
    sf::Text score_text;
    sf::Text time_text;
    sf::Text currentShape_text;
    sf::Text nextShape_text;
    sf::Text gameOverText;
    sf::Text gamePausedText;
    
    shapeList.InitLastScore();

    displayCurrentShape(currentShape_text, font);
    displayNextShape(nextShape_text, font);

    // Create drawable objects for current and next shapes
    sf::Drawable* currentDrawable = createSFMLShape(currentShape);
    sf::Drawable* nextDrawable = createSFMLShape(nextShape);

    // Main loop
    while (window.isOpen()) {
        // Clear the window
        window.clear();

        // Draw the background image
        window.draw(backgroundSprite);
        // Draw the background rules
        window.draw(rulesSprite);

        // Update and display time left
        sf::Time elapsedTime = clock.restart(); // Restart the clock and get elapsed time
        if (!paused) {
            totalElapsedTime += elapsedTime; // Accumulate total elapsed time
        }
        int secondsLeft = timeLimit - totalElapsedTime.asSeconds();
        displayTime(time_text, font, secondsLeft);

        // Check if time is up
        if (secondsLeft <= 0) {
            gameOver(gameOverText, font, window);
        }

        // Draw the text
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
                if (event.key.code == sf::Keyboard::Q) {
                    // Close the window if Escape key is pressed
                    window.close();
                }
                else if (event.key.code == sf::Keyboard::Right) {
                    // Add the next shape to the end of the list
                    if (shapeList.size < 14) {
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
                    else {
                        gameOver(gameOverText, font, window);
                    }
                }
                else if (event.key.code == sf::Keyboard::Left) {
                    // Add the next shape to the beginning of the list
                    if (shapeList.size < 14) {
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
                    else {
                        gameOver(gameOverText, font, window);
                    }
                }
                else if (event.key.code == sf::Keyboard::P) {
                    paused = true; // Pause the game
                    pauseStartTime = clock.getElapsedTime(); // Record the time when paused
                }
                else if (event.key.code == sf::Keyboard::R) {
                    paused = false; // Resume the game
                    // Subtract the pause duration from total elapsed time
                    totalElapsedTime += clock.getElapsedTime() - pauseStartTime;
                }
            }
        }

        // Check if the game is paused
        if (paused) {
            gamePaused(gamePausedText, font, window);
		}
        
        // Display the list of shapes
        displayShapeList(window); 
        int x = 640;
        for (int i = 0; i < 4; i++)
        {
            displaySameFormsListSFML(window, i , x);
            x += 39;

        }
        x = 830;
        for (int i = 0; i < 4; i++)
        {
            displaySameColorsListSFML(window, i,x);
            x += 39;
        }

        // Draw current and next shapes using SFML
        if (currentDrawable != nullptr && nextDrawable != nullptr) {
            // Set positions for the shapes
            sf::Vector2f currentPosition(900 , 400); // Adjust position as needed
            sf::Vector2f nextPosition(900, 200); // Adjust position as needed

            // Cast to sf::Transformable to set positions
            sf::Transformable* currentTransformable = dynamic_cast<sf::Transformable*>(nextDrawable);
            sf::Transformable* nextTransformable = dynamic_cast<sf::Transformable*>(nextDrawable);

            if (currentTransformable && nextTransformable) {
                currentTransformable->setPosition(currentPosition);
                nextTransformable->setPosition(nextPosition);
            }

            // Draw current and next shapes
            window.draw(*nextDrawable);
            window.draw(*currentDrawable);
            
        }
        // Check for duplicates and remove them
        shapeList.removeNodesWithSameColorOrType();
        shapeList.updateScores();
        displayScore(score_text, font, shapeList.getLastScore(), shapeList.getTopScore());
        window.draw(score_text);
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
    if (!font.loadFromFile("C:/Users/LEGEND/Desktop/c++/APPLICATION1/test.ttf")) {
        std::cerr << "Failed to load font." << std::endl;
        return Exit;
    }

    // Load the background image
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("D:/ENSET/S2/Projet/bg1.png")) {
        std::cerr << "Failed to load background image." << std::endl;
        return Exit;
    }

    // Create a sprite for the background and set its texture
    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.scale(sf::Vector2f(0.4, 0.4));

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
        window.draw(backgroundSprite);
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
    sf::RenderWindow window(sf::VideoMode(540, 300), "Menu");

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