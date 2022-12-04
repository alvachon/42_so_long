/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 15:32:09 by alvachon          #+#    #+#             */
/*   Updated: 2022/12/03 21:55:17 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	set_xpm(t_master *game)
{
	game->floor = mlx_xpm_file_to_image(game->mlx,
			"include/xpm/floor.xpm", &game->x, &game->y);
	game->a_exit = mlx_xpm_file_to_image(game->mlx,
			"include/xpm/exit_act.xpm", &game->x, &game->y);
	game->u_exit = mlx_xpm_file_to_image(game->mlx,
			"include/xpm/exit_unact.xpm", &game->x, &game->y);
	game->collect = mlx_xpm_file_to_image(game->mlx,
			"include/xpm/collect.xpm", &game->x, &game->y);
	game->player = mlx_xpm_file_to_image(game->mlx,
			"include/xpm/pj.xpm", &game->x, &game->y);
}

void	corner(t_master *game)
{
	game->o_wall = mlx_xpm_file_to_image(game->mlx,
			"include/xpm/wall_o.xpm", &game->x, &game->y);
	if (game->o_wall == NULL)
	{
		free_element(game->o_wall);
		exit(1);
	}
	mlx_put_image_to_window(game->mlx, game->win,
		game->o_wall, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win,
		game->o_wall, 0, game->win_y - 32);
	mlx_put_image_to_window(game->mlx, game->win,
		game->o_wall, game->win_x - 32, 0);
	mlx_put_image_to_window(game->mlx, game->win,
		game->o_wall, game->win_x - 32, game->win_x - 32);
}

void	set_row_wall(t_master *game)
{
	game->n_wall = mlx_xpm_file_to_image(game->mlx,
			"include/xpm/wall_n.xpm", &game->x, &game->y);
	if (game->n_wall == NULL)
	{
		free_element(game->n_wall);
		exit(1);
	}
	game->s_wall = mlx_xpm_file_to_image(game->mlx,
			"include/xpm/wall_s.xpm", &game->x, &game->y);
	if (game->s_wall == NULL)
	{
		free_element(game->s_wall);
		exit(1);
	}
}

void	set_col_wall(t_master *game)
{
	game->e_wall = mlx_xpm_file_to_image(game->mlx,
			"include/xpm/wall_e.xpm", &game->x, &game->y);
	if (game->e_wall == NULL)
	{
		free_element(game->e_wall);
		exit(1);
	}
	game->w_wall = mlx_xpm_file_to_image(game->mlx,
			"include/xpm/wall_w.xpm", &game->x, &game->y);
	if (game->w_wall == NULL)
	{
		free_element(game->w_wall);
		exit(1);
	}
}

void	row_wall(int pos, t_master *game)
{
	set_row_wall(game);
	while (pos != game->win_x - 32)
	{
		mlx_put_image_to_window(game->mlx, game->win,
			game->n_wall, pos, 0);
		pos += 32;
	}
	pos = 32;
	while (pos != game->win_x - 32)
	{
		mlx_put_image_to_window(game->mlx, game->win,
			game->s_wall, pos, game->win_y - 32);
		pos += 32;
	}
}

void	col_wall(int pos, t_master *game)
{
	set_col_wall(game);
	while (pos != game->win_y - 32)
	{
		mlx_put_image_to_window(game->mlx, game->win,
			game->w_wall, 0, pos);
		pos += 32;
	}
	pos = 32;
	while (pos != game->win_y - 32)
	{
		mlx_put_image_to_window(game->mlx, game->win,
			game->w_wall, game->win_x - 32, pos);
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
	exit(1);
	all_floor(position, game);
	set_active(game);
}
