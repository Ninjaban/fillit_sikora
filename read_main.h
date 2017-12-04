//
// Created by Jonathan on 04/12/2017.
//

#ifndef FILLIT_READ_MAIN_H
#define FILLIT_READ_MAIN_H

#include "file_id.h"
#include "error.h"

/* ft_read()
 *
 * This function read a file and stock the content in a list
 *
 * The function fails (return FALSE) in the following successive cases:
 * - the internal_context doesn't exist (READ_MAIN__FT_READ__NOT_INITIALIZE)
 */

#define READ_MAIN__FT_READ__NOT_INITIALIZE		FAILURE_CODE_FORMAT(FILLIT_READ_MAIN_ID, 3, 1)
#define READ_MAIN__FT_READ__STOCK_FAILED		FAILURE_CODE_FORMAT(FILLIT_READ_MAIN_ID, 3, 2)

t_bool		ft_read(t_tetris			**out_tetriminos_lst,
					t_failure_code		*out_failure_code);

#endif //FILLIT_READ_MAIN_H
