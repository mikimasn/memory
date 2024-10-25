#include "SaveScreen.h"
#include "../../game/Application.h"

void Memory::tui::SaveScreen::closeDialog() {
    Memory::game::Application::popWindowStack();
}

void Memory::tui::SaveScreen::centerElements() {
    Positioner::center(*this, this->getChild(0));
    Positioner::center(frame, frame.getChild(0), {true, false});
    Positioner::center(frame, frame.getChild(1), {true, false});
    Positioner::center(frame, frame.getChild(2), {true, false});
}

void Memory::tui::SaveScreen::saveAndClose() {
    return;
}

Memory::tui::SaveScreen::SaveScreen(const Memory::tui::ElementParent &parent) : Sheet(parent),
                                                                                Title({10, 1}, "Enter Path"),
                                                                                path({min(this->getSize().width - 6,
                                                                                          146), 1}),
                                                                                closeButton({7, 1}, "[Close]",
                                                                                            closeDialog),
                                                                                saveButton({7, 1}, "[Save]",
                                                                                           saveAndClose),
                                                                                frame({min(
                                                                                        this->getSize().width - 2, 150),
                                                                                       7}, '#'),
                                                                                outerFrame(
                                                                                        {min(
                                                                                                this->getSize().width,
                                                                                                152), 9}, ' '),
                                                                                group({7 + 2 + 7, 1}) {
    outerFrame.updateParent(ElementParent{this, this->addChild(&outerFrame, 0, 0)});
    frame.updateParent(ElementParent{&outerFrame, outerFrame.addChild(&frame, 1, 1)});
    path.updateParent(ElementParent{&frame, frame.addChild(&path, 2, 3)});
    path.setInput(Memory::game::Application::getCwd());
    Title.updateParent(ElementParent{&frame, frame.addChild(&Title, 2, 1)});
    saveButton.updateParent(ElementParent{&group, group.addChild(&saveButton, 0, 0)});
    closeButton.updateParent(ElementParent{&group, group.addChild(&closeButton, 8, 0)});
    group.updateParent(ElementParent{&frame, frame.addChild(&group, 2, 5)});
    centerElements();
    instance = this;
}
