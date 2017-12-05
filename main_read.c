//
// Created by Jonathan on 04/12/2017.
//

#include <string.h>
#include "error.h.gen"

#include <unistd.h>			/* |read()| */
#include <stdlib.h>			/* |malloc()| */
#include <fcntl.h>			/* |open()| */
#include "types.h"
#include "fillit.h"

#define		TETRIMINOS_MAX_PER_FILE		(t_uint)26
#define		TETRIMINOS_NB_CHAR			(t_uint)21
#define		MALLOC_SIZE					(t_uint)(TETRIMINOS_MAX_PER_FILE * \
													TETRIMINOS_NB_CHAR)

#define		READ_COUNT					(t_uint)21


static void			internal_get_size (t_cpchar in_file_content,
									   t_uint *out_tetriminos_point_min,
									   t_uint **out_tetriminos_point,
									   t_tetris **out_tetriminos_lst)
{
	t_uint 		tetriminos_point_max;
	int			i;
	int			n;

	i = -1;
	n = 0;
	while (++i < 20)
		if (in_file_content[i] == '#')
			(*out_tetriminos_point)[n++] = (t_uint)i;
	(*out_tetriminos_lst)->height = (((*out_tetriminos_point)[3] / 5) -
			((*out_tetriminos_point)[0] / 5)) + 1;
	n = 0;
	tetriminos_point_max = 0;
	while (n < 4)
	{
		(*out_tetriminos_point)[n] = (*out_tetriminos_point)[n] % 5;
		if ((*out_tetriminos_point)[n] > tetriminos_point_max)
			tetriminos_point_max = (*out_tetriminos_point)[n];
		if ((*out_tetriminos_point)[n] < *out_tetriminos_point_min)
			*out_tetriminos_point_min = (*out_tetriminos_point)[n];
		n = n + 1;
	}
	(*out_tetriminos_lst)->width = tetriminos_point_max -
			*out_tetriminos_point_min + 1;
}

static t_bool		internal_create_tab (t_uint *tetriminos_point,
										 t_uint tetriminos_point_min,
										 t_tetris **out_tetriminos_lst,
										 t_uint i)
{
	t_uint			n;

	if (! ((*out_tetriminos_lst)->tetriminos = malloc(sizeof (char *) *
											  (*out_tetriminos_lst)->height)))
		return (FALSE);
	while (i != (*out_tetriminos_lst)->height)
	{
		if (! ((*out_tetriminos_lst)->tetriminos[i] =
					   malloc((*out_tetriminos_lst)->width)))
			return (FALSE);
		memset ((*out_tetriminos_lst)->tetriminos[i], '.',
				(*out_tetriminos_lst)->width);
		i = i + 1;
	}
	i = 0;
	n = 0;
	while (n < 4)
	{
		tetriminos_point[n] = tetriminos_point[n] - tetriminos_point_min;
		if (n != 0 && tetriminos_point[n] <= tetriminos_point[n - 1])
			i = i + 1;
		(*out_tetriminos_lst)->tetriminos[i][tetriminos_point[n]] = '#';
		n = n + 1;
	}
	return (TRUE);
}

static t_bool		internal_stock_file_content (t_cpchar in_file_content,
												 t_cuint in_tetriminos_id,
												 t_tetris **out_tetriminos_lst)
{
	t_uint			*tetriminos_point;
	t_uint 			tetriminos_point_min;

	if (!(*out_tetriminos_lst = malloc (sizeof (t_tetris))))
		return (FALSE);
	(*out_tetriminos_lst)->number = in_tetriminos_id;
	(*out_tetriminos_lst)->next = NULL;
	if (!(tetriminos_point = malloc(sizeof (t_uint) * 4)))
		return (FALSE);
	internal_get_size(in_file_content, &tetriminos_point_min,
					  &tetriminos_point, out_tetriminos_lst);
	if (!internal_create_tab(tetriminos_point, tetriminos_point_min,
							out_tetriminos_lst, 0))
		return (FALSE);
	free(tetriminos_point);
	if (in_file_content[20] == '\n')
		if (!internal_stock_file_content(in_file_content + 21,
						in_tetriminos_id + 1, &((*out_tetriminos_lst)->next)))
			return (FALSE);
	return (TRUE);
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
static t_bool		internal_ft_read (t_cpchar in_filename,
									  t_tetris **out_tetriminos_lst)
{
	int				file_descriptor;
	t_pchar			file_content;
	ssize_t			file_content_size;
	char			read_buf[ READ_COUNT + 1 ];
	ssize_t			read_ret;

	if ((file_descriptor = open (in_filename, O_RDONLY)) == -1)
		return (FALSE);
	if (!(file_content = malloc (MALLOC_SIZE)))
		return (FALSE);
	memset (file_content, '\0', READ_COUNT + 1);
	file_content_size = 0;
	while ((read_ret = read (file_descriptor, read_buf, READ_COUNT)) > 0)
	{
		read_buf[read_ret] = '\0';
		memcpy (file_content + file_content_size, read_buf,
				   (size_t)read_ret);
		file_content_size = file_content_size + read_ret;
	}

	/* //TEMP CHECK CONTENT AND SEE IF IT'S VALID HERE */

	if (!internal_stock_file_content (file_content, 1, out_tetriminos_lst))
		return (FALSE);
	return (TRUE);
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
extern t_bool		ft_read (t_cpchar in_filename,
							 t_tetris **out_tetriminos_lst)
{
	if (out_tetriminos_lst == NULL)
		return (FALSE);
	*out_tetriminos_lst = NULL;
	if (!internal_ft_read (in_filename, out_tetriminos_lst))
		return (FALSE);
	return (TRUE);
}
