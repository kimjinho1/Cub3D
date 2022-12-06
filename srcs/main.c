#include "cub3d.h"

/*
int	check(char *pile_path)
{
	int		w;
	int		fd;
	char	*line;
	int		j;

	w = 0;
	get_next_line(fd, &line);
	if (check_top_bottom(line, w) == 1)
		return (1);
	w = ft_strlen(line);
	free(line);
	while (get_next_line(fd, &line))
	{
		j = -1;
		while (line[++j])
		{
			if (line[j] == '0' && check2(line, j, w) == 1)
				return (1);
		}
		if (w < j)
			w = j;
		free(line);
	}
	free(line);
	return (0);
}
*/

void	a(void) {
	system("leaks cub3d");
}

int	main(int ac, char **av)
{
	atexit(a);
	t_info	info;

	if (ac != 2)
		perror_exit("argument error");
	if (check_cub(&info, av[1]) == -1)
		perror_exit("infile error");
	init_info(&info);
	if (check_element(&info) == -1)
		perror_exit("element error");
	if (check_map(&info) == -1)
		perror_exit("map error");
	if (check_map2(&info) == -1)
		perror_exit("map2 error");
	// 맵 파싱 전까지는 에러, 누수 다 잡은 것 같음. 테스트 바람
	// 이제 개행이면 넘긴 후에 맵 파싱 구현해야함
//	for (int i = 0; i < 4; i++)
//		printf("path: %s\n", info.texture_image_paths[i]);
//	printf("f_rgb -> r: %d, g: %d, b: %d\n", info.f_rgb[0], info.f_rgb[1], info.f_rgb[2]);
//	printf("c_rgb -> r: %d, g: %d, b: %d\n", info.c_rgb[0], info.c_rgb[1], info.c_rgb[2]);
	free_info(&info);
	/*
	info.win = mlx_new_window(info.mlx, info.img_len * info.w,
			info.img_len * info.h, "zelda so_long");
	draw_map(&info);
	mlx_hook(info.win, X_EVENT_KEY_RELEASE, 0, &key_press, &info);
	mlx_hook(info.win, X_EVENT_KEY_EXIT, 0, &mlx_destroy_exit, &info);
	mlx_loop(info.mlx);
	*/
	return (0);
}
