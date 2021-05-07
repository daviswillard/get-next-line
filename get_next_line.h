#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

int		get_next_line(int fd, char **line);

char	*ft_strjoin(char const *s1, char const *s2);

char	*ft_strchr(const char *s, int c);

char	*ft_strdup(const char *s1);

int		ft_strlen(char const *s);

char	*ft_strcpy(char *dst, const char *src);

char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif
