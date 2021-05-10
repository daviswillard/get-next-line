#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE 100

static int 	tail_check(char **tail, char **line)
{
	char	*tempest;

	if (*tail)
	{
		tempest = ft_strchr(*tail, '\n');
		if (tempest)
		{
			*tempest++ = '\0';
	//		printf("tail_check  %s\n", *tail);
			*line = ft_strdup(*tail);
			*tail = ft_strdup(tempest);
			return (1);
		}
		else
		{
			*line = ft_strdup(*tail);
			*tail = NULL;
			free(*tail);
		}
	}
	else
		*line = "";
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char		*tail;
	char			*temp;
	char			buf[BUFFER_SIZE + 1];
	size_t			bytes_read;

	if (!line || fd < 0 || read(fd, buf, 0) < 0 || BUFFER_SIZE <= 0)
		return (-1);
	if (tail_check(&tail, line))
		return (1);
	bytes_read = read(fd, buf, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buf[BUFFER_SIZE] = '\0';
		tail = ft_strdup(ft_strchr(buf, '\n'));
		if (tail)
		{
			*tail++ = '\0';
			*ft_strchr(buf, '\n') = '\0';
			*line = ft_strjoin(*line, buf);
			return (1);
		}
		*line = ft_strjoin(*line, buf);
		bytes_read = read(fd, buf, BUFFER_SIZE);
	}
	if (bytes_read < 0)
		return (-1);
	return (0);
}

int	main(int argc, char **argv)
{
	int		fd;
	int		cond;
	int		k;
	char	*line;

	if (argc < 2)
		fd = 1;
	else
		fd = open(argv[1], O_RDONLY);
	k = 0;
	line = "";
	cond = get_next_line(fd, &line);
	while (cond)
	{
		if (cond < 0)
			return (-1);
		printf("k = %d\n\n%s\n\n", k, line);
		free(line);
		k++;
		cond = get_next_line(fd, &line);
		if (k > 30)
			return (-1);
	}
	close(fd);
	return (0);
}
