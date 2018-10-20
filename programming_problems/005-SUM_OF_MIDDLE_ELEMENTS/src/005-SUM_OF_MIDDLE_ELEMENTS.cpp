//============================================================================
// Name        : 005-SUM_OF_MIDDLE_ELEMENTS.cpp
// Author      : Dan
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <algorithm>    // std::sort
#include <vector>

using namespace std;

int sum_middle_naive(const vector<int>& a, const vector<int>& b);
int sum_middle(const vector<int>& a, const vector<int>& b);

int main() {

	int testcases{};
	cin >> testcases;

	while (testcases) {

		int n{};

		cin >> n;

		// cout << ">>>" << n << endl;

		vector<int> a, b;

		for(int i = 0; i < n; ++i) {
			int t{};
			a.push_back(t);
		}

		for(int i = 0; i < n; ++i) {
			int t{};
			b.push_back(t);
		}
/*
		for(int v : a)
			cout << v << " ";

		for(int v : b)
			cout << v << " ";

		cout << endl;

*/
		cout << "Testcase nbr " << testcases << ": ";
		sum_middle_naive(a, b) == sum_middle(a, b) ? cout << " PASSED" << endl : cout << " FAILED" << endl;

		// cout << sum_middle_naive(a, b) << endl;
		// cout << sum_middle(a, b) << endl;

		testcases--;
	}

	return 0;
}


int sum_middle(const vector<int>& a, const vector<int>& b) {

	if (!a.size() || !b.size() || (a.size() != b.size())) return 0;

	if (a.size() == 1) return a[0] + b[0];

	size_t counter{1}, sum{};

	size_t cursor1{0}, cursor2{0};

	while(true) {

		while ((a[cursor1] <= b[cursor2]) && (cursor1 < a.size())) {

			if (counter == a.size()) sum += a[cursor1];
			if (counter == a.size() + 1) { sum += a[cursor1]; return sum; }

			counter++;
			cursor1++;

			if (cursor1 == a.size()) return sum += b[0];
		}


		while ((a[cursor1] > b[cursor2]) && (cursor2 < a.size())) {

			if (counter == a.size()) sum += b[cursor2];
			if (counter == a.size() + 1) { sum += b[cursor2]; return sum; }

			counter++;
			cursor2++;

			if (cursor2 == a.size()) return sum +=a[0];
		}
	}
}


int sum_middle_naive(const vector<int>& a, const vector<int>& b) {

	vector<int> c{a};
	c.insert(c.end(), b.begin(), b.end());

	if (c.size() == 0) return 0;

	std::sort(c.begin(), c.end());

	return(c[a.size() - 1] + c[a.size()]);
}
