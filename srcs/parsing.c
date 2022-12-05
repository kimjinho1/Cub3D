#include "cub3d.h"

/*
int	check_map_width_height(t_info *info)
{
	int		fd;
	char	*line;
	int		h;

	fd = open(info->map_path, O_RDONLY);
	get_next_line(fd, &line);
	info->w = ft_strlen(line);
	h = 1;
	free(line);
	while (get_next_line(fd, &line))
	{
		if (info->w != (int)ft_strlen(line))
		{
			free(line);
			return (0);
		}
		free(line);
		h++;
	}
	free(line);
	close(fd);
	if (h <= 3)
		return (0);
	info->h = h;
	return (1);
}

void	load_map(t_info *info)
{
	int	i;

	i = -1;
	info->map = (char **)malloc(sizeof(char *) * info->h);
	while (++i < info->h)
		get_next_line(info->fd, &info->map[i]);
}

void	check_wall(t_info *info)
{
	int	i;
	int	j;

	i = -1;
	while (++i < info->h)
	{
		if (i == 0 || i == info->h - 1)
		{
			j = -1;
			while (++j < info->w)
			{
				if (info->map[i][j] != '1')
					perror_free_exit("top/bottom wall error", info);
			}
		}
		else
		{
			if (info->map[i][0] != '1' || info->map[i][info->w - 1] != '1')
				perror_free_exit("middle wall error", info);
		}
	}
}

void	check_map_element(t_info *info)
{
	int	i;
	int	j;

	i = -1;
	while (++i < info->h)
	{
		j = -1;
		while (++j < info->w)
		{
			if (info->map[i][j] == 'P')
			{
				info->p_cnt++;
				info->y = i;
				info->x = j;
			}
			else if (info->map[i][j] == 'C')
				info->c_cnt++;
			else if (info->map[i][j] == 'E')
				info->e_cnt++;
			else if (info->map[i][j] != '0' && info->map[i][j] != '1')
				perror_free_exit("element error", info);
		}
	}
	if (info->p_cnt != 1 || info->c_cnt < 1 || info->e_cnt != 1)
		perror_free_exit("element error", info);
}

void	parse_map(t_info *info)
{
	if (!check_map_width_height(info))
		perror_exit("rectangular error");
	info->fd = open(info->map_path, O_RDONLY);
	load_map(info);
	check_wall(info);
	check_map_element(info);
}
*/
