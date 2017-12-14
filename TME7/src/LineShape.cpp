#include "Symbol.h"
#include "Shape.h"
#include "Box.h"
#include "XmlUtil.h"
#include <libxml/xmlreader.h>

using namespace Netlist;

LineShape::LineShape(Symbol* owner, int x1, int y1,int x2, int y2)
    :Shape(owner),x1_(x1),y1_(y1),x2_(x2),y2_(y2)
{} 

LineShape::~LineShape()
{}

Box LineShape::getBoundingBox()
{return Box(x1_,y1_,x2_,y2_);}

LineShape* LineShape::fromXml(Symbol* owner, xmlTextReaderPtr reader)
{
    LineShape* lineshape = NULL;
    const xmlChar* lineTag = xmlTextReaderConstString(reader,(const xmlChar*)"line");
    const xmlChar* nodeName=xmlTextReaderConstLocalName(reader);

    if(lineTag == nodeName)
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
            return lineshape;
        lineshape = new LineShape(owner,x2_.c_str(),y2_.c_str(),x2_.c_str(),y2_.c_str());
    }
    return lineshape;
}

void BoxShape::toXml(std::ostream& o)
{
   o << indent << "<line x1=\"" << this.x1_ << "\" y1=\"" << this.y1_
       << "\" x2=\"" << this.x2_ << "\" y2=\"" << this.y2_ << "\"/>";
}
