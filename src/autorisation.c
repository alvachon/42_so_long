/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autorisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 18:47:29 by alvachon          #+#    #+#             */
/*   Updated: 2022/12/13 17:43:37 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	move_autorisation_up(t_master *game)
{
	if (game->map->prev->index == 1)
		return (1);
	if (game->map->prev->line[game->data->p_x] == '1')
		return (1);
	else
		return (0);
}

int	move_autorisation_down(t_master *game)
{
	if (game->map->next->index == game->map->index)
		return (1);
	if (game->map->next->line[game->data->p_x] == '1')
		return (1);
	else
		return (0);
}

int	move_autorisation_left(t_master *game)
{
	if (game->map->line[game->data->p_x - 1] == '1')
		return (1);
	else
		return (0);
}

int	move_autorisation_right(t_master *game)
{
	if (game->map->line[game->data->p_x + 1] == '1')
		return (1);
	else
		return (0);
}
