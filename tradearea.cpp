
#include "tradearea.h"

/*
    default constructor
*/
TradeArea::TradeArea() {

}

/*
    constructor for restoring from file
*/
TradeArea::TradeArea(std::istream& in, CardFactory* CF) {
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
    += operator to add card to trade area
*/
TradeArea& TradeArea::operator+= (Card* C) {
    cards.push_back(C);
    return *this;
}

/*
    test if a card is legal to be added to the trade area
    this only applies to moving card from discard pile to trade area
*/
bool TradeArea::legal(Card* C) {
    for (std::list<Card*>::iterator it = cards.begin(); it != cards.end(); it++) {
        if ((*it)->getName() == C->getName()) {
            return true;
        }
    }
    return false;
}

/*
    removes a card from trade area by name
    returns null if named card does not exist
*/
Card* TradeArea::trade(std::string cardName) {
    Card* C;
    for (std::list<Card*>::iterator it = cards.begin(); it != cards.end(); it++) {
        if ((*it)->getName() == cardName) {
            C = *it;
            cards.erase(it);
            return C;
        }
    }
    return NULL;
    // raise exception when not found?
}

int TradeArea::numCards() {
    return cards.size();
}

std::list<Card *> TradeArea::getAllCards() {
    return cards;
}

/*
    for both displaying to console and saving to file
*/
std::ostream& operator<< (std::ostream& out, const TradeArea& TA) {
    out << TA.cards.size();
    std::list<Card*> cards = TA.cards;
    for (std::list<Card*>::iterator it = cards.begin(); it != cards.end(); it++) {
        out << " ";
        (*it)->print(out);
    }
    return out;
}

