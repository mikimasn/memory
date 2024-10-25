#pragma once
#include "../UI/Window.h"
#include "../MaterialDesign/Text.h"
#include "../MaterialDesign/Button.h"
#include "../MaterialDesign/FramedElement.h"
#include "../MaterialDesign/Positioner.h"
#include "../../game/Game.h"
#include "../MaterialDesign/InputBox.h"
#include "../MaterialDesign/Group.h"
namespace Memory::tui {
    class SaveScreen : public Sheet {
    private:
        Text Title;
        InputBox path;
        Button closeButton;
        Button saveButton;
        FramedElement frame;
        FramedElement outerFrame;
        Group group;

        static void closeDialog();
        static void saveAndClose();

        static SaveScreen *instance;

        void centerElements();

    public:
        explicit SaveScreen(const ElementParent &parent);

        static SaveScreen *getInstance() {
            return SaveScreen::instance;
        }
    };
}
