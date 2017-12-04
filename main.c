//
// Created by Nathan on 04/12/17.
//

#include "types.h"
#include "error.h"

#include "fillit.h"

#include "read_main.h"

int main(int ac, char **av)
{
	t_tetris			*tetris;
	t_failure_code		failure_code;

	if (ac == 1)
		return 1;

	if (! ft_read_initialize(av[1], &failure_code))
	{
		FT_WARNING("ft_read_initialize() failed failure_code %" PRIu64, failure_code);

		return 1;
	}

	if (! ft_read(&tetris, &failure_code))
	{
		FT_WARNING("ft_read() failed failure_code %" PRIu64, failure_code);

		return 1;
	}

	if (! ft_read_finalize(&failure_code))
	{
		FT_WARNING("ft_read_finalize() failed failure_code %" PRIu64, failure_code);

		return 1;
	}

	return 0;
}