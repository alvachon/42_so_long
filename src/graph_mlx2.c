/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_mlx2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 18:04:46 by alvachon          #+#    #+#             */
/*   Updated: 2022/12/13 17:43:52 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	set_obs(t_master *game, int i, int row)
{
	mlx_put_image_to_window(game->mlx, game->win,
		game->o_wall, i * 32, (row * 32) - 32);
}

void	set_player(t_master *game, int i, int row)
{
	game->player = mlx_xpm_file_to_image(game->mlx,
			"include/xpm/pj.xpm", &game->x, &game->y);
	if (game->player == NULL)
	{
		free_element(game->player);
		exit(1);
	}
	mlx_put_image_to_window(game->mlx, game->win,
		game->player, i * 32, (row * 32) - 32);
	game->data->p_x = i;
	game->data->p_y = row;
}

void	set_exit(t_master *game, int i, int row)
{
	game->u_exit = mlx_xpm_file_to_image(game->mlx,
			"include/xpm/exit_inact.xpm", &game->x, &game->y);
	if (game->u_exit == NULL)
	{
		free_element(game->u_exit);
		exit(1);
	}
	game->a_exit = mlx_xpm_file_to_image(game->mlx,
			"include/xpm/exit_act.xpm", &game->x, &game->y);
	if (game->a_exit == NULL)
	{
		free_element(game->a_exit);
		exit(1);
	}
	mlx_put_image_to_window(game->mlx, game->win,
		game->u_exit, i * 32, (row * 32) - 32);
}

void	set_unlock(t_master *game, int i, int row)
{
	mlx_put_image_to_window(game->mlx, game->win,
		game->a_exit, i * 32, (row * 32) - 32);
}

void	set_collect(t_master *game, int i, int row)
{
	game->collect = mlx_xpm_file_to_image(game->mlx,
			"include/xpm/collect.xpm", &game->x, &game->y);
	if (game->collect == NULL)
	{
		free_element(game->collect);
		exit(1);
	}
	mlx_put_image_to_window(game->mlx, game->win,
		game->collect, i * 32, (row * 32) - 32);
}
