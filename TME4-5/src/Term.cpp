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
	owner_(c), name_(name), direction_(d)
{
	type_ = Term::External;
	net_ = NULL;
	node_ = Node (this);
}

Term::Term (Instance* i, const Term* modelTerm) :
	owner_(i)
{
	type_ = Term::Internal;
	name_ = modelTerm->getName();
	net_ = NULL;
	direction_ = modelTerm->getDirection();
	node_ = Node (this);
}

Term::~Term ()
{
	delete node_;
}

void Term::setNet(Net* n)
{
	net_ = n;
	n->add(node_);
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
