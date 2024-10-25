#pragma once

#include "../UI/Element.h"

namespace Memory::tui {
    struct PositionerPosition {
        int x;
        int y;
        ElementSize size;
    };
    struct CenterDescriptor {
        bool x = true;
        bool y = true;
    };

    class Positioner {
    public:
        static std::pair<int, int> center(ElementSize parent, ElementSize child) {
            return {(std::max(parent.width - child.width, 0)) / 2, (std::max(parent.height - child.height, 0)) / 2};
        };

        static void center(Element &parent, ElementChild &child, CenterDescriptor desc = {});

        static std::vector<PositionerPosition> devideinto(Element &parent, int rows, int cols);
    };
}
