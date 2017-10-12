#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include "Timer.h"
#include "GPL_2_text.h"

using namespace std;

void backInsert()
{
	vector<string> GPL_2_vector (GPL_2_text, GPL_2_text + sizeof(GPL_2_text)/sizeof(char*));
	cerr << "GPL_2_vector created" << endl;
	
	vector<string>::iterator it;
	vector<string>::iterator it_begin = GPL_2_vector.begin();
	vector<string>::iterator it_end = GPL_2_vector.end();

	for(vector<string>::const_iterator it = it_begin; it != it_end; ++it)
	{
		cout << *it << " ";
	}

	sort(GPL_2_vector.begin(),GPL_2_vector.end());


	for(vector<string>::const_iterator it = it_begin; it != it_end; ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
}

int main ( int argc, char* argv[] )
{

	Timer t;
	t = t.start();
	backInsert    ();
	t = t.stop();
	cout << "backInsert exec. time : " << t << endl;
	//frontInsert   ();
	//sortEachInsert();

	return 0;
}
