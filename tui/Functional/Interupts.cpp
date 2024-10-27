#include <csignal>
#include <cstdlib>
#include "Interupts.h"
#include "../TerminalHelper.h"

namespace Memory::tui {
    timer_t Interupts::timerid;

    void (*Interupts::callback)() = nullptr;

    void Interupts::setupInterupts() {
        signal(SIGINT, Interupts::handleTermination);
        signal(SIGTERM, Interupts::handleTermination);
        signal(SIGQUIT, Interupts::handleTermination);
        signal(SIGALRM, Interupts::handleTimer);
    }

    void Interupts::handleTermination(int i) {
        TerminalHelper::restoreTerminal();
        exit(0);
    }

    bool Interupts::callAfter(int ms, void (*callbackfn)()) {
        if (Interupts::callback != nullptr) return false;
        if(Interupts::timerid == nullptr) Interupts::timerid= malloc(sizeof (timer_t));
        sigevent timer;
        timer.sigev_notify = SIGEV_SIGNAL;
        timer.sigev_signo = SIGALRM;
        int res = timer_create(CLOCK_REALTIME, &timer, &Interupts::timerid);
        if (res != 0) return false;
        itimerspec time;
        time.it_value.tv_nsec = (ms % 1000) * 1000000;
        time.it_interval.tv_nsec = 0;
        time.it_interval.tv_sec = 0;
        time.it_value.tv_sec = ms / 1000;
        res = timer_settime(Interupts::timerid, 0, &time, nullptr);
        if(res==0) Interupts::callback = callbackfn;
        return res == 0;
    }

    void Interupts::handleTimer(int i) {
        if (Interupts::callback != nullptr) {
            Interupts::callback();
            Interupts::callback = nullptr;
            timer_delete(Interupts::timerid);
        }
    }
}

