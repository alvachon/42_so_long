/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 11:07:24 by alvachon          #+#    #+#             */
/*   Updated: 2022/12/08 14:51:21 by alvachon         ###   ########.fr       */
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

typedef struct s_nav
{
	int				len;
	int				index;
	char			*line;
	struct s_nav	*prev;
	struct s_nav	*next;
}	t_nav;

typedef struct s_info
{
	int				quantity;
	int				index_row;
	int				index_col;
}	t_info;

typedef struct s_target
{
	int				number;
	int				index_x;
	int				index_y;
	int				taken;
	struct s_target	*next;
	struct s_target	*prev;
}	t_target;

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
}	t_master;

/*action_collect.c*/
void		reset_collect(t_master *game);
int			collect_taken(t_master *game);
void		collect_data(t_master *game);

/*exit_game*/
void		del_target(t_master *game);
void		del_nav(t_master *game);
void		del_game(t_master *game);

/*so_long.c*/
t_master	*set_memory(void);
void		verify_map(t_master *game, t_nav *map);
void		verify_file(int fd, t_master *game);
void		verify(int ac, char **av, t_master *game);
int			main(int ac, char **av);

/*verify_contour.c*/
t_nav		*keep_data(int row_index, char *line, t_nav *last);
void		get_all_data(char *line, int fd, int i, t_nav **map);
void		verify_dimension(int x, int y, t_master *game);
void		verify_x_wall(t_master *game, t_nav *map);
void		verify_y_wall(t_master *game, t_nav *map);

/*verify_data.c*/
t_target	*collect(int n, int x_index, int y_index, t_target *last);
void		verify_data(t_master *game);
int			ft_strchr(const char *s, char c);
void		data(t_master *game, t_nav *map, int i);
void		data_collect(t_master *game, t_nav *map);

/*verify_matrix.c*/
char		**copy_map(t_master *game);
int			verify_flood(t_master *game, int x, int y);

/*graph_mlx.c*/
void		corner(t_master *game);
void		set_row_wall(t_master *game);
void		set_col_wall(t_master *game);
void		row_wall(int pos, t_master *game);
void		col_wall(int pos, t_master *game);

/*graph_mlx1.c*/
void		all_floor(int x, t_master *game);
void		set_floor(t_master *game, int i, int row);
void		set_active(t_master *game);
void		graph_mlx(t_master *game);

/*graph_mlx2.c*/
void		set_obs(t_master *game, int i, int row);
void		set_player(t_master *game, int i, int row);
void		set_exit(t_master *game, int i, int row);
void		set_unlock(t_master *game, int i, int row);
void		set_collect(t_master *game, int i, int row);

/*autorisation.c*/
int			move_autorisation_up(t_master *game);
int			move_autorisation_down(t_master *game);
int			move_autorisation_left(t_master *game);
int			move_autorisation_right(t_master *game);

/*move.c*/
void		player_up(t_master *game);
void		player_down(t_master *game);
void		player_left(t_master *game);
void		player_right(t_master *game);

/*hook.c*/
int			x_close(int keycode, t_master *game);
int			key_hook(int key, t_master *game);
void		del_target(t_master *game);
void		del_nav(t_master *game);
int			esc(t_master *game);

/*04_gnl.c*/
char		*ft_strrchr(const char *s, int c);
void		ft_copy_next(char *s1, char *s2);
int			ft_get_line(char *container, char **line);
char		*ft_free(char **line);
char		*get_next_line(int fd);

/*05_utils.c*/
int			ft_strcmp(char *s1, char *s2);
size_t		ft_strlen(const char *s);
void		*ft_memset(void *b, int c, size_t len);
void		*ft_calloc(size_t count, size_t size);
char		*ft_strjoin(char *s1, char *s2);

/*07_return.c*/
int			free_element(t_data *element);
int			error(char *message);
void		*null_error(char *message, t_master *game);
void		place_at_player_up(t_master *game);
void		place_at_player_down(t_master *game);

#endif
