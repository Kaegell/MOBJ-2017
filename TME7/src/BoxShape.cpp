#include "Symbol.h"
#include "Shape.h"
#include "Box.h"
#include "XmlUtil.h"
#include <libxml/xmlreader.h>

using namespace Netlist;

BoxShape::BoxShape(Symbol* owner, const Box& box)
    :Shape(owner), box_(box)
{}

BoxShape::BoxShape(Symbol* owner, int x1 , int y1, int x2, int y2)
    :Shape(owner),box_(x1,y1,x2,y2)
{}

BoxShape::~BoxShape()
{}

Box BoxShape::getBoundingBox() const
{return box_;}

BoxShape* BoxShape::fromXml(Symbol* owner, xmlTextReaderPtr reader)
{
    BoxShape* boxshape = NULL;
    const xmlChar* boxTag = xmlTextReaderConstString(reader,(const xmlChar*)"box");
    const xmlChar* nodeName=xmlTextReaderConstLocalName(reader);

    if(boxTag == nodeName)
    {
        std::string x1_ = xmlCharToString(
                xmlTextReaderGetAttribute(reader,(const xmlChar*)"x1"));
        std::string y1_ = xmlCharToString(
                xmlTextReaderGetAttribute(reader,(const xmlChar*)"y1"));
        std::string x2_ = xmlCharToString(
                xmlTextReaderGetAttribute(reader,(const xmlChar*)"x2"));
        std::string y2_ = xmlCharToString(
                xmlTextReaderGetAttribute(reader,(const xmlChar*)"y2"));
        if(x1_.empty() or y1_.empty() or x2_.empty() or y2_.empty())
            return boxshape;
        boxshape = new BoxShape(owner,x2_.c_str(),y2_.c_str(),x2_.c_str(),y2_.c_str());
    }
    return boxshape;
}

void BoxShape::toXml(std::ostream& o)
{
   o << indent << "<box x1=\"" << this.x1_ << "\" y1=\"" << this.y1_
       << "\" x2=\"" << this.x2_ << "\" y2=\"" << this.y2_ << "\"/>";
}
