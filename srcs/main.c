#include "cub3d.h"

int	main(int ac, char **av)
{
	t_info	info;

	if (ac != 2)
		perror_exit("argument error");
	if (check_cub(&info, av[1]) == -1)
		perror_exit("infile error");
	init_info(&info);
	if (check_element(&info) == -1)
		perror_exit("element error");
	if (texture_path_check(&info) == -1)
		perror_exit("texture path error");
	if (check_map(&info) == -1)
		perror_exit("map error");
	if (check_map2(&info) == -1)
		perror_exit("map2 error");
	info.win = mlx_new_window(info.mlx, info.img_len * info.map_width,
			info.img_len * info.map_height, "zelda so_long");
	draw_map(&info);
	mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, &key_press, &info);
	mlx_hook(info.win, X_EVENT_KEY_EXIT, 0, &mlx_destroy_exit, &info);
	mlx_loop(info.mlx);
	return (0);
}
