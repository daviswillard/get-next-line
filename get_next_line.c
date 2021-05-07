#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

#define BUFFER_SIZE 20

/*static void	make_it_static(char *tails, char **cache, char *buf, char
**line)
{

}*/
int	get_next_line(int fd, char **line)
{
	char			buf[BUFFER_SIZE + 1];
	char			*tails;
	static char		*cache;
	size_t			read_bytes;

	if (cache)
	{
		*line = ft_strdup(cache);
		free(cache);
	}
	else
		*line = "";
	if (fd < 0 || !*line || read(fd, NULL, 0) < 0 || BUFFER_SIZE <= 0)
		return (-1);
	read_bytes = read(fd, buf, BUFFER_SIZE);
	while (read_bytes)
	{
		if (read_bytes < 0)
			return (-1);
		buf[BUFFER_SIZE] = 0;
		if (ft_strchr(buf, '\n'))
		{
			tails = ft_strchr(buf, '\n');
			*tails++ = 0;
			cache = ft_strdup(tails);
			*line = ft_strjoin(*line, buf);
			return (1);
		}
		*line = ft_strjoin(*line, buf);
		read_bytes = read(fd, buf, BUFFER_SIZE);
	}
	return (0);
}

int	main(void)
{
	int		fd;
	int		cond;
	int		k;
	char	*line;

	fd = open("text.txt", O_RDONLY);
	k = 0;
	line = "";
	cond = get_next_line(fd, &line);
	while (cond)
	{
		k++;
		if (cond < 0)
			return (-1);
		printf("k = %d: %s\n", k, line);
		free(line);
		cond = get_next_line(fd, &line);
	}
	close(fd);
	return (0);
}
