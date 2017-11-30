#ifndef NETLIST_TERM_H
#define NETLIST_TERM_H
#include <iostream>
#include <vector>
#include "Indentation.h"
#include "Node.h"
#include "Cell.h"
#include "Term.h"
#include "Point.h"
#include "Instance.h"

namespace Netlist
{
    class Instance;
    class Cell;

    class Term
    {
        friend class Instance;
        public:
        enum Type { Internal = 1, External = 2 };
        enum Direction { In = 1, Out = 2, Inout = 3, Tristate = 4, Transcv = 5, Unknown = 6 };
        static std::string toString (Type t);
        static std::string toString (Direction d);
        static Direction toDirection (std::string s);
        static Term* fromXml (Cell* c, xmlTextReaderPtr reader);

        Term (Cell* c, const std::string& name, Direction d);
        Term (Instance* i, const Term* modelTerm);
        ~Term ();

        inline bool isInternal() const
        {return type_ == Internal;}

        inline bool isExternal() const
        {return type_ == External;}

        inline const std::string& getName() const
        {return name_;}

        inline Node* getNode()
        {return &node_;}

        inline Net* getNet()
        {return net_;}

        inline Cell* getCell() const
        {return (type_ == External) ? static_cast<Cell*>(owner_) :
            NULL;}

        inline Cell* getOwnerCell()
        {return (type_ == External) ? static_cast<Cell*>(owner_) :
            static_cast<Instance*>(owner_)->getCell();}

        inline Instance* getInstance() const
        {return (type_ == Internal) ? static_cast<Instance*>(owner_) :
            NULL;}

        inline Direction getDirection() const
        {return direction_;}

        inline Point getPosition() const
        {return node_.getPosition();}

        inline Type getType() const
        {return type_;}

        void setNet(Net* n);
        void setNet(const std::string& s);
        inline void setDirection (Direction d)
        {direction_ = d;}
        void setPosition (const Point& p);
        void setPosition (int x, int y);
        void toXml(std::ostream& o);
        private:
        void*         owner_;
        std::string   name_;
        Direction     direction_;
        Type          type_;
        Net*          net_;
        Node          node_;
    };
}
#endif
