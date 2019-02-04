/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeguin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 14:03:02 by tbeguin           #+#    #+#             */
/*   Updated: 2019/02/04 19:32:22 by msaubin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include "libft/libft.h"
# include <fcntl.h>

typedef struct	s_tetri
{
	char		height;
	char		width;
	char		**tetri;
}				t_tetri;

typedef struct	s_map
{
	char		**array;
	char		size;
}				t_map;

t_list			*ft_read_tetri(int fd);
int				ft_check_input(char *s, int ret);
int				ft_check_links(char *s);
int				ft_check_sharp(char *s);
t_tetri			*ft_convert_to_tetri(char *str, int tetri_nb);
t_tetri			*ft_get_tetrimino(char *str, int tetri_nb, int *len_tetri);
t_list			*ft_free_list(t_list *alst);
void			ft_free_tetri(t_tetri *tetri);
void			ft_free_map(t_map *amap);
t_map			*ft_new_map(char size);
t_tetri			*ft_new_tetri(char **tetri, int height, int width);
char			**ft_new_tab_2d(int height, int width);
int				ft_high_sqrt(int nb);
int				ft_solve(t_list *lst);
int				ft_solve_next(t_map *map, t_list *lst);
int				ft_put_tetri(t_map *map, t_tetri *atetri, int i_put, int j_put);
int				ft_del_tetri(t_map *map, t_tetri *atetri, int i_put, int j_put);
void			ft_display_map(t_map *map);
int				ft_last_check(int fd);
#endif
