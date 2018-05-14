
#ifndef __CARDFACTORY_H__
#define __CARDFACTORY_H__

#include <algorithm>
#include <random>
#include <vector>
//#include <hash_map>

#include "deck.h"
#include "gemstones.h"

class Deck;
class CardFactory;
class Card;

class CardFactory
{
public:
    static CardFactory* getFactory();
    Deck getDeck();
    Card* createCard(char cardType);
    void createAllCards();
    void deleteAllCards();

    const int maxQuartzes = 20;
    const int maxHematites = 18;
    const int maxObsidians = 16;
    const int maxMalachites = 14;
    const int maxTurquoises = 12;
    const int maxRubies = 10;
    const int maxAmethysts = 8;
    const int maxEmeralds = 6;



private:
    static CardFactory* onlyFactory;
    std::vector<Card*> allCards;

    void createCards(char cardType, int count);
    CardFactory();
    CardFactory(const CardFactory& other) {}
    CardFactory& operator= (const CardFactory& other) {}
};

#endif