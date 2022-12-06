#include "cub3d.h"

static int	check_map_line(t_info *info, char *line)
{
	int	i;

	i = -1;
	if (ft_strlen(line) == 0 && info->empty_flag == 0)
		return (1);
	else if (ft_strlen(line) == 0 && info->empty_flag != 0)
		return (-1);
	while (line[++i])
	{
		if (info->nsew != 0 && (line[i] == 'N' || line[i] == 'S' || \
			line[i] == 'E' || line[i] == 'W'))
			return (-1);
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || \
			line[i] == 'W')
			info->nsew = line[i];
		else if (line[i] != '1' && line[i] != ' ' && line[i] != '0')
			return (-1);
	}
	if (info->map_width < i)
		info->map_width = i;
	info->map_height++;
	info->empty_flag = 1;
	return (1);
}

void	check_map_init(t_info *info)
{
	info->nsew = 0;
	info->empty_flag = 0;
	info->map_height = 0;
	info->first_line = NULL;
}

static int	check_map_free(t_info *info, char *line, int flag)
{
	close(info->fd);
	free(line);
	return (flag);
}

int	check_map(t_info *info)
{
	char	*line;
	int		r;

	check_map_init(info);
	while (1)
	{
		r = get_next_line(info->fd, &line);
		if (r == 0 && info->empty_flag == 0)
			return (check_map_free(info, line, -1));
		if (r == 1 && info->empty_flag == 1 && ft_strlen(line) == 0)
			return (check_map_free(info, line, -1));
		if (r == 0 && info->empty_flag == 1 && ft_strlen(line) != 0)
		{
			if (check_map_line(info, line) == -1)
				return (check_map_free(info, line, -1));
			return (check_map_free(info, line, 1));
		}
		if (check_map_line(info, line) == -1)
			return (check_map_free(info, line, -1));
		if (info->map_height == 1)
			info->first_line = ft_strdup(line);
		free(line);
	}
	return (1);
}

int	texture_path_check(t_info *info)
{
	int	i;
	int	fd;

	i = -1;
	while (++i < 4)
	{
		fd = open(info->texture_image_paths[i], O_WRONLY);
		if (fd == -1)
			return (-1);
		close(fd);
	}
	return (1);
}
