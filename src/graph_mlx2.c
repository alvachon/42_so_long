/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_mlx2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 18:04:46 by alvachon          #+#    #+#             */
/*   Updated: 2022/11/30 19:05:43 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	set_obs(t_master *game, int i, int row)
{
	mlx_put_image_to_window(game->mlx->mlx, game->mlx->win,
		game->mlx->img->o_wall, i * 32, (row * 32) - 32);
}

void	set_player(t_master *game, int i, int row)
{
	mlx_put_image_to_window(game->mlx->mlx, game->mlx->win,
		game->mlx->img->player, i * 32, (row * 32) - 32);
	game->data->p_x = i;
	game->data->p_y = row;
}

void	set_exit(t_master *game, int i, int row)
{
	mlx_put_image_to_window(game->mlx->mlx, game->mlx->win,
		game->mlx->img->u_exit, i * 32, (row * 32) - 32);
}

void	set_unlock(t_master *game, int i, int row)
{
	mlx_put_image_to_window(game->mlx->mlx, game->mlx->win,
		game->mlx->img->a_exit, i * 32, (row * 32) - 32);
}

void	set_collect(t_master *game, int i, int row)
{
	mlx_put_image_to_window(game->mlx->mlx, game->mlx->win,
		game->mlx->img->collect, i * 32, (row * 32) - 32);
}
