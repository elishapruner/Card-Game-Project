
#include "discardpile.h"

/*
    default constructor
    nothing special
*/
DiscardPile::DiscardPile() {

}

/*
    constructor for use when retoring from save file
*/
DiscardPile::DiscardPile(std::istream& in, CardFactory* CF) {
    int size;
    in >> size;
    char cardType;
    Card* C;
    for (int i = 0; i < size; i++) {
        in >> cardType;
        C = CF->createCard(cardType);
        cards.push_back(C);
    }
}

/*
    += operator
    for use when adding a card to the discard pile
*/
DiscardPile& DiscardPile::operator+= (Card* C) {
    cards.push_back(C);
    return *this;
}

/*
    picking up a card from the discard pile
    removes a card from the pile's open end and returns it
    returns NULL if pile is empty
*/
Card* DiscardPile::pickUp() {
    if (cards.size() > 0) {
        Card* C = cards.back();
        cards.pop_back();
        return C;
    }
    return NULL;
}

/*
    peeks at the discard pile's open end
    returns NULL if pile is empty
*/
Card* DiscardPile::top() {
    if (cards.size() > 0) {
        Card* C = cards.back();
        return C;
    }
    return NULL;
}

/*
    writes the entire discard pile into the stream
    used for serialization
*/
void DiscardPile::print(std::ostream& out) {
    out << cards.size();
    for (int i = 0; i < cards.size(); i++) {
        out << " ";
        cards.at(i)->print(out);
    }
}

/*
    stream insertion operator
    writes only the top card (at pile's open end) to the stream
*/
std::ostream& operator<<(std::ostream& out, const DiscardPile& DP) {
    if (DP.cards.size() > 1) {
        Card* C = DP.cards.back();
        C->print(out);
    }
    return out;
}
