//============================================================================
// Name        : interval_manager.cpp
// Author      : Dan
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include "interval_manager.h"

void interval_manager_test();

int main() {
	std::cout << "Starting...\n" << std::endl; // prints Starting...\n

	interval_manager_test();

	return 0;
}

void interval_manager_test() {

	std::cout << "interval_manager<unsigned int, char> t1 ('K');" << std::endl;
	interval_manager<unsigned int, char> t1 ('K');
	std::cout << "t1.add(100, 300, 'M')" << std::endl;
	t1.add(100, 300, 'M');

	for (auto it = t1._map.begin(); it != t1._map.end(); ++it)
	    std::cout << it->first << " -> " << it->second << std::endl;

	std::cout << "t1.add(150, 290, 'O')" << std::endl;
	t1.add(150, 290, 'O');

	for (auto it = t1._map.begin(); it != t1._map.end(); ++it)
	    std::cout << it->first << " -> " << it->second << std::endl;

	std::cout << "t1.add(140, 322, 'K')" << std::endl;
	t1.add(140, 322, 'K');

	for (auto it = t1._map.begin(); it != t1._map.end(); ++it)
		 std::cout << it->first << " -> " << it->second << std::endl;

}


