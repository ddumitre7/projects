//============================================================================
// Name        : 014-Knapsack.cpp
// Author      : Dan
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include <algorithm>    // std::sort
#include <vector>
#include <functional>

using namespace std;

int calculate(int w, vector<int>& val, vector<int>& wt, int pos, int tbl[][100]);
int calculatex(int w, vector<int>& val, vector<int>& wt);





int main() {

	int testcases{};
	cin >> testcases;

	while (testcases) {

		int n{};

		cin >> n;

//		cout << ">>> number of elements: " << n << endl;

		int w{};

		cin >> w;

//		cout << ">>> weight: " << w << endl;


		vector<int>val(n);
		vector<int>wt(n);

		for(int i = 0; i < n; ++i) {
			int t{};
			cin >> t;
			val[i] = t;
		}

		for(int i = 0; i < n; ++i) {
			int t{};
			cin >> t;
			wt[i] = t;
		}


//		cout << "_____________________________" << endl;
//		for(int v : val)
//			cout << v << " ";
//		cout << endl;
//
//		for(int v : wt)
//			cout << v << " ";
//		cout << endl;
//
//		cout << "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _" << endl;



		cout << calculatex(w, val, wt) << endl;

//		cout << "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _" << endl;

		testcases--;
	}

	return 0;

}


int calculatex(int w, vector<int>& val, vector<int>& wt) {

	int tbl[val.size()][100];

	for(unsigned int i = 0; i < val.size(); ++i)
		for(int j = 0; j <= w; ++j)
			tbl[i][j] = -1;

	return calculate(w, val, wt, 0, tbl);
}

int calculate(int w, vector<int>& val, vector<int>& wt, int pos, int tbl[][100]) {

	int result{};

    if (val.size() - pos == 0) return 0;
    if (w == 0) return 0;

    if (tbl[pos][w] != -1) return tbl[pos][w];

    if (wt[pos] > w)

    	result = calculate(w, val, wt, pos + 1, tbl);

    else {

    	int temp1 = calculate(w, val, wt, pos + 1, tbl);
    	int temp2 = val[pos] + calculate(w - wt[pos], val, wt, pos + 1, tbl);

    	result = max(temp1, temp2);

    	tbl[pos][w] = result;

    }

    return result;
}

