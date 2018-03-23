//============================================================================
// Name        : circular_buffer_uint32.h
// Author      : Dan
// Version     :
// Copyright   :
// Description : Header file in C++, Ansi-style
//============================================================================


#ifndef CIRCULAR_BUFFER_H_
#define CIRCULAR_BUFFER_H_

#include <stdint.h>
#include <stdio.h>

#include "config.h"
#include "I_circular_buffer_uint32.h"

struct mem_block;
struct cursor;

class circular_buffer_uint32 : I_circular_buffer_uint32 {

public:
	/** @brief It builds a circular_buffer_uint32 object based on
	  *        a memory block
	  *
	  *  If any argument is invalid, then the circular buffer is
	  *  full and empty in the same time.
	  *
	  *  @param buffer A pointer to the memory block.
	  *  @param s The size in bytes of the memory block.
	  *  @return Void.
	  */
	circular_buffer_uint32(char*, size_t);

	/** @brief It builds a circular_buffer_uint32 object based on
	  *        several memory blocks.
	  *
	  *  If any memory block is invalid, then the block is not added
	  *  to the circular_buffer_uint32 object. If the circular_buffer_uint32 object
	  *  is not sane after the constructor has been called, then the
	  *  buffer is full and empty in the same time.
	  *
	  *  @param mem An array of memory blocks.
	  *  @param s The size of the array of memory blocks.
	  *  @return Void.
	  */
	circular_buffer_uint32(mem_block [], size_t);

	/** @brief It adds one element at the end of the buffer.
 	  *
 	  *  If the buffer is full and the overwrite feature is off,
	  *  then the element is ignored.
	  *
	  *  @param val A uint32_t which is added to the buffer.
	  *  @return None.
 	  */
	void push(uint32_t);

	/** @brief It removes the oldest element from the buffer.
	  *
	  *  If the buffer is empty, then this operation doesn't affect
	  *  the state of the object.
	  *
	  *  @return None.
	  */
	void pop();

	/** @brief It returns the oldest element from the buffer.
	  *
	  *  This function returns a valid value only if the buffer is not empty.
	  *  The user must check before using this function if the the buffer
	  *  is empty. If this function is called and the buffer is empty, then
	  *  this function returns 0.
	  *
	  *  @return The value of the oldest element from the buffer.
	  */
	uint32_t top() const;

	/** @brief It returns how many elements are currently stored in the buffer.
	  *
	  *  @return The current number of elements.
	  */
	size_t size() const;

	/** @brief It returns the maximum number of elements that can be
	  *        stored in the buffer.
	  *
	  *  When the actual number of elements that are stored in the buffer
	  *  equals with the maximum size, then the buffer is declared as
 	  *  full.
 	  *
	  *  @return The maximum number of elements that this buffer can store.
	  */
	size_t max_size() const;

	/** @brief It tells whether the buffer is empty or not.
	  *
	  *  @return True if buffer is empty, false otherwise.
	  */
	bool empty() const;

	/** @brief It tells if the buffer is full or not.
	  *
	  *  @return True is buffer is full, false otherwise.
	  */
	bool full() const;

	/** @brief It resets the buffer.
	  *
	  *  After this operation the buffer is be empty.
	  *
	  *  @return None.
	  */
	void clear();

	/** @brief It tells if the new push operations will overwrite
	  *        the oldest elements if the buffer is full.
	  *
	  *  @return True is buffer can be overwritten, false otherwise.
	  */
	bool overwrite() const;

	/** @brief It sets the overwrite feature of the buffer.
	  *
	  *  @return None.
  	  */
	void set_overwrite(bool);

private:

	struct cursor {

		uint16_t position;             /**< The position in the the memory block. */
		uint16_t mem_block_nbr;        /**< The memory block index. */

		void clear() { position = 0; mem_block_nbr = 0; }

		bool operator ==(const cursor& c) {
			if ((position == c.position) && (mem_block_nbr == c.mem_block_nbr))
				return true;

	        	return false;
	    	}
	};

	uint32_t *_mem_block[MAX_BUFFERS];     /**< Array of pointers to the memory blocks. */
	uint16_t _mem_block_size[MAX_BUFFERS]; /**< Array which stores the size for each block.
	                                         *  The size tells how many uint32_t elements
	                                         *  can be stored in the memory block. */
	cursor _read_pointer;                  /**< Head of the circular buffer - it's the place we read from. */
	cursor _write_pointer;                 /**< Tail of the circular buffer - it's the place we write to. */
	size_t _mem_blocks_nbr;                /**< How many buffers there are. */

	size_t _size;                          /**< How many elements are stored in the buffer. */
	size_t _max_size;                      /**< The max number of elements that this buffer can host. */

	bool _overwrite;                       /**< This flag determines if the oldest elements can be
	                                         *  overwritten when the buffer becomes full. */

};

struct mem_block {
	char* mem_block_address;               /**< The address of the memory block. */
	size_t length;                         /**< The size of the memory block in bytes. */
};


#endif /* CIRCULAR_BUFFER_H_ */
