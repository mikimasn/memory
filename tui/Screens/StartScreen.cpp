//
// Created by pythontest on 19.10.24.
//

#include "StartScreen.h"

Memory::tui::StartScreen *Memory::tui::StartScreen::instance = nullptr;
void Memory::tui::StartScreen::startCallback() {
    Interupts::handleTermination(0);
}

void Memory::tui::StartScreen::loadCallback() {
    Interupts::handleTermination(0);
}
