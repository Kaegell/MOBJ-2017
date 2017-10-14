#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <list>
#include <algorithm>
#include "Timer.h"
#include "GPL_2_text.h"

using namespace std;

namespace vector_bench
{
	void backInsert()
	{
		vector<string> GPL_2_vector;
		for(int i = 0;GPL_2_text[i] != NULL; i++)
		{
			GPL_2_vector.push_back(string(GPL_2_text[i]));
		}

		sort(GPL_2_vector.begin(),GPL_2_vector.end());
	}

	void frontInsert()
	{
		vector<string> GPL_2_vector;
		for(int i = 0;GPL_2_text[i] != NULL; i++)
		{
			GPL_2_vector.insert(GPL_2_vector.end(), GPL_2_text[i]);
		}

		sort(GPL_2_vector.begin(),GPL_2_vector.end());
	}

	void sortEachInsert()
	{
		vector<string> GPL_2_vector;
		for(int i = 0;GPL_2_text[i] != NULL; i++)
		{
			GPL_2_vector.insert(GPL_2_vector.end(), GPL_2_text[i]);
			sort(GPL_2_vector.begin(),GPL_2_vector.end());
		}
	}
}

namespace list_bench
{
	void backInsert()
	{
		list<string> GPL_2_list;
		for(int i = 0;GPL_2_text[i] != NULL; i++)
		{
			GPL_2_list.push_back(GPL_2_text[i]);
		}

		GPL_2_list.sort();
	}

	void frontInsert()
	{
		list<string> GPL_2_list;
		for(int i = 0;GPL_2_text[i] != NULL; i++)
		{
			GPL_2_list.push_front(GPL_2_text[i]);
		}

		GPL_2_list.sort();
	}

	void sortEachInsert()
	{
		list<string> GPL_2_list;
		for(int i = 0;GPL_2_text[i] != NULL; i++)
		{
			GPL_2_list.push_front(GPL_2_text[i]);
			GPL_2_list.sort();
		}
	}
}

namespace map_bench
{
	void insert()
	{
		string str;
		map<string,int> GPL_2_map;
		map<string,int>::iterator it;
		for(int i = 0; GPL_2_text[i] != NULL; i++)
		{
			str = string(GPL_2_text[i]);
			it = GPL_2_map.find(str);
			if (it != GPL_2_map.end())
			{
				it->second++;
			}
			else
			{
				GPL_2_map.insert(pair<string,int>(str,1));
			}
		}
	}
}

int main ( int argc, char* argv[] )
{

	Timer t;

	cout << "Vector Bench Test" << endl;
	t = t.start();
	vector_bench::backInsert    ();
	t = t.stop();
	cout << "backInsert exec. time : " << t << endl;
	t = t.start();
	vector_bench::frontInsert   ();
	t = t.stop();
	cout << "frontInsert exec. time : " << t << endl;
	t = t.start();
	vector_bench::sortEachInsert();
	t = t.stop();
	cout << "sortEachInsert exec. time : " << t << endl << endl;

	cout << "List Bench Test" << endl;
	t = t.start();
	list_bench::backInsert    ();
	t = t.stop();
	cout << "backInsert exec. time : " << t << endl;
	t = t.start();
	list_bench::frontInsert   ();
	t = t.stop();
	cout << "frontInsert exec. time : " << t << endl;
	t = t.start();
	list_bench::sortEachInsert();
	t = t.stop();
	cout << "sortEachInsert exec. time : " << t << endl << endl;

	cout << "Map Bench Test" << endl;
	t = t.start();
	map_bench::insert    ();
	t = t.stop();
	cout << "insert exec. time : " << t << endl << endl;
	return 0;
}
