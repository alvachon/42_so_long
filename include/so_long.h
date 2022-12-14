/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 11:07:24 by alvachon          #+#    #+#             */
/*   Updated: 2022/12/14 10:49:06 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <stdint.h>

# define MLX_ERROR 0
# define NO_FILE "Error\n No file\n"
# define FILE_TYPE "Error\n Bad file type\n"
# define NO_TEXT "Error\n File is empty\n"
# define NO_PLAY "Error\n Map is too small\n"
# define ARG_COUNT "Error\n Argument count\n"
# define NOT_REC "Error\n Map is not rectangular\n"
# define LIMIT_WALL "Error\n Map is not surrounded by wall\n"
# define INTRUDER "Error\n Character not allowed in the map\n"
# define DUPLICATE "Error\n Quantity of data is not autorised\n"
# define MORE_COLLECT "Error\n Need at least one object to collect\n"
# define INVALID "Error\n Unplayable game\n"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE BUFSIZ
# endif

# if BUFFER_SIZE > 9223372036854775806
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

/*
* Each node of this struct contain map data, indexed by Y (row) postion.
*/
typedef struct s_nav
{
	int				len;
	int				index;
	char			*line;
	struct s_nav	*prev;
	struct s_nav	*next;
}	t_nav
;
/*
* Each copy of this struct contain information about unique data.
* ex : Player, Exit.
*/
typedef struct s_info
{
	int				quantity;
	int				index_row;
	int				index_col;
}	t_info
;
/*
* Each node of this struct contain data of a collectible,
* with position and target trigger.
*/
typedef struct s_target
{
	int				number;
	int				index_x;
	int				index_y;
	int				taken;
	struct s_target	*next;
	struct s_target	*prev;
}	t_target;

/*
* This struct contain essential data for the game mechanic and refer to
* 3 sub-structs (player, exit, collectible).
*/
typedef struct s_data
{
	int				max_row;
	int				p_x;
	int				p_y;
	int				move_count;
	int				trig_exit;
	int				collected;
	int				to_collect;
	t_info			player;
	t_info			exit;
	t_target		*collectible;
}	t_data;

/*
* This struct link to 2 sub-structs (map, data) and contain data for mlx.
*/
typedef struct s_master
{
	t_nav			*map;
	t_data			*data;
	void			*mlx;
	void			*win;
	int				win_x;
	int				win_y;
	int				x;
	int				y;
	char			**path;
	void			*n_wall;
	void			*s_wall;
	void			*e_wall;
	void			*w_wall;
	void			*o_wall;
	void			*floor;
	void			*player;
	void			*collect;
	void			*u_exit;
	void			*a_exit;
}	t_master
;

/*
* action_collect.c (mechanic)
*/
// Access the first node of data collectible.
void		reset_collect(t_master *game);
// Check position of collectible in the map and return access if taken or not.
int			collect_taken(t_master *game);
// Set elements associated to the exit tile that make quit the game.
void		unlock_exit(t_master *game);
// System mechanic triggered by the number of collected items to quit the game.
void		collect_data(t_master *game);

/*
* action_hook.c (key and X close)
*/
// Close the game with the graphic X button.
int			x_close(int keycode, t_master *game);
// Close the game with esc key.
int			esc(t_master *game);
// System call for key hook.
int			key_hook(int key, t_master *game);

/*
* action_move.c (Action linked with a key hook)
*/
void		player_up(t_master *game);
void		player_down(t_master *game);
void		player_left(t_master *game);
void		player_right(t_master *game);

/*
* autorisation.c
* (System to access or not an action asked in action_move.c)
*/
int			move_autorisation_up(t_master *game);
int			move_autorisation_down(t_master *game);
int			move_autorisation_left(t_master *game);
int			move_autorisation_right(t_master *game);

/*
* exit_game.c
*/
void		del_target(t_master *game);
void		del_array(t_master **game);
void		del_game(t_master *game);

/*
* gnl.c (Get_next_line)
*/
char		*ft_strrchr(const char *s, int c);
void		ft_copy_next(char *s1, char *s2);
int			ft_get_line(char *container, char **line);
char		*ft_free(char **line);
char		*get_next_line(int fd);

/*
* graph_mlx.c (wall and corner)
*/
// (corner) img ref for the mlx and postion.
void		corner(t_master *game);
// (wall) img ref for the mlx.
void		set_row_wall(t_master *game);
// (wall) img ref for the mlx.
void		set_col_wall(t_master *game);
// (wall) img position for the first and last row.
void		row_wall(int pos, t_master *game);
// (wall) img position for the first and last element in a row.
void		col_wall(int pos, t_master *game);

/*
 * graph_mlx1.c (floor and mechanic)
 */
// (floor) img ref for the mlx and postion.
void		all_floor(int x, t_master *game);
// (floor) floor printer for walking player.
void		set_floor(t_master *game, int i, int row);
// Mechanic to set images for obstacle, collectible, exit, player.
void		set_active(t_master *game);
// System mechanic to set graphics (2 levels, background and active)
void		graph_mlx(t_master *game);

/*
*  graph_mlx2.c (active elements associated with data)
*/
// (wall) obstacle printer function.
void		set_obs(t_master *game, int i, int row);
// (player) img ref for the mlx and postion at start.
void		set_player(t_master *game, int i, int row);
// (active and unactive exit) img ref for the mlx and postion at start.
void		set_exit(t_master *game, int i, int row);
// (active exit) active exit printer function.
void		set_unlock(t_master *game, int i, int row);
// (collectible) img ref for the mlx and postion at start.
void		set_collect(t_master *game, int i, int row);

/*
* help.c
*/
int			free_element(t_data *element);
int			error(char *message);
void		*null_error(char *message, t_master *game);
void		place_at_player_up(t_master *game);
void		place_at_player_down(t_master *game);

/*
* so_long.c (main)
*/
t_master	*set_memory(void);
void		verify_map(t_master *game);
void		verify_file(int fd, t_master *game);
void		verify(int ac, char **av, t_master *game);
int			main(int ac, char **av);

/*
* utils.c (libft functions)
*/
int			ft_strcmp(char *s1, char *s2);
size_t		ft_strlen(const char *s);
void		*ft_memset(void *b, int c, size_t len);
void		*ft_calloc(size_t count, size_t size);
char		*ft_strjoin(char *s1, char *s2);

/*
* verify_contour.c (Collect data, verify dimensions and wall contours)
*/
// Adding node with map-row information.
t_nav		*keep_data(int row_index, char *line, t_nav *last);
// Transfer information fd to node.
void		get_all_data(char *line, int fd, int i, t_nav **map);
// Trigger for min dimension.
void		verify_dimension(int x, int y, t_master *game);
// Verify row that are all wall
void		verify_x_wall(t_master *game);
// Verify wall positioned at (0 and max_len) if they are indeed, walls.
void		verify_y_wall(t_master *game);

/*
* verify_data.c
*/
// Adding node with collectible information.
t_target	*collect(int n, int x_index, int y_index, t_target *last);
// Verify data for game mechanics (player, exit, collectible)
void		verify_data(t_master *game);
// Add data in information struct if 'P' or 'E' at position.
void		data(t_master *game, int i);
int			ft_strchr(const char *s, char c);
// System mechanic to verify the amount, type of data.
void		data_collect(t_master *game);

/*
* verify_matrix.c (food_fill)
*/
char		*ft_strdup(const char *str);
char		**copy_map(t_master *game);
int			verify_flood(t_master *game, int x, int y);

#endif
