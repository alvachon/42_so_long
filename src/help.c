/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 11:36:31 by alvachon          #+#    #+#             */
/*   Updated: 2022/12/02 16:02:51 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	free_element(t_data *element)
{
	free(element);
	return (MLX_ERROR);
}

int	error(char *message)
{
	if (1)
		write(2, message, ft_strlen(message));
	return (1);
}

void	*null_error(char *message)
{
	error(message);
	exit(1);
}

void	place_at_player_up(t_master *game)
{
	while (game->map->index != game->data->p_y)
		game->map = game->map->prev;
}

void	place_at_player_down(t_master *game)
{
	while (game->map->index != game->data->p_y)
		game->map = game->map->next;
}
