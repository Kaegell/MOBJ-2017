#include <iostream>
#include <vector>
#include "Cell.h"
#include "Term.h"
#include "Net.h"
#include "Point.h"

using namespace Netlist;

Net::Net (Cell* c, const std::string& s, Term::Type t) :
	owner_(c), name_(s), type_(t)
{
	nodes_ = new vector;
	id_ = owner.newNetId();
	owner.add(this);
}

Net::~Net ()
{
	owner.remove(this);
}

Cell* Net::getCell () const
{
	return (type_ == Term::External) ? owner :
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

void add (Node* n)
{
	size_t id = getFreeNodeId();
	nodes_.insert(nodes_.begin()+id, n);
}

bool remove (Node* n)
{return true;}
