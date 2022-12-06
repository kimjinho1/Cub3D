#include "cub3d.h"

void check_map2_insert(t_info *info, char *map_low, char *line)
{
	int i;

	i = -1;
	while (line[++i])
	{
		map_low[i] = line[i];
	}
	i --;
	while (++i < info->map_width)
		map_low[i] = ' ';
}

int check_map2_init(t_info *info)
{
	int		i;
	char	*line;

	info->fd = open(info->av_path, O_RDONLY);
	if (info->fd == -1)
		return (-1);
	i = -1;
	info->map = (char **)malloc(sizeof(char *) * info->map_height);
	while (++i < info->map_height)
		info->map[i] = (char *)malloc(sizeof(char) * info->map_width);
	i = -1;
	while (1)
	{
		get_next_line(info->fd, &line);
		if (ft_strncmp(line, info->first_line, info->map_width) == 0)
			break;
		free(line);
	}
	while (++i < info->map_height)
	{
		check_map2_insert(info, info->map[i], line);
		get_next_line(info->fd, &line);
	}
	close (info->fd);
	return (0);
}

int check_map2_valid_loop(t_info *info, int ga, int se)
{
	if (info->map[se][ga] == '0' || info->map[se][ga] == info->NSEW)
	{
		if (ga <= 0 || se <= 0 || ga >= info->map_width - 1 || se >= info->map_height - 1)
			return (-1);
		else
		{
			if (info->map[se][ga - 1] == ' ' || info->map[se][ga + 1] == ' ' || \
			info->map[se - 1][ga] == ' ' || info->map[se + 1][ga] == ' ')
				return (-1);
			else
				return (0);
		}
	}
	return (0);
}

int check_map2_valid(t_info *info)
{
	int	i;
	int j;

	i = -1;
	j = -1;
	while (++i < info->map_height)
	{
		while (++j < info->map_width)
		{
			if (check_map2_valid_loop(info, j, i) == -1)
			{
				printf("%d %d\n",j,i);
				return (-1);
			}
		}
		j = -1;
	}
	return (0);
}

int	check_map2(t_info *info)
{
	if (check_map2_init(info) == -1)
		return (-1);
	int i = -1;
	printf("--- PRINT MAP ---\n");
	while (++i < info->map_height)
		printf("%s-\n", info->map[i]);
	if (check_map2_valid(info) == -1)
		return (-1);
	return (1);
}