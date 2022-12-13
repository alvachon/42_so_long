/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 10:00:11 by alvachon          #+#    #+#             */
/*   Updated: 2022/12/13 17:43:40 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	del_target(t_master *game)
{
	t_target	*next;

	while (game->data->collectible->prev != NULL)
		game->data->collectible = game->data->collectible->prev;
	while (game->data->collectible != NULL)
	{
		next = game->data->collectible->next;
		free(game->data->collectible);
		game->data->collectible = next;
	}
	free(game->data->collectible);
	game->data->collectible = NULL;
}

void	del_nav(t_master **game)
{
	t_nav	*next;

	while ((*game)->map->prev != NULL)
		(*game)->map = (*game)->map->prev;
	while ((*game)->map != NULL)
	{
		next = (*game)->map->next;
		free((*game)->map);
		(*game)->map = next;
	}
}

void	del_array(t_master **game)
{
	int		i;

	i = 0;
	if ((*game)->path == NULL)
		return ;
	while ((*game)->path[i] != NULL)
	{
		free((*game)->path[i]);
		i++;
	}
	free((*game)->path);
	(*game)->path = NULL;
	return ;
}

void	del_game(t_master *game)
{
	if (game->data->collectible != NULL)
		del_target(game);
	if (game->path != NULL)
		del_array(&game);
}
