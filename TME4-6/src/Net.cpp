#include <iostream>
#include <vector>
#include "Indentation.h"
#include "Cell.h"
#include "Term.h"
#include "Net.h"
#include "Point.h"
#include <libxml/xmlreader.h>
#include "XmlUtil.h"

using namespace Netlist;
using namespace std;

Net::Net (Cell* c, const std::string& s, Term::Type t) :
	owner_(c),
	name_(s),
	id_(owner_->newNetId()),
	type_(t),
	nodes_()
{
	owner_->add(this);
	id_ = owner_->newNetId();
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
	if(n->getId() == Node::noid)
	{
		nodes_.insert(nodes_.begin()+id, n);
	}
	else
	{
		nodes_.insert(nodes_.begin()+n->getId(), n);
	}
	n->setId(id);
}

bool Net::remove (Node* n)
{
	for (std::vector<Node*>::iterator it = nodes_.begin();
			(it != nodes_.end()) && (it != nodes_.end());
			it++)
	{
		if(*it == n)
		{
			*it = NULL;
			return true;
		}
	}
	return false;
}

void Net::toXml(std::ostream& o)
{
	std::string typ;
	if(type_ == Term::Internal)
	{
		typ = "Internal";
	}
	else
	{
		typ = "External";
	}
	o << indent++ << "<net name=\"" << name_ << "\"";
	o << " type=\"" << typ << "\"/>";
	o << endl;
	for(std::vector<Node*>::const_iterator it = nodes_.begin();
			(it != nodes_.end());
			it++)
	{
		(*it)->toXml(o);
	}
	o << --indent << "</net>";
	o << endl;
}

//Net* Net::fromXml(Cell* c, xmlTextReaderPtr reader)
//{
//    std::cout << "now entering Net::fromXml()" << std::endl;
//
//	const xmlChar* netTag = xmlTextReaderConstString(reader, (const xmlChar*)"net");
//	const xmlChar* nodeTag = xmlTextReaderConstString(reader, (const xmlChar*)"node");
//
//	Net* net = NULL;
//
//	while(true)
//	{
//		const xmlChar* nodeName = xmlTextReaderConstLocalName( reader );
//
//        if(nodeName == netTag and xmlTextReaderNodeType(reader) == XML_READER_TYPE_ELEMENT)
//        {
//            std::string netName = xmlCharToString(
//                    xmlTextReaderGetAttribute(reader, (const xmlChar*)"name"));
//            std::string netTypeStr= xmlCharToString(
//                    xmlTextReaderGetAttribute(reader, (const xmlChar*)"type"));
//            if (netName.empty() or netTypeStr.empty())
//            {
//                return NULL;
//            }
//            Term::Type netType;
//            if(netTypeStr == "Internal")
//                netType = Term::Internal;
//            else
//                netType = Term::External;
//            std::cout << netName << std::endl;
//            net = new Net(c,netName, netType);
//            if(!net) return NULL;
//            continue;
//        }
//
//		int status = xmlTextReaderRead(reader);
//		if (status != 1) {
//			if (status != 0) {
//				cerr << "[ERROR] Cell::fromXml(): Unexpected termination of the XML parser." << endl;
//			}
//			break;
//		}
//
//
//        if(nodeName == nodeTag and xmlTextReaderNodeType(reader) == XML_READER_TYPE_END_ELEMENT)
//        {
//            if (Node::fromXml(net,reader)) continue;
//        }
//
//        if(nodeName == netTag and xmlTextReaderNodeType(reader) == XML_READER_TYPE_END_ELEMENT)
//        {
//            break;
//        }
//
//		cerr << "[ERROR] Net::fromXml(): Unknown or misplaced tag <" << nodeName
//			<< "> (line:" << xmlTextReaderGetParserLineNumber(reader) << ")." << endl;
//		break;
//	}
//    return net;
//}

Net* Net::fromXml(Cell* c, xmlTextReaderPtr reader){
    Net* net = NULL;

    const xmlChar* nodeTag  = xmlTextReaderConstString        ( reader, (const xmlChar*)"net" );
    const xmlChar* nodeName = xmlTextReaderConstLocalName     ( reader );


    if((nodeTag == nodeName) and !(xmlTextReaderNodeType(reader) == XML_READER_TYPE_END_ELEMENT))
    {

        std::string netName = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"name" ) );
        std::string netType = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"type" ) );


        //Term::Type t = Term::toType(netType);
        Term::Type t;
            if(netType == "Internal")
                t = Term::Internal;
            else
                t = Term::External;

        net = new Net(c, netName, t);
        const xmlChar* nTag     = xmlTextReaderConstString        ( reader, (const xmlChar*)"node" );
        //const xmlChar* lineTag  = xmlTextReaderConstString        ( reader, (const xmlChar*)"line" );


        while(!((nodeTag == nodeName) and (xmlTextReaderNodeType(reader) == XML_READER_TYPE_END_ELEMENT))){

            xmlTextReaderRead(reader);

            switch ( xmlTextReaderNodeType(reader) ) {
                case XML_READER_TYPE_COMMENT:
                case XML_READER_TYPE_WHITESPACE:
                case XML_READER_TYPE_SIGNIFICANT_WHITESPACE:
                continue;
            }

            const xmlChar* tmpNodeName = xmlTextReaderConstLocalName     ( reader );

            if(tmpNodeName == nTag){
                if( !(Node::fromXml(net, reader)) ) return NULL;
            }
            //if(tmpNodeName == lineTag){
             //   if( !(Line::fromXml(net, reader)) ) return NULL;
            //}
        }
    }
    return net;
}
