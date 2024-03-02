#include "ShapeList.h"
#include <iostream>

ShapeList::ShapeList() : head(nullptr), tail(nullptr), lastScore(0), topScore(0) {
    readScoresFromFile("scores.txt"); // Read scores from file when creating ShapeList
}

ShapeList::~ShapeList() {
    // Implémentez ici la logique du destructeur pour libérer la mémoire si nécessaire
    Node* current = head;
    while (current) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

void ShapeList::addToBeginning(Shape shape) {
    Node* newNode = new Node{ shape, head, nullptr };
    if (head)
        head->prev = newNode;
    head = newNode;
    if (!tail)
        tail = head;
}

void ShapeList::addToEnd(Shape shape) {
    Node* newNode = new Node{ shape, nullptr, tail };
    if (tail)
        tail->next = newNode;
    tail = newNode;
    if (!head)
        head = tail;
}

void ShapeList::displayList() {
    Node* current = head;
    while (current) {
        std::cout << "Shape: " << current->data.type << ", Color: " << current->data.color << std::endl;
        current = current->next;
    }
}
void ShapeList::checkPatterns(int& score) {
    if (head == nullptr || head->next == nullptr || head->next->next == nullptr) {
        // If the list contains fewer than three elements, there are no patterns to check
        return;
    }

    Node* current = head;
    Node* prev = nullptr;

    // Traverse the list
    while (current != nullptr && current->next != nullptr && current->next->next != nullptr) {
        // Check if there are three consecutive pieces with the same type or color
        if ((current->data.type == current->next->data.type && current->next->data.type == current->next->next->data.type) ||
            (current->data.color == current->next->data.color && current->next->data.color == current->next->next->data.color)) {
            // Remove the three consecutive pieces
            Node* temp = current->next->next->next;
            delete current->next->next;
            delete current->next;
            if (prev == nullptr) {
                // If the deleted pieces were at the beginning of the list
                head = temp;
                if (temp) {
                    temp->prev = nullptr; // Update the prev pointer of the new head
                }
            }
            else {
                // Update the pointers
                prev->next = temp;
                if (temp) {
                    temp->prev = prev;
                }
            }
            // Update the score
            score += 300; // Adjust as needed
            current = temp;
        }
        else {
            // Move to the next node
            prev = current;
            current = current->next;
        }
    }
}


Node* ShapeList::getHead() const {
    return head;
}

void ShapeList::updateScores() {
    // Update the scores
    if (lastScore > topScore) {
        topScore = lastScore;
        writeScoresToFile("scores.txt"); // Write updated scores to file
    }
}

int ShapeList::getLastScore() const {
    return lastScore;
}

int ShapeList::getTopScore() const {
    return topScore;
}

void ShapeList::readScoresFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        if (std::getline(file, line)) {
            lastScore = std::stoi(line); // Read last score from the first line
        }
        if (std::getline(file, line)) {
            topScore = std::stoi(line); // Read top score from the second line
        }
        file.close();
    }
    else {
        std::cout << "Unable to open file: " << filename << std::endl;
    }
}
// Implémentation de la fonction setTopScore
void ShapeList::setTopScore(int score) {
    topScore = score;
}
// Implémentation de la fonction writeScoresToFile
void ShapeList::writeScoresToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << lastScore << "\n"; // Write last score on the first line
        file << topScore << "\n";  // Write top score on the second line
        file.close();
    }
    else {
        std::cout << "Unable to open file: " << filename << std::endl;
    }
}


void ShapeList::createScoresFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Failed to create scores file: " << filename << std::endl;
    }
    else {
        file.close();
        std::cout << "Scores file created successfully: " << filename << std::endl;
    }
}
