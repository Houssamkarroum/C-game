#include "ShapeList.h"
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "console.h"
using namespace std;
ShapeList::ShapeList() : head(nullptr), tail(nullptr), lastScore(0), topScore(0) , size(0) {
    readScoresFromFile("scores.txt"); // Read scores from file when creating ShapeList
}

void swappos(Node* a, Node* b) {
    if (a == nullptr || b == nullptr) {
        // Handle the error, e.g., by returning from the function
        return;
    }
    Shape temp = a->data;
    a->data = b->data;
    b->data = temp;
}

void ShapeList::shiftcolor(int a) {
    if (a > 3) {
        return;
    }
    // get head jouj merate    
    Node* current = getHead();
    Node* current1 = getHead();
    // get head dyal list khasa b couleur
    while (current !=nullptr && current->data.color != a) {
        current = current->next;
        current1 = current1->next;
    }
    Node* tail = nullptr;
    // get tail dyal list khasa b couleur
    while (current1 != nullptr && current1->nextcouleur != nullptr) {
        current1 = current1->nextcouleur;
        tail = current1;
    }


    /*Node* tail = tailcoleur;
    Node* current = headcoleur;*/
    // b9a nswapi kola mera m3a element b numbre iteration
    while (current != tail) {
        swappos(current, tail);
        current = current->nextcouleur;
    }
    this->establishFormLinks();
}

void ShapeList::establishColorLinks() {
    // Iterate through the list to establish color links
    Node* current = getHead();
    while (current != nullptr) {
        // Find the next shape with the same color
        Node* nextSameColor = current->next;
        while (nextSameColor != nullptr && nextSameColor->data.color != current->data.color) {
            nextSameColor = nextSameColor->next;
        }
        // Establish the link if found
        current->nextcouleur = nextSameColor;
        if (nextSameColor != nullptr) {
            nextSameColor->prevcouleur = current;
        }
        // Move to the next shape
        current = current->next;
    }
}

void ShapeList::establishFormLinks() {
    // Iterate through the list to establish form links
    Node* current = getHead();
    while (current != nullptr) {
        // Find the next shape with the same form
        Node* nextSameForm = current->next;

        while (nextSameForm != nullptr && nextSameForm->data.type != current->data.type) {
            nextSameForm = nextSameForm->next;
        }
        // Establish the link if found
        current->nextforme = nextSameForm;
        if (nextSameForm != nullptr) {
            nextSameForm->prevforme = current;
        }
        // Move to the next shape
        current = current->next;
    }
}


void ShapeList::shiftform(int a) {
    if (a > 3) {
        return;
    }
    // get head jouj merate
    Node* current = getHead();
    Node* current1 = getHead();
    // get head dyal list khasa b form
    while (current != nullptr &&  current->data.type != a) {
        current = current->next;
        current1 = current1->next;
    }
    Node* tail = nullptr;
    // get tail dyal list khasa b form
    while (current1 != nullptr &&  current1->nextforme != nullptr) {
        current1 = current1->nextforme;
        tail = current1;
    }
    /*Node* tail = tailcoleur;
    Node* current = headcoleur;*/
    // b9a nswapi kola mera m3a element b numbre iteration
    while (current != tail) {
        swappos(current, tail);
        current = current->nextforme;
    }
    this->establishColorLinks();
}


void ShapeList::addToBeginning(Shape shape) {
    size++;
    Console console;
    Node* newNode = new Node{ shape, head, nullptr , nullptr ,nullptr };
    if (head)
        head->prev = newNode;
    head = newNode;
    if (!tail)
        tail = head;

    int count1 = 0, count2 = 0;
    Node* current = head->next;
    while (current != nullptr) {

        if (count1 == 0)
        {

            if (current->data.color == newNode->data.color) {
                newNode->nextcouleur = current;
                current->prevcouleur = newNode;
                count1 = 1;

            }
        }

        if (count2 == 0)
        {


            if (current->data.type == newNode->data.type) {
                newNode->nextforme = current;
                current->prevforme = newNode;
                count2 = 1;

            }
        }

        current = current->next;
    }
}

void ShapeList::InitLastScore() {
    lastScore = 0;
}
void ShapeList::displaySameFormsList(int form)  {
    Node* current = head;
    std::cout << "Shapes with the same form (" << form << "): ";
    while (current != nullptr) {
        if (current->data.type == form) {
            std::cout << "(" << current->data.color << ", " << current->data.type << ") ";
        }
        current = current->next;
    }
    std::cout << std::endl;
}

void ShapeList::displaySameColorsList(int color)  {
    Node* current = head;
    std::cout << "Shapes with the same color (" << color << "): ";
    while (current != nullptr) {
        if (current->data.color == color) {
            std::cout << "(" << current->data.color << ", " << current->data.type << ") ";
        }
        current = current->next;
    }
    std::cout << std::endl;
}


void ShapeList::addToEnd(Shape shape) {
    size++;
    Node* newNode = new Node{ shape, nullptr, tail , nullptr ,nullptr };
    if (tail)
        tail->next = newNode;
    tail = newNode;
    if (!head)
        head = tail;

    Node* current = tail->prev;
    int count1 = 0, count2 = 0;
    while (current != nullptr) {
        if (count1 == 0) {
            if (current->data.color == newNode->data.color) {
                newNode->prevcouleur = current;
                current->nextcouleur = newNode;
                count1 = 1;

            }
        }

        if (count2 == 0) {
            if (current->data.type == newNode->data.type) {
                newNode->prevforme = current;
                current->nextforme = newNode;

                count2 = 1;

            }
        }


        current = current->prev;
    }
}

