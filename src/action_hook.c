/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 18:21:12 by alvachon          #+#    #+#             */
/*   Updated: 2022/12/07 14:25:07 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	del_target(t_master *game)
{
	t_target	*collect;

	while (game->data->collectible)
	{
		collect = game->data->collectible->next;
		free(game->data->collectible);
		game->data->collectible = collect;
	}
	game->data->collectible = NULL;
}

void	del_nav(t_master *game)
{
	t_nav	*map;

	while (game->map)
	{
		map = game->map->next;
		free(game->map);
		game->map = map;
	}
	game->map = NULL;
}

void	del_game(t_master *game)
{
	del_target(game);
	del_nav(game);
	free(game);
	game = NULL;
	return ;
}

int	x_close(int keycode, t_master *game)
{
	keycode = 0;
	if (game && keycode)
		del_game(game);
	exit(0);
}

int	esc(t_master *game)
{
	mlx_destroy_window(game, game->win);
	del_game(game);
	exit (0);
}

int	key_hook(int key, t_master *game)
{
	if (key == 53 || 65307)
		esc(game);
	if (key == 13 || key == 119)
		player_up(game);
	if (key == 1 || key == 115)
		player_down(game);
	if (key == 0 || key == 97)
		player_left(game);
	if (key == 2 || key == 100)
		player_right(game);
	return (0);
}
