// -*- explicit-buffer-name: "Node.cpp<M1-MOBJ/4-5>" -*-

#include  <limits>
#include  "Node.h"
#include  "Term.h"
#include  "Net.h"
#include  "Instance.h"
#include  "Cell.h"
#include <libxml/xmlreader.h>
#include "XmlUtil.h"

namespace Netlist {

    using namespace std;


    const size_t  Node::noid = numeric_limits<size_t>::max();


    Node::Node ( Term* term, size_t id  )
        : id_      (id)
          , term_    (term)
          , position_()
    { }


    Node::~Node ()
    {
        if (getNet()) getNet()->remove( this );
    }


    inline Net* Node::getNet () const { return term_->getNet(); }


    void Node::toXml(std::ostream& o)
    {
        o << indent << "<node term=\"" << term_-> getName() << "\"";
        if(term_->isInternal())
        {
            o << " instance=\"" << term_->getInstance()->getName() << "\"";
        }
        o << " id=\"" << id_ << "\"";
        o << " x=\"" << position_.getX() << "\"";
        o << " y=\"" << position_.getY() << "\"/>";
        o << endl;
    }

    bool Node::fromXml(Net* net, xmlTextReaderPtr reader)
    {
        bool ret;
        int x,y;
        std::string term = xmlCharToString(xmlTextReaderGetAttribute(reader,(const xmlChar*)"term"));
        std::string id = xmlCharToString(xmlTextReaderGetAttribute(reader,(const xmlChar*)"id"));
        std::string instance = xmlCharToString(xmlTextReaderGetAttribute(reader,(const xmlChar*)"instance"));
        std::string x_str = xmlCharToString(xmlTextReaderGetAttribute(reader,(const xmlChar*)"x"));
        std::string y_str = xmlCharToString(xmlTextReaderGetAttribute(reader,(const xmlChar*)"y"));
        if(term.empty() || id.empty())
            return false;
        if(not(x_str.empty() || y_str.empty()))
        {
            x = atoi(x_str.c_str());
            y = atoi(y_str.c_str());
        }
        if(!instance.empty())
        {
            ret = net->getCell()->getInstance(instance)->connect(term,net);
            if(!ret) return false;
            if(not(x_str.empty() && y_str.empty()))
                net->getCell()->getInstance(instance)->getFromTerms(term)->setPosition(x,y);
            return true;
        }
        ret = net->getCell()->connect(term,net);
        if(!ret) return false;
        if(not(x_str.empty() && y_str.empty()))
            net->getCell()->getTerm(term)->setPosition(x,y);
        return true;
    }
}  // Netlist namespace.
