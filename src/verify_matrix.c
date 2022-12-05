/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 13:29:25 by alvachon          #+#    #+#             */
/*   Updated: 2022/12/05 18:29:26 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static char	*ft_strdup(const char *str)
{
	size_t	i;
	size_t	len;
	char	*copy;

	i = 0;
	len = ft_strlen(str);
	copy = ft_calloc(len + 1, sizeof(char));
	while (i < len)
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char	**copy_map(t_master *game)
{
	char	**copy;
	int		i;

	i = 0;
	copy = ft_calloc(game->data->max_row + 1, sizeof(char *));
	while (i < game->data->max_row)
	{
		copy[i] = ft_strdup((const char *)game->map);
		i++;
	}
	return (copy);
}

int	verify_flood(t_master *game, int x, int y)
{
	static int	items = -1;
	static char	**map;

	if (items == -1)
		items = game->data->to_collect + 2;
	if (!map)
		map = copy_map(game);
	if (x >= 0 && x <= game->map->len && y >= 0 && y <= game->data->max_row)
	{
		if (map[y][x] == 'F')
			return (items);
		else
		{
			if (map[y][x] == 'C' || map[y][x] == 'E' || map[y][x] == 'P')
				items--;
			else if (map[y][x] == '1')
				return (items);
			map[y][x] = 'F';
		}
		verify_flood(game, x + 1, y);
		verify_flood(game, x - 1, y);
		verify_flood(game, x, y + 1);
		verify_flood(game, x, y - 1);
	}
	return (items);
}
