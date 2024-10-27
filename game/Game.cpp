#include "Game.h"
#include <random>
#include <algorithm>
#include <set>
#include <stdexcept>


Memory::game::Game::Game(int seed, int width, int height, std::string &player1Name, std::string &player2Name) {
    this->seed = seed;
    this->width = width;
    this->height = height;
    this->player1Name = player1Name;
    this->player2Name = player2Name;
    this->cards.resize(width * height);
    this->discovered.resize(width * height);
    this->discovered.assign(width * height, false);
    generateFromSeed();
}

Memory::game::GameAction Memory::game::Game::discover(int index) {
    if (nowDiscovered == -1) {
        nowDiscovered = index;
        return Memory::game::Void;
    } else {
        if (cards[nowDiscovered] == cards[index]) {
            discovered[nowDiscovered] = true;
            discovered[index] = true;
            if (currentPlayer == 0) {
                score1++;
            } else {
                score2++;
            }
            if (score1 + score2 == (width * height) / 2) {
                if (score1 > score2) result = Memory::game::Player1;
                else if (score2 > score1) result = Memory::game::Player2;
                else result = Memory::game::Draw;
                return Memory::game::EndGame;
            }
            nowDiscovered = -1;
            return Memory::game::Score;
        } else {
            nowDiscovered = -1;
            currentPlayer = 1 - currentPlayer;
        }
    }
    return Memory::game::SwitchPlayer;
}

std::vector<char> convertinttochar(int a) {
    std::vector<char> c(4);
    c[0] = (a >> 24) & 0xFF;
    c[1] = (a >> 16) & 0xFF;
    c[2] = (a >> 8) & 0xFF;
    c[3] = a & 0xFF;
    return c;
}

int convertchartoint(std::vector<char> c) {
    return ((unsigned char) c[0] << 24) | ((unsigned char) c[1] << 16) | ((unsigned char) c[2] << 8) |
           (unsigned char) c[3];
}

std::vector<char> Memory::game::Game::dumpGame() {
    std::vector<char> gameDump;
    for (auto c: MagicNumber) gameDump.push_back(c);
    gameDump.push_back('\000');
    for (auto c: player1Name) gameDump.push_back(c);
    gameDump.push_back('\000');
    for (auto c: player2Name) gameDump.push_back(c);
    gameDump.push_back('\000');
    for (auto c: convertinttochar(seed)) gameDump.push_back(c);
    for (auto c: convertinttochar(width)) gameDump.push_back(c);
    for (auto c: convertinttochar(height)) gameDump.push_back(c);
    for (auto c: convertinttochar(score1)) gameDump.push_back(c);
    for (auto c: convertinttochar(score2)) gameDump.push_back(c);
    for (auto c: convertinttochar(currentPlayer)) gameDump.push_back(c);
    //convert discovered to bool array
    for (auto d: discovered) gameDump.push_back(d);
    return gameDump;
}

Memory::game::Game::Game(std::vector<char> &gameDump) {
    int i = 0;
    for (; i < (int)MagicNumber.size(); i++) {
        if (gameDump[i] != MagicNumber[i]) throw std::invalid_argument("Invalid save file");
    }
    i++;
    std::string name1;
    for (; gameDump[i] != '\000'; i++) {
        name1.push_back(gameDump[i]);
    }
    i++;
    std::string name2;
    for (; gameDump[i] != '\000'; i++) {
        name2.push_back(gameDump[i]);
    }
    i++;
    player1Name = name1;
    player2Name = name2;
    seed = convertchartoint({gameDump[i], gameDump[i + 1], gameDump[i + 2], gameDump[i + 3]});
    i += 4;
    width = convertchartoint({gameDump[i], gameDump[i + 1], gameDump[i + 2], gameDump[i + 3]});
    i += 4;
    height = convertchartoint({gameDump[i], gameDump[i + 1], gameDump[i + 2], gameDump[i + 3]});
    i += 4;
    score1 = convertchartoint({gameDump[i], gameDump[i + 1], gameDump[i + 2], gameDump[i + 3]});
    i += 4;
    score2 = convertchartoint({gameDump[i], gameDump[i + 1], gameDump[i + 2], gameDump[i + 3]});
    i += 4;
    currentPlayer = convertchartoint({gameDump[i], gameDump[i + 1], gameDump[i + 2], gameDump[i + 3]});
    i += 4;
    for (; i < (int)gameDump.size(); i++) {
        discovered.push_back(gameDump[i]);
    }
    cards.resize(width * height);
    generateFromSeed();
}

void Memory::game::Game::generateFromSeed() {
    std::mt19937 rng(seed);
    std::uniform_int_distribution<short> dist(0, INT16_MAX);
    std::set<short> cardsTmp;
    for (int i = 0; i < width * height; i += 2) {
        short card = dist(rng);
        while (cardsTmp.contains(card)) {
            card = dist(rng);
        }
        cardsTmp.insert(card);
        this->cards[i] = this->cards[i + 1] = card;
    }
    std::shuffle(this->cards.begin(), this->cards.end(), rng);
}
