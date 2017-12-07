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

Net* Net::fromXml(Cell* c, xmlTextReaderPtr reader)
{

	const xmlChar* netTag = xmlTextReaderConstString(reader, (const xmlChar*)"net");
	const xmlChar* nodeTag = xmlTextReaderConstString(reader, (const xmlChar*)"node");

	enum State {
		Init = 0,
		BeginNet,
		BeginNode,
		EndNode,
		EndNet
	};

	Net* net = NULL;
	State state = BeginNet;

	while(true)
	{
		int status = xmlTextReaderRead(reader);
		if (status != 1) {
			if (status != 0) {
				cerr << "[ERROR] Cell::fromXml(): Unexpected termination of the XML parser." << endl;
			}
			break;
		}

		switch ( xmlTextReaderNodeType(reader) ) {
			case XML_READER_TYPE_COMMENT:
			case XML_READER_TYPE_WHITESPACE:
			case XML_READER_TYPE_SIGNIFICANT_WHITESPACE:
				continue;
		}

		const xmlChar* nodeName = xmlTextReaderConstLocalName( reader );

		switch(state)
		{
			case Init:
				if(netTag == nodeName)
				{
					state = BeginNet;
					std::string netName = xmlCharToString(
							xmlTextReaderGetAttribute(reader, (const xmlChar*)"name"));
					std::string netTypeStr= xmlCharToString(
							xmlTextReaderGetAttribute(reader, (const xmlChar*)"type"));
					if (not (netName.empty() or netTypeStr.empty()))
					{
						Term::Type netType;
						if(netTypeStr == "Internal")
							netType = Term::Internal;
						else
							netType = Term::External;
						net = new Net(c,netName, netType);
						state = BeginNode;
						continue;
					}
				}
				break;

			case BeginNode:
				if(nodeName == nodeTag
						and xmlTextReaderNodeType(reader) == XML_READER_TYPE_ELEMENT)
				{
					state = EndNet;
					continue;
				}
				break;

			case EndNode:
				if(nodeName == nodeTag
						and xmlTextReaderNodeType(reader) == XML_READER_TYPE_END_ELEMENT)
				{
					state = EndNet;
					continue;
				}
				else
				{
					if (Node::fromXml(net,reader)) continue;
				}
				break;
			case EndNet:
				if(nodeName == netTag
						and xmlTextReaderNodeType(reader) == XML_READER_TYPE_END_ELEMENT)
				{
					continue;
				}
				break;

			default:
				break;
		}
		cerr << "[ERROR] Net::fromXml(): Unknown or misplaced tag <" << nodeName
			<< "> (line:" << xmlTextReaderGetParserLineNumber(reader) << ")." << endl;
		break;
	}
	c->add(net);
	return net;
}
