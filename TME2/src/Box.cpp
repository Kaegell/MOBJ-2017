#include <iostream>
#include "Box.h"
using namespace tme2;
using namespace std;

int Box::count = 0;

Box::Box() : name_("unknown"), x1_(1), y1_(1), x2_(-1), y2_(-1)
{
	count++;
	cerr << "Debug : Box::Box() ";
	print(cerr);
	cerr << endl;
}

Box::Box(std::string name, long x1, long y1, long x2, long y2) :
	name_(name), x1_(x1), y1_(y1), x2_(x2), y2_(y2)
{
	count++;
	cerr << "Debug : Box::Box( std::string, ... ) ";
	print(cerr);
	cerr << endl;
}

Box::Box(const Box& other) :
	name_(other.name_), x1_(other.x1_), y1_(other.y1_), x2_(other.x2_), y2_(other.y2_)
{
	count++;
	name_ += "_c";
	cerr << "Debug : Box::Box( const Box& ) ";
	print(cerr);
	cerr << endl;
}

Box::~Box()
{
	count--;
	cerr << "Debug : Box::~Box() ";
	print(cerr);
	cerr << endl;
}

bool Box::intersect(const Box& other) const
{
	return !isEmpty() || !other.isEmpty() 
		|| ((x2_ >= other.x1_) && (x1_ <= other.x2_)
		&& (y2_ >= other.y1_) && (y1_ <= other.y2_));
}

void Box::print(std::ostream& o) const
{
	std::string str;
	str = str + "<\"" + name_ + "\""
		+ "[" + std::to_string(x1_)
		+ " " + std::to_string(y1_)
		+ " " + std::to_string(x2_)
		+ " " + std::to_string(y2_) + "]>";
	o << str << endl;
	//o.operator<<(str).operator<<(endl);
}

void Box::makeEmpty()
{
	int midx = (x1_ + x2_) / 2;
	int midy = (y1_ + y2_) / 2;
	x1_ = midx;
	y1_ = midy;
	x2_ = midx;
	y2_ = midy;
}

void Box::inflate (long dxy)
{
	x1_ -= dxy;
	y1_ -= dxy;
	x2_ += dxy;
	y2_ += dxy;
	if((x2_<=x1_) || (y2_<=y1_)) makeEmpty();
}

void Box::inflate (long dx, long dy)
{
	x1_ -= dx;
	y1_ -= dy;
	x2_ += dx;
	y2_ += dy;
	if((x2_<=x1_) || (y2_<=y1_)) makeEmpty();
}

void Box::inflate(long dx1, long dy1, long dx2, long dy2)
{
	x1_ -= dx1;
	y1_ -= dy1;
	x2_ += dx2;
	y2_ += dy2;
	if((x2_<=x1_) || (y2_<=y1_)) makeEmpty();
}

Box Box::getIntersection(Box& other)
{
	if (intersect(other))
	{
		std::string name = name_ + "_" + other.name_;
		return Box (name,
				std::max(x1_, other.x1_),std::max(y1_, other.y1_),
				std::min(x2_, other.x2_),std::min(y2_, other.y2_));
	}
	return Box ();
}

Box Box::operator&&(Box& other) { return getIntersection(other); }
