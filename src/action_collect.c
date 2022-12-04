/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_collect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 18:37:32 by alvachon          #+#    #+#             */
/*   Updated: 2022/12/04 16:00:49 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	reset_collect(t_master *game)
{
	while (game->data->collectible->number != 1)
		game->data->collectible = game->data->collectible->prev;
}

int	collect_taken(t_master *game)
{
	reset_collect(game);
	while (game->data->collectible->number <= game->data->to_collect)
	{
		if (game->data->collectible->index_y != game->data->p_y)
			game->data->collectible = game->data->collectible->next;
		if (game->data->collectible->index_y == game->data->p_y)
		{
			if (game->data->collectible->index_x == game->data->p_x)
			{
				if (game->data->collectible->taken != 1)
				{
					game->data->collectible->taken = 1;
					return (0);
				}
				else
					return (1);
			}
			else if (game->data->collectible->number < game->data->to_collect)
			{
				game->data->collectible = game->data->collectible->next;
			}
		}
	}
	return (0);
}

void	unlock_exit(t_master *game)
{
	game->data->trig_exit = 1;
	free_element(game->u_exit);
	set_unlock(game, game->data->exit.index_row - 1,
		game->data->exit.index_col + 1);
}

void	collect_data(t_master *game)
{
	if (game->map->line[game->data->p_x] == 'C')
	{
		if (collect_taken(game) == 0)
		{
			game->data->collected += 1;
			if (game->data->collected == game->data->to_collect)
				unlock_exit(game);
		}
	}
	if (game->map->line[game->data->p_x] == 'E')
	{
		if (game->data->trig_exit == 1)
		{
			exit(1);
			//win_the_game();
		}
	}
}
