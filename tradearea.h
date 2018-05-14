
#ifndef __TRADEAREA_H__
#define __TRADEAREA_H__

#include <list>
#include <string>
//#include <typeinfo>

#include "gemstones.h"
#include "cardfactory.h"

class TradeArea
{
public:
    TradeArea();
    TradeArea(std::istream& in, CardFactory* CF);
    TradeArea& operator+=(Card* C);
    bool legal(Card* C);
    Card* trade(std::string cardName);
    int numCards();
    std::list<Card *> getAllCards();
    friend std::ostream& operator<< (std::ostream& out, const TradeArea& TA);
private:
    std::list<Card *> cards;
};



#endif
