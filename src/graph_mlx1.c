/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_mlx1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:03:50 by alvachon          #+#    #+#             */
/*   Updated: 2022/11/30 19:05:43 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	all_floor(int x, t_master *game)
{
	int	y;
	int	index_row;

	y = 32;
	index_row = 2;
	while (y < game->mlx->win_y - 32 && index_row < (game->data->max_row - 1))
	{
		while (x < game->mlx->win_x - 32)
		{
			mlx_put_image_to_window(game->mlx->mlx, game->mlx->win,
				game->mlx->img->floor, x, y);
			x += 32;
		}
		x = 32;
		y += 32;
		index_row++;
	}
}

void	set_floor(t_master *game, int i, int row)
{
	mlx_put_image_to_window(game->mlx->mlx, game->mlx->win,
		game->mlx->img->floor, i * 32, (row * 32) - 32);
}

void	set_active(t_master *game)
{
	int	i;

	game->map = game->map->next;
	while (game->map->index != game->data->max_row)
	{
		i = 1;
		while (i <= game->map->len - 2)
		{
			if (game->map->line[i] == '1')
				set_obs(game, i, game->map->index);
			if (game->map->line[i] == 'C')
				set_collect(game, i, game->map->index);
			if (game->map->line[i] == 'E')
				set_exit(game, i, game->map->index);
			if (game->map->line[i] == 'P')
				set_player(game, i, game->map->index);
			i++;
		}
		game->map = game->map->next;
	}
	place_at_player_up(game);
}
