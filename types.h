//
// Created by Jonathan on 04/12/2017.
//

#ifndef FILLIT_TYPES_H
#define FILLIT_TYPES_H

#include <stdint.h>		/* |uint64_t| */

/* In an specific file named type.h: */
#define TRUE		1
#define FALSE		0

typedef char			t_bool;
typedef void *			t_pvoid;
typedef char *			t_pchar;
typedef unsigned int	t_uint;

typedef const char			t_cbool;
typedef const void *		t_cpvoid;
typedef const char *		t_cpchar;
typedef const unsigned int	t_cuint;

typedef struct
{
	t_uint			size;
	t_pvoid			bytes;
} t_buffer;

#define BUFFER_CLEAR(target)					{ (target).size = 0; (target).bytes = NULL; }
#define BUFFER_SETUP(target, size, bytes)		{ (target).size = (size}; (target).bytes = (bytes) }
#define BUFFER_CHECK(target)									\
{																\
	(((target).size == 0) && ((target).bytes == NULL)) ||		\
	(((target).size >  0) && ((target).bytes != NULL)) ||		\
}

#endif //FILLIT_TYPES_H
