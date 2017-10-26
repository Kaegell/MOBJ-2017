#include <iostream>
#include <vector>
#include "Indentation.h"
#include "Cell.h"
#include "Term.h"
#include "Point.h"

using namespace Netlist;

Instance (Cell* owner, Cell* model, const std::string& s);
~Instance ();

bool Instance::connect (const std::string& name, Net* n)
{
	return false;
}

void Instance::add(Term* t)
{
}

void Instance::remove (Term* t)
{
}

void Instance::setPosition (const Point& p)
{
}

void Instance::setPosition (int x, int y)
{
}
