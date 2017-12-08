#include <iostream>
#include <vector>
#include "Indentation.h"
#include "Cell.h"
#include "Term.h"
#include "Point.h"
#include <libxml/xmlreader.h>
#include "XmlUtil.h"

using namespace Netlist;

Instance::Instance (Cell* owner, Cell* model, const std::string& s) :
	owner_(owner),
	masterCell_(model),
	name_(s),
	terms_(),
	position_()
{
	for (std::vector<Term*>::const_iterator it = model->getTerms().begin();
			it != model->getTerms().end();
			it++)
	{
		new Term(this, *it);
	}
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

Term* Instance::getFromTerms ( const std::string& name ) const
{
	for ( std::vector<Term*>::const_iterator iterm=terms_.begin() ; iterm != terms_.end() ; ++iterm ) {
	  if ((*iterm)->getName() == name)  return *iterm;
	}
	return NULL;
}

bool Instance::connect (const std::string& name, Net* n)
{
    Term* term = getFromTerms(name);
    if (term == NULL) return false;
 
    term->setNet(n);
    return true;
}

void Instance::add(Term* t)
{
	terms_.push_back(t);
}

void Instance::remove (Term* t)
{
    for ( std::vector<Term*>::iterator iterm=terms_.begin() ; iterm != terms_.end() ; ++iterm ) {
      if (*iterm == t) terms_.erase( iterm );
	}
}

void Instance::setPosition (const Point& p)
{
	position_ = p;
}

void Instance::setPosition (int x, int y)
{
	position_ = Point (x, y);
}

void Instance::toXml(std::ostream& o)
{
	o << indent << "<instance name=\"" << name_ << "\"";
	o << " mastercell=\"" << masterCell_->getName() << "\"";
	o << " x=\"" << position_.getX();
	o << " y=\"" << position_.getY();
	o << "/>" << std::endl;
}

Instance* Instance::fromXml(Cell* c, xmlTextReaderPtr reader)
{
	std::string name = xmlCharToString(xmlTextReaderGetAttribute(reader,(const xmlChar*)"name"));
	std::string mastercell= xmlCharToString(xmlTextReaderGetAttribute(reader,(const xmlChar*)"mastercell"));
	std::string x_str = xmlCharToString(xmlTextReaderGetAttribute(reader,(const xmlChar*)"x"));
	std::string y_str = xmlCharToString(xmlTextReaderGetAttribute(reader,(const xmlChar*)"y"));

	if(name.empty() || mastercell.empty()
			|| x_str.empty() || y_str.empty())
	{
		return NULL;
	}

	int x = atoi(x_str.c_str());
	int y = atoi(y_str.c_str());

	Cell* model;
	if(!(model = Cell::find(mastercell)))
		return NULL;
	Instance* instance = new Instance(c,model,name);
	instance->setPosition(x,y);
	return instance;
}
