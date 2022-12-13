#include "cub3d.h"

void	draw_img(t_info *info, char c, int x, int y)
{
	if (c == 'N')
		mlx_put_image_to_window(info->mlx, info->win, \
			info->textures[0].img, x, y);
}

void	draw_map(t_info *info)
{
	int	i;
	int	j;

	i = -1;
	mlx_clear_window(info->mlx, info->win);
	while (++i < info->map_height)
	{
		j = -1;
		while (++j < info->map_width)
			draw_img(info, info->map[i][j], \
					j * info->img_len, i * info->img_len);
	}
}
