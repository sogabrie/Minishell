#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;
	size_t			len;

	i = 0;
	if (!s || !f)
		return ;
	len = ft_strlen(s);
	while (i < (unsigned int)len)
	{
		f(i, &s[i]);
		++i;
	}
}
