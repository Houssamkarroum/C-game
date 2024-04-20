#include "ShapeList.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "console.h"

ShapeList::ShapeList() : head(nullptr), tail(nullptr), lastScore(0), topScore(0) {
    readScoresFromFile("scores.txt"); // Read scores from file when creating ShapeList
}

//void SwapNodes(Node* itemNbr1, Node* itemNbr2)
//{
//    // Handle if either of the nodes is NULL or if they are the same node
//    if (!itemNbr1 || !itemNbr2 || itemNbr1 == itemNbr2)
//        return;
//
//    // Swap next pointers
//    Node* tempNext = itemNbr1->next;
//    itemNbr1->next = itemNbr2->next;
//    itemNbr2->next = tempNext;
//
//    if (itemNbr1->next)
//        itemNbr1->next->prev = itemNbr1;
//    if (itemNbr2->next)
//        itemNbr2->next->prev = itemNbr2;
//
//    if (itemNbr1->prev == itemNbr2)
//    { // Handling adjacent nodes
//        itemNbr2->prev = itemNbr1->prev;
//        itemNbr1->prev = itemNbr2;
//    }
//    else
//    {
//        Node* tempPrev = itemNbr1->prev;
//        itemNbr1->prev = itemNbr2->prev;
//        itemNbr2->prev = tempPrev;
//    }
//
//    if (itemNbr1->prev)
//        itemNbr1->prev->next = itemNbr1;
//    if (itemNbr2->prev)
//        itemNbr2->prev->prev = itemNbr2;
//
//    // Update head if necessary
//    if (itemNbr1 == Head)
//        Head = itemNbr2;
//    else if (itemNbr2 == Head)
//        Head = itemNbr1;
//
//    // Update tail if necessary
//    if (itemNbr1 == Tail)
//        Tail = itemNbr2;
//    else if (itemNbr2 == Tail)
//        Tail = itemNbr1;
//}

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
    while (current1->nextcouleur != nullptr) {
        current1 = current1->nextcouleur;
        tail = current1;
    }


    /*Node* tail = tailcoleur;
    Node* current = headcoleur;*/
    // b9a nswapi kola mera m3a element b numbre iteration
    while (current != tail) {

        /* swappos(current, tail);*/
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
        /* swappos(current, tail);*/
        current = current->nextforme;
    }

}

void ShapeList::addToBeginning(Shape shape) {

    Node* newNode = new Node{ shape, head, nullptr , nullptr ,nullptr,nullptr,nullptr };
    if (head)
        head->prev = newNode;
    head = newNode;
    if (!tail)
        tail = head;

    newNode->nextcouleur = newNode;
    newNode->prevcouleur = newNode;


    newNode->nextforme = newNode;
    newNode->prevforme = newNode;

    if (headcolor[newNode->data.color]) {
        headcolor[newNode->data.color]->prevcouleur->nextcouleur = newNode;
        newNode->prevcouleur = headcolor[newNode->data.color]->prevcouleur;
        newNode->nextcouleur = headcolor[newNode->data.color];
        headcolor[newNode->data.color]->prevcouleur = newNode;
        headcolor[newNode->data.color] = newNode;
    }
    else {
        headcolor[newNode->data.color] = newNode;
    }

    // forme 
    if (headshape[newNode->data.type]) {
        headshape[newNode->data.type]->prevforme->nextforme = newNode;
        newNode->prevforme = headshape[newNode->data.type]->prevforme;
        newNode->nextforme = headshape[newNode->data.type];
        headshape[newNode->data.type]->prevforme = newNode;
        headshape[newNode->data.type] = newNode;
    }
    else
    {
        headshape[newNode->data.type] = newNode;

    }

}


