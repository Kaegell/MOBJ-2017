#include <iostream>
#include <vector>
#include "Indentation.h"
#include "Cell.h"
#include "Term.h"
#include "Point.h"

using namespace Netlist;

Instance::Instance (Cell* owner, Cell* model, const std::string& s) :
	owner_(owner),
	masterCell_(model),
	name_(s),
	terms_(),
	position_()
{
}

Instance::~Instance ()
{
}

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
