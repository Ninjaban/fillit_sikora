//
// Created by Jonathan on 04/12/2017.
//

#include <unistd.h>			/* |read()| */
#include <stdlib.h>			/* |malloc()| */
#include <string.h>			/* |strlen()|, |memset()|, |memcpy()| */
#include <sys/types.h>		/* |open()| */
#include <sys/stat.h>
#include <fcntl.h>

#include "types.h"
#include "error.h"

#include "fillit.h"


#define		TETRIMINOS_MAX_PER_FILE		(t_uint)26
#define		TETRIMINOS_NB_CHAR			(t_uint)21
#define		MALLOC_SIZE					(t_uint)(TETRIMINOS_MAX_PER_FILE * TETRIMINOS_NB_CHAR)

#define		READ_COUNT		(21)

/* -- library_configuration */
static struct
{
	t_bool			initialized;

	t_bool			debug_mode;

	t_buffer		filename;
} internal_context = {
	.initialized	= FALSE,

	.debug_mode	= FALSE
};


/**
 *		internal_context_is_initialize
 *
 *		@param	none
 *
 *		@error	none
 *
 *		@return	TRUE in success, FALSE otherwise
 */
static t_bool		internal_context_is_initialize (void)
{
	return (internal_context.initialized);
}


/* === initialisation function === */
/**
 *		internal_context_initialize
 *
 *		@param	none
 *
 *		@error	none
 */
static void			internal_context_initialize (void)
{
	internal_context.initialized = TRUE;

	BUFFER_CLEAR (internal_context.filename);
}


/**
 *
 *
 * @param out_tetriminos_lst
 * @param out_failure_code
 *
 *
 *
 * @return
 */
static t_bool		internal_ft_read (t_tetris				*out_tetriminos_lst,
									  t_failure_code		*out_failure_code)
{
	int				file_descriptor;
	t_pchar			file_content;
	t_uint			file_content_size;
	char			read_buf[ READ_COUNT + 1 ];
	int				read_ret;
	t_tetris		tetriminos_lst;


	/* Read part*/
	if ((file_descriptor = open (internal_context.filename, O_RDONLY)))
	{
		FT_ERROR ("open() failed filename {%.*s}", (int)internal_context.filename.size, internal_context.filename.bytes);

		*out_failure_code = FAILURE_CODE_FATAL;
		return FALSE;
	}

	if (file_content = malloc (MALLOC_SIZE))
	{
		FT_ERROR ("malloc() failed size %" PRIu64, MALLOC_SIZE);

		*out_failure_code = FAILURE_CODE_FATAL;
		return FALSE;
	}
	memset (file_content, '\0', READ_COUNT + 1);
	file_content_size = 0;

	while ((read_ret = read (file_descriptor, read_buf, READ_COUNT)) > 0)
	{
		read_buf[read_ret] = '\0';
		memcpy (file_content + file_content_size, read_buf, read_ret);
	}

	if (read_ret == -1)
	{
		FT_ERROR ("read() failed %s", "");

		*out_failure_code = FAILURE_CODE_FATAL;
		return FALSE;
	}


	/* //TEMP CHECK CONTENT AND SEE IF IT'S VALID HERE */


	/* Stock part */


	*out_failure_code = FAILURE_CODE_NONE;

	return TRUE;
}

/**
 * This function read a file and stock the content in a list
 *
 * @param out_tetriminos_lst
 * @param out_failure_code
 *
 * @error out_tetriminos_lst is NULL
 * @error out_failure_code is NULL
 * @error internal_ft_read() failed
 *
 * @return TRUE in success, FALSE otherwise
 */
extern t_bool		ft_read (t_tetris			*out_tetriminos_lst,
							 t_failure_code		out_failure_code)
{
	/* basic check */
	if (out_failure_code == NULL)
	{
		FT_ERROR ("out_failure_code %p", (void *)out_failure_code);

		return FALSE;
	}
	*out_failure_code = FAILURE_CODE_UNDEFINED;

	if (out_tetriminos_lst == NULL)
	{
		FT_ERROR ("out_tetriminos_lst %p", (void *)out_tetriminos_lst);

		out_failure_code = FAILURE_CODE_NULL_PARAMETER;
		return FALSE;
	}
	*out_tetriminos_lst = NULL;

	if (! internal_context_is_initialize ())
	{
		FT_ERROR ("internal_context_is_initialized() %s", "failed");

		*out_failure_code = READ_MAIN__FT_READ__NOT_INITIALIZE;
		return FALSE;
	}


	if (! internal_ft_read (out_tetriminos_lst, out_failure_code))
	{
		FT_WARNING("internal_ft_read() %s", "failed");

		/* out_failure_code is set in the internal function */
		return FALSE;
	}


	*out_failure_code = FAILURE_CODE_NONE;

	return TRUE;
}


extern t_bool		ft_read_initialize (const t_pchar		in_filename,
										t_failure_code		*out_failure_code)
{
	/* basic check */
	if (out_failure_code == NULL)
	{
		FT_ERROR ("out_failure_code %p", (void *)out_failure_code);

		return FALSE;
	}
	*out_failure_code = FAILURE_CODE_UNDEFINED;

	if (in_filename == NULL)
	{
		FT_ERROR ("in_filename %p", (void *)in_filename);

		out_failure_code = FAILURE_CODE_NULL_PARAMETER;
		return FALSE;
	}

	internal_context_initialize ();

	BUFFER_SETUP (internal_context.filename, strlen (in_filename), in_filename);


	*out_failure_code = FAILURE_CODE_NONE;

	return TRUE;
}