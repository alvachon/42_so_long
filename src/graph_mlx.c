/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 15:32:09 by alvachon          #+#    #+#             */
/*   Updated: 2022/11/30 19:05:43 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	set_xpm(t_master *game)
{
	game->mlx->img->n_wall = mlx_xpm_file_to_image(game->mlx->mlx,
			"include/xpm/wall_n.xpm", &game->mlx->x, &game->mlx->y);
	game->mlx->img->s_wall = mlx_xpm_file_to_image(game->mlx->mlx,
			"include/xpm/wall_s.xpm", &game->mlx->x, &game->mlx->y);
	game->mlx->img->e_wall = mlx_xpm_file_to_image(game->mlx->mlx,
			"include/xpm/wall_e.xpm", &game->mlx->x, &game->mlx->y);
	game->mlx->img->w_wall = mlx_xpm_file_to_image(game->mlx->mlx,
			"include/xpm/wall_w.xpm", &game->mlx->x, &game->mlx->y);
	game->mlx->img->o_wall = mlx_xpm_file_to_image(game->mlx->mlx,
			"include/xpm/corner.xpm", &game->mlx->x, &game->mlx->y);
	game->mlx->img->floor = mlx_xpm_file_to_image(game->mlx->mlx,
			"include/xpm/floor.xpm", &game->mlx->x, &game->mlx->y);
	game->mlx->img->a_exit = mlx_xpm_file_to_image(game->mlx->mlx,
			"include/xpm/exit_act.xpm", &game->mlx->x, &game->mlx->y);
	game->mlx->img->u_exit = mlx_xpm_file_to_image(game->mlx->mlx,
			"include/xpm/exit_unact.xpm", &game->mlx->x, &game->mlx->y);
	game->mlx->img->collect = mlx_xpm_file_to_image(game->mlx->mlx,
			"include/xpm/collect.xpm", &game->mlx->x, &game->mlx->y);
	game->mlx->img->player = mlx_xpm_file_to_image(game->mlx->mlx,
			"include/xpm/pj.xpm", &game->mlx->x, &game->mlx->y);
}

void	corner(t_master *game)
{
	mlx_put_image_to_window(game->mlx->mlx, game->mlx->win,
		game->mlx->img->o_wall, 0, 0);
	mlx_put_image_to_window(game->mlx->mlx, game->mlx->win,
		game->mlx->img->o_wall, 0, game->mlx->win_y - 32);
	mlx_put_image_to_window(game->mlx->mlx, game->mlx->win,
		game->mlx->img->o_wall, game->mlx->win_x - 32, 0);
	mlx_put_image_to_window(game->mlx->mlx, game->mlx->win,
		game->mlx->img->o_wall, game->mlx->win_x - 32, game->mlx->win_x - 32);
}

void	row_wall(int pos, t_master *game)
{
	while (pos != game->mlx->win_x - 32)
	{
		mlx_put_image_to_window(game->mlx->mlx, game->mlx->win,
			game->mlx->img->n_wall, pos, 0);
		pos += 32;
	}
	pos = 32;
	while (pos != game->mlx->win_x - 32)
	{
		mlx_put_image_to_window(game->mlx->mlx, game->mlx->win,
			game->mlx->img->s_wall, pos, game->mlx->win_y - 32);
		pos += 32;
	}
}

void	col_wall(int pos, t_master *game)
{
	while (pos != game->mlx->win_y - 32)
	{
		mlx_put_image_to_window(game->mlx->mlx, game->mlx->win,
			game->mlx->img->w_wall, 0, pos);
		pos += 32;
	}
	pos = 32;
	while (pos != game->mlx->win_y - 32)
	{
		mlx_put_image_to_window(game->mlx->mlx, game->mlx->win,
			game->mlx->img->w_wall, game->mlx->win_x - 32, pos);
		pos += 32;
	}
}

void	graph_mlx(t_master *game)
{
	int	position;

	position = 32;
	set_xpm(game);
	corner(game);
	row_wall(position, game);
	col_wall(position, game);
	all_floor(position, game);
	set_active(game);
}
