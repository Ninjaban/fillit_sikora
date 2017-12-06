//
// Created by Nathan on 04/12/17.
//

#include "error.h.gen"
#include "types.h"
#include "fillit.h"
#include "main_read.h"

int main(int ac, char **av)
{
	t_tetris			*tetris;
	t_uint				n;

	if (ac == 1)
		return 1;
	if (! ft_read(av[1], &tetris))
	{
		FT_ERROR("ft_read() failed %s", "");
		return 1;
	}
	while (tetris)
	{
		FT_WARNING("tetris number %" PRIu32 " height %" PRIu32 " width %" PRIu32, tetris->number, tetris->height, tetris->width);
		n = 0;
		while (n < tetris->height)
			FT_WARNING("{%.*s}", tetris->width, tetris->tetriminos[n++]);
		tetris = tetris->next;
	}
	return 0;
}