#pragma once

#include <vector>
#include <string>

namespace Memory::game {
    enum GameAction {
        Void,
        Score,
        SwitchPlayer,
        EndGame
    };
    enum GameResult {
        Player1,
        Player2,
        Draw,
        NotFinished
    };

    class Game {
    private:
        int seed;
        std::vector<short> cards;
        std::vector<bool> discovered;
        int width;
        int height;
        std::string player1Name;
        std::string player2Name;
        int score1 = 0;
        int score2 = 0;
        int currentPlayer = 0;
        int nowDiscovered = -1;
        GameResult result = NotFinished;
        void generateFromSeed();
    public:
        explicit Game(int seed, int width, int height, std::string &player1Name, std::string &player2Name);
        explicit Game(std::vector<char> &gameDump);

        GameAction discover(int index);

        GameResult getResult() {
            return result;
        };

        std::pair<int, int> getScores() {
            return {score1, score2};
        };

        std::pair<std::string, std::string> getNames() {
            return {player1Name, player2Name};
        };

        std::vector<short> &getCards() {
            return cards;
        };

        std::vector<bool> &getDiscovered() {
            return discovered;
        };

        int getSeed() const {
            return seed;
        }

        std::pair<int, int> getDimensions() {
            return {width, height};
        }

        int getCurrentPlayer() {
            return currentPlayer;
        }
        std::vector<char> dumpGame();
    };
}