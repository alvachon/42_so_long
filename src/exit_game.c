/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 10:00:11 by alvachon          #+#    #+#             */
/*   Updated: 2022/12/08 17:23:26 by alvachon         ###   ########.fr       */
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
	free(game->data->collectible);
	game->data->collectible = NULL;
}

void	del_nav(t_master *game)
{
	while (game->map->index != game->data->max_row)
		game->map = game->map->next;
	while (game->map)
	{
		free(game->map->prev);
		game->map = game->map->next;
	}
	free(game->map->prev);
	free(game->map);
	game->map->prev = NULL;
	game->map = NULL;
	game->map->next = NULL;
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

void	clean_graph(t_master *game)
{
	mlx_destroy_image(game->mlx, game->n_wall);
	mlx_destroy_image(game->mlx, game->s_wall);
	mlx_destroy_image(game->mlx, game->e_wall);
	mlx_destroy_image(game->mlx, game->w_wall);
	mlx_destroy_image(game->mlx, game->o_wall);
	mlx_destroy_image(game->mlx, game->floor);
	mlx_destroy_image(game->mlx, game->a_exit);
	mlx_destroy_image(game->mlx, game->u_exit);
	mlx_destroy_image(game->mlx, game->player);
	mlx_destroy_image(game->mlx, game->collect);
	mlx_clear_window(game->mlx, game->win);
	mlx_destroy_window(game->mlx, game->win);
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
	clean_graph(game);
	free(game);
	game = NULL;
	return ;
}
