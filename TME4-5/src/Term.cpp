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
	static_cast<Instance*>(owner_)->add(this);
}

Term::~Term ()
{
	delete &node_;
	if(type_ == Term::External)
	{
		static_cast<Cell*>(owner_)->remove(this);
	}
	else
	{
		static_cast<Instance*>(owner_)->remove(this);
	}
}

void Term::setNet(Net* n)
{
	if(n)
	{
		net_ = n;
		n->add(&node_);
	}
	else
	{
		net_->remove(&node_);
		net_ = n;
	}
}

void Term::setNet(const std::string& s)
{
	Term::setNet(static_cast<Cell*>(owner_)->getNet(s));
}

void Term::setPosition (const Point& p)
{
	node_.setPosition(p);
}

void Term::setPosition (int x, int y)
{
	node_.setPosition(x,y);
}

void Term::toXml(std::ostream& o)
{
	std::string dir;
	switch(direction_)
	{
		case Term::In :
			dir = "In";
			break;
		case Term::Out :
			dir = "Out";
			break;
		case Term::Inout :
			dir = "Inout";
			break;
		case Term::Tristate :
			dir = "Tristate";
			break;
		case Term::Transcv :
			dir = "Transcv";
			break;
		default :
			dir = "Unknown";
	}
	o << indent << "<term name=\"" << name_ << "\"";
	o << " direction=\"" << dir << "\"/>";
	o << std::endl;
}
