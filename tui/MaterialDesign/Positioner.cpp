
#include "Positioner.h"

void Memory::tui::Positioner::center(Element &parent, ElementChild &child, CenterDescriptor desc) {
    auto pos = center(parent.getSize(), child.element->getSize());
    if(desc.x) child.x = pos.first;
    if(desc.y) child.y = pos.second;
}

std::vector<Memory::tui::PositionerPosition> Memory::tui::Positioner::devideinto(Memory::tui::Element &parent, int rows, int cols) {
    std::vector<PositionerPosition> positions;
    int width = parent.getSize().width / cols;
    int height = parent.getSize().height / rows;
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            positions.push_back({j*width, i*height, {width, height}});
        }
    }
    return positions;
}

