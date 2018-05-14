
#include "table.h"

/*
    default constructor
*/
Table::Table()
{
    CF = CardFactory::getFactory();
    D = new Deck();
    *D = CF->getDeck();
    DP = new DiscardPile();
    TA = new TradeArea();
}

/*
    Player can be created after the constructor
*/
Player* Table::createP1(std::string name) {
    P1 = new Player(name);
    return P1;
}

/*
    Player can be created after the constructor
*/
Player* Table::createP2(std::string name) {
    P2 = new Player(name);
    return P2;
}

Player* Table::getP1() {
    return P1;
}

Player* Table::getP2() {
    return P2;
}

/*
    constructor for restoring from save game
*/
Table::Table(std::istream& in, CardFactory* CF)
{
    CF->deleteAllCards();
    P1 = new Player(in, CF);
    P2 = new Player(in, CF);
    D = new Deck(in, CF);
    DP = new DiscardPile(in, CF);
    TA = new TradeArea(in, CF);
}

/*
    for saving to file
*/
void Table::print(std::ostream& out)
{
    out << *P1 << std::endl;
    P1->printHand(out, true);
    out << std::endl;
    out << *P2 << std::endl;
    P2->printHand(out, true);
    out << std::endl;
    out << *D << std::endl;
    DP->print(out);
    out << std::endl;
    out << *TA;
}

/*
    for displaying to console
*/
std::ostream& operator<< (std::ostream& out, const Table& T)
{
    out << "Player 1" << std::endl;
    out << *(T.P1) << std::endl;
    T.P1->printHand(out, false);
    out << " " << T.P1->handSize() << std::endl;
    out << "Player 2" << std::endl;
    out << *(T.P2) << std::endl;
    T.P2->printHand(out, false);
    out << " " << T.P2->handSize() << std::endl;
    out << "Discard Pile " << *(T.DP) << std::endl;
    out << "Trade Area " << *(T.TA);
    return out;
}

/*
    check win condition
*/
bool Table::win(std::string& name)
{
    if (D->size() > 0)
    {
        return false;
    }
    else
    {
        if (P1->getNumCoins() > P2->getNumCoins())
        {
            name = P1->getName();
        }
        else if (P2->getNumCoins() > P1->getNumChains())
        {
            name = P2->getName();
        }
        else
        {
            name = "X";
        }
        return true;
    }
}

/*
    helpers to main flow
*/
void Table::drawCard(Player* P) {
    Card* C = D->draw();
    P->addCard(C);
}

/*
helpers to main flow
*/
void Table::discardFromHand(Player* P, int index) {
    Card* C = P->removeFromHand(index);
    (*DP) += C;
}

/*
    helpers to main flow
*/
TradeArea* Table::fillTradeArea() {
    for (int i = 0; i < 3; i++) {
        (*TA) += D->back();
        D->pop_back();
    }
    while (DP->top() != NULL && TA->legal(DP->top())) {
        (*TA) += DP->pickUp();
    }
    return TA;
}

/*
    helpers to main flow
*/
bool Table::attemptTrade(Player* P, std::string cardName) {
    Card* C = TA->trade(cardName);
    if (C == NULL) {
        return false;
    }
    else
    {
        P->playCard(C);
    }
}

TradeArea* Table::getTradeArea() {
    return TA;
}

void Table::emptyTradeArea() {
    std::list<Card*> cards = TA->getAllCards();
    for (std::list<Card*>::iterator it = cards.begin(); it != cards.end(); it++) {
        (*DP) += *it;
        TA->trade((*it)->getName());
    }
}

