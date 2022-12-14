/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 18:24:17 by jinhokim          #+#    #+#             */
/*   Updated: 2022/12/14 18:24:17 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	first_ray_init(t_info *info)
{
	int		x;
	double	camera_x;

	x = -1;
	while (++x < WIDTH)
	{
		info->plane_y = 0.0;
		info->plane_x = 0.0;
		if (info->dir_x != 0)
			info->plane_y = 0.66;
		else
			info->plane_x = 0.66;
		camera_x = 2 * x / (double)WIDTH - 1;
		info->ray->ray_dir_y = info->dir_y + info->plane_y * camera_x;
		info->ray->ray_dir_x = info->dir_x + info->plane_x * camera_x;
		info->ray->map_y = (int)info->player_y;
		info->ray->map_x = (int)info->player_x;
		info->ray->delta_dist_y = fabs(1 / info->ray->ray_dir_y);
		info->ray->delta_dist_x = fabs(1 / info->ray->ray_dir_x);
	}
}

static void	ray_init(t_info *info, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)WIDTH - 1;
	info->ray->ray_dir_y = info->dir_y + info->plane_y * camera_x;
	info->ray->ray_dir_x = info->dir_x + info->plane_x * camera_x;
	info->ray->map_y = (int)info->player_y;
	info->ray->map_x = (int)info->player_x;
	info->ray->delta_dist_y = fabs(1 / info->ray->ray_dir_y);
	info->ray->delta_dist_x = fabs(1 / info->ray->ray_dir_x);
}

static void	set_ray_step(t_info *info)
{
	if (info->ray->ray_dir_y < 0)
	{
		info->ray->step_y = -1;
		info->ray->side_dist_y = (info->player_y - info->ray->map_y) * \
			info->ray->delta_dist_y;
	}
	else
	{
		info->ray->step_y = 1;
		info->ray->side_dist_y = (info->ray->map_y + 1.0 - info->player_y) * \
			info->ray->delta_dist_y;
	}
	if (info->ray->ray_dir_x < 0)
	{
		info->ray->step_x = -1;
		info->ray->side_dist_x = (info->player_x - info->ray->map_x) * \
			info->ray->delta_dist_x;
	}
	else
	{
		info->ray->step_x = 1;
		info->ray->side_dist_x = (info->ray->map_x + 1.0 - info->player_x) * \
			info->ray->delta_dist_x;
	}
}

static void	dda(t_info *info)
{
	while (42)
	{
		if (info->ray->side_dist_y < info->ray->side_dist_x)
		{
			info->ray->side_dist_y += info->ray->delta_dist_y;
			info->ray->map_y += info->ray->step_y;
			info->ray->side = 0;
		}
		else
		{
			info->ray->side_dist_x += info->ray->delta_dist_x;
			info->ray->map_x += info->ray->step_x;
			info->ray->side = 1;
		}
		if (info->map[info->ray->map_y][info->ray->map_x] == '1')
			break ;
	}
	if (info->ray->ray_dir_x > 0 && info->ray->side == 1)
		info->ray->texture_i = 0;
	else if (info->ray->ray_dir_x < 0 && info->ray->side == 1)
		info->ray->texture_i = 1;
	else if (info->ray->ray_dir_y > 0 && info->ray->side == 0)
		info->ray->texture_i = 2;
	else if (info->ray->ray_dir_y < 0 && info->ray->side == 0)
		info->ray->texture_i = 3;
}

void	raycast(t_info *info)
{
	int		x;
	double	wall_dist;
	double	wall_x;

	x = -1;
	while (++x < WIDTH)
	{
		ray_init(info, x);
		set_ray_step(info);
		dda(info);
		if (info->ray->side == 0)
			wall_dist = (info->ray->map_y - info->player_y + \
				(1 - info->ray->step_y) / 2) / info->ray->ray_dir_y;
		else
			wall_dist = (info->ray->map_x - info->player_x + \
				(1 - info->ray->step_x) / 2) / info->ray->ray_dir_x;
		info->ray->height = (int)(HEIGHT / wall_dist);
		if (info->ray->side == 0)
			wall_x = info->player_x + wall_dist * info->ray->ray_dir_x;
		else
			wall_x = info->player_y + wall_dist * info->ray->ray_dir_y;
		wall_x -= floor(wall_x);
		info->ray->tex_x = (int)(wall_x * (double)TEXTURE_WIDTH);
		draw_vertical_line(info, x);
	}
}
