#include "Application.h"
#include <random>

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
