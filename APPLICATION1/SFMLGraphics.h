// sfml.h

#ifndef SFML_H
#define SFML_H

#include <SFML/Graphics.hpp>
#include "shapelist.h"

class SFMLGraphics {
private:
    sf::RenderWindow window;
    ShapeList shapeList;
    sf::Color getColorFromIndex(int colorIndex);
    sf::Drawable* createSFMLShape(const Shape& shape);

public:
    SFMLGraphics();
    void run();
};

#endif // SFML_H
