#include "cub3d.h"

/*
void	draw_img(t_info *info, char c, int x, int y)
{
	mlx_put_image_to_window(info->mlx, info->win, info->g_img, x, y);
	if (c == '1')
		mlx_put_image_to_window(info->mlx, info->win, info->w_img, x, y);
	else if (c == 'P')
		mlx_put_image_to_window(info->mlx, info->win, info->p_img, x, y);
	else if (c == 'C')
		mlx_put_image_to_window(info->mlx, info->win, info->c_img, x, y);
	else if (c == 'E')
		mlx_put_image_to_window(info->mlx, info->win, info->e_img, x, y);
}

void	draw_map(t_info *info)
{
	int	i;
	int	j;

	i = -1;
	mlx_clear_window(info->mlx, info->win);
	while (++i < info->h)
	{
		j = -1;
		while (++j < info->w)
			draw_img(info, info->map[i][j], \
					j * info->img_len, i * info->img_len);
	}
}
*/