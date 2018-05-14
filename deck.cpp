
#include "deck.h"

/*
    default constructor
    actually does not do anything special
*/
Deck::Deck() {
}

/*
    constructor for restoring from save file
*/
Deck::Deck(std::istream& in, CardFactory* CF) {
    int size;
    in >> size;
    char cardType;
    Card* C;
    for (int i = 0; i < size; i++)
    {
        in >> cardType;
        C = CF->createCard(cardType);
        this->push_back(C);
    }
}

/*
    removes one card and gives it to caller
*/
Card* Deck::draw() {
    Card* C = this->back();
    this->pop_back();
    return C;
}

/*
    stream insertion operation
*/
std::ostream& operator<< (std::ostream& out, const Deck& D) {
    out << D.size();
    for (int i = 0; i < D.size(); i++) {
        out << " ";
        D.at(i)->print(out);
    }
    return out;
}
