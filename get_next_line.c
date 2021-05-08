#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE 100

static int	check_cache(char **cache, char **line)
{
	char *tails;

	*line = "";
	tails = NULL;
//	printf("cache = %s\n\n", *cache);
	if (*cache)
	{
		tails = ft_strchr(*cache, '\n');
		if (tails != NULL)
		{
			*tails++ = '\0';
			printf("tails = %s\n\n", tails);
			*line = ft_strdup(*cache);
			printf("line = %s\n\n", *line);
			free(*cache);
			*cache = ft_strdup(tails);
			printf("cache = %s\n\n", *cache);
			return (1);
		}
		else
		{
			*line = ft_strdup(*cache);
			free(*cache);
		}
	}
	return (0);
}

/*static int returner(char **tails, char **cache, char **line, char **buf)
{
	if (ft_strchr(*buf, '\n'))
	{
		*tails = ft_strchr(*buf, '\n');
		**tails++ = 0;
		*cache = ft_strdup(*tails);
		*line = ft_strjoin(*line, *buf);
		return (1);
	}
	else
		return (0);
}
*/
int	get_next_line(int fd, char **line)
{
	char 		buf[BUFFER_SIZE + 1];
	char 		*tails;
	static char *cache;
	int 		read_bytes;
	int 		k;

	if (fd < 0 || !*line || read(fd, NULL, 0) < 0 || BUFFER_SIZE <= 0)
		return (-1);
	if ((k = check_cache(&cache, line)))
	{
		printf("%d\n", k);
		return (1);
	}
	printf("%d\n", k);
	read_bytes = 1;
	while (read_bytes)
	{
		read_bytes = read(fd, buf, BUFFER_SIZE);
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
//		printf("k = %d: %s\n", k, line);
		printf("k = %d: %s\n********************************\n", k, line);
		free(line);
		cond = get_next_line(fd, &line);
		if (k > 30)
			return (0);
	}
	close(fd);
	return (0);
}

/*	42-43
 	if (cache)
	{
		*line = ft_strdup(cache);
		cache = NULL;
		free(cache);
	}
	else
		*line = "";*/
