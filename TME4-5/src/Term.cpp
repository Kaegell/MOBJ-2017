#include <iostream>
#include <vector>
#include "Indentation.h"
#include "Cell.h"
#include "Term.h"
#include "Point.h"

using namespace Netlist;

Term::Term (Cell* c, const std::string& name, Direction d) :
	owner_(c), name_(name), direction_(d)
{
	type_ = Term::External;
	net_ = NULL;
	node_ = new Node (this, Node::noid);
}

Term::Term (Instance* i, const Term* modelTerm) :
	owner_(i)
{
	type_ = Term::Internal;
	name_ = modelTerm.getName();
	net_ = NULL;
	direction_ = modelTerm.getDirection();
	node_ = new Node (this, Node::noid);
}

Term::~Term ()
{
	~node();
}

void Term::setNet(Net* n)
{
	net_ = n;
	n.add(node_);
}

void Term::setNet(const std::string& s)
{
	net_ = new Net(NULL,s,type_); 
}

void Term::setPosition (const Point& p)
{
	node_.setPosition(p);
}

void Term::setPosition (int x, int y)
{
	node_.setPosition(x,y);
}
