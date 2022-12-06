#include "cub3d.h"

int	check_cub(t_info *info, char *path)
{
	int	i;

	i = ft_strlen(path);
	if (i < 5)
		return (-1);
	if (ft_strncmp(path + (i - 4), ".cub", 4) != 0)
		return (-1);
	info->fd = open(path, O_RDONLY);
	if (info->fd == -1)
		return (-1);
	info->av_path = path;
	return (1);
}

static int	check_order(t_info *info, char **li)
{
	int	ret;

	ret = -1;
	if (ft_strncmp(li[0], "NO", 3) == 0)
		ret = 0;
	else if (ft_strncmp(li[0], "SO", 3) == 0)
		ret = 1;
	else if (ft_strncmp(li[0], "WE", 3) == 0)
		ret = 2;
	else if (ft_strncmp(li[0], "EA", 3) == 0)
		ret = 3;
	else if (ft_strncmp(li[0], "F", 2) == 0)
		ret = 4;
	else if (ft_strncmp(li[0], "C", 2) == 0)
		ret = 5;
	if (ret == -1 || (ret != -1 && info->check_li[ret] == 1))
		return (-1);
	info->check_cnt++;
	if (info->check_cnt > 6)
		return (-1);
	info->check_li[ret] = 1;
	return (ret);
}

static int	set_color(t_info *info, int ret, char *str)
{
	int		i;
	char	**li;
	int		n;

	if (check_arr_size(str, ',', 3) == -1)
		return (-1);
	i = -1;
	li = ft_split(str, ',');
	while (++i < 3)
	{
		n = ft_atoi(li[i]);
		if (n < 0 || n > 255)
		{
			free_arr(li);
			return (-1);
		}
		if (ret == 4)
			info->f_rgb[i] = n;
		else if (ret == 5)
			info->c_rgb[i] = n;
	}
	free_arr(li);
	return (1);
}

static int	check_element_line(t_info *info, char *line)
{
	char	**li;
	int		ret;

	if (ft_strlen(line) == 0)
		return (1);
	if (check_arr_size(line, ' ', 2) == -1)
		return (-1);
	li = ft_split(line, ' ');
	ret = check_order(info, li);
	if (ret >= 0 && ret <= 3)
		info->texture_image_paths[ret] = ft_strdup(li[1]);
	else if (ret >= 4 && ret <= 5)
	{
		if (set_color(info, ret, li[1]) == -1)
		{
			free_arr(li);
			return (-1);
		}
	}
	free_arr(li);
	return (ret);
}

int	check_element(t_info *info)
{
	char	*line;

	while (info->check_cnt < 6)
	{
		if (get_next_line(info->fd, &line) == 0)
		{
			close(info->fd);
			free(line);
			return (-1);
		}
		if (check_element_line(info, line) == -1)
		{
			close(info->fd);
			free(line);
			return (-1);
		}
		free(line);
	}
	return (1);
}
