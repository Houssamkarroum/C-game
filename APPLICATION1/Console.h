#pragma once
#include <fstream> // For file input/output
#include <string>
#include "ShapeList.h"

class Console
{
private:
    
    int lastScore;
    int topScore;

public:
    void console_game();
    int getLastScore() const;
    int getTopScore() const;
    void setTopScore(int score);
    void updateScores(); // Method to update the score
    void readScoresFromFile(const std::string& filename);
    void writeScoresToFile(const std::string& filename); 
    void createScoresFile(const std::string& filename); 
    void exitYN(void);
    void pauseALL(void);
    void welcomeToTetriseGame();
    
    void gameOverScreen();
    void youWinScreen();
    void setColor(int color);
    void AfficheC(void);
    void afficheScore(ShapeList);
    void afficheshapes(Shape , Shape);
    void affichelist(ShapeList);
    void afficheTimer();
    void welcomeAnimation();
    void gotoxy(int x, int y);
};


