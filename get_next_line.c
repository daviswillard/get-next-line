#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE 8

static int 	tail_check(char **tail, char **line)
{
	char	*tempest;
	char 	*temp;

	if (*tail)
	{
		tempest = ft_strchr(*tail, '\n');
		if (tempest)
		{
			*tempest++ = '\0';
			*line = ft_strdup(*tail);
			temp = *tail;
			*tail = ft_strdup(tempest);
			free(temp);
			return (1);
		}
		else
			*line = ft_strdup(*tail);
	}
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char		*tail;
	char 			*tmp;
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
		tmp = tail;
		tail = ft_strdup(ft_strchr(buf, '\n'));
		free(tmp);
		if (tail)
		{
			tmp = tail;
			*tail++ = '\0';
			tail = ft_strdup(tail);
			free(tmp);
			*ft_strchr(buf, '\n') = '\0';
			tmp = *line;
			*line = ft_strjoin(*line, buf);
			free(tmp);
			return (1);
		}
		tmp = *line;
		*line = ft_strjoin(*line, buf);
		free(tmp);
		bytes_read = read(fd, buf, BUFFER_SIZE);
	}
	if (bytes_read < 0)
		return (-1);
	return (0);
}

int	main(void)
{
	int		fd;
	int		cond;
	int		k;
	char	*line;

	fd = open("../text.txt", O_RDONLY);
	k = 0;
	line = ft_strdup("");
	cond = get_next_line(fd, &line);
	while (cond)
	{
		if(cond < 0)
			return (-1);
		printf("%s\n",line);
		free(line);
		k++;
		cond = get_next_line(fd, &line);
	}
	close(fd);
	return (0);
}