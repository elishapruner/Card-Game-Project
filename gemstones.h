
#ifndef __CARD_H__
#define __CARD_H__

#include <string>
#include <exception>

#include "chain.h"

class Card
{
public:
    virtual int getCardsPerCoin(int coins) = 0;
    virtual std::string getName() = 0;
    virtual void print(std::ostream& out) = 0;
private:

};

class Quartz : public Card
{
public:
    int getCardsPerCoin(int coins);
    std::string getName();
    void print(std::ostream& out);
private:
};

class Hematite : public Card
{
public:
    int getCardsPerCoin(int coins);
    std::string getName();
    void print(std::ostream& out);
private:
};

class Obsidian : public Card
{
public:
    int getCardsPerCoin(int coins);
    std::string getName();
    void print(std::ostream& out);
private:
};

class Malachite : public Card
{
public:
    int getCardsPerCoin(int coins);
    std::string getName();
    void print(std::ostream& out);
private:
};

class Turquoise : public Card
{
public:
    int getCardsPerCoin(int coins);
    std::string getName();
    void print(std::ostream& out);
private:
};

class Ruby : public Card
{
public:
    int getCardsPerCoin(int coins);
    std::string getName();
    void print(std::ostream& out);
private:
};

class Amethyst : public Card
{
public:
    int getCardsPerCoin(int coins);
    std::string getName();
    void print(std::ostream& out);
private:
};

class Emerald : public Card
{
public:
    int getCardsPerCoin(int coins);
    std::string getName();
    void print(std::ostream& out);
private:
};

class IllegalTypeException : public std::exception
{
public:
    virtual const char* what() const throw();
};

#endif
