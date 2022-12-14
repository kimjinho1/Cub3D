/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 18:23:42 by jinhokim          #+#    #+#             */
/*   Updated: 2022/12/14 18:23:43 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_data(t_parse *parse, t_info *info)
{
	int	i;

	i = -1;
	parse->check_li = (int *)malloc(sizeof(int) * 6);
	while (++i < 6)
		parse->check_li[i] = 0;
	parse->check_cnt = 0;
	parse->texture_image_paths = (char **)malloc(sizeof(char *) * 4);
	parse->empty_flag = 0;
	parse->first_line = NULL;
	info->ewsn = 0;
	info->map_width = 0;
	info->map_height = 0;
	info->img_len = 64;
	info->f_rgb = (int *)malloc(sizeof(int) * 3);
	info->c_rgb = (int *)malloc(sizeof(int) * 3);
	info->imgs = (t_img *)malloc(sizeof(t_img) * 4);
	info->mlx = mlx_init();
}

void	free_parse(t_parse *parse)
{
	int	i;

	i = -1;
	while (++i < 4)
		free(parse->texture_image_paths[i]);
	free(parse->texture_image_paths);
	free(parse->check_li);
	free(parse->first_line);
}

void	free_info(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->map_height)
		free(info->map[i]);
	free(info->map);
	free(info->buf);
	free(info->f_rgb);
	free(info->c_rgb);
	free(info->imgs);
}

void	free_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

void	init(t_info *info)
{
	t_ray	ray;

	info->dir_y = 0;
	info->dir_x = 0;
	if (info->ewsn == 'E')
		info->dir_x++;
	else if (info->ewsn == 'W')
		info->dir_x--;
	else if (info->ewsn == 'S')
		info->dir_y++;
	else if (info->ewsn == 'N')
		info->dir_y--;
	info->move_speed = 0.047319731;
	info->rotate_speed = 0.05;
	info->buf = (int *)malloc(sizeof(int) * WIDTH * HEIGHT);
	info->win = mlx_new_window(info->mlx, WIDTH, HEIGHT, "cub3d");
	info->img.img = mlx_new_image(info->mlx, WIDTH, HEIGHT);
	info->img.data_addr = (int *)mlx_get_data_addr(info->img.img, \
			&info->img.bpp, &info->img.size, &info->img.endian);
	info->ray = &ray;
	first_ray_init(info);
}
