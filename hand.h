
#ifndef __HAND_H__
#define __HAND_H__

#include <vector>
#include <queue>

#include "gemstones.h"
#include "cardfactory.h"

class Hand
{
public:
    Hand();
    Hand(std::istream& in, CardFactory* CF);
    Hand& operator+=(Card* C);
    Card* play();
    Card* top();
    Card* operator[](int index);
    int getSize();
    friend std::ostream& operator<< (std::ostream& out, const Hand& H);
private:
    //std::vector<Card*> cards;
    //std::queue<Card*, std::vector<Card*>> cards;
    std::deque<Card*> cards;
    //std::queue<Card*> cards;
};



#endif
