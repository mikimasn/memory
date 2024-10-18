namespace Memory::tui {
    enum InputActionResult{
        VOID,
        MOVE_UP,
        MOVE_DOWN,
        MOVE_LEFT,
        MOVE_RIGHT,
        NOT_HANDLED
    };
    enum InputGroup{
        ARROW_KEYS,
        ENTER,
        NUMBERS,
        TEXT,
        UNKNOWN,
    };
    struct InputSignal{
        InputGroup group;
        char c;
    };
    class InputHandler{
    public:
        static InputSignal parseInput(char* c);
        static InputActionResult convertArrowKeys(InputSignal signal);
        static InputSignal blockForInput();
    };
}

