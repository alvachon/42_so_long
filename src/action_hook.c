/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 18:21:12 by alvachon          #+#    #+#             */
/*   Updated: 2022/12/04 12:55:23 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	x_close(t_master *game)
{
	if (game)
	{
		mlx_clear_window(game, game->win);
		mlx_destroy_window(game, game->win);
	}
	exit (0);
}

/*int	red_exit(int key, t_master *game)
{
	key = 0;
	if (game)
	{
		mlx_clear_window(game, game->win);
		mlx_destroy_window(game, game->win);
	}
	exit (0);
}*/

int	key_hook(int key, t_master *game)
{
	/*if (key == 53)65307
		red_exit(key, game);*/
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
