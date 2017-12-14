#ifndef NETLIST_SHAPE_H
#define NETLIST_SHAPE_H

#include "Symbol.h"
#include "Box.h"

namespace Netlist
{
    class  Shape {
        public:
            Shape ( Symbol* );
            virtual ~Shape();
            inline Symbol* getSymbol()  const;
            virtual Box getBoundingBox() const = 0;
        private:
            Symbol* owner_;
    };
}
#endif
