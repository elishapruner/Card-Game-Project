
#include "CardFactory.h"

CardFactory* CardFactory::onlyFactory = NULL; // static pointer to only instance of CardFactory

/*
    used during restoring from save file
    given card type, creates an instance of the specified card type
    returns newly created card
*/
Card* CardFactory::createCard(char cardType)
{
    Card* C;
    switch (cardType)
    {
    case 'Q':
        C = new Quartz();
        break;
    case 'H':
        C = new Hematite();
        break;
    case 'O':
        C = new Obsidian();
        break;
    case 'M':
        C = new Malachite();
        break;
    case 'T':
        C = new Turquoise();
        break;
    case 'R':
        C = new Ruby();
        break;
    case 'A':
        C = new Amethyst();
        break;
    case 'E':
        C = new Emerald();
        break;
    default:
        // raise exception; invalid card type
        break;
    }
    allCards.push_back(C);
    return C;
}

/*
    used by default constructor only
    creates multiple cards of same type using createCard
*/
void CardFactory::createCards(char cardType, int count)
{
    for (int i = 0; i < count; i++) {
        createCard(cardType);
    }
}

/*
    default (private) constructor
    creates all cards via helper
*/
CardFactory::CardFactory()
{
    createAllCards();
}

/*
    creates the default number of each type of cards
*/
void CardFactory::createAllCards()
{
    createCards('Q', maxQuartzes);
    createCards('H', maxHematites);
    createCards('O', maxObsidians);
    createCards('M', maxMalachites);
    createCards('T', maxTurquoises);
    createCards('R', maxRubies);
    createCards('A', maxAmethysts);
    createCards('E', maxEmeralds);
}

/*
    used before loading from a file
    deletes all cards
*/
void CardFactory::deleteAllCards()
{
    allCards.clear();
}

/*
    the way to retrieve the sole instance of CardFactory
    invokes private construtor if the sole instance does not exist
*/
CardFactory * CardFactory::getFactory()
{
    if (CardFactory::onlyFactory == NULL)
    {
        CardFactory::onlyFactory = new CardFactory();
    }
    return onlyFactory;
}

/*
    creates a new randomly sorted Deck
*/
Deck CardFactory::getDeck()
{
    Deck* D = new Deck();
    for (int i = 0; i < allCards.size(); i++)
    {
        D->push_back(allCards.at(i));
    }
    // shuffle randomly
    auto engine = std::default_random_engine{};
    std::shuffle(D->begin(), D->end(), engine);
    return *D;
}

