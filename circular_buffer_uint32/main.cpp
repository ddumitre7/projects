//============================================================================
// Name        : main.cpp
// Author      : Dan
// Version     :
// Copyright   : Your copyright notice
// Description : Main file in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdint.h>
#include <stdio.h>

#include "circular_buffer_uint32.h"

using namespace std;

void print_info(const circular_buffer_uint32 &c);

void test_001(bool);
void test_002();
void test_003();
void test_009();
void test_004(bool);
void test_005();
void test_006();
void test_007();
void test_008();
void test_009();


char p[200];

int main() {


	test_001(true);
	test_001(false);
	test_002();
	test_003();
	test_004(true);
	test_004(false);
	test_005();
	test_006();
	test_007();
	test_008();
	test_009();
	return 0;
}

void print_info(const circular_buffer_uint32 &c) {

	cout << "Top element: ";

	if(c.empty()) cout << "None / ";
	else cout << c.top() << " / ";

	cout << "Current size: ";
	cout << c.size() << " / ";

	cout << "Maximum size: ";
	cout << c.max_size() << " / ";


	cout << "Empty:";
	if(c.empty()) cout << " TRUE / ";
	else cout << " FALSE / ";


	cout << "Full:";
	if(c.full()) cout << " TRUE";
	else cout << " FALSE";


	cout << endl;
	return;
}

void test_001(bool value) {

	cout << endl << endl;

	size_t len = 5;

	circular_buffer_uint32 c(&p[0], len * sizeof (uint32_t));
	c.set_overwrite(value);

	cout << "Test case: using one memory block for the buffer / overwrite is ";
	c.overwrite() ? cout << "ON" : cout << "OFF";
	cout << endl << endl;

	print_info(c);

	cout << "Adding "<< len << " elements" << endl;

	for (size_t i = 0; i < 5; i++)
		c.push(100 + i);

	print_info(c);

	cout << "Removing 3 elements" << endl;

	for (size_t i = 0; i < 3; i++)
		c.pop();

	print_info(c);

	cout << "Adding "<< 3 * len + 20 << " elements" << endl;

	for (size_t i = 0; i < 3 * len + 20; i++)
		c.push(1000 + i);

	print_info(c);


	cout << "Emptying the buffer"<< endl;
	cout << "Top elements are: ";

	while(!c.empty()) {

		cout << c.top() << " ";
        	c.pop();
	}

	cout << endl;
	print_info(c);
}


void test_002() {

	cout << endl << endl;

	size_t len = 5;

	circular_buffer_uint32 c(reinterpret_cast<char*>(NULL), len * sizeof (uint32_t));

	cout << "Test case: using a NULL memory block for the buffer / overwrite is ";
	c.overwrite() ? cout << "ON" : cout << "OFF";
	cout << endl << endl;

	print_info(c);

	cout << "Adding "<< len << " elements" << endl;

	for (size_t i = 0; i < 5; i++)
		c.push(100 + i);

	print_info(c);

	cout << "Removing 3 elements" << endl;

	for (size_t i = 0; i < 3; i++)
		c.pop();

	print_info(c);

}


void test_003() {

	cout << endl << endl;

	circular_buffer_uint32 c(&p[0], 2);

	cout << "Test case: using a memory block which too small (only 2 bytes)";
	cout << endl << endl;

	print_info(c);

	cout << "Adding 5 elements" << endl;

	for (size_t i = 0; i < 5; i++)
		c.push(100 + i);

	print_info(c);

	cout << "Removing 3 elements" << endl;

	for (size_t i = 0; i < 3; i++)
		c.pop();

	print_info(c);

}


void test_004(bool value) {

	cout << endl << endl;

	size_t len1 = 5, len2 = 7, len3 = 3;

	mem_block mem[] = {{&p[0],  len1 * sizeof (uint32_t)},
    			   	   {&p[40],  len2 * sizeof (uint32_t)},
    			   	   {&p[100], len3 * sizeof (uint32_t)}};


	circular_buffer_uint32 c(mem, sizeof(mem) / sizeof(mem_block));

	c.set_overwrite(value);

	cout << "Test case: using 3 memory blocks for the buffer / overwrite is ";
	c.overwrite() ? cout << "ON" : cout << "OFF";
	cout << endl << endl;

	print_info(c);

	cout << "Adding "<< len1 + len2 + len3 << " elements" << endl;

	for (size_t i = 0; i < len1 + len2 + len3; i++)
		c.push(100 + i);

	print_info(c);

	cout << "Removing 10 elements" << endl;

	for (size_t i = 0; i < 10; i++)
		c.pop();

	print_info(c);

	cout << "Adding "<< 50 << " elements" << endl;

	for (size_t i = 0; i < 50; i++)
		c.push(1000 + i);

	print_info(c);


	cout << "Emptying the buffer"<< endl;
	cout << "Top elements are: ";

	while(!c.empty()) {

		cout << c.top() << " ";
        c.pop();

    }

	cout << endl;
	print_info(c);
}


