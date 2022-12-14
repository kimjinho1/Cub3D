/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 18:24:13 by jinhokim          #+#    #+#             */
/*   Updated: 2022/12/14 18:24:14 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_map2_insert(t_info *info, char *map_low, char *line)
{
	int	i;

	i = -1;
	while (line[++i])
		map_low[i] = line[i];
	i--;
	while (++i < info->map_width)
		map_low[i] = ' ';
	map_low[i] = 0;
}

static int	check_map2_init(t_parse *parse, t_info *info)
{
	int		i;
	char	*line;

	i = -1;
	info->map = (char **)malloc(sizeof(char *) * info->map_height);
	while (++i < info->map_height)
		info->map[i] = (char *)malloc(sizeof(char) * info->map_width);
	i = -1;
	while (1)
	{
		get_next_line(parse->fd, &line);
		if (ft_strncmp(line, parse->first_line, info->map_width) == 0)
			break ;
		free(line);
	}
	while (++i < info->map_height)
	{
		check_map2_insert(info, info->map[i], line);
		free(line);
		get_next_line(parse->fd, &line);
	}
	free(line);
	close(parse->fd);
	return (0);
}

static int	check_map2_valid_loop(t_info *info, int ga, int se)
{
	if (info->map[se][ga] == '0' || info->map[se][ga] == info->ewsn)
	{
		if (ga <= 0 || se <= 0 || ga >= info->map_width - 1 || \
			se >= info->map_height - 1)
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

static int	check_map2_valid(t_info *info)
{
	int	i;
	int	j;

	i = -1;
	while (++i < info->map_height)
	{
		j = -1;
		while (++j < info->map_width)
		{
			if (check_map2_valid_loop(info, j, i) == -1)
				return (-1);
			if (info->map[i][j] == 'N' || info->map[i][j] == 'E' || \
				info->map[i][j] == 'S' || info->map[i][j] == 'W')
			{
				info->player_y = (double)i + 0.5;
				info->player_x = (double)j + 0.5;
			}
		}
	}
	return (0);
}

int	check_map2(t_parse *parse, t_info *info)
{
	parse->fd = open(parse->av_path, O_RDONLY);
	if (parse->fd == -1)
		return (-1);
	if (check_map2_init(parse, info) == -1)
		return (-1);
	if (check_map2_valid(info) == -1 || info->ewsn == 0)
		return (-1);
	return (1);
}
