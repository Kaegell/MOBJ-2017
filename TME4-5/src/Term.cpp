#include <iostream>
#include <vector>
#include "Indentation.h"
#include "Net.h"
#include "Node.h"
#include "Cell.h"
#include "Term.h"
#include "Point.h"

using namespace Netlist;

Term::Term (Cell* c, const std::string& name, Term::Direction d) :
	owner_((void*)c),
	name_(name),
	direction_(d),
	type_(Term::External),
	net_(NULL),
	node_(this)
{
	static_cast<Cell*>(owner_)->add(this);
}

Term::Term (Instance* i, const Term* modelTerm) :
	owner_((void *)i),
	name_(modelTerm->getName()),
	direction_(modelTerm->getDirection()),
	type_(Term::Internal),
	net_(NULL),
	node_(this)
{
}

Term::~Term ()
{
	delete &node_;
}

void Term::setNet(Net* n)
{
	net_ = n;
	n->add(&node_);
	if(type_ == Term::External)
	{
	static_cast<Cell*>(owner_)->remove(this);
	}
}

void Term::setNet(const std::string& s)
{
}

void Term::setPosition (const Point& p)
{
	node_.setPosition(p);
}

void Term::setPosition (int x, int y)
{
	node_.setPosition(x,y);
}
