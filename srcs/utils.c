#include "cub3d.h"

void	init_info(t_info *info, char *map_path)
{
	//int	img_len;
	int	fd;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		perror_exit("infile error");
	close(fd);
	info->map_path = map_path;
	info->img_len = 64;
	/*
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
		*/
}

void	free_info(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->h)
		free(info->map[i]);
	free(info->map);
}

void	perror_exit(char *opt)
{
	perror(opt);
	exit(EXIT_FAILURE);
}

void	perror_free_exit(char *opt, t_info *info)
{
	perror(opt);
	free_info(info);
	exit(EXIT_FAILURE);
}

int	mlx_destroy_exit(t_info *info)
{
	mlx_destroy_window(info->mlx, info->win);
	free_info(info);
	exit(EXIT_SUCCESS);
}
