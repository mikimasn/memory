#pragma once
namespace Memory::tui {
    class Interupts {
    public:
        static void setupInterupts();
        static void handleTermination(int i);
    };
}


