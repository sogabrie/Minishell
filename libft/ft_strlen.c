#include "libft.h"

size_t	ft_strlen(const char *a )
{
	int	i;

	i = 0;
	if (!a)
		return (0);
	while (a[i] != 0)
		++i;
	return (i);
}
