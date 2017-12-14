#include "Symbol.h"
#include "Shape.h"
#include "Box.h"
#include "XmlUtil.h"
#include <libxml/xmlreader.h>

using namespace Netlist;

TermShape::TermShape( Symbol* owner , string  name , int x1, int y1 )
    :Shape(owner), term_(NULL), x1_(x1), y1_(y1), align_(TermShape::TopLeft)
{
    Cell* cell = getCell ();
    term_ = cell ->getTerm( name );
}

TermShape::~TermShape()
{}

Box TermShape::getBoundingBox() const
{return Box(x1_, y1_,x1_, y1_);}

void setNameAlign(NameAlign align)
{align_ = align;}

TermShape* TermShape::fromXml(Symbol* owner, xmlTextReaderPtr reader)
{
    TermShape* termshape = NULL;
    const xmlChar* termTag = xmlTextReaderConstString(reader,(const xmlChar*)"term");
    const xmlChar* nodeName=xmlTextReaderConstLocalName(reader);

    if(termTag == nodeName)
    {
        std::string name_ = xmlCharToString(
                xmlTextReaderGetAttribute(reader,(const xmlChar*)"name"));
        std::string x1_ = xmlCharToString(
                xmlTextReaderGetAttribute(reader,(const xmlChar*)"x1"));
        std::string y1_ = xmlCharToString(
                xmlTextReaderGetAttribute(reader,(const xmlChar*)"y1"));
        std::string align_ = xmlCharToString(
                xmlTextReaderGetAttribute(reader,(const xmlChar*)"align"));
        if(x1_.empty() or y1_.empty() or align_.empty() or name_.empty())
            return termshape;
        termshape = new TermShape(owner,name,x1_.c_str(),y1_.c_str());
    }
    return termshape;
}

void TermShape::toXml(std::ostream& o)
{
   o << indent << "<term name=\"" << this.term_->getName
       << "\" x1=\"" << this.x1_ << "\" y1=\"" << this.y1_
       << "\" x2=\"" << this.x2_ << "\" y2=\"" << this.y2_ << "\"/>";
}
