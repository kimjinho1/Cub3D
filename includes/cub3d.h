#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <fcntl.h>
# include "libft.h"
# include "../mlx/mlx.h"

# define X_EVENT_KEY_PRESS	    2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_KEY_EXIT		17

# define KEY_ESC		53
# define KEY_W			13
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2

# define BUFFER_SIZE 	42
# define OPEN_MAX 		10240

typedef struct s_info
{
	int		fd;

	int		*check_li;
	int		check_cnt;

	char	**texture_image_paths;
	void	**texture_images;
	int		*f_rgb;
	int		*c_rgb;

	char	**map;
	int		map_width;
	int		map_height;
	char	*first_line;
	char	nsew;
	int		empty_flag;
	char	*av_path;

	int		y;
	int		x;
	int		img_len;
	void	*mlx;
	void	*win;
}				t_info;

// gnl.c
size_t			gnl_strlen(const char *s);
size_t			gnl_strlcpy(char *dst, const char *src, size_t size);
size_t			gnl_strlcat(char *dst, const char *src, size_t size);
char			*gnl_strdup(const char *s);
char			*gnl_strjoin(char *s1, char *s2);
int				get_next_line(int fd, char **line);

//utils.c
void			init_info(t_info *info);
void			free_info(t_info *info);
void			free_arr(char **arr);
int				check_arr_size(char *str, char c, int n);

//exit.c
void			perror_exit(char *opt);
void			perror_free_exit(char *opt, t_info *info);
int				mlx_destroy_exit(t_info *info);

//element_check.c
int				check_cub(t_info *info, char *path);
int				check_element(t_info *info);
int				texture_path_check(t_info *info);

//map_check.c
int				check_map(t_info *info);
int				check_map2(t_info *info);

void			parse_map(t_info *info);

void			draw_map(t_info *info);

int				key_press(int key, t_info *info);

#endif