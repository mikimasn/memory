#pragma once
#include <ctime>
namespace Memory::tui {
    class Interupts {
    public:
        static void setupInterupts();
        static void handleTermination(int i);
        static bool callAfter(int ms, void (*callback)());
        static void handleTimer(int i);
        static void (*callback)();
        static timer_t timerid;
    };
}


