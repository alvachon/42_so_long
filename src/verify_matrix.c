/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 13:29:25 by alvachon          #+#    #+#             */
/*   Updated: 2022/12/05 16:06:07 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	verify_matrix(t_master *game)
{
	int		i;
	int		len;
	t_nav	*copy;

	i = 1;
	len = game->map->len - 2;
	copy = game->map;
	game->map = game->map->next;
/*while (game->data->zone_exit != 1)
		flood_fill_next(i, game);
	while (game->map->index != 2)
		flood_fill_prev(len, game);*/
	//verify_zone(game);
	exit(1);
	game->map = copy;
}
