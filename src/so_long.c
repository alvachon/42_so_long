/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 11:28:33 by alvachon          #+#    #+#             */
/*   Updated: 2022/11/30 19:32:12 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

t_master	*set_memory(void)
{
	static	t_master	*game = NULL;

	if (game == NULL)
		game = ft_calloc(1, sizeof(t_master));
	return (game);
}

void	verify_map(t_master *game, t_nav *map)
{
	int		i;
	int		len;
	t_nav	*copy;

	i = 1;
	len = map->len;
	copy = map;
	while (i <= game->data->max_row)
	{
		if (map->len != len)
			null_error(NOT_REC);
		if (map->index == 1 || map->index == game->data->max_row)
			verify_x_wall(game, map);
		else if (map->index > 1 || map->index < game->data->max_row)
			verify_y_wall(game, map);
		map = map->next;
		i++;
	}
	verify_dimension(len, game->data->max_row);
	game->mlx->win_x = len * 32;
	game->mlx->win_y = game->data->max_row * 32;
	game->map = copy;
}

void	verify_file(int fd, t_master *game)
{
	int		row_count;
	char	*line;
	t_nav	*map;
	t_data	*data;

	row_count = 1;
	map = game->map;
	data = game->data;
	line = NULL;
	line = get_next_line(fd);
	if (!line)
		null_error(NO_FILE);
	map = keep_data(row_count, line, NULL);
	get_all_data(line, fd, row_count, &map);
	printf("index : %d\n", map->index);
	game->data->max_row = 1;
	printf("max_row : %d\n", game->data->max_row);
	//game->data->max_row = map->index;
	exit(1);
	if (game->data->max_row <= 2)
		null_error(NO_PLAY);
	while (map->index != 1)
		map = map->prev;
	game->map = map;
	exit(1);
	verify_map(game, map);
}

void	verify(int ac, char **av, t_master *game)
{
	int		fd;
	char	*str;

	fd = open(av[0], O_RDONLY);
	if (fd < 0)
		null_error(NO_FILE);
	if (ac != 2)
		null_error(ARG_COUNT);
	str = ft_strrchr(av[0], '.');
	while (ft_strlen(str) != 4)
		str = ft_strrchr(str, '.');
	if (ft_strcmp(str, ".ber") != 0)
		null_error(FILE_TYPE);
	verify_file(fd, game);
	exit(1);
	verify_matrix(game);
	close(fd);
}

int	main(int ac, char **av)
{
	t_master	*game;

	game = set_memory();
	verify(ac, av + 1, game);
	game->mlx->mlx = mlx_init();
	graph_mlx(game);
	game->mlx->win = mlx_new_window(game->mlx->mlx,
			game->mlx->win_x, game->mlx->win_y, "so_long");
	mlx_hook(game->mlx->win, 17, 0, x_close, game);
	mlx_hook(game->mlx->win, 2, 0, key_hook, game);
	mlx_loop(game->mlx->mlx);
	return (0);
}
