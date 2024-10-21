#include "../tui/UI/Window.h"
#include "../tui/Screens/StartScreen.h"

namespace Memory::game{
    enum Screens{
        Start
    };
    class Application {
    private:
        static void initiliaze();
        static Memory::tui::Window window;
        static Memory::tui::StartScreen startScreen;

    public:
        static void start();

    };
}

