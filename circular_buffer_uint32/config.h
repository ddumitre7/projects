//============================================================================
// Name        : config.h
// Author      : Dan
// Version     :
// Copyright   : Your copyright notice
// Description : Config file in C++, Ansi-style
//============================================================================

#ifndef CONFIG_H_
#define CONFIG_H_

#define NDEBUG /**< Comment this out if you want to enable assert function calls. */

const int MAX_BUFFERS = 20; /**< The maximum number of memory blocks that the circular buffer can use. */
const bool OVERWRITE = true; /**< If overwrite is true, then the oldest element will be overwritten when
                               *  the buffer is full. */

#endif /* CONFIG_H_ */
