/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 18:23:32 by jinhokim          #+#    #+#             */
/*   Updated: 2022/12/14 18:23:33 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_arr_size(char *str, char c, int n)
{
	int		i;
	char	**li;

	i = -1;
	li = ft_split(str, c);
	while (li[++i])
		;
	free_arr(li);
	if (i != n)
		return (-1);
	return (1);
}

int	texture_path_check(t_parse *parse, t_info *info)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		info->imgs[i].img = mlx_xpm_file_to_image(info->mlx, \
			parse->texture_image_paths[i], &info->imgs[i].width, \
			&info->imgs[i].height);
		if (!info->imgs[i].img)
			return (-1);
		info->imgs[i].data_addr = (int *)mlx_get_data_addr(
				info->imgs[i].img, &info->imgs[i].bpp, \
				&info->imgs[i].size, &info->imgs[i].endian);
	}
	return (1);
}

static int	check_map_line(t_parse *parse, t_info *info, char *line)
{
	int	i;

	i = -1;
	if (ft_strlen(line) == 0 && parse->empty_flag == 0)
		return (1);
	else if (ft_strlen(line) == 0 && parse->empty_flag != 0)
		return (-1);
	while (line[++i])
	{
		if (info->ewsn != 0 && (line[i] == 'N' || line[i] == 'S' || \
			line[i] == 'E' || line[i] == 'W'))
			return (-1);
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || \
			line[i] == 'W')
			info->ewsn = line[i];
		else if (line[i] != '1' && line[i] != ' ' && line[i] != '0')
			return (-1);
	}
	if (info->map_width < i)
		info->map_width = i;
	info->map_height++;
	parse->empty_flag = 1;
	return (1);
}

static int	check_map_free(t_parse *parse, char *line, int flag)
{
	close(parse->fd);
	free(line);
	return (flag);
}

int	check_map(t_parse *parse, t_info *info)
{
	char	*line;
	int		r;

	while (1)
	{
		r = get_next_line(parse->fd, &line);
		if (r == 0 && parse->empty_flag == 0)
			return (check_map_free(parse, line, -1));
		if (r == 1 && parse->empty_flag == 1 && ft_strlen(line) == 0)
			return (check_map_free(parse, line, -1));
		if (r == 0 && parse->empty_flag == 1 && ft_strlen(line) != 0)
		{
			if (check_map_line(parse, info, line) == -1)
				return (check_map_free(parse, line, -1));
			return (check_map_free(parse, line, 1));
		}
		if (check_map_line(parse, info, line) == -1)
			return (check_map_free(parse, line, -1));
		if (info->map_height == 1)
			parse->first_line = ft_strdup(line);
		free(line);
	}
	return (1);
}
