#ifndef SFML_H
#define SFML_H

#include <SFML/Graphics.hpp>
#include "shapelist.h"
#include "Console.h"

class SFMLGraphics {
private:
    sf::RenderWindow window;
    void displayScore(sf::Text&, sf::RectangleShape&, sf::Font&, int, int);
    void displayTime(sf::Text&, sf::RectangleShape&, sf::Font&, int);
    void displayArrows(sf::RenderWindow&);
    void displayCurrentShape(sf::Text&, sf::RectangleShape&, sf::Font&);
    void displayNextShape(sf::Text&, sf::RectangleShape&, sf::Font&);
    void displayShapeList(sf::RenderWindow&);
    sf::Color getColorFromIndex(int);
    sf::Drawable* createSFMLShape(const Shape&);
    ShapeList shapeList;
    Console console;
        
public:
    void display();
    void menu();
};

#endif
