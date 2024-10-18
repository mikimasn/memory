#include <csignal>
#include <cstdlib>
#include "Interupts.h"
#include "../TerminalHelper.h"
namespace Memory::tui{
    void Interupts::setupInterupts() {
        signal(SIGINT, Interupts::handleTermination);
        signal(SIGTERM, Interupts::handleTermination);
        signal(SIGQUIT, Interupts::handleTermination);
    }

    void Interupts::handleTermination(int i) {
        TerminalHelper::restoreTerminal();
        exit(0);
    }
}

