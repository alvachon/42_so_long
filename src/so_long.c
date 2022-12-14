/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 11:28:33 by alvachon          #+#    #+#             */
/*   Updated: 2022/12/14 10:49:26 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

t_master	*set_memory(void)
{
	t_master	*game;

	game = ft_calloc(1, sizeof(t_master));
	game->data = ft_calloc(1, sizeof(t_data));
	return (game);
}

void	verify_map(t_master *game)
{
	int		i;
	int		len;

	i = 1;
	len = game->map->len;
	while (i <= game->data->max_row)
	{
		if (game->map->len != len)
			null_error(NOT_REC, game);
		if (game->map->index == 1 || game->map->index == game->data->max_row)
			verify_x_wall(game);
		else if (game->map->index > 1 || game->map->index < game->data->max_row)
			verify_y_wall(game);
		game->map = game->map->next;
		i++;
	}
	verify_dimension(len, game->data->max_row, game);
	while (game->map->index != 1)
		game->map = game->map->prev;
	game->win_x = len * 32;
	game->win_y = game->data->max_row * 32;
}

void	verify_file(int fd, t_master *game)
{
	int		row_count;
	char	*line;

	row_count = 1;
	line = NULL;
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		null_error(NO_FILE, game);
	}
	game->map = NULL;
	game->map = keep_data(row_count, line, game->map);
	get_all_data(line, fd, row_count, &game->map);
	game->data->max_row = game->map->index;
	if (game->data->max_row <= 2)
	{
		close(fd);
		null_error(NO_PLAY, game);
	}
	close(fd);
	while (game->map->prev != NULL)
		game->map = game->map->prev;
	verify_map(game);
}

void	verify(int ac, char **av, t_master *game)
{
	int		fd;
	char	*str;

	if (ac != 2)
		null_error(ARG_COUNT, game);
	str = ft_strrchr(av[0], '.');
	while (ft_strlen(str) != 4)
		str = ft_strrchr(str, '.');
	if (ft_strcmp(str, ".ber") != 0)
		null_error(FILE_TYPE, game);
	fd = open(av[0], O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		null_error(NO_FILE, game);
	}
	verify_file(fd, game);
	if (verify_flood(game, game->data->p_x, game->data->p_y - 1) != 0)
		null_error(INVALID, game);
}

int	main(int ac, char **av)
{
	t_master	*game;

	game = set_memory();
	verify(ac, av + 1, game);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx,
			game->win_x, game->win_y, "so_long");
	graph_mlx(game);
	mlx_hook(game->win, 17, 0, x_close, game);
	mlx_key_hook(game->win, key_hook, game);
	mlx_loop(game->mlx);
	return (0);
}