void test_005() {

	cout << endl << endl;

	size_t len = 50;

	size_t len1 = 5, len2 = 7, len3 = 3;

	mem_block mem[] = {{&p[0],   len1 * sizeof (uint32_t)},
			   {NULL,    len2 * sizeof (uint32_t)},
			   {&p[100], len3 * sizeof (uint32_t)}};


	circular_buffer_uint32 c(mem, sizeof(mem) / sizeof(mem_block));

	cout << "Test case: using a multiple memory blocks and one block is NULL";
	cout << endl << endl;

	print_info(c);

	cout << "Adding "<< len << " elements" << endl;

	for (size_t i = 0; i < len; i++) 
		c.push(100 + i);

	print_info(c);

	cout << "Removing 3 elements" << endl;

	for (size_t i = 0; i < 3; i++)
		c.pop();

	print_info(c);

}

void test_006() {

	cout << endl << endl;

	size_t len = 50;

	size_t len1 = 5, len2 = 7;

	mem_block mem[] = {{&p[0],   len1 * sizeof (uint32_t)},
			   {&p[40],  len2 * sizeof (uint32_t)},
			   {&p[100], 3}};


	circular_buffer_uint32 c(mem, sizeof(mem) / sizeof(mem_block));

	cout << "Test case: using a multiple memory blocks and one block is NULL";
	cout << endl << endl;

	print_info(c);

	cout << "Adding "<< len << " elements" << endl;

	for (size_t i = 0; i < len; i++)
		c.push(100 + i);

	print_info(c);

	cout << "Removing 3 elements" << endl;

	for (size_t i = 0; i < 3; i++)
		c.pop();

	print_info(c);

}

void test_007() {

	cout << endl << endl;

	size_t len = 50;

	size_t len1 = 5, len2 = 7;

	mem_block mem[] = {{NULL, len1 * sizeof (uint32_t)},
			   {NULL, len2 * sizeof (uint32_t)},
			   {NULL, 3}};


	circular_buffer_uint32 c(mem, sizeof(mem) / sizeof(mem_block));

	cout << "Test case: using a multiple memory blocks and all of them are NULL";
	cout << endl << endl;

	print_info(c);

	cout << "Adding "<< len << " elements" << endl;

	for (size_t i = 0; i < len; i++)
		c.push(100 + i);
	

	print_info(c);

	cout << "Removing 3 elements" << endl;

	for (size_t i = 0; i < 3; i++)
		c.pop();

	print_info(c);

}

void test_008() {

	cout << endl << endl;

	size_t len = 50;


	mem_block mem[] = {{&p[0],   1},
			   {&p[40],  1},
			   {&p[100], 3}};


	circular_buffer_uint32 c(mem, sizeof(mem) / sizeof(mem_block));


	cout << "Test case: using a multiple memory blocks and all of them are too small";
	cout << endl << endl;

	print_info(c);

	cout << "Adding "<< len << " elements" << endl;

	for (size_t i = 0; i < len; i++)
		c.push(100 + i);
	
	print_info(c);

	cout << "Removing 3 elements" << endl;

	for (size_t i = 0; i < 3; i++)
		c.pop();

	print_info(c);

}

void test_009() {

	cout << endl << endl;

	size_t len1 = 5, len2 = 7, len3 = 3;

	mem_block mem[] = {{&p[0],   len1 * sizeof (uint32_t)},
    			   {&p[40],  len2 * sizeof (uint32_t)},
    			   {&p[100], len3 * sizeof (uint32_t)}};


	circular_buffer_uint32 c(mem, sizeof(mem) / sizeof(mem_block));

	cout << "Test case: using 3 memory blocks and the calling clear API  / overwrite is ";
	c.overwrite() ? cout << "ON" : cout << "OFF";
	cout << endl << endl;

	print_info(c);

	cout << "Adding "<< len1 + len2 + len3 << " elements" << endl;

	for (size_t i = 0; i < len1 + len2 + len3; i++)
		c.push(100 + i);

	print_info(c);

	cout << "Removing 10 elements" << endl;

	for (size_t i = 0; i < 10; i++)
		c.pop();

	print_info(c);

	cout << "Adding "<< 50 << " elements" << endl;

	for (size_t i = 0; i < 50; i++)
		c.push(1000 + i);

	print_info(c);


	cout << "Clearing the buffer"<< endl;
	c.clear();
	print_info(c);

	cout << "Adding "<< 200 << " elements" << endl;

	for (size_t i = 0; i < 50; i++)
		c.push(4000 + i);

	print_info(c);

}

