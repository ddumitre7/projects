//============================================================================
// Name        : 003-remove_k_th.cpp
// Author      : Dan
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <algorithm>

#include "SLinkedList.h"

using namespace std;

int main() {
	cout << "Starting...\n" << endl; // prints Starting...\n

	{
	SLinkedList<int> l;


	l.push_back(1900).push_back(1910).push_back(1920).push_back(1930);
	l.push_back(2900).push_back(2910).push_back(2920).push_back(3930);

	cout << "___________________________________" << endl << endl;

	cout << "\tThe list l is (SIZE " << l.size() << "): " << endl << "\t";

	print(l);

	l.delete_k_th(3);

	cout << "\tThe NEW list l is (SIZE " << l.size() << "): " << endl << "\t";

	print(l);
	}

	cout << endl;
	cout << "___________________________________" << endl << endl;

	{

	SLinkedList<string> lstr;

	string s1{"Chicago"};
	string s2{"London"};

	string s3{"Paris"};

	lstr.push_back(s1 + s2);
	lstr.push_back(s3);

	cout << "\tThe list lstr is (SIZE " << lstr.size() << "): " << endl << "\t";

	print(lstr);

	lstr.delete_k_th(2);

	cout << "\tThe NEW list lstr is (SIZE " << lstr.size() << "): " << endl << "\t";

	print(lstr);

	}

	cout << endl;

	return 0;
}

