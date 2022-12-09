/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 10:00:11 by alvachon          #+#    #+#             */
/*   Updated: 2022/12/09 11:51:39 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	del_target(t_master *game)
{
	t_target	*next;

	if (game->data == NULL || game->data->collectible == NULL)
		return ;
	while (game->data->collectible->prev != NULL)
		game->data->collectible = game->data->collectible->prev;
	while (game->data->collectible != NULL)
	{
		next = game->data->collectible->next;
		free(game->data->collectible);
		game->data->collectible = next;
	}
	game->data->collectible = NULL;
}

void	del_nav(t_master *game)
{
	t_nav	*next;

	if (game->map == NULL)
		return ;
	while (game->map->prev != NULL)
		game->map = game->map->prev;
	while (game->map != NULL)
	{
		next = game->map->next;
		free(game->map);
		game->map = next;
	}
	game->map = NULL;
}

void	del_array(t_master *game)
{
	char	**line;

	if (game->path == NULL)
		return ;
	line = game->path;
	while (line != NULL && *line != NULL)
	{
		free(*line);
		line++;
	}
	game->path = NULL;
	return ;
}

void	del_game(t_master *game)
{
	if (game->data && game->data->collectible)
		del_target(game);
	if (game->map)
		del_nav(game);
	if (game->path)
		del_array(game);
	if (game->data != NULL)
	{
		free(game->data);
		game->data = NULL;
	}
	mlx_destroy_window(game->mlx, game->win);
	free(game);
	game = NULL;
	exit(0);
}
