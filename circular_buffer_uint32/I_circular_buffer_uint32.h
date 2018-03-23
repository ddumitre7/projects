//============================================================================
// Name        : I_circular_buffer_uint32.h
// Author      : Dan
// Version     :
// Copyright   : Your copyright notice
// Description : Interface file in C++, Ansi-style
//============================================================================

#ifndef I_CIRCULAR_BUFFER_H_
#define I_CIRCULAR_BUFFER_H_


#include <stdint.h>

class I_circular_buffer_uint32 {

public:

    virtual void push(uint32_t) = 0;
    virtual void pop() = 0;
    virtual uint32_t top() const = 0;
    virtual size_t size() const = 0;
    virtual size_t max_size() const = 0;
    virtual bool empty() const = 0;
    virtual bool full() const = 0;
    virtual void clear() = 0;
    virtual bool overwrite() const = 0;
    virtual void set_overwrite(bool) = 0;
    virtual ~I_circular_buffer_uint32() {};
};

#endif /* I_CIRCULAR_BUFFER_H_ */
