/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 18:24:09 by jinhokim          #+#    #+#             */
/*   Updated: 2022/12/14 18:24:10 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	main_loop(t_info *info)
{
	draw_floor_ceil(info);
	raycast(info);
	draw_map(info);
	return (0);
}

int	main(int ac, char **av)
{
	t_parse	parse;
	t_info	info;

	if (ac != 2)
		perror_exit("argument error");
	if (check_cub(&parse, av[1]) == -1)
		perror_exit("infile error");
	init_data(&parse, &info);
	if (check_element(&parse, &info) == -1)
		perror_exit("element error");
	if (texture_path_check(&parse, &info) == -1)
		perror_exit("texture path error");
	if (check_map(&parse, &info) == -1)
		perror_exit("map error");
	if (check_map2(&parse, &info) == -1)
		perror_exit("map2 error");
	free_parse(&parse);
	init(&info);
	mlx_loop_hook(info.mlx, &main_loop, &info);
	mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, &key_press, &info);
	mlx_hook(info.win, X_EVENT_KEY_EXIT, 0, &mlx_destroy_exit, &info);
	mlx_loop(info.mlx);
	return (0);
}
