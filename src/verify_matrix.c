/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 13:29:25 by alvachon          #+#    #+#             */
/*   Updated: 2022/12/02 16:03:04 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	matrix(t_nav **map, int i)
{
	if ((*map)->line[i] == 'P' || (*map)->line[i] == 'E'
		|| (*map)->line[i] == 'C' || (*map)->line[i] == '0')
			(*map)->verif[i] = '0';
}

int	x_1(t_nav **map, int i)
{
	while ((*map)->verif[i] == '1' && i < (*map)->len)
	{
		i++;
		if (i + 1 == (*map)->len)
		{
			i = 1;
			(*map) = (*map)->next;
		}
	}
	return (i);
}

void	verify_matrix(t_master *game)
{
	int		i;
	int		total;
	int		trig;
	t_nav	*map;

	i = 1;
	trig = 0;
	total = 0;
	map = game->map;
	map = map->next;
	while (map->index < game->data->max_row)
	{
		if (trig == 0)
			i = x_1(&map, i);
		if (map->verif[i] != 1)
			trig = 1;
		while (map->verif[i] != '1' && i < map->len)
		{
			map->verif[i] = 'x';
			if (map->line[i] == 'C' || map->line[i] == 'E'
				|| map->line[i] == 'P')
				total++;
			i++;
			if (i + 1 == map->len)
			{
				i = 1;
				printf(" print line : %s\n", map->verif);
				map = map->next;
			}
		}
	}
	exit (1);
}
