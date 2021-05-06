#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

#define BUFFER_SIZE 8

int get_next_line(int fd, char **line)
{
	char			buf[BUFFER_SIZE + 1];
	char 			*tails;
	static char 	*cache;
	size_t			read_bytes;


	if (!cache)
	{
		*line = ft_strdup(cache);
		free(cache);
	}
	else
		*line = "";
/*	if (fd < 0 || !*line || read(fd, NULL, 0) < 0 || BUFFER_SIZE <= 0)
		return (-1);*/
	while ((read_bytes = read(fd, buf, BUFFER_SIZE)))
	{
		if (read_bytes < 0)
			return (-1);
		buf[BUFFER_SIZE] = 0;
		if ((tails = ft_strchr(buf, '\n')))
		{
			*tails++ = 0;
			cache = ft_strdup(tails);
			*line = ft_strjoin(*line, buf);
			return (1);
		}
		*line = ft_strjoin(*line, buf);
	}
	return (0);
}

int main(void)
{
	int		fd;
	int 	cond;
	int		k;
	char	*line;

	fd = open("text.txt", O_RDONLY);
	k = 0;
	line = "";
	while ((cond = get_next_line(fd, &line)))
	{
		k++;
		if (cond < 0)
			return (-1);
		printf("k = %d: %s\n", k, line);
		free(line);
	}
	return (0);
}
