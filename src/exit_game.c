/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 10:00:11 by alvachon          #+#    #+#             */
/*   Updated: 2022/12/08 13:46:25 by alvachon         ###   ########.fr       */
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
	game->map = game->map->next;
	while (game->map->next)
	{
		free(game->map->prev);
		game->map = game->map->next;
	}
	game->map = game->map->next;
	free(game->map->prev);
	free(game->map);
	game->map = NULL;
}

void	del_array(t_master *game)
{
	char	**line;

	line = game->path;
	while (line)
	{
		if (*line != NULL)
			free(*line);
	}
	game->path = NULL;
	return ;
}

void	del_game(t_master *game)
{
	if (game->data->collectible)
		del_target(game);
	if (game->map)
		del_nav(game);
	if (game->path)
		del_array(game);
	if (game->data)
	{
		free(game->data);
		game->data = NULL;
	}
	free(game);
	game = NULL;
	return ;
}
