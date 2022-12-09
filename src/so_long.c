/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 11:28:33 by alvachon          #+#    #+#             */
/*   Updated: 2022/12/09 11:31:02 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

t_master	*set_memory(void)
{
	t_master	*game;
	t_data		*data;
	t_nav		*map;
	t_target	*collectible;

	game = ft_calloc(1, sizeof(t_master));
	if (!game)
		return (NULL);
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (NULL);
	map = ft_calloc(1, sizeof(t_nav));
	if (!map)
	{
		free(game);
		free(data);
		return (NULL);
	}
	collectible = ft_calloc(1, sizeof(t_target));
	if (!collectible)
	{
		free(game);
		free(data);
		free(map);
		return (NULL);
	}
	game->data = data;
	game->data->collectible = collectible;
	game->map = map;
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
			null_error(NOT_REC, game);
		if (map->index == 1 || map->index == game->data->max_row)
			verify_x_wall(game, map);
		else if (map->index > 1 || map->index < game->data->max_row)
			verify_y_wall(game, map);
		map = map->next;
		i++;
	}
	verify_dimension(len, game->data->max_row, game);
	game->win_x = len * 32;
	game->win_y = game->data->max_row * 32;
	game->map = copy;
}

void	verify_file(int fd, t_master *game)
{
	int		row_count;
	char	*line;
	t_nav	*map;

	row_count = 1;
	map = game->map;
	line = NULL;
	line = get_next_line(fd);
	if (!line)
		null_error(NO_FILE, game);
	map = keep_data(row_count, line, NULL);
	get_all_data(line, fd, row_count, &map);
	game->data->max_row = map->index;
	if (game->data->max_row <= 2)
		null_error(NO_PLAY, game);
	while (map->index != 1)
		map = map->prev;
	game->map = map;
	verify_map(game, map);
}

void	verify(int ac, char **av, t_master *game)
{
	int		fd;
	char	*str;

	fd = open(av[0], O_RDONLY);
	if (fd < 0)
		null_error(NO_FILE, game);
	if (ac != 2)
		null_error(ARG_COUNT, game);
	str = ft_strrchr(av[0], '.');
	while (ft_strlen(str) != 4)
		str = ft_strrchr(str, '.');
	if (ft_strcmp(str, ".ber") != 0)
		null_error(FILE_TYPE, game);
	verify_file(fd, game);
	if (verify_flood(game, game->data->p_x, game->data->p_y) != 0)
		null_error(INVALID, game);
	close(fd);
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
