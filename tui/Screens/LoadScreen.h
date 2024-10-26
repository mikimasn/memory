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
    class LoadScreen : public Sheet {
    private:
        Text Title;
        InputBox path;
        Button closeButton;
        Button saveButton;
        FramedElement frame;
        FramedElement outerFrame;
        Group group;

        static void goBack();
        static void load();

        static LoadScreen *instance;

        void centerElements();

    public:
        explicit LoadScreen(const ElementParent &parent);

        static LoadScreen *getInstance() {
            return LoadScreen::instance;
        }
        vector<char> &render(bool shouldNotifyParent) final {
            this->flushFramebuffer();
            framebuffer.assign(framebuffer.size(), ' ');
            return Element::render(shouldNotifyParent);
        }
    };
}
