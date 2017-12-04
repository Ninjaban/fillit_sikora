/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 16:20:02 by cpieri            #+#    #+#             */
/*   Updated: 2017/12/04 13:20:39 by nsikora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

/* # include "libft/libft.h" */
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

typedef	struct			s_tetris
{
	char				**tetriminos;
	unsigned int		number;
	unsigned int		height;
	unsigned int		width;
	struct s_tetris		*next;
}						t_tetris;

typedef	struct			s_map
{
	char				**map;
	int					x;
	int					y;
}						t_map;

void					print_lst(t_tetris *lst);
void					solve_to_map(t_tetris *lst);
t_tetris				*tetris_lstnew(char *s, unsigned int number);
t_tetris				*check_file(int fd);
void					ft_putstr(const char *s);
void					ft_putendl(const char *s);
void					ft_putchar(char c);

#endif
