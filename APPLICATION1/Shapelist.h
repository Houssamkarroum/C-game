#ifndef SHAPE_LIST_H
#define SHAPE_LIST_H


#include <fstream> // For file input/output
#include <string>
#include <SFML/Graphics.hpp>
#include <map>

// Define integer constants for shape type
const int SQUARE = 0;
const int CIRCLE = 1;
const int TRIANGLE = 2;
const int RECTANGLE = 3;

// Define integer constants for color
const int RED = 0;
const int BLUE = 1;
const int GREEN = 2;
const int YELLOW = 3;


// Define struct for Shape
struct Shape {
    int type;
    int color;
    sf::Vector2f position;  
};

// Define struct for Node

struct Node {
    Shape data;
    Node* next;
    Node* prev;
    Node* nextcouleur;
    Node* prevcouleur;
    Node* nextforme;
    Node* prevforme;
};

// Define class for ShapeList
class ShapeList {

private:
    Node* head;
    Node* tail;
    int lastScore;
    int topScore;

public:
    Node* headcolor[4];
    Node* headshape[4];
    ShapeList();
    ~ShapeList();
    void addToBeginning(Shape shape);
    void addToEnd(Shape shape);
    void displayList();
    
    void removeNodesWithSameColorOrType(int& score);

    Node* getHead() const;
    int getLastScore() const;
    int getTopScore() const;
    void setTopScore(int score);
    void updateScores(); // Method to update the score
    void readScoresFromFile(const std::string& filename);
    void writeScoresToFile(const std::string& filename);
    void createScoresFile(const std::string& filename);
    // Method to return the score
};
 
#endif // SHAPE_LIST_H
