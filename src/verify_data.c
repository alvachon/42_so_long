/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:54:38 by alvachon          #+#    #+#             */
/*   Updated: 2022/12/08 10:21:46 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

t_target	*collect(int n, int x_index, int y_index, t_target *last)
{
	t_target	*collectible_data;

	collectible_data = ft_calloc(1, sizeof(t_target));
	collectible_data->number = n;
	collectible_data->index_y = y_index;
	collectible_data->index_x = x_index;
	collectible_data->prev = last;
	return (collectible_data);
}

void	verify_data(t_master *game)
{
	if (game->data->player.quantity != 1)
		null_error(DUPLICATE, game);
	if (game->data->exit.quantity != 1)
		null_error(DUPLICATE, game);
	if (game->data->to_collect < 1)
		null_error(MORE_COLLECT, game);
}

void	data_player(t_master *game, t_nav *map, int i)
{
	game->data->player.quantity += 1;
	game->data->player.index_row = map->index;
	game->data->player.index_col = i;
	game->data->p_y = map->index;
	game->data->p_x = i;
}

void	data_exit(t_master *game, t_nav *map, int i)
{
		game->data->exit.quantity += 1;
		game->data->exit.index_row = map->index;
		game->data->exit.index_col = i;
}

void	data_collect(t_master *game, t_nav *map)
{
	int	i;

	i = 1;
	while (map->line[i] != '\0')
	{
		if (map->line[i] == 'P')
			data_player(game, map, i);
		if (map->line[i] == 'E')
			data_exit(game, map, i);
		if (map->line[i] == 'C')
		{
			game->data->to_collect += 1;
			if (game->data->to_collect != 1)
			{
				game->data->collectible->next = collect(game->data->to_collect,
						i, map->index, game->data->collectible);
				game->data->collectible = game->data->collectible->next;
			}
			if (game->data->to_collect == 1)
				game->data->collectible = collect(game->data->to_collect,
						i, map->index, NULL);
		}
		i++;
	}
}
