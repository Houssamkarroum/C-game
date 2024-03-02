//#include "SFMLGraphics.h"
//#include <iostream>
//SFMLGraphics::SFMLGraphics() {
//    window.create(sf::VideoMode(800, 600), "SFML Game");
//
//    if (!font.loadFromFile("arial.ttf")) {
//        std::cout << "Failed to load font file!" << std::endl;
//    }
//
//    scoreText.setFont(font);
//    scoreText.setCharacterSize(24);
//    scoreText.setFillColor(sf::Color::White);
//    scoreText.setPosition(10, 10);
//}
//
//void SFMLGraphics::drawShape(Shape shape) {
//    // Implement drawing logic for shapes using SFML
//}
//
//void SFMLGraphics::drawScore(int score) {
//    scoreText.setString("Score: " + std::to_string(score));
//    window.draw(scoreText);
//}
//
//void SFMLGraphics::display() {
//    window.display();
//}
//
//bool SFMLGraphics::isOpen() {
//    return window.isOpen();
//}
//
//void SFMLGraphics::clear() {
//    window.clear();
//}
//
//void SFMLGraphics::close() {
//    window.close();
//}
