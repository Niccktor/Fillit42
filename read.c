/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaubin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 12:57:49 by msaubin           #+#    #+#             */
/*   Updated: 2019/02/05 18:42:55 by tbeguin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

t_list	*ft_read_tetri(int fd)
{
	char		*buf;
	ssize_t		ret;
	t_list		*list;
	t_tetri		*tetri;
	int			tetri_nb;

	buf = ft_strnew(21);
	list = NULL;
	tetri_nb = 0;
	while ((ret = read(fd, buf, 21)) >= 20 && buf)
	{
		if (ft_check_input(buf, ret) == -1
				|| (tetri = ft_convert_to_tetri(buf, tetri_nb++)) == NULL)
		{
			ft_memdel((void **)&buf);
			return (ft_free_list(list));
		}
		ft_lstadd(&list, ft_lstnew(tetri, sizeof(t_tetri)));
		ft_memdel((void **)&tetri);
	}
	if (ret != 0 || tetri_nb > 26 || !buf)
		return (ft_free_list(list));
	ft_memdel((void **)&buf);
	ft_lstrev(&list);
	return (list);
}

int		ft_check_input(char *s, int ret)
{
	int		i;

	if (ft_check_sharp(s) != 4 || ft_check_links(s) == -1)
		return (-1);
	i = 0;
	while (s[i] && i < 20)
	{
		if ((i + 1) % 5 != '\0' && (s[i] == '.' || s[i] == '#'))
			i++;
		else if ((i + 1) % 5 == 0 && s[i] == '\n')
			i++;
		else
			return (-1);
	}
	if (ret == 21 && s[20] != '\n')
		return (-1);
	else
		return (0);
}

int		ft_check_links(char *s)
{
	int	i;
	int	links;

	i = 0;
	links = 0;
	while (s[i])
	{
		if (s[i] == '#')
		{
			if (i >= 1 && s[i - 1] == '#')
				links++;
			if (i >= 5 && s[i - 5] == '#')
				links++;
			if (i < 19 && s[i + 1] == '#')
				links++;
			if (i < 15 && s[i + 5] == '#')
				links++;
		}
		i++;
	}
	if (links == 6 || links == 8)
		return (0);
	return (-1);
}

int		ft_check_sharp(char *s)
{
	int	i;
	int	sharp;

	i = 0;
	sharp = 0;
	while (s[i])
	{
		if (s[i] == '#')
			sharp++;
		i++;
	}
	return (sharp);
}

int		ft_last_check(int fd)
{
	ssize_t		ret;
	char		*buf;

	buf = ft_strnew(26 * 21);
	if (!buf)
		return (-1);
	ret = read(fd, buf, 26 * 21);
	if ((ret + 1) % 21 == 0)
	{
		ft_memdel((void **)&buf);
		return (0);
	}
	ft_memdel((void **)&buf);
	return (-1);
}
