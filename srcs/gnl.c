#include "cub3d.h"

static int	gnl_check_newline(char *stack)
{
	int			i;

	i = 0;
	while (stack[i])
	{
		if (stack[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static int	gnl_split_stack(char **stack, char **line, int nl_idx)
{
	char		*temp;
	int			len;

	(*stack)[nl_idx] = '\0';
	*line = gnl_strdup(*stack);
	len = gnl_strlen(*stack + nl_idx + 1);
	if (len == 0)
	{
		free(*stack);
		*stack = 0;
		return (1);
	}
	temp = gnl_strdup(*stack + nl_idx + 1);
	free(*stack);
	*stack = temp;
	return (1);
}

static int	gnl_return_all(char **stack, char **line, int ret)
{
	int			nl_idx;

	if (ret < 0)
		return (-1);
	if (*stack)
	{
		nl_idx = gnl_check_newline(*stack);
		if (nl_idx >= 0)
			return (gnl_split_stack(stack, line, nl_idx));
		else
		{
			*line = *stack;
			*stack = 0;
			return (0);
		}
	}
	*line = gnl_strdup("");
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char	*stack[OPEN_MAX];
	char		buf[BUFFER_SIZE + 1];
	int			ret;
	int			nl_idx;

	if ((fd < 0) || (line == 0) || (BUFFER_SIZE <= 0))
		return (-1);
	ret = read(fd, buf, BUFFER_SIZE);
	while (ret > 0)
	{
		buf[ret] = '\0';
		stack[fd] = gnl_strjoin(stack[fd], buf);
		nl_idx = gnl_check_newline(stack[fd]);
		if (nl_idx >= 0)
			return (gnl_split_stack(&stack[fd], line, nl_idx));
		ret = read(fd, buf, BUFFER_SIZE);
	}
	return (gnl_return_all(&stack[fd], line, ret));
}