void ShapeList::addToEnd(Shape shape) {
    Node* newNode = new Node{ shape, nullptr, tail , nullptr ,nullptr, nullptr ,nullptr };
    if (tail)
        tail->next = newNode;
    tail = newNode;
    if (!head)
        head = tail;

    newNode->nextcouleur = newNode;
    newNode->prevcouleur = newNode;
    newNode->nextforme = newNode;
    newNode->prevforme = newNode;



    if (headcolor[newNode->data.color]) {
        Node* last_color_item = headcolor[newNode->data.color]->prevcouleur;
        last_color_item->nextcouleur->prevcouleur = newNode;
        newNode->nextcouleur = last_color_item->nextcouleur;
        newNode->prevcouleur = last_color_item;
        last_color_item->nextcouleur = newNode;

    }
    else {
        headcolor[newNode->data.color] = newNode;
    }

    // forme 


    if (headshape[newNode->data.type]) {
        Node* last_form_item = headshape[newNode->data.type]->prevforme;
        last_form_item->nextforme->prevforme = newNode;
        newNode->nextforme = last_form_item->nextforme;

        newNode->prevforme = last_form_item;
        last_form_item->nextforme = newNode;


    }
    else
    {
        headshape[newNode->data.type] = newNode;

    }
    // for not comparing it with itself

}

void ShapeList::displayList() {
    Node* current = head;
    while (current) {
        std::cout << "Shape: " << current->data.type << ", Color: " << current->data.color << std::endl;
        current = current->next;
    }
}

