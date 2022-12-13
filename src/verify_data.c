/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:54:38 by alvachon          #+#    #+#             */
/*   Updated: 2022/12/13 14:19:29 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

t_target	*collect(int n, int x_index, int y_index, t_target *last)
{
	t_target	*collectible_data;

	collectible_data = ft_calloc(1, sizeof(t_target));
	collectible_data->number = n;
	collectible_data->index_y = y_index;
	collectible_data->index_x = x_index;
	collectible_data->prev = last;
	return (collectible_data);
}

void	verify_data(t_master *game)
{
	if (game->data->player.quantity != 1)
		null_error(DUPLICATE, game);
	if (game->data->exit.quantity != 1)
		null_error(DUPLICATE, game);
	if (game->data->to_collect < 1)
		null_error(MORE_COLLECT, game);
	while (game->map->prev != NULL)
		game->map = game->map->prev;
}

void	data(t_master *game, int i)
{
	if (game->map->line[i] == 'P')
	{
		game->data->player.quantity += 1;
		game->data->player.index_row = game->map->index;
		game->data->player.index_col = i;
		game->data->p_y = game->map->index;
		game->data->p_x = i;
	}
	else if (game->map->line[i] == 'E')
	{
		game->data->exit.quantity += 1;
		game->data->exit.index_row = game->map->index;
		game->data->exit.index_col = i;
	}
}

int	ft_strchr(const char *s, char c)
{
	while (*s != c)
	{
		if (*s == '\0')
			return (1);
		s++;
	}
	return (0);
}

void	data_collect(t_master *game)
{
	int	i;

	i = 1;
	while (game->map->line[i] != '\0' && i < game->map->len)
	{
		if (ft_strchr("PE", game->map->line[i]) == 0)
			data(game, i);
		if (ft_strchr("PEC10", game->map->line[i]) == 1)
			null_error(INTRUDER, game);
		if (game->map->line[i] == 'C')
		{
			game->data->to_collect += 1;
			if (game->data->to_collect != 1)
			{
				game->data->collectible->next = collect(game->data->to_collect,
						i, game->map->index, game->data->collectible);
				game->data->collectible = game->data->collectible->next;
			}
			if (game->data->to_collect == 1)
				game->data->collectible = collect(game->data->to_collect,
						i, game->map->index, NULL);
		}
		i++;
	}
}
