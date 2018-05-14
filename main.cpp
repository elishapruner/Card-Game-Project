
#include <iostream>
#include <fstream>
#include <string>

#include "table.h"
#include "cardfactory.h"
#include "player.h"

/*
    helper function to main flow
    asks user a question and forces a Y or N response
*/
std::string askYNQuestion(std::string question) {
    std::string temp;
    do {
        std::cout << question << " (Y/N) ";
        std::getline(std::cin, temp);
    } while (temp != "Y" && temp != "N");
    return temp;
}

/*
    helper function to main flow
    handles the subroutine of allowing a player to take cards from the trade area
*/
void performTrades(Table* T, Player* P) {
    TradeArea* TA = T->getTradeArea();
    std::cout << "Trade Area " << *TA << std::endl;
    bool valid = true;
    bool success;
    //std::string cardName;
    std::string temp;
    do {
        std::cout << "Which type of card would you like to take from the Trade Area? (empty to skip)";
        std::getline(std::cin, temp);
        if (temp == "") {
            valid = false;
        }
        else {
            success = T->attemptTrade(P, temp);
            if (!success) {
                std::cout << "card name is invalid!" << std::endl;
            }
            else {
                std::cout << "retrived card from Trade Area!" << std::endl;
                std::cout << "Trade Area " << *TA << std::endl;
                std::cout << *P << std::endl;
                P->printHand(std::cout, false);
                std::cout << " " << P->handSize() << std::endl;
            }
        }
    } while (valid);
}

/*
    helper function to main flow
    handles the interactions during a given player's turn
*/
void playerTurn(Table* T, Player* P) {
    std::string temp;
    std::cout << "Game State" << std::endl;
    std::cout << *T << std::endl;
    //operator<<(std::cout, *T);
    std::cout << P->getName() << "'s turn..." << std::endl;
    if (P->getNumCoins() >= 3 && P->getNumChains() < 3) {
        temp = askYNQuestion("Would you like to buy an extra chain?");
        if (temp == "Y") {
            P->buyThirdChain();
        }
    }
    else {
        std::cout << "no option to buy another change" << std::endl;
    }
    //T->drawCard(P);
    //temp = askYNQuestion("Would you like to add all cards from Trade Area to your chains?");
    //if (temp == "Y") {
    //    T->takeTrade(P);
    //}
    //else {
    //    T->discardTrade();
    //}
    performTrades(T, P);
    std::cout << "Discarding all remaining cards from Trade Area" << std::endl;
    T->emptyTradeArea();
    //std::cout << "Player " << P->getName() << "'s Status" << std::endl;
    std::cout << *P << std::endl;
    P->printHand(std::cout, false);
    std::cout << " " << P->handSize() << std::endl;
    do {
        std::cout << "Playing your top card!" << std::endl;
        P->playTopCard();
        std::cout << *P << std::endl;
        P->printHand(std::cout, false);
        std::cout << " " << P->handSize() << std::endl;
        if (P->handSize() > 0) {
            temp = askYNQuestion("Would you like to play your top card again?");
        }
        else {
            temp = "N";
        }
    } while (temp == "Y");
    temp = askYNQuestion("Would you like to remove a card from hand?");
    if (temp == "Y") {
        P->printHand(std::cout, true);
        std::cout << std::endl;
        int index;
        do {
            std::cout << "Please enter a valid index (starting at 0) ";
            std::getline(std::cin, temp);
            try {
                index = std::stoi(temp);
            }
            catch (const std::invalid_argument& e) {
                index = -1;
            }
        } while (index < 0 || index >= P->handSize());
        T->discardFromHand(P, index);
        P->printHand(std::cout, true);
        std::cout << std::endl;
    }
    TradeArea* TA = T->fillTradeArea();
    std::cout << "Trade Area" << std::endl;
    std::cout << *TA << std::endl;
    //temp = askYNQuestion("Would you like to add all cards from Trade Area to your chains?");
    //if (temp == "Y") {
    //    T->takeTrade(P);
    //}
    performTrades(T, P);
    T->drawCard(P);
    T->drawCard(P);
}

/*
    executes the main flow of the game
*/
int main() {

    Table* T;
    CardFactory* CF = CardFactory::getFactory();
    Player* P1;
    Player* P2;

    std::ifstream in;
    std::string temp;

    do
    {
        std::cout << "Enter file name to load from paused game (or just enter to start new game): ";
        std::getline(std::cin, temp);
        in.open(temp, std::ios::in);
    } while (temp != "" && !in.good());

    if (temp == "") {
        // new game
        T = new Table();
        std::cout << "Enter name of Player 1: ";
        std::getline(std::cin, temp);
        P1 = T->createP1(temp);
        std::cout << "Enter name of Player 2: ";
        std::getline(std::cin, temp);
        P2 = T->createP2(temp);
        for (int i = 0; i < 5; i++) {
            T->drawCard(P1);
            T->drawCard(P2);
        }
    }
    else {
        // load game
        //in.open(temp, std::ios::in);
        T = new Table(in, CF);
        P1 = T->getP1();
        P2 = T->getP2();
    }

    std::string winner;

    while (!T->win(winner)) {
        std::cout << "Enter file name to pause game (or just enter to continue): ";
        std::getline(std::cin, temp);
        if (temp != "") {
            // save game
            std::ofstream out;
            out.open(temp, std::ios::out);
            T->print(out);
        }
        playerTurn(T, P1);
        playerTurn(T, P2);
    }

    std::cout << winner << " has won the game!" << std::endl;

    return 0;
}