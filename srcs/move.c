/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 18:23:37 by jinhokim          #+#    #+#             */
/*   Updated: 2022/12/14 18:23:38 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move(t_info *info, double dy, double dx)
{
	double	y;
	double	x;

	y = info->player_y + dy * info->move_speed * 3;
	x = info->player_x + dx * info->move_speed * 3;
	if (info->map[(int)y][(int)info->player_x] != '1')
		info->player_y += dy * info->move_speed;
	if (info->map[(int)info->player_y][(int)x] != '1')
		info->player_x += dx * info->move_speed;
}

static void	rotate_right(t_info *info)
{
	double	old_dir_y;
	double	old_plane_y;

	old_dir_y = info->dir_y;
	info->dir_y = info->dir_y * cos(info->rotate_speed) - \
		info->dir_x * sin(info->rotate_speed);
	info->dir_x = old_dir_y * sin(info->rotate_speed) + \
		info->dir_x * cos(info->rotate_speed);
	old_plane_y = info->plane_y;
	info->plane_y = info->plane_y * cos(info->rotate_speed) - \
		info->plane_x * sin(info->rotate_speed);
	info->plane_x = old_plane_y * sin(info->rotate_speed) + \
		info->plane_x * cos(info->rotate_speed);
}

static void	rotate_left(t_info *info)
{
	double	old_dir_y;
	double	old_plane_y;

	old_dir_y = info->dir_y;
	printf("1, dir_x: %f, dir_y: %f\n", info->dir_x, info->dir_y);
	printf("1, plane_x: %f, plane_y: %f\n", info->plane_x, info->plane_y);
	info->dir_y = info->dir_y * cos(-info->rotate_speed) - \
		info->dir_x * sin(-info->rotate_speed);
	info->dir_x = old_dir_y * sin(-info->rotate_speed) + \
		info->dir_x * cos(-info->rotate_speed);
	old_plane_y = info->plane_y;
	info->plane_y = info->plane_y * cos(-info->rotate_speed) - \
		info->plane_x * sin(-info->rotate_speed);
	info->plane_x = old_plane_y * sin(-info->rotate_speed) + \
		info->plane_x * cos(-info->rotate_speed);
	printf("2, dir_x: %f, dir_y: %f\n", info->dir_x, info->dir_y);
	printf("2, plane_x: %f, plane_y: %f\n", info->plane_x, info->plane_y);
}

int	key_press(int key, t_info *info)
{
	if (key == KEY_W)
		move(info, info->dir_y, info->dir_x);
	else if (key == KEY_A)
		move(info, -info->dir_x, info->dir_y);
	else if (key == KEY_S)
		move(info, -info->dir_y, -info->dir_x);
	else if (key == KEY_D)
		move(info, info->dir_x, -info->dir_y);
	else if (key == KEY_LEFT)
		rotate_left(info);
	else if (key == KEY_RIGHT)
		rotate_right(info);
	else if (key == KEY_ESC)
		mlx_destroy_exit(info);
	else
		return (0);
	draw_map(info);
	return (1);
}
