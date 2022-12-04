/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_contour.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 11:54:17 by alvachon          #+#    #+#             */
/*   Updated: 2022/12/04 16:07:36 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

t_nav	*keep_data(int row_index, char *line, t_nav *last)
{
	t_nav	*map;

	map = ft_calloc(1, sizeof(t_nav));
	map->len = ft_strlen(line) - 1;
	map->index = row_index;
	map->line = line;
	map->verif = line;
	map->prev = last;
	return (map);
}

void	get_all_data(char *line, int fd, int i, t_nav **map)
{
	while (line)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		i++;
		(*map)->next = keep_data(i, line, *map);
		*map = (*map)->next;
	}
	(*map)->len += 1;
}

void	verify_dimension(int x, int y)
{
	if (x < 5 || y < 3)
		null_error(NO_PLAY);
}

void	verify_x_wall(t_master *game, t_nav *map)
{
	int	i;

	i = 0;
	while (i != map->len)
	{
		if (map->line[i] != '1')
			null_error(LIMIT_WALL);
		i++;
	}
	if (map->index == game->data->max_row)
	{
		verify_data(game);
		return ;
	}
}

void	verify_y_wall(t_master *game, t_nav *map)
{
	int		len;

	len = map->len;
	if (map->line[0] != '1' || map->line[len - 1] != '1')
		null_error(LIMIT_WALL);
	data_collect(game, map);
}
