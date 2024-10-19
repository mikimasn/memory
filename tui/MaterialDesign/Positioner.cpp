
#include "Positioner.h"

void Memory::tui::Positioner::center(Element &parent, ElementChild &child) {
    auto pos = center(parent.getSize(), child.element->getSize());
    child.x = pos.first;
    child.y = pos.second;
}