void ShapeList::displayList() {
    Node* current = head;
    while (current) {
        std::cout << "Shape: " << current->data.type << ", Color: " << current->data.color << std::endl;
        current = current->next;
    }
}

void ShapeList::setHead(Node* node) {
    head = node;
}
void ShapeList::removeNodesWithSameColorOrType() {
    if (head == nullptr || head->next == nullptr || head->next->next == nullptr) {
        // If the list contains fewer than three elements, there are no patterns to check
        return;
    }

    Node* current = head;
    while (current != nullptr && current->next != nullptr && current->next->next != nullptr) {

        // Check if there are three consecutive pieces with the same type or color
        if ((current->data.type == current->next->data.type && current->next->data.type == current->next->next->data.type) ||
            (current->data.color == current->next->data.color && current->next->data.color == current->next->next->data.color)) {

            Node* first = current;
            Node* second = first->next;
            Node* third = second->next;

            // Update the head pointer to skip the first three nodes
            if (first == head) {
                head = third->next;
                if (head)
                    head->prev = nullptr; // Update the prev pointer of the new head
                // Update the next and prev pointers of the color/form lists in the beginning
                if (first->nextcouleur)
                    first->nextcouleur->prevcouleur = nullptr;
                if (first->nextforme)
                    first->nextforme->prevforme = nullptr;
                if (second->nextcouleur)
                    second->nextcouleur->prevcouleur = nullptr;
                if (second->nextforme)
                    second->nextforme->prevforme = nullptr;
                if (third->nextcouleur)
                    third->nextcouleur->prevcouleur = nullptr;
                if (third->nextforme)
                    third->nextforme->prevforme = nullptr;

            }
            else { 
                first->prev->next = third->next; // Update the next pointer of the previous node
                if (third->next) {
                    third->next->prev = first->prev; // Update the prev pointer of the next node
                    // Update the next and prev pointers of the color/form lists in the middle
                    if (first->nextcouleur && first->prevcouleur) {
                        first->nextcouleur->prevcouleur = first->prevcouleur;
                        first->prevcouleur->nextcouleur = first->nextcouleur;
                    }
                    else if (first->nextcouleur) {
                        first->nextcouleur->prevcouleur = nullptr;
                    }
                    else {
                        first->prevcouleur->nextcouleur = nullptr;
                    }
                    if (first->nextforme && first->prevforme) {
                        first->nextforme->prevforme = first->prevforme;
                        first->prevforme->nextforme = first->nextforme;
                    }
                    else if (first->nextforme) {
                        first->nextforme->prevforme = nullptr;
                    }
                    else {
                        first->prevforme->nextforme = nullptr;
                    }
                    if (second->nextcouleur && second->prevcouleur) {
                        second->nextcouleur->prevcouleur = second->prevcouleur;
                        second->prevcouleur->nextcouleur = second->nextcouleur;
                    }
                    else if (second->nextcouleur) {
                        second->nextcouleur->prevcouleur = nullptr;
                    }
                    else {
                        second->prevcouleur->nextcouleur = nullptr;
                    }
                    if (second->nextforme && second->prevforme) {
                        second->nextforme->prevforme = second->prevforme;
                        second->prevforme->nextforme = second->nextforme;
                    }
                    else if (second->nextforme) {
                        second->nextforme->prevforme = nullptr;
                    }
                    else {
                        second->prevforme->nextforme = nullptr;
                    }

                    if (third->nextcouleur && third->prevcouleur) {
                        third->nextcouleur->prevcouleur = third->prevcouleur;
                        third->prevcouleur->nextcouleur = third->nextcouleur;
                    }
                    else if (third->nextcouleur) {
                        third->nextcouleur->prevcouleur = nullptr;
                    }
                    else {
                        third->prevcouleur->nextcouleur = nullptr;
                    }
                    if (third->nextforme && third->prevforme) {
                        third->nextforme->prevforme = third->prevforme;
                        third->prevforme->nextforme = third->nextforme;
                    }
                    else if (third->nextforme) {
                        third->nextforme->prevforme = nullptr;
                    }
                    else {
                        third->prevforme->nextforme = nullptr;
                    }

                }
                else {
                    tail = first->prev;
                    // Update the next and prev pointers of the color/form lists in the end
                    if (first->prevcouleur)
                        first->prevcouleur->prevcouleur = nullptr;
                    if (first->prevforme)
                        first->prevforme->nextforme = nullptr;
                    if (second->prevcouleur)
                        second->prevcouleur->prevcouleur = nullptr;
                    if (second->prevforme)
                        second->prevforme->nextforme = nullptr;
                    if (third->prevcouleur)
                        third->prevcouleur->prevcouleur = nullptr;
                    if (third->prevforme)
                        third->prevforme->nextforme = nullptr;
                }
            }

            // Move to the next node to continue checking for patterns
            current = third->next;


            // Delete the first three nodes
            delete first;
            delete second;
            delete third;

            // Update the score
            setlastscore(10);
            size -= 3;
        }
        else {
            // Move to the next node
            current = current->next;
        }
    }
}

void ShapeList::setlastscore(int score) {
    lastScore+= score;
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


ShapeList::~ShapeList() {
    // Implémentez ici la logique du destructeur pour libérer la mémoire si nécessaire
    /*Node* current = head;
    Node* next = nullptr;
    while (current && current->next) {

        next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;*/
}