#ifndef SFML_H
#define SFML_H

#include <SFML/Graphics.hpp>
#include "shapelist.h"
#include "Console.h"

class SFMLGraphics {
private:
    sf::RenderWindow window;
    void displayScore(sf::Text&, sf::Font&, int, int);
    void displayTime(sf::Text&, sf::Font&, int);
    void displayArrows(sf::RenderWindow&);
    void displayCurrentShape(sf::Text&, sf::Font&);
    void displayNextShape(sf::Text&, sf::Font&);
    void displaySameFormsListSFML(sf::RenderWindow& window, int form ,int x);
    void displaySameColorsListSFML(sf::RenderWindow& window, int form , int x);
    void displayShapeList(sf::RenderWindow&);
    void gameOver(sf::Text&, sf::Font&, sf::RenderWindow&);
    void gamePaused(sf::Text&, sf::Font&, sf::RenderWindow&);
    void YouWin(sf::Text&, sf::Font&, sf::RenderWindow&);
    sf::Color getColorFromIndex(int);
    sf::Drawable* createSFMLShape(const Shape&);
    ShapeList shapeList;
    Console console;

public:
    void display();
    void menu();
};

#endif