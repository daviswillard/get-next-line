#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE 200

/*char	*check_cache(char *cache, char **line)
{
	char	*ptr;

	ptr = NULL;
	if (cache)
	{
		ptr = ft_strchr(cache, '\n');
		if (ptr)
		{
			*ptr++ = '\0';
			*line = ft_strdup(cache);
			cache = ft_strcpy(cache, ptr);
		}
		else
		{
			*line = ft_strdup(cache);
			cache = NULL;
			free(cache);
		}
	}
	else
		*line = "";
	return (ptr);
}
*/
int	get_next_line(int fd, char **line)
{
	char			buf[BUFFER_SIZE + 1];
	char			*tails;
	static char		*cache;
	int 			read_bytes;

	if (fd < 0 || !*line || read(fd, NULL, 0) < 0 || BUFFER_SIZE <= 0)
		return (-1);
//	tails = check_cache(cache, line);
	if (cache)
	{
		*line = ft_strdup(cache);
		cache = NULL;
		free(cache);
	}
	else
		*line = "";
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
