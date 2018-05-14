
#ifndef __TABLE_H__
#define __TABLE_H__



#include "cardfactory.h"
#include "player.h"
#include "discardpile.h"
#include "tradearea.h"

class Table
{
public:
    Table();
    Table(std::istream& in, CardFactory * CF);
    Player* createP1(std::string name);
    Player* createP2(std::string name);
    Player* getP1();
    Player* getP2();
    friend std::ostream& operator<< (std::ostream& out, const Table& T);
    bool win(std::string& name);
    void print(std::ostream& out);

    void drawCard(Player* P);
    void discardFromHand(Player* P, int index);
    TradeArea* fillTradeArea();
    bool attemptTrade(Player* P, std::string cardName);
    TradeArea* getTradeArea();
    void emptyTradeArea();
    //void takeTrade(Player* P);

private:
    CardFactory* CF;
    Player* P1;
    Player* P2;
    Deck* D;
    DiscardPile* DP;
    TradeArea* TA;
};

#endif
