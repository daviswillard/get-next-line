#include "get_next_line.h"

int	ft_strlen(char const *s)
{
	int	counter;

	counter = 0;
	if (s)
		while (*s++)
			counter++;
	return (counter);
}



char	*ft_strjoin(char const *s1, char const *s2)
{
	char 	*dup_ret;
	char	*ret;

	ret = malloc(sizeof(ret) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (ret == NULL)
		return (NULL);
	dup_ret = ret;
	while (*s1)
		*dup_ret++ = *s1++;
	while (*s2)
		*dup_ret++ = *s2++;
	*dup_ret = '\0';
	return (ret);
}

char	*ft_strchr(const char *s, int c)
{
	char	ch;

	ch = c;
	while (*s)
	{
		if (*s == ch)
			return ((char *)s);
		s++;
	}
	if (*s == ch)
		return ((char *)s);
	return (NULL);
}

char	*ft_strdup(const char *s1)
{
	char	*ret;
	char	*ptr;

	ret = malloc(sizeof(char *) * ft_strlen(s1) + 1);
	if (ret == NULL || !s1)
		return (NULL);
	ptr = ret;
	while (*s1)
		*ptr++ = *s1++;
	*ptr = '\0';
	return (ret);
}

char 	*ft_strcpy(char *dst, const char *src)
{
	char	*ret;

	ret = dst;
	while (*src)
		*dst++ = *src++;
	*dst = *src;
	return (ret);
}
