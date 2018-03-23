//============================================================================
// Name        : 003_NBR_SUBARRAYS_K.cpp
// Author      : Dan
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
//#include <vector>

#include "nbr_subarrays_k.h"

long nbr_subarrays_counter_naive(const vector<int>&, long);

using namespace std;

int main() {
	cout << "Started in main()" << endl; // prints !!!Hello World!!!

	struct Test_Suite {
		vector<int> v;
		long k;
	};

	Test_Suite ts[] = {
					{{}, 2000},
					{{2000, 3000, 5000, 500, 14000, 30000}, 10},
					{{2000, 3000, 4, 3000, 5000, 50000, 100}, 10},
					{{2000, 3000, 4000, 3000, 5000, 50000, 100, 2}, 10},
					{{2, 3, 4, 3, 5, 5, 1}, 1000000},
					{{2, 3, 4, 2}, 25},
					{{2, 3, 4, 3000, 5000, 50000, 1000, 299, 899, 599}, 100}, //7
					{{4, 2, 5, 400, 4, 2, 5}, 41},
					{{4, 2, 8, 4, 20}, 100},
					{{1, 2, 3, 4}, 10},
					{{1, 9, 2, 8, 6, 4, 3}, 100},
					{{1, 2, 3, 4}, 10000},
					{{1, 2, 3, 4, 1}, 10000}
					};

	for(unsigned int i = 0; i < sizeof(ts) / sizeof(Test_Suite); ++i) {

		long m = nbr_subarrays_counter(ts[i].v, ts[i].k);
		long n = nbr_subarrays_counter_naive(ts[i].v, ts[i].k);

		cout << "Test case "<< i + 1 << ": Counter: " << m << ", " \
			 << "Test value: " << n << " ";

		(m == n) ? cout << "--> OK" : cout << "--> Failed";

		cout << endl;

	}
	return 0;
}


long nbr_subarrays_counter_naive(const vector<int>& v, long K) {


	long counter{0};

	for(uint i = 0; i < v.size(); ++i) {

		long long P{1};

		for(uint k = i; k < v.size(); ++k) {

			P = P * v[k];

			if (P < K) ++counter;
			else break;
		}
	}

	return counter;

}
