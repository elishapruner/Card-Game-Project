
#include "player.h"

/*
    construtor for a new player
    requires name to be specified
*/
Player::Player(std::string& name)
{
    this->name = name;
    maxChains = 2;
    coins = 0;
    H = new Hand();
    //chains = *(new std::vector<Base_Chain*>());
}

/*
    constructor for use when restoring from stream
*/
Player::Player(std::istream& in, CardFactory* CF)
{
    std::string temp;
    in >> name;
    in >> coins;
    in >> temp;
    in >> maxChains;
    getline(in, temp);
    Base_Chain* BC;
    for (int i = 0; i < 3; i++)
    {
        switch (in.peek())
        {
        case 'Q':
            BC = new Chain<Quartz>(in, CF);
            break;
        case 'H':
            BC = new Chain<Hematite>(in, CF);
            break;
        case 'O':
            BC = new Chain<Obsidian>(in, CF);
            break;
        case 'M':
            BC = new Chain<Malachite>(in, CF);
            break;
        case 'T':
            BC = new Chain<Turquoise>(in, CF);
            break;
        case 'R':
            BC = new Chain<Ruby>(in, CF);
            break;
        case 'A':
            BC = new Chain<Amethyst>(in, CF);
            break;
        case 'E':
            BC = new Chain<Emerald>(in, CF);
            break;
        default:
            getline(in, temp);
            break;
        }
    }
    H = new Hand(in, CF);
}


std::string Player::getName()
{
    return name;
}

int Player::getNumCoins()
{
    return coins;
}

Player& Player::operator+=(int coins)
{
    this->coins += coins;
    return *this;
}

int Player::getMaxNumChains() {
    return maxChains;
}

int Player::getNumChains() {
    return chains.size();
}

Base_Chain& Player::operator[] (int i) {
    return *chains.at(i);
}

void Player::buyThirdChain()
{
    if (maxChains < 3)
    {
        if (coins < 3)
        {
            // raise exception; not enough coins
        }
        else
        {
            maxChains = 3;
            coins -= 3;
        }
    }
    else
    {
        // raise exception; additional chain already bought
    }
}

/*
    creates a new chain with the specified card in it
*/
Base_Chain* Player::newChain(Card* C) {
    Base_Chain* BC;
    char cardType = C->getName().at(0);
    switch (C->getName().at(0))
    {
    case 'Q':
        BC = new Chain<Quartz>();
        break;
    case 'H':
        BC = new Chain<Hematite>();
        break;
    case 'O':
        BC = new Chain<Obsidian>();
        break;
    case 'M':
        BC = new Chain<Malachite>();
        break;
    case 'T':
        BC = new Chain<Turquoise>();
        break;
    case 'R':
        BC = new Chain<Ruby>();
        break;
    case 'A':
        BC = new Chain<Amethyst>();
        break;
    case 'E':
        BC = new Chain<Emerald>();
        break;
    default:
        BC = new Chain<Card>();
        break;
    }
    BC->addCard(C);
    return BC;
}

/*
    writes contents of hand to stream
    has 2 modes of operation
    one for displaying during game (full is false)
    other for saving game state (full is true)
*/
void Player::printHand(std::ostream& out, bool full)
{
    if (full)
    {
        out << *H;
    }
    else
    {
        if (H->getSize() > 0) {
            H->top()->print(out);
        }
    }
}

int Player::handSize() {
    return H->getSize();
}

void Player::addCard(Card* C) {
    (*H) += C;
}

/*
    plays top card from hand and handles what happens to the chains
*/
void Player::playCard(Card* C) {
    int maxCoins = 0;
    int bestIndex = 0;
    for (int i = 0; i < 3; i++) {
        if (i < chains.size()) {
            if (chains.at(i)->getName() == C->getName()) {
                chains.at(i)->addCard(C);
                return;
            }
            if (chains.at(i)->sell() > maxCoins) {
                maxCoins = chains.at(i)->sell();
                bestIndex = i;
            }
        }
        else if (i < maxChains) {
            chains.push_back(Player::newChain(C));
            return;
        }
    }
    coins += chains.at(bestIndex)->sell();
    chains.erase(chains.begin() + bestIndex);
    playCard(C);
}


void Player::playTopCard() {
    Card* C = H->play();
    playCard(C);
}

Card* Player::removeFromHand(int index) {
    return (*H)[index];
}

std::ostream& operator<< (std::ostream& out, const Player& P) {
    out << P.name;
    out << " ";
    out << P.coins;
    out << " coins ";
    out << P.maxChains;
    for (int i = 0; i < 3; i++) {
        out << std::endl;
        if (i < P.chains.size()) {
            //Base_Chain* BC = P.chains.at(i);
            P.chains.at(i)->print(out);
        }
        else {
            out << "----";
        }
    }
    return out;
}

const char* NotEnoughCoinsException::what() const throw() {
    return "NOT ENOUGH COINS TO COMPLETE ACTION!";
}
