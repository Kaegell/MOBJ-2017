#include <iostream>
#include "Box.h"

using namespace tme2;
using namespace std;

ostream& operator<< (ostream& o, const Box& b)
{
	b.print(o);
	return o;
}

Box testFunction(Box& ab)
{
	cerr << " + testFunction() called" << endl;
	Box area ( "area", 0, 0, 15, 50 );
	if (area.intersect(ab))
	{
		Box ib = area and ab;
		cerr << " | Intersection between:" << endl;
		cerr << " |   " << area << endl;
		cerr << " |   " << ab   << endl;
		cerr << " | Gives:" << endl;
		cerr << " |   " << ib << endl;
	}
	else
		cout << " No intersection" << endl;
	
	return ab;
}

int main(int argc, char* argv[])
{
	Box b0;
	Box b1 ( "b1", 15, 10, 30, 20 );
	cerr << "Allocated boxes: " << Box::getAllocateds() << endl;
	
	cerr << "\nTest1: "; b1.print(cerr); cerr << endl;
	testFunction(b1);

	b1.inflate(5, 5, 5, 5);
	cerr << "\nTest2: "; b1.print(cerr); cerr << endl;
	testFunction(b1);

	cerr << "\nTest3: " << endl;
	cerr << "+ Box\"" << b1.getName() << "\" empty:  "
		<< boolalpha << b1.isEmpty() << endl;
	cerr << "+ Box\"" << b1.getName() << "\" width:  "
		<< boolalpha << b1.getWidth() << endl;
	cerr << "+ Box\"" << b1.getName() << "\" height:  "
		<< boolalpha << b1.getHeight() << endl;
	b1.inflate(-11);
	cerr << "+ Box\"" << b1.getName() << "\" empty:  "
		<< boolalpha << b1.isEmpty() << "(inflated -11)\n";
	cerr << "+ Box\"" << b1.getName() << "\" width:  "
		<< boolalpha << b1.getWidth() << endl;
	cerr << "+ Box\"" << b1.getName() << "\" height:  "
		<< boolalpha << b1.getHeight() << endl;

	cerr << "Allocated boxes: " << Box::getAllocateds() << endl;
}
