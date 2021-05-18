#include "get_next_line.h"

#define BUFFER_SIZE 1

static int 	tail_check(char **tail, char **line)
{
	char		*tempest;

	if (*tail)
	{
		free(*line);
		tempest = ft_strchr(*tail, '\n');
		if (tempest)
		{
			*tempest++ = '\0';
			*line = ft_strdup(*tail);
			free(*tail);
			*tail = ft_strdup(tempest);
			return (1);
		}
		*line = ft_strdup(*tail);
		free(*tail);
	}
	else
		*line = ft_strdup("");
	return (0);
}

static void		ft_liberty(char **dst, char *src)
{
	char *temp;

	temp = ft_strjoin(*dst, src);
	free(*dst);
	*dst = temp;
}

static char 	*buf_refill(char *buf)
{
	free(buf);
	buf = malloc(BUFFER_SIZE + 1);
	if (buf == NULL)
		return (NULL);
	return (buf);
}

int	get_next_line(int fd, char **line)
{
	static char		*tail;
	char			*buf;
	size_t			bytes_read;

	if (!line || fd < 0 || read(fd, buf, 0) < 0 || BUFFER_SIZE <= 0)
		return (-1);
	buf = malloc(BUFFER_SIZE + 1);
	if (buf == NULL)
		return (-1);
	if (tail_check(&tail, line))
	{
		free(buf);
		return (1);
	}
	bytes_read = read(fd, buf, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buf[bytes_read] = '\0';
		tail = ft_strchr(buf, '\n');
		if (tail != NULL)
		{
			*tail++ = '\0';
			tail = ft_strdup(tail);
			ft_liberty(line, buf);
			free(buf);
			return (1);
		}
		ft_liberty(line, buf);
		buf = buf_refill(buf);
		bytes_read = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	return (0);
}
