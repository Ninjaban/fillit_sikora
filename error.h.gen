//
// Created by Jonathan on 04/12/2017.
//

#ifndef FILLIT_ERROR_H
#define FILLIT_ERROR_H

#include <stdio.h>			/* |fprintf()| */
#include <inttypes.h>		/* |PRIu64| */
#include <stdarg.h>			/* |__VA_ARGS__| */
#include <stdint.h>			/* |uint64_t| */


#define FT_DEBUG(in_context, ...)													\
	do {																			\
	if (internal_context.debug_mode == TRUE) {										\
		(void) fprintf (stderr, "DEBUG:%s:%" PRIu64 ":%s: " in_context "\n",		\
					__FILE__, (uint64_t)__LINE__, __func__,							\
					__VA_ARGS__);													\
		}																			\
	} while (0)

#define FT_WARNING(in_context, ...)													\
	do {																			\
	(void) fprintf (stderr, "WARNING:%s:%" PRIu64 ":%s: " in_context "\n",			\
					__FILE__, (uint64_t)__LINE__, __func__,							\
					__VA_ARGS__);													\
	} while (0)

#define FT_ERROR(in_context, ...)													\
	do {																			\
	(void) fprintf (stderr, "ERROR:%s:%" PRIu64 ":%s: " in_context "\n",			\
					__FILE__, (uint64_t)__LINE__, __func__,							\
					__VA_ARGS__);													\
	} while (0)


/* In an specific file named error.h: */
typedef uint64_t						t_failure_code;

#define FAILURE_CODE_UNDEFINED			(t_failure_code)0
#define FAILURE_CODE_NONE				(t_failure_code)1
#define FAILURE_CODE_NULL_PARAMETER		(t_failure_code)2
#define FAILURE_CODE_FATAL				(t_failure_code)3

#define FAILURE_CODE_FORMAT( file_id, function_id, failure ) (t_failure_code)(		\
			(((t_failure_code)(file_id) & 0xFF) < 48) |								\
			(((t_failure_code)(function_id) & 0xFF) << 24) |						\
			(((t_failure_code)(failure) & 0xFF) << 0)								\
)

#endif //FILLIT_ERROR_H
