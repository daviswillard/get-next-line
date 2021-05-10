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
	int		cntr1;
	int		cntr2;
	int		cntr;
	char	*ret;

	cntr = -1;
	cntr1 = 0;
	cntr2 = 0;
	while (s1[cntr1])
		cntr1++;
	while (s2[cntr2])
		cntr2++;
	ret = malloc(sizeof(*ret) * (cntr1 + cntr2 + 1));
	if (ret == NULL)
		return (NULL);
	while (++cntr < cntr1)
		ret[cntr] = s1[cntr];
	ret[cntr + cntr2] = '\0';
	while (--cntr2 >= 0)
		ret[cntr + cntr2] = s2[cntr2];
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
