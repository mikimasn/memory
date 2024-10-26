#pragma once

#include "../tui/UI/Window.h"
#include "../tui/Screens/StartScreen.h"
#include "../tui/Screens/SetupScreen.h"
#include "../tui/Screens/ErrorScreen.h"
#include "../tui/Screens/GameScreen.h"
#include "../tui/Screens/ResultScreen.h"
#include "../tui/Screens/SaveScreen.h"
#include "../tui/Screens/LoadScreen.h"

namespace Memory::game {
    enum Screens {
        Start = 0,
        Setup = 1,
        Error = 2,
        Gameplay = 3,
        Result = 4,
        Save = 5,
        Load = 6
    };

    class Application {
    private:
        static void initiliaze();

        static Memory::tui::Window window;
        static Memory::tui::StartScreen startScreen;
        static Memory::tui::SetupScreen setupScreen;
        static bool isError;
        static Memory::tui::ErrorScreen errorScreen;
        static Memory::tui::GameScreen gameScreen;
        static Memory::game::Game game;
        static Memory::tui::ResultScreen resultScreen;
        static Memory::tui::SaveScreen saveScreen;
        static Memory::tui::LoadScreen loadScreen;


    public:
        static void start();

        static void goToSetup();

        static void throwError(const std::string &message);

        static void closeError();

        static void popWindowStack();

        static void createAndStartGame(std::string &player1, std::string &player2, int width, int height);

        static void showSaveDialog();

        static void showGameResult();

        static void saveGame(std::string path);

        static void loadGame(std::string path);

        static void goToLoad();

        static std::string getCwd();
    };
}

