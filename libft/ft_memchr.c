#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*a;
	size_t			i;
	unsigned char	c2;

	i = 0;
	c2 = (unsigned char)c;
	a = (unsigned char *) s;
	while (i < n)
	{
		if (*a == c2)
			return (a);
		++a;
		++i;
	}
	return (0);
}
