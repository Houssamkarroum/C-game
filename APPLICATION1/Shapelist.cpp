#include "ShapeList.h"
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "console.h"

ShapeList::ShapeList() : head(nullptr), tail(nullptr), lastScore(0), topScore(0) {
    readScoresFromFile("scores.txt"); // Read scores from file when creating ShapeList
}

void swappos(Node* a, Node* b) {
    if (a == nullptr || b == nullptr) {
        // Handle the error, e.g., by returning from the function
        return;
    }
	Shape temp = a->data ;
	a->data = b->data;
	b->data = temp;
}

void ShapeList::shiftcolor(int a) {
    // get head jouj merate
    Node* current = getHead();
    Node* current1 = getHead();
    // get head dyal list khasa b couleur
    while (current->data.color != a) {
		current = current->next;
        current1 = current1->next;
	}
    Node* tail = nullptr;
    // get tail dyal list khasa b couleur
    while (current1->nextcouleur != nullptr ) {
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

}

void ShapeList::shiftform(int a) {
    // get head jouj merate
    Node* current = getHead();
    Node* current1 = getHead();
    // get head dyal list khasa b form
    while (current->data.type != a) {
        current = current->next;
        current1 = current1->next;
    }
    Node* tail = nullptr;
    // get tail dyal list khasa b form
    while (current1->nextforme != nullptr) {
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

}


void ShapeList::addToBeginning(Shape shape) {
    Console console;
    Node* newNode = new Node{ shape, head, nullptr , nullptr ,nullptr };
    if (head)
        head->prev = newNode;
    head = newNode;
    if (!tail)
        tail = head;

    int count1 = 0, count2 = 0;
    Node* current = head->next;
    while (current != nullptr ) {
        
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


void ShapeList::addToEnd(Shape shape) {
    Node* newNode = new Node{ shape, nullptr, tail , nullptr ,nullptr };
    if (tail)
        tail->next = newNode;
    tail = newNode;
    if (!head)
      head = tail;
   
    Node* current = tail->prev;
    int count1 = 0 , count2 = 0;
    while (current != nullptr) {
        if(count1==0){
            if (current->data.color == newNode->data.color) {
                newNode->prevcouleur= current;
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

void ShapeList::removeNodesWithSameColorOrType(int &score) {
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
            score += 300;
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