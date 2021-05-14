#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

#define BUFF_SIZE 2

static void	ft_strdel(char **as)
{
	if (as)
	{
		free(*as);
		*as = NULL;
	}
	return ;
}

static char	*ft_strnew(size_t size)
{
	char	*s;
	size_t	i;

	i = 0;
	s = (char*)malloc(size + 1);
	if (s == NULL)
		return (NULL);
	while (i < size)
		s[i++] = 0;
	s[size] = '\0';
	return (s);
}

static char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*s2;
	size_t	i;

	i = 0;
	if (s == NULL)
		return (0);
	s2 = (char*)malloc(sizeof(char) * (len + 1));
	if (s2 == NULL)
		return (NULL);
	while (i < len)
	{
		s2[i] = s[start + i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

static int		ft_new_line(char **s, char **line, int fd, int ret)
{
	char	*tmp;
	int		len;

	len = 0;
	while (s[fd][len] != '\n' && s[fd][len] != '\0')
		len++;
	if (s[fd][len] == '\n')
	{
		*line = ft_strsub(s[fd], 0, len);
		tmp = ft_strdup(s[fd] + len + 1);
		free(s[fd]);
		s[fd] = tmp;
		if (s[fd][0] == '\0')
			ft_strdel(&s[fd]);
	}
	else if (s[fd][len] == '\0')
	{
		if (ret == BUFF_SIZE)
			return (get_next_line(fd, line));
		*line = ft_strdup(s[fd]);
		ft_strdel(&s[fd]);
	}
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static char	*s[255];
	char		buf[BUFF_SIZE + 1];
	char		*tmp;
	int			ret;

	if (fd < 0 || line == NULL)
		return (-1);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (s[fd] == NULL)
			s[fd] = ft_strnew(1);
		tmp = ft_strjoin(s[fd], buf);
		free(s[fd]);
		s[fd] = tmp;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (ret < 0)
		return (-1);
	else if (ret == 0 && (s[fd] == NULL || s[fd][0] == '\0'))
		return (0);
	return (ft_new_line(s, line, fd, ret));
}

int	main(void)
{
	int		fd;
	int		cond;
	int		k;
	char	*line;

	fd = open("text.txt", O_RDONLY);
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

///////////////////////////////////////////////////////////////////////////////
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
