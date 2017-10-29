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
	terms_.insert(terms_.begin(), model->getTerms().begin(), model->getTerms().end());
	owner_->add(this);
}

Instance::~Instance ()
{
	for (std::vector<Term*>::iterator it = terms_.begin();
			it != terms_.end();
			it++)
	{
		delete *it;
	}
	owner_->remove(this);
}

bool Instance::connect (const std::string& name, Net* n)
{
	return owner_->connect(name,n);
}

void Instance::add(Term* t)
{
	owner_->add(t);
}

void Instance::remove (Term* t)
{
	owner_->remove(t);
}

void Instance::setPosition (const Point& p)
{
	position_ = p;
}

void Instance::setPosition (int x, int y)
{
	position_ = Point (x, y);
}
