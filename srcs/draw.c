/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 18:23:12 by jinhokim          #+#    #+#             */
/*   Updated: 2022/12/14 18:23:14 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_floor_ceil(t_info *info)
{
	int	i;
	int	j;
	int	f_color;
	int	c_color;

	i = -1;
	f_color = info->f_rgb[0] << 16 | info->f_rgb[1] << 8 | info->f_rgb[2];
	c_color = info->c_rgb[0] << 16 | info->c_rgb[1] << 8 | info->c_rgb[2];
	while (++i < (int)(HEIGHT / 2))
	{
		j = -1;
		while (++j < WIDTH)
		{
			info->buf[i * WIDTH + j] = f_color;
			info->buf[(HEIGHT - i - 1) * WIDTH + j] = c_color;
		}
	}
}

static void	set_buf_color(t_info *info, int x, int y)
{
	int	color;

	color = info->imgs[info->ray->texture_i].data_addr[TEXTURE_WIDTH * \
				info->ray->tex_y + info->ray->tex_x];
	info->buf[y * WIDTH + x] = color;
}

void	draw_vertical_line(t_info *info, int x)
{
	double	step;
	int		start;
	int		end;
	double	tex_pos;

	if ((info->ray->side == 0 && info->ray->ray_dir_y > 0) || \
			(info->ray->side == 1 && info->ray->ray_dir_x < 0))
		info->ray->tex_x = TEXTURE_WIDTH - info->ray->tex_x - 1;
	step = 1.0 * TEXTURE_HEIGHT / info->ray->height;
	start = HEIGHT / 2 - info->ray->height / 2;
	if (start < 0)
		start = 0;
	end = HEIGHT / 2 + info->ray->height / 2;
	if (end >= HEIGHT)
		end = HEIGHT - 1;
	tex_pos = (start + info->ray->height / 2 - HEIGHT / 2) * step;
	while (start++ < end)
	{
		info->ray->tex_y = (int)tex_pos & (TEXTURE_HEIGHT - 1);
		tex_pos += step;
		set_buf_color(info, x, start);
	}
}

void	draw_map(t_info *info)
{
	int		i;
	int		j;

	i = -1;
	while (++i < HEIGHT)
	{
		j = -1;
		while (++j < WIDTH)
			info->img.data_addr[i * WIDTH + j] = info->buf[i * WIDTH + j];
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
}
