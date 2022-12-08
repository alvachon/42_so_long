/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 10:00:11 by alvachon          #+#    #+#             */
/*   Updated: 2022/12/08 10:34:15 by alvachon         ###   ########.fr       */
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

void	del_array(char **array)
{
	char	**map;

	map = NULL;
	while (*array)
		free(*array);
	array = NULL;
}

void	del_game(t_master *game)
{
	del_target(game);
	del_nav(game);
	free(game);
	game = NULL;
	return ;
}
