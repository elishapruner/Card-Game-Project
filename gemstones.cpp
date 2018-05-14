
#include "gemstones.h"

/*
    returns miminum number of cards (identical, in a chain)
    needed to get specified # of coins
*/
int Quartz::getCardsPerCoin(int coins) {
    switch (coins)
    {
    case 4:
        return 10;
    case 3:
        return 8;
    case 2:
        return 6;
    case 1:
        return 4;
    default:
        return 0;
    }
}

std::string Quartz::getName() {
    return "Quartz";
}

void Quartz::print(std::ostream& out) {
    out << "Q";
}


/*
returns miminum number of cards (identical, in a chain)
needed to get specified # of coins
*/
int Hematite::getCardsPerCoin(int coins) {
    switch (coins)
    {
    case 4:
        return 9;
    case 3:
        return 8;
    case 2:
        return 6;
    case 1:
        return 3;
    default:
        return 0;
    }
}

std::string Hematite::getName() {
    return "Hematite";
}

void Hematite::print(std::ostream& out) {
    out << "H";
}


/*
returns miminum number of cards (identical, in a chain)
needed to get specified # of coins
*/
int Obsidian::getCardsPerCoin(int coins) {
    switch (coins)
    {
    case 4:
        return 8;
    case 3:
        return 7;
    case 2:
        return 5;
    case 1:
        return 3;
    default:
        return 0;
    }
}

std::string Obsidian::getName() {
    return "Obsidian";
}

void Obsidian::print(std::ostream& out) {
    out << "O";
}


/*
returns miminum number of cards (identical, in a chain)
needed to get specified # of coins
*/
int Malachite::getCardsPerCoin(int coins) {
    switch (coins)
    {
    case 4:
        return 7;
    case 3:
        return 6;
    case 2:
        return 5;
    case 1:
        return 3;
    default:
        return 0;
    }
}

std::string Malachite::getName() {
    return "Malachite";
}

void Malachite::print(std::ostream& out) {
    out << "M";
}


/*
returns miminum number of cards (identical, in a chain)
needed to get specified # of coins
*/
int Turquoise::getCardsPerCoin(int coins) {
    switch (coins)
    {
    case 4:
        return 7;
    case 3:
        return 6;
    case 2:
        return 4;
    case 1:
        return 2;
    default:
        return 0;
    }
}

std::string Turquoise::getName() {
    return "Turquoise";
}

void Turquoise::print(std::ostream& out) {
    out << "T";
}


/*
returns miminum number of cards (identical, in a chain)
needed to get specified # of coins
*/
int Ruby::getCardsPerCoin(int coins) {
    switch (coins)
    {
    case 4:
        return 6;
    case 3:
        return 5;
    case 2:
        return 4;
    case 1:
        return 2;
    default:
        return 0;
    }
}

std::string Ruby::getName() {
    return "Ruby";
}

void Ruby::print(std::ostream& out) {
    out << "R";
}


/*
returns miminum number of cards (identical, in a chain)
needed to get specified # of coins
*/
int Amethyst::getCardsPerCoin(int coins) {
    switch (coins)
    {
    case 4:
        return 5;
    case 3:
        return 4;
    case 2:
        return 3;
    case 1:
        return 2;
    default:
        return 0;
    }
}

std::string Amethyst::getName() {
    return "Amethyst";
}

void Amethyst::print(std::ostream& out) {
    out << "A";
}


/*
returns miminum number of cards (identical, in a chain)
needed to get specified # of coins
*/
int Emerald::getCardsPerCoin(int coins) {
    switch (coins)
    {
    case 4:
        return 500;
    case 3:
        return 3;
    case 2:
        return 2;
    case 1:
        return 500;
    default:
        return 0;
    }
}

std::string Emerald::getName() {
    return "Emerald";
}

void Emerald::print(std::ostream& out) {
    out << "E";
}


const char* IllegalTypeException::what() const throw() {
    return "CARD TYPE IS ILLEGAL!";
}
