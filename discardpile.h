
#ifndef __DISCARDPILE__
#define __DISCARDPILE__

#include <vector>

#include "cardfactory.h"
#include "gemstones.h"

class DiscardPile
{
public:
    DiscardPile();
    DiscardPile(std::istream& in, CardFactory* CF);
    DiscardPile& operator+=(Card* C);
    Card* pickUp();
    Card* top();
    void print(std::ostream& out);
    friend std::ostream& operator<<(std::ostream& out, const DiscardPile& DP);
private:
    std::vector<Card*> cards;

};



#endif
