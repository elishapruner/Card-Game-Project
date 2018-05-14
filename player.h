
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <string>
#include <vector>
#include <iostream>
#include <exception>

#include "chain.h"
#include "cardfactory.h"
#include "gemstones.h"
#include "hand.h"

class Player
{
public:
    Player(std::string& name);
    Player(std::istream&, CardFactory*);
    std::string getName();
    int getNumCoins();
    Player& operator+= (int coins);
    int getMaxNumChains();
    int getNumChains();
    Base_Chain& operator[] (int i);
    void buyThirdChain();
    void printHand(std::ostream& out, bool full);
    int handSize();
    void addCard(Card* C);
    void playTopCard();
    void playCard(Card* C);
    Card* removeFromHand(int index);
    friend std::ostream& operator<< (std::ostream& out, const Player& P);
    static Base_Chain* newChain(Card* C);
private:
    std::string name;
    int coins;
    int maxChains;
    std::vector<Base_Chain*> chains;
    Hand* H;
};

class NotEnoughCoinsException : public std::exception
{
public:
    virtual const char* what() const throw();
};

#endif
