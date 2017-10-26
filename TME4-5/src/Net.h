#ifndef NETLIST_NET_H
#define NETLIST_NET_H

#include <iostream>
#include <vector>
#include "Cell.h"
#include "Term.h"
#include "Point.h"

namespace Netlist
{
	class Cell;
	class Term;

	class Net
	{
		public :
			 Net (Cell* c, const std::string& s, Term::Type t);
			 ~Net ();

			 Cell* getCell () const;
			 const std::string& getName () const;
			 unsigned int getId () const;
			 Term::Type getType () const;
			 const std::vector<Node*>& getNodes () const;
			 size_t getFreeNodeId () const;

			 void add (Node* n);
			 bool remove (Node* n);
		private :
			Cell* owner_;
			std::string name_;
			unsigned int id_;
			Term::Type type_;
			std::vector<Node*> nodes_;
	};
}



#endif
