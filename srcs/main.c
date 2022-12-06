#include "cub3d.h"

int	main(int ac, char **av)
{
	t_info	info;

	if (ac != 2)
		perror_exit("argument error");
	if (check_cub(&info, av[1]) == -1)
		perror_exit("infile error");
	init_info(&info);
	if (check_element(&info) == -1)
		perror_exit("element error");
	if (texture_path_check(&info) == -1)
		perror_exit("texture path error");
	if (check_map(&info) == -1)
		perror_exit("map error");
	if (check_map2(&info) == -1)
		perror_exit("map2 error");
	free_info(&info);
	return (0);
}
