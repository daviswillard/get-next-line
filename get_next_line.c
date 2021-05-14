#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE 400

static int 	tail_check(char **tail, char **line)
{
	char	*tempest;
	char 	*temp;

	if (*tail)
	{
		free(*line);
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
		*line = ft_strdup(*tail);
	}
	else
	{
		*line = ft_strdup("");
		printf("%p\n", *line);
	}
	return (0);
}

static void		ft_liberty(char **line, char *buf)
{
	char *temp;

	temp = *line;
	*line = ft_strjoin(*line, buf);
	free(temp);
}

int	get_next_line(int fd, char **line)
{
	static char		*tail;
	static int 		count;
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
			tail = ft_strdup(tail + 1);
			free(tmp);
			*ft_strchr(buf, '\n') = '\0';
			ft_liberty(line, buf);
			return (1);
		}
		ft_liberty(line, buf);
		bytes_read = read(fd, buf, BUFFER_SIZE);
	}
	if (bytes_read < 0)
		return (-1);
	ft_liberty(line, buf);
	return (0);
}

int	main(void)
{
	int		fd;
	int		cond;
	int		k;
	char	*line;

	fd = open("text.txt", O_RDONLY);
	k = 1;
	line = "";
	cond = get_next_line(fd, &line);
	while (cond)
	{
		if(cond < 0)
			return (-1);
		printf("%d\n%s\n", k, line);
		free(line);
		line = NULL;
		k++;
		cond = get_next_line(fd, &line);
	}
	while (1)
		NULL;
	close(fd);
	return (0);
}
