
#ifndef __CHAIN_H__
#define __CHAIN_H__

#include <vector>

#include "gemstones.h"
#include "cardfactory.h"

class Card;
class CardFactory;

class Base_Chain
{
public:
    virtual int sell() = 0;
    virtual std::string getName() = 0;
    virtual void addCard(Card* C) = 0;
    virtual void print(std::ostream& out) = 0;
};

template<typename T> class Chain : public Base_Chain
{
public:
    Chain() {}
    Chain(std::istream& in, CardFactory * CF) {
        std::string temp;
        in >> temp;
        int size;
        in >> size;
        char cardType;
        Card* C;
        for (int i = 0; i < size; i++)
        {
            in >> cardType;
            C = CF->createCard(cardType);
            T* XC = dynamic_cast<T*>(C);
            if (XC == NULL) {
                throw new IllegalTypeException();
            }
            cards.push_back(XC);
        }
    }
    Chain<T>& operator+= (Card* C) {
        addCard(C);
        return *this;
    }
    void addCard(Card* C) {
        T* XC = dynamic_cast<T*>(C);
        if (XC == NULL) {
            throw new IllegalTypeException();
        }
        cards.push_back(XC);
    }
    int sell() {
        for (int i = 4; i > 0; i--) {
            if (cards.size() >= cards.back()->getCardsPerCoin(i)) {
                return i;
            }
        }
        return 0;
    }
    friend std::ostream& operator<<(std::ostream& out, const Chain& C) {
        std::vector<T*> cards = C.cards;
        out << cards.back()->getName();
        out << " ";
        out << cards.size();
        for (int i = 0; i < cards.size(); i++) {
            out << " ";
            cards.at(i)->print(out);
        }
    }
    std::string getName() {
        return cards.back()->getName();
    }
    void print(std::ostream& out) {
        out << cards.back()->getName();
        out << " ";
        out << cards.size();
        for (int i = 0; i < cards.size(); i++) {
            out << " ";
            cards.at(i)->print(out);
        }
    }
private:
    std::vector<T*> cards;

};

#endif
