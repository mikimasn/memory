#include "Game.h"
#include <random>
#include <algorithm>
#include <set>

Memory::game::Game::Game(int seed, int width, int height, std::string &player1Name, std::string &player2Name) {
    this->seed = seed;
    this->width = width;
    this->height = height;
    this->player1Name = player1Name;
    this->player2Name = player2Name;
    this->cards.resize(width * height);
    this->discovered.resize(width * height);
    this->discovered.assign(width * height, false);
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