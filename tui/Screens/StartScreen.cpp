#include "StartScreen.h"
#include "../../game/Application.h"

Memory::tui::StartScreen *Memory::tui::StartScreen::instance = nullptr;

void Memory::tui::StartScreen::startCallback() {
    Memory::game::Application::goToSetup();
}

void Memory::tui::StartScreen::loadCallback() {
    Interupts::handleTermination(0);
}
