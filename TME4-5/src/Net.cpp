#include <iostream>
#include <vector>
#include "Cell.h"
#include "Term.h"
#include "Net.h"
#include "Point.h"

using namespace Netlist;

Net::Net (Cell* c, const std::string& s, Term::Type t) :
	owner_(c),
	name_(s),
	id_(owner_->newNetId()),
	type_(t),
	nodes_()
{
	owner_->add(this);
}

Net::~Net ()
{
	owner_->remove(this);
}

Cell* Net::getCell () const
{
	return (type_ == Term::External) ? owner_ :
		NULL;
}

const std::string& Net::getName () const
{return name_;}

unsigned int Net::getId () const
{return id_;}

Term::Type Net::getType () const
{return type_;}

const std::vector<Node*>& Net::getNodes () const
{return nodes_;}

size_t Net::getFreeNodeId () const
{
	size_t id = 0;
	for (std::vector<Node*>::const_iterator it = nodes_.begin();
			(it != nodes_.end()) && (*it != NULL);
			it++)
	{
		id++;
	}
	if (id == nodes_.size() - 1)
		id++;
	return id;
}

void Net::add (Node* n)
{
	size_t id = Net::getFreeNodeId();
	nodes_.insert(nodes_.begin()+id, n);
}

bool Net::remove (Node* n)
{return true;}
