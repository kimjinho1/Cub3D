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
	printf("dy: %f, dx: %f\n", dy, dx);
	printf("y: %f, x: %f\n", y, x);
	if ((info->map[(int)y][(int)info->player_x] == '0' || \
			info->map[(int)y][(int)info->player_x] == info->ewsn) &&
			(info->map[(int)info->player_y][(int)x] == '0' || \
			info->map[(int)info->player_y][(int)x] == info->ewsn))
	{
		info->player_y += dy * info->move_speed;
		info->player_x += dx * info->move_speed;
	}
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
	info->dir_y = info->dir_y * cos(-info->rotate_speed) - \
		info->dir_x * sin(-info->rotate_speed);
	info->dir_x = old_dir_y * sin(-info->rotate_speed) + \
		info->dir_x * cos(-info->rotate_speed);
	old_plane_y = info->plane_y;
	info->plane_y = info->plane_y * cos(-info->rotate_speed) - \
		info->plane_x * sin(-info->rotate_speed);
	info->plane_x = old_plane_y * sin(-info->rotate_speed) + \
		info->plane_x * cos(-info->rotate_speed);
}

// E -> 회전  좌우
// W -> move  좌우
// S -> move  좌우
// N -> 회전  좌우


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
