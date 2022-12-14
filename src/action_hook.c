/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 18:21:12 by alvachon          #+#    #+#             */
/*   Updated: 2022/12/13 17:43:32 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	x_close(int keycode, t_master *game)
{
	if (keycode && game)
		del_game(game);
	exit(0);
	return (0);
}

int	esc(t_master *game)
{
	if (game)
		del_game(game);
	exit(0);
	return (0);
}

int	key_hook(int key, t_master *game)
{
	if (key == 53 || key == 65307)
		esc(game);
	if (!(key == 53 || key == 65307))
	{
		if (key == 13 || key == 119)
			player_up(game);
		if (key == 1 || key == 115)
			player_down(game);
		if (key == 0 || key == 97)
			player_left(game);
		if (key == 2 || key == 100)
			player_right(game);
		if (game->data)
		{
			game->data->move_count += 1;
			printf("Move count : %d\n", game->data->move_count);
		}
	}
	return (0);
}
