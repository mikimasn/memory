#include "../UI/Element.h"

namespace Memory::tui{
    class Positioner {
    public:
        static std::pair<int,int> center(ElementSize parent, ElementSize child){
            return {(parent.width-child.width)/2, (parent.height-child.height)/2};
        };
        static void center(Element& parent, ElementChild& child);
    };
}