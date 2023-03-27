#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	s;

	s = 0;
	while (s < n)
	{
		if (s1[s] > s2[s] || s1[s] < s2[s])
			return ((unsigned char)s1[s] - (unsigned char)s2[s]);
		if (s1[s] == '\0' || s2[s] == '\0')
			return (0);
		++s;
	}
	return (0);
}
