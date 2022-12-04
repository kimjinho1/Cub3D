#include "cub3d.h"

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

static int	check_cub(t_info *info, char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 5)
		return (len);
	if (ft_strncmp(path + (len - 4), ".cub", 4) == 0)
		return (0);
	info->fd = open(path, O_RDONLY);
	if (info->fd == -1)
		perror_exit("infile error");
	return (1);
}

static int	return_line_type(int **li)
{
	if (ft_strncmp(li[0], "NO", 3) == 0)
		return (0);
	if (ft_strncmp(li[0], "SO", 3) == 0)
		return (1);
	if (ft_strncmp(li[0], "WE", 3) == 0)
		return (2);
	if (ft_strncmp(li[0], "EA", 3) == 0)
		return (3);
	if (ft_strncmp(li[0], "F", 2) == 0)
		return (4);
	if (ft_strncmp(li[0], "C", 2) == 0)
		return (5);
	return (-1);
}

static int	check_element_line(t_info *info, char *line)
{
	int	i;
	int	**li;

	i = -1;
	li = ft_split(line, " ");
	while (li[++i])
		;
	if (i != 2)
		perror_exit("element error");
	return (1);
}

static int	check_element(t_info *info)
{
	char	*line;
	int		i;

	info->check_li = (int *)malloc(sizeof(int) * 6);
	i = -1;
	info->check_cnt = 0;
	while (++i)
		info->check_li[i] = 0;
	//NO ./path_to_the_north_texture
	//SO ./path_to_the_south_texture
	//WE ./path_to_the_west_texture
	//EA ./path_to_the_east_texture
	//F 220,100,0
	//C 225,30,0
	while (get_next_line(info->fd, &line))
	{
		check_element_line(info);
		free(line);
	}
	free(line);
	return (0);
}

int	main(int ac, char **av)
{
	t_info	info;

	if (ac != 2)
		perror_exit("argument error");
	if (check_cub(&info, av[1]) == 1)
		perror_exit("infile error");
	check_element(&info);
	/*
	printf("w: %d, h: %d\n", info.w, info.h);
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
