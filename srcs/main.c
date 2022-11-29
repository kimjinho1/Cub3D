#include "cub3d.h"

static int	check_cub(char *path)
{
	int	i;

	i = ft_strlen(path);
	if (i < 5)
		return (1);
	if (ft_strncmp(path + (i - 4), "cub", 4) == 0)
		return (1);
	return (0);
}

int	get_wh(t_info *info, char *pile_path)
{
	int		w;
	int		fd;
	char	*line;
	int		j;

	w = 0;
	info->h = 1;
	fd = open(pile_path, O_RDONLY);
	if (fd == -1)
		perror_exit("infile error");
	get_next_line(fd, &line);
	w = ft_strlen(line);
	free(line);
	while (get_next_line(fd, &line))
	{
		j = -1;
		while (line[++j])
			;
		if (w < j)
			w = j;
		free(line);
		info->h++;
	}
	free(line);
	info->w = w;
	return (0);
}

/*
int	check2(char *line, int x, int w)
{
	int	i;
	int	j;

	i = -2;
	while (++i < 2)
	{
		j = -2;
		while (++j < 2)
		{
			if (line[x + j] == 'N' || (i == 0 && j == 0))
				continue ;
			if (x + j < w && line[x + j] == 0)
				return (1);
			if (line[x + j] == ' ')
				return (1);
		}
	}
	return (0);
}

int	check_top_bottom(char *line, int w)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '0')
			return (1);
	}
	return (0);
}

int	check(char *pile_path)
{
	int		w;
	int		fd;
	char	*line;
	int		j;

	w = 0;
	fd = open(pile_path, O_RDONLY);
	if (fd == -1)
		perror_exit("infile error");
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

int	main(int ac, char **av)
{
	t_info	info;

	if (ac != 2)
		perror_exit("argument error");
	if (check_cub(av[1]) == 1)
		perror_exit("infile error");
	get_wh(&info, av[1]);
	printf("w: %d, h: %d\n", info.w, info.h);
	/*
	if (check(av[1]) == 1)
		perror_exit("map invalid error");
	init_info(&info, av[1]);
	parse_map(&info);
	info.win = mlx_new_window(info.mlx, info.img_len * info.w,
			info.img_len * info.h, "zelda so_long");
	draw_map(&info);
	mlx_hook(info.win, X_EVENT_KEY_RELEASE, 0, &key_press, &info);
	mlx_hook(info.win, X_EVENT_KEY_EXIT, 0, &mlx_destroy_exit, &info);
	mlx_loop(info.mlx);
	*/
	return (0);
}
