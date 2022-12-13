#include "cub3d.h"

	/*
void	init_info(t_info *info, char *map_path)
{
	//int	img_len;
	int	fd;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		perror_exit("infile error");
	close(fd);
	info->img_len = 64;
	info->move_cnt = 0;
	info->p_cnt = 0;
	info->c_cnt = 0;
	info->e_cnt = 0;
	info->mlx = mlx_init();
	info->g_img = mlx_xpm_file_to_image(info->mlx,
			"images/g.xpm", &img_len, &img_len);
	info->w_img = mlx_xpm_file_to_image(info->mlx,
			"images/w.xpm", &img_len, &img_len);
	info->p_img = mlx_xpm_file_to_image(info->mlx,
			"images/p1.xpm", &img_len, &img_len);
	info->c_img = mlx_xpm_file_to_image(info->mlx,
			"images/c.xpm", &img_len, &img_len);
	info->e_img = mlx_xpm_file_to_image(info->mlx,
			"images/open.xpm", &img_len, &img_len);
}
		*/

void	init_info(t_info *info)
{
	int	i;

	i = -1;
	info->check_cnt = 0;
	info->check_li = (int *)malloc(sizeof(int) * 6);
	info->f_rgb = (int *)malloc(sizeof(int) * 3);
	info->c_rgb = (int *)malloc(sizeof(int) * 3);
	info->texture_image_paths = (char **)malloc(sizeof(char *) * 4);
	info->textures = (t_texture *)malloc(sizeof(t_texture) * 4);
	while (++i < 6)
		info->check_li[i] = 0;
	info->mlx = mlx_init();
}

void	free_info(t_info *info)
{
	int	i;

	free(info->check_li);
	free(info->f_rgb);
	free(info->c_rgb);
	i = -1;
	while (++i < 4)
		free(info->texture_image_paths[i]);
	free(info->texture_image_paths);
	free(info->textures);
	i = -1;
	while (++i < info->map_height)
		free(info->map[i]);
	free(info->map);
	free(info->first_line);
}

void	free_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

int	check_arr_size(char *str, char c, int n)
{
	int		i;
	char	**li;

	i = -1;
	li = ft_split(str, c);
	while (li[++i])
		;
	free_arr(li);
	if (i != n)
		return (-1);
	return (1);
}
