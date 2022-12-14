/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_contour.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 11:54:17 by alvachon          #+#    #+#             */
/*   Updated: 2022/12/13 14:13:31 by alvachon         ###   ########.fr       */
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

void	verify_dimension(int x, int y, t_master *game)
{
	if (x < 5 || y < 3)
		null_error(NO_PLAY, game);
}

void	verify_x_wall(t_master *game)
{
	int	i;

	i = 0;
	while (i != game->map->len)
	{
		if (game->map->line[i] != '1')
			null_error(LIMIT_WALL, game);
		i++;
	}
	if (game->map->index == game->data->max_row)
	{
		verify_data(game);
		return ;
	}
}

void	verify_y_wall(t_master *game)
{
	int		len;

	len = game->map->len;
	if (game->map->line[0] != '1' || game->map->line[len - 1] != '1')
		null_error(LIMIT_WALL, game);
	data_collect(game);
}
