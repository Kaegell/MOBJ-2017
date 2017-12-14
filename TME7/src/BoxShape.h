#ifndef NETLIST_BOXSHAPE_H
#define NETLIST_BOXSHAPE_H

#include "Symbol.h"
#include "Shape.h"
#include "Box.h"

namespace Netlist
{
    class  BoxShape : public  Shape {
        public:
            BoxShape         ( Symbol*, const  Box& );
            BoxShape         ( Symbol*, int x1 , int y1, int x2, int y2 );
            ~BoxShape         ();
            Box   getBoundingBox  ()  const;
            BoxShape* fromXml(Symbol* owner, xmlTextReaderPtr reader);
            void toXml(std::ostream&);
        private:
            Box   box_;
    };
}
#endif
