#include "Application.h"
#include <random>
#include <filesystem>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <iostream>

Memory::tui::Window Memory::game::Application::window;
Memory::tui::StartScreen Memory::game::Application::startScreen = Memory::tui::StartScreen(
        Memory::tui::ElementParent{&window, window.addChild(&startScreen, 0, 0)});
Memory::tui::SetupScreen Memory::game::Application::setupScreen = Memory::tui::SetupScreen(
        Memory::tui::ElementParent{&window, window.addChild(&setupScreen, 0, 0)});
Memory::tui::ErrorScreen Memory::game::Application::errorScreen = Memory::tui::ErrorScreen(
        Memory::tui::ElementParent{&window, window.addChild(&errorScreen, 0, 0)}, "");
std::string name;
Memory::game::Game Memory::game::Application::game = Memory::game::Game(0, 0, 0, name, name);
Memory::tui::GameScreen Memory::game::Application::gameScreen = Memory::tui::GameScreen(
        Memory::tui::ElementParent{&window, window.addChild(&gameScreen, 0, 0)});
bool Memory::game::Application::isError = false;
Memory::tui::ResultScreen Memory::game::Application::resultScreen = Memory::tui::ResultScreen(
        Memory::tui::ElementParent{&window, window.addChild(&resultScreen, 0, 0)}, "");
Memory::tui::SaveScreen Memory::game::Application::saveScreen = Memory::tui::SaveScreen(
        Memory::tui::ElementParent{&window, window.addChild(&saveScreen, 0, 0)});
Memory::tui::LoadScreen Memory::game::Application::loadScreen = Memory::tui::LoadScreen(
        Memory::tui::ElementParent{&window, window.addChild(&loadScreen, 0, 0)});
constexpr int MaxSaveFileLength = 1e5;
char saveFileBuffer[MaxSaveFileLength];

void Memory::game::Application::initiliaze() {
    Memory::tui::Interupts::setupInterupts();
}

void Memory::game::Application::start() {
    initiliaze();
    window.pushFocus(0);
    window.render(true);
    while (true) {
        auto ele = Memory::tui::InputHandler::blockForInput();
        window.handleInput(ele);
    }
}

void Memory::game::Application::goToSetup() {
    window.clearFocus();
    window.pushFocus(Screens::Setup);
    window.render(true);
}

void Memory::game::Application::throwError(const string &message) {
    errorScreen.updateMessage(message);
    window.pushFocus(Screens::Error);
    window.render(true);
    isError = true;
}

void Memory::game::Application::closeError() {
    if (!isError) return;
    window.popFocus();
    window.render(true);
    isError = false;
}

void Memory::game::Application::createAndStartGame(string &player1, string &player2, int width, int height) {
    int seed = std::random_device()();
    game = Game(seed, width, height, player1, player2);
    gameScreen.attachGame(&game);
    window.clearFocus();
    window.pushFocus(Screens::Gameplay);
    window.render(true);
}

void Memory::game::Application::showGameResult() {
    window.clearFocus();
    auto res = game.getResult();
    string name = "";
    if (res == GameResult::Player1) name = game.getNames().first;
    else if (res == GameResult::Player2) name = game.getNames().second;
    resultScreen.update(res, name);
    window.pushFocus(Screens::Result);
    window.render(true);
}

std::string Memory::game::Application::getCwd() {
    return std::filesystem::current_path().string();
}

void Memory::game::Application::popWindowStack() {
    window.popFocus();
    window.render(true);
}

void Memory::game::Application::showSaveDialog() {
    window.pushFocus(Screens::Save);
    window.render(true);
}

void Memory::game::Application::saveGame(std::string path) {
    int fd = open(path.c_str(), O_WRONLY | O_CREAT | O_EXCL, S_IRWXU | S_IRGRP | S_IROTH);
    if (fd == -1)
        throw std::runtime_error("Failed to open file OS returned error: " + std::string(std::strerror(errno)));
    auto dump = game.dumpGame();
    if (write(fd, dump.data(), dump.size()) == -1)
        throw std::runtime_error("Failed to write to file OS returned error: " + std::string(std::strerror(errno)));
    close(fd);
}

void Memory::game::Application::loadGame(std::string path) {
    int fd = open(path.c_str(), O_RDONLY);
    if (fd == -1)
        throw std::runtime_error("Failed to open file OS returned error: " + std::string(std::strerror(errno)));
    //read magic number
    std::vector<char> magicNumber(Memory::game::Game::MagicNumber.size());
    int recived = read(fd, saveFileBuffer, MaxSaveFileLength);
    if (recived == -1)
        throw std::runtime_error("Failed to read from file OS returned error: " + std::string(std::strerror(errno)));
    if (recived == MaxSaveFileLength) throw std::runtime_error("File is too large");
    vector<char> file(saveFileBuffer, saveFileBuffer + recived);
    game = Game(file);
    gameScreen.attachGame(&game);
    window.clearFocus();
    window.pushFocus(Screens::Gameplay);
    window.render(true);
}

void Memory::game::Application::goToLoad() {
    window.pushFocus(Screens::Load);
    window.render(true);
}
