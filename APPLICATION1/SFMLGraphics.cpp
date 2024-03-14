//#include "SFMLGraphics.h"
//
//SFMLGraphics::SFMLGraphics() : window(sf::VideoMode(800, 600), "SFML Game") {
//    if (!font.loadFromFile("arial.ttf")) {
//        // error handling
//    }
//    text.setFont(font);
//    text.setCharacterSize(24);
//    text.setFillColor(sf::Color::White);
//
//    loadTextures();
//}
//
//void SFMLGraphics::display(ShapeList& shapeList, Shape currentShape, Shape nextShape, int currentScore, int topScore) {
//    window.clear();
//
//    // Display current score and top score
//    text.setString("Current Score: " + std::to_string(currentScore));
//    text.setPosition(10, 10);
//    window.draw(text);
//
//    text.setString("Top Score: " + std::to_string(topScore));
//    text.setPosition(10, 40);
//    window.draw(text);
//
//    // Display current and next shapes
//    switch (currentShape.type) {
//    case SQUARE:
//        currentShapeSprite.setTexture(squareTexture);
//        break;
//    case CIRCLE:
//        currentShapeSprite.setTexture(circleTexture);
//        break;
//    case TRIANGLE:
//        currentShapeSprite.setTexture(triangleTexture);
//        break;
//    case RECTANGLE:
//        currentShapeSprite.setTexture(rectangleTexture);
//        break;
//    }
//    currentShapeSprite.setPosition(200, 200);
//    window.draw(currentShapeSprite);
//
//    // Similar process for next shape...
//
//    // Display shape list
//    // You'll need to iterate through the shape list and draw each shape
//
//    window.display();
//}
//
//int SFMLGraphics::getUserChoice() {
//    sf::Event event;
//    while (window.pollEvent(event)) {
//        if (event.type == sf::Event::KeyPressed) {
//            if (event.key.code == sf::Keyboard::Num1)
//                return 1;
//            else if (event.key.code == sf::Keyboard::Num2)
//                return 2;
//            else if (event.key.code == sf::Keyboard::Escape)
//                return 0;
//        }
//    }
//    return -1;
//}
//
//void SFMLGraphics::loadTextures() {
//    // Load textures for shapes
//    // Load squareTexture, circleTexture, triangleTexture, and rectangleTexture
//}
