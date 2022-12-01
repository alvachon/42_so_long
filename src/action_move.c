/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 18:25:34 by alvachon          #+#    #+#             */
/*   Updated: 2022/11/30 19:05:43 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	player_up(t_master *game)
{
	if (move_autorisation_up(game) == 0)
	{
		if (game->map->line[game->data->p_x] != 'E')
			set_floor(game, game->data->p_x, game->data->p_y);
		else
			set_exit(game, game->data->p_x, game->data->p_y);
		set_player(game, game->data->p_x, game->map->prev->index);
		place_at_player_up(game);
		collect_data(game);
	}
}

void	player_down(t_master *game)
{
	if (move_autorisation_down(game) == 0)
	{
		if (game->map->line[game->data->p_x] != 'E')
			set_floor(game, game->data->p_x, game->data->p_y);
		else
			set_exit(game, game->data->p_x, game->data->p_y);
		set_player(game, game->data->p_x, game->map->next->index);
		place_at_player_down(game);
		collect_data(game);
	}
}

void	player_left(t_master *game)
{
	if (move_autorisation_left(game) == 0)
	{
		if (game->map->line[game->data->p_x] != 'E')
			set_floor(game, game->data->p_x, game->data->p_y);
		else
			set_exit(game, game->data->p_x, game->data->p_y);
		set_player(game, game->data->p_x - 1, game->data->p_y);
		collect_data(game);
	}
}

void	player_right(t_master *game)
{
	if (move_autorisation_right(game) == 0)
	{
		if (game->map->line[game->data->p_x] != 'E')
			set_floor(game, game->data->p_x, game->data->p_y);
		else
			set_exit(game, game->data->p_x, game->data->p_y);
		set_player(game, game->data->p_x + 1, game->data->p_y);
		collect_data(game);
	}
}