void ShapeList::removeNodesWithSameColorOrType(int& score) {
    if (head == nullptr || head->next == nullptr || head->next->next == nullptr) {
        // If the list contains fewer than three elements, there are no patterns to check
        return;
    }
    int a;
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
                if (first->nextcouleur) {
                    a = first->data.color;
                    first->nextcouleur->prevcouleur = headcolor[a]->prevcouleur;
                    headcolor[a]->prevcouleur->nextcouleur = first->nextcouleur;
                    headcolor[a] = first->nextcouleur;
                }
                if (first->nextforme) {
                    a = first->data.type;
                    first->nextforme->prevforme = headshape[a]->prevforme;
                    headshape[a]->prevforme->nextforme = first->nextforme;
                    headshape[a] = first->nextforme;
                }

                if (second->nextcouleur) {
                    a = second->data.color;
                    second->nextcouleur->prevcouleur = headcolor[a]->prevcouleur;
                    headcolor[a]->prevcouleur->nextcouleur = second->nextcouleur;
                    headcolor[a] = second->nextcouleur;
                }
                if (second->nextforme) {
                    a = second->data.type;
                    second->nextforme->prevforme = headshape[a]->prevforme;
                    headshape[a]->prevforme->nextforme = second->nextforme;
                    headshape[a] = second->nextforme;
                }

                if (third->nextcouleur) {
                    a = third->data.color;
                    third->nextcouleur->prevcouleur = headcolor[a]->prevcouleur;
                    headcolor[a]->prevcouleur->nextcouleur = third->nextcouleur;
                    headcolor[a] = third->nextcouleur;
                }
                if (third->nextforme) {
                    a = third->data.type;
                    third->nextforme->prevforme = headshape[a]->prevforme;
                    headshape[a]->prevforme->nextforme = third->nextforme;
                    headshape[a] = third->nextforme;
                }

            }

            else {
                first->prev->next = third->next; // Update the next pointer of the previous node
                if (third->next) {
                    third->next->prev = first->prev; // Update the prev pointer of the next node
                    // Update the next and prev pointers of the color/form lists in the middle
                    if (first->nextcouleur && first->prevcouleur) {
                        first->prevcouleur->nextcouleur = first->nextcouleur;
                        first->prevcouleur->prevcouleur = first->nextcouleur;
                        first->nextcouleur->prevcouleur = first->prevcouleur;
                        first->nextcouleur->nextcouleur = first->prevcouleur;
                        if (first == headcolor[first->data.color])
                            headcolor[first->data.color] = first->nextcouleur;
                    }

                    if (first->nextforme && first->prevforme) {
                        first->prevforme->nextforme = first->nextforme;
                        first->prevforme->prevforme = first->nextforme;
                        first->nextforme->prevforme = first->prevforme;
                        first->nextforme->nextforme = first->prevforme;
                        if (first == headshape[first->data.color])
                            headshape[first->data.color] = first->nextforme;
                    }

                    if (second->nextcouleur && second->prevcouleur) {
                        second->prevcouleur->nextcouleur = second->nextcouleur;
                        second->prevcouleur->prevcouleur = second->nextcouleur;
                        second->nextcouleur->prevcouleur = second->prevcouleur;
                        second->nextcouleur->nextcouleur = second->prevcouleur;
                        if (second == headcolor[second->data.color])
                            headcolor[second->data.color] = second->nextcouleur;
                    }

                    if (second->nextforme && second->prevforme) {
                        second->prevforme->nextforme = second->nextforme;
                        second->prevforme->prevforme = second->nextforme;
                        second->nextforme->prevforme = second->prevforme;
                        second->nextforme->nextforme = second->prevforme;
                        if (second == headshape[second->data.color])
                            headshape[second->data.color] = second->nextforme;
                    }

                    if (third->nextcouleur && third->prevcouleur) {
                        third->prevcouleur->nextcouleur = third->nextcouleur;
                        third->prevcouleur->prevcouleur = third->nextcouleur;
                        third->nextcouleur->prevcouleur = third->prevcouleur;
                        third->nextcouleur->nextcouleur = third->prevcouleur;
                        if (third == headcolor[third->data.color])
                            headcolor[third->data.color] = third->nextcouleur;
                    }

                    if (third->nextforme && third->prevforme) {
                        third->prevforme->nextforme = third->nextforme;
                        third->prevforme->prevforme = third->nextforme;
                        third->nextforme->prevforme = third->prevforme;
                        third->nextforme->nextforme = third->prevforme;
                        if (third == headshape[third->data.color])
                            headshape[third->data.color] = third->nextforme;
                    }
                }

                else {
                    tail = first->prev;

                    // Update the next and prev pointers of the color/form lists in the end
                    if (third->prevforme) {
                        a = third->data.type;
                        third->prevforme->nextforme = headshape[a];
                        headshape[a]->prevforme = third->prevforme;
                    }
                    if (third->prevcouleur) {
                        a = third->data.color;
                        third->prevcouleur->nextcouleur = headcolor[a];
                        headcolor[a]->prevcouleur = third->prevcouleur;
                    }

                    if (second->prevforme) {
                        a = second->data.type;
                        second->prevforme->nextforme = headshape[a];
                        headshape[a]->prevforme = second->prevforme;
                    }
                    if (second->prevcouleur) {
                        a = second->data.color;
                        second->prevcouleur->nextcouleur = headcolor[a];
                        headcolor[a]->prevcouleur = second->prevcouleur;
                    }

                    if (first->prevforme) {
                        a = first->data.type;
                        first->prevforme->nextforme = headshape[a];
                        headshape[a]->prevforme = first->prevforme;
                    }
                    if (first->prevcouleur) {
                        a = first->data.color;
                        first->prevcouleur->nextcouleur = headcolor[a];
                        headcolor[a]->prevcouleur = first->prevcouleur;
                    }
                }
            }

            // Move to the next node to continue checking for patterns
            current = third->next;


            // Delete the three nodes and delete the head pointers of the color/form lists if necessary
            if (first == headshape[first->data.type] && headshape[first->data.type]->nextforme == headshape[first->data.type]) {
                headshape[first->data.type] = nullptr;
            }
            if (first == headcolor[first->data.color] && headcolor[first->data.color]->nextforme == headcolor[first->data.color]) {
                headcolor[first->data.color] = nullptr;
            }
            delete first;


            if (second == headshape[second->data.type] && headshape[second->data.type]->nextforme == headshape[second->data.type]) {
                headshape[second->data.type] = nullptr;
            }
            if (second == headcolor[second->data.color] && headcolor[second->data.color]->nextforme == headcolor[second->data.color]) {
                headcolor[second->data.color] = nullptr;
            }
            delete second;


            if (third == headshape[third->data.type] && headshape[third->data.type]->nextforme == headshape[third->data.type]) {
                headshape[third->data.type] = nullptr;
            }
            if (third == headcolor[third->data.color] && headcolor[third->data.color]->nextforme == headcolor[third->data.color]) {
                headcolor[third->data.color] = nullptr;
            }
            delete third;


            // Update the score
            score += 300;
        }

        else {
            // Move to the next node
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