/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeguin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 18:33:16 by tbeguin           #+#    #+#             */
/*   Updated: 2019/02/04 20:21:28 by msaubin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		ft_solve(t_list *lst)
{
	t_map	*map;
	int		size;

	size = ft_high_sqrt(ft_lstcount(lst) * 4);
	map = ft_new_map(size);
	while (ft_solve_next(map, lst) == -1)
	{
		size++;
		ft_free_map(map);
		map = ft_new_map(size);
	}
	ft_display_map(map);
	ft_free_map(map);
	return (0);
}

int		ft_solve_next(t_map *map, t_list *lst)
{
	int	i;
	int	j;

	if (lst == NULL)
		return (0);
	i = 0;
	while (i < map->size)
	{
		j = 0;
		while (j < map->size)
		{
			if (ft_put_tetri(map, (t_tetri *)(lst->content), i, j) == 0)
			{
				if (ft_solve_next(map, lst->next) == 0)
					return (0);
				else
					ft_del_tetri(map, lst->content, i, j);
			}
			else
				ft_del_tetri(map, lst->content, i, j);
			j++;
		}
		i++;
	}
	return (-1);
}

int		ft_del_tetri(t_map *map, t_tetri *atetri, int i_put, int j_put)
{
	int		i;
	int		j;
	char	car;

	if (atetri->height + i_put > map->size || atetri->width + j_put > map->size)
		return (-1);
	i = 0;
	car = '.';
	while (i < atetri->height)
	{
		j = 0;
		while (j < atetri->width)
		{
			if (atetri->tetri[i][j] != '.')
				car = atetri->tetri[i][j];
			if (map->array[i + i_put][j + j_put] == car && car != '.')
				map->array[i + i_put][j + j_put] = '.';
			j++;
		}
		i++;
	}
	return (0);
}

int		ft_put_tetri(t_map *map, t_tetri *atetri, int i_put, int j_put)
{
	int	i;
	int	j;

	i = 0;
	if (atetri->height + i_put > map->size || atetri->width + j_put > map->size)
		return (-1);
	while (i < atetri->height)
	{
		j = 0;
		while (j < atetri->width)
		{
			if (atetri->tetri[i][j] != '.' && \
					map->array[i + i_put][j + j_put] == '.')
				map->array[i + i_put][j + j_put] = atetri->tetri[i][j];
			else if (atetri->tetri[i][j] != '.')
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

void	ft_display_map(t_map *map)
{
	int i;

	i = 0;
	while (i < map->size)
	{
		ft_putstr(map->array[i]);
		ft_putchar('\n');
		i++;
	}
	ft_putchar('\n');
}
