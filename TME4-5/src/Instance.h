#ifndef NETLIST_INSTANCE_H
#define NETLIST_INSTANCE_H
#include <iostream>
#include <vector>
#include "Indentation.h"
#include "Cell.h"
#include "Point.h"

namespace Netlist
{
	class Instance
	{
		public:
			Instance (Cell* owner, Cell* model, const std::string& s);
			~Instance ();

			inline const std::string& getName () const
			{return name_;}

			inline Cell* getMasterCell () const
			{return masterCell_;}
			
			inline Cell* getCell () const
			{return owner_;}

			inline const std::vector<Term*>& getTerms () const
			{return terms_;}

			inline Term* getTerm (const std::string& s) const
			{return NULL;}

			inline Point getPosition () const
			{return position_;}

			bool connect (const std::string& name, Net* n);
			void add (Term* t);
			void remove (Term* t);
			void setPosition (const Point& p);
			void setPosition (int x, int y);
		private:
			Cell* owner_;
			Cell* masterCell_;
			std::string name_;
			std::vector<Term*> terms_;
			Point position_;
	};
}

#endif
