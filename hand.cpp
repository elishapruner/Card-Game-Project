
#include "hand.h"

/*
    default construtor
    nothing special
*/
Hand::Hand() {
    //cards = *(new std::queue<Card*>());
}

/*
    constructor for use when restoring from save file
*/
Hand::Hand(std::istream& in, CardFactory* CF)
{
    //cards = *(new std::queue<Card*>());
    int size;
    in >> size;
    char cardType;
    Card* C;
    for (int i = 0; i < size; i++)
    {
        in >> cardType;
        C = CF->createCard(cardType);
        cards.push_back(C);
    }
    //std::vector<Card*> CV = cards._Get_container();
    //CV.pop_back();
}

/*
    += operator
    adds card to hand (bottom)
*/
Hand& Hand::operator+= (Card* C)
{
    cards.push_back(C);
    return *this;
}

/*
    removes and returns card from top of hand
*/
Card* Hand::play() {
    Card* C = cards.front();
    cards.pop_front();
    return C;
}

/*
    peaks at the top hard of hand
*/
Card* Hand::top() {
    Card* C = cards.front();
    return C;
}

/*
    index based card removal from hand
    used only using one step in the game when the player can choose to discard one card
*/
Card* Hand::operator[](int index) {
    //std::vector<Card*> CV = cards._Get_container();
    //std::deque<Card*> container = cards._Get_container();
    //Card* C = *(container.begin() + index);
    //container.erase(container.begin() + index);
    Card* C = *(cards.begin() + index);
    cards.erase(cards.begin() + index);
    return C;
}

/*
    allows other parts of the game to get the current hand size
*/
int Hand::getSize() {
    return cards.size();
}

/*
    stream insertion operator
*/
std::ostream& operator<< (std::ostream& out, const Hand& H) {
    //std::vector<Card*> CV = H.cards._Get_container();
    //std::deque<Card*> container = H.cards._Get_container();
    std::deque<Card*> cards = H.cards;
    out << H.cards.size();
    for (std::deque<Card*>::iterator it = cards.begin(); it != cards.end(); it++) {
        out << " ";
        (*it)->print(out);
    }
    return out;
}
