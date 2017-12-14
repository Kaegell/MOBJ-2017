#include <cstdlib>
#include "Symbol.h"
#include "Box.h"

using namespace Netlist;

Shape::Shape(Symbol* owner):
    owner_(owner)
{owner->add(this);}

Shape::~Shape()
{owner->remove(this);}

Shape::Symbol* getSymbol() const
{return owner_;}
