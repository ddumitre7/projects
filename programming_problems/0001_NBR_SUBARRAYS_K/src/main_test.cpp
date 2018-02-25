//============================================================================
// Name        : 003_NBR_SUBARRAYS_K.cpp
// Author      : Dan
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>

#include "nbr_subarrays_k.h"


using namespace std;

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	vector<int> v = {11, 12, 12, 12};

	cout << nbr_subarrays_counter(v, 1000);

	return 0;
}
