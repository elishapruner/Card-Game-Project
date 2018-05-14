
#ifndef __DECK_H__
#define __DECK_H__

#include <vector>

#include "gemstones.h"
#include "cardfactory.h"

class CardFactory;
class Card;

class Deck : public std::vector<Card*>
{
public:
    Deck();
    Deck(std::istream& in, CardFactory* CF);
    Card* draw();
    friend std::ostream& operator<< (std::ostream& out, const Deck& D);
private:



};

#endif
