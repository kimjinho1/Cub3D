#include "cub3d.h"

static int	check_map_line(t_info *info, char *line)
{
	int 	i;

	i = -1;
	if (ft_strlen(line) == 0 && info->empty_flag == 0)
		return (1);
	else if (ft_strlen(line) == 0 && info->empty_flag != 0)
		return (-1);
	//check_arr_size(line, ' ', 2)
	// -> ft_split(line, ' ')의 길이가 2인지 확인함 아니면 -1
	while (line[++i])
	{
		if (info->NSEW_flag > 1)
			return (-1);
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
		{
			info->NSEW = line[i];
			info->NSEW_flag ++;
		}
		else if (line[i] != '1' && line[i] != ' ' && line[i] != '0')
			return (-1);
		i ++;
	}
	if (info->map_width < i - 1)
		info->map_width = i - 1;
	info->map_height++;
	info->empty_flag = 1;
	return (1);
}

void check_map_init(t_info *info)
{
	info->NSEW_flag = 0;
	info->empty_flag = 0;
	info->map_height = 0;
	info->first_line = NULL;
}

int	check_map(t_info *info)
{
	char	*line;

	check_map_init(info);
	while (1)
	{
		if (get_next_line(info->fd, &line) == 0 && ft_strlen(line) == 0)
		{
			close(info->fd);
			free(line);
			if (info->empty_flag == 1)
				return (1);
			return (-1);
		}
		if (check_map_line(info, line) == -1)
		{
			close(info->fd);
			free(line);
			return (-1);
		}
		if (info->map_height == 1)
		{
			info->first_line = malloc(sizeof(char) * ft_strlen(line));
			ft_strlcpy(info->first_line, line, ft_strlen(line) + 1);
		}
		free(line);
	}
	return (1);
}