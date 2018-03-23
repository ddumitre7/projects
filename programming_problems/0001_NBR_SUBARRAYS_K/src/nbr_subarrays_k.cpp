/*
 * nbr_subarrays_k.cpp
 *
 *  Created on: Feb 25, 2018
 *      Author: dan
 */

#include <utility>
#include <functional>

#include "nbr_subarrays_k.h"

inline static long calculate_helper(int n);

/* This implementation is optimal. It's execution time is O(n). */
long nbr_subarrays_counter(const vector<int>& v, long K) {

	long counter{0}, product{1};

	if (!v.size()) return 0;

	pair<size_t, size_t> window = make_pair(0, 1);

	while ((window.first < v.size()) && (v[window.first] > K)) {

		++window.first;
		++window.second;
	}

	if (window.first >= v.size()) return counter;

	product = v[window.first];
	while (true) {

		if (window.second >= v.size()) break;

		long p{product * v[window.second]};

		if (p > K) break;
		else {

			++window.second;
			product = p;
		}
	}

	counter += calculate_helper(window.second - window.first);

	if (window.second >= v.size()) return counter;

	// We have an initial window. We go on finding the next windows in a loop

	while(true) {

		auto old_window = window;

		// cout << "######### WHILE STARTS HERE - window: [" << window.first <<", " << window.second << ") product = " << product << endl;

		if (window.second >= v.size()) break;

		product /= v[window.first++];
		auto p{product * v[window.second]};
		++window.second;

		if (p < K) {

			product = p;

			while (true)
			{
				if (window.second >= v.size()) break;

				auto p{product * v[window.second]};

				if (p > K) break;
				else {

					product = p;
					++window.second;
				}
			}

		} else {

			while (window.first != window.second - 1) {

				p /= v[window.first];

				if (p < K) {

					product = p;
					window.first++;
					break;
				} else
					window.first++;
			}

			if (window.first == window.second - 1) {

				if (window.second >= v.size()) {

					if (p < K) return counter + 1;

					return counter;
				}

 				while (true) {

 					if (window.first >= v.size()) return counter;

 					if(v[window.first] < K) {

 						product = v[window.first];
 						window.second = window.first + 1;

 						break;
 					}
 					else window.first++;
 				}


 				////////
 				// Expand right as much as we can

 				window.second = window.first + 1;
 				while (true)
 				{
 					if (window.second >= v.size()) break;

 					auto p{product * v[window.second]};

 					if (p > K) break;
 					else {

 						product = p;
 						++window.second;
 					}

 				}

 				///////

			} else {

				while (true)
				{
					if (window.second >= v.size()) break;

					auto p{product * v[window.second]};

					if (p > K) break;
					else {

						product = p;
						++window.second;
					}

				}

			}

		}

		// We have a new window
		counter += calculate_helper(window.second - window.first) -
				calculate_helper(old_window.second - window.first);

	} // END While


	return counter;
}

static long calculate_helper(int n) {

	if (n <= 0) return 0;

	return n * (n + 1) / 2;

}
