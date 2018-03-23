//============================================================================
// Name        : circular_buffer_uint32.cpp
// Author      : Dan
// Version     :
// Copyright   :
// Description : circular_buffer_uint32 class file in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <cassert>

#include "config.h"
#include "circular_buffer_uint32.h"

using namespace std;


circular_buffer_uint32::circular_buffer_uint32(char* buffer, size_t s) : _read_pointer{0, 0}, _write_pointer{0, 0}, _mem_blocks_nbr{1},
							   _size{0}, _max_size{s  / sizeof(uint32_t)}, _overwrite{OVERWRITE} {

     if (!buffer)
    	 _max_size = 0;
     else {

    	 _mem_block[0] = reinterpret_cast<uint32_t*>(buffer);
    	 _mem_block_size[0] = s / sizeof(uint32_t);
     }
}


circular_buffer_uint32::circular_buffer_uint32(mem_block mem[], size_t s) : _read_pointer{0, 0}, _write_pointer{0, 0},
								_mem_blocks_nbr{0}, _size{0},
								_max_size{0}, _overwrite{OVERWRITE} {


	for (size_t i = 0, j = 0; i < s; ++i) {

		if ((_mem_block_size[j] = mem[i].length / sizeof(uint32_t)) == 0) 
			// We ignore the memory blocks which can't store at least one uint32_t element
			continue;

		if (!mem[i].mem_block_address)
			// We also ignore NULL memory blocks
			continue;

		_mem_block[j] = reinterpret_cast<uint32_t*>(mem[i].mem_block_address);

		// Update the max size
		_max_size += _mem_block_size[j];

		// Update the number of blocks
		++_mem_blocks_nbr;

		++j;
		if (j == MAX_BUFFERS) break;
	}

}


bool circular_buffer_uint32::empty() const {

	if (_size) return false;
	else return true;

}


size_t circular_buffer_uint32::size() const { return _size; }


bool circular_buffer_uint32::full() const { return(_size == _max_size); }


size_t circular_buffer_uint32::max_size() const { return _max_size; }


uint32_t circular_buffer_uint32::top() const {

	if (empty()) return 0;

	return *(_mem_block[_read_pointer.mem_block_nbr] + _read_pointer.position);
}


void circular_buffer_uint32::pop() {

	if (empty()) return;

	--_size;

	if (!_size) {

		_read_pointer = _write_pointer;
		return;
	}


	if (++_read_pointer.position == _mem_block_size[_read_pointer.mem_block_nbr]) {

		// We move on to the beginning of the next memory block
		_read_pointer.position = 0;
		++_read_pointer.mem_block_nbr %= _mem_blocks_nbr;
	}

	return;
}


void circular_buffer_uint32::push(uint32_t val) {

	// Some sanity checking in case we are not able to store any element
	if (!_max_size) return;

	if (empty()) {

		assert(!_size);
		assert(_read_pointer == _write_pointer);

		++_size;
		*(_mem_block[_write_pointer.mem_block_nbr] + _write_pointer.position) = val;

		return;
	}

	if (full()) {

		if (!_overwrite) return; // The buffer is full and we are not allowed to overwrite


		// The circular buffer is full and we move both the tail and the head with one position
		_write_pointer = _read_pointer;

		*(_mem_block[_write_pointer.mem_block_nbr] + _write_pointer.position) = val;

		// We move the head to the next element
		if (++_read_pointer.position == _mem_block_size[_read_pointer.mem_block_nbr]) {

					// We move on to the next memory block
					_read_pointer.position = 0;
					++_read_pointer.mem_block_nbr %= _mem_blocks_nbr;
		}

		return;

   } else {

	   ++_size;

	   if (++_write_pointer.position == _mem_block_size[_write_pointer.mem_block_nbr]) {

	   					// We move on to the next memory block
	   					_write_pointer.position = 0;
	   					++_write_pointer.mem_block_nbr;
	   					_write_pointer.mem_block_nbr %= _mem_blocks_nbr;
	   }

	   *(_mem_block[_write_pointer.mem_block_nbr] + _write_pointer.position) = val;
   }

	return;
}


void circular_buffer_uint32::clear() {

	_size = 0;

	_read_pointer.clear();
	_write_pointer.clear();
}


bool circular_buffer_uint32::overwrite() const { return _overwrite; }


void circular_buffer_uint32::set_overwrite(bool value) {

	_overwrite = value;
}
